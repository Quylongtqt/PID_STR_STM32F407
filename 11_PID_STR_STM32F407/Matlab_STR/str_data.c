/*
 * File: str_data.c
 *
 * Real-Time Workshop code generated for Simulink model str.
 *
 * Model version                        : 1.60
 * Real-Time Workshop file version      : 7.4  (R2009b)  29-Jun-2009
 * Real-Time Workshop file generated on : Thu Dec 17 22:35:47 2020
 * TLC version                          : 7.4 (Jul 14 2009)
 * C/C++ source code generated on       : Thu Dec 17 22:35:47 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "str.h"
#include "str_private.h"

/* Block parameters (auto storage) */
Parameters_str str_P = {
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Unit Delay3'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Unit Delay2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Unit Delay6'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Unit Delay5'
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
                                        * Referenced by: '<S3>/Unit Delay6'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Unit Delay5'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Unit Delay2'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/Unit Delay1'
                                        */
  10.0,                                /* Expression: 12
                                        * Referenced by: '<S3>/Saturation'
                                        */
  -10.0                                /* Expression: -12
                                        * Referenced by: '<S3>/Saturation'
                                        */
};

/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
