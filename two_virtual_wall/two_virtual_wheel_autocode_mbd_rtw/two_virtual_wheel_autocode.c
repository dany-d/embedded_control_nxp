/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: two_virtual_wheel_autocode.c
 *
 * Code generated for Simulink model 'two_virtual_wheel_autocode'.
 *
 * Model version                   : 1.77
 * Simulink Coder version          : 8.14 (R2018a) 06-Feb-2018
 * MBDT for S32K1xx Series Version : 2018.R1 (R2016b-R2018a) 23-Jul-2018
 * C/C++ source code generated on  : Fri Mar 29 12:54:46 2019
 *
 * Target selection: mbd_s32k14.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objective: Traceability
 * Validation result: Not run
 */

#include "two_virtual_wheel_autocode.h"
#include "two_virtual_wheel_autocode_private.h"

/* Block signals (default storage) */
B_two_virtual_wheel_autocode_T two_virtual_wheel_autocode_B;

/* Block states (default storage) */
DW_two_virtual_wheel_autocode_T two_virtual_wheel_autocode_DW;

/* Real-time model */
RT_MODEL_two_virtual_wheel_au_T two_virtual_wheel_autocode_M_;
RT_MODEL_two_virtual_wheel_au_T *const two_virtual_wheel_autocode_M =
  &two_virtual_wheel_autocode_M_;
