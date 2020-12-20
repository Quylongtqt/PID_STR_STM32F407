/*
 * File: str_speed.c
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

#include "str_speed.h"
#include "str_speed_private.h"

///* Exported block signals */
//real_T In2;                            /* '<Root>/Sensor' */
//real_T In1;                            /* '<Root>/Set point' */
//real_T Out1;                           /* '<S3>/Saturation' */

/* Block states (auto storage) */
D_Work_str_speed str_speed_DWork;

/* Real-time model */
RT_MODEL_str_speed str_speed_M_;
RT_MODEL_str_speed *str_speed_M = &str_speed_M_;

/* Model step function */
void str_speed_step(void)
{
  real_T eml_e;
  real_T eml_B;
  real_T eml_y;
  real_T eml_a[4];
  real_T eml_a_0;
  real_T eml_r;
  real_T eml_r_0;
  real_T eml_r_1;
  real_T eml_r_2;
  real_T eml_r_3;
  real_T rtb_UnitDelay3;
  real_T rtb_UnitDelay6;
  real_T rtb_UnitDelay6_l;
  real_T rtb_UnitDelay2_m;
  real_T rtb_Theta[4];
  int32_T tmp;
  real_T tmp_0[4];
  real_T eml_PHI[4];
  real_T tmp_1[16];
  real_T eml_PHI_idx;
  real_T eml_PHI_idx_0;

  /* UnitDelay: '<S2>/Unit Delay3' */
  rtb_UnitDelay3 = str_speed_DWork.UnitDelay3_DSTATE;

  /* UnitDelay: '<S2>/Unit Delay6' */
  rtb_UnitDelay6 = str_speed_DWork.UnitDelay6_DSTATE;

  /* Embedded MATLAB: '<S2>/Embedded MATLAB Function' incorporates:
   *  Inport: '<Root>/Sensor'
   *  SignalConversion: '<S4>/TmpSignal ConversionAt SFunction Inport1'
   *  SignalConversion: '<S4>/TmpSignal ConversionAt SFunction Inport2'
   *  UnitDelay: '<S2>/Unit Delay'
   *  UnitDelay: '<S2>/Unit Delay1'
   *  UnitDelay: '<S2>/Unit Delay2'
   *  UnitDelay: '<S2>/Unit Delay5'
   */
  /* Embedded MATLAB Function 'Identification/Embedded MATLAB Function': '<S4>:1' */
  /* '<S4>:1:3' */
  /* '<S4>:1:4' */
  eml_PHI_idx = -str_speed_DWork.UnitDelay6_DSTATE;
  eml_PHI_idx_0 = -str_speed_DWork.UnitDelay5_DSTATE;

  /* '<S4>:1:5' */
  eml_a[0] = eml_PHI_idx;
  eml_a[1] = eml_PHI_idx_0;
  eml_a[2] = str_speed_DWork.UnitDelay3_DSTATE;
  eml_a[3] = str_speed_DWork.UnitDelay2_DSTATE;
  eml_e = In2 - (((eml_a[0] * str_speed_DWork.UnitDelay_DSTATE[0] + eml_a[1] *
                   str_speed_DWork.UnitDelay_DSTATE[1]) + eml_a[2] *
                  str_speed_DWork.UnitDelay_DSTATE[2]) + eml_a[3] *
                 str_speed_DWork.UnitDelay_DSTATE[3]);

  /* '<S4>:1:6' */
  for (tmp = 0; tmp < 4; tmp++) {
    eml_y = str_speed_DWork.UnitDelay1_DSTATE[(tmp << 2) + 3] *
      str_speed_DWork.UnitDelay2_DSTATE + (str_speed_DWork.UnitDelay1_DSTATE
      [(tmp << 2) + 2] * str_speed_DWork.UnitDelay3_DSTATE +
      (str_speed_DWork.UnitDelay1_DSTATE[(tmp << 2) + 1] * eml_PHI_idx_0 +
       str_speed_DWork.UnitDelay1_DSTATE[(tmp << 2)] * eml_PHI_idx));
    eml_a[tmp] = eml_y;
  }

  eml_B = (((eml_a[0] * eml_PHI_idx + eml_a[1] * eml_PHI_idx_0) + eml_a[2] *
            str_speed_DWork.UnitDelay3_DSTATE) + eml_a[3] *
           str_speed_DWork.UnitDelay2_DSTATE) + 0.95;

  /* '<S4>:1:7' */
  for (tmp = 0; tmp < 4; tmp++) {
    eml_y = str_speed_DWork.UnitDelay1_DSTATE[(tmp << 2) + 3] *
      str_speed_DWork.UnitDelay2_DSTATE + (str_speed_DWork.UnitDelay1_DSTATE
      [(tmp << 2) + 2] * str_speed_DWork.UnitDelay3_DSTATE +
      (str_speed_DWork.UnitDelay1_DSTATE[(tmp << 2) + 1] * eml_PHI_idx_0 +
       str_speed_DWork.UnitDelay1_DSTATE[(tmp << 2)] * eml_PHI_idx));
    rtb_Theta[tmp] = (((str_speed_DWork.UnitDelay1_DSTATE[tmp + 4] *
                        eml_PHI_idx_0 + str_speed_DWork.UnitDelay1_DSTATE[tmp] *
                        eml_PHI_idx) + str_speed_DWork.UnitDelay1_DSTATE[tmp + 8]
                       * str_speed_DWork.UnitDelay3_DSTATE) +
                      str_speed_DWork.UnitDelay1_DSTATE[tmp + 12] *
                      str_speed_DWork.UnitDelay2_DSTATE) / eml_B * eml_e +
      str_speed_DWork.UnitDelay_DSTATE[tmp];
    rtb_UnitDelay6_l = str_speed_DWork.UnitDelay1_DSTATE[tmp + 12] *
      str_speed_DWork.UnitDelay2_DSTATE + (str_speed_DWork.UnitDelay1_DSTATE[tmp
      + 8] * str_speed_DWork.UnitDelay3_DSTATE +
      (str_speed_DWork.UnitDelay1_DSTATE[tmp + 4] * eml_PHI_idx_0 +
       str_speed_DWork.UnitDelay1_DSTATE[tmp] * eml_PHI_idx));
    rtb_UnitDelay2_m = str_speed_DWork.UnitDelay1_DSTATE[(tmp << 2) + 3] *
      str_speed_DWork.UnitDelay2_DSTATE + (str_speed_DWork.UnitDelay1_DSTATE
      [(tmp << 2) + 2] * str_speed_DWork.UnitDelay3_DSTATE +
      (str_speed_DWork.UnitDelay1_DSTATE[(tmp << 2) + 1] * eml_PHI_idx_0 +
       str_speed_DWork.UnitDelay1_DSTATE[(tmp << 2)] * eml_PHI_idx));
    eml_PHI[tmp] = rtb_UnitDelay2_m;
    tmp_0[tmp] = rtb_UnitDelay6_l;
    eml_a[tmp] = eml_y;
  }

  eml_y = (((eml_a[0] * eml_PHI_idx + eml_a[1] * eml_PHI_idx_0) + eml_a[2] *
            str_speed_DWork.UnitDelay3_DSTATE) + eml_a[3] *
           str_speed_DWork.UnitDelay2_DSTATE) + 0.95;

  /* '<S4>:1:8' */

  /* UnitDelay: '<S3>/Unit Delay6' */
  rtb_UnitDelay6_l = str_speed_DWork.UnitDelay6_DSTATE_o;

  /* UnitDelay: '<S3>/Unit Delay2' */
  rtb_UnitDelay2_m = str_speed_DWork.UnitDelay2_DSTATE_a;

  /* Embedded MATLAB: '<S3>/Embedded MATLAB Function' incorporates:
   *  Inport: '<Root>/Sensor'
   *  Inport: '<Root>/Set point'
   *  SignalConversion: '<S5>/TmpSignal ConversionAt SFunction Inport3'
   *  SignalConversion: '<S5>/TmpSignal ConversionAt SFunction Inport4'
   *  UnitDelay: '<S3>/Unit Delay1'
   *  UnitDelay: '<S3>/Unit Delay5'
   */
  /* Embedded MATLAB Function 'Self-Tuning Regulator/Embedded MATLAB Function': '<S5>:1' */
  /*  Cai dat cap cuc (mien roi rac) mong muon */
  /*  Gan lai cho de su dung */
  /* '<S5>:1:7' */
  /* '<S5>:1:8' */
  /* '<S5>:1:9' */
  /* '<S5>:1:10' */
  /*  Sinh vien tham khao huong dan Muc 2.4.2 de viet bo sung code */
  /* '<S5>:1:12' */
  eml_e = -1.4 - rtb_Theta[0];

  /* '<S5>:1:13' */
  eml_B = (2.17 + rtb_Theta[0]) - rtb_Theta[1];

  /* '<S5>:1:14' */
  eml_PHI_idx = 0.876 - rtb_Theta[1];

  /* '<S5>:1:15' */
  /* '<S5>:1:17' */
  eml_PHI_idx_0 = ((rtb_Theta[0] * rtb_Theta[2] * rtb_Theta[3] - rtb_Theta[1] *
                    rt_pow_snf(rtb_Theta[2], 2.0)) - rt_pow_snf(rtb_Theta[3],
    2.0)) * (rtb_Theta[2] + rtb_Theta[3]);

  /* '<S5>:1:18' */
  eml_r = (((eml_B - eml_PHI_idx) + 1.3319999999999999E-001) * rtb_Theta[2] -
           rtb_Theta[3] * eml_e) * (rtb_Theta[0] * rtb_Theta[3]);

  /* '<S5>:1:19' */
  eml_r_0 = (rtb_Theta[3] * eml_e - ((eml_B - eml_PHI_idx) +
              1.3319999999999999E-001) * rtb_Theta[2]) * (rtb_Theta[1] *
    rtb_Theta[2]);

  /* '<S5>:1:20' */
  eml_r_1 = ((eml_PHI_idx - 1.3319999999999999E-001) * rtb_Theta[3] + rtb_Theta
             [2] * 1.3319999999999999E-001) * (rtb_Theta[2] + rtb_Theta[3]);

  /* '<S5>:1:21' */
  eml_r_2 = ((rtb_Theta[2] * rtb_Theta[3] * eml_PHI_idx + rt_pow_snf(rtb_Theta[2],
    2.0) * 1.3319999999999999E-001) + rt_pow_snf(rtb_Theta[3], 2.0) * eml_B) *
    rtb_Theta[2] - rt_pow_snf(rtb_Theta[3], 3.0) * eml_e;

  /* '<S5>:1:22' */
  eml_r_3 = ((rtb_Theta[1] * eml_PHI_idx + rtb_Theta[0] *
              1.3319999999999999E-001) - rtb_Theta[1] * 1.3319999999999999E-001)
    * rt_pow_snf(rtb_Theta[2], 2.0);

  /* '<S5>:1:23' */
  eml_a_0 = (((rtb_Theta[0] * 1.3319999999999999E-001 + rtb_Theta[1] * eml_B) -
              1.3319999999999999E-001) * rtb_Theta[2] - (rtb_Theta[1] * eml_e +
              1.3319999999999999E-001) * rtb_Theta[3]) * rtb_Theta[3];

  /* '<S5>:1:25' */
  eml_e = (((eml_e + eml_B) - eml_PHI_idx) + 1.3319999999999999E-001) /
    (rtb_Theta[2] + rtb_Theta[3]);

  /* '<S5>:1:26' */
  /* '<S5>:1:27' */
  /* '<S5>:1:28' */
  /* '<S5>:1:29' */
  /* '<S5>:1:30' */
  /*  Luat dieu khien */
  /* '<S5>:1:33' */
  eml_e = ((((eml_e * In1 - (eml_e - ((eml_r + eml_r_0) + eml_r_1) /
    eml_PHI_idx_0) * In2) - ((((eml_r + eml_r_0) + eml_r_1) - eml_r_3) - eml_a_0)
             / eml_PHI_idx_0 * str_speed_DWork.UnitDelay6_DSTATE_o) - (eml_r_3 +
             eml_a_0) / eml_PHI_idx_0 * str_speed_DWork.UnitDelay5_DSTATE_h) -
           (eml_r_2 - eml_PHI_idx_0) / eml_PHI_idx_0 *
           str_speed_DWork.UnitDelay2_DSTATE_a) - (-(eml_r_2 / eml_PHI_idx_0)) *
    str_speed_DWork.UnitDelay1_DSTATE_k;

  /* Saturate: '<S3>/Saturation' */
  Out1 = rt_SATURATE(eml_e, str_speed_P.Saturation_LowerSat,
                     str_speed_P.Saturation_UpperSat);

  /* Update for UnitDelay: '<S2>/Unit Delay3' */
  str_speed_DWork.UnitDelay3_DSTATE = Out1;

  /* Update for UnitDelay: '<S2>/Unit Delay2' */
  str_speed_DWork.UnitDelay2_DSTATE = rtb_UnitDelay3;

  /* Update for UnitDelay: '<S2>/Unit Delay6' incorporates:
   *  Update for Inport: '<Root>/Sensor'
   */
  str_speed_DWork.UnitDelay6_DSTATE = In2;

  /* Update for UnitDelay: '<S2>/Unit Delay5' */
  str_speed_DWork.UnitDelay5_DSTATE = rtb_UnitDelay6;

  /* Update for UnitDelay: '<S2>/Unit Delay1' incorporates:
   *  UnitDelay: '<S2>/Unit Delay1'
   */
  for (tmp = 0; tmp < 4; tmp++) {
    tmp_1[tmp] = str_speed_DWork.UnitDelay1_DSTATE[tmp] - tmp_0[tmp] * eml_PHI[0]
      / eml_y;
    tmp_1[tmp + 4] = str_speed_DWork.UnitDelay1_DSTATE[tmp + 4] - tmp_0[tmp] *
      eml_PHI[1] / eml_y;
    tmp_1[tmp + 8] = str_speed_DWork.UnitDelay1_DSTATE[tmp + 8] - tmp_0[tmp] *
      eml_PHI[2] / eml_y;
    tmp_1[tmp + 12] = str_speed_DWork.UnitDelay1_DSTATE[tmp + 12] - tmp_0[tmp] *
      eml_PHI[3] / eml_y;
  }

  for (tmp = 0; tmp < 4; tmp++) {
    str_speed_DWork.UnitDelay1_DSTATE[(tmp << 2)] = tmp_1[tmp << 2] *
      1.0526315789473684E+000;
    str_speed_DWork.UnitDelay1_DSTATE[1 + (tmp << 2)] = tmp_1[(tmp << 2) + 1] *
      1.0526315789473684E+000;
    str_speed_DWork.UnitDelay1_DSTATE[2 + (tmp << 2)] = tmp_1[(tmp << 2) + 2] *
      1.0526315789473684E+000;
    str_speed_DWork.UnitDelay1_DSTATE[3 + (tmp << 2)] = tmp_1[(tmp << 2) + 3] *
      1.0526315789473684E+000;
  }

  /* Update for UnitDelay: '<S2>/Unit Delay' */
  str_speed_DWork.UnitDelay_DSTATE[0] = rtb_Theta[0];
  str_speed_DWork.UnitDelay_DSTATE[1] = rtb_Theta[1];
  str_speed_DWork.UnitDelay_DSTATE[2] = rtb_Theta[2];
  str_speed_DWork.UnitDelay_DSTATE[3] = rtb_Theta[3];

  /* Update for UnitDelay: '<S3>/Unit Delay6' incorporates:
   *  Update for Inport: '<Root>/Sensor'
   */
  str_speed_DWork.UnitDelay6_DSTATE_o = In2;

  /* Update for UnitDelay: '<S3>/Unit Delay5' */
  str_speed_DWork.UnitDelay5_DSTATE_h = rtb_UnitDelay6_l;

  /* Update for UnitDelay: '<S3>/Unit Delay2' */
  str_speed_DWork.UnitDelay2_DSTATE_a = Out1;

  /* Update for UnitDelay: '<S3>/Unit Delay1' */
  str_speed_DWork.UnitDelay1_DSTATE_k = rtb_UnitDelay2_m;
}

