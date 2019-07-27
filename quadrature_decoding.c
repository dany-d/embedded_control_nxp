 #include "eecs461.h"
 #include "S32K144.h"
 #include "gpio.h"
 #include "qd.h"


#define base_portD 0x4004C000u
#define base_portE 0x4004D000u
#define base_GPIO 0x400FF000
#define GPIOD_offset 0xC0u
#define GPIOE_offset 0x100u

typedef struct {
 volatile uint32_t PDOR;
 volatile uint32_t PSOR;
 volatile uint32_t PCOR;
 volatile uint32_t PTOR;
 const volatile uint32_t PDIR;
 volatile uint32_t PDDR;
 volatile uint32_t PIDR;
} GPIO_addr;

 int main(void){
   int32_t counter = 0, pos_count;
   int index;
   float angle;
   int16_t angleInt;
   volatile uint32_t * const portD_PCR = (uint32_t *)(base_portD);
   GPIO_addr * const gpioD = (GPIO_addr *)(base_GPIO + GPIOD_offset);
   int section = 2; //Set to case you are testing

   /* Initialize EECS461, QD, GPDO */
   initEECS461();
   initQD();

   while(1){
     switch(section){
     case 1://Read the counter
       counter = FTM2->CNT & FTM_CNT_COUNT_MASK;

       /* fill in */
       break;

     case 2://Overflow and Underflow

       counter = FTM2->CNT & FTM_CNT_COUNT_MASK;

       for(index = 0; index <16; index++)
       {
        portD_PCR[index] = 0b001 << 8; /* Configure pin mux to gpio */
        gpioD->PDDR |= 0b1 << index; /* Set the direction to output */
       }
        gpioD->PDOR = counter;

       /* fill in */

       break;

     case 3: //updateCounter and Faulty Casting
        pos_count  =  (updateCounter() >> 8);

        for(index = 0; index <16; index++)
        {
         portD_PCR[index] = 0b001 << 8; /* Configure pin mux to gpio */
         gpioD->PDDR |= 0b1 << index; /* Set the direction to output */
        }

          gpioD->PDOR = pos_count;


       /* fill in */
       break;

     case 4: //Angle Calculation
       /* fill in */
       angle = updateAngle();
       for(index = 0; index <16; index++)
       {
        portD_PCR[index] = 0b001 << 8; /* Configure pin mux to gpio */
        gpioD->PDDR |= 0b1 << index; /* Set the direction to output */
       }

        gpioD->PDOR = angle;


       break;
     }
   }
 }
