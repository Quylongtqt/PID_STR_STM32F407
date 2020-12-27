/*
 * File: lqr.h
 *
 * Real-Time Workshop code generated for Simulink model lqr.
 *
 * Model version                        : 1.94
 * Real-Time Workshop file version      : 7.4  (R2009b)  29-Jun-2009
 * Real-Time Workshop file generated on : Thu Dec 24 00:12:56 2020
 * TLC version                          : 7.4 (Jul 14 2009)
 * C/C++ source code generated on       : Thu Dec 24 00:12:57 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_lqr_h_
#define RTW_HEADER_lqr_h_
#ifndef lqr_COMMON_INCLUDES_
# define lqr_COMMON_INCLUDES_
#include <stddef.h>
#include <math.h>
#include <string.h>
#include "rtwtypes.h"
#include "rt_SATURATE.h"
#endif                                 /* lqr_COMMON_INCLUDES_ */

#include "lqr_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T uk1_DSTATE;                   /* '<S2>/u(k+1)' */
  real_T uk_DSTATE;                    /* '<S2>/u(k)' */
  real_T yk1_DSTATE;                   /* '<S2>/y(k+1)' */
  real_T yk_DSTATE;                    /* '<S2>/y(k)' */
  real_T UnitDelay1_DSTATE[16];        /* '<S2>/Unit Delay1' */
  real_T UnitDelay_DSTATE[4];          /* '<S2>/Unit Delay' */
  real_T yk1_DSTATE_o;                 /* '<S3>/y(k+1)' */
  real_T yk_DSTATE_n;                  /* '<S3>/y(k)' */
} D_Work_lqr;

/* Parameters (auto storage) */
struct Parameters_lqr_ {
  real_T uk1_X0;                       /* Expression: 0
                                        * Referenced by: '<S2>/u(k+1)'
                                        */
  real_T uk_X0;                        /* Expression: 0
                                        * Referenced by: '<S2>/u(k)'
                                        */
  real_T yk1_X0;                       /* Expression: 0
                                        * Referenced by: '<S2>/y(k+1)'
                                        */
  real_T yk_X0;                        /* Expression: 0
                                        * Referenced by: '<S2>/y(k)'
                                        */
  real_T UnitDelay1_X0[16];            /* Expression: 1e5*eye(4)
                                        * Referenced by: '<S2>/Unit Delay1'
                                        */
  real_T UnitDelay_X0[4];              /* Expression: [-1; 0.1; 0.1; 1]
                                        * Referenced by: '<S2>/Unit Delay'
                                        */
  real_T yk1_X0_m;                     /* Expression: 0
                                        * Referenced by: '<S3>/y(k+1)'
                                        */
  real_T yk_X0_f;                      /* Expression: 0
                                        * Referenced by: '<S3>/y(k)'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 12
                                        * Referenced by: '<S3>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -12
                                        * Referenced by: '<S3>/Saturation'
                                        */
};

/* Real-time Model Data Structure */
struct RT_MODEL_lqr {
  const char_T * volatile errorStatus;
};

/* Block parameters (auto storage) */
extern Parameters_lqr lqr_P;

/* Block states (auto storage) */
extern D_Work_lqr lqr_DWork;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  RTW declares the memory for these signals
 * and exports their symbols.
 *
 */
extern real_T In2;                     /* '<Root>/Sensor' */
extern real_T In1;                     /* '<Root>/Setpoint' */
extern real_T Out1;                    /* '<S3>/Saturation' */

/* Model entry point functions */
extern void lqr_initialize(void);
extern void lqr_step(void);
extern void lqr_terminate(void);

/* Real-time Model object */
extern RT_MODEL_lqr *lqr_M;

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
 * '<Root>' : lqr
 * '<S1>'   : lqr/DC Motor
 * '<S2>'   : lqr/Identification
 * '<S3>'   : lqr/Self-Tuning Regulator
 * '<S4>'   : lqr/Identification/Embedded MATLAB Function
 * '<S5>'   : lqr/Self-Tuning Regulator/Embedded MATLAB Function
 */
#endif                                 /* RTW_HEADER_lqr_h_ */

/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
