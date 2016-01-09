/* Include files */

#include <stddef.h>
#include "blas.h"
#include "mpc_tmpdemo_2014b_sfun.h"
#include "c1_mpc_tmpdemo_2014b.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "mpc_tmpdemo_2014b_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c1_debug_family_names[28] = { "options", "zopt", "nu", "ny",
  "u0", "y", "xkk", "p", "b", "h", "nargin", "nargout", "f", "H", "F", "G", "S",
  "s", "M", "L", "A", "B", "C", "xkk1", "u", "feasRes", "xk1k", "time" };

/* Function Declarations */
static void initialize_c1_mpc_tmpdemo_2014b(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance);
static void initialize_params_c1_mpc_tmpdemo_2014b
  (SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance);
static void enable_c1_mpc_tmpdemo_2014b(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance);
static void disable_c1_mpc_tmpdemo_2014b(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance);
static void c1_update_debugger_state_c1_mpc_tmpdemo_2014b
  (SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c1_mpc_tmpdemo_2014b
  (SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance);
static void set_sim_state_c1_mpc_tmpdemo_2014b
  (SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance, const mxArray *c1_st);
static void finalize_c1_mpc_tmpdemo_2014b(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance);
static void sf_gateway_c1_mpc_tmpdemo_2014b(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance);
static void mdl_start_c1_mpc_tmpdemo_2014b(SFc1_mpc_tmpdemo_2014bInstanceStruct *
  chartInstance);
static void c1_chartstep_c1_mpc_tmpdemo_2014b
  (SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance);
static void initSimStructsc1_mpc_tmpdemo_2014b
  (SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_b_xk1k, const char_T *c1_identifier, real_T
  c1_y[7]);
static void c1_b_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[7]);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_c_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_b_feasRes, const char_T *c1_identifier,
  real_T c1_y[195]);
static void c1_d_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[195]);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_e_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const char_T *c1_identifier, real_T
  c1_y[5]);
static void c1_f_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[5]);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_i_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_j_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_k_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_l_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_m_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_n_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_o_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_g_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[18]);
static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_p_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_h_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[6]);
static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_q_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static c1_sflJsObR9dsqNm7nhVXYguC c1_i_emlrt_marshallIn
  (SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance, const mxArray *c1_c_u,
   const emlrtMsgIdentifier *c1_parentId);
static void c1_j_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId,
  char_T c1_y[21]);
static void c1_k_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId,
  char_T c1_y[4]);
static void c1_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_info_helper(const mxArray **c1_info);
static const mxArray *c1_emlrt_marshallOut(const char * c1_c_u);
static const mxArray *c1_b_emlrt_marshallOut(const uint32_T c1_c_u);
static void c1_eml_scalar_eg(SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance);
static void c1_threshold(SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance);
static void c1_b_eml_scalar_eg(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance);
static void c1_c_eml_scalar_eg(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance);
static void c1_eml_xgemm(SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance,
  real_T c1_b_A[3510], real_T c1_b_B[18], real_T c1_b_C[195], real_T c1_c_C[195]);
static void c1_d_eml_scalar_eg(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance);
static void c1_e_eml_scalar_eg(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance);
static void c1_b_eml_xgemm(SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance,
  real_T c1_b_A[5070], real_T c1_b_B[26], real_T c1_b_C[195], real_T c1_c_C[195]);
static void c1_f_eml_scalar_eg(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance);
static void c1_g_eml_scalar_eg(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance);
static void c1_l_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_zopt, const char_T *c1_identifier, real_T
  c1_y[26]);
static void c1_m_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[26]);
static real_T c1_n_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_b_time, const char_T *c1_identifier);
static real_T c1_o_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId);
static const mxArray *c1_r_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_p_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_q_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_mpc_tmpdemo_2014b, const
  char_T *c1_identifier);
static uint8_T c1_r_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_c_eml_xgemm(SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance,
  real_T c1_b_A[3510], real_T c1_b_B[18], real_T c1_b_C[195]);
static void c1_d_eml_xgemm(SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance,
  real_T c1_b_A[5070], real_T c1_b_B[26], real_T c1_b_C[195]);
static void init_dsm_address_info(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c1_mpc_tmpdemo_2014b(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c1_is_active_c1_mpc_tmpdemo_2014b = 0U;
}

static void initialize_params_c1_mpc_tmpdemo_2014b
  (SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c1_mpc_tmpdemo_2014b(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c1_mpc_tmpdemo_2014b(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c1_update_debugger_state_c1_mpc_tmpdemo_2014b
  (SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c1_mpc_tmpdemo_2014b
  (SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  int32_T c1_i0;
  real_T c1_c_u[195];
  const mxArray *c1_b_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_d_u;
  const mxArray *c1_c_y = NULL;
  int32_T c1_i1;
  real_T c1_e_u[5];
  const mxArray *c1_d_y = NULL;
  int32_T c1_i2;
  real_T c1_f_u[7];
  const mxArray *c1_e_y = NULL;
  uint8_T c1_b_hoistedGlobal;
  uint8_T c1_g_u;
  const mxArray *c1_f_y = NULL;
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellmatrix(5, 1), false);
  for (c1_i0 = 0; c1_i0 < 195; c1_i0++) {
    c1_c_u[c1_i0] = (*chartInstance->c1_feasRes)[c1_i0];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 1, 195),
                false);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_hoistedGlobal = *chartInstance->c1_time;
  c1_d_u = c1_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  for (c1_i1 = 0; c1_i1 < 5; c1_i1++) {
    c1_e_u[c1_i1] = (*chartInstance->c1_b_u)[c1_i1];
  }

  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_e_u, 0, 0U, 1U, 0U, 1, 5), false);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  for (c1_i2 = 0; c1_i2 < 7; c1_i2++) {
    c1_f_u[c1_i2] = (*chartInstance->c1_xk1k)[c1_i2];
  }

  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", c1_f_u, 0, 0U, 1U, 0U, 1, 7), false);
  sf_mex_setcell(c1_y, 3, c1_e_y);
  c1_b_hoistedGlobal = chartInstance->c1_is_active_c1_mpc_tmpdemo_2014b;
  c1_g_u = c1_b_hoistedGlobal;
  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_g_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 4, c1_f_y);
  sf_mex_assign(&c1_st, c1_y, false);
  return c1_st;
}

static void set_sim_state_c1_mpc_tmpdemo_2014b
  (SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance, const mxArray *c1_st)
{
  const mxArray *c1_c_u;
  real_T c1_dv0[195];
  int32_T c1_i3;
  real_T c1_dv1[5];
  int32_T c1_i4;
  real_T c1_dv2[7];
  int32_T c1_i5;
  chartInstance->c1_doneDoubleBufferReInit = true;
  c1_c_u = sf_mex_dup(c1_st);
  c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_c_u, 0)),
                        "feasRes", c1_dv0);
  for (c1_i3 = 0; c1_i3 < 195; c1_i3++) {
    (*chartInstance->c1_feasRes)[c1_i3] = c1_dv0[c1_i3];
  }

  *chartInstance->c1_time = c1_n_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_c_u, 1)), "time");
  c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_c_u, 2)),
                        "u", c1_dv1);
  for (c1_i4 = 0; c1_i4 < 5; c1_i4++) {
    (*chartInstance->c1_b_u)[c1_i4] = c1_dv1[c1_i4];
  }

  c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_c_u, 3)),
                      "xk1k", c1_dv2);
  for (c1_i5 = 0; c1_i5 < 7; c1_i5++) {
    (*chartInstance->c1_xk1k)[c1_i5] = c1_dv2[c1_i5];
  }

  chartInstance->c1_is_active_c1_mpc_tmpdemo_2014b = c1_q_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_c_u, 4)),
     "is_active_c1_mpc_tmpdemo_2014b");
  sf_mex_destroy(&c1_c_u);
  c1_update_debugger_state_c1_mpc_tmpdemo_2014b(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_mpc_tmpdemo_2014b(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c1_mpc_tmpdemo_2014b(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance)
{
  int32_T c1_i6;
  int32_T c1_i7;
  int32_T c1_i8;
  int32_T c1_i9;
  int32_T c1_i10;
  int32_T c1_i11;
  int32_T c1_i12;
  int32_T c1_i13;
  int32_T c1_i14;
  int32_T c1_i15;
  int32_T c1_i16;
  int32_T c1_i17;
  int32_T c1_i18;
  int32_T c1_i19;
  int32_T c1_i20;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i6 = 0; c1_i6 < 17; c1_i6++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_f)[c1_i6], 0U);
  }

  for (c1_i7 = 0; c1_i7 < 676; c1_i7++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_H)[c1_i7], 1U);
  }

  for (c1_i8 = 0; c1_i8 < 468; c1_i8++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_F)[c1_i8], 2U);
  }

  for (c1_i9 = 0; c1_i9 < 5070; c1_i9++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_b_G)[c1_i9], 3U);
  }

  for (c1_i10 = 0; c1_i10 < 3510; c1_i10++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_S)[c1_i10], 4U);
  }

  for (c1_i11 = 0; c1_i11 < 195; c1_i11++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_s)[c1_i11], 5U);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_mpc_tmpdemo_2014b(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_mpc_tmpdemo_2014bMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c1_i12 = 0; c1_i12 < 5; c1_i12++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_b_u)[c1_i12], 6U);
  }

  for (c1_i13 = 0; c1_i13 < 195; c1_i13++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_feasRes)[c1_i13], 7U);
  }

  for (c1_i14 = 0; c1_i14 < 42; c1_i14++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_M)[c1_i14], 8U);
  }

  for (c1_i15 = 0; c1_i15 < 42; c1_i15++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_L)[c1_i15], 9U);
  }

  for (c1_i16 = 0; c1_i16 < 7; c1_i16++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_xk1k)[c1_i16], 10U);
  }

  for (c1_i17 = 0; c1_i17 < 49; c1_i17++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_A)[c1_i17], 11U);
  }

  for (c1_i18 = 0; c1_i18 < 35; c1_i18++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_B)[c1_i18], 12U);
  }

  for (c1_i19 = 0; c1_i19 < 42; c1_i19++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_C)[c1_i19], 13U);
  }

  for (c1_i20 = 0; c1_i20 < 7; c1_i20++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_xkk1)[c1_i20], 14U);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_time, 15U);
}

