#include <string.h>
#include <stdlib.h>

#include "eecs461.h"
#include "S32K144.h"
#include "gpio.h"
#include "adc.h"
#include "flexcan.h"
#include "pwm.h"
#include "qd.h"
#include "worlds.h"
#include "LPIT.h"

/* define VWALLA, VWALLB, or VCHAIN depending on lab section */
#define VCHAIN

#ifdef VWALLA
void virt_wall_A(void);
#endif

#ifdef VWALLB
void virt_wall_B(void);
#endif

#ifdef VCHAIN
void virt_chain();
#endif


//*************************************************************************************
// EDIT STATION IDS
#define STATIONBASEID 40 /* ID of your lab station */
#define VWPARTNERID 60   /* ID of your partner's lab station for the virtual wall */
#define CHAIN_A_ID 30    /* ID of the station to your "left" */
#define CHAIN_B_ID 100    /* ID of the station to your "right" */
//*************************************************************************************

const uint16_t vwA_tx_ID = 0 + STATIONBASEID;
const uint16_t vwA_rx_ID = 1 + VWPARTNERID;
const uint16_t vwB_tx_ID = 1 + STATIONBASEID;
const uint16_t vwB_rx_ID = 0 + VWPARTNERID;

const uint8_t vwA_tx_buffnum = 0;
const uint8_t vwA_rx_buffnum = 1;
const uint8_t vwB_tx_buffnum = 2;
const uint8_t vwB_rx_buffnum = 3;

const uint16_t chain_tx_ID = 2 + STATIONBASEID;
const uint16_t chainA_rx_ID = 2 + CHAIN_A_ID;
const uint16_t chainB_rx_ID = 2 + CHAIN_B_ID;

const uint8_t chain_tx_buff_num = 0;
const uint8_t chainA_rx_buff_num = 1;
const uint8_t chainB_rx_buff_num = 2;

/* Shared Data: the CAN message-received ISR copies new data into
 * the following variables */
static volatile float vw_torque=0;	/* wall torque (FLOAT32, N-mm) */
static volatile float posA=0;		/* chain position A (FLOAT32, N-mm) */
static volatile float velA=0;		/* chain velocity A (FLOAT32, N-mm) */
static volatile float posB=0;		/* chain position B (FLOAT32, N-mm) */
static volatile float velB=0;		/* chain velocity B (FLOAT32, N-mm) */

/***************************************************************************
 * Function:	rx_ISR()
 * Description:	This interrupt is called when a CAN message is received.
 ***************************************************************************/
void rx_ISR(void){

	#ifdef VWALLA
    CAN_RXINFO rxinfo;
    int ret;

    /* Message for: Virtual Wall A */
    /* First check to see if there is a new message in the buffer */
    if (can_get_buff_flag(vwA_rx_buffnum) == 1 )
    {
        rxinfo.buff_num = vwA_rx_buffnum;
        ret = can_rxmsg(&rxinfo);

        if(ret!=0) //Read not succesfull
        {
            exit(2);
        }
        if(ret == 0 && rxinfo.length == 4)
        {
            memcpy(&vw_torque, rxinfo.data, sizeof(vw_torque));
        }
    }
	#endif

	#ifdef VWALLB
    /* Message for: Virtual Wall B */
    /* First check to see if there is a new message in the buffer */
    if ( can_get_buff_flag(vwB_rx_buffnum) == 1 ) {
        virt_wall_B();/* Let virt_wall_B() handle this */
    /* fill in */
    }
	#endif

	#ifdef VCHAIN
    CAN_RXINFO rxinfo;
    int ret;
    /* Message for: Virtual Chain (from A) */
    /* First check to see if there is a new message in the buffer */

    //** NOTE: position and velocity are sent together as a package.
    //**       position is the first four bytes, and velocity is
    //**       the second 4 bytes.

    if( can_get_buff_flag(chainA_rx_buff_num) == 1 )
    {
        rxinfo.buff_num = chainA_rx_buff_num;
        ret = can_rxmsg(&rxinfo);

        if(ret!=0) //Read not succesfull
        {
            exit(2);
        }

        if(ret == 0 && rxinfo.length == 8)
        {
            memcpy(&posA, rxinfo.data, sizeof(posA));
            memcpy(&velA, rxinfo.data+4, sizeof(velA));
        }

    }

    /* Message for: Virtual Chain (from B) */
    /* First check to see if there is a new message in the buffer */
    if(can_get_buff_flag(chainB_rx_buff_num) == 1 ){
        rxinfo.buff_num = chainB_rx_buff_num;
        ret = can_rxmsg(&rxinfo);

        if(ret!=0) //Read not succesfull
        {
            exit(2);
        }

        if(ret == 0 && rxinfo.length == 8)
        {
            memcpy(&posB, rxinfo.data, sizeof(posB));
            memcpy(&velB, rxinfo.data+4, sizeof(velB));
        }

        clearFlagLPIT(CAN_RX_ISR_CHANNEL);

    }
    #endif
}

