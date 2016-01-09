/* Include files */

#include <stddef.h>
#include "blas.h"
#include "mpc_aircraft_sfun.h"
#include "c1_mpc_aircraft.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "mpc_aircraft_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c1_debug_family_names[29] = { "options", "zopt", "nu", "ny",
  "u0", "y", "xkk", "p", "b", "h", "nargin", "nargout", "f", "H", "F", "G", "S",
  "s", "M", "L", "A", "B", "C", "xkk1", "u", "feasRes", "xk1k", "time", "iter" };

/* Function Declarations */
static void initialize_c1_mpc_aircraft(SFc1_mpc_aircraftInstanceStruct
  *chartInstance);
static void initialize_params_c1_mpc_aircraft(SFc1_mpc_aircraftInstanceStruct
  *chartInstance);
static void enable_c1_mpc_aircraft(SFc1_mpc_aircraftInstanceStruct
  *chartInstance);
static void disable_c1_mpc_aircraft(SFc1_mpc_aircraftInstanceStruct
  *chartInstance);
static void c1_update_debugger_state_c1_mpc_aircraft
  (SFc1_mpc_aircraftInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c1_mpc_aircraft
  (SFc1_mpc_aircraftInstanceStruct *chartInstance);
static void set_sim_state_c1_mpc_aircraft(SFc1_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c1_st);
static void finalize_c1_mpc_aircraft(SFc1_mpc_aircraftInstanceStruct
  *chartInstance);
static void sf_gateway_c1_mpc_aircraft(SFc1_mpc_aircraftInstanceStruct
  *chartInstance);
static void mdl_start_c1_mpc_aircraft(SFc1_mpc_aircraftInstanceStruct
  *chartInstance);
static void c1_chartstep_c1_mpc_aircraft(SFc1_mpc_aircraftInstanceStruct
  *chartInstance);
static void initSimStructsc1_mpc_aircraft(SFc1_mpc_aircraftInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_b_xk1k, const char_T *c1_identifier, real_T c1_y[6]);
static void c1_b_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[6]);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_c_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_b_feasRes, const char_T *c1_identifier, real_T c1_y[12]);
static void c1_d_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[12]);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_e_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const char_T *c1_identifier, real_T c1_y[2]);
static void c1_f_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[2]);
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
static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_m_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_g_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[10]);
static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_n_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static c1_sflJsObR9dsqNm7nhVXYguC c1_h_emlrt_marshallIn
  (SFc1_mpc_aircraftInstanceStruct *chartInstance, const mxArray *c1_b_u, const
   emlrtMsgIdentifier *c1_parentId);
static void c1_i_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId, char_T c1_y[21]);
static void c1_j_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId, char_T c1_y[4]);
static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_eml_scalar_eg(SFc1_mpc_aircraftInstanceStruct *chartInstance);
static void c1_threshold(SFc1_mpc_aircraftInstanceStruct *chartInstance);
static void c1_b_eml_scalar_eg(SFc1_mpc_aircraftInstanceStruct *chartInstance);
static void c1_c_eml_scalar_eg(SFc1_mpc_aircraftInstanceStruct *chartInstance);
static void c1_d_eml_scalar_eg(SFc1_mpc_aircraftInstanceStruct *chartInstance);
static void c1_e_eml_scalar_eg(SFc1_mpc_aircraftInstanceStruct *chartInstance);
static void c1_f_eml_scalar_eg(SFc1_mpc_aircraftInstanceStruct *chartInstance);
static void c1_k_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_zopt, const char_T *c1_identifier, real_T c1_y[5]);
static void c1_l_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[5]);
static real_T c1_m_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c1_b_time, const char_T *c1_identifier);
static real_T c1_n_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId);
static const mxArray *c1_o_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_o_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_p_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_mpc_aircraft, const char_T
  *c1_identifier);
static uint8_T c1_q_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_mpc_aircraftInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc1_mpc_aircraftInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c1_mpc_aircraft(SFc1_mpc_aircraftInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc1_mpc_aircraft(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c1_is_active_c1_mpc_aircraft = 0U;
}

static void initialize_params_c1_mpc_aircraft(SFc1_mpc_aircraftInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c1_mpc_aircraft(SFc1_mpc_aircraftInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c1_mpc_aircraft(SFc1_mpc_aircraftInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c1_update_debugger_state_c1_mpc_aircraft
  (SFc1_mpc_aircraftInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c1_mpc_aircraft
  (SFc1_mpc_aircraftInstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  const mxArray *c1_b_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  real_T c1_b_hoistedGlobal;
  real_T c1_c_u;
  const mxArray *c1_d_y = NULL;
  const mxArray *c1_e_y = NULL;
  const mxArray *c1_f_y = NULL;
  uint8_T c1_c_hoistedGlobal;
  uint8_T c1_d_u;
  const mxArray *c1_g_y = NULL;
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellmatrix(6, 1), false);
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", *chartInstance->c1_feasRes, 0, 0U,
    1U, 0U, 1, 12), false);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_hoistedGlobal = *chartInstance->c1_iter;
  c1_b_u = c1_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_b_hoistedGlobal = *chartInstance->c1_time;
  c1_c_u = c1_b_hoistedGlobal;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", *chartInstance->c1_u, 0, 0U, 1U, 0U,
    1, 2), false);
  sf_mex_setcell(c1_y, 3, c1_e_y);
  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", *chartInstance->c1_xk1k, 0, 0U, 1U,
    0U, 1, 6), false);
  sf_mex_setcell(c1_y, 4, c1_f_y);
  c1_c_hoistedGlobal = chartInstance->c1_is_active_c1_mpc_aircraft;
  c1_d_u = c1_c_hoistedGlobal;
  c1_g_y = NULL;
  sf_mex_assign(&c1_g_y, sf_mex_create("y", &c1_d_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 5, c1_g_y);
  sf_mex_assign(&c1_st, c1_y, false);
  return c1_st;
}