static void mdl_start_c1_mpc_tmpdemo_2014b(SFc1_mpc_tmpdemo_2014bInstanceStruct *
  chartInstance)
{
  (void)chartInstance;
}

static void c1_chartstep_c1_mpc_tmpdemo_2014b
  (SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance)
{
  int32_T c1_i21;
  real_T c1_b_f[17];
  int32_T c1_i22;
  real_T c1_b_H[676];
  int32_T c1_i23;
  real_T c1_b_F[468];
  int32_T c1_i24;
  int32_T c1_i25;
  real_T c1_b_S[3510];
  int32_T c1_i26;
  real_T c1_b_s[195];
  int32_T c1_i27;
  real_T c1_b_M[42];
  int32_T c1_i28;
  real_T c1_b_L[42];
  int32_T c1_i29;
  real_T c1_b_A[49];
  int32_T c1_i30;
  real_T c1_b_B[35];
  int32_T c1_i31;
  real_T c1_b_C[42];
  int32_T c1_i32;
  real_T c1_b_xkk1[7];
  uint32_T c1_debug_family_var_map[28];
  c1_sflJsObR9dsqNm7nhVXYguC c1_options;
  real_T c1_zopt[26];
  real_T c1_nu;
  real_T c1_ny;
  real_T c1_u0[5];
  real_T c1_y[6];
  real_T c1_xkk[7];
  real_T c1_p[18];
  real_T c1_b[195];
  real_T c1_h[26];
  real_T c1_nargin = 12.0;
  real_T c1_nargout = 4.0;
  real_T c1_c_u[5];
  real_T c1_b_feasRes[195];
  real_T c1_b_xk1k[7];
  real_T c1_b_time;
  int32_T c1_i33;
  static char_T c1_cv0[21] = { 'i', 'n', 't', 'e', 'r', 'i', 'o', 'r', '-', 'p',
    'o', 'i', 'n', 't', '-', 'c', 'o', 'n', 'v', 'e', 'x' };

  int32_T c1_i34;
  static char_T c1_cv1[4] = { 'n', 'o', 'n', 'e' };

  int32_T c1_i35;
  int32_T c1_i36;
  int32_T c1_i37;
  int32_T c1_i38;
  real_T c1_a[42];
  int32_T c1_i39;
  real_T c1_b_b[7];
  int32_T c1_i40;
  real_T c1_b_y[6];
  int32_T c1_i41;
  int32_T c1_i42;
  int32_T c1_i43;
  real_T c1_b_a[42];
  int32_T c1_i44;
  int32_T c1_i45;
  real_T c1_c_y[7];
  int32_T c1_i46;
  int32_T c1_i47;
  int32_T c1_i48;
  int32_T c1_i49;
  int32_T c1_i50;
  int32_T c1_i51;
  int32_T c1_i52;
  real_T c1_c_a[3510];
  int32_T c1_i53;
  real_T c1_c_b[18];
  int32_T c1_i54;
  real_T c1_d_y[195];
  int32_T c1_i55;
  real_T c1_d_a[3510];
  int32_T c1_i56;
  real_T c1_d_b[18];
  int32_T c1_i57;
  int32_T c1_i58;
  real_T c1_e_a[468];
  int32_T c1_i59;
  int32_T c1_i60;
  int32_T c1_i61;
  int32_T c1_i62;
  real_T c1_c_C[26];
  int32_T c1_i63;
  int32_T c1_i64;
  int32_T c1_i65;
  int32_T c1_i66;
  int32_T c1_i67;
  int32_T c1_i68;
  int32_T c1_i69;
  real_T c1_d_u[676];
  const mxArray *c1_e_y = NULL;
  int32_T c1_i70;
  real_T c1_e_u[26];
  const mxArray *c1_f_y = NULL;
  int32_T c1_i71;
  const mxArray *c1_g_y = NULL;
  int32_T c1_i72;
  real_T c1_f_u[195];
  const mxArray *c1_h_y = NULL;
  const mxArray *c1_i_y = NULL;
  const mxArray *c1_j_y = NULL;
  const mxArray *c1_k_y = NULL;
  const mxArray *c1_l_y = NULL;
  const mxArray *c1_m_y = NULL;
  real_T c1_g_u;
  const mxArray *c1_n_y = NULL;
  const mxArray *c1_unusedU1 = NULL;
  const mxArray *c1_c_time = NULL;
  const mxArray *c1_b_zopt = NULL;
  real_T c1_dv3[26];
  int32_T c1_i73;
  const mxArray *c1_b_unusedU1 = NULL;
  int32_T c1_i74;
  real_T c1_f_a[5070];
  int32_T c1_i75;
  int32_T c1_i76;
  int32_T c1_i77;
  real_T c1_g_a[5070];
  int32_T c1_i78;
  real_T c1_d_C[26];
  int32_T c1_i79;
  int32_T c1_i80;
  int32_T c1_i81;
  real_T c1_h_a[49];
  int32_T c1_i82;
  int32_T c1_i83;
  int32_T c1_i84;
  int32_T c1_i85;
  int32_T c1_i86;
  real_T c1_i_a[35];
  int32_T c1_i87;
  real_T c1_e_b[5];
  int32_T c1_i88;
  real_T c1_o_y[7];
  int32_T c1_i89;
  int32_T c1_i90;
  int32_T c1_i91;
  int32_T c1_i92;
  int32_T c1_i93;
  int32_T c1_i94;
  int32_T c1_i95;
  int32_T c1_i96;
  int32_T c1_i97;
  int32_T c1_i98;
  int32_T c1_i99;
  int32_T c1_i100;
  int32_T c1_i101;
  int32_T c1_i102;
  int32_T c1_i103;
  int32_T c1_i104;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i21 = 0; c1_i21 < 17; c1_i21++) {
    c1_b_f[c1_i21] = (*chartInstance->c1_f)[c1_i21];
  }

  for (c1_i22 = 0; c1_i22 < 676; c1_i22++) {
    c1_b_H[c1_i22] = (*chartInstance->c1_H)[c1_i22];
  }

  for (c1_i23 = 0; c1_i23 < 468; c1_i23++) {
    c1_b_F[c1_i23] = (*chartInstance->c1_F)[c1_i23];
  }

  for (c1_i24 = 0; c1_i24 < 5070; c1_i24++) {
    chartInstance->c1_G[c1_i24] = (*chartInstance->c1_b_G)[c1_i24];
  }

  for (c1_i25 = 0; c1_i25 < 3510; c1_i25++) {
    c1_b_S[c1_i25] = (*chartInstance->c1_S)[c1_i25];
  }

  for (c1_i26 = 0; c1_i26 < 195; c1_i26++) {
    c1_b_s[c1_i26] = (*chartInstance->c1_s)[c1_i26];
  }

  for (c1_i27 = 0; c1_i27 < 42; c1_i27++) {
    c1_b_M[c1_i27] = (*chartInstance->c1_M)[c1_i27];
  }

  for (c1_i28 = 0; c1_i28 < 42; c1_i28++) {
    c1_b_L[c1_i28] = (*chartInstance->c1_L)[c1_i28];
  }

  for (c1_i29 = 0; c1_i29 < 49; c1_i29++) {
    c1_b_A[c1_i29] = (*chartInstance->c1_A)[c1_i29];
  }

  for (c1_i30 = 0; c1_i30 < 35; c1_i30++) {
    c1_b_B[c1_i30] = (*chartInstance->c1_B)[c1_i30];
  }

  for (c1_i31 = 0; c1_i31 < 42; c1_i31++) {
    c1_b_C[c1_i31] = (*chartInstance->c1_C)[c1_i31];
  }

  for (c1_i32 = 0; c1_i32 < 7; c1_i32++) {
    c1_b_xkk1[c1_i32] = (*chartInstance->c1_xkk1)[c1_i32];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 28U, 28U, c1_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_options, 0U, c1_q_sf_marshallOut,
    c1_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_zopt, 1U, c1_n_sf_marshallOut,
    c1_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_nu, 2U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_ny, 3U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_u0, 4U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_y, 5U, c1_p_sf_marshallOut,
    c1_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_xkk, 6U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_p, 7U, c1_o_sf_marshallOut,
    c1_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_b, 8U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_h, 9U, c1_n_sf_marshallOut,
    c1_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 10U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 11U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_f, 12U, c1_m_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_H, 13U, c1_l_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_F, 14U, c1_k_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(chartInstance->c1_G, 15U, c1_j_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_S, 16U, c1_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_s, 17U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_M, 18U, c1_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_L, 19U, c1_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_A, 20U, c1_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_B, 21U, c1_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_C, 22U, c1_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_xkk1, 23U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_c_u, 24U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_b_feasRes, 25U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_b_xk1k, 26U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_time, 27U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 7);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 8);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 9);
  for (c1_i33 = 0; c1_i33 < 21; c1_i33++) {
    c1_options.Algorithm[c1_i33] = c1_cv0[c1_i33];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 10);
  c1_options.MaxIter = 1000.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 11);
  c1_options.TolCon = 1.0E-12;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 12);
  c1_options.TolFun = 1.0E-12;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 13);
  c1_options.TolX = 1.0E-12;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 14);
  for (c1_i34 = 0; c1_i34 < 4; c1_i34++) {
    c1_options.Display[c1_i34] = c1_cv1[c1_i34];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 15);
  for (c1_i35 = 0; c1_i35 < 26; c1_i35++) {
    c1_zopt[c1_i35] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 16);
  c1_b_time = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 19);
  c1_nu = 5.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 19);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 20);
  c1_ny = 6.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 21);
  for (c1_i36 = 0; c1_i36 < 5; c1_i36++) {
    c1_u0[c1_i36] = c1_b_f[c1_i36];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 22);
  for (c1_i37 = 0; c1_i37 < 6; c1_i37++) {
    c1_y[c1_i37] = c1_b_f[c1_i37 + 5];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 24);
  for (c1_i38 = 0; c1_i38 < 42; c1_i38++) {
    c1_a[c1_i38] = c1_b_C[c1_i38];
  }

  for (c1_i39 = 0; c1_i39 < 7; c1_i39++) {
    c1_b_b[c1_i39] = c1_b_xkk1[c1_i39];
  }

  c1_eml_scalar_eg(chartInstance);
  c1_eml_scalar_eg(chartInstance);
  c1_threshold(chartInstance);
  for (c1_i40 = 0; c1_i40 < 6; c1_i40++) {
    c1_b_y[c1_i40] = 0.0;
    c1_i41 = 0;
    for (c1_i42 = 0; c1_i42 < 7; c1_i42++) {
      c1_b_y[c1_i40] += c1_a[c1_i41 + c1_i40] * c1_b_b[c1_i42];
      c1_i41 += 6;
    }
  }

  for (c1_i43 = 0; c1_i43 < 42; c1_i43++) {
    c1_b_a[c1_i43] = c1_b_M[c1_i43];
  }

  for (c1_i44 = 0; c1_i44 < 6; c1_i44++) {
    c1_b_y[c1_i44] = c1_y[c1_i44] - c1_b_y[c1_i44];
  }

  c1_b_eml_scalar_eg(chartInstance);
  c1_b_eml_scalar_eg(chartInstance);
  c1_threshold(chartInstance);
  for (c1_i45 = 0; c1_i45 < 7; c1_i45++) {
    c1_c_y[c1_i45] = 0.0;
    c1_i46 = 0;
    for (c1_i47 = 0; c1_i47 < 6; c1_i47++) {
      c1_c_y[c1_i45] += c1_b_a[c1_i46 + c1_i45] * c1_b_y[c1_i47];
      c1_i46 += 7;
    }
  }

  for (c1_i48 = 0; c1_i48 < 7; c1_i48++) {
    c1_xkk[c1_i48] = c1_b_xkk1[c1_i48] + c1_c_y[c1_i48];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 27);
  for (c1_i49 = 0; c1_i49 < 5; c1_i49++) {
    c1_p[c1_i49] = c1_b_f[c1_i49];
  }

  for (c1_i50 = 0; c1_i50 < 7; c1_i50++) {
    c1_p[c1_i50 + 5] = c1_xkk[c1_i50];
  }

  for (c1_i51 = 0; c1_i51 < 6; c1_i51++) {
    c1_p[c1_i51 + 12] = c1_b_f[c1_i51 + 11];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 29);
  for (c1_i52 = 0; c1_i52 < 3510; c1_i52++) {
    c1_c_a[c1_i52] = c1_b_S[c1_i52];
  }

  for (c1_i53 = 0; c1_i53 < 18; c1_i53++) {
    c1_c_b[c1_i53] = c1_p[c1_i53];
  }

  c1_c_eml_scalar_eg(chartInstance);
  c1_c_eml_scalar_eg(chartInstance);
  for (c1_i54 = 0; c1_i54 < 195; c1_i54++) {
    c1_d_y[c1_i54] = 0.0;
  }

  for (c1_i55 = 0; c1_i55 < 3510; c1_i55++) {
    c1_d_a[c1_i55] = c1_c_a[c1_i55];
  }

  for (c1_i56 = 0; c1_i56 < 18; c1_i56++) {
    c1_d_b[c1_i56] = c1_c_b[c1_i56];
  }

  c1_c_eml_xgemm(chartInstance, c1_d_a, c1_d_b, c1_d_y);
  for (c1_i57 = 0; c1_i57 < 195; c1_i57++) {
    c1_b[c1_i57] = c1_d_y[c1_i57] + c1_b_s[c1_i57];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 30);
  for (c1_i58 = 0; c1_i58 < 468; c1_i58++) {
    c1_e_a[c1_i58] = c1_b_F[c1_i58];
  }

  for (c1_i59 = 0; c1_i59 < 18; c1_i59++) {
    c1_c_b[c1_i59] = c1_p[c1_i59];
  }

  c1_d_eml_scalar_eg(chartInstance);
  c1_d_eml_scalar_eg(chartInstance);
  for (c1_i60 = 0; c1_i60 < 26; c1_i60++) {
    c1_h[c1_i60] = 0.0;
  }

  for (c1_i61 = 0; c1_i61 < 26; c1_i61++) {
    c1_h[c1_i61] = 0.0;
  }

  for (c1_i62 = 0; c1_i62 < 26; c1_i62++) {
    c1_c_C[c1_i62] = c1_h[c1_i62];
  }

  for (c1_i63 = 0; c1_i63 < 26; c1_i63++) {
    c1_h[c1_i63] = c1_c_C[c1_i63];
  }

  c1_threshold(chartInstance);
  for (c1_i64 = 0; c1_i64 < 26; c1_i64++) {
    c1_c_C[c1_i64] = c1_h[c1_i64];
  }

  for (c1_i65 = 0; c1_i65 < 26; c1_i65++) {
    c1_h[c1_i65] = c1_c_C[c1_i65];
  }

  for (c1_i66 = 0; c1_i66 < 26; c1_i66++) {
    c1_h[c1_i66] = 0.0;
    c1_i67 = 0;
    for (c1_i68 = 0; c1_i68 < 18; c1_i68++) {
      c1_h[c1_i66] += c1_e_a[c1_i67 + c1_i66] * c1_c_b[c1_i68];
      c1_i67 += 26;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 32);
  for (c1_i69 = 0; c1_i69 < 676; c1_i69++) {
    c1_d_u[c1_i69] = c1_b_H[c1_i69];
  }

  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", c1_d_u, 0, 0U, 1U, 0U, 2, 26, 26),
                false);
  for (c1_i70 = 0; c1_i70 < 26; c1_i70++) {
    c1_e_u[c1_i70] = c1_h[c1_i70];
  }

  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", c1_e_u, 0, 0U, 1U, 0U, 1, 26), false);
  for (c1_i71 = 0; c1_i71 < 5070; c1_i71++) {
    chartInstance->c1_u[c1_i71] = -chartInstance->c1_G[c1_i71];
  }

  c1_g_y = NULL;
  sf_mex_assign(&c1_g_y, sf_mex_create("y", chartInstance->c1_u, 0, 0U, 1U, 0U,
    2, 195, 26), false);
  for (c1_i72 = 0; c1_i72 < 195; c1_i72++) {
    c1_f_u[c1_i72] = -c1_b[c1_i72];
  }

  c1_h_y = NULL;
  sf_mex_assign(&c1_h_y, sf_mex_create("y", c1_f_u, 0, 0U, 1U, 0U, 1, 195),
                false);
  c1_i_y = NULL;
  sf_mex_assign(&c1_i_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  c1_j_y = NULL;
  sf_mex_assign(&c1_j_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  c1_k_y = NULL;
  sf_mex_assign(&c1_k_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  c1_l_y = NULL;
  sf_mex_assign(&c1_l_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  c1_m_y = NULL;
  sf_mex_assign(&c1_m_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  c1_g_u = 1.0;
  c1_n_y = NULL;
  sf_mex_assign(&c1_n_y, sf_mex_create("y", &c1_g_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "wgsSolver", 3U, 10U, 14,
                    c1_e_y, 14, c1_f_y, 14, c1_g_y, 14, c1_h_y, 14, c1_i_y, 14,
                    c1_j_y, 14, c1_k_y, 14, c1_l_y, 14, c1_m_y, 14, c1_n_y,
                    &c1_b_zopt, &c1_c_time, &c1_unusedU1);
  c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_zopt), "zopt", c1_dv3);
  for (c1_i73 = 0; c1_i73 < 26; c1_i73++) {
    c1_zopt[c1_i73] = c1_dv3[c1_i73];
  }

  c1_b_time = c1_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_c_time), "time");
  sf_mex_assign(&c1_b_unusedU1, sf_mex_dup(c1_unusedU1), false);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 32);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 33);
  for (c1_i74 = 0; c1_i74 < 5070; c1_i74++) {
    c1_f_a[c1_i74] = chartInstance->c1_G[c1_i74];
  }

  for (c1_i75 = 0; c1_i75 < 26; c1_i75++) {
    c1_c_C[c1_i75] = c1_zopt[c1_i75];
  }

  c1_e_eml_scalar_eg(chartInstance);
  c1_e_eml_scalar_eg(chartInstance);
  for (c1_i76 = 0; c1_i76 < 195; c1_i76++) {
    c1_d_y[c1_i76] = 0.0;
  }

  for (c1_i77 = 0; c1_i77 < 5070; c1_i77++) {
    c1_g_a[c1_i77] = c1_f_a[c1_i77];
  }

  for (c1_i78 = 0; c1_i78 < 26; c1_i78++) {
    c1_d_C[c1_i78] = c1_c_C[c1_i78];
  }

  c1_d_eml_xgemm(chartInstance, c1_g_a, c1_d_C, c1_d_y);
  for (c1_i79 = 0; c1_i79 < 195; c1_i79++) {
    c1_b_feasRes[c1_i79] = c1_d_y[c1_i79] - c1_b[c1_i79];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 35);
  c1_nu = 5.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 36);
  for (c1_i80 = 0; c1_i80 < 5; c1_i80++) {
    c1_c_u[c1_i80] = c1_zopt[c1_i80] + c1_u0[c1_i80];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 38);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 40);
  for (c1_i81 = 0; c1_i81 < 49; c1_i81++) {
    c1_h_a[c1_i81] = c1_b_A[c1_i81];
  }

  for (c1_i82 = 0; c1_i82 < 7; c1_i82++) {
    c1_b_b[c1_i82] = c1_b_xkk1[c1_i82];
  }

  c1_f_eml_scalar_eg(chartInstance);
  c1_f_eml_scalar_eg(chartInstance);
  c1_threshold(chartInstance);
  for (c1_i83 = 0; c1_i83 < 7; c1_i83++) {
    c1_c_y[c1_i83] = 0.0;
    c1_i84 = 0;
    for (c1_i85 = 0; c1_i85 < 7; c1_i85++) {
      c1_c_y[c1_i83] += c1_h_a[c1_i84 + c1_i83] * c1_b_b[c1_i85];
      c1_i84 += 7;
    }
  }

  for (c1_i86 = 0; c1_i86 < 35; c1_i86++) {
    c1_i_a[c1_i86] = c1_b_B[c1_i86];
  }

  for (c1_i87 = 0; c1_i87 < 5; c1_i87++) {
    c1_e_b[c1_i87] = c1_c_u[c1_i87];
  }

  c1_g_eml_scalar_eg(chartInstance);
  c1_g_eml_scalar_eg(chartInstance);
  c1_threshold(chartInstance);
  for (c1_i88 = 0; c1_i88 < 7; c1_i88++) {
    c1_o_y[c1_i88] = 0.0;
    c1_i89 = 0;
    for (c1_i90 = 0; c1_i90 < 5; c1_i90++) {
      c1_o_y[c1_i88] += c1_i_a[c1_i89 + c1_i88] * c1_e_b[c1_i90];
      c1_i89 += 7;
    }
  }

  for (c1_i91 = 0; c1_i91 < 42; c1_i91++) {
    c1_a[c1_i91] = c1_b_C[c1_i91];
  }

  for (c1_i92 = 0; c1_i92 < 7; c1_i92++) {
    c1_b_b[c1_i92] = c1_b_xkk1[c1_i92];
  }

  c1_eml_scalar_eg(chartInstance);
  c1_eml_scalar_eg(chartInstance);
  c1_threshold(chartInstance);
  for (c1_i93 = 0; c1_i93 < 6; c1_i93++) {
    c1_b_y[c1_i93] = 0.0;
    c1_i94 = 0;
    for (c1_i95 = 0; c1_i95 < 7; c1_i95++) {
      c1_b_y[c1_i93] += c1_a[c1_i94 + c1_i93] * c1_b_b[c1_i95];
      c1_i94 += 6;
    }
  }

  for (c1_i96 = 0; c1_i96 < 42; c1_i96++) {
    c1_b_a[c1_i96] = c1_b_L[c1_i96];
  }

  for (c1_i97 = 0; c1_i97 < 6; c1_i97++) {
    c1_b_y[c1_i97] = c1_y[c1_i97] - c1_b_y[c1_i97];
  }

  c1_b_eml_scalar_eg(chartInstance);
  c1_b_eml_scalar_eg(chartInstance);
  c1_threshold(chartInstance);
  for (c1_i98 = 0; c1_i98 < 7; c1_i98++) {
    c1_b_b[c1_i98] = 0.0;
    c1_i99 = 0;
    for (c1_i100 = 0; c1_i100 < 6; c1_i100++) {
      c1_b_b[c1_i98] += c1_b_a[c1_i99 + c1_i98] * c1_b_y[c1_i100];
      c1_i99 += 7;
    }
  }

  for (c1_i101 = 0; c1_i101 < 7; c1_i101++) {
    c1_b_xk1k[c1_i101] = (c1_c_y[c1_i101] + c1_o_y[c1_i101]) + c1_b_b[c1_i101];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -40);
  _SFD_SYMBOL_SCOPE_POP();
  sf_mex_destroy(&c1_b_unusedU1);
  sf_mex_destroy(&c1_b_zopt);
  sf_mex_destroy(&c1_c_time);
  sf_mex_destroy(&c1_unusedU1);
  for (c1_i102 = 0; c1_i102 < 5; c1_i102++) {
    (*chartInstance->c1_b_u)[c1_i102] = c1_c_u[c1_i102];
  }

  for (c1_i103 = 0; c1_i103 < 195; c1_i103++) {
    (*chartInstance->c1_feasRes)[c1_i103] = c1_b_feasRes[c1_i103];
  }

  for (c1_i104 = 0; c1_i104 < 7; c1_i104++) {
    (*chartInstance->c1_xk1k)[c1_i104] = c1_b_xk1k[c1_i104];
  }

  *chartInstance->c1_time = c1_b_time;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void initSimStructsc1_mpc_tmpdemo_2014b
  (SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber)
{
  (void)c1_machineNumber;
  (void)c1_chartNumber;
  (void)c1_instanceNumber;
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_c_u;
  const mxArray *c1_y = NULL;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_c_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_time;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_b_time = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_time), &c1_thisId);
  sf_mex_destroy(&c1_b_time);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i105;
  real_T c1_b_inData[7];
  int32_T c1_i106;
  real_T c1_c_u[7];
  const mxArray *c1_y = NULL;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i105 = 0; c1_i105 < 7; c1_i105++) {
    c1_b_inData[c1_i105] = (*(real_T (*)[7])c1_inData)[c1_i105];
  }

  for (c1_i106 = 0; c1_i106 < 7; c1_i106++) {
    c1_c_u[c1_i106] = c1_b_inData[c1_i106];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 1, 7), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_b_xk1k, const char_T *c1_identifier, real_T
  c1_y[7])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_xk1k), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_b_xk1k);
}

