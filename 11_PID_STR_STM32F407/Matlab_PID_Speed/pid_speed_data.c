/*
 * File: pid_speed_data.c
 *
 * Real-Time Workshop code generated for Simulink model pid_speed.
 *
 * Model version                        : 1.38
 * Real-Time Workshop file version      : 7.4  (R2009b)  29-Jun-2009
 * Real-Time Workshop file generated on : Wed Dec 16 23:45:46 2020
 * TLC version                          : 7.4 (Jul 14 2009)
 * C/C++ source code generated on       : Wed Dec 16 23:45:47 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Generic->32-bit Embedded Processor
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "pid_speed.h"
#include "pid_speed_private.h"

/* Block parameters (auto storage) */
Parameters_pid_speed pid_speed_P = {
  0.015,                                 /* Expression: P
                                        * Referenced by: '<S1>/Proportional Gain'
                                        */
  0.005,                               /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S1>/Integrator'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S1>/Integrator'
                                        */
  0.0,                                 /* Expression: D
                                        * Referenced by: '<S1>/Derivative Gain'
                                        */
  0.005,                               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S1>/Filter'
                                        */
  0.0,                                 /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S1>/Filter'
                                        */
  100.0,                               /* Expression: N
                                        * Referenced by: '<S1>/Filter Coefficient'
                                        */
  10.0,                                /* Expression: 10
                                        * Referenced by: '<Root>/Saturation'
                                        */
  -10.0,                               /* Expression: -10
                                        * Referenced by: '<Root>/Saturation'
                                        */
  0.000006                               /* Expression: I
                                        * Referenced by: '<S1>/Integral Gain'
                                        */
};

/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
