/*
 * File: lqr_data.c
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

#include "lqr.h"
#include "lqr_private.h"

/* Block parameters (auto storage) */
Parameters_lqr lqr_P = {
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/u(k+1)'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/u(k)'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/y(k+1)'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/y(k)'
                                        */

  /*  Expression: 1e5*eye(4)
   * Referenced by: '<S2>/Unit Delay1'
   */
  { 1.0E+005, 0.0, 0.0, 0.0, 0.0, 1.0E+005, 0.0, 0.0, 0.0, 0.0, 1.0E+005, 0.0,
    0.0, 0.0, 0.0, 1.0E+005 },

  /*  Expression: [-1; 0.1; 0.1; 1]
   * Referenced by: '<S2>/Unit Delay'
   */
  { -1.0, 0.1, 0.1, 1.0 },
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/y(k+1)'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/y(k)'
                                        */
  12.0,                                /* Expression: 12
                                        * Referenced by: '<S3>/Saturation'
                                        */
  -12.0                                /* Expression: -12
                                        * Referenced by: '<S3>/Saturation'
                                        */
};

/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