static void c1_b_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[7])
{
  real_T c1_dv4[7];
  int32_T c1_i107;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_c_u), c1_dv4, 1, 0, 0U, 1, 0U, 1, 7);
  for (c1_i107 = 0; c1_i107 < 7; c1_i107++) {
    c1_y[c1_i107] = c1_dv4[c1_i107];
  }

  sf_mex_destroy(&c1_c_u);
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_xk1k;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[7];
  int32_T c1_i108;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_b_xk1k = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_xk1k), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_b_xk1k);
  for (c1_i108 = 0; c1_i108 < 7; c1_i108++) {
    (*(real_T (*)[7])c1_outData)[c1_i108] = c1_y[c1_i108];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i109;
  real_T c1_b_inData[195];
  int32_T c1_i110;
  real_T c1_c_u[195];
  const mxArray *c1_y = NULL;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i109 = 0; c1_i109 < 195; c1_i109++) {
    c1_b_inData[c1_i109] = (*(real_T (*)[195])c1_inData)[c1_i109];
  }

  for (c1_i110 = 0; c1_i110 < 195; c1_i110++) {
    c1_c_u[c1_i110] = c1_b_inData[c1_i110];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 1, 195), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_c_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_b_feasRes, const char_T *c1_identifier,
  real_T c1_y[195])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_feasRes), &c1_thisId,
                        c1_y);
  sf_mex_destroy(&c1_b_feasRes);
}