static void set_sim_state_c1_mpc_aircraft(SFc1_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c1_st)
{
  const mxArray *c1_b_u;
  real_T c1_dv0[12];
  int32_T c1_i0;
  real_T c1_dv1[2];
  int32_T c1_i1;
  real_T c1_dv2[6];
  int32_T c1_i2;
  chartInstance->c1_doneDoubleBufferReInit = true;
  c1_b_u = sf_mex_dup(c1_st);
  c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("feasRes",
    c1_b_u, 0)), "feasRes", c1_dv0);
  for (c1_i0 = 0; c1_i0 < 12; c1_i0++) {
    (*chartInstance->c1_feasRes)[c1_i0] = c1_dv0[c1_i0];
  }

  *chartInstance->c1_iter = c1_m_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("iter", c1_b_u, 1)), "iter");
  *chartInstance->c1_time = c1_m_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("time", c1_b_u, 2)), "time");
  c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("u", c1_b_u, 3)),
                        "u", c1_dv1);
  for (c1_i1 = 0; c1_i1 < 2; c1_i1++) {
    (*chartInstance->c1_u)[c1_i1] = c1_dv1[c1_i1];
  }

  c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("xk1k", c1_b_u, 4)),
                      "xk1k", c1_dv2);
  for (c1_i2 = 0; c1_i2 < 6; c1_i2++) {
    (*chartInstance->c1_xk1k)[c1_i2] = c1_dv2[c1_i2];
  }

  chartInstance->c1_is_active_c1_mpc_aircraft = c1_p_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell("is_active_c1_mpc_aircraft",
       c1_b_u, 5)), "is_active_c1_mpc_aircraft");
  sf_mex_destroy(&c1_b_u);
  c1_update_debugger_state_c1_mpc_aircraft(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_mpc_aircraft(SFc1_mpc_aircraftInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c1_mpc_aircraft(SFc1_mpc_aircraftInstanceStruct
  *chartInstance)
{
  int32_T c1_i3;
  int32_T c1_i4;
  int32_T c1_i5;
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
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i3 = 0; c1_i3 < 6; c1_i3++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_xkk1)[c1_i3], 11U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  for (c1_i4 = 0; c1_i4 < 12; c1_i4++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_C)[c1_i4], 10U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  for (c1_i5 = 0; c1_i5 < 12; c1_i5++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_B)[c1_i5], 9U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  for (c1_i6 = 0; c1_i6 < 36; c1_i6++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_A)[c1_i6], 8U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  for (c1_i7 = 0; c1_i7 < 12; c1_i7++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_L)[c1_i7], 7U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  for (c1_i8 = 0; c1_i8 < 12; c1_i8++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_M)[c1_i8], 6U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  for (c1_i9 = 0; c1_i9 < 12; c1_i9++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_s)[c1_i9], 5U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  for (c1_i10 = 0; c1_i10 < 120; c1_i10++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_S)[c1_i10], 4U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  for (c1_i11 = 0; c1_i11 < 60; c1_i11++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_G)[c1_i11], 3U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  for (c1_i12 = 0; c1_i12 < 50; c1_i12++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_F)[c1_i12], 2U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  for (c1_i13 = 0; c1_i13 < 25; c1_i13++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_H)[c1_i13], 1U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  for (c1_i14 = 0; c1_i14 < 6; c1_i14++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_f)[c1_i14], 0U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_mpc_aircraft(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_mpc_aircraftMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c1_i15 = 0; c1_i15 < 2; c1_i15++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_u)[c1_i15], 12U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  for (c1_i16 = 0; c1_i16 < 12; c1_i16++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_feasRes)[c1_i16], 13U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  for (c1_i17 = 0; c1_i17 < 6; c1_i17++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_xk1k)[c1_i17], 14U, 1U, 0U,
                          chartInstance->c1_sfEvent, false);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_time, 15U, 1U, 0U,
                        chartInstance->c1_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_iter, 16U, 1U, 0U,
                        chartInstance->c1_sfEvent, false);
}