/* Model initialize function */
void str_speed_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatus(str_speed_M, (NULL));

  /* block I/O */

  /* exported global signals */
  Out1 = 0.0;

  /* states (dwork) */
  (void) memset((void *)&str_speed_DWork, 0,
                sizeof(D_Work_str_speed));

  /* external inputs */
  In2 = 0.0;
  In1 = 0.0;

  /* InitializeConditions for UnitDelay: '<S2>/Unit Delay3' */
  str_speed_DWork.UnitDelay3_DSTATE = str_speed_P.UnitDelay3_X0;

  /* InitializeConditions for UnitDelay: '<S2>/Unit Delay2' */
  str_speed_DWork.UnitDelay2_DSTATE = str_speed_P.UnitDelay2_X0;

  /* InitializeConditions for UnitDelay: '<S2>/Unit Delay6' */
  str_speed_DWork.UnitDelay6_DSTATE = str_speed_P.UnitDelay6_X0;

  /* InitializeConditions for UnitDelay: '<S2>/Unit Delay5' */
  str_speed_DWork.UnitDelay5_DSTATE = str_speed_P.UnitDelay5_X0;

  /* InitializeConditions for UnitDelay: '<S2>/Unit Delay1' */
  memcpy((void *)(&str_speed_DWork.UnitDelay1_DSTATE[0]), (void *)
         (&str_speed_P.UnitDelay1_X0[0]), sizeof(real_T) << 4U);

  /* InitializeConditions for UnitDelay: '<S2>/Unit Delay' */
  str_speed_DWork.UnitDelay_DSTATE[0] = str_speed_P.UnitDelay_X0[0];
  str_speed_DWork.UnitDelay_DSTATE[1] = str_speed_P.UnitDelay_X0[1];
  str_speed_DWork.UnitDelay_DSTATE[2] = str_speed_P.UnitDelay_X0[2];
  str_speed_DWork.UnitDelay_DSTATE[3] = str_speed_P.UnitDelay_X0[3];

  /* InitializeConditions for UnitDelay: '<S3>/Unit Delay6' */
  str_speed_DWork.UnitDelay6_DSTATE_o = str_speed_P.UnitDelay6_X0_a;

  /* InitializeConditions for UnitDelay: '<S3>/Unit Delay5' */
  str_speed_DWork.UnitDelay5_DSTATE_h = str_speed_P.UnitDelay5_X0_d;

  /* InitializeConditions for UnitDelay: '<S3>/Unit Delay2' */
  str_speed_DWork.UnitDelay2_DSTATE_a = str_speed_P.UnitDelay2_X0_h;

  /* InitializeConditions for UnitDelay: '<S3>/Unit Delay1' */
  str_speed_DWork.UnitDelay1_DSTATE_k = str_speed_P.UnitDelay1_X0_c;
}

/* Model terminate function */
void str_speed_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for Real-Time Workshop generated code.
 *
 * [EOF]
 */