static void c1_d_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[195])
{
  real_T c1_dv5[195];
  int32_T c1_i111;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_c_u), c1_dv5, 1, 0, 0U, 1, 0U, 1, 195);
  for (c1_i111 = 0; c1_i111 < 195; c1_i111++) {
    c1_y[c1_i111] = c1_dv5[c1_i111];
  }

  sf_mex_destroy(&c1_c_u);
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_feasRes;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[195];
  int32_T c1_i112;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_b_feasRes = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_feasRes), &c1_thisId,
                        c1_y);
  sf_mex_destroy(&c1_b_feasRes);
  for (c1_i112 = 0; c1_i112 < 195; c1_i112++) {
    (*(real_T (*)[195])c1_outData)[c1_i112] = c1_y[c1_i112];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i113;
  real_T c1_b_inData[5];
  int32_T c1_i114;
  real_T c1_c_u[5];
  const mxArray *c1_y = NULL;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i113 = 0; c1_i113 < 5; c1_i113++) {
    c1_b_inData[c1_i113] = (*(real_T (*)[5])c1_inData)[c1_i113];
  }

  for (c1_i114 = 0; c1_i114 < 5; c1_i114++) {
    c1_c_u[c1_i114] = c1_b_inData[c1_i114];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 1, 5), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_e_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const char_T *c1_identifier, real_T
  c1_y[5])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_c_u), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_c_u);
}