static void mdl_start_c1_mpc_aircraft(SFc1_mpc_aircraftInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c1_chartstep_c1_mpc_aircraft(SFc1_mpc_aircraftInstanceStruct
  *chartInstance)
{
  int32_T c1_i18;
  real_T c1_b_f[6];
  int32_T c1_i19;
  real_T c1_b_H[25];
  int32_T c1_i20;
  real_T c1_b_F[50];
  int32_T c1_i21;
  real_T c1_b_G[60];
  int32_T c1_i22;
  real_T c1_b_S[120];
  int32_T c1_i23;
  real_T c1_b_s[12];
  int32_T c1_i24;
  real_T c1_b_M[12];
  int32_T c1_i25;
  real_T c1_b_L[12];
  int32_T c1_i26;
  real_T c1_b_A[36];
  int32_T c1_i27;
  real_T c1_b_B[12];
  int32_T c1_i28;
  real_T c1_b_C[12];
  int32_T c1_i29;
  real_T c1_b_xkk1[6];
  uint32_T c1_debug_family_var_map[29];
  c1_sflJsObR9dsqNm7nhVXYguC c1_options;
  real_T c1_zopt[5];
  real_T c1_nu;
  real_T c1_ny;
  real_T c1_u0[2];
  real_T c1_y[2];
  real_T c1_xkk[6];
  real_T c1_p[10];
  real_T c1_b[12];
  real_T c1_h[5];
  real_T c1_nargin = 12.0;
  real_T c1_nargout = 5.0;
  real_T c1_b_u[2];
  real_T c1_b_feasRes[12];
  real_T c1_b_xk1k[6];
  real_T c1_b_time;
  real_T c1_b_iter;
  int32_T c1_i30;
  static char_T c1_cv0[21] = { 'i', 'n', 't', 'e', 'r', 'i', 'o', 'r', '-', 'p',
    'o', 'i', 'n', 't', '-', 'c', 'o', 'n', 'v', 'e', 'x' };

  int32_T c1_i31;
  static char_T c1_cv1[4] = { 'n', 'o', 'n', 'e' };

  int32_T c1_i32;
  int32_T c1_i33;
  int32_T c1_i34;
  int32_T c1_i35;
  real_T c1_a[12];
  int32_T c1_i36;
  real_T c1_b_b[6];
  int32_T c1_i37;
  real_T c1_b_y[2];
  int32_T c1_i38;
  int32_T c1_i39;
  int32_T c1_i40;
  real_T c1_b_a[12];
  int32_T c1_i41;
  int32_T c1_i42;
  real_T c1_c_y[6];
  int32_T c1_i43;
  int32_T c1_i44;
  int32_T c1_i45;
  int32_T c1_i46;
  int32_T c1_i47;
  int32_T c1_i48;
  int32_T c1_i49;
  real_T c1_c_a[120];
  int32_T c1_i50;
  real_T c1_c_b[10];
  int32_T c1_i51;
  real_T c1_d_y[12];
  int32_T c1_i52;
  int32_T c1_i53;
  int32_T c1_i54;
  int32_T c1_i55;
  real_T c1_d_a[50];
  int32_T c1_i56;
  int32_T c1_i57;
  int32_T c1_i58;
  int32_T c1_i59;
  real_T c1_c_C[5];
  int32_T c1_i60;
  int32_T c1_i61;
  int32_T c1_i62;
  int32_T c1_i63;
  int32_T c1_i64;
  int32_T c1_i65;
  int32_T c1_i66;
  real_T c1_c_u[25];
  const mxArray *c1_e_y = NULL;
  int32_T c1_i67;
  const mxArray *c1_f_y = NULL;
  int32_T c1_i68;
  real_T c1_d_u[60];
  const mxArray *c1_g_y = NULL;
  int32_T c1_i69;
  const mxArray *c1_h_y = NULL;
  const mxArray *c1_i_y = NULL;
  const mxArray *c1_j_y = NULL;
  const mxArray *c1_k_y = NULL;
  const mxArray *c1_l_y = NULL;
  const mxArray *c1_m_y = NULL;
  real_T c1_e_u;
  const mxArray *c1_n_y = NULL;
  const mxArray *c1_c_iter = NULL;
  const mxArray *c1_c_time = NULL;
  const mxArray *c1_b_zopt = NULL;
  real_T c1_dv3[5];
  int32_T c1_i70;
  int32_T c1_i71;
  int32_T c1_i72;
  int32_T c1_i73;
  int32_T c1_i74;
  int32_T c1_i75;
  int32_T c1_i76;
  int32_T c1_i77;
  int32_T c1_i78;
  real_T c1_e_a[36];
  int32_T c1_i79;
  int32_T c1_i80;
  int32_T c1_i81;
  int32_T c1_i82;
  int32_T c1_i83;
  int32_T c1_i84;
  int32_T c1_i85;
  real_T c1_o_y[6];
  int32_T c1_i86;
  int32_T c1_i87;
  int32_T c1_i88;
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
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i18 = 0; c1_i18 < 6; c1_i18++) {
    c1_b_f[c1_i18] = (*chartInstance->c1_f)[c1_i18];
  }

  for (c1_i19 = 0; c1_i19 < 25; c1_i19++) {
    c1_b_H[c1_i19] = (*chartInstance->c1_H)[c1_i19];
  }

  for (c1_i20 = 0; c1_i20 < 50; c1_i20++) {
    c1_b_F[c1_i20] = (*chartInstance->c1_F)[c1_i20];
  }

  for (c1_i21 = 0; c1_i21 < 60; c1_i21++) {
    c1_b_G[c1_i21] = (*chartInstance->c1_G)[c1_i21];
  }

  for (c1_i22 = 0; c1_i22 < 120; c1_i22++) {
    c1_b_S[c1_i22] = (*chartInstance->c1_S)[c1_i22];
  }

  for (c1_i23 = 0; c1_i23 < 12; c1_i23++) {
    c1_b_s[c1_i23] = (*chartInstance->c1_s)[c1_i23];
  }

  for (c1_i24 = 0; c1_i24 < 12; c1_i24++) {
    c1_b_M[c1_i24] = (*chartInstance->c1_M)[c1_i24];
  }

  for (c1_i25 = 0; c1_i25 < 12; c1_i25++) {
    c1_b_L[c1_i25] = (*chartInstance->c1_L)[c1_i25];
  }

  for (c1_i26 = 0; c1_i26 < 36; c1_i26++) {
    c1_b_A[c1_i26] = (*chartInstance->c1_A)[c1_i26];
  }

  for (c1_i27 = 0; c1_i27 < 12; c1_i27++) {
    c1_b_B[c1_i27] = (*chartInstance->c1_B)[c1_i27];
  }

  for (c1_i28 = 0; c1_i28 < 12; c1_i28++) {
    c1_b_C[c1_i28] = (*chartInstance->c1_C)[c1_i28];
  }

  for (c1_i29 = 0; c1_i29 < 6; c1_i29++) {
    c1_b_xkk1[c1_i29] = (*chartInstance->c1_xkk1)[c1_i29];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 29U, 29U, c1_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_options, 0U, c1_n_sf_marshallOut,
    c1_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_zopt, 1U, c1_l_sf_marshallOut,
    c1_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_nu, 2U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_ny, 3U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_u0, 4U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_y, 5U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_xkk, 6U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_p, 7U, c1_m_sf_marshallOut,
    c1_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_b, 8U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_h, 9U, c1_l_sf_marshallOut,
    c1_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 10U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 11U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_f, 12U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_H, 13U, c1_k_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_F, 14U, c1_j_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_G, 15U, c1_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_S, 16U, c1_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_s, 17U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_M, 18U, c1_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_L, 19U, c1_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_A, 20U, c1_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_B, 21U, c1_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_C, 22U, c1_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_b_xkk1, 23U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_b_u, 24U, c1_d_sf_marshallOut,
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_b_feasRes, 25U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_b_xk1k, 26U, c1_b_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_time, 27U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_b_iter, 28U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 7);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 8);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 10);
  for (c1_i30 = 0; c1_i30 < 21; c1_i30++) {
    c1_options.Algorithm[c1_i30] = c1_cv0[c1_i30];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 11);
  c1_options.MaxIter = 1000.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 12);
  c1_options.TolCon = 1.0E-12;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 13);
  c1_options.TolFun = 1.0E-12;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 14);
  c1_options.TolX = 1.0E-12;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 15);
  for (c1_i31 = 0; c1_i31 < 4; c1_i31++) {
    c1_options.Display[c1_i31] = c1_cv1[c1_i31];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 16);
  for (c1_i32 = 0; c1_i32 < 5; c1_i32++) {
    c1_zopt[c1_i32] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 17);
  c1_b_time = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 18);
  c1_b_iter = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 21);
  c1_nu = 2.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 21);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 22);
  c1_ny = 2.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 23);
  for (c1_i33 = 0; c1_i33 < 2; c1_i33++) {
    c1_u0[c1_i33] = c1_b_f[c1_i33];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 24);
  for (c1_i34 = 0; c1_i34 < 2; c1_i34++) {
    c1_y[c1_i34] = c1_b_f[c1_i34 + 2];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 26);
  for (c1_i35 = 0; c1_i35 < 12; c1_i35++) {
    c1_a[c1_i35] = c1_b_C[c1_i35];
  }

  for (c1_i36 = 0; c1_i36 < 6; c1_i36++) {
    c1_b_b[c1_i36] = c1_b_xkk1[c1_i36];
  }

  c1_eml_scalar_eg(chartInstance);
  c1_eml_scalar_eg(chartInstance);
  c1_threshold(chartInstance);
  for (c1_i37 = 0; c1_i37 < 2; c1_i37++) {
    c1_b_y[c1_i37] = 0.0;
    c1_i38 = 0;
    for (c1_i39 = 0; c1_i39 < 6; c1_i39++) {
      c1_b_y[c1_i37] += c1_a[c1_i38 + c1_i37] * c1_b_b[c1_i39];
      c1_i38 += 2;
    }
  }

  for (c1_i40 = 0; c1_i40 < 12; c1_i40++) {
    c1_b_a[c1_i40] = c1_b_M[c1_i40];
  }

  for (c1_i41 = 0; c1_i41 < 2; c1_i41++) {
    c1_b_y[c1_i41] = c1_y[c1_i41] - c1_b_y[c1_i41];
  }

  c1_b_eml_scalar_eg(chartInstance);
  c1_b_eml_scalar_eg(chartInstance);
  c1_threshold(chartInstance);
  for (c1_i42 = 0; c1_i42 < 6; c1_i42++) {
    c1_c_y[c1_i42] = 0.0;
    c1_i43 = 0;
    for (c1_i44 = 0; c1_i44 < 2; c1_i44++) {
      c1_c_y[c1_i42] += c1_b_a[c1_i43 + c1_i42] * c1_b_y[c1_i44];
      c1_i43 += 6;
    }
  }

  for (c1_i45 = 0; c1_i45 < 6; c1_i45++) {
    c1_xkk[c1_i45] = c1_b_xkk1[c1_i45] + c1_c_y[c1_i45];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 29);
  for (c1_i46 = 0; c1_i46 < 2; c1_i46++) {
    c1_p[c1_i46] = c1_b_f[c1_i46];
  }

  for (c1_i47 = 0; c1_i47 < 6; c1_i47++) {
    c1_p[c1_i47 + 2] = c1_xkk[c1_i47];
  }

  for (c1_i48 = 0; c1_i48 < 2; c1_i48++) {
    c1_p[c1_i48 + 8] = c1_b_f[c1_i48 + 4];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 31);
  for (c1_i49 = 0; c1_i49 < 120; c1_i49++) {
    c1_c_a[c1_i49] = c1_b_S[c1_i49];
  }

  for (c1_i50 = 0; c1_i50 < 10; c1_i50++) {
    c1_c_b[c1_i50] = c1_p[c1_i50];
  }

  c1_c_eml_scalar_eg(chartInstance);
  c1_c_eml_scalar_eg(chartInstance);
  c1_threshold(chartInstance);
  for (c1_i51 = 0; c1_i51 < 12; c1_i51++) {
    c1_d_y[c1_i51] = 0.0;
    c1_i52 = 0;
    for (c1_i53 = 0; c1_i53 < 10; c1_i53++) {
      c1_d_y[c1_i51] += c1_c_a[c1_i52 + c1_i51] * c1_c_b[c1_i53];
      c1_i52 += 12;
    }
  }

  for (c1_i54 = 0; c1_i54 < 12; c1_i54++) {
    c1_b[c1_i54] = c1_d_y[c1_i54] + c1_b_s[c1_i54];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 32);
  for (c1_i55 = 0; c1_i55 < 50; c1_i55++) {
    c1_d_a[c1_i55] = c1_b_F[c1_i55];
  }

  for (c1_i56 = 0; c1_i56 < 10; c1_i56++) {
    c1_c_b[c1_i56] = c1_p[c1_i56];
  }

  c1_d_eml_scalar_eg(chartInstance);
  c1_d_eml_scalar_eg(chartInstance);
  for (c1_i57 = 0; c1_i57 < 5; c1_i57++) {
    c1_h[c1_i57] = 0.0;
  }

  for (c1_i58 = 0; c1_i58 < 5; c1_i58++) {
    c1_h[c1_i58] = 0.0;
  }

  for (c1_i59 = 0; c1_i59 < 5; c1_i59++) {
    c1_c_C[c1_i59] = c1_h[c1_i59];
  }

  for (c1_i60 = 0; c1_i60 < 5; c1_i60++) {
    c1_h[c1_i60] = c1_c_C[c1_i60];
  }

  c1_threshold(chartInstance);
  for (c1_i61 = 0; c1_i61 < 5; c1_i61++) {
    c1_c_C[c1_i61] = c1_h[c1_i61];
  }

  for (c1_i62 = 0; c1_i62 < 5; c1_i62++) {
    c1_h[c1_i62] = c1_c_C[c1_i62];
  }

  for (c1_i63 = 0; c1_i63 < 5; c1_i63++) {
    c1_h[c1_i63] = 0.0;
    c1_i64 = 0;
    for (c1_i65 = 0; c1_i65 < 10; c1_i65++) {
      c1_h[c1_i63] += c1_d_a[c1_i64 + c1_i63] * c1_c_b[c1_i65];
      c1_i64 += 5;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 34);
  for (c1_i66 = 0; c1_i66 < 25; c1_i66++) {
    c1_c_u[c1_i66] = c1_b_H[c1_i66];
  }

  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 2, 5, 5),
                false);
  for (c1_i67 = 0; c1_i67 < 5; c1_i67++) {
    c1_c_C[c1_i67] = c1_h[c1_i67];
  }

  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", c1_c_C, 0, 0U, 1U, 0U, 1, 5), false);
  for (c1_i68 = 0; c1_i68 < 60; c1_i68++) {
    c1_d_u[c1_i68] = -c1_b_G[c1_i68];
  }

  c1_g_y = NULL;
  sf_mex_assign(&c1_g_y, sf_mex_create("y", c1_d_u, 0, 0U, 1U, 0U, 2, 12, 5),
                false);
  for (c1_i69 = 0; c1_i69 < 12; c1_i69++) {
    c1_d_y[c1_i69] = -c1_b[c1_i69];
  }

  c1_h_y = NULL;
  sf_mex_assign(&c1_h_y, sf_mex_create("y", c1_d_y, 0, 0U, 1U, 0U, 1, 12), false);
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
  c1_e_u = 1.0;
  c1_n_y = NULL;
  sf_mex_assign(&c1_n_y, sf_mex_create("y", &c1_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "wgsSolver", 3U, 10U, 14,
                    c1_e_y, 14, c1_f_y, 14, c1_g_y, 14, c1_h_y, 14, c1_i_y, 14,
                    c1_j_y, 14, c1_k_y, 14, c1_l_y, 14, c1_m_y, 14, c1_n_y,
                    &c1_b_zopt, &c1_c_time, &c1_c_iter);
  c1_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_zopt), "zopt", c1_dv3);
  for (c1_i70 = 0; c1_i70 < 5; c1_i70++) {
    c1_zopt[c1_i70] = c1_dv3[c1_i70];
  }

  c1_b_time = c1_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_c_time), "time");
  c1_b_iter = c1_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_c_iter), "iter");
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 37);
  for (c1_i71 = 0; c1_i71 < 60; c1_i71++) {
    c1_d_u[c1_i71] = c1_b_G[c1_i71];
  }

  for (c1_i72 = 0; c1_i72 < 5; c1_i72++) {
    c1_c_C[c1_i72] = c1_zopt[c1_i72];
  }

  c1_e_eml_scalar_eg(chartInstance);
  c1_e_eml_scalar_eg(chartInstance);
  c1_threshold(chartInstance);
  for (c1_i73 = 0; c1_i73 < 12; c1_i73++) {
    c1_d_y[c1_i73] = 0.0;
    c1_i74 = 0;
    for (c1_i75 = 0; c1_i75 < 5; c1_i75++) {
      c1_d_y[c1_i73] += c1_d_u[c1_i74 + c1_i73] * c1_c_C[c1_i75];
      c1_i74 += 12;
    }
  }

  for (c1_i76 = 0; c1_i76 < 12; c1_i76++) {
    c1_b_feasRes[c1_i76] = c1_d_y[c1_i76] - c1_b[c1_i76];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 39);
  c1_nu = 2.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 40);
  for (c1_i77 = 0; c1_i77 < 2; c1_i77++) {
    c1_b_u[c1_i77] = c1_zopt[c1_i77] + c1_u0[c1_i77];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 42);
  for (c1_i78 = 0; c1_i78 < 36; c1_i78++) {
    c1_e_a[c1_i78] = c1_b_A[c1_i78];
  }

  for (c1_i79 = 0; c1_i79 < 6; c1_i79++) {
    c1_b_b[c1_i79] = c1_b_xkk1[c1_i79];
  }

  c1_f_eml_scalar_eg(chartInstance);
  c1_f_eml_scalar_eg(chartInstance);
  c1_threshold(chartInstance);
  for (c1_i80 = 0; c1_i80 < 6; c1_i80++) {
    c1_c_y[c1_i80] = 0.0;
    c1_i81 = 0;
    for (c1_i82 = 0; c1_i82 < 6; c1_i82++) {
      c1_c_y[c1_i80] += c1_e_a[c1_i81 + c1_i80] * c1_b_b[c1_i82];
      c1_i81 += 6;
    }
  }

  for (c1_i83 = 0; c1_i83 < 12; c1_i83++) {
    c1_b_a[c1_i83] = c1_b_B[c1_i83];
  }

  for (c1_i84 = 0; c1_i84 < 2; c1_i84++) {
    c1_b_y[c1_i84] = c1_b_u[c1_i84];
  }

  c1_b_eml_scalar_eg(chartInstance);
  c1_b_eml_scalar_eg(chartInstance);
  c1_threshold(chartInstance);
  for (c1_i85 = 0; c1_i85 < 6; c1_i85++) {
    c1_o_y[c1_i85] = 0.0;
    c1_i86 = 0;
    for (c1_i87 = 0; c1_i87 < 2; c1_i87++) {
      c1_o_y[c1_i85] += c1_b_a[c1_i86 + c1_i85] * c1_b_y[c1_i87];
      c1_i86 += 6;
    }
  }

  for (c1_i88 = 0; c1_i88 < 12; c1_i88++) {
    c1_a[c1_i88] = c1_b_C[c1_i88];
  }

  for (c1_i89 = 0; c1_i89 < 6; c1_i89++) {
    c1_b_b[c1_i89] = c1_b_xkk1[c1_i89];
  }

  c1_eml_scalar_eg(chartInstance);
  c1_eml_scalar_eg(chartInstance);
  c1_threshold(chartInstance);
  for (c1_i90 = 0; c1_i90 < 2; c1_i90++) {
    c1_b_y[c1_i90] = 0.0;
    c1_i91 = 0;
    for (c1_i92 = 0; c1_i92 < 6; c1_i92++) {
      c1_b_y[c1_i90] += c1_a[c1_i91 + c1_i90] * c1_b_b[c1_i92];
      c1_i91 += 2;
    }
  }

  for (c1_i93 = 0; c1_i93 < 12; c1_i93++) {
    c1_b_a[c1_i93] = c1_b_L[c1_i93];
  }

  for (c1_i94 = 0; c1_i94 < 2; c1_i94++) {
    c1_b_y[c1_i94] = c1_y[c1_i94] - c1_b_y[c1_i94];
  }

  c1_b_eml_scalar_eg(chartInstance);
  c1_b_eml_scalar_eg(chartInstance);
  c1_threshold(chartInstance);
  for (c1_i95 = 0; c1_i95 < 6; c1_i95++) {
    c1_b_b[c1_i95] = 0.0;
    c1_i96 = 0;
    for (c1_i97 = 0; c1_i97 < 2; c1_i97++) {
      c1_b_b[c1_i95] += c1_b_a[c1_i96 + c1_i95] * c1_b_y[c1_i97];
      c1_i96 += 6;
    }
  }

  for (c1_i98 = 0; c1_i98 < 6; c1_i98++) {
    c1_b_xk1k[c1_i98] = (c1_c_y[c1_i98] + c1_o_y[c1_i98]) + c1_b_b[c1_i98];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -42);
  _SFD_SYMBOL_SCOPE_POP();
  sf_mex_destroy(&c1_b_zopt);
  sf_mex_destroy(&c1_c_time);
  sf_mex_destroy(&c1_c_iter);
  for (c1_i99 = 0; c1_i99 < 2; c1_i99++) {
    (*chartInstance->c1_u)[c1_i99] = c1_b_u[c1_i99];
  }

  for (c1_i100 = 0; c1_i100 < 12; c1_i100++) {
    (*chartInstance->c1_feasRes)[c1_i100] = c1_b_feasRes[c1_i100];
  }

  for (c1_i101 = 0; c1_i101 < 6; c1_i101++) {
    (*chartInstance->c1_xk1k)[c1_i101] = c1_b_xk1k[c1_i101];
  }

  *chartInstance->c1_time = c1_b_time;
  *chartInstance->c1_iter = c1_b_iter;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void initSimStructsc1_mpc_aircraft(SFc1_mpc_aircraftInstanceStruct
  *chartInstance)
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
  real_T c1_b_u;
  const mxArray *c1_y = NULL;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_b_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0), false);
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
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_b_time = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_time), &c1_thisId);
  sf_mex_destroy(&c1_b_time);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i102;
  real_T c1_b_u[6];
  const mxArray *c1_y = NULL;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i102 = 0; c1_i102 < 6; c1_i102++) {
    c1_b_u[c1_i102] = (*(real_T (*)[6])c1_inData)[c1_i102];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 1, 6), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_b_xk1k, const char_T *c1_identifier, real_T c1_y[6])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_xk1k), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_b_xk1k);
}

