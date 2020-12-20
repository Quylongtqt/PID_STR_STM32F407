/*
 * File: pid_speed.c
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

///* Exported block signals */
//real_T In2;                            /* '<Root>/In2' */
//real_T In1;                            /* '<Root>/In1' */
//real_T Out1;                           /* '<Root>/Saturation' */

/* Block states (auto storage) */
D_Work_pid_speed pid_speed_DWork;

/* Real-time model */
RT_MODEL_pid_speed pid_speed_M_;
RT_MODEL_pid_speed *pid_speed_M = &pid_speed_M_;

/* Model step function */
void pid_speed_step(void)
{
  real_T rtb_Add;
  real_T rtb_Sum;
  real_T rtb_FilterCoefficient;

  /* Sum: '<Root>/Add' incorporates:
   *  Inport: '<Root>/In1'
   *  Inport: '<Root>/In2'
   */
  rtb_Add = In1 - In2;

  /* Gain: '<S1>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S1>/Filter'
   *  Gain: '<S1>/Derivative Gain'
   *  Sum: '<S1>/SumD'
   */
  rtb_FilterCoefficient = (pid_speed_P.DerivativeGain_Gain * rtb_Add -
    pid_speed_DWork.Filter_DSTATE) * pid_speed_P.FilterCoefficient_Gain;

  /* Sum: '<S1>/Sum' incorporates:
   *  DiscreteIntegrator: '<S1>/Integrator'
   *  Gain: '<S1>/Proportional Gain'
   */
  rtb_Sum = (pid_speed_P.ProportionalGain_Gain * rtb_Add +
             pid_speed_DWork.Integrator_DSTATE) + rtb_FilterCoefficient;

  /* Saturate: '<Root>/Saturation' */
  Out1 = rt_SATURATE(rtb_Sum, pid_speed_P.Saturation_LowerSat,
                     pid_speed_P.Saturation_UpperSat);

  /* Update for DiscreteIntegrator: '<S1>/Integrator' incorporates:
   *  Gain: '<S1>/Integral Gain'
   */
  pid_speed_DWork.Integrator_DSTATE = pid_speed_P.IntegralGain_Gain * rtb_Add *
    pid_speed_P.Integrator_gainval + pid_speed_DWork.Integrator_DSTATE;

  /* Update for DiscreteIntegrator: '<S1>/Filter' */
  pid_speed_DWork.Filter_DSTATE = pid_speed_P.Filter_gainval *
    rtb_FilterCoefficient + pid_speed_DWork.Filter_DSTATE;
}

/* Model initialize function */
void pid_speed_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(pid_speed_M, (NULL));

  /* block I/O */

  /* exported global signals */
  Out1 = 0.0;

  /* states (dwork) */
  (void) memset((void *)&pid_speed_DWork, 0,
                sizeof(D_Work_pid_speed));

  /* external inputs */
  In2 = 0.0;
  In1 = 0.0;

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Integrator' */
  pid_speed_DWork.Integrator_DSTATE = pid_speed_P.Integrator_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Filter' */
  pid_speed_DWork.Filter_DSTATE = pid_speed_P.Filter_IC;
}

/* Model terminate function */
void pid_speed_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
