/*
   qd.h
   University of Michigan
   EECS 461, Embedded Control Systems
   FlexTimer Module (FTM): Quadrature Decode
   Read Chapter 45 in S32K144 User's Manual
    Section 45.5.27: Quadrature Decoder Mode

   Revision History:
     2017-03-14  RMC
     2017-03     Paul Domanico
 */
#include "qd.h"

/* Quadrature Decoding Parameters */
#define ENCODER_COUNT 4000 /* fill in */

#define QD_PHA_PORT PORTA/* fill in */
#define QD_PHB_PORT PORTA/* fill in */
#define QD_PHA_PIN  13/* fill in */
#define QD_PHB_PIN  12/* fill in */

/******************************************************************************
* Function: init_QD
* Description: Initializes eTimer for Quadrature Decoding
******************************************************************************/
void initQD()
{
  /* Initialize Phase A and B input PCR */
  QD_PHA_PORT->PCR[QD_PHA_PIN] |= PORT_PCR_MUX(0b110);
  QD_PHB_PORT->PCR[QD_PHB_PIN] |= PORT_PCR_MUX(0b110);

  /* Set up FTM2 for Quadrature Decode */
  FTM2->MODE |= FTM_MODE_WPDIS_MASK; /* Disable write protection (should already be disabled) */
  FTM2->MOD = FTM_MOD_MOD(0xFFFF)  /* fill in */;
  FTM2->CNTIN = (FTM2->CNTIN & ~FTM_CNTIN_INIT_MASK) | FTM_CNTIN_INIT(0x0000) /* fill in */;
  FTM2->QDCTRL =  FTM_QDCTRL_QUADEN(0b1)/* fill in */;   /* Enable QD mode */

  FTM2->CONF |= FTM_CONF_BDMMODE(0b11); /* Optional: enable in debug mode */

  return;
}

/******************************************************************************
 * Function:    updateCounter
 * Description: Returns an updated counter value that keeps track of absolute
 *              wheel position
 ******************************************************************************/
int32_t updateCounter()
{
  static int32_t TOTAL = 0;
  static uint16_t PREV = 0;
  uint16_t CURR = 0;

  CURR=FTM2->CNT & FTM_CNT_COUNT_MASK;
  TOTAL+=((int16_t) (CURR - PREV)); /* */
  PREV=CURR;
  return (TOTAL);/* fill in */
}


/******************************************************************************
 * Function:    updateAngle
 * Description: Returns the angle of the wheel
 ******************************************************************************/
float updateAngle()
{

  int angle;
  int32_t COUNTS;
  COUNTS=updateCounter();
  angle=0.09*(int)(COUNTS);
  return angle; /* fill in  -- don't reinvent the wheel*/
}