static void c1_f_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[5])
{
  real_T c1_dv6[5];
  int32_T c1_i115;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_c_u), c1_dv6, 1, 0, 0U, 1, 0U, 1, 5);
  for (c1_i115 = 0; c1_i115 < 5; c1_i115++) {
    c1_y[c1_i115] = c1_dv6[c1_i115];
  }

  sf_mex_destroy(&c1_c_u);
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_c_u;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[5];
  int32_T c1_i116;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_c_u = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_c_u), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_c_u);
  for (c1_i116 = 0; c1_i116 < 5; c1_i116++) {
    (*(real_T (*)[5])c1_outData)[c1_i116] = c1_y[c1_i116];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i117;
  int32_T c1_i118;
  int32_T c1_i119;
  real_T c1_b_inData[42];
  int32_T c1_i120;
  int32_T c1_i121;
  int32_T c1_i122;
  real_T c1_c_u[42];
  const mxArray *c1_y = NULL;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i117 = 0;
  for (c1_i118 = 0; c1_i118 < 7; c1_i118++) {
    for (c1_i119 = 0; c1_i119 < 6; c1_i119++) {
      c1_b_inData[c1_i119 + c1_i117] = (*(real_T (*)[42])c1_inData)[c1_i119 +
        c1_i117];
    }

    c1_i117 += 6;
  }

  c1_i120 = 0;
  for (c1_i121 = 0; c1_i121 < 7; c1_i121++) {
    for (c1_i122 = 0; c1_i122 < 6; c1_i122++) {
      c1_c_u[c1_i122 + c1_i120] = c1_b_inData[c1_i122 + c1_i120];
    }

    c1_i120 += 6;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 2, 6, 7), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i123;
  int32_T c1_i124;
  int32_T c1_i125;
  real_T c1_b_inData[35];
  int32_T c1_i126;
  int32_T c1_i127;
  int32_T c1_i128;
  real_T c1_c_u[35];
  const mxArray *c1_y = NULL;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i123 = 0;
  for (c1_i124 = 0; c1_i124 < 5; c1_i124++) {
    for (c1_i125 = 0; c1_i125 < 7; c1_i125++) {
      c1_b_inData[c1_i125 + c1_i123] = (*(real_T (*)[35])c1_inData)[c1_i125 +
        c1_i123];
    }

    c1_i123 += 7;
  }

  c1_i126 = 0;
  for (c1_i127 = 0; c1_i127 < 5; c1_i127++) {
    for (c1_i128 = 0; c1_i128 < 7; c1_i128++) {
      c1_c_u[c1_i128 + c1_i126] = c1_b_inData[c1_i128 + c1_i126];
    }

    c1_i126 += 7;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 2, 7, 5), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i129;
  int32_T c1_i130;
  int32_T c1_i131;
  real_T c1_b_inData[49];
  int32_T c1_i132;
  int32_T c1_i133;
  int32_T c1_i134;
  real_T c1_c_u[49];
  const mxArray *c1_y = NULL;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i129 = 0;
  for (c1_i130 = 0; c1_i130 < 7; c1_i130++) {
    for (c1_i131 = 0; c1_i131 < 7; c1_i131++) {
      c1_b_inData[c1_i131 + c1_i129] = (*(real_T (*)[49])c1_inData)[c1_i131 +
        c1_i129];
    }

    c1_i129 += 7;
  }

  c1_i132 = 0;
  for (c1_i133 = 0; c1_i133 < 7; c1_i133++) {
    for (c1_i134 = 0; c1_i134 < 7; c1_i134++) {
      c1_c_u[c1_i134 + c1_i132] = c1_b_inData[c1_i134 + c1_i132];
    }

    c1_i132 += 7;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 2, 7, 7), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i135;
  int32_T c1_i136;
  int32_T c1_i137;
  real_T c1_b_inData[42];
  int32_T c1_i138;
  int32_T c1_i139;
  int32_T c1_i140;
  real_T c1_c_u[42];
  const mxArray *c1_y = NULL;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i135 = 0;
  for (c1_i136 = 0; c1_i136 < 6; c1_i136++) {
    for (c1_i137 = 0; c1_i137 < 7; c1_i137++) {
      c1_b_inData[c1_i137 + c1_i135] = (*(real_T (*)[42])c1_inData)[c1_i137 +
        c1_i135];
    }

    c1_i135 += 7;
  }

  c1_i138 = 0;
  for (c1_i139 = 0; c1_i139 < 6; c1_i139++) {
    for (c1_i140 = 0; c1_i140 < 7; c1_i140++) {
      c1_c_u[c1_i140 + c1_i138] = c1_b_inData[c1_i140 + c1_i138];
    }

    c1_i138 += 7;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 2, 7, 6), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_i_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i141;
  int32_T c1_i142;
  int32_T c1_i143;
  real_T c1_b_inData[3510];
  int32_T c1_i144;
  int32_T c1_i145;
  int32_T c1_i146;
  real_T c1_c_u[3510];
  const mxArray *c1_y = NULL;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i141 = 0;
  for (c1_i142 = 0; c1_i142 < 18; c1_i142++) {
    for (c1_i143 = 0; c1_i143 < 195; c1_i143++) {
      c1_b_inData[c1_i143 + c1_i141] = (*(real_T (*)[3510])c1_inData)[c1_i143 +
        c1_i141];
    }

    c1_i141 += 195;
  }

  c1_i144 = 0;
  for (c1_i145 = 0; c1_i145 < 18; c1_i145++) {
    for (c1_i146 = 0; c1_i146 < 195; c1_i146++) {
      c1_c_u[c1_i146 + c1_i144] = c1_b_inData[c1_i146 + c1_i144];
    }

    c1_i144 += 195;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 2, 195, 18),
                false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_j_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i147;
  int32_T c1_i148;
  int32_T c1_i149;
  real_T c1_b_inData[5070];
  int32_T c1_i150;
  int32_T c1_i151;
  int32_T c1_i152;
  real_T c1_c_u[5070];
  const mxArray *c1_y = NULL;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i147 = 0;
  for (c1_i148 = 0; c1_i148 < 26; c1_i148++) {
    for (c1_i149 = 0; c1_i149 < 195; c1_i149++) {
      c1_b_inData[c1_i149 + c1_i147] = (*(real_T (*)[5070])c1_inData)[c1_i149 +
        c1_i147];
    }

    c1_i147 += 195;
  }

  c1_i150 = 0;
  for (c1_i151 = 0; c1_i151 < 26; c1_i151++) {
    for (c1_i152 = 0; c1_i152 < 195; c1_i152++) {
      c1_c_u[c1_i152 + c1_i150] = c1_b_inData[c1_i152 + c1_i150];
    }

    c1_i150 += 195;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 2, 195, 26),
                false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_k_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i153;
  int32_T c1_i154;
  int32_T c1_i155;
  real_T c1_b_inData[468];
  int32_T c1_i156;
  int32_T c1_i157;
  int32_T c1_i158;
  real_T c1_c_u[468];
  const mxArray *c1_y = NULL;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i153 = 0;
  for (c1_i154 = 0; c1_i154 < 18; c1_i154++) {
    for (c1_i155 = 0; c1_i155 < 26; c1_i155++) {
      c1_b_inData[c1_i155 + c1_i153] = (*(real_T (*)[468])c1_inData)[c1_i155 +
        c1_i153];
    }

    c1_i153 += 26;
  }

  c1_i156 = 0;
  for (c1_i157 = 0; c1_i157 < 18; c1_i157++) {
    for (c1_i158 = 0; c1_i158 < 26; c1_i158++) {
      c1_c_u[c1_i158 + c1_i156] = c1_b_inData[c1_i158 + c1_i156];
    }

    c1_i156 += 26;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 2, 26, 18),
                false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_l_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i159;
  int32_T c1_i160;
  int32_T c1_i161;
  real_T c1_b_inData[676];
  int32_T c1_i162;
  int32_T c1_i163;
  int32_T c1_i164;
  real_T c1_c_u[676];
  const mxArray *c1_y = NULL;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i159 = 0;
  for (c1_i160 = 0; c1_i160 < 26; c1_i160++) {
    for (c1_i161 = 0; c1_i161 < 26; c1_i161++) {
      c1_b_inData[c1_i161 + c1_i159] = (*(real_T (*)[676])c1_inData)[c1_i161 +
        c1_i159];
    }

    c1_i159 += 26;
  }

  c1_i162 = 0;
  for (c1_i163 = 0; c1_i163 < 26; c1_i163++) {
    for (c1_i164 = 0; c1_i164 < 26; c1_i164++) {
      c1_c_u[c1_i164 + c1_i162] = c1_b_inData[c1_i164 + c1_i162];
    }

    c1_i162 += 26;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 2, 26, 26),
                false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_m_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i165;
  real_T c1_b_inData[17];
  int32_T c1_i166;
  real_T c1_c_u[17];
  const mxArray *c1_y = NULL;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i165 = 0; c1_i165 < 17; c1_i165++) {
    c1_b_inData[c1_i165] = (*(real_T (*)[17])c1_inData)[c1_i165];
  }

  for (c1_i166 = 0; c1_i166 < 17; c1_i166++) {
    c1_c_u[c1_i166] = c1_b_inData[c1_i166];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 1, 17), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_n_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i167;
  real_T c1_b_inData[26];
  int32_T c1_i168;
  real_T c1_c_u[26];
  const mxArray *c1_y = NULL;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i167 = 0; c1_i167 < 26; c1_i167++) {
    c1_b_inData[c1_i167] = (*(real_T (*)[26])c1_inData)[c1_i167];
  }

  for (c1_i168 = 0; c1_i168 < 26; c1_i168++) {
    c1_c_u[c1_i168] = c1_b_inData[c1_i168];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 1, 26), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_zopt;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[26];
  int32_T c1_i169;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_zopt = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_zopt), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_zopt);
  for (c1_i169 = 0; c1_i169 < 26; c1_i169++) {
    (*(real_T (*)[26])c1_outData)[c1_i169] = c1_y[c1_i169];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_o_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i170;
  real_T c1_b_inData[18];
  int32_T c1_i171;
  real_T c1_c_u[18];
  const mxArray *c1_y = NULL;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i170 = 0; c1_i170 < 18; c1_i170++) {
    c1_b_inData[c1_i170] = (*(real_T (*)[18])c1_inData)[c1_i170];
  }

  for (c1_i171 = 0; c1_i171 < 18; c1_i171++) {
    c1_c_u[c1_i171] = c1_b_inData[c1_i171];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 1, 18), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_g_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[18])
{
  real_T c1_dv7[18];
  int32_T c1_i172;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_c_u), c1_dv7, 1, 0, 0U, 1, 0U, 1, 18);
  for (c1_i172 = 0; c1_i172 < 18; c1_i172++) {
    c1_y[c1_i172] = c1_dv7[c1_i172];
  }

  sf_mex_destroy(&c1_c_u);
}