static void c1_b_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[6])
{
  real_T c1_dv4[6];
  int32_T c1_i103;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_b_u), c1_dv4, 1, 0, 0U, 1, 0U, 1, 6);
  for (c1_i103 = 0; c1_i103 < 6; c1_i103++) {
    c1_y[c1_i103] = c1_dv4[c1_i103];
  }

  sf_mex_destroy(&c1_b_u);
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_xk1k;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[6];
  int32_T c1_i104;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_b_xk1k = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_xk1k), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_b_xk1k);
  for (c1_i104 = 0; c1_i104 < 6; c1_i104++) {
    (*(real_T (*)[6])c1_outData)[c1_i104] = c1_y[c1_i104];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i105;
  real_T c1_b_u[12];
  const mxArray *c1_y = NULL;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i105 = 0; c1_i105 < 12; c1_i105++) {
    c1_b_u[c1_i105] = (*(real_T (*)[12])c1_inData)[c1_i105];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 1, 12), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_c_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_b_feasRes, const char_T *c1_identifier, real_T c1_y[12])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_feasRes), &c1_thisId,
                        c1_y);
  sf_mex_destroy(&c1_b_feasRes);
}

static void c1_d_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[12])
{
  real_T c1_dv5[12];
  int32_T c1_i106;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_b_u), c1_dv5, 1, 0, 0U, 1, 0U, 1, 12);
  for (c1_i106 = 0; c1_i106 < 12; c1_i106++) {
    c1_y[c1_i106] = c1_dv5[c1_i106];
  }

  sf_mex_destroy(&c1_b_u);
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_feasRes;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[12];
  int32_T c1_i107;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_b_feasRes = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_feasRes), &c1_thisId,
                        c1_y);
  sf_mex_destroy(&c1_b_feasRes);
  for (c1_i107 = 0; c1_i107 < 12; c1_i107++) {
    (*(real_T (*)[12])c1_outData)[c1_i107] = c1_y[c1_i107];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i108;
  real_T c1_b_u[2];
  const mxArray *c1_y = NULL;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i108 = 0; c1_i108 < 2; c1_i108++) {
    c1_b_u[c1_i108] = (*(real_T (*)[2])c1_inData)[c1_i108];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_e_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const char_T *c1_identifier, real_T c1_y[2])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_u), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_b_u);
}

