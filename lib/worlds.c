
/*
  EECS461
  Lab 6
*/
#include "eecs461.h"
#include "pwm.h"
#include "worlds.h"
#include "gpio.h"

// ====================LAB 4================================
// **************************************************************************
// * Virtual Wall
// **************************************************************************
float virtualWall(float angle)
{
 uint16_t k_wall = 700;
 float torque = 0;
 if(angle < 0){
   return 0;
 }
 torque = -k_wall*angle;
 return torque;
}

// **************************************************************************
// * Virtual Spring
// **************************************************************************
float virtualSpring(float angle)
{
 float k_spring = 10;
 float torque = 0;
 torque = -k_spring*angle;
 return torque;
}

//
// **************************************************************************
// * Virtual Spring Damper
// **************************************************************************
float virtualSpringDamper(float angle,float velocity)
{
 float k_spring = 10;
 float b_spring = 0.6715;
 float torque = 0;
 torque = -k_spring*angle - b_spring*velocity;
 return torque;
}
//
// ///***************************************************************************
// * Virtual Wall Damper
// ***************************************************************************/
float virtualWallDamper(float angle, float velocity)
{
 float k_wall = 500.;
 float b_wall = 0.25;
 float torque = 0;
 if(angle < 0){
   return 0;
 }
 torque = -k_wall*angle - b_wall*velocity;
 return torque;

}
//

/***************************************************************************
* Virtual Spring Mass
***************************************************************************/
float virtualSpringMass(float angle)
{
  static float prevangle = 0;
  static float prevvel = 0;
  float x_1,x_2;

  x_1 = prevangle+(0.001*prevvel);

  x_2 = -(gk*0.001*prevangle)/gJ + prevvel + (gk*0.001)*angle/gJ;

  prevangle = x_1;
  prevvel= x_2;
 float torque = 0;
 torque = gk*(x_1- angle);
 return torque;
}


/***************************************************************************
* Virtual Spring Mass Damper
***************************************************************************/
float virtualSpringMassDamper(float angle,float velocity)
{
  static float prevangle = 0;
  static float prevvel = 0;
  float b = 0.01778;
  float x_1,x_2;

  x_1 = prevangle + 0.001*prevvel;
  x_2 = -(gk*0.001*prevangle)/gJ -(b*0.001*prevvel)/gJ + prevvel + (gk*0.001*angle)/gJ + (b*0.001*velocity)/gJ;

  prevangle = x_1;
  prevvel= x_2;

  float torque = 0;
  torque = gk*(x_1- angle) + b*(x_2 -velocity);
  return torque;
}



/***************************************************************************
* Virtual Knob
***************************************************************************/
float virtualKnob(float angle, float velocity)
{
 uint16_t k_spring = 500;
 uint16_t b_spring = 0.25;
 velocity = 0;
 float torque = 0;
 int deg=angle;
 deg=deg%40;
// deg=deg-20;

 return k_spring*(angle-deg)-b_spring*velocity;

// if(deg>20)
// {
//     return k_spring*(angle)-b_spring*velocity;
// }
// else if(deg>0 && deg<20)
// {
//     return -k_spring*(angle)-b_spring*velocity;
// }
// else if(deg<0 && deg>-20)
// {
//   return -k_spring*(angle)-b_spring*velocity;
// }
// else if(deg<-20)
// {
//   return k_spring*(angle)-b_spring*velocity;
// }
// return -b_spring*velocity;
}