static void rate_monotonic_scheduler(void);

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to "remember" which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void two_virtual_wheel_autocode_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[1] = ((boolean_T)rtmStepTask(two_virtual_wheel_autocode_M, 1));
  eventFlags[2] = ((boolean_T)rtmStepTask(two_virtual_wheel_autocode_M, 2));
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* To ensure a deterministic data transfer between two rates,
   * data is transferred at the priority of a fast task and the frequency
   * of the slow task.  The following flags indicate when the data transfer
   * happens.  That is, a rate interaction flag is set true when both rates
   * will run, and false otherwise.
   */

  /* tid 1 shares data with slower tid rate: 2 */
  if (two_virtual_wheel_autocode_M->Timing.TaskCounters.TID[1] == 0) {
    two_virtual_wheel_autocode_M->Timing.RateInteraction.TID1_2 =
      (two_virtual_wheel_autocode_M->Timing.TaskCounters.TID[2] == 0);
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (two_virtual_wheel_autocode_M->Timing.TaskCounters.TID[1])++;
  if ((two_virtual_wheel_autocode_M->Timing.TaskCounters.TID[1]) > 1) {/* Sample time: [0.002s, 0.0s] */
    two_virtual_wheel_autocode_M->Timing.TaskCounters.TID[1] = 0;
  }

  (two_virtual_wheel_autocode_M->Timing.TaskCounters.TID[2])++;
  if ((two_virtual_wheel_autocode_M->Timing.TaskCounters.TID[2]) > 19) {/* Sample time: [0.02s, 0.0s] */
    two_virtual_wheel_autocode_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/* Model step function for TID0 */
void two_virtual_wheel_autocode_step0(void) /* Sample time: [0.001s, 0.0s] */
{
  {                                    /* Sample time: [0.001s, 0.0s] */
    rate_monotonic_scheduler();
  }
}

/* Model step function for TID1 */
void two_virtual_wheel_autocode_step1(void) /* Sample time: [0.002s, 0.0s] */
{
  uint16_T rtb_DataTypeConversion;
  real32_T rtb_Sum3;
  int32_T Switch;
  uint32_T TriggeredSubsystem_ELAPS_T;
  uint32_T TriggeredSubsystem_ELAPS_T_tmp;
  real32_T DiscreteTimeIntegrator2_DSTATE_;

  /* S-Function (ftm_s32k14_pwm_config): '<Root>/FTM_PWM_Config1' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant2'
   */
  {
    uint16_t dutyA = FTM_MAX_DUTY_CYCLE * 0.5F;
    FTM_DRV_UpdatePwmChannel(FTM_PWM3, 0U, FTM_PWM_UPDATE_IN_DUTY_CYCLE, dutyA,
      0, true);
  }

  /* RateTransition: '<S1>/Rate Transition2' */
  if (two_virtual_wheel_autocode_M->Timing.RateInteraction.TID1_2) {
    two_virtual_wheel_autocode_B.RateTransition2 =
      two_virtual_wheel_autocode_DW.RateTransition2_Buffer0;
  }

  /* End of RateTransition: '<S1>/Rate Transition2' */

  /* S-Function (fcncallgen): '<S1>/Function-Call Generator' incorporates:
   *  SubSystem: '<S1>/Triggered Subsystem'
   */
  TriggeredSubsystem_ELAPS_T_tmp =
    two_virtual_wheel_autocode_M->Timing.clockTick1;
  TriggeredSubsystem_ELAPS_T = TriggeredSubsystem_ELAPS_T_tmp -
    two_virtual_wheel_autocode_DW.TriggeredSubsystem_PREV_T;
  two_virtual_wheel_autocode_DW.TriggeredSubsystem_PREV_T =
    TriggeredSubsystem_ELAPS_T_tmp;

  /* S-Function (ftm_s32k14_quadrature_decoder): '<S2>/Quadrature_Decoder' */

  /* FTM2: get counter value */
  two_virtual_wheel_autocode_B.Quadrature_Decoder = FTM_DRV_GetCounter (FTM2);

  /* DataTypeConversion: '<S4>/Data Type Conversion' */
  rtb_DataTypeConversion = (uint16_T)
    two_virtual_wheel_autocode_B.Quadrature_Decoder;

  /* Sum: '<S4>/Sum1' incorporates:
   *  DataTypeConversion: '<S4>/Data Type Conversion1'
   *  DataTypeConversion: '<S4>/Data Type Conversion2'
   *  Gain: '<S4>/Gain'
   *  Sum: '<S4>/Sum'
   *  UnitDelay: '<S4>/Unit Delay'
   *  UnitDelay: '<S4>/Unit Delay1'
   */
  two_virtual_wheel_autocode_DW.UnitDelay1_DSTATE += (real32_T)(int16_T)
    (rtb_DataTypeConversion - two_virtual_wheel_autocode_DW.UnitDelay_DSTATE) *
    0.09F;

  /* Switch: '<S2>/Switch' incorporates:
   *  Abs: '<S2>/Abs'
   *  Constant: '<S2>/Constant'
   *  Constant: '<S2>/Constant1'
   *  Constant: '<S2>/Constant2'
   *  RelationalOperator: '<S2>/Less Than'
   *  UnitDelay: '<S4>/Unit Delay1'
   */
  if ((real32_T)fabs(two_virtual_wheel_autocode_DW.UnitDelay1_DSTATE) < 45.0F) {
    Switch = 0;
  } else {
    Switch = 45;
  }

  /* End of Switch: '<S2>/Switch' */

  /* Sum: '<S2>/Sum3' incorporates:
   *  DiscreteIntegrator: '<S2>/Discrete-Time Integrator2'
   *  DiscreteIntegrator: '<S2>/Discrete-Time Integrator3'
   *  Gain: '<S2>/damping4'
   *  Gain: '<S2>/spring  constant2'
   *  Sum: '<S2>/Sum1'
   */
  rtb_Sum3 = ((real32_T)Switch -
              two_virtual_wheel_autocode_DW.DiscreteTimeIntegrator2_DSTATE) *
    7.5F - 0.015F * two_virtual_wheel_autocode_DW.DiscreteTimeIntegrator3_DSTATE;

  /* Sum: '<S7>/Sum' incorporates:
   *  Constant: '<S7>/Constant'
   *  Gain: '<S7>/Gain'
   *  Sum: '<S2>/Add'
   */
  two_virtual_wheel_autocode_B.Saturation = ((0.0F -
    two_virtual_wheel_autocode_B.RateTransition2) - rtb_Sum3) * 0.0003162F +
    0.5F;

  /* Saturate: '<S7>/Saturation' */
  if (two_virtual_wheel_autocode_B.Saturation > 0.76F) {
    /* Sum: '<S7>/Sum' */
    two_virtual_wheel_autocode_B.Saturation = 0.76F;
  } else {
    if (two_virtual_wheel_autocode_B.Saturation < 0.24F) {
      /* Sum: '<S7>/Sum' */
      two_virtual_wheel_autocode_B.Saturation = 0.24F;
    }
  }

  /* End of Saturate: '<S7>/Saturation' */

  /* S-Function (ftm_s32k14_pwm_config): '<S5>/FTM_PWM_Config' incorporates:
   *  Constant: '<S5>/Constant'
   */
  {
    uint16_t dutyA = FTM_MAX_DUTY_CYCLE *
      two_virtual_wheel_autocode_B.Saturation;
    FTM_DRV_UpdatePwmChannel(FTM_PWM0, 0U, FTM_PWM_UPDATE_IN_DUTY_CYCLE, dutyA,
      0, true);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion' incorporates:
   *  S-Function (sfix_bitop): '<S6>/Bitwise Operator'
   */
  two_virtual_wheel_autocode_B.DataTypeConversion =
    ((two_virtual_wheel_autocode_B.Quadrature_Decoder & 1U) != 0U);

  /* S-Function (gpio_s32k14_output): '<S6>/Digital_Output' */

  /* GPOPORTD0 Data Signal Update */
  if (two_virtual_wheel_autocode_B.DataTypeConversion) {
    PINS_DRV_SetPins(PTD, 1UL<<0);
  } else {
    PINS_DRV_ClearPins(PTD, 1UL<<0);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion1' incorporates:
   *  S-Function (sfix_bitop): '<S6>/Bitwise Operator1'
   */
  two_virtual_wheel_autocode_B.DataTypeConversion1 =
    ((two_virtual_wheel_autocode_B.Quadrature_Decoder & 2U) != 0U);

  /* S-Function (gpio_s32k14_output): '<S6>/Digital_Output1' */

  /* GPOPORTD1 Data Signal Update */
  if (two_virtual_wheel_autocode_B.DataTypeConversion1) {
    PINS_DRV_SetPins(PTD, 1UL<<1);
  } else {
    PINS_DRV_ClearPins(PTD, 1UL<<1);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion10' incorporates:
   *  S-Function (sfix_bitop): '<S6>/Bitwise Operator10'
   */
  two_virtual_wheel_autocode_B.DataTypeConversion10 =
    ((two_virtual_wheel_autocode_B.Quadrature_Decoder & 1024U) != 0U);

  /* S-Function (gpio_s32k14_output): '<S6>/Digital_Output10' */

  /* GPOPORTD10 Data Signal Update */
  if (two_virtual_wheel_autocode_B.DataTypeConversion10) {
    PINS_DRV_SetPins(PTD, 1UL<<10);
  } else {
    PINS_DRV_ClearPins(PTD, 1UL<<10);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion11' incorporates:
   *  S-Function (sfix_bitop): '<S6>/Bitwise Operator11'
   */
  two_virtual_wheel_autocode_B.DataTypeConversion11 =
    ((two_virtual_wheel_autocode_B.Quadrature_Decoder & 2048U) != 0U);

  /* S-Function (gpio_s32k14_output): '<S6>/Digital_Output11' */

  /* GPOPORTD11 Data Signal Update */
  if (two_virtual_wheel_autocode_B.DataTypeConversion11) {
    PINS_DRV_SetPins(PTD, 1UL<<11);
  } else {
    PINS_DRV_ClearPins(PTD, 1UL<<11);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion12' incorporates:
   *  S-Function (sfix_bitop): '<S6>/Bitwise Operator12'
   */
  two_virtual_wheel_autocode_B.DataTypeConversion12 =
    ((two_virtual_wheel_autocode_B.Quadrature_Decoder & 4096U) != 0U);

  /* S-Function (gpio_s32k14_output): '<S6>/Digital_Output12' */

  /* GPOPORTD12 Data Signal Update */
  if (two_virtual_wheel_autocode_B.DataTypeConversion12) {
    PINS_DRV_SetPins(PTD, 1UL<<12);
  } else {
    PINS_DRV_ClearPins(PTD, 1UL<<12);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion13' incorporates:
   *  S-Function (sfix_bitop): '<S6>/Bitwise Operator13'
   */
  two_virtual_wheel_autocode_B.DataTypeConversion13 =
    ((two_virtual_wheel_autocode_B.Quadrature_Decoder & 8192U) != 0U);

  /* S-Function (gpio_s32k14_output): '<S6>/Digital_Output13' */

  /* GPOPORTD13 Data Signal Update */
  if (two_virtual_wheel_autocode_B.DataTypeConversion13) {
    PINS_DRV_SetPins(PTD, 1UL<<13);
  } else {
    PINS_DRV_ClearPins(PTD, 1UL<<13);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion14' incorporates:
   *  S-Function (sfix_bitop): '<S6>/Bitwise Operator14'
   */
  two_virtual_wheel_autocode_B.DataTypeConversion14 =
    ((two_virtual_wheel_autocode_B.Quadrature_Decoder & 16384U) != 0U);

  /* S-Function (gpio_s32k14_output): '<S6>/Digital_Output14' */

  /* GPOPORTD14 Data Signal Update */
  if (two_virtual_wheel_autocode_B.DataTypeConversion14) {
    PINS_DRV_SetPins(PTD, 1UL<<14);
  } else {
    PINS_DRV_ClearPins(PTD, 1UL<<14);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion15' incorporates:
   *  S-Function (sfix_bitop): '<S6>/Bitwise Operator15'
   */
  two_virtual_wheel_autocode_B.DataTypeConversion15 = ((int16_T)
    (two_virtual_wheel_autocode_B.Quadrature_Decoder & MIN_int16_T) != 0);

  /* S-Function (gpio_s32k14_output): '<S6>/Digital_Output15' */

  /* GPOPORTD15 Data Signal Update */
  if (two_virtual_wheel_autocode_B.DataTypeConversion15) {
    PINS_DRV_SetPins(PTD, 1UL<<15);
  } else {
    PINS_DRV_ClearPins(PTD, 1UL<<15);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion2' incorporates:
   *  S-Function (sfix_bitop): '<S6>/Bitwise Operator2'
   */
  two_virtual_wheel_autocode_B.DataTypeConversion2 =
    ((two_virtual_wheel_autocode_B.Quadrature_Decoder & 4U) != 0U);

  /* S-Function (gpio_s32k14_output): '<S6>/Digital_Output2' */

  /* GPOPORTD2 Data Signal Update */
  if (two_virtual_wheel_autocode_B.DataTypeConversion2) {
    PINS_DRV_SetPins(PTD, 1UL<<2);
  } else {
    PINS_DRV_ClearPins(PTD, 1UL<<2);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion3' incorporates:
   *  S-Function (sfix_bitop): '<S6>/Bitwise Operator3'
   */
  two_virtual_wheel_autocode_B.DataTypeConversion3 =
    ((two_virtual_wheel_autocode_B.Quadrature_Decoder & 8U) != 0U);

  /* S-Function (gpio_s32k14_output): '<S6>/Digital_Output3' */

  /* GPOPORTD3 Data Signal Update */
  if (two_virtual_wheel_autocode_B.DataTypeConversion3) {
    PINS_DRV_SetPins(PTD, 1UL<<3);
  } else {
    PINS_DRV_ClearPins(PTD, 1UL<<3);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion4' incorporates:
   *  S-Function (sfix_bitop): '<S6>/Bitwise Operator4'
   */
  two_virtual_wheel_autocode_B.DataTypeConversion4 =
    ((two_virtual_wheel_autocode_B.Quadrature_Decoder & 16U) != 0U);

  /* S-Function (gpio_s32k14_output): '<S6>/Digital_Output4' */

  /* GPOPORTD4 Data Signal Update */
  if (two_virtual_wheel_autocode_B.DataTypeConversion4) {
    PINS_DRV_SetPins(PTD, 1UL<<4);
  } else {
    PINS_DRV_ClearPins(PTD, 1UL<<4);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion5' incorporates:
   *  S-Function (sfix_bitop): '<S6>/Bitwise Operator5'
   */
  two_virtual_wheel_autocode_B.DataTypeConversion5 =
    ((two_virtual_wheel_autocode_B.Quadrature_Decoder & 32U) != 0U);

  /* S-Function (gpio_s32k14_output): '<S6>/Digital_Output5' */

  /* GPOPORTD5 Data Signal Update */
  if (two_virtual_wheel_autocode_B.DataTypeConversion5) {
    PINS_DRV_SetPins(PTD, 1UL<<5);
  } else {
    PINS_DRV_ClearPins(PTD, 1UL<<5);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion6' incorporates:
   *  S-Function (sfix_bitop): '<S6>/Bitwise Operator6'
   */
  two_virtual_wheel_autocode_B.DataTypeConversion6 =
    ((two_virtual_wheel_autocode_B.Quadrature_Decoder & 64U) != 0U);

  /* S-Function (gpio_s32k14_output): '<S6>/Digital_Output6' */

  /* GPOPORTD6 Data Signal Update */
  if (two_virtual_wheel_autocode_B.DataTypeConversion6) {
    PINS_DRV_SetPins(PTD, 1UL<<6);
  } else {
    PINS_DRV_ClearPins(PTD, 1UL<<6);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion7' incorporates:
   *  S-Function (sfix_bitop): '<S6>/Bitwise Operator7'
   */
  two_virtual_wheel_autocode_B.DataTypeConversion7 =
    ((two_virtual_wheel_autocode_B.Quadrature_Decoder & 128U) != 0U);

  /* S-Function (gpio_s32k14_output): '<S6>/Digital_Output7' */

  /* GPOPORTD7 Data Signal Update */
  if (two_virtual_wheel_autocode_B.DataTypeConversion7) {
    PINS_DRV_SetPins(PTD, 1UL<<7);
  } else {
    PINS_DRV_ClearPins(PTD, 1UL<<7);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion8' incorporates:
   *  S-Function (sfix_bitop): '<S6>/Bitwise Operator8'
   */
  two_virtual_wheel_autocode_B.DataTypeConversion8 =
    ((two_virtual_wheel_autocode_B.Quadrature_Decoder & 256U) != 0U);

  /* S-Function (gpio_s32k14_output): '<S6>/Digital_Output8' */

  /* GPOPORTD8 Data Signal Update */
  if (two_virtual_wheel_autocode_B.DataTypeConversion8) {
    PINS_DRV_SetPins(PTD, 1UL<<8);
  } else {
    PINS_DRV_ClearPins(PTD, 1UL<<8);
  }

  /* DataTypeConversion: '<S6>/Data Type Conversion9' incorporates:
   *  S-Function (sfix_bitop): '<S6>/Bitwise Operator9'
   */
  two_virtual_wheel_autocode_B.DataTypeConversion9 =
    ((two_virtual_wheel_autocode_B.Quadrature_Decoder & 512U) != 0U);

  /* S-Function (gpio_s32k14_output): '<S6>/Digital_Output9' */

  /* GPOPORTD9 Data Signal Update */
  if (two_virtual_wheel_autocode_B.DataTypeConversion9) {
    PINS_DRV_SetPins(PTD, 1UL<<9);
  } else {
    PINS_DRV_ClearPins(PTD, 1UL<<9);
  }

  /* Update for UnitDelay: '<S4>/Unit Delay' */
  two_virtual_wheel_autocode_DW.UnitDelay_DSTATE = rtb_DataTypeConversion;

  /* Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator2' incorporates:
   *  DiscreteIntegrator: '<S2>/Discrete-Time Integrator3'
   *  DiscreteIntegrator: '<S2>/Discrete-Time Integrator3'
   */
  DiscreteTimeIntegrator2_DSTATE_ = 0.002F * (real32_T)
    TriggeredSubsystem_ELAPS_T;
  two_virtual_wheel_autocode_DW.DiscreteTimeIntegrator2_DSTATE +=
    DiscreteTimeIntegrator2_DSTATE_ *
    two_virtual_wheel_autocode_DW.DiscreteTimeIntegrator3_DSTATE;

  /* Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator3' incorporates:
   *  Gain: '<S2>/1//virtual inertia2'
   */
  two_virtual_wheel_autocode_DW.DiscreteTimeIntegrator3_DSTATE +=
    DiscreteTimeIntegrator2_DSTATE_ * (533.333313F * rtb_Sum3);

  /* End of Outputs for S-Function (fcncallgen): '<S1>/Function-Call Generator' */

  /* RateTransition: '<S1>/Rate Transition3' */
  if (two_virtual_wheel_autocode_M->Timing.RateInteraction.TID1_2) {
    two_virtual_wheel_autocode_B.RateTransition3 = (real32_T)Switch;
  }

  /* End of RateTransition: '<S1>/Rate Transition3' */

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.002, which is the step size
   * of the task. Size of "clockTick1" ensures timer will not overflow during the
   * application lifespan selected.
   */
  two_virtual_wheel_autocode_M->Timing.clockTick1++;
}

/* Model step function for TID2 */
void two_virtual_wheel_autocode_step2(void) /* Sample time: [0.02s, 0.0s] */
{
  real32_T Sum2;
  uint32_T TriggeredSubsystem1_ELAPS_T;
  uint32_T TriggeredSubsystem1_ELAPS_T_tmp;
  real32_T DiscreteTimeIntegrator1_DSTATE_;

  /* S-Function (fcncallgen): '<S1>/Function-Call Generator1' incorporates:
   *  SubSystem: '<S1>/Triggered Subsystem1'
   */
  TriggeredSubsystem1_ELAPS_T_tmp =
    two_virtual_wheel_autocode_M->Timing.clockTick2;
  TriggeredSubsystem1_ELAPS_T = TriggeredSubsystem1_ELAPS_T_tmp -
    two_virtual_wheel_autocode_DW.TriggeredSubsystem1_PREV_T;
  two_virtual_wheel_autocode_DW.TriggeredSubsystem1_PREV_T =
    TriggeredSubsystem1_ELAPS_T_tmp;

  /* Sum: '<S3>/Sum2' incorporates:
   *  DiscreteIntegrator: '<S3>/Discrete-Time Integrator'
   *  DiscreteIntegrator: '<S3>/Discrete-Time Integrator1'
   *  Gain: '<S3>/damping1'
   *  Gain: '<S3>/spring  constant1'
   *  Sum: '<S3>/Sum'
   */
  Sum2 = (two_virtual_wheel_autocode_B.RateTransition3 -
          two_virtual_wheel_autocode_DW.DiscreteTimeIntegrator1_DSTATE) * 7.5F -
    0.15F * two_virtual_wheel_autocode_DW.DiscreteTimeIntegrator_DSTATE;

  /* Update for DiscreteIntegrator: '<S3>/Discrete-Time Integrator1' incorporates:
   *  DiscreteIntegrator: '<S3>/Discrete-Time Integrator'
   *  DiscreteIntegrator: '<S3>/Discrete-Time Integrator'
   */
  DiscreteTimeIntegrator1_DSTATE_ = 0.02F * (real32_T)
    TriggeredSubsystem1_ELAPS_T;
  two_virtual_wheel_autocode_DW.DiscreteTimeIntegrator1_DSTATE +=
    DiscreteTimeIntegrator1_DSTATE_ *
    two_virtual_wheel_autocode_DW.DiscreteTimeIntegrator_DSTATE;

  /* Update for DiscreteIntegrator: '<S3>/Discrete-Time Integrator' incorporates:
   *  Gain: '<S3>/1//virtual inertia1'
   */
  two_virtual_wheel_autocode_DW.DiscreteTimeIntegrator_DSTATE +=
    DiscreteTimeIntegrator1_DSTATE_ * (5.33333349F * Sum2);

  /* End of Outputs for S-Function (fcncallgen): '<S1>/Function-Call Generator1' */

  /* Update for RateTransition: '<S1>/Rate Transition2' */
  two_virtual_wheel_autocode_DW.RateTransition2_Buffer0 = Sum2;

  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.02, which is the step size
   * of the task. Size of "clockTick2" ensures timer will not overflow during the
   * application lifespan selected.
   */
  two_virtual_wheel_autocode_M->Timing.clockTick2++;
}

/* Model step wrapper function for compatibility with a static main program */
void two_virtual_wheel_autocode_step(int_T tid)
{
  switch (tid) {
   case 0 :
    two_virtual_wheel_autocode_step0();
    break;

   case 1 :
    two_virtual_wheel_autocode_step1();
    break;

   case 2 :
    two_virtual_wheel_autocode_step2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void two_virtual_wheel_autocode_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)two_virtual_wheel_autocode_M, 0,
                sizeof(RT_MODEL_two_virtual_wheel_au_T));

  /* block I/O */
  (void) memset(((void *) &two_virtual_wheel_autocode_B), 0,
                sizeof(B_two_virtual_wheel_autocode_T));

  {
    two_virtual_wheel_autocode_B.RateTransition2 = 0.0F;
    two_virtual_wheel_autocode_B.RateTransition3 = 0.0F;
    two_virtual_wheel_autocode_B.Saturation = 0.0F;
  }

  /* states (dwork) */
  (void) memset((void *)&two_virtual_wheel_autocode_DW, 0,
                sizeof(DW_two_virtual_wheel_autocode_T));
  two_virtual_wheel_autocode_DW.DiscreteTimeIntegrator1_DSTATE = 0.0F;
  two_virtual_wheel_autocode_DW.DiscreteTimeIntegrator_DSTATE = 0.0F;
  two_virtual_wheel_autocode_DW.UnitDelay1_DSTATE = 0.0F;
  two_virtual_wheel_autocode_DW.DiscreteTimeIntegrator2_DSTATE = 0.0F;
  two_virtual_wheel_autocode_DW.DiscreteTimeIntegrator3_DSTATE = 0.0F;
  two_virtual_wheel_autocode_DW.RateTransition2_Buffer0 = 0.0F;

  /* Start for S-Function (ftm_s32k14_pwm_config): '<Root>/FTM_PWM_Config1' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant2'
   */

  /* Enable clock for PORTB */
  PCC_SetClockMode (PCC, PCC_PORTB_CLOCK, true);

  /* Pin is configured for FTM function */
  PINS_SetMuxModeSel(PORTB, 8, PORT_MUX_ALT2);

  /* Set FTM_3 clock source */
  PCC_SetPeripheralClockControl (PCC, PCC_FTM3_CLOCK, true, CLK_SRC_SPLL, 0, 0);

  /* Enable clock for FTM_3 */
  PCC_SetClockMode (PCC, PCC_FTM3_CLOCK, true);

  /* PWM3 initialization */
  FTM_DRV_Init (FTM_PWM3, &flexTimer_pwm3_InitConfig, &ftmStateStruct3);
  FTM_DRV_InitPwm (FTM_PWM3, &flexTimer_pwm3_PwmConfig);
  FTM_DRV_SetChnTriggerCmd(FTM3, 1, false);

  /* Start for S-Function (fcncallgen): '<S1>/Function-Call Generator' incorporates:
   *  SubSystem: '<S1>/Triggered Subsystem'
   */

  /* Start for S-Function (ftm_s32k14_quadrature_decoder): '<S2>/Quadrature_Decoder' */

  /* Enable clock for PORTA */
  PCC_SetClockMode (PCC, PCC_PORTA_CLOCK, true);

  /* Pin is configured for FTM function */
  PINS_SetMuxModeSel(PORTA, 13, PORT_MUX_ALT6);

  /* Enable clock for PORTA */
  PCC_SetClockMode (PCC, PCC_PORTA_CLOCK, true);

  /* Pin is configured for FTM function */
  PINS_SetMuxModeSel(PORTA, 12, PORT_MUX_ALT6);

  {
    ftm_quad_decode_config_t quadParams = {
      FTM_QUAD_PHASE_ENCODE,           /* Quadrature decoder mode */
      0U,                              /* Initial counter value */
      0xFFFF,                          /* Maximum counter value */

      {
        false,                         /* Filter state */
        0,                             /* Filter value */
        FTM_QUAD_PHASE_NORMAL          /* Phase polarity */
      },

      {
        false,                         /* Filter state */
        0,                             /* Filter value */
        FTM_QUAD_PHASE_NORMAL          /* Phase polarity */
      }
    };

    FTM_DRV_QuadDecodeStart(2, &quadParams);
  }

  /* Start for S-Function (ftm_s32k14_pwm_config): '<S5>/FTM_PWM_Config' incorporates:
   *  Constant: '<S5>/Constant'
   */

  /* Enable clock for PORTB */
  PCC_SetClockMode (PCC, PCC_PORTB_CLOCK, true);

  /* Pin is configured for FTM function */
  PINS_SetMuxModeSel(PORTB, 12, PORT_MUX_ALT2);

  /* Set FTM_0 clock source */
  PCC_SetPeripheralClockControl (PCC, PCC_FTM0_CLOCK, true, CLK_SRC_SPLL, 0, 0);

  /* Enable clock for FTM_0 */
  PCC_SetClockMode (PCC, PCC_FTM0_CLOCK, true);

  /* PWM0 initialization */
  FTM_DRV_Init (FTM_PWM0, &flexTimer_pwm0_InitConfig, &ftmStateStruct0);
  FTM_DRV_InitPwm (FTM_PWM0, &flexTimer_pwm0_PwmConfig);
  FTM_DRV_SetChnTriggerCmd(FTM0, 1, false);

  /* Start for S-Function (gpio_s32k14_output): '<S6>/Digital_Output' */
  {
    /* Enable clock for PORTD */
    PCC_SetClockMode(PCC, PCC_PORTD_CLOCK, true);

    /* Configure the output port init structure. */
    const pin_settings_config_t gpioPORTDPin0 = {
      .base = PORTD,
      .pinPortIdx = 0,
      .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
      .passiveFilter = false,
      .driveSelect = PORT_LOW_DRIVE_STRENGTH,
      .mux = PORT_MUX_AS_GPIO,
      .pinLock = false,
      .intConfig = PORT_DMA_INT_DISABLED,
      .clearIntFlag = true,
      .gpioBase = PTD,
      .direction = GPIO_OUTPUT_DIRECTION,
    };

    /* Initialize GPIPORTD0. */
    PINS_DRV_Init(1, &gpioPORTDPin0);
  }

  /* Start for S-Function (gpio_s32k14_output): '<S6>/Digital_Output1' */
  {
    /* Enable clock for PORTD */
    PCC_SetClockMode(PCC, PCC_PORTD_CLOCK, true);

    /* Configure the output port init structure. */
    const pin_settings_config_t gpioPORTDPin1 = {
      .base = PORTD,
      .pinPortIdx = 1,
      .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
      .passiveFilter = false,
      .driveSelect = PORT_LOW_DRIVE_STRENGTH,
      .mux = PORT_MUX_AS_GPIO,
      .pinLock = false,
      .intConfig = PORT_DMA_INT_DISABLED,
      .clearIntFlag = true,
      .gpioBase = PTD,
      .direction = GPIO_OUTPUT_DIRECTION,
    };

    /* Initialize GPIPORTD1. */
    PINS_DRV_Init(1, &gpioPORTDPin1);
  }

  /* Start for S-Function (gpio_s32k14_output): '<S6>/Digital_Output10' */
  {
    /* Enable clock for PORTD */
    PCC_SetClockMode(PCC, PCC_PORTD_CLOCK, true);

    /* Configure the output port init structure. */
    const pin_settings_config_t gpioPORTDPin10 = {
      .base = PORTD,
      .pinPortIdx = 10,
      .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
      .passiveFilter = false,
      .driveSelect = PORT_LOW_DRIVE_STRENGTH,
      .mux = PORT_MUX_AS_GPIO,
      .pinLock = false,
      .intConfig = PORT_DMA_INT_DISABLED,
      .clearIntFlag = true,
      .gpioBase = PTD,
      .direction = GPIO_OUTPUT_DIRECTION,
    };

    /* Initialize GPIPORTD10. */
    PINS_DRV_Init(1, &gpioPORTDPin10);
  }

  /* Start for S-Function (gpio_s32k14_output): '<S6>/Digital_Output11' */
  {
    /* Enable clock for PORTD */
    PCC_SetClockMode(PCC, PCC_PORTD_CLOCK, true);

    /* Configure the output port init structure. */
    const pin_settings_config_t gpioPORTDPin11 = {
      .base = PORTD,
      .pinPortIdx = 11,
      .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
      .passiveFilter = false,
      .driveSelect = PORT_LOW_DRIVE_STRENGTH,
      .mux = PORT_MUX_AS_GPIO,
      .pinLock = false,
      .intConfig = PORT_DMA_INT_DISABLED,
      .clearIntFlag = true,
      .gpioBase = PTD,
      .direction = GPIO_OUTPUT_DIRECTION,
    };

    /* Initialize GPIPORTD11. */
    PINS_DRV_Init(1, &gpioPORTDPin11);
  }

  /* Start for S-Function (gpio_s32k14_output): '<S6>/Digital_Output12' */
  {
    /* Enable clock for PORTD */
    PCC_SetClockMode(PCC, PCC_PORTD_CLOCK, true);

    /* Configure the output port init structure. */
    const pin_settings_config_t gpioPORTDPin12 = {
      .base = PORTD,
      .pinPortIdx = 12,
      .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
      .passiveFilter = false,
      .driveSelect = PORT_LOW_DRIVE_STRENGTH,
      .mux = PORT_MUX_AS_GPIO,
      .pinLock = false,
      .intConfig = PORT_DMA_INT_DISABLED,
      .clearIntFlag = true,
      .gpioBase = PTD,
      .direction = GPIO_OUTPUT_DIRECTION,
    };

    /* Initialize GPIPORTD12. */
    PINS_DRV_Init(1, &gpioPORTDPin12);
  }

  /* Start for S-Function (gpio_s32k14_output): '<S6>/Digital_Output13' */
  {
    /* Enable clock for PORTD */
    PCC_SetClockMode(PCC, PCC_PORTD_CLOCK, true);

    /* Configure the output port init structure. */
    const pin_settings_config_t gpioPORTDPin13 = {
      .base = PORTD,
      .pinPortIdx = 13,
      .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
      .passiveFilter = false,
      .driveSelect = PORT_LOW_DRIVE_STRENGTH,
      .mux = PORT_MUX_AS_GPIO,
      .pinLock = false,
      .intConfig = PORT_DMA_INT_DISABLED,
      .clearIntFlag = true,
      .gpioBase = PTD,
      .direction = GPIO_OUTPUT_DIRECTION,
    };

    /* Initialize GPIPORTD13. */
    PINS_DRV_Init(1, &gpioPORTDPin13);
  }

  /* Start for S-Function (gpio_s32k14_output): '<S6>/Digital_Output14' */
  {
    /* Enable clock for PORTD */
    PCC_SetClockMode(PCC, PCC_PORTD_CLOCK, true);

    /* Configure the output port init structure. */
    const pin_settings_config_t gpioPORTDPin14 = {
      .base = PORTD,
      .pinPortIdx = 14,
      .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
      .passiveFilter = false,
      .driveSelect = PORT_LOW_DRIVE_STRENGTH,
      .mux = PORT_MUX_AS_GPIO,
      .pinLock = false,
      .intConfig = PORT_DMA_INT_DISABLED,
      .clearIntFlag = true,
      .gpioBase = PTD,
      .direction = GPIO_OUTPUT_DIRECTION,
    };

    /* Initialize GPIPORTD14. */
    PINS_DRV_Init(1, &gpioPORTDPin14);
  }

  /* Start for S-Function (gpio_s32k14_output): '<S6>/Digital_Output15' */
  {
    /* Enable clock for PORTD */
    PCC_SetClockMode(PCC, PCC_PORTD_CLOCK, true);

    /* Configure the output port init structure. */
    const pin_settings_config_t gpioPORTDPin15 = {
      .base = PORTD,
      .pinPortIdx = 15,
      .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
      .passiveFilter = false,
      .driveSelect = PORT_LOW_DRIVE_STRENGTH,
      .mux = PORT_MUX_AS_GPIO,
      .pinLock = false,
      .intConfig = PORT_DMA_INT_DISABLED,
      .clearIntFlag = true,
      .gpioBase = PTD,
      .direction = GPIO_OUTPUT_DIRECTION,
    };

    /* Initialize GPIPORTD15. */
    PINS_DRV_Init(1, &gpioPORTDPin15);
  }

  /* Start for S-Function (gpio_s32k14_output): '<S6>/Digital_Output2' */
  {
    /* Enable clock for PORTD */
    PCC_SetClockMode(PCC, PCC_PORTD_CLOCK, true);

    /* Configure the output port init structure. */
    const pin_settings_config_t gpioPORTDPin2 = {
      .base = PORTD,
      .pinPortIdx = 2,
      .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
      .passiveFilter = false,
      .driveSelect = PORT_LOW_DRIVE_STRENGTH,
      .mux = PORT_MUX_AS_GPIO,
      .pinLock = false,
      .intConfig = PORT_DMA_INT_DISABLED,
      .clearIntFlag = true,
      .gpioBase = PTD,
      .direction = GPIO_OUTPUT_DIRECTION,
    };

    /* Initialize GPIPORTD2. */
    PINS_DRV_Init(1, &gpioPORTDPin2);
  }

  /* Start for S-Function (gpio_s32k14_output): '<S6>/Digital_Output3' */
  {
    /* Enable clock for PORTD */
    PCC_SetClockMode(PCC, PCC_PORTD_CLOCK, true);

    /* Configure the output port init structure. */
    const pin_settings_config_t gpioPORTDPin3 = {
      .base = PORTD,
      .pinPortIdx = 3,
      .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
      .passiveFilter = false,
      .driveSelect = PORT_LOW_DRIVE_STRENGTH,
      .mux = PORT_MUX_AS_GPIO,
      .pinLock = false,
      .intConfig = PORT_DMA_INT_DISABLED,
      .clearIntFlag = true,
      .gpioBase = PTD,
      .direction = GPIO_OUTPUT_DIRECTION,
    };

    /* Initialize GPIPORTD3. */
    PINS_DRV_Init(1, &gpioPORTDPin3);
  }

  /* Start for S-Function (gpio_s32k14_output): '<S6>/Digital_Output4' */
  {
    /* Enable clock for PORTD */
    PCC_SetClockMode(PCC, PCC_PORTD_CLOCK, true);

    /* Configure the output port init structure. */
    const pin_settings_config_t gpioPORTDPin4 = {
      .base = PORTD,
      .pinPortIdx = 4,
      .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
      .passiveFilter = false,
      .driveSelect = PORT_LOW_DRIVE_STRENGTH,
      .mux = PORT_MUX_AS_GPIO,
      .pinLock = false,
      .intConfig = PORT_DMA_INT_DISABLED,
      .clearIntFlag = true,
      .gpioBase = PTD,
      .direction = GPIO_OUTPUT_DIRECTION,
    };

    /* Initialize GPIPORTD4. */
    PINS_DRV_Init(1, &gpioPORTDPin4);
  }

  /* Start for S-Function (gpio_s32k14_output): '<S6>/Digital_Output5' */
  {
    /* Enable clock for PORTD */
    PCC_SetClockMode(PCC, PCC_PORTD_CLOCK, true);

    /* Configure the output port init structure. */
    const pin_settings_config_t gpioPORTDPin5 = {
      .base = PORTD,
      .pinPortIdx = 5,
      .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
      .passiveFilter = false,
      .driveSelect = PORT_LOW_DRIVE_STRENGTH,
      .mux = PORT_MUX_AS_GPIO,
      .pinLock = false,
      .intConfig = PORT_DMA_INT_DISABLED,
      .clearIntFlag = true,
      .gpioBase = PTD,
      .direction = GPIO_OUTPUT_DIRECTION,
    };

    /* Initialize GPIPORTD5. */
    PINS_DRV_Init(1, &gpioPORTDPin5);
  }

  /* Start for S-Function (gpio_s32k14_output): '<S6>/Digital_Output6' */
  {
    /* Enable clock for PORTD */
    PCC_SetClockMode(PCC, PCC_PORTD_CLOCK, true);

    /* Configure the output port init structure. */
    const pin_settings_config_t gpioPORTDPin6 = {
      .base = PORTD,
      .pinPortIdx = 6,
      .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
      .passiveFilter = false,
      .driveSelect = PORT_LOW_DRIVE_STRENGTH,
      .mux = PORT_MUX_AS_GPIO,
      .pinLock = false,
      .intConfig = PORT_DMA_INT_DISABLED,
      .clearIntFlag = true,
      .gpioBase = PTD,
      .direction = GPIO_OUTPUT_DIRECTION,
    };

    /* Initialize GPIPORTD6. */
    PINS_DRV_Init(1, &gpioPORTDPin6);
  }

  /* Start for S-Function (gpio_s32k14_output): '<S6>/Digital_Output7' */
  {
    /* Enable clock for PORTD */
    PCC_SetClockMode(PCC, PCC_PORTD_CLOCK, true);

    /* Configure the output port init structure. */
    const pin_settings_config_t gpioPORTDPin7 = {
      .base = PORTD,
      .pinPortIdx = 7,
      .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
      .passiveFilter = false,
      .driveSelect = PORT_LOW_DRIVE_STRENGTH,
      .mux = PORT_MUX_AS_GPIO,
      .pinLock = false,
      .intConfig = PORT_DMA_INT_DISABLED,
      .clearIntFlag = true,
      .gpioBase = PTD,
      .direction = GPIO_OUTPUT_DIRECTION,
    };

    /* Initialize GPIPORTD7. */
    PINS_DRV_Init(1, &gpioPORTDPin7);
  }

  /* Start for S-Function (gpio_s32k14_output): '<S6>/Digital_Output8' */
  {
    /* Enable clock for PORTD */
    PCC_SetClockMode(PCC, PCC_PORTD_CLOCK, true);

    /* Configure the output port init structure. */
    const pin_settings_config_t gpioPORTDPin8 = {
      .base = PORTD,
      .pinPortIdx = 8,
      .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
      .passiveFilter = false,
      .driveSelect = PORT_LOW_DRIVE_STRENGTH,
      .mux = PORT_MUX_AS_GPIO,
      .pinLock = false,
      .intConfig = PORT_DMA_INT_DISABLED,
      .clearIntFlag = true,
      .gpioBase = PTD,
      .direction = GPIO_OUTPUT_DIRECTION,
    };

    /* Initialize GPIPORTD8. */
    PINS_DRV_Init(1, &gpioPORTDPin8);
  }

  /* Start for S-Function (gpio_s32k14_output): '<S6>/Digital_Output9' */
  {
    /* Enable clock for PORTD */
    PCC_SetClockMode(PCC, PCC_PORTD_CLOCK, true);

    /* Configure the output port init structure. */
    const pin_settings_config_t gpioPORTDPin9 = {
      .base = PORTD,
      .pinPortIdx = 9,
      .pullConfig = PORT_INTERNAL_PULL_NOT_ENABLED,
      .passiveFilter = false,
      .driveSelect = PORT_LOW_DRIVE_STRENGTH,
      .mux = PORT_MUX_AS_GPIO,
      .pinLock = false,
      .intConfig = PORT_DMA_INT_DISABLED,
      .clearIntFlag = true,
      .gpioBase = PTD,
      .direction = GPIO_OUTPUT_DIRECTION,
    };

    /* Initialize GPIPORTD9. */
    PINS_DRV_Init(1, &gpioPORTDPin9);
  }

  /* End of Start for S-Function (fcncallgen): '<S1>/Function-Call Generator' */

  /* SystemInitialize for S-Function (fcncallgen): '<S1>/Function-Call Generator' incorporates:
   *  SubSystem: '<S1>/Triggered Subsystem'
   */
  two_virtual_wheel_autocode_DW.TriggeredSubsystem_PREV_T =
    two_virtual_wheel_autocode_M->Timing.clockTick1;

  /* End of SystemInitialize for S-Function (fcncallgen): '<S1>/Function-Call Generator' */

  /* SystemInitialize for S-Function (fcncallgen): '<S1>/Function-Call Generator1' incorporates:
   *  SubSystem: '<S1>/Triggered Subsystem1'
   */
  two_virtual_wheel_autocode_DW.TriggeredSubsystem1_PREV_T =
    two_virtual_wheel_autocode_M->Timing.clockTick2;

  /* End of SystemInitialize for S-Function (fcncallgen): '<S1>/Function-Call Generator1' */
}

/* Model terminate function */
void two_virtual_wheel_autocode_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