static void c1_f_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[2])
{
  real_T c1_dv6[2];
  int32_T c1_i109;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_b_u), c1_dv6, 1, 0, 0U, 1, 0U, 1, 2);
  for (c1_i109 = 0; c1_i109 < 2; c1_i109++) {
    c1_y[c1_i109] = c1_dv6[c1_i109];
  }

  sf_mex_destroy(&c1_b_u);
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_u;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[2];
  int32_T c1_i110;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_b_u = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_u), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_b_u);
  for (c1_i110 = 0; c1_i110 < 2; c1_i110++) {
    (*(real_T (*)[2])c1_outData)[c1_i110] = c1_y[c1_i110];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i111;
  int32_T c1_i112;
  int32_T c1_i113;
  real_T c1_b_u[12];
  const mxArray *c1_y = NULL;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i111 = 0;
  for (c1_i112 = 0; c1_i112 < 6; c1_i112++) {
    for (c1_i113 = 0; c1_i113 < 2; c1_i113++) {
      c1_b_u[c1_i113 + c1_i111] = (*(real_T (*)[12])c1_inData)[c1_i113 + c1_i111];
    }

    c1_i111 += 2;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 2, 2, 6), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i114;
  int32_T c1_i115;
  int32_T c1_i116;
  real_T c1_b_u[12];
  const mxArray *c1_y = NULL;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i114 = 0;
  for (c1_i115 = 0; c1_i115 < 2; c1_i115++) {
    for (c1_i116 = 0; c1_i116 < 6; c1_i116++) {
      c1_b_u[c1_i116 + c1_i114] = (*(real_T (*)[12])c1_inData)[c1_i116 + c1_i114];
    }

    c1_i114 += 6;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 2, 6, 2), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i117;
  int32_T c1_i118;
  int32_T c1_i119;
  real_T c1_b_u[36];
  const mxArray *c1_y = NULL;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i117 = 0;
  for (c1_i118 = 0; c1_i118 < 6; c1_i118++) {
    for (c1_i119 = 0; c1_i119 < 6; c1_i119++) {
      c1_b_u[c1_i119 + c1_i117] = (*(real_T (*)[36])c1_inData)[c1_i119 + c1_i117];
    }

    c1_i117 += 6;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 2, 6, 6), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i120;
  int32_T c1_i121;
  int32_T c1_i122;
  real_T c1_b_u[120];
  const mxArray *c1_y = NULL;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i120 = 0;
  for (c1_i121 = 0; c1_i121 < 10; c1_i121++) {
    for (c1_i122 = 0; c1_i122 < 12; c1_i122++) {
      c1_b_u[c1_i122 + c1_i120] = (*(real_T (*)[120])c1_inData)[c1_i122 +
        c1_i120];
    }

    c1_i120 += 12;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 2, 12, 10),
                false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_i_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i123;
  int32_T c1_i124;
  int32_T c1_i125;
  real_T c1_b_u[60];
  const mxArray *c1_y = NULL;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i123 = 0;
  for (c1_i124 = 0; c1_i124 < 5; c1_i124++) {
    for (c1_i125 = 0; c1_i125 < 12; c1_i125++) {
      c1_b_u[c1_i125 + c1_i123] = (*(real_T (*)[60])c1_inData)[c1_i125 + c1_i123];
    }

    c1_i123 += 12;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 2, 12, 5),
                false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_j_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i126;
  int32_T c1_i127;
  int32_T c1_i128;
  real_T c1_b_u[50];
  const mxArray *c1_y = NULL;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i126 = 0;
  for (c1_i127 = 0; c1_i127 < 10; c1_i127++) {
    for (c1_i128 = 0; c1_i128 < 5; c1_i128++) {
      c1_b_u[c1_i128 + c1_i126] = (*(real_T (*)[50])c1_inData)[c1_i128 + c1_i126];
    }

    c1_i126 += 5;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 2, 5, 10),
                false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_k_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i129;
  int32_T c1_i130;
  int32_T c1_i131;
  real_T c1_b_u[25];
  const mxArray *c1_y = NULL;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i129 = 0;
  for (c1_i130 = 0; c1_i130 < 5; c1_i130++) {
    for (c1_i131 = 0; c1_i131 < 5; c1_i131++) {
      c1_b_u[c1_i131 + c1_i129] = (*(real_T (*)[25])c1_inData)[c1_i131 + c1_i129];
    }

    c1_i129 += 5;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 2, 5, 5), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_l_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i132;
  real_T c1_b_u[5];
  const mxArray *c1_y = NULL;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i132 = 0; c1_i132 < 5; c1_i132++) {
    c1_b_u[c1_i132] = (*(real_T (*)[5])c1_inData)[c1_i132];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 1, 5), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_zopt;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[5];
  int32_T c1_i133;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_zopt = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_zopt), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_zopt);
  for (c1_i133 = 0; c1_i133 < 5; c1_i133++) {
    (*(real_T (*)[5])c1_outData)[c1_i133] = c1_y[c1_i133];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_m_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i134;
  real_T c1_b_u[10];
  const mxArray *c1_y = NULL;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i134 = 0; c1_i134 < 10; c1_i134++) {
    c1_b_u[c1_i134] = (*(real_T (*)[10])c1_inData)[c1_i134];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 1, 10), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_g_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[10])
{
  real_T c1_dv7[10];
  int32_T c1_i135;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_b_u), c1_dv7, 1, 0, 0U, 1, 0U, 1, 10);
  for (c1_i135 = 0; c1_i135 < 10; c1_i135++) {
    c1_y[c1_i135] = c1_dv7[c1_i135];
  }

  sf_mex_destroy(&c1_b_u);
}

