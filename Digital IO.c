

#include "eecs461.h"
#include <stdint.h>

/* Change section number to match the section (1-3) being tested */
#define SECTION 3

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

#if SECTION == 1

/******************************************************************************
 * Function:    section1
 * Description: read and write to the GPIO registers using your header file
 ******************************************************************************/
void section1(){

  /* code for section 1 */

  uint16_t sum, value1, value2;
  uint32_t regReadVal;
  int index;

  volatile uint32_t * const portD_PCR = (uint32_t *)(base_portD);
  volatile uint32_t * const portE_PCR = (uint32_t *)(base_portE);
  GPIO_addr * const gpioD = (GPIO_addr *)(base_GPIO + GPIOD_offset);
  GPIO_addr * const gpioE = (GPIO_addr *)(base_GPIO + GPIOE_offset);


  initEECS461();

  /* For DIP pins */
  for(index = 6; index < 14; index++)
  {
   portE_PCR[index] = 0b001 << 8; /* Configure pin mux to gpio */
   gpioE->PDDR &= ~(1 << index); /* Set the direction to input */
  }

  /* For LED pins */
  for(index = 0; index <5; index++)
  {
   portD_PCR[index] = 0b001 << 8; /* Configure pin mux to gpio */
   gpioD->PDDR |= 0b1 << index; /* Set the direction to output */
  }

  while(1)
  {
      value1 = 0;
      value2 = 0;
      sum = 0;

      value1=gpioE->PDIR;
      value1=value1>>6;
      value2=((0b11110000)&value1)>>4;
      value1= (0b1111)&value1;
      sum = (value1 + value2);

      gpioD->PDOR=sum;

  }

}


#elif SECTION == 2
#include "S32K144.h"
#include "gpio.h"
/******************************************************************************
 * Function:    section2
 * Description: Use the provided S32K144.h header file
 ******************************************************************************/
void section2(){
  /* code for section 2 */
  int index;
  int pin;
  uint16_t value1, value2;
  uint16_t sum;
  initEECS461();

  /* For defining input pins */
    for(index = 6; index < 14; index++)
  {
    initGPDI(4, index);
  }


 /* For defining output pins*/

    initGPDO(3, 0);
    initGPDO(3, 1);
    initGPDO(3, 2);
    initGPDO(3, 3);
    initGPDO(3, 4);

 /* For defining input pins*/


  while(1){
    sum=0;
    value1=0;
    value2=0;

    for(index = 6; index < 10; index++)
    {
      value1+=(readGPIO(4, index)<<index-6);
      value2+= (readGPIO(4, index+4)<<index-6);

    }
    sum = value1 + value2;
    for(index=0; index<6; index++)
    {
      writeGPIO(3,index,((sum >> index) & 0b1));
    }
  }
}


#elif SECTION == 3
#include "LPUART.h"
#include "gpio.h"
/******************************************************************************
 * Function:    section3
 * Description: Communicate with the computer using the keyboard interface
 ******************************************************************************/
void section3(){
  /* code for section 3 */
  char byte_in;
  char old_byte_in=0;
  uint16_t value1;
  uint16_t sum=0;
  int index;
  int i, bin[10];
  volatile uint32_t * const portD_PCR = (uint32_t *)(base_portD);
  volatile uint32_t * const portE_PCR = (uint32_t *)(base_portE);
  GPIO_addr * const gpioD = (GPIO_addr *)(base_GPIO + GPIOD_offset);
  GPIO_addr * const gpioE = (GPIO_addr *)(base_GPIO + GPIOE_offset);
  initEECS461();

  /* For defining input pins */

  for(index = 6; index < 14; index++)
  {
    initGPDI(4, index);
  }


 /* For defining output pins*/

    initGPDO(3, 0);
    initGPDO(3, 1);
    initGPDO(3, 2);
    initGPDO(3, 3);
    initGPDO(3, 4);

  /* LPUART functions for sending and receiving serial data */
  LPUART1_init();
  LPUART1_transmit_string("\n\rSerial Output Enable...........");

  while(1)
  {
    sum=0;
    byte_in = LPUART1_receive_char(); // returns ASCII representation

    if(byte_in<='9' && byte_in>='0')
    {
      value1 = byte_in - 48;
    }

    sum=value1+old_byte_in;

    /* Convert to Binary
    for(i=0;sum>0;i++)
    {
      bin[i]=sum%2;
      sum=sum/2;

      for(index=0; index<6; index++)
    {
     writeGPIO(3,index,((sum >> index) & 0b1));
    }
    }
    */

    gpioD->PDOR=sum;

    old_byte_in = value1;



  }
}
#endif

int main(){
  /* Always call initEECS461() before doing anything else */

  #if(SECTION == 1)
  section1();
  #elif(SECTION == 2)
  section2();
  #elif(SECTION == 3)
  section3();
  #endif

  /* Should never reach this point */
  return 0;
}
