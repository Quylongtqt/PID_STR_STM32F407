/*
 * File: lqr.c
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

/* Exported block signals */
real_T In2;                            /* '<Root>/Sensor' */
real_T In1;                            /* '<Root>/Setpoint' */
real_T Out1;                           /* '<S3>/Saturation' */

/* Block states (auto storage) */
D_Work_lqr lqr_DWork;

/* Real-time model */
RT_MODEL_lqr lqr_M_;
RT_MODEL_lqr *lqr_M = &lqr_M_;

/* Forward declaration for local functions */
static void lqr_refp1_mpower(real_T eml_a[4]);

/* Function for Embedded MATLAB: '<S3>/Embedded MATLAB Function' */
static void lqr_refp1_mpower(real_T eml_a[4])
{
  real_T eml_x;
  real_T eml_d;
  eml_x = eml_a[0];
  eml_d = eml_x * eml_a[3] - eml_a[1] * eml_a[2];
  eml_a[0] = eml_a[3] / eml_d;
  eml_a[3] = eml_x / eml_d;
  eml_a[1] = (-eml_a[1]) / eml_d;
  eml_a[2] = (-eml_a[2]) / eml_d;
}

/* Model step function */
void lqr_step(void)
{
  real_T eml_e;
  real_T eml_B;
  real_T eml_y;
  real_T eml_a[4];
  real_T eml_Ad[4];
  real_T eml_P[4];
  real_T eml_E[4];
  real_T eml_hoistedExpr[4];
  real_T rtb_uk1;
  real_T rtb_yk1;
  real_T rtb_P[16];
  int32_T i;
  real_T eml_PHI[4];
  real_T tmp[16];
  real_T eml_Ad_0[4];
  real_T rtb_TmpSignalConversionAtSFun_0;
  real_T eml_PHI_idx;
  real_T eml_PHI_idx_0;
  real_T rtb_Theta_idx;
  real_T rtb_Theta_idx_0;
  real_T rtb_Theta_idx_1;
  real_T rtb_Theta_idx_2;
  real_T eml_x_idx;
  real_T eml_P_ins_idx;
  real_T unnamed_idx;
  static int8_T tmp_0[4] = { 1, 0, 0, 1 };

  /* UnitDelay: '<S2>/u(k+1)' */
  rtb_uk1 = lqr_DWork.uk1_DSTATE;

  /* UnitDelay: '<S2>/y(k+1)' */
  rtb_yk1 = lqr_DWork.yk1_DSTATE;

  /* Embedded MATLAB: '<S2>/Embedded MATLAB Function' incorporates:
   *  Inport: '<Root>/Sensor'
   *  SignalConversion: '<S4>/TmpSignal ConversionAt SFunction Inport1'
   *  SignalConversion: '<S4>/TmpSignal ConversionAt SFunction Inport2'
   *  UnitDelay: '<S2>/Unit Delay'
   *  UnitDelay: '<S2>/Unit Delay1'
   *  UnitDelay: '<S2>/u(k)'
   *  UnitDelay: '<S2>/y(k)'
   */
  /* Embedded MATLAB Function 'Identification/Embedded MATLAB Function': '<S4>:1' */
  /* '<S4>:1:3' */
  /* '<S4>:1:4' */
  eml_PHI_idx = -lqr_DWork.yk1_DSTATE;
  eml_PHI_idx_0 = -lqr_DWork.yk_DSTATE;

  /* '<S4>:1:5' */
  eml_a[0] = eml_PHI_idx;
  eml_a[1] = eml_PHI_idx_0;
  eml_a[2] = lqr_DWork.uk1_DSTATE;
  eml_a[3] = lqr_DWork.uk_DSTATE;
  eml_e = In2 - (((eml_a[0] * lqr_DWork.UnitDelay_DSTATE[0] + eml_a[1] *
                   lqr_DWork.UnitDelay_DSTATE[1]) + eml_a[2] *
                  lqr_DWork.UnitDelay_DSTATE[2]) + eml_a[3] *
                 lqr_DWork.UnitDelay_DSTATE[3]);

  /* '<S4>:1:6' */
  for (i = 0; i < 4; i++) {
    rtb_TmpSignalConversionAtSFun_0 = lqr_DWork.UnitDelay1_DSTATE[(i << 2) + 3] *
      lqr_DWork.uk_DSTATE + (lqr_DWork.UnitDelay1_DSTATE[(i << 2) + 2] *
      lqr_DWork.uk1_DSTATE + (lqr_DWork.UnitDelay1_DSTATE[(i << 2) + 1] *
      eml_PHI_idx_0 + lqr_DWork.UnitDelay1_DSTATE[(i << 2)] * eml_PHI_idx));
    eml_a[i] = rtb_TmpSignalConversionAtSFun_0;
  }

  eml_B = (((eml_a[0] * eml_PHI_idx + eml_a[1] * eml_PHI_idx_0) + eml_a[2] *
            lqr_DWork.uk1_DSTATE) + eml_a[3] * lqr_DWork.uk_DSTATE) + 0.95;

  /* '<S4>:1:7' */
  for (i = 0; i < 4; i++) {
    rtb_TmpSignalConversionAtSFun_0 = lqr_DWork.UnitDelay1_DSTATE[(i << 2) + 3] *
      lqr_DWork.uk_DSTATE + (lqr_DWork.UnitDelay1_DSTATE[(i << 2) + 2] *
      lqr_DWork.uk1_DSTATE + (lqr_DWork.UnitDelay1_DSTATE[(i << 2) + 1] *
      eml_PHI_idx_0 + lqr_DWork.UnitDelay1_DSTATE[(i << 2)] * eml_PHI_idx));
    unnamed_idx = lqr_DWork.UnitDelay1_DSTATE[i + 12] * lqr_DWork.uk_DSTATE +
      (lqr_DWork.UnitDelay1_DSTATE[i + 8] * lqr_DWork.uk1_DSTATE +
       (lqr_DWork.UnitDelay1_DSTATE[i + 4] * eml_PHI_idx_0 +
        lqr_DWork.UnitDelay1_DSTATE[i] * eml_PHI_idx));
    eml_P_ins_idx = lqr_DWork.UnitDelay1_DSTATE[(i << 2) + 3] *
      lqr_DWork.uk_DSTATE + (lqr_DWork.UnitDelay1_DSTATE[(i << 2) + 2] *
      lqr_DWork.uk1_DSTATE + (lqr_DWork.UnitDelay1_DSTATE[(i << 2) + 1] *
      eml_PHI_idx_0 + lqr_DWork.UnitDelay1_DSTATE[(i << 2)] * eml_PHI_idx));
    eml_PHI[i] = eml_P_ins_idx;
    eml_Ad_0[i] = unnamed_idx;
    eml_a[i] = rtb_TmpSignalConversionAtSFun_0;
  }

  eml_y = (((eml_a[0] * eml_PHI_idx + eml_a[1] * eml_PHI_idx_0) + eml_a[2] *
            lqr_DWork.uk1_DSTATE) + eml_a[3] * lqr_DWork.uk_DSTATE) + 0.95;
  for (i = 0; i < 4; i++) {
    tmp[i] = lqr_DWork.UnitDelay1_DSTATE[i] - eml_Ad_0[i] * eml_PHI[0] / eml_y;
    tmp[i + 4] = lqr_DWork.UnitDelay1_DSTATE[i + 4] - eml_Ad_0[i] * eml_PHI[1] /
      eml_y;
    tmp[i + 8] = lqr_DWork.UnitDelay1_DSTATE[i + 8] - eml_Ad_0[i] * eml_PHI[2] /
      eml_y;
    tmp[i + 12] = lqr_DWork.UnitDelay1_DSTATE[i + 12] - eml_Ad_0[i] * eml_PHI[3]
      / eml_y;
  }

  for (i = 0; i < 4; i++) {
    rtb_P[i << 2] = tmp[i << 2] * 1.0526315789473684E+000;
    rtb_P[1 + (i << 2)] = tmp[(i << 2) + 1] * 1.0526315789473684E+000;
    rtb_P[2 + (i << 2)] = tmp[(i << 2) + 2] * 1.0526315789473684E+000;
    rtb_P[3 + (i << 2)] = tmp[(i << 2) + 3] * 1.0526315789473684E+000;
  }

  /* '<S4>:1:8' */
  for (i = 0; i < 4; i++) {
    eml_a[i] = (((lqr_DWork.UnitDelay1_DSTATE[i + 4] * eml_PHI_idx_0 +
                  lqr_DWork.UnitDelay1_DSTATE[i] * eml_PHI_idx) +
                 lqr_DWork.UnitDelay1_DSTATE[i + 8] * lqr_DWork.uk1_DSTATE) +
                lqr_DWork.UnitDelay1_DSTATE[i + 12] * lqr_DWork.uk_DSTATE) /
      eml_B;
  }

  rtb_Theta_idx_0 = eml_a[0] * eml_e + lqr_DWork.UnitDelay_DSTATE[0];
  rtb_Theta_idx = eml_a[1] * eml_e + lqr_DWork.UnitDelay_DSTATE[1];
  rtb_Theta_idx_1 = eml_a[2] * eml_e + lqr_DWork.UnitDelay_DSTATE[2];
  rtb_Theta_idx_2 = eml_a[3] * eml_e + lqr_DWork.UnitDelay_DSTATE[3];

  /* UnitDelay: '<S3>/y(k+1)' */
  eml_y = lqr_DWork.yk1_DSTATE_o;

  /* Embedded MATLAB: '<S3>/Embedded MATLAB Function' incorporates:
   *  Inport: '<Root>/Setpoint'
   *  SignalConversion: '<S5>/TmpSignal ConversionAt SFunction Inport3'
   *  UnitDelay: '<S3>/y(k)'
   */
  /* Embedded MATLAB Function 'Self-Tuning Regulator/Embedded MATLAB Function': '<S5>:1' */
  /*  Gan lai cho de su dung */
  /* '<S5>:1:3' */
  /* '<S5>:1:4' */
  /* '<S5>:1:5' */
  /* '<S5>:1:6' */
  /*  PT sai phan: */
  /*      a0.z^2+a1.y.z+a2.y = b1.u.z + b2.u */
  /*  <=> y(k+2) + a1.y(k+1) + a2.y(k) = b1.u(k+1) + b2.u(k) */
  /*  PT Trang thai mo ta he thong tinh tu PT sai phan */
  /*  x(k+1) = Ad.x(k) + Bd.u(k) */
  /*  y(k) = Cd.x(k) */
  /*  Refer to Chuong 7 CSTD */
  /* '<S5>:1:15' */
  /* '<S5>:1:16' */
  eml_Ad[0] = 0.0;
  eml_Ad[2] = 1.0;
  eml_Ad[1] = -rtb_Theta_idx;
  eml_Ad[3] = -rtb_Theta_idx_0;

  /* '<S5>:1:17' */
  rtb_TmpSignalConversionAtSFun_0 = rtb_Theta_idx_2 - rtb_Theta_idx_0 *
    rtb_Theta_idx_1;

  /* '<S5>:1:19' */
  eml_e = lqr_DWork.yk_DSTATE_n;
  eml_x_idx = lqr_DWork.yk1_DSTATE_o - rtb_Theta_idx_1 * In1;

  /*  LQR: */
  /* '<S5>:1:21' */
  /* '<S5>:1:23' */
  /* '<S5>:1:24' */
  eml_P[0] = 0.0;
  eml_P[1] = 0.0;
  eml_P[2] = 0.0;
  eml_P[3] = 0.0;
  eml_P[0] = 1.0;
  eml_P[3] = 1.0;

  /* '<S5>:1:25' */
  eml_E[0] = 0.0;
  eml_E[0] = rtb_Theta_idx_1 * rtb_Theta_idx_1;
  eml_E[2] = 0.0;
  eml_E[2] = rtb_Theta_idx_1 * rtb_TmpSignalConversionAtSFun_0;
  eml_E[1] = 0.0;
  eml_E[1] = rtb_TmpSignalConversionAtSFun_0 * rtb_Theta_idx_1;
  eml_E[3] = 0.0;
  eml_E[3] = rtb_TmpSignalConversionAtSFun_0 * rtb_TmpSignalConversionAtSFun_0;
  do {
    /* '<S5>:1:27' */
    eml_P_ins_idx = eml_P[0];
    eml_B = eml_P[1];
    eml_PHI_idx = eml_P[2];
    eml_PHI_idx_0 = eml_P[3];

    /* '<S5>:1:28' */
    for (i = 0; i < 2; i++) {
      eml_hoistedExpr[i] = (eml_E[i + 2] * eml_P[1] + eml_E[i] * eml_P[0]) +
        (real_T)tmp_0[i];
      eml_hoistedExpr[i + 2] = (eml_E[i + 2] * eml_P[3] + eml_E[i] * eml_P[2]) +
        (real_T)tmp_0[i + 2];
    }

    lqr_refp1_mpower(eml_hoistedExpr);
    for (i = 0; i < 2; i++) {
      eml_a[i] = 0.0;
      eml_a[i] += eml_Ad[i << 1] * eml_P[0];
      eml_a[i] += eml_Ad[(i << 1) + 1] * eml_P[1];
      eml_a[i + 2] = 0.0;
      eml_a[i + 2] += eml_Ad[i << 1] * eml_P[2];
      eml_a[i + 2] += eml_Ad[(i << 1) + 1] * eml_P[3];
    }

    for (i = 0; i < 2; i++) {
      eml_Ad_0[i] = 0.0;
      eml_Ad_0[i] += eml_a[i] * eml_hoistedExpr[0];
      eml_Ad_0[i] += eml_a[i + 2] * eml_hoistedExpr[1];
      eml_Ad_0[i + 2] = 0.0;
      eml_Ad_0[i + 2] += eml_a[i] * eml_hoistedExpr[2];
      eml_Ad_0[i + 2] += eml_a[i + 2] * eml_hoistedExpr[3];
    }

    for (i = 0; i < 2; i++) {
      eml_P[i] = (eml_Ad_0[i + 2] * eml_Ad[1] + eml_Ad_0[i] * 0.0) + (real_T)
        tmp_0[i];
      eml_P[i + 2] = (eml_Ad_0[i + 2] * eml_Ad[3] + eml_Ad_0[i]) + (real_T)
        tmp_0[i + 2];
    }

    /* '<S5>:1:29' */
    eml_P_ins_idx = eml_P[0] - eml_P_ins_idx;
    eml_B = eml_P[1] - eml_B;
    eml_PHI_idx = eml_P[2] - eml_PHI_idx;
  } while (!((fabs(eml_P_ins_idx) < 0.0001) && (fabs(eml_B) < 0.0001) && (fabs
             (eml_PHI_idx) < 0.0001) && (fabs(eml_P[3] - eml_PHI_idx_0) < 0.0001)));

  /* '<S5>:1:30' */
  /* '<S5>:1:34' */
  /*  Luat dieu khien */
  /* '<S5>:1:36' */
  lqr_refp1_mpower(eml_Ad);
  unnamed_idx = rtb_Theta_idx_1 * eml_Ad[0] + rtb_TmpSignalConversionAtSFun_0 *
    eml_Ad[2];
  rtb_TmpSignalConversionAtSFun_0 = rtb_Theta_idx_1 * eml_Ad[1] +
    rtb_TmpSignalConversionAtSFun_0 * eml_Ad[3];
  eml_e = (-((eml_P[0] - 1.0) * unnamed_idx + rtb_TmpSignalConversionAtSFun_0 *
             eml_P[1])) * eml_e + (-((eml_P[3] - 1.0) *
    rtb_TmpSignalConversionAtSFun_0 + unnamed_idx * eml_P[2])) * eml_x_idx;

  /* Saturate: '<S3>/Saturation' */
  Out1 = rt_SATURATE(eml_e, lqr_P.Saturation_LowerSat, lqr_P.Saturation_UpperSat);

  /* Update for UnitDelay: '<S2>/u(k+1)' */
  lqr_DWork.uk1_DSTATE = Out1;

  /* Update for UnitDelay: '<S2>/u(k)' */
  lqr_DWork.uk_DSTATE = rtb_uk1;

  /* Update for UnitDelay: '<S2>/y(k+1)' incorporates:
   *  Update for Inport: '<Root>/Sensor'
   */
  lqr_DWork.yk1_DSTATE = In2;

  /* Update for UnitDelay: '<S2>/y(k)' */
  lqr_DWork.yk_DSTATE = rtb_yk1;

  /* Update for UnitDelay: '<S2>/Unit Delay1' */
  memcpy((void *)(&lqr_DWork.UnitDelay1_DSTATE[0]), (void *)&rtb_P[0], sizeof
         (real_T) << 4U);

  /* Update for UnitDelay: '<S2>/Unit Delay' */
  lqr_DWork.UnitDelay_DSTATE[0] = rtb_Theta_idx_0;
  lqr_DWork.UnitDelay_DSTATE[1] = rtb_Theta_idx;
  lqr_DWork.UnitDelay_DSTATE[2] = rtb_Theta_idx_1;
  lqr_DWork.UnitDelay_DSTATE[3] = rtb_Theta_idx_2;

  /* Update for UnitDelay: '<S3>/y(k+1)' incorporates:
   *  Update for Inport: '<Root>/Sensor'
   */
  lqr_DWork.yk1_DSTATE_o = In2;

  /* Update for UnitDelay: '<S3>/y(k)' */
  lqr_DWork.yk_DSTATE_n = eml_y;
}

