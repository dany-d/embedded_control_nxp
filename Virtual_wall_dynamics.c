

#include "S32K144.h"
#include "eecs461.h"
#include "LPIT.h"
#include "LPUART.h"
#include "qd.h"
#include "pwm.h"
#include "worlds.h"

extern float gk=17.7778;
extern float gJ=0.45;

void wallDamper(void)
{
  /* ISR for the wall-damper system */
  static float prevangle=0;
  float angle;
  angle = updateAngle();
  float vel = (angle - prevangle)/0.001;

  outputTorque(virtualWallDamper(angle,vel));
  clearFlagLPIT(0);/* Make sure to clear interrupt flag */
  prevangle = angle;
}


void springDamper(void)
{
	/* ISR for the spring-damper system */
  static float prevangle=0;
  float angle;
  angle = updateAngle();
  float vel = (angle - prevangle)/0.001;

  outputTorque(virtualSpringDamper(angle, vel));
  clearFlagLPIT(1);/* Make sure to clear interrupt flag */
  prevangle = angle;
  /*  Make sure to clear interrupt flag  */

}

void springMass(void)
{
  float angle = 0;
	/* ISR for the spring-mass system */
  angle = updateAngle();

  outputTorque(virtualSpringMass(angle));
  clearFlagLPIT(1);/* Make sure to clear interrupt flag */

  /* Make sure to clear interrupt flag */

}

void springMassDamper(void)
{
	/* ISR for the spring-mass-damper system */
    static float prevangle=0;
    float angle;
    angle = updateAngle();
    float vel = (angle - prevangle)/0.001;
    /* ISR for the spring-mass system */

    outputTorque(virtualSpringMassDamper(angle,vel));
    prevangle=angle;
    clearFlagLPIT(1);
  /* Make sure to clear interrupt flag  */

}

void knobIndents(void)
{
	/* ISR for the virtual knob system */
  static float prevangle=0;
  float angle;
  angle = updateAngle();
  float velocity = (angle - prevangle)/0.001;

  outputTorque(virtualKnob(angle,velocity));
  prevangle=angle;
  clearFlagLPIT(1);
  /* Make sure to clear interrupt flag */

}

int main(void) {


  initEECS461();
  initQD();
  enableLPIT();

  char byte_in = 0;
  void (*interrupt)(void);
  int section = 6;

  // Initialize PWMs
  initPWMPCRs();

  initPWM(MOTOR_SUBMODULE, MOTOR_CHANNEL, MOTOR_FREQUENCY, 0.5f);
  initPWM(FILTER_SUBMODULE, FILTER_CHANNEL, FILTER_FREQUENCY, 0.5f);

  if(section == 6)
  {
    LPUART1_init();
    LPUART1_transmit_string("\n\n\n\n\n\n\n\rSerial Output Enabled.");
  }
  switch(section)
  {
    case 1:
      interrupt = &wallDamper;
      break;

    case 2:
      interrupt = &springDamper;
      break;

    case 3:
      interrupt = &springMass;
      break;

    case 4:
      interrupt = &springMassDamper;
      break;

    case 5:
      interrupt = &springMassDamper;
      break;

    case 6:
      interrupt = &knobIndents;
      break;
  }

  //Fill in the arguments to initialize the appropriate interrupt routine for
  //each part of the lab. Be sure to use the correct channel specified in worlds.h
  initLPIT(WORLDISR_LPIT_CHANNEL, WORLDISR_FREQUENCY,interrupt, 0xC);

  LPUART1_transmit_string("\n\rSerial Output Enable...........");

  while(1){
    if(section == 5){
      byte_in = LPUART1_receive_char();

      if(byte_in=='2' || byte_in=='1')
          {
            DISABLE_INTERRUPTS();
            if(byte_in=='2')
            {
              gk=gk*1.1;
              LPUART1_transmit_string("\n\rK increased");
            }
            else{
              gk=gk*0.9;
              LPUART1_transmit_string("\n\rK Decreased");
            }
            ENABLE_INTERRUPTS();
          }

      if(byte_in=='4' || byte_in=='3')
          {
            DISABLE_INTERRUPTS();
            if(byte_in=='4')
            {
              gJ=gJ*1.1;
              LPUART1_transmit_string("\n\rInertia Increased");
            }
            else{
              gJ=gJ*0.9;
              LPUART1_transmit_string("\n\rInertia Decreased");
            }
            ENABLE_INTERRUPTS();
          }
      /* adjust K and M from the keyboard. Must be a critical section. */
    }
  }

}