/***************************************************************************
 * Function:	virt_wall_A()
 * Description:	Implements the sensing and actuation of the virtual wall.
 *				It applies the calculated torque received from wall B.
 *				It then reads the wheel position and transmits it to wall B.
 * Shared Data: vw_torque (FLOAT32, N-mm)
 *
 * 1. Apply the current torque value (last received)
 * 2. Read the wheel position
 * 3. Transmit the wheel position in a CAN message
 ***************************************************************************/
#ifdef VWALLA
void virt_wall_A() {
	CAN_TXINFO txinfo;		/* buffer to tx wheel angle */
	float curr_angle = 0;
	int ret;

    outputTorque(vw_torque);

    curr_angle = updateAngle();

    txinfo.buff_num = vwA_tx_buffnum;
    memcpy(txinfo.data, &curr_angle, sizeof(curr_angle));
    txinfo.length = sizeof(curr_angle);
    txinfo.id = vwA_tx_ID;
    ret = can_txmsg(&txinfo);


    if(can_txmsg(&txinfo) != 0) //Read not succesfull
    {
        exit(3);

    }

    clearFlagLPIT(CAN_TX_ISR_CHANNEL);
}
#endif


 /***************************************************************************
 * Function:	virt_wall_B()
 * Description:	Implements the computation of the virtual wall.
 *				It calculates torque from the received position
 *				value from wall A.
 *
 * 1. Read the CAN message
 * 2. Calculate the torque
 * 3. Transmit the torque as a CAN message
 ***************************************************************************/
#ifdef VWALLB
 void virt_wall_B(void) {
	CAN_RXINFO rxinfo;
	CAN_TXINFO txinfo;

	float curr_angle;
	float torque;
	int ret;
  float k=500;

   rxinfo.buff_num = vwB_rx_buffnum;
   ret = can_rxmsg(&rxinfo);

   if(ret != 0) //Read not succesfull
   {
       exit(0);

   }

   if(ret == 0 && rxinfo.length == 4)
   {
       memcpy(&curr_angle, rxinfo.data, sizeof(curr_angle));
   }


   torque =virtualWall(curr_angle) ;

   txinfo.buff_num = vwB_tx_buffnum;
   memcpy(txinfo.data, &torque, sizeof(torque));
   txinfo.length = sizeof(torque);
   txinfo.id = vwB_tx_ID;
   can_txmsg(&txinfo);

   clearFlagLPIT(CAN_TX_ISR_CHANNEL);
}
#endif



 /***************************************************************************
 * Function:	virt_chain()
 * Description:	Implements one station in part of a chain.  The position and
 *				velocity of neighboring stations are received and the
 *				appropriate torque calculations are applied.
 * Equation:	k*(posA+posB-2*pos) + b*(velA+velB-2*vel)
 * Shared Data: posA (float, deg)
 *				velA (float, deg/s)
 *				posB (float, deg)
 *				velB (float, deg/s)
 *
 * 1. Read wheel angle (deg)
 * 2. Calculate wheel velocity (deg/s)
 * 3. Calculate & apply torque
 * 4. Transmit the wheel position and velocity
 ***************************************************************************/
