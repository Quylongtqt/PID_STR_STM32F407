/*
 * File: pid.c
 *
 * Real-Time Workshop code generated for Simulink model pid.
 *
 * Model version                        : 1.31
 * Real-Time Workshop file version      : 7.4  (R2009b)  29-Jun-2009
 * Real-Time Workshop file generated on : Sun Nov 29 16:33:36 2020
 * TLC version                          : 7.4 (Jul 14 2009)
 * C/C++ source code generated on       : Sun Nov 29 16:33:37 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Generic->32-bit Embedded Processor
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "pid.h"
#include "pid_private.h"

///* Exported block signals */
//real_T In2;                            /* '<Root>/In2' */
//real_T Out2;                           /* '<Root>/Setpoint (Deg)' */
//real_T Out1;                           /* '<Root>/Saturation' */

/* Block states (auto storage) */
D_Work_pid pid_DWork;

/* Real-time model */
RT_MODEL_pid pid_M_;
RT_MODEL_pid *pid_M = &pid_M_;

/* Model step function */
void pid_step(void)
{
  real_T rtb_Add;
  real_T rtb_Sum;
  real_T rtb_FilterCoefficient;

  /* Constant: '<Root>/Setpoint (Deg)' */
  Out2 = pid_P.SetpointDeg_Value;

  /* Sum: '<Root>/Add' incorporates:
   *  Inport: '<Root>/In2'
   */
  rtb_Add = Out2 - In2;

  /* Gain: '<S1>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S1>/Filter'
   *  Gain: '<S1>/Derivative Gain'
   *  Sum: '<S1>/SumD'
   */
  rtb_FilterCoefficient = (pid_P.DerivativeGain_Gain * rtb_Add -
    pid_DWork.Filter_DSTATE) * pid_P.FilterCoefficient_Gain;

  /* Sum: '<S1>/Sum' incorporates:
   *  DiscreteIntegrator: '<S1>/Integrator'
   *  Gain: '<S1>/Proportional Gain'
   */
  rtb_Sum = (pid_P.ProportionalGain_Gain * rtb_Add + pid_DWork.Integrator_DSTATE)
    + rtb_FilterCoefficient;

  /* Saturate: '<Root>/Saturation' */
  Out1 = rt_SATURATE(rtb_Sum, pid_P.Saturation_LowerSat,
                     pid_P.Saturation_UpperSat);

  /* Update for DiscreteIntegrator: '<S1>/Integrator' incorporates:
   *  Gain: '<S1>/Integral Gain'
   */
  pid_DWork.Integrator_DSTATE = pid_P.IntegralGain_Gain * rtb_Add *
    pid_P.Integrator_gainval + pid_DWork.Integrator_DSTATE;

  /* Update for DiscreteIntegrator: '<S1>/Filter' */
  pid_DWork.Filter_DSTATE = pid_P.Filter_gainval * rtb_FilterCoefficient +
    pid_DWork.Filter_DSTATE;
}

/* Model initialize function */
void pid_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(pid_M, (NULL));

  /* block I/O */

  /* exported global signals */
  Out2 = 0.0;
  Out1 = 0.0;

  /* states (dwork) */
  (void) memset((void *)&pid_DWork, 0,
                sizeof(D_Work_pid));

  /* external inputs */
  In2 = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Integrator' */
  pid_DWork.Integrator_DSTATE = pid_P.Integrator_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Filter' */
  pid_DWork.Filter_DSTATE = pid_P.Filter_IC;
}

/* Model terminate function */
void pid_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