static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_p;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[10];
  int32_T c1_i136;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_p = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_p), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_p);
  for (c1_i136 = 0; c1_i136 < 10; c1_i136++) {
    (*(real_T (*)[10])c1_outData)[c1_i136] = c1_y[c1_i136];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_n_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData;
  c1_sflJsObR9dsqNm7nhVXYguC c1_b_u;
  const mxArray *c1_y = NULL;
  int32_T c1_i137;
  char_T c1_c_u[21];
  const mxArray *c1_b_y = NULL;
  real_T c1_d_u;
  const mxArray *c1_c_y = NULL;
  real_T c1_e_u;
  const mxArray *c1_d_y = NULL;
  real_T c1_f_u;
  const mxArray *c1_e_y = NULL;
  real_T c1_g_u;
  const mxArray *c1_f_y = NULL;
  int32_T c1_i138;
  char_T c1_h_u[4];
  const mxArray *c1_g_y = NULL;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_mxArrayOutData = NULL;
  c1_b_u = *(c1_sflJsObR9dsqNm7nhVXYguC *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  for (c1_i137 = 0; c1_i137 < 21; c1_i137++) {
    c1_c_u[c1_i137] = c1_b_u.Algorithm[c1_i137];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_c_u, 10, 0U, 1U, 0U, 2, 1, 21),
                false);
  sf_mex_addfield(c1_y, c1_b_y, "Algorithm", "Algorithm", 0);
  c1_d_u = c1_b_u.MaxIter;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_c_y, "MaxIter", "MaxIter", 0);
  c1_e_u = c1_b_u.TolCon;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_d_y, "TolCon", "TolCon", 0);
  c1_f_u = c1_b_u.TolFun;
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_f_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_e_y, "TolFun", "TolFun", 0);
  c1_g_u = c1_b_u.TolX;
  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_g_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c1_y, c1_f_y, "TolX", "TolX", 0);
  for (c1_i138 = 0; c1_i138 < 4; c1_i138++) {
    c1_h_u[c1_i138] = c1_b_u.Display[c1_i138];
  }

  c1_g_y = NULL;
  sf_mex_assign(&c1_g_y, sf_mex_create("y", c1_h_u, 10, 0U, 1U, 0U, 2, 1, 4),
                false);
  sf_mex_addfield(c1_y, c1_g_y, "Display", "Display", 0);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static c1_sflJsObR9dsqNm7nhVXYguC c1_h_emlrt_marshallIn
  (SFc1_mpc_aircraftInstanceStruct *chartInstance, const mxArray *c1_b_u, const
   emlrtMsgIdentifier *c1_parentId)
{
  c1_sflJsObR9dsqNm7nhVXYguC c1_y;
  emlrtMsgIdentifier c1_thisId;
  static const char * c1_fieldNames[6] = { "Algorithm", "MaxIter", "TolCon",
    "TolFun", "TolX", "Display" };

  c1_thisId.fParent = c1_parentId;
  sf_mex_check_struct(c1_parentId, c1_b_u, 6, c1_fieldNames, 0U, NULL);
  c1_thisId.fIdentifier = "Algorithm";
  c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_b_u,
    "Algorithm", "Algorithm", 0)), &c1_thisId, c1_y.Algorithm);
  c1_thisId.fIdentifier = "MaxIter";
  c1_y.MaxIter = c1_n_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_b_u, "MaxIter", "MaxIter", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "TolCon";
  c1_y.TolCon = c1_n_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_b_u, "TolCon", "TolCon", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "TolFun";
  c1_y.TolFun = c1_n_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_b_u, "TolFun", "TolFun", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "TolX";
  c1_y.TolX = c1_n_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c1_b_u, "TolX", "TolX", 0)), &c1_thisId);
  c1_thisId.fIdentifier = "Display";
  c1_j_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c1_b_u,
    "Display", "Display", 0)), &c1_thisId, c1_y.Display);
  sf_mex_destroy(&c1_b_u);
  return c1_y;
}

