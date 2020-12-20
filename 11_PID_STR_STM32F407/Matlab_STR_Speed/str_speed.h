/*
 * File: str_speed.h
 *
 * Real-Time Workshop code generated for Simulink model str_speed.
 *
 * Model version                        : 1.62
 * Real-Time Workshop file version      : 7.4  (R2009b)  29-Jun-2009
 * Real-Time Workshop file generated on : Sat Dec 19 10:18:52 2020
 * TLC version                          : 7.4 (Jul 14 2009)
 * C/C++ source code generated on       : Sat Dec 19 10:18:53 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_str_speed_h_
#define RTW_HEADER_str_speed_h_
#ifndef str_speed_COMMON_INCLUDES_
# define str_speed_COMMON_INCLUDES_
#include <stddef.h>
#include <math.h>
#include <string.h>
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include "rt_SATURATE.h"
#include "rt_pow_snf.h"
#endif                                 /* str_speed_COMMON_INCLUDES_ */

#include "str_speed_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay3_DSTATE;            /* '<S2>/Unit Delay3' */
  real_T UnitDelay2_DSTATE;            /* '<S2>/Unit Delay2' */
  real_T UnitDelay6_DSTATE;            /* '<S2>/Unit Delay6' */
  real_T UnitDelay5_DSTATE;            /* '<S2>/Unit Delay5' */
  real_T UnitDelay1_DSTATE[16];        /* '<S2>/Unit Delay1' */
  real_T UnitDelay_DSTATE[4];          /* '<S2>/Unit Delay' */
  real_T UnitDelay6_DSTATE_o;          /* '<S3>/Unit Delay6' */
  real_T UnitDelay5_DSTATE_h;          /* '<S3>/Unit Delay5' */
  real_T UnitDelay2_DSTATE_a;          /* '<S3>/Unit Delay2' */
  real_T UnitDelay1_DSTATE_k;          /* '<S3>/Unit Delay1' */
} D_Work_str_speed;

/* Parameters (auto storage) */
struct Parameters_str_speed_ {
  real_T UnitDelay3_X0;                /* Expression: 0
                                        * Referenced by: '<S2>/Unit Delay3'
                                        */
  real_T UnitDelay2_X0;                /* Expression: 0
                                        * Referenced by: '<S2>/Unit Delay2'
                                        */
  real_T UnitDelay6_X0;                /* Expression: 0
                                        * Referenced by: '<S2>/Unit Delay6'
                                        */
  real_T UnitDelay5_X0;                /* Expression: 0
                                        * Referenced by: '<S2>/Unit Delay5'
                                        */
  real_T UnitDelay1_X0[16];            /* Expression: 1e5*eye(4)
                                        * Referenced by: '<S2>/Unit Delay1'
                                        */
  real_T UnitDelay_X0[4];              /* Expression: [-1; 0.1; 0.1; 1]
                                        * Referenced by: '<S2>/Unit Delay'
                                        */
  real_T UnitDelay6_X0_a;              /* Expression: 0
                                        * Referenced by: '<S3>/Unit Delay6'
                                        */
  real_T UnitDelay5_X0_d;              /* Expression: 0
                                        * Referenced by: '<S3>/Unit Delay5'
                                        */
  real_T UnitDelay2_X0_h;              /* Expression: 0
                                        * Referenced by: '<S3>/Unit Delay2'
                                        */
  real_T UnitDelay1_X0_c;              /* Expression: 0
                                        * Referenced by: '<S3>/Unit Delay1'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 10
                                        * Referenced by: '<S3>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -10
                                        * Referenced by: '<S3>/Saturation'
                                        */
};

/* Real-time Model Data Structure */
struct RT_MODEL_str_speed {
  const char_T * volatile errorStatus;
};

/* Block parameters (auto storage) */
extern Parameters_str_speed str_speed_P;

/* Block states (auto storage) */
extern D_Work_str_speed str_speed_DWork;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  RTW declares the memory for these signals
 * and exports their symbols.
 *
 */
extern real_T In2;                     /* '<Root>/Sensor' */
extern real_T In1;                     /* '<Root>/Set point' */
extern real_T Out1;                    /* '<S3>/Saturation' */

/* Model entry point functions */
extern void str_speed_initialize(void);
extern void str_speed_step(void);
extern void str_speed_terminate(void);

/* Real-time Model object */
extern RT_MODEL_str_speed *str_speed_M;

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
 * '<Root>' : str_speed
 * '<S1>'   : str_speed/DC Motor
 * '<S2>'   : str_speed/Identification
 * '<S3>'   : str_speed/Self-Tuning Regulator
 * '<S4>'   : str_speed/Identification/Embedded MATLAB Function
 * '<S5>'   : str_speed/Self-Tuning Regulator/Embedded MATLAB Function
 */
#endif                                 /* RTW_HEADER_str_speed_h_ */

/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