static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_p;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[18];
  int32_T c1_i173;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_p = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_p), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_p);
  for (c1_i173 = 0; c1_i173 < 18; c1_i173++) {
    (*(real_T (*)[18])c1_outData)[c1_i173] = c1_y[c1_i173];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_p_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i174;
  real_T c1_b_inData[6];
  int32_T c1_i175;
  real_T c1_c_u[6];
  const mxArray *c1_y = NULL;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i174 = 0; c1_i174 < 6; c1_i174++) {
    c1_b_inData[c1_i174] = (*(real_T (*)[6])c1_inData)[c1_i174];
  }

  for (c1_i175 = 0; c1_i175 < 6; c1_i175++) {
    c1_c_u[c1_i175] = c1_b_inData[c1_i175];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 1, 6), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_h_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[6])
{
  real_T c1_dv8[6];
  int32_T c1_i176;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_c_u), c1_dv8, 1, 0, 0U, 1, 0U, 1, 6);
  for (c1_i176 = 0; c1_i176 < 6; c1_i176++) {
    c1_y[c1_i176] = c1_dv8[c1_i176];
  }

  sf_mex_destroy(&c1_c_u);
}

static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_y;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_b_y[6];
  int32_T c1_i177;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_y = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_y), &c1_thisId, c1_b_y);
  sf_mex_destroy(&c1_y);
  for (c1_i177 = 0; c1_i177 < 6; c1_i177++) {
    (*(real_T (*)[6])c1_outData)[c1_i177] = c1_b_y[c1_i177];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_q_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  c1_sflJsObR9dsqNm7nhVXYguC c1_c_u;
  const mxArray *c1_y = NULL;
  int32_T c1_i178;
  char_T c1_d_u[21];
  const mxArray *c1_b_y = NULL;
  real_T c1_e_u;
  const mxArray *c1_c_y = NULL;
  real_T c1_f_u;
  const mxArray *c1_d_y = NULL;
  real_T c1_g_u;
  const mxArray *c1_e_y = NULL;
  real_T c1_h_u;
  const mxArray *c1_f_y = NULL;
  int32_T c1_i179;
  char_T c1_i_u[4];
  const mxArray *c1_g_y = NULL;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_c_u = *(c1_sflJsObR9dsqNm7nhVXYguC *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  for (c1_i178 = 0; c1_i178 < 21; c1_i178++) {
    c1_d_u[c1_i178] = c1_c_u.Algorithm[c1_i178];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_d_u, 10, 0U, 1U, 0U, 2, 1, 21),
                false);
  sf_mex_addfield(c1_y, c1_b_y, "Algorithm", "Algorithm", 0);
  c1_e_u = c1_c_u.MaxIter;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_c_y, "MaxIter", "MaxIter", 0);
  c1_f_u = c1_c_u.TolCon;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_f_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_d_y, "TolCon", "TolCon", 0);
  c1_g_u = c1_c_u.TolFun;
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_g_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_e_y, "TolFun", "TolFun", 0);
  c1_h_u = c1_c_u.TolX;
  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_h_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_f_y, "TolX", "TolX", 0);
  for (c1_i179 = 0; c1_i179 < 4; c1_i179++) {
    c1_i_u[c1_i179] = c1_c_u.Display[c1_i179];
  }

  c1_g_y = NULL;
  sf_mex_assign(&c1_g_y, sf_mex_create("y", c1_i_u, 10, 0U, 1U, 0U, 2, 1, 4),
                false);
  sf_mex_addfield(c1_y, c1_g_y, "Display", "Display", 0);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static c1_sflJsObR9dsqNm7nhVXYguC c1_i_emlrt_marshallIn
  (SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance, const mxArray *c1_c_u,
   const emlrtMsgIdentifier *c1_parentId)
{
  c1_sflJsObR9dsqNm7nhVXYguC c1_y;
  emlrtMsgIdentifier c1_thisId;
  static const char * c1_fieldNames[6] = { "Algorithm", "MaxIter", "TolCon",
    "TolFun", "TolX", "Display" };

  c1_thisId.fParent = c1_parentId;
  sf_mex_check_struct(c1_parentId, c1_c_u, 6, c1_fieldNames, 0U, NULL);
  c1_thisId.fIdentifier = "Algorithm";
  c1_j_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_c_u,
    "Algorithm", "Algorithm", 0)), &c1_thisId, c1_y.Algorithm);
  c1_thisId.fIdentifier = "MaxIter";
  c1_y.MaxIter = c1_o_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
                                        (c1_c_u, "MaxIter", "MaxIter", 0)),
    &c1_thisId);
  c1_thisId.fIdentifier = "TolCon";
  c1_y.TolCon = c1_o_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_c_u, "TolCon", "TolCon", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "TolFun";
  c1_y.TolFun = c1_o_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_c_u, "TolFun", "TolFun", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "TolX";
  c1_y.TolX = c1_o_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_c_u, "TolX", "TolX", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "Display";
  c1_k_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_c_u,
    "Display", "Display", 0)), &c1_thisId, c1_y.Display);
  sf_mex_destroy(&c1_c_u);
  return c1_y;
}

static void c1_j_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId,
  char_T c1_y[21])
{
  char_T c1_cv2[21];
  int32_T c1_i180;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_c_u), c1_cv2, 1, 10, 0U, 1, 0U, 2, 1,
                21);
  for (c1_i180 = 0; c1_i180 < 21; c1_i180++) {
    c1_y[c1_i180] = c1_cv2[c1_i180];
  }

  sf_mex_destroy(&c1_c_u);
}

static void c1_k_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId,
  char_T c1_y[4])
{
  char_T c1_cv3[4];
  int32_T c1_i181;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_c_u), c1_cv3, 1, 10, 0U, 1, 0U, 2, 1,
                4);
  for (c1_i181 = 0; c1_i181 < 4; c1_i181++) {
    c1_y[c1_i181] = c1_cv3[c1_i181];
  }

  sf_mex_destroy(&c1_c_u);
}

static void c1_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_options;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  c1_sflJsObR9dsqNm7nhVXYguC c1_y;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_options = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_options), &c1_thisId);
  sf_mex_destroy(&c1_options);
  *(c1_sflJsObR9dsqNm7nhVXYguC *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_mpc_tmpdemo_2014b_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  sf_mex_assign(&c1_nameCaptureInfo, sf_mex_createstruct("structure", 2, 17, 1),
                false);
  c1_info_helper(&c1_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c1_nameCaptureInfo);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(const mxArray **c1_info)
{
  const mxArray *c1_rhs0 = NULL;
  const mxArray *c1_lhs0 = NULL;
  const mxArray *c1_rhs1 = NULL;
  const mxArray *c1_lhs1 = NULL;
  const mxArray *c1_rhs2 = NULL;
  const mxArray *c1_lhs2 = NULL;
  const mxArray *c1_rhs3 = NULL;
  const mxArray *c1_lhs3 = NULL;
  const mxArray *c1_rhs4 = NULL;
  const mxArray *c1_lhs4 = NULL;
  const mxArray *c1_rhs5 = NULL;
  const mxArray *c1_lhs5 = NULL;
  const mxArray *c1_rhs6 = NULL;
  const mxArray *c1_lhs6 = NULL;
  const mxArray *c1_rhs7 = NULL;
  const mxArray *c1_lhs7 = NULL;
  const mxArray *c1_rhs8 = NULL;
  const mxArray *c1_lhs8 = NULL;
  const mxArray *c1_rhs9 = NULL;
  const mxArray *c1_lhs9 = NULL;
  const mxArray *c1_rhs10 = NULL;
  const mxArray *c1_lhs10 = NULL;
  const mxArray *c1_rhs11 = NULL;
  const mxArray *c1_lhs11 = NULL;
  const mxArray *c1_rhs12 = NULL;
  const mxArray *c1_lhs12 = NULL;
  const mxArray *c1_rhs13 = NULL;
  const mxArray *c1_lhs13 = NULL;
  const mxArray *c1_rhs14 = NULL;
  const mxArray *c1_lhs14 = NULL;
  const mxArray *c1_rhs15 = NULL;
  const mxArray *c1_lhs15 = NULL;
  const mxArray *c1_rhs16 = NULL;
  const mxArray *c1_lhs16 = NULL;
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1383852094U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c1_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1395906656U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c1_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323145378U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c1_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 3);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 3);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375959088U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c1_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 4);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c1_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 5);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_xgemm"), "name", "name", 5);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1375959090U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c1_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 6);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c1_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.xgemm"),
                  "name", "name", 7);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c1_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 8);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 8);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c1_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!below_threshold"),
                  "context", "context", 9);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 9);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c1_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "context", "context", 10);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 10);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1393305658U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c1_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 11);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 11);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c1_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 12);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.refblas.xgemm"),
                  "name", "name", 12);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c1_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 13);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.int"),
                  "name", "name", 13);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/int.p"),
                  "resolved", "resolved", 13);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c1_rhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs13, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!ceval_xgemm"),
                  "context", "context", 14);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.blas.size_ptr"),
                  "name", "name", 14);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/size_ptr.p"),
                  "resolved", "resolved", 14);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c1_rhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs14, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!ceval_xgemm"),
                  "context", "context", 15);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.c_cast"),
                  "name", "name", 15);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("int32"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/c_cast.p"),
                  "resolved", "resolved", 15);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c1_rhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs15, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "context", "context", 16);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("length"), "name", "name", 16);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 16);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1303124606U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c1_rhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c1_lhs16, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs16), "lhs", "lhs",
                  16);
  sf_mex_destroy(&c1_rhs0);
  sf_mex_destroy(&c1_lhs0);
  sf_mex_destroy(&c1_rhs1);
  sf_mex_destroy(&c1_lhs1);
  sf_mex_destroy(&c1_rhs2);
  sf_mex_destroy(&c1_lhs2);
  sf_mex_destroy(&c1_rhs3);
  sf_mex_destroy(&c1_lhs3);
  sf_mex_destroy(&c1_rhs4);
  sf_mex_destroy(&c1_lhs4);
  sf_mex_destroy(&c1_rhs5);
  sf_mex_destroy(&c1_lhs5);
  sf_mex_destroy(&c1_rhs6);
  sf_mex_destroy(&c1_lhs6);
  sf_mex_destroy(&c1_rhs7);
  sf_mex_destroy(&c1_lhs7);
  sf_mex_destroy(&c1_rhs8);
  sf_mex_destroy(&c1_lhs8);
  sf_mex_destroy(&c1_rhs9);
  sf_mex_destroy(&c1_lhs9);
  sf_mex_destroy(&c1_rhs10);
  sf_mex_destroy(&c1_lhs10);
  sf_mex_destroy(&c1_rhs11);
  sf_mex_destroy(&c1_lhs11);
  sf_mex_destroy(&c1_rhs12);
  sf_mex_destroy(&c1_lhs12);
  sf_mex_destroy(&c1_rhs13);
  sf_mex_destroy(&c1_lhs13);
  sf_mex_destroy(&c1_rhs14);
  sf_mex_destroy(&c1_lhs14);
  sf_mex_destroy(&c1_rhs15);
  sf_mex_destroy(&c1_lhs15);
  sf_mex_destroy(&c1_rhs16);
  sf_mex_destroy(&c1_lhs16);
}

