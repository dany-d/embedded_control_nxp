/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: two_virtual_wheel_autocode.h
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

#ifndef RTW_HEADER_two_virtual_wheel_autocode_h_
#define RTW_HEADER_two_virtual_wheel_autocode_h_
#include <math.h>
#include <string.h>
#ifndef two_virtual_wheel_autocode_COMMON_INCLUDES_
# define two_virtual_wheel_autocode_COMMON_INCLUDES_
#include <string.h>
#include "rtwtypes.h"
#include "ftm_qd_driver.h"
#include "clock_manager.h"
#include "pcc_hw_access.h"
#include "pins_port_hw_access.h"
#include "ftm_pwm_driver.h"
#include "ftm_hw_access.h"
#include "ftm3_pwm_params.h"
#include "ftm0_pwm_params.h"
#include "pins_driver.h"
#endif                                 /* two_virtual_wheel_autocode_COMMON_INCLUDES_ */

#include "two_virtual_wheel_autocode_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
# define rtmStepTask(rtm, idx)         ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmTaskCounter
# define rtmTaskCounter(rtm, idx)      ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

/* Block signals (default storage) */
typedef struct {
  real32_T RateTransition2;            /* '<S1>/Rate Transition2' */
  real32_T RateTransition3;            /* '<S1>/Rate Transition3' */
  real32_T Saturation;                 /* '<S7>/Saturation' */
  int16_T Quadrature_Decoder;          /* '<S2>/Quadrature_Decoder' */
  boolean_T DataTypeConversion;        /* '<S6>/Data Type Conversion' */
  boolean_T DataTypeConversion1;       /* '<S6>/Data Type Conversion1' */
  boolean_T DataTypeConversion10;      /* '<S6>/Data Type Conversion10' */
  boolean_T DataTypeConversion11;      /* '<S6>/Data Type Conversion11' */
  boolean_T DataTypeConversion12;      /* '<S6>/Data Type Conversion12' */
  boolean_T DataTypeConversion13;      /* '<S6>/Data Type Conversion13' */
  boolean_T DataTypeConversion14;      /* '<S6>/Data Type Conversion14' */
  boolean_T DataTypeConversion15;      /* '<S6>/Data Type Conversion15' */
  boolean_T DataTypeConversion2;       /* '<S6>/Data Type Conversion2' */
  boolean_T DataTypeConversion3;       /* '<S6>/Data Type Conversion3' */
  boolean_T DataTypeConversion4;       /* '<S6>/Data Type Conversion4' */
  boolean_T DataTypeConversion5;       /* '<S6>/Data Type Conversion5' */
  boolean_T DataTypeConversion6;       /* '<S6>/Data Type Conversion6' */
  boolean_T DataTypeConversion7;       /* '<S6>/Data Type Conversion7' */
  boolean_T DataTypeConversion8;       /* '<S6>/Data Type Conversion8' */
  boolean_T DataTypeConversion9;       /* '<S6>/Data Type Conversion9' */
} B_two_virtual_wheel_autocode_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S3>/Discrete-Time Integrator1' */
  real32_T DiscreteTimeIntegrator_DSTATE;/* '<S3>/Discrete-Time Integrator' */
  real32_T UnitDelay1_DSTATE;          /* '<S4>/Unit Delay1' */
  real32_T DiscreteTimeIntegrator2_DSTATE;/* '<S2>/Discrete-Time Integrator2' */
  real32_T DiscreteTimeIntegrator3_DSTATE;/* '<S2>/Discrete-Time Integrator3' */
  real32_T RateTransition2_Buffer0;    /* '<S1>/Rate Transition2' */
  uint32_T TriggeredSubsystem1_PREV_T; /* '<S1>/Triggered Subsystem1' */
  uint32_T TriggeredSubsystem_PREV_T;  /* '<S1>/Triggered Subsystem' */
  uint16_T UnitDelay_DSTATE;           /* '<S4>/Unit Delay' */
} DW_two_virtual_wheel_autocode_T;

/* Real-time Model Data Structure */
struct tag_RTM_two_virtual_wheel_aut_T {
  const char_T *errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick1;
    uint32_T clockTick2;
    struct {
      uint8_T TID[3];
    } TaskCounters;

    struct {
      boolean_T TID1_2;
    } RateInteraction;
  } Timing;
};

/* Block signals (default storage) */
extern B_two_virtual_wheel_autocode_T two_virtual_wheel_autocode_B;

/* Block states (default storage) */
extern DW_two_virtual_wheel_autocode_T two_virtual_wheel_autocode_DW;

/* External function called from main */
extern void two_virtual_wheel_autocode_SetEventsForThisBaseStep(boolean_T
  *eventFlags);

/* Model entry point functions */
extern void two_virtual_wheel_autocode_SetEventsForThisBaseStep(boolean_T
  *eventFlags);
extern void two_virtual_wheel_autocode_initialize(void);
extern void two_virtual_wheel_autocode_step(int_T tid);
extern void two_virtual_wheel_autocode_terminate(void);

/* Real-time Model object */
extern RT_MODEL_two_virtual_wheel_au_T *const two_virtual_wheel_autocode_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S3>/To Workspace' : Unused code path elimination
 * Block '<S3>/To Workspace1' : Unused code path elimination
 * Block '<S3>/To Workspace2' : Unused code path elimination
 * Block '<S5>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<S6>/Data Type Conversion16' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'two_virtual_wheel_autocode'
 * '<S1>'   : 'two_virtual_wheel_autocode/Subsystem'
 * '<S2>'   : 'two_virtual_wheel_autocode/Subsystem/Triggered Subsystem'
 * '<S3>'   : 'two_virtual_wheel_autocode/Subsystem/Triggered Subsystem1'
 * '<S4>'   : 'two_virtual_wheel_autocode/Subsystem/Triggered Subsystem/Subsystem'
 * '<S5>'   : 'two_virtual_wheel_autocode/Subsystem/Triggered Subsystem/Subsystem1'
 * '<S6>'   : 'two_virtual_wheel_autocode/Subsystem/Triggered Subsystem/Write 16 Bits'
 * '<S7>'   : 'two_virtual_wheel_autocode/Subsystem/Triggered Subsystem/Subsystem1/Subsystem2'
 */
#endif                                 /* RTW_HEADER_two_virtual_wheel_autocode_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
