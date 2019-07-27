 #include "eecs461.h"
 #include "S32K144.h"
 #include "gpio.h"
 #include "qd.h"
 #include "adc.h"
 #include <stdint.h>


int main(void){
initEECS461();

init_ADC0_single();
uint32_t iAnalog;

initGPDO(3, 0);
while(1){


//       writeGPIO(3,0,1);
//       iAnalog = read_ADC0_single(0);
//       writeGPIO(3,0,0);

       if(read_ADC0_single(0)>2500){
         writeGPIO(3,0,1);}
       else{
         writeGPIO(3,0,0);}
}
}



