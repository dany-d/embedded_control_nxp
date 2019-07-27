
#include "eecs461.h"
#include "qd.h"
#include "pwm.h"
#include "worlds.h"
#include "adc.h"
#include <stdint.h>
#include "gpio.h"

int main(void)
{
  int section = 6;
  uint32_t input_GPIO;
  float dutyCycle=0;
  float angle=0;
  float torque;
  int32_t counter = 0;
  initEECS461();
  
  
  initQD();// Initialize QD and ADC
  init_ADC0_single();/* fill in */

  // Initialize PWMs
  int freq=20000;
  initPWMPCRs();
  initPWM(MOTOR_SUBMODULE,MOTOR_CHANNEL,MOTOR_FREQUENCY,0.5);
  initPWM(FILTER_SUBMODULE,FILTER_CHANNEL,FILTER_FREQUENCY,0.5); // Filter

  // Intialize for GPIO Pin
  initGPDO(3, 0);

  while(1)
  {
    switch(section)
    {
	case 1:
	  outputTorque(0);// 0 Torque
	  break;
    case 2: //Analog Input Control of PWM
      input_GPIO = read_ADC0_single(0);
      dutyCycle=(float)(0.52/5000)*input_GPIO+0.24;
      writeGPIO(3,0,1);
      setPWM(0,0, 20000, dutyCycle);
      writeGPIO(3,0,0);/* fill in */
      break;
    case 3: //Change PWM Frequency to 1 kHz torque = 0 N-mm
      setPWM(0,0, freq, 0.5);
      outputTorque(0);
       /* fill in */ 
      break;
    case 4:
      outputTorque(200); //Set torque to 200 N-mm
       /* fill in */ 
      break;
    case 5: //Virtual Spring
      writeGPIO(3,0,1);
      angle = updateAngle();
      torque = virtualSpring(angle);
      outputTorque((torque));
      writeGPIO(3,0,0);
       /* fill in */ 
      break;
    case 6: // Virtual Wall
      angle = updateAngle();
      torque = virtualWall(angle);
      outputTorque((torque)); /* fill in */
      break;
    }
  }
}