static const mxArray *c1_emlrt_marshallOut(const char * c1_c_u)
{
  const mxArray *c1_y = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_c_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c1_c_u)), false);
  return c1_y;
}

static const mxArray *c1_b_emlrt_marshallOut(const uint32_T c1_c_u)
{
  const mxArray *c1_y = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_c_u, 7, 0U, 0U, 0U, 0), false);
  return c1_y;
}

static void c1_eml_scalar_eg(SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_threshold(SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_b_eml_scalar_eg(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c1_c_eml_scalar_eg(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c1_eml_xgemm(SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance,
  real_T c1_b_A[3510], real_T c1_b_B[18], real_T c1_b_C[195], real_T c1_c_C[195])
{
  int32_T c1_i182;
  int32_T c1_i183;
  real_T c1_c_A[3510];
  int32_T c1_i184;
  real_T c1_c_B[18];
  for (c1_i182 = 0; c1_i182 < 195; c1_i182++) {
    c1_c_C[c1_i182] = c1_b_C[c1_i182];
  }

  for (c1_i183 = 0; c1_i183 < 3510; c1_i183++) {
    c1_c_A[c1_i183] = c1_b_A[c1_i183];
  }

  for (c1_i184 = 0; c1_i184 < 18; c1_i184++) {
    c1_c_B[c1_i184] = c1_b_B[c1_i184];
  }

  c1_c_eml_xgemm(chartInstance, c1_c_A, c1_c_B, c1_c_C);
}

static void c1_d_eml_scalar_eg(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c1_e_eml_scalar_eg(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c1_b_eml_xgemm(SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance,
  real_T c1_b_A[5070], real_T c1_b_B[26], real_T c1_b_C[195], real_T c1_c_C[195])
{
  int32_T c1_i185;
  int32_T c1_i186;
  real_T c1_c_A[5070];
  int32_T c1_i187;
  real_T c1_c_B[26];
  for (c1_i185 = 0; c1_i185 < 195; c1_i185++) {
    c1_c_C[c1_i185] = c1_b_C[c1_i185];
  }

  for (c1_i186 = 0; c1_i186 < 5070; c1_i186++) {
    c1_c_A[c1_i186] = c1_b_A[c1_i186];
  }

  for (c1_i187 = 0; c1_i187 < 26; c1_i187++) {
    c1_c_B[c1_i187] = c1_b_B[c1_i187];
  }

  c1_d_eml_xgemm(chartInstance, c1_c_A, c1_c_B, c1_c_C);
}

static void c1_f_eml_scalar_eg(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c1_g_eml_scalar_eg(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c1_l_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_zopt, const char_T *c1_identifier, real_T
  c1_y[26])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_zopt), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_zopt);
}

static void c1_m_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId,
  real_T c1_y[26])
{
  real_T c1_dv9[26];
  int32_T c1_i188;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_c_u), c1_dv9, 1, 0, 0U, 1, 0U, 1, 26);
  for (c1_i188 = 0; c1_i188 < 26; c1_i188++) {
    c1_y[c1_i188] = c1_dv9[c1_i188];
  }

  sf_mex_destroy(&c1_c_u);
}

static real_T c1_n_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_b_time, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_time), &c1_thisId);
  sf_mex_destroy(&c1_b_time);
  return c1_y;
}

static real_T c1_o_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_c_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_c_u);
  return c1_y;
}

static const mxArray *c1_r_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_c_u;
  const mxArray *c1_y = NULL;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_c_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_c_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static int32_T c1_p_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i189;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_c_u), &c1_i189, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i189;
  sf_mex_destroy(&c1_c_u);
  return c1_y;
}

static void c1_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_q_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_mpc_tmpdemo_2014b, const
  char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_r_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_mpc_tmpdemo_2014b), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_mpc_tmpdemo_2014b);
  return c1_y;
}

static uint8_T c1_r_emlrt_marshallIn(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance, const mxArray *c1_c_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_c_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_c_u);
  return c1_y;
}

static void c1_c_eml_xgemm(SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance,
  real_T c1_b_A[3510], real_T c1_b_B[18], real_T c1_b_C[195])
{
  real_T c1_alpha1;
  real_T c1_beta1;
  char_T c1_TRANSB;
  char_T c1_TRANSA;
  ptrdiff_t c1_m_t;
  ptrdiff_t c1_n_t;
  ptrdiff_t c1_k_t;
  ptrdiff_t c1_lda_t;
  ptrdiff_t c1_ldb_t;
  ptrdiff_t c1_ldc_t;
  double * c1_alpha1_t;
  double * c1_Aia0_t;
  double * c1_Bib0_t;
  double * c1_beta1_t;
  double * c1_Cic0_t;
  c1_threshold(chartInstance);
  c1_alpha1 = 1.0;
  c1_beta1 = 0.0;
  c1_TRANSB = 'N';
  c1_TRANSA = 'N';
  c1_m_t = (ptrdiff_t)(195);
  c1_n_t = (ptrdiff_t)(1);
  c1_k_t = (ptrdiff_t)(18);
  c1_lda_t = (ptrdiff_t)(195);
  c1_ldb_t = (ptrdiff_t)(18);
  c1_ldc_t = (ptrdiff_t)(195);
  c1_alpha1_t = (double *)(&c1_alpha1);
  c1_Aia0_t = (double *)(&c1_b_A[0]);
  c1_Bib0_t = (double *)(&c1_b_B[0]);
  c1_beta1_t = (double *)(&c1_beta1);
  c1_Cic0_t = (double *)(&c1_b_C[0]);
  dgemm(&c1_TRANSA, &c1_TRANSB, &c1_m_t, &c1_n_t, &c1_k_t, c1_alpha1_t,
        c1_Aia0_t, &c1_lda_t, c1_Bib0_t, &c1_ldb_t, c1_beta1_t, c1_Cic0_t,
        &c1_ldc_t);
}

static void c1_d_eml_xgemm(SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance,
  real_T c1_b_A[5070], real_T c1_b_B[26], real_T c1_b_C[195])
{
  real_T c1_alpha1;
  real_T c1_beta1;
  char_T c1_TRANSB;
  char_T c1_TRANSA;
  ptrdiff_t c1_m_t;
  ptrdiff_t c1_n_t;
  ptrdiff_t c1_k_t;
  ptrdiff_t c1_lda_t;
  ptrdiff_t c1_ldb_t;
  ptrdiff_t c1_ldc_t;
  double * c1_alpha1_t;
  double * c1_Aia0_t;
  double * c1_Bib0_t;
  double * c1_beta1_t;
  double * c1_Cic0_t;
  c1_threshold(chartInstance);
  c1_alpha1 = 1.0;
  c1_beta1 = 0.0;
  c1_TRANSB = 'N';
  c1_TRANSA = 'N';
  c1_m_t = (ptrdiff_t)(195);
  c1_n_t = (ptrdiff_t)(1);
  c1_k_t = (ptrdiff_t)(26);
  c1_lda_t = (ptrdiff_t)(195);
  c1_ldb_t = (ptrdiff_t)(26);
  c1_ldc_t = (ptrdiff_t)(195);
  c1_alpha1_t = (double *)(&c1_alpha1);
  c1_Aia0_t = (double *)(&c1_b_A[0]);
  c1_Bib0_t = (double *)(&c1_b_B[0]);
  c1_beta1_t = (double *)(&c1_beta1);
  c1_Cic0_t = (double *)(&c1_b_C[0]);
  dgemm(&c1_TRANSA, &c1_TRANSB, &c1_m_t, &c1_n_t, &c1_k_t, c1_alpha1_t,
        c1_Aia0_t, &c1_lda_t, c1_Bib0_t, &c1_ldb_t, c1_beta1_t, c1_Cic0_t,
        &c1_ldc_t);
}