/* Model initialize function */
void lqr_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(lqr_M, (NULL));

  /* block I/O */

  /* exported global signals */
  Out1 = 0.0;

  /* states (dwork) */
  (void) memset((void *)&lqr_DWork, 0,
                sizeof(D_Work_lqr));

  /* external inputs */
  In2 = 0.0;
  In1 = 0.0;

  /* InitializeConditions for UnitDelay: '<S2>/u(k+1)' */
  lqr_DWork.uk1_DSTATE = lqr_P.uk1_X0;

  /* InitializeConditions for UnitDelay: '<S2>/u(k)' */
  lqr_DWork.uk_DSTATE = lqr_P.uk_X0;

  /* InitializeConditions for UnitDelay: '<S2>/y(k+1)' */
  lqr_DWork.yk1_DSTATE = lqr_P.yk1_X0;

  /* InitializeConditions for UnitDelay: '<S2>/y(k)' */
  lqr_DWork.yk_DSTATE = lqr_P.yk_X0;

  /* InitializeConditions for UnitDelay: '<S2>/Unit Delay1' */
  memcpy((void *)(&lqr_DWork.UnitDelay1_DSTATE[0]), (void *)
         (&lqr_P.UnitDelay1_X0[0]), sizeof(real_T) << 4U);

  /* InitializeConditions for UnitDelay: '<S2>/Unit Delay' */
  lqr_DWork.UnitDelay_DSTATE[0] = lqr_P.UnitDelay_X0[0];
  lqr_DWork.UnitDelay_DSTATE[1] = lqr_P.UnitDelay_X0[1];
  lqr_DWork.UnitDelay_DSTATE[2] = lqr_P.UnitDelay_X0[2];
  lqr_DWork.UnitDelay_DSTATE[3] = lqr_P.UnitDelay_X0[3];

  /* InitializeConditions for UnitDelay: '<S3>/y(k+1)' */
  lqr_DWork.yk1_DSTATE_o = lqr_P.yk1_X0_m;

  /* InitializeConditions for UnitDelay: '<S3>/y(k)' */
  lqr_DWork.yk_DSTATE_n = lqr_P.yk_X0_f;
}

/* Model terminate function */
void lqr_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