#ifdef VCHAIN
const uint32_t vc_f = 250; /* frequency of the chain wall (Hz) */
const float k = 25.0;      /* spring-rate (N-mm/deg) */
const float b = 0.2;       /* damping (N-mm/(deg/s)) */

void virt_chain()
{
	CAN_TXINFO txinfo; 		/* buffer to transmit pos and velocity */
	float curr_angle, velocity,torque_left,torque_right,torque;

	static float prev_angle=0;

    curr_angle = updateAngle();

    velocity = (curr_angle - prev_angle) * vc_f;

    torque = k*(posA+posB-2*curr_angle) + b*(velA+velB-2*velocity);
    outputTorque(torque);
    prev_angle = curr_angle;
    txinfo.buff_num = chain_tx_buff_num;
    memcpy(txinfo.data, &curr_angle, sizeof(curr_angle));
    memcpy(txinfo.data+4, &velocity, sizeof(velocity));
    txinfo.length = 8;
    txinfo.id = chain_tx_ID;
    can_txmsg(&txinfo);

    if( can_txmsg(&txinfo) != 0) //Read not succesfull
    {
        exit(2);
    }

    clearFlagLPIT(CAN_TX_ISR_CHANNEL);

	return;
}
#endif


int main()
{
	int ret;

	/* Processor initialization */
	initEECS461();

	/* Configure QD module */
	initQD();

	/* Configure PWM module for motor */
	initPWMPCRs();
	initGPDI(DIP_BASE[0], DIP[0]);
	initPWM(MOTOR_SUBMODULE,MOTOR_CHANNEL,MOTOR_FREQUENCY, 0.50f);
	initPWM(FILTER_SUBMODULE,FILTER_CHANNEL,FILTER_FREQUENCY, 0.50f);

	/* Configure FlexCan module */
    initFlexcan();

    /* Enable the LPIT */
    enableLPIT();

	/* Set the CAN receive ISR */
    can_set_rxisr(&rx_ISR);

	#ifdef VWALLA
    can_rxbuff_init(vwA_rx_buffnum, vwA_rx_ID);
	#endif

	#ifdef VWALLB
            can_rxbuff_init(vwB_rx_buffnum, vwB_rx_ID);
	#endif

	#ifdef VCHAIN
        if(can_rxbuff_init(chainA_rx_buff_num, chainA_rx_ID) !=0)
        {
            exit(2);

        }
        if(can_rxbuff_init(chainB_rx_buff_num, chainB_rx_ID) !=0)
        {
            exit(2);
        }
	#endif

	/* Initialize the shared global variables */
	vw_torque = 0 ;	/* wall torque (FLOAT32, N-mm) */
	posA = 0 ;		/* chain position A (FLOAT32, N-mm) */
	velA = 0 ;		/* chain velocity A (FLOAT32, N-mm) */
	posB = 0 ;		/* chain position B (FLOAT32, N-mm) */
	velB = 0 ;		/* chain velocity B (FLOAT32, N-mm) */

	#ifdef VWALLA
		initLPIT(CAN_TX_ISR_CHANNEL, 250, &virt_wall_A, 0xB);
	#endif

	#ifdef VWALLB
		// Do nothing. VWALLB interrupted by CAN Rx only
	#endif

	#ifdef VCHAIN
		initLPIT(CAN_TX_ISR_CHANNEL, 250, &virt_chain, 0xB);
	#endif
	ENABLE_INTERRUPTS()


	// idle loop
	while (1)
	{}
   }