static void init_dsm_address_info(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc1_mpc_tmpdemo_2014bInstanceStruct
  *chartInstance)
{
  chartInstance->c1_f = (real_T (*)[17])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c1_H = (real_T (*)[676])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c1_F = (real_T (*)[468])ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c1_b_G = (real_T (*)[5070])ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c1_S = (real_T (*)[3510])ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c1_s = (real_T (*)[195])ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c1_b_u = (real_T (*)[5])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c1_feasRes = (real_T (*)[195])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c1_M = (real_T (*)[42])ssGetInputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c1_L = (real_T (*)[42])ssGetInputPortSignal_wrapper
    (chartInstance->S, 7);
  chartInstance->c1_xk1k = (real_T (*)[7])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c1_A = (real_T (*)[49])ssGetInputPortSignal_wrapper
    (chartInstance->S, 8);
  chartInstance->c1_B = (real_T (*)[35])ssGetInputPortSignal_wrapper
    (chartInstance->S, 9);
  chartInstance->c1_C = (real_T (*)[42])ssGetInputPortSignal_wrapper
    (chartInstance->S, 10);
  chartInstance->c1_xkk1 = (real_T (*)[7])ssGetInputPortSignal_wrapper
    (chartInstance->S, 11);
  chartInstance->c1_time = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 4);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c1_mpc_tmpdemo_2014b_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(49607659U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(855502067U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1335185631U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3182528764U);
}

mxArray* sf_c1_mpc_tmpdemo_2014b_get_post_codegen_info(void);
mxArray *sf_c1_mpc_tmpdemo_2014b_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("NUepuk52MScRP8gEI9k8NF");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,12,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(17);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(26);
      pr[1] = (double)(26);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(26);
      pr[1] = (double)(18);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(195);
      pr[1] = (double)(26);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(195);
      pr[1] = (double)(18);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(195);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(7);
      pr[1] = (double)(6);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(7);
      pr[1] = (double)(6);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(7);
      pr[1] = (double)(7);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(7);
      pr[1] = (double)(5);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(7);
      mxSetField(mxData,10,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(7);
      pr[1] = (double)(1);
      mxSetField(mxData,11,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,11,"type",mxType);
    }

    mxSetField(mxData,11,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(5);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(195);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(7);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c1_mpc_tmpdemo_2014b_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_mpc_tmpdemo_2014b_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c1_mpc_tmpdemo_2014b_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "incompatibleSymbol", };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 3, infoFields);
  mxArray *fallbackReason = mxCreateString("feature_off");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxArray *fallbackType = mxCreateString("early");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c1_mpc_tmpdemo_2014b_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c1_mpc_tmpdemo_2014b_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c1_mpc_tmpdemo_2014b(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[13],T\"feasRes\",},{M[1],M[23],T\"time\",},{M[1],M[12],T\"u\",},{M[1],M[16],T\"xk1k\",},{M[8],M[0],T\"is_active_c1_mpc_tmpdemo_2014b\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_mpc_tmpdemo_2014b_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)
      chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _mpc_tmpdemo_2014bMachineNumber_,
           1,
           1,
           1,
           0,
           16,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_mpc_tmpdemo_2014bMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_mpc_tmpdemo_2014bMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _mpc_tmpdemo_2014bMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"f");
          _SFD_SET_DATA_PROPS(1,1,1,0,"H");
          _SFD_SET_DATA_PROPS(2,1,1,0,"F");
          _SFD_SET_DATA_PROPS(3,1,1,0,"G");
          _SFD_SET_DATA_PROPS(4,1,1,0,"S");
          _SFD_SET_DATA_PROPS(5,1,1,0,"s");
          _SFD_SET_DATA_PROPS(6,2,0,1,"u");
          _SFD_SET_DATA_PROPS(7,2,0,1,"feasRes");
          _SFD_SET_DATA_PROPS(8,1,1,0,"M");
          _SFD_SET_DATA_PROPS(9,1,1,0,"L");
          _SFD_SET_DATA_PROPS(10,2,0,1,"xk1k");
          _SFD_SET_DATA_PROPS(11,1,1,0,"A");
          _SFD_SET_DATA_PROPS(12,1,1,0,"B");
          _SFD_SET_DATA_PROPS(13,1,1,0,"C");
          _SFD_SET_DATA_PROPS(14,1,1,0,"xkk1");
          _SFD_SET_DATA_PROPS(15,2,0,1,"time");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",62,-1,862);

        {
          unsigned int dimVector[1];
          dimVector[0]= 17;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_m_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 26;
          dimVector[1]= 26;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_l_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 26;
          dimVector[1]= 18;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_k_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 195;
          dimVector[1]= 26;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_j_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 195;
          dimVector[1]= 18;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_i_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 195;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)
            c1_d_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 195;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)
            c1_c_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 7;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_h_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 7;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_h_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 7;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)
            c1_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 7;
          dimVector[1]= 7;
          _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_g_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 7;
          dimVector[1]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 7;
          _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 7;
          _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(15,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_VALUE_PTR(0U, *chartInstance->c1_f);
        _SFD_SET_DATA_VALUE_PTR(1U, *chartInstance->c1_H);
        _SFD_SET_DATA_VALUE_PTR(2U, *chartInstance->c1_F);
        _SFD_SET_DATA_VALUE_PTR(3U, *chartInstance->c1_b_G);
        _SFD_SET_DATA_VALUE_PTR(4U, *chartInstance->c1_S);
        _SFD_SET_DATA_VALUE_PTR(5U, *chartInstance->c1_s);
        _SFD_SET_DATA_VALUE_PTR(6U, *chartInstance->c1_b_u);
        _SFD_SET_DATA_VALUE_PTR(7U, *chartInstance->c1_feasRes);
        _SFD_SET_DATA_VALUE_PTR(8U, *chartInstance->c1_M);
        _SFD_SET_DATA_VALUE_PTR(9U, *chartInstance->c1_L);
        _SFD_SET_DATA_VALUE_PTR(10U, *chartInstance->c1_xk1k);
        _SFD_SET_DATA_VALUE_PTR(11U, *chartInstance->c1_A);
        _SFD_SET_DATA_VALUE_PTR(12U, *chartInstance->c1_B);
        _SFD_SET_DATA_VALUE_PTR(13U, *chartInstance->c1_C);
        _SFD_SET_DATA_VALUE_PTR(14U, *chartInstance->c1_xkk1);
        _SFD_SET_DATA_VALUE_PTR(15U, chartInstance->c1_time);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _mpc_tmpdemo_2014bMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "a5a3918WR7a2vz2o9EeUX";
}

static void sf_opaque_initialize_c1_mpc_tmpdemo_2014b(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_mpc_tmpdemo_2014bInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c1_mpc_tmpdemo_2014b((SFc1_mpc_tmpdemo_2014bInstanceStruct*)
    chartInstanceVar);
  initialize_c1_mpc_tmpdemo_2014b((SFc1_mpc_tmpdemo_2014bInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c1_mpc_tmpdemo_2014b(void *chartInstanceVar)
{
  enable_c1_mpc_tmpdemo_2014b((SFc1_mpc_tmpdemo_2014bInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c1_mpc_tmpdemo_2014b(void *chartInstanceVar)
{
  disable_c1_mpc_tmpdemo_2014b((SFc1_mpc_tmpdemo_2014bInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c1_mpc_tmpdemo_2014b(void *chartInstanceVar)
{
  sf_gateway_c1_mpc_tmpdemo_2014b((SFc1_mpc_tmpdemo_2014bInstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c1_mpc_tmpdemo_2014b(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c1_mpc_tmpdemo_2014b
    ((SFc1_mpc_tmpdemo_2014bInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
}

static void sf_opaque_set_sim_state_c1_mpc_tmpdemo_2014b(SimStruct* S, const
  mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c1_mpc_tmpdemo_2014b((SFc1_mpc_tmpdemo_2014bInstanceStruct*)
    chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c1_mpc_tmpdemo_2014b(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_mpc_tmpdemo_2014bInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_mpc_tmpdemo_2014b_optimization_info();
    }

    finalize_c1_mpc_tmpdemo_2014b((SFc1_mpc_tmpdemo_2014bInstanceStruct*)
      chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_mpc_tmpdemo_2014b((SFc1_mpc_tmpdemo_2014bInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_mpc_tmpdemo_2014b(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c1_mpc_tmpdemo_2014b((SFc1_mpc_tmpdemo_2014bInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_mpc_tmpdemo_2014b(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_mpc_tmpdemo_2014b_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,1,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,1);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 8, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 9, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 10, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 11, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,12);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,4);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=4; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 12; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3127816328U));
  ssSetChecksum1(S,(973667461U));
  ssSetChecksum2(S,(754788033U));
  ssSetChecksum3(S,(2577039607U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_mpc_tmpdemo_2014b(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_mpc_tmpdemo_2014b(SimStruct *S)
{
  SFc1_mpc_tmpdemo_2014bInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc1_mpc_tmpdemo_2014bInstanceStruct *)utMalloc(sizeof
    (SFc1_mpc_tmpdemo_2014bInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_mpc_tmpdemo_2014bInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c1_mpc_tmpdemo_2014b;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c1_mpc_tmpdemo_2014b;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c1_mpc_tmpdemo_2014b;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_mpc_tmpdemo_2014b;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_mpc_tmpdemo_2014b;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c1_mpc_tmpdemo_2014b;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c1_mpc_tmpdemo_2014b;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c1_mpc_tmpdemo_2014b;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_mpc_tmpdemo_2014b;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_mpc_tmpdemo_2014b;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c1_mpc_tmpdemo_2014b;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->checksum = SF_RUNTIME_INFO_CHECKSUM;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  crtInfo->compiledInfo = NULL;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c1_mpc_tmpdemo_2014b_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_mpc_tmpdemo_2014b(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_mpc_tmpdemo_2014b(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_mpc_tmpdemo_2014b(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_mpc_tmpdemo_2014b_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