static void c1_i_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId, char_T c1_y[21])
{
  char_T c1_cv2[21];
  int32_T c1_i139;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_b_u), c1_cv2, 1, 10, 0U, 1, 0U, 2, 1,
                21);
  for (c1_i139 = 0; c1_i139 < 21; c1_i139++) {
    c1_y[c1_i139] = c1_cv2[c1_i139];
  }

  sf_mex_destroy(&c1_b_u);
}

static void c1_j_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId, char_T c1_y[4])
{
  char_T c1_cv3[4];
  int32_T c1_i140;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_b_u), c1_cv3, 1, 10, 0U, 1, 0U, 2, 1,
                4);
  for (c1_i140 = 0; c1_i140 < 4; c1_i140++) {
    c1_y[c1_i140] = c1_cv3[c1_i140];
  }

  sf_mex_destroy(&c1_b_u);
}

static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_options;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  c1_sflJsObR9dsqNm7nhVXYguC c1_y;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_options = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_options), &c1_thisId);
  sf_mex_destroy(&c1_options);
  *(c1_sflJsObR9dsqNm7nhVXYguC *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_mpc_aircraft_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  sf_mex_assign(&c1_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c1_nameCaptureInfo;
}

static void c1_eml_scalar_eg(SFc1_mpc_aircraftInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_threshold(SFc1_mpc_aircraftInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_b_eml_scalar_eg(SFc1_mpc_aircraftInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_c_eml_scalar_eg(SFc1_mpc_aircraftInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_d_eml_scalar_eg(SFc1_mpc_aircraftInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_e_eml_scalar_eg(SFc1_mpc_aircraftInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_f_eml_scalar_eg(SFc1_mpc_aircraftInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_k_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_zopt, const char_T *c1_identifier, real_T c1_y[5])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_zopt), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_zopt);
}

static void c1_l_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[5])
{
  real_T c1_dv8[5];
  int32_T c1_i141;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_b_u), c1_dv8, 1, 0, 0U, 1, 0U, 1, 5);
  for (c1_i141 = 0; c1_i141 < 5; c1_i141++) {
    c1_y[c1_i141] = c1_dv8[c1_i141];
  }

  sf_mex_destroy(&c1_b_u);
}

static real_T c1_m_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c1_b_time, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_time), &c1_thisId);
  sf_mex_destroy(&c1_b_time);
  return c1_y;
}

static real_T c1_n_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_b_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_b_u);
  return c1_y;
}

static const mxArray *c1_o_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_b_u;
  const mxArray *c1_y = NULL;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_b_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_b_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static int32_T c1_o_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i142;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_b_u), &c1_i142, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i142;
  sf_mex_destroy(&c1_b_u);
  return c1_y;
}

static void c1_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_p_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c1_b_is_active_c1_mpc_aircraft, const char_T
  *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_q_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_mpc_aircraft), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_mpc_aircraft);
  return c1_y;
}

static uint8_T c1_q_emlrt_marshallIn(SFc1_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c1_b_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_b_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_b_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_mpc_aircraftInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc1_mpc_aircraftInstanceStruct
  *chartInstance)
{
  chartInstance->c1_f = (real_T (*)[6])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c1_H = (real_T (*)[25])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c1_F = (real_T (*)[50])ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c1_G = (real_T (*)[60])ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c1_S = (real_T (*)[120])ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c1_s = (real_T (*)[12])ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c1_u = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c1_feasRes = (real_T (*)[12])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c1_M = (real_T (*)[12])ssGetInputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c1_L = (real_T (*)[12])ssGetInputPortSignal_wrapper
    (chartInstance->S, 7);
  chartInstance->c1_xk1k = (real_T (*)[6])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c1_A = (real_T (*)[36])ssGetInputPortSignal_wrapper
    (chartInstance->S, 8);
  chartInstance->c1_B = (real_T (*)[12])ssGetInputPortSignal_wrapper
    (chartInstance->S, 9);
  chartInstance->c1_C = (real_T (*)[12])ssGetInputPortSignal_wrapper
    (chartInstance->S, 10);
  chartInstance->c1_xkk1 = (real_T (*)[6])ssGetInputPortSignal_wrapper
    (chartInstance->S, 11);
  chartInstance->c1_time = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c1_iter = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 5);
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

void sf_c1_mpc_aircraft_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3394119208U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1132068369U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2408494920U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2404094877U);
}

