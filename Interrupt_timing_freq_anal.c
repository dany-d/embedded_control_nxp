

#include "S32K144.h"
#include "eecs461.h"

#include "pwm.h"
#include "LPIT.h"
#include "adc.h"
#include "gpio.h"
#include "math.h"

#define LPIT0_CHANNEL  0

float sineTable[10]; // Ten samples/period
int sineIndex = 0;
const float pi = 3.14159;
static int i= 0;
float theta;
float dutyCycle;
int dip2;
int dip1;
int PWMfreq;


void IsrA(void){

 	/* Turn on LED */
  writeGPIO(3,0,1);
	/* fill in here */

	/* Read sine value */
  sineIndex = read_ADC0_single(0);
	/* fill in here */

	/* Calculate PWM duty cycle */
  dip2= readGPIO(4, 2);
  dip1= readGPIO(4, 1);

  if (dip2 ==1){
    dutyCycle=(float)0.8*sineIndex/5000+0.1;
  }
  else{
    dutyCycle=(float)0.2*sineIndex/5000+0.4;
  }
	/* fill in here */

	/* Set PWM frequency based on dipswitch */
  if (dip1 ==1){
    PWMfreq = 60000;
   }
   else{
    PWMfreq = 20000;
   }
	/* fill in here */

	/* Set PWM duty cycle and frequency */
    setPWM(0,0, PWMfreq, dutyCycle);
	/* fill in here */

	/* Turn off LED */
    writeGPIO(3,0,0);
	/* fill in here */

	/* Clear interrupt flag */
    clearFlagLPIT(0);
	/* fill in here */


}

void IsrB(void){

	/* Turn on LED */
  writeGPIO(3,0,1);

	/* Calculate and set PWM duty cycle */
  i = (i+1)%10;
  theta = sinf(2*pi*i/10);
  dutyCycle=(float)0.4*theta+0.5;
  setPWM(0,0, 60000, dutyCycle);

	/* Turn off LED */
  writeGPIO(3,0,0);

	/* Clear interrupt flag */
  clearFlagLPIT(0);
	/* fill in here */

}

void IsrC(void){

	/* Turn on LED */
  writeGPIO(3,0,1);
	/* fill in here */

	/* Calculate and set PWM duty cycle */
  i = (i+1)%10;
  dutyCycle=sineTable[i];
  setPWM(0,0, 60000, dutyCycle);
	/* fill in here */

	/* Turn off LED */
  writeGPIO(3,0,0);
	/* fill in here */

	/* Clear interrupt flag */
  clearFlagLPIT(0);
	/* fill in here */

}

int main(){

  initEECS461();
  enableLPIT();
  init_ADC0_single();
  int j= 0;

  /* Initialize PWMs  */
   initPWMPCRs();
   initPWM(MOTOR_SUBMODULE,MOTOR_CHANNEL,MOTOR_FREQUENCY,0.5);
   initPWM(FILTER_SUBMODULE,FILTER_CHANNEL,FILTER_FREQUENCY,0.5); // Filter
  /* fill in */

  /* Initialize GPIO  */
   initGPDO(3, 0);
   initGPDI(4, 1);
   initGPDI(4, 2);
  /*   fill in    */

  for(j=0;j<10;j++){

    sineTable[j]=0.4*sinf(2*pi*j/10)+0.5;
  }

  initLPIT(LPIT0_CHANNEL, 1000, &IsrB, 0xC);

  while(1){
    /*Loop forever */
  };
}