mxArray* sf_c1_mpc_aircraft_get_post_codegen_info(void);
mxArray *sf_c1_mpc_aircraft_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("TPS1dNlDB6IgfBXHQZDjz");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,12,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(5);
      pr[1] = (double)(5);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(5);
      pr[1] = (double)(10);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(12);
      pr[1] = (double)(5);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(12);
      pr[1] = (double)(10);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(12);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(2);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(2);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(6);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(2);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(6);
      mxSetField(mxData,10,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,11,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
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

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(12);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
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
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c1_mpc_aircraft_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_mpc_aircraft_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c1_mpc_aircraft_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("pre");
  mxArray *fallbackReason = mxCreateString("hasBreakpoints");
  mxArray *hiddenFallbackType = mxCreateString("none");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c1_mpc_aircraft_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c1_mpc_aircraft_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c1_mpc_aircraft(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x6'type','srcId','name','auxInfo'{{M[1],M[13],T\"feasRes\",},{M[1],M[22],T\"iter\",},{M[1],M[21],T\"time\",},{M[1],M[12],T\"u\",},{M[1],M[16],T\"xk1k\",},{M[8],M[0],T\"is_active_c1_mpc_aircraft\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 6, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_mpc_aircraft_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_mpc_aircraftInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc1_mpc_aircraftInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _mpc_aircraftMachineNumber_,
           1,
           1,
           1,
           0,
           17,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_mpc_aircraftMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_mpc_aircraftMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _mpc_aircraftMachineNumber_,
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
          _SFD_SET_DATA_PROPS(6,1,1,0,"M");
          _SFD_SET_DATA_PROPS(7,1,1,0,"L");
          _SFD_SET_DATA_PROPS(8,1,1,0,"A");
          _SFD_SET_DATA_PROPS(9,1,1,0,"B");
          _SFD_SET_DATA_PROPS(10,1,1,0,"C");
          _SFD_SET_DATA_PROPS(11,1,1,0,"xkk1");
          _SFD_SET_DATA_PROPS(12,2,0,1,"u");
          _SFD_SET_DATA_PROPS(13,2,0,1,"feasRes");
          _SFD_SET_DATA_PROPS(14,2,0,1,"xk1k");
          _SFD_SET_DATA_PROPS(15,2,0,1,"time");
          _SFD_SET_DATA_PROPS(16,2,0,1,"iter");
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
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",62,-1,858);

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 5;
          dimVector[1]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_k_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 5;
          dimVector[1]= 10;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_j_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 12;
          dimVector[1]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_i_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 12;
          dimVector[1]= 10;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_h_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 12;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_g_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)
            c1_d_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 12;
          _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)
            c1_c_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)
            c1_b_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(15,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(16,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _mpc_aircraftMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_mpc_aircraftInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc1_mpc_aircraftInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, *chartInstance->c1_f);
        _SFD_SET_DATA_VALUE_PTR(1U, *chartInstance->c1_H);
        _SFD_SET_DATA_VALUE_PTR(2U, *chartInstance->c1_F);
        _SFD_SET_DATA_VALUE_PTR(3U, *chartInstance->c1_G);
        _SFD_SET_DATA_VALUE_PTR(4U, *chartInstance->c1_S);
        _SFD_SET_DATA_VALUE_PTR(5U, *chartInstance->c1_s);
        _SFD_SET_DATA_VALUE_PTR(12U, *chartInstance->c1_u);
        _SFD_SET_DATA_VALUE_PTR(13U, *chartInstance->c1_feasRes);
        _SFD_SET_DATA_VALUE_PTR(6U, *chartInstance->c1_M);
        _SFD_SET_DATA_VALUE_PTR(7U, *chartInstance->c1_L);
        _SFD_SET_DATA_VALUE_PTR(14U, *chartInstance->c1_xk1k);
        _SFD_SET_DATA_VALUE_PTR(8U, *chartInstance->c1_A);
        _SFD_SET_DATA_VALUE_PTR(9U, *chartInstance->c1_B);
        _SFD_SET_DATA_VALUE_PTR(10U, *chartInstance->c1_C);
        _SFD_SET_DATA_VALUE_PTR(11U, *chartInstance->c1_xkk1);
        _SFD_SET_DATA_VALUE_PTR(15U, chartInstance->c1_time);
        _SFD_SET_DATA_VALUE_PTR(16U, chartInstance->c1_iter);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "socpqofscSpuSLxeMyc1gND";
}

static void sf_opaque_initialize_c1_mpc_aircraft(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_mpc_aircraftInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c1_mpc_aircraft((SFc1_mpc_aircraftInstanceStruct*)
    chartInstanceVar);
  initialize_c1_mpc_aircraft((SFc1_mpc_aircraftInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_mpc_aircraft(void *chartInstanceVar)
{
  enable_c1_mpc_aircraft((SFc1_mpc_aircraftInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_mpc_aircraft(void *chartInstanceVar)
{
  disable_c1_mpc_aircraft((SFc1_mpc_aircraftInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_mpc_aircraft(void *chartInstanceVar)
{
  sf_gateway_c1_mpc_aircraft((SFc1_mpc_aircraftInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c1_mpc_aircraft(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c1_mpc_aircraft((SFc1_mpc_aircraftInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c1_mpc_aircraft(SimStruct* S, const mxArray *
  st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c1_mpc_aircraft((SFc1_mpc_aircraftInstanceStruct*)
    chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c1_mpc_aircraft(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_mpc_aircraftInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_mpc_aircraft_optimization_info();
    }

    finalize_c1_mpc_aircraft((SFc1_mpc_aircraftInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_mpc_aircraft((SFc1_mpc_aircraftInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_mpc_aircraft(SimStruct *S)
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
    initialize_params_c1_mpc_aircraft((SFc1_mpc_aircraftInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_mpc_aircraft(SimStruct *S)
{
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_mpc_aircraft_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
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
        infoStruct,1,5);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=5; ++outPortIdx) {
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
  ssSetChecksum0(S,(1511218056U));
  ssSetChecksum1(S,(3469110327U));
  ssSetChecksum2(S,(835153400U));
  ssSetChecksum3(S,(1324171738U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_mpc_aircraft(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_mpc_aircraft(SimStruct *S)
{
  SFc1_mpc_aircraftInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc1_mpc_aircraftInstanceStruct *)utMalloc(sizeof
    (SFc1_mpc_aircraftInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_mpc_aircraftInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_mpc_aircraft;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c1_mpc_aircraft;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_mpc_aircraft;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_mpc_aircraft;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_mpc_aircraft;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_mpc_aircraft;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_mpc_aircraft;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c1_mpc_aircraft;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_mpc_aircraft;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_mpc_aircraft;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_mpc_aircraft;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->isEnhancedMooreMachine = 0;
  crtInfo->checksum = SF_RUNTIME_INFO_CHECKSUM;
  crtInfo->fCheckOverflow = sf_runtime_overflow_check_is_on(S);
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  crtInfo->compiledInfo = NULL;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
}

void c1_mpc_aircraft_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_mpc_aircraft(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_mpc_aircraft(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_mpc_aircraft(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_mpc_aircraft_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
