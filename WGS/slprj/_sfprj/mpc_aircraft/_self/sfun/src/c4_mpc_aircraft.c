/* Include files */

#include <stddef.h>
#include "blas.h"
#include "mpc_aircraft_sfun.h"
#include "c4_mpc_aircraft.h"
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
static const char * c4_debug_family_names[31] = { "options", "zopt", "mess",
  "output", "nu", "ny", "u0", "y", "xkk", "p", "b", "h", "nargin", "nargout",
  "f", "H", "F", "G", "S", "s", "M", "L", "A", "B", "C", "xkk1", "u", "feasRes",
  "xk1k", "time", "iter" };

/* Function Declarations */
static void initialize_c4_mpc_aircraft(SFc4_mpc_aircraftInstanceStruct
  *chartInstance);
static void initialize_params_c4_mpc_aircraft(SFc4_mpc_aircraftInstanceStruct
  *chartInstance);
static void enable_c4_mpc_aircraft(SFc4_mpc_aircraftInstanceStruct
  *chartInstance);
static void disable_c4_mpc_aircraft(SFc4_mpc_aircraftInstanceStruct
  *chartInstance);
static void c4_update_debugger_state_c4_mpc_aircraft
  (SFc4_mpc_aircraftInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c4_mpc_aircraft
  (SFc4_mpc_aircraftInstanceStruct *chartInstance);
static void set_sim_state_c4_mpc_aircraft(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c4_st);
static void finalize_c4_mpc_aircraft(SFc4_mpc_aircraftInstanceStruct
  *chartInstance);
static void sf_gateway_c4_mpc_aircraft(SFc4_mpc_aircraftInstanceStruct
  *chartInstance);
static void mdl_start_c4_mpc_aircraft(SFc4_mpc_aircraftInstanceStruct
  *chartInstance);
static void c4_chartstep_c4_mpc_aircraft(SFc4_mpc_aircraftInstanceStruct
  *chartInstance);
static void initSimStructsc4_mpc_aircraft(SFc4_mpc_aircraftInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber, uint32_T c4_instanceNumber);
static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData);
static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static void c4_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_xk1k, const char_T *c4_identifier, real_T c4_y[6]);
static void c4_b_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[6]);
static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static void c4_c_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_feasRes, const char_T *c4_identifier, real_T c4_y[12]);
static void c4_d_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[12]);
static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static void c4_e_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const char_T *c4_identifier, real_T c4_y[2]);
static void c4_f_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[2]);
static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_e_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_f_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_g_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_h_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_i_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_j_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_k_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_l_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static void c4_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_m_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static void c4_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_n_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static void c4_g_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[10]);
static void c4_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_o_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static void c4_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static const mxArray *c4_p_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static const mxArray *c4_q_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static c4_sflJsObR9dsqNm7nhVXYguC c4_h_emlrt_marshallIn
  (SFc4_mpc_aircraftInstanceStruct *chartInstance, const mxArray *c4_b_u, const
   emlrtMsgIdentifier *c4_parentId);
static void c4_i_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId, char_T c4_y[4]);
static void c4_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static void c4_char(SFc4_mpc_aircraftInstanceStruct *chartInstance);
static void c4_eml_scalar_eg(SFc4_mpc_aircraftInstanceStruct *chartInstance);
static void c4_threshold(SFc4_mpc_aircraftInstanceStruct *chartInstance);
static void c4_b_eml_scalar_eg(SFc4_mpc_aircraftInstanceStruct *chartInstance);
static void c4_c_eml_scalar_eg(SFc4_mpc_aircraftInstanceStruct *chartInstance);
static void c4_d_eml_scalar_eg(SFc4_mpc_aircraftInstanceStruct *chartInstance);
static void c4_e_eml_scalar_eg(SFc4_mpc_aircraftInstanceStruct *chartInstance);
static void c4_f_eml_scalar_eg(SFc4_mpc_aircraftInstanceStruct *chartInstance);
static const mxArray *c4_emlrt_marshallOut(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const real_T c4_b_u[25]);
static const mxArray *c4_b_emlrt_marshallOut(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const real_T c4_b_u[5]);
static const mxArray *c4_c_emlrt_marshallOut(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const real_T c4_b_u[60]);
static const mxArray *c4_d_emlrt_marshallOut(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const real_T c4_b_u[12]);
static const mxArray *c4_e_emlrt_marshallOut(SFc4_mpc_aircraftInstanceStruct
  *chartInstance);
static const mxArray *c4_f_emlrt_marshallOut(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const c4_sflJsObR9dsqNm7nhVXYguC c4_b_u);
static void c4_j_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_zopt, const char_T *c4_identifier, real_T c4_y[5]);
static void c4_k_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[5]);
static void c4_l_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_output, const char_T *c4_identifier,
  c4_sTH1uaqaUOn3AI0zmFyKbPF *c4_y);
static void c4_m_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId,
  c4_sTH1uaqaUOn3AI0zmFyKbPF *c4_y);
static void c4_n_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId, char_T c4_y[912]);
static void c4_o_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId, char_T c4_y[21]);
static real_T c4_p_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_q_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId);
static real_T c4_r_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c4_toc, const char_T *c4_identifier);
static const mxArray *c4_r_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData);
static int32_T c4_s_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId);
static void c4_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData);
static uint8_T c4_t_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c4_b_is_active_c4_mpc_aircraft, const char_T
  *c4_identifier);
static uint8_T c4_u_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId);
static void init_dsm_address_info(SFc4_mpc_aircraftInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc4_mpc_aircraftInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c4_mpc_aircraft(SFc4_mpc_aircraftInstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc4_mpc_aircraft(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c4_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c4_is_active_c4_mpc_aircraft = 0U;
}

static void initialize_params_c4_mpc_aircraft(SFc4_mpc_aircraftInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c4_mpc_aircraft(SFc4_mpc_aircraftInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c4_mpc_aircraft(SFc4_mpc_aircraftInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c4_update_debugger_state_c4_mpc_aircraft
  (SFc4_mpc_aircraftInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c4_mpc_aircraft
  (SFc4_mpc_aircraftInstanceStruct *chartInstance)
{
  const mxArray *c4_st;
  const mxArray *c4_y = NULL;
  const mxArray *c4_b_y = NULL;
  real_T c4_hoistedGlobal;
  real_T c4_b_u;
  const mxArray *c4_c_y = NULL;
  real_T c4_b_hoistedGlobal;
  real_T c4_c_u;
  const mxArray *c4_d_y = NULL;
  const mxArray *c4_e_y = NULL;
  const mxArray *c4_f_y = NULL;
  uint8_T c4_c_hoistedGlobal;
  uint8_T c4_d_u;
  const mxArray *c4_g_y = NULL;
  c4_st = NULL;
  c4_st = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createcellmatrix(6, 1), false);
  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", *chartInstance->c4_feasRes, 0, 0U,
    1U, 0U, 1, 12), false);
  sf_mex_setcell(c4_y, 0, c4_b_y);
  c4_hoistedGlobal = *chartInstance->c4_iter;
  c4_b_u = c4_hoistedGlobal;
  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", &c4_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 1, c4_c_y);
  c4_b_hoistedGlobal = *chartInstance->c4_time;
  c4_c_u = c4_b_hoistedGlobal;
  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", &c4_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 2, c4_d_y);
  c4_e_y = NULL;
  sf_mex_assign(&c4_e_y, sf_mex_create("y", *chartInstance->c4_u, 0, 0U, 1U, 0U,
    1, 2), false);
  sf_mex_setcell(c4_y, 3, c4_e_y);
  c4_f_y = NULL;
  sf_mex_assign(&c4_f_y, sf_mex_create("y", *chartInstance->c4_xk1k, 0, 0U, 1U,
    0U, 1, 6), false);
  sf_mex_setcell(c4_y, 4, c4_f_y);
  c4_c_hoistedGlobal = chartInstance->c4_is_active_c4_mpc_aircraft;
  c4_d_u = c4_c_hoistedGlobal;
  c4_g_y = NULL;
  sf_mex_assign(&c4_g_y, sf_mex_create("y", &c4_d_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c4_y, 5, c4_g_y);
  sf_mex_assign(&c4_st, c4_y, false);
  return c4_st;
}

static void set_sim_state_c4_mpc_aircraft(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c4_st)
{
  const mxArray *c4_b_u;
  real_T c4_dv0[12];
  int32_T c4_i0;
  real_T c4_dv1[2];
  int32_T c4_i1;
  real_T c4_dv2[6];
  int32_T c4_i2;
  chartInstance->c4_doneDoubleBufferReInit = true;
  c4_b_u = sf_mex_dup(c4_st);
  c4_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("feasRes",
    c4_b_u, 0)), "feasRes", c4_dv0);
  for (c4_i0 = 0; c4_i0 < 12; c4_i0++) {
    (*chartInstance->c4_feasRes)[c4_i0] = c4_dv0[c4_i0];
  }

  *chartInstance->c4_iter = c4_r_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("iter", c4_b_u, 1)), "iter");
  *chartInstance->c4_time = c4_r_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("time", c4_b_u, 2)), "time");
  c4_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("u", c4_b_u, 3)),
                        "u", c4_dv1);
  for (c4_i1 = 0; c4_i1 < 2; c4_i1++) {
    (*chartInstance->c4_u)[c4_i1] = c4_dv1[c4_i1];
  }

  c4_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell("xk1k", c4_b_u, 4)),
                      "xk1k", c4_dv2);
  for (c4_i2 = 0; c4_i2 < 6; c4_i2++) {
    (*chartInstance->c4_xk1k)[c4_i2] = c4_dv2[c4_i2];
  }

  chartInstance->c4_is_active_c4_mpc_aircraft = c4_t_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell("is_active_c4_mpc_aircraft",
       c4_b_u, 5)), "is_active_c4_mpc_aircraft");
  sf_mex_destroy(&c4_b_u);
  c4_update_debugger_state_c4_mpc_aircraft(chartInstance);
  sf_mex_destroy(&c4_st);
}

static void finalize_c4_mpc_aircraft(SFc4_mpc_aircraftInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c4_mpc_aircraft(SFc4_mpc_aircraftInstanceStruct
  *chartInstance)
{
  int32_T c4_i3;
  int32_T c4_i4;
  int32_T c4_i5;
  int32_T c4_i6;
  int32_T c4_i7;
  int32_T c4_i8;
  int32_T c4_i9;
  int32_T c4_i10;
  int32_T c4_i11;
  int32_T c4_i12;
  int32_T c4_i13;
  int32_T c4_i14;
  int32_T c4_i15;
  int32_T c4_i16;
  int32_T c4_i17;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  for (c4_i3 = 0; c4_i3 < 6; c4_i3++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_xkk1)[c4_i3], 11U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  for (c4_i4 = 0; c4_i4 < 12; c4_i4++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_C)[c4_i4], 10U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  for (c4_i5 = 0; c4_i5 < 12; c4_i5++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_B)[c4_i5], 9U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  for (c4_i6 = 0; c4_i6 < 36; c4_i6++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_A)[c4_i6], 8U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  for (c4_i7 = 0; c4_i7 < 12; c4_i7++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_L)[c4_i7], 7U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  for (c4_i8 = 0; c4_i8 < 12; c4_i8++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_M)[c4_i8], 6U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  for (c4_i9 = 0; c4_i9 < 12; c4_i9++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_s)[c4_i9], 5U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  for (c4_i10 = 0; c4_i10 < 120; c4_i10++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_S)[c4_i10], 4U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  for (c4_i11 = 0; c4_i11 < 60; c4_i11++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_G)[c4_i11], 3U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  for (c4_i12 = 0; c4_i12 < 50; c4_i12++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_F)[c4_i12], 2U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  for (c4_i13 = 0; c4_i13 < 25; c4_i13++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_H)[c4_i13], 1U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  for (c4_i14 = 0; c4_i14 < 6; c4_i14++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_f)[c4_i14], 0U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  chartInstance->c4_sfEvent = CALL_EVENT;
  c4_chartstep_c4_mpc_aircraft(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_mpc_aircraftMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c4_i15 = 0; c4_i15 < 2; c4_i15++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_u)[c4_i15], 12U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  for (c4_i16 = 0; c4_i16 < 12; c4_i16++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_feasRes)[c4_i16], 13U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  for (c4_i17 = 0; c4_i17 < 6; c4_i17++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c4_xk1k)[c4_i17], 14U, 1U, 0U,
                          chartInstance->c4_sfEvent, false);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_time, 15U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c4_iter, 16U, 1U, 0U,
                        chartInstance->c4_sfEvent, false);
}

static void mdl_start_c4_mpc_aircraft(SFc4_mpc_aircraftInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c4_chartstep_c4_mpc_aircraft(SFc4_mpc_aircraftInstanceStruct
  *chartInstance)
{
  int32_T c4_i18;
  real_T c4_b_f[6];
  int32_T c4_i19;
  real_T c4_b_H[25];
  int32_T c4_i20;
  real_T c4_b_F[50];
  int32_T c4_i21;
  real_T c4_b_G[60];
  int32_T c4_i22;
  real_T c4_b_S[120];
  int32_T c4_i23;
  real_T c4_b_s[12];
  int32_T c4_i24;
  real_T c4_b_M[12];
  int32_T c4_i25;
  real_T c4_b_L[12];
  int32_T c4_i26;
  real_T c4_b_A[36];
  int32_T c4_i27;
  real_T c4_b_B[12];
  int32_T c4_i28;
  real_T c4_b_C[12];
  int32_T c4_i29;
  real_T c4_b_xkk1[6];
  uint32_T c4_debug_family_var_map[31];
  c4_sflJsObR9dsqNm7nhVXYguC c4_options;
  real_T c4_zopt[5];
  real_T c4_mess[912];
  c4_sTH1uaqaUOn3AI0zmFyKbPF c4_output;
  real_T c4_nu;
  real_T c4_ny;
  real_T c4_u0[2];
  real_T c4_y[2];
  real_T c4_xkk[6];
  real_T c4_p[10];
  real_T c4_b[12];
  real_T c4_h[5];
  char_T c4_b_mess[912];
  real_T c4_nargin = 12.0;
  real_T c4_nargout = 5.0;
  real_T c4_b_u[2];
  real_T c4_b_feasRes[12];
  real_T c4_b_xk1k[6];
  real_T c4_b_time;
  real_T c4_b_iter;
  int32_T c4_i30;
  static char_T c4_cv0[21] = { 'i', 'n', 't', 'e', 'r', 'i', 'o', 'r', '-', 'p',
    'o', 'i', 'n', 't', '-', 'c', 'o', 'n', 'v', 'e', 'x' };

  int32_T c4_i31;
  static char_T c4_cv1[4] = { 'n', 'o', 'n', 'e' };

  int32_T c4_i32;
  int32_T c4_i33;
  int32_T c4_i34;
  int32_T c4_i35;
  int32_T c4_i36;
  int32_T c4_i37;
  int32_T c4_i38;
  int32_T c4_i39;
  real_T c4_a[12];
  int32_T c4_i40;
  real_T c4_b_b[6];
  int32_T c4_i41;
  real_T c4_b_y[2];
  int32_T c4_i42;
  int32_T c4_i43;
  int32_T c4_i44;
  real_T c4_b_a[12];
  int32_T c4_i45;
  int32_T c4_i46;
  real_T c4_c_y[6];
  int32_T c4_i47;
  int32_T c4_i48;
  int32_T c4_i49;
  int32_T c4_i50;
  int32_T c4_i51;
  int32_T c4_i52;
  int32_T c4_i53;
  real_T c4_c_a[120];
  int32_T c4_i54;
  real_T c4_c_b[10];
  int32_T c4_i55;
  real_T c4_d_y[12];
  int32_T c4_i56;
  int32_T c4_i57;
  int32_T c4_i58;
  int32_T c4_i59;
  real_T c4_d_a[50];
  int32_T c4_i60;
  int32_T c4_i61;
  int32_T c4_i62;
  int32_T c4_i63;
  real_T c4_c_C[5];
  int32_T c4_i64;
  int32_T c4_i65;
  int32_T c4_i66;
  int32_T c4_i67;
  int32_T c4_i68;
  int32_T c4_i69;
  const mxArray *c4_b_output = NULL;
  const mxArray *c4_unusedU2 = NULL;
  const mxArray *c4_unusedU1 = NULL;
  const mxArray *c4_b_zopt = NULL;
  real_T c4_dv3[5];
  int32_T c4_i70;
  const mxArray *c4_b_unusedU1 = NULL;
  const mxArray *c4_b_unusedU2 = NULL;
  c4_sTH1uaqaUOn3AI0zmFyKbPF c4_r0;
  int32_T c4_i71;
  real_T c4_e_a[60];
  int32_T c4_i72;
  int32_T c4_i73;
  int32_T c4_i74;
  int32_T c4_i75;
  int32_T c4_i76;
  int32_T c4_i77;
  int32_T c4_i78;
  real_T c4_f_a[36];
  int32_T c4_i79;
  int32_T c4_i80;
  int32_T c4_i81;
  int32_T c4_i82;
  int32_T c4_i83;
  int32_T c4_i84;
  int32_T c4_i85;
  real_T c4_e_y[6];
  int32_T c4_i86;
  int32_T c4_i87;
  int32_T c4_i88;
  int32_T c4_i89;
  int32_T c4_i90;
  int32_T c4_i91;
  int32_T c4_i92;
  int32_T c4_i93;
  int32_T c4_i94;
  int32_T c4_i95;
  int32_T c4_i96;
  int32_T c4_i97;
  int32_T c4_i98;
  int32_T c4_i99;
  int32_T c4_i100;
  int32_T c4_i101;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
  for (c4_i18 = 0; c4_i18 < 6; c4_i18++) {
    c4_b_f[c4_i18] = (*chartInstance->c4_f)[c4_i18];
  }

  for (c4_i19 = 0; c4_i19 < 25; c4_i19++) {
    c4_b_H[c4_i19] = (*chartInstance->c4_H)[c4_i19];
  }

  for (c4_i20 = 0; c4_i20 < 50; c4_i20++) {
    c4_b_F[c4_i20] = (*chartInstance->c4_F)[c4_i20];
  }

  for (c4_i21 = 0; c4_i21 < 60; c4_i21++) {
    c4_b_G[c4_i21] = (*chartInstance->c4_G)[c4_i21];
  }

  for (c4_i22 = 0; c4_i22 < 120; c4_i22++) {
    c4_b_S[c4_i22] = (*chartInstance->c4_S)[c4_i22];
  }

  for (c4_i23 = 0; c4_i23 < 12; c4_i23++) {
    c4_b_s[c4_i23] = (*chartInstance->c4_s)[c4_i23];
  }

  for (c4_i24 = 0; c4_i24 < 12; c4_i24++) {
    c4_b_M[c4_i24] = (*chartInstance->c4_M)[c4_i24];
  }

  for (c4_i25 = 0; c4_i25 < 12; c4_i25++) {
    c4_b_L[c4_i25] = (*chartInstance->c4_L)[c4_i25];
  }

  for (c4_i26 = 0; c4_i26 < 36; c4_i26++) {
    c4_b_A[c4_i26] = (*chartInstance->c4_A)[c4_i26];
  }

  for (c4_i27 = 0; c4_i27 < 12; c4_i27++) {
    c4_b_B[c4_i27] = (*chartInstance->c4_B)[c4_i27];
  }

  for (c4_i28 = 0; c4_i28 < 12; c4_i28++) {
    c4_b_C[c4_i28] = (*chartInstance->c4_C)[c4_i28];
  }

  for (c4_i29 = 0; c4_i29 < 6; c4_i29++) {
    c4_b_xkk1[c4_i29] = (*chartInstance->c4_xkk1)[c4_i29];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 31U, 32U, c4_debug_family_names,
    c4_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_options, 0U, c4_q_sf_marshallOut,
    c4_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_zopt, 1U, c4_m_sf_marshallOut,
    c4_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_mess, MAX_uint32_T, c4_p_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_output, 3U, c4_o_sf_marshallOut,
    c4_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_nu, 4U, c4_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c4_ny, 5U, c4_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_u0, 6U, c4_d_sf_marshallOut,
    c4_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_y, 7U, c4_d_sf_marshallOut,
    c4_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_xkk, 8U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_p, 9U, c4_n_sf_marshallOut,
    c4_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_b, 10U, c4_c_sf_marshallOut,
    c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_h, 11U, c4_m_sf_marshallOut,
    c4_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_b_mess, MAX_uint32_T,
    c4_l_sf_marshallOut, c4_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargin, 12U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_nargout, 13U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_b_f, 14U, c4_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_b_H, 15U, c4_k_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_b_F, 16U, c4_j_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_b_G, 17U, c4_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_b_S, 18U, c4_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_b_s, 19U, c4_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_b_M, 20U, c4_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_b_L, 21U, c4_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_b_A, 22U, c4_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_b_B, 23U, c4_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_b_C, 24U, c4_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c4_b_xkk1, 25U, c4_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_b_u, 26U, c4_d_sf_marshallOut,
    c4_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_b_feasRes, 27U, c4_c_sf_marshallOut,
    c4_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c4_b_xk1k, 28U, c4_b_sf_marshallOut,
    c4_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_b_time, 29U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c4_b_iter, 30U, c4_sf_marshallOut,
    c4_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 7);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 8);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 9);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 10);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 11);
  for (c4_i30 = 0; c4_i30 < 21; c4_i30++) {
    c4_options.Algorithm[c4_i30] = c4_cv0[c4_i30];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 12);
  c4_options.MaxIter = 1000.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 13);
  c4_options.TolCon = 1.0E-12;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 14);
  c4_options.TolFun = 1.0E-12;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 15);
  c4_options.TolX = 1.0E-12;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 16);
  for (c4_i31 = 0; c4_i31 < 4; c4_i31++) {
    c4_options.Display[c4_i31] = c4_cv1[c4_i31];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 17);
  for (c4_i32 = 0; c4_i32 < 5; c4_i32++) {
    c4_zopt[c4_i32] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 18);
  c4_b_time = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 19);
  c4_b_iter = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 20);
  for (c4_i33 = 0; c4_i33 < 912; c4_i33++) {
    c4_mess[c4_i33] = 0.0;
  }

  _SFD_SYMBOL_SWITCH(2U, 2U);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 21);
  c4_char(chartInstance);
  for (c4_i34 = 0; c4_i34 < 912; c4_i34++) {
    c4_b_mess[c4_i34] = '\x00';
  }

  _SFD_SYMBOL_SWITCH(2U, 12U);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 23);
  for (c4_i35 = 0; c4_i35 < 912; c4_i35++) {
    c4_output.message[c4_i35] = c4_b_mess[c4_i35];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 24);
  for (c4_i36 = 0; c4_i36 < 21; c4_i36++) {
    c4_output.algorithm[c4_i36] = c4_cv0[c4_i36];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 25);
  c4_output.firstorderopt = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 26);
  c4_output.constrviolation = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 27);
  c4_output.iterations = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 28);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 31);
  c4_nu = 2.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 31);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 32);
  c4_ny = 2.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 33);
  for (c4_i37 = 0; c4_i37 < 2; c4_i37++) {
    c4_u0[c4_i37] = c4_b_f[c4_i37];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 34);
  for (c4_i38 = 0; c4_i38 < 2; c4_i38++) {
    c4_y[c4_i38] = c4_b_f[c4_i38 + 2];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 36);
  for (c4_i39 = 0; c4_i39 < 12; c4_i39++) {
    c4_a[c4_i39] = c4_b_C[c4_i39];
  }

  for (c4_i40 = 0; c4_i40 < 6; c4_i40++) {
    c4_b_b[c4_i40] = c4_b_xkk1[c4_i40];
  }

  c4_eml_scalar_eg(chartInstance);
  c4_eml_scalar_eg(chartInstance);
  c4_threshold(chartInstance);
  for (c4_i41 = 0; c4_i41 < 2; c4_i41++) {
    c4_b_y[c4_i41] = 0.0;
    c4_i42 = 0;
    for (c4_i43 = 0; c4_i43 < 6; c4_i43++) {
      c4_b_y[c4_i41] += c4_a[c4_i42 + c4_i41] * c4_b_b[c4_i43];
      c4_i42 += 2;
    }
  }

  for (c4_i44 = 0; c4_i44 < 12; c4_i44++) {
    c4_b_a[c4_i44] = c4_b_M[c4_i44];
  }

  for (c4_i45 = 0; c4_i45 < 2; c4_i45++) {
    c4_b_y[c4_i45] = c4_y[c4_i45] - c4_b_y[c4_i45];
  }

  c4_b_eml_scalar_eg(chartInstance);
  c4_b_eml_scalar_eg(chartInstance);
  c4_threshold(chartInstance);
  for (c4_i46 = 0; c4_i46 < 6; c4_i46++) {
    c4_c_y[c4_i46] = 0.0;
    c4_i47 = 0;
    for (c4_i48 = 0; c4_i48 < 2; c4_i48++) {
      c4_c_y[c4_i46] += c4_b_a[c4_i47 + c4_i46] * c4_b_y[c4_i48];
      c4_i47 += 6;
    }
  }

  for (c4_i49 = 0; c4_i49 < 6; c4_i49++) {
    c4_xkk[c4_i49] = c4_b_xkk1[c4_i49] + c4_c_y[c4_i49];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 39);
  for (c4_i50 = 0; c4_i50 < 2; c4_i50++) {
    c4_p[c4_i50] = c4_b_f[c4_i50];
  }

  for (c4_i51 = 0; c4_i51 < 6; c4_i51++) {
    c4_p[c4_i51 + 2] = c4_xkk[c4_i51];
  }

  for (c4_i52 = 0; c4_i52 < 2; c4_i52++) {
    c4_p[c4_i52 + 8] = c4_b_f[c4_i52 + 4];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 41);
  for (c4_i53 = 0; c4_i53 < 120; c4_i53++) {
    c4_c_a[c4_i53] = c4_b_S[c4_i53];
  }

  for (c4_i54 = 0; c4_i54 < 10; c4_i54++) {
    c4_c_b[c4_i54] = c4_p[c4_i54];
  }

  c4_c_eml_scalar_eg(chartInstance);
  c4_c_eml_scalar_eg(chartInstance);
  c4_threshold(chartInstance);
  for (c4_i55 = 0; c4_i55 < 12; c4_i55++) {
    c4_d_y[c4_i55] = 0.0;
    c4_i56 = 0;
    for (c4_i57 = 0; c4_i57 < 10; c4_i57++) {
      c4_d_y[c4_i55] += c4_c_a[c4_i56 + c4_i55] * c4_c_b[c4_i57];
      c4_i56 += 12;
    }
  }

  for (c4_i58 = 0; c4_i58 < 12; c4_i58++) {
    c4_b[c4_i58] = c4_d_y[c4_i58] + c4_b_s[c4_i58];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 42);
  for (c4_i59 = 0; c4_i59 < 50; c4_i59++) {
    c4_d_a[c4_i59] = c4_b_F[c4_i59];
  }

  for (c4_i60 = 0; c4_i60 < 10; c4_i60++) {
    c4_c_b[c4_i60] = c4_p[c4_i60];
  }

  c4_d_eml_scalar_eg(chartInstance);
  c4_d_eml_scalar_eg(chartInstance);
  for (c4_i61 = 0; c4_i61 < 5; c4_i61++) {
    c4_h[c4_i61] = 0.0;
  }

  for (c4_i62 = 0; c4_i62 < 5; c4_i62++) {
    c4_h[c4_i62] = 0.0;
  }

  for (c4_i63 = 0; c4_i63 < 5; c4_i63++) {
    c4_c_C[c4_i63] = c4_h[c4_i63];
  }

  for (c4_i64 = 0; c4_i64 < 5; c4_i64++) {
    c4_h[c4_i64] = c4_c_C[c4_i64];
  }

  c4_threshold(chartInstance);
  for (c4_i65 = 0; c4_i65 < 5; c4_i65++) {
    c4_c_C[c4_i65] = c4_h[c4_i65];
  }

  for (c4_i66 = 0; c4_i66 < 5; c4_i66++) {
    c4_h[c4_i66] = c4_c_C[c4_i66];
  }

  for (c4_i67 = 0; c4_i67 < 5; c4_i67++) {
    c4_h[c4_i67] = 0.0;
    c4_i68 = 0;
    for (c4_i69 = 0; c4_i69 < 10; c4_i69++) {
      c4_h[c4_i67] += c4_d_a[c4_i68 + c4_i67] * c4_c_b[c4_i69];
      c4_i68 += 5;
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 43);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "tic", 0U, 0U);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 44);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "quadprog", 4U, 10U, 14,
                    c4_emlrt_marshallOut(chartInstance, c4_b_H), 14,
                    c4_b_emlrt_marshallOut(chartInstance, c4_h), 14,
                    c4_c_emlrt_marshallOut(chartInstance, c4_b_G), 14,
                    c4_d_emlrt_marshallOut(chartInstance, c4_b), 14,
                    c4_e_emlrt_marshallOut(chartInstance), 14,
                    c4_e_emlrt_marshallOut(chartInstance), 14,
                    c4_e_emlrt_marshallOut(chartInstance), 14,
                    c4_e_emlrt_marshallOut(chartInstance), 14,
                    c4_e_emlrt_marshallOut(chartInstance), 14,
                    c4_f_emlrt_marshallOut(chartInstance, c4_options),
                    &c4_b_zopt, &c4_unusedU1, &c4_unusedU2, &c4_b_output);
  c4_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_zopt), "zopt", c4_dv3);
  for (c4_i70 = 0; c4_i70 < 5; c4_i70++) {
    c4_zopt[c4_i70] = c4_dv3[c4_i70];
  }

  sf_mex_assign(&c4_b_unusedU1, sf_mex_dup(c4_unusedU1), false);
  sf_mex_assign(&c4_b_unusedU2, sf_mex_dup(c4_unusedU2), false);
  c4_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_output), "output", &c4_r0);
  c4_output = c4_r0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 44);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 44);
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 46);
  c4_b_time = c4_r_emlrt_marshallIn(chartInstance, sf_mex_call_debug
    (sfGlobalDebugInstanceStruct, "toc", 1U, 0U), "toc");
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 47);
  for (c4_i71 = 0; c4_i71 < 60; c4_i71++) {
    c4_e_a[c4_i71] = c4_b_G[c4_i71];
  }

  for (c4_i72 = 0; c4_i72 < 5; c4_i72++) {
    c4_c_C[c4_i72] = c4_zopt[c4_i72];
  }

  c4_e_eml_scalar_eg(chartInstance);
  c4_e_eml_scalar_eg(chartInstance);
  c4_threshold(chartInstance);
  for (c4_i73 = 0; c4_i73 < 12; c4_i73++) {
    c4_d_y[c4_i73] = 0.0;
    c4_i74 = 0;
    for (c4_i75 = 0; c4_i75 < 5; c4_i75++) {
      c4_d_y[c4_i73] += c4_e_a[c4_i74 + c4_i73] * c4_c_C[c4_i75];
      c4_i74 += 12;
    }
  }

  for (c4_i76 = 0; c4_i76 < 12; c4_i76++) {
    c4_b_feasRes[c4_i76] = c4_d_y[c4_i76] - c4_b[c4_i76];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 48);
  c4_b_iter = c4_output.iterations;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 50);
  c4_nu = 2.0;
  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 51);
  for (c4_i77 = 0; c4_i77 < 2; c4_i77++) {
    c4_b_u[c4_i77] = c4_zopt[c4_i77] + c4_u0[c4_i77];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, 53);
  for (c4_i78 = 0; c4_i78 < 36; c4_i78++) {
    c4_f_a[c4_i78] = c4_b_A[c4_i78];
  }

  for (c4_i79 = 0; c4_i79 < 6; c4_i79++) {
    c4_b_b[c4_i79] = c4_b_xkk1[c4_i79];
  }

  c4_f_eml_scalar_eg(chartInstance);
  c4_f_eml_scalar_eg(chartInstance);
  c4_threshold(chartInstance);
  for (c4_i80 = 0; c4_i80 < 6; c4_i80++) {
    c4_c_y[c4_i80] = 0.0;
    c4_i81 = 0;
    for (c4_i82 = 0; c4_i82 < 6; c4_i82++) {
      c4_c_y[c4_i80] += c4_f_a[c4_i81 + c4_i80] * c4_b_b[c4_i82];
      c4_i81 += 6;
    }
  }

  for (c4_i83 = 0; c4_i83 < 12; c4_i83++) {
    c4_b_a[c4_i83] = c4_b_B[c4_i83];
  }

  for (c4_i84 = 0; c4_i84 < 2; c4_i84++) {
    c4_b_y[c4_i84] = c4_b_u[c4_i84];
  }

  c4_b_eml_scalar_eg(chartInstance);
  c4_b_eml_scalar_eg(chartInstance);
  c4_threshold(chartInstance);
  for (c4_i85 = 0; c4_i85 < 6; c4_i85++) {
    c4_e_y[c4_i85] = 0.0;
    c4_i86 = 0;
    for (c4_i87 = 0; c4_i87 < 2; c4_i87++) {
      c4_e_y[c4_i85] += c4_b_a[c4_i86 + c4_i85] * c4_b_y[c4_i87];
      c4_i86 += 6;
    }
  }

  for (c4_i88 = 0; c4_i88 < 12; c4_i88++) {
    c4_a[c4_i88] = c4_b_C[c4_i88];
  }

  for (c4_i89 = 0; c4_i89 < 6; c4_i89++) {
    c4_b_b[c4_i89] = c4_b_xkk1[c4_i89];
  }

  c4_eml_scalar_eg(chartInstance);
  c4_eml_scalar_eg(chartInstance);
  c4_threshold(chartInstance);
  for (c4_i90 = 0; c4_i90 < 2; c4_i90++) {
    c4_b_y[c4_i90] = 0.0;
    c4_i91 = 0;
    for (c4_i92 = 0; c4_i92 < 6; c4_i92++) {
      c4_b_y[c4_i90] += c4_a[c4_i91 + c4_i90] * c4_b_b[c4_i92];
      c4_i91 += 2;
    }
  }

  for (c4_i93 = 0; c4_i93 < 12; c4_i93++) {
    c4_b_a[c4_i93] = c4_b_L[c4_i93];
  }

  for (c4_i94 = 0; c4_i94 < 2; c4_i94++) {
    c4_b_y[c4_i94] = c4_y[c4_i94] - c4_b_y[c4_i94];
  }

  c4_b_eml_scalar_eg(chartInstance);
  c4_b_eml_scalar_eg(chartInstance);
  c4_threshold(chartInstance);
  for (c4_i95 = 0; c4_i95 < 6; c4_i95++) {
    c4_b_b[c4_i95] = 0.0;
    c4_i96 = 0;
    for (c4_i97 = 0; c4_i97 < 2; c4_i97++) {
      c4_b_b[c4_i95] += c4_b_a[c4_i96 + c4_i95] * c4_b_y[c4_i97];
      c4_i96 += 6;
    }
  }

  for (c4_i98 = 0; c4_i98 < 6; c4_i98++) {
    c4_b_xk1k[c4_i98] = (c4_c_y[c4_i98] + c4_e_y[c4_i98]) + c4_b_b[c4_i98];
  }

  _SFD_EML_CALL(0U, chartInstance->c4_sfEvent, -53);
  _SFD_SYMBOL_SCOPE_POP();
  sf_mex_destroy(&c4_b_unusedU1);
  sf_mex_destroy(&c4_b_unusedU2);
  sf_mex_destroy(&c4_b_zopt);
  sf_mex_destroy(&c4_unusedU1);
  sf_mex_destroy(&c4_unusedU2);
  sf_mex_destroy(&c4_b_output);
  for (c4_i99 = 0; c4_i99 < 2; c4_i99++) {
    (*chartInstance->c4_u)[c4_i99] = c4_b_u[c4_i99];
  }

  for (c4_i100 = 0; c4_i100 < 12; c4_i100++) {
    (*chartInstance->c4_feasRes)[c4_i100] = c4_b_feasRes[c4_i100];
  }

  for (c4_i101 = 0; c4_i101 < 6; c4_i101++) {
    (*chartInstance->c4_xk1k)[c4_i101] = c4_b_xk1k[c4_i101];
  }

  *chartInstance->c4_time = c4_b_time;
  *chartInstance->c4_iter = c4_b_iter;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c4_sfEvent);
}

static void initSimStructsc4_mpc_aircraft(SFc4_mpc_aircraftInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c4_machineNumber, uint32_T
  c4_chartNumber, uint32_T c4_instanceNumber)
{
  (void)c4_machineNumber;
  (void)c4_chartNumber;
  (void)c4_instanceNumber;
}

static const mxArray *c4_sf_marshallOut(void *chartInstanceVoid, void *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  real_T c4_b_u;
  const mxArray *c4_y = NULL;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_b_u = *(real_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static void c4_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_toc;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_toc = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_toc), &c4_thisId);
  sf_mex_destroy(&c4_toc);
  *(real_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_b_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i102;
  real_T c4_b_u[6];
  const mxArray *c4_y = NULL;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  for (c4_i102 = 0; c4_i102 < 6; c4_i102++) {
    c4_b_u[c4_i102] = (*(real_T (*)[6])c4_inData)[c4_i102];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 1, 6), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static void c4_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_xk1k, const char_T *c4_identifier, real_T c4_y[6])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_xk1k), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_b_xk1k);
}

static void c4_b_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[6])
{
  real_T c4_dv4[6];
  int32_T c4_i103;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_b_u), c4_dv4, 1, 0, 0U, 1, 0U, 1, 6);
  for (c4_i103 = 0; c4_i103 < 6; c4_i103++) {
    c4_y[c4_i103] = c4_dv4[c4_i103];
  }

  sf_mex_destroy(&c4_b_u);
}

static void c4_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_xk1k;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[6];
  int32_T c4_i104;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_b_xk1k = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_xk1k), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_b_xk1k);
  for (c4_i104 = 0; c4_i104 < 6; c4_i104++) {
    (*(real_T (*)[6])c4_outData)[c4_i104] = c4_y[c4_i104];
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_c_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i105;
  real_T c4_b_u[12];
  const mxArray *c4_y = NULL;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  for (c4_i105 = 0; c4_i105 < 12; c4_i105++) {
    c4_b_u[c4_i105] = (*(real_T (*)[12])c4_inData)[c4_i105];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 1, 12), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static void c4_c_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_feasRes, const char_T *c4_identifier, real_T c4_y[12])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_feasRes), &c4_thisId,
                        c4_y);
  sf_mex_destroy(&c4_b_feasRes);
}

static void c4_d_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[12])
{
  real_T c4_dv5[12];
  int32_T c4_i106;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_b_u), c4_dv5, 1, 0, 0U, 1, 0U, 1, 12);
  for (c4_i106 = 0; c4_i106 < 12; c4_i106++) {
    c4_y[c4_i106] = c4_dv5[c4_i106];
  }

  sf_mex_destroy(&c4_b_u);
}

static void c4_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_feasRes;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[12];
  int32_T c4_i107;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_b_feasRes = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_feasRes), &c4_thisId,
                        c4_y);
  sf_mex_destroy(&c4_b_feasRes);
  for (c4_i107 = 0; c4_i107 < 12; c4_i107++) {
    (*(real_T (*)[12])c4_outData)[c4_i107] = c4_y[c4_i107];
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_d_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i108;
  real_T c4_b_u[2];
  const mxArray *c4_y = NULL;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  for (c4_i108 = 0; c4_i108 < 2; c4_i108++) {
    c4_b_u[c4_i108] = (*(real_T (*)[2])c4_inData)[c4_i108];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static void c4_e_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const char_T *c4_identifier, real_T c4_y[2])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_u), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_b_u);
}

static void c4_f_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[2])
{
  real_T c4_dv6[2];
  int32_T c4_i109;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_b_u), c4_dv6, 1, 0, 0U, 1, 0U, 1, 2);
  for (c4_i109 = 0; c4_i109 < 2; c4_i109++) {
    c4_y[c4_i109] = c4_dv6[c4_i109];
  }

  sf_mex_destroy(&c4_b_u);
}

static void c4_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_u;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[2];
  int32_T c4_i110;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_b_u = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_u), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_b_u);
  for (c4_i110 = 0; c4_i110 < 2; c4_i110++) {
    (*(real_T (*)[2])c4_outData)[c4_i110] = c4_y[c4_i110];
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_e_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i111;
  int32_T c4_i112;
  int32_T c4_i113;
  real_T c4_b_u[12];
  const mxArray *c4_y = NULL;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_i111 = 0;
  for (c4_i112 = 0; c4_i112 < 6; c4_i112++) {
    for (c4_i113 = 0; c4_i113 < 2; c4_i113++) {
      c4_b_u[c4_i113 + c4_i111] = (*(real_T (*)[12])c4_inData)[c4_i113 + c4_i111];
    }

    c4_i111 += 2;
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 2, 2, 6), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static const mxArray *c4_f_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i114;
  int32_T c4_i115;
  int32_T c4_i116;
  real_T c4_b_u[12];
  const mxArray *c4_y = NULL;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_i114 = 0;
  for (c4_i115 = 0; c4_i115 < 2; c4_i115++) {
    for (c4_i116 = 0; c4_i116 < 6; c4_i116++) {
      c4_b_u[c4_i116 + c4_i114] = (*(real_T (*)[12])c4_inData)[c4_i116 + c4_i114];
    }

    c4_i114 += 6;
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 2, 6, 2), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static const mxArray *c4_g_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i117;
  int32_T c4_i118;
  int32_T c4_i119;
  real_T c4_b_u[36];
  const mxArray *c4_y = NULL;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_i117 = 0;
  for (c4_i118 = 0; c4_i118 < 6; c4_i118++) {
    for (c4_i119 = 0; c4_i119 < 6; c4_i119++) {
      c4_b_u[c4_i119 + c4_i117] = (*(real_T (*)[36])c4_inData)[c4_i119 + c4_i117];
    }

    c4_i117 += 6;
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 2, 6, 6), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static const mxArray *c4_h_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i120;
  int32_T c4_i121;
  int32_T c4_i122;
  real_T c4_b_u[120];
  const mxArray *c4_y = NULL;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_i120 = 0;
  for (c4_i121 = 0; c4_i121 < 10; c4_i121++) {
    for (c4_i122 = 0; c4_i122 < 12; c4_i122++) {
      c4_b_u[c4_i122 + c4_i120] = (*(real_T (*)[120])c4_inData)[c4_i122 +
        c4_i120];
    }

    c4_i120 += 12;
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 2, 12, 10),
                false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static const mxArray *c4_i_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i123;
  int32_T c4_i124;
  int32_T c4_i125;
  real_T c4_b_u[60];
  const mxArray *c4_y = NULL;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_i123 = 0;
  for (c4_i124 = 0; c4_i124 < 5; c4_i124++) {
    for (c4_i125 = 0; c4_i125 < 12; c4_i125++) {
      c4_b_u[c4_i125 + c4_i123] = (*(real_T (*)[60])c4_inData)[c4_i125 + c4_i123];
    }

    c4_i123 += 12;
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 2, 12, 5),
                false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static const mxArray *c4_j_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i126;
  int32_T c4_i127;
  int32_T c4_i128;
  real_T c4_b_u[50];
  const mxArray *c4_y = NULL;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_i126 = 0;
  for (c4_i127 = 0; c4_i127 < 10; c4_i127++) {
    for (c4_i128 = 0; c4_i128 < 5; c4_i128++) {
      c4_b_u[c4_i128 + c4_i126] = (*(real_T (*)[50])c4_inData)[c4_i128 + c4_i126];
    }

    c4_i126 += 5;
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 2, 5, 10),
                false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static const mxArray *c4_k_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i129;
  int32_T c4_i130;
  int32_T c4_i131;
  real_T c4_b_u[25];
  const mxArray *c4_y = NULL;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_i129 = 0;
  for (c4_i130 = 0; c4_i130 < 5; c4_i130++) {
    for (c4_i131 = 0; c4_i131 < 5; c4_i131++) {
      c4_b_u[c4_i131 + c4_i129] = (*(real_T (*)[25])c4_inData)[c4_i131 + c4_i129];
    }

    c4_i129 += 5;
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 2, 5, 5), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static const mxArray *c4_l_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i132;
  char_T c4_b_u[912];
  const mxArray *c4_y = NULL;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  for (c4_i132 = 0; c4_i132 < 912; c4_i132++) {
    c4_b_u[c4_i132] = (*(char_T (*)[912])c4_inData)[c4_i132];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_b_u, 10, 0U, 1U, 0U, 2, 1, 912),
                false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static void c4_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_mess;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  char_T c4_y[912];
  int32_T c4_i133;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_mess = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_mess), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_mess);
  for (c4_i133 = 0; c4_i133 < 912; c4_i133++) {
    (*(char_T (*)[912])c4_outData)[c4_i133] = c4_y[c4_i133];
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_m_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i134;
  real_T c4_b_u[5];
  const mxArray *c4_y = NULL;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  for (c4_i134 = 0; c4_i134 < 5; c4_i134++) {
    c4_b_u[c4_i134] = (*(real_T (*)[5])c4_inData)[c4_i134];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 1, 5), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static void c4_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_zopt;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[5];
  int32_T c4_i135;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_zopt = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_zopt), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_zopt);
  for (c4_i135 = 0; c4_i135 < 5; c4_i135++) {
    (*(real_T (*)[5])c4_outData)[c4_i135] = c4_y[c4_i135];
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_n_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i136;
  real_T c4_b_u[10];
  const mxArray *c4_y = NULL;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  for (c4_i136 = 0; c4_i136 < 10; c4_i136++) {
    c4_b_u[c4_i136] = (*(real_T (*)[10])c4_inData)[c4_i136];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 1, 10), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static void c4_g_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[10])
{
  real_T c4_dv7[10];
  int32_T c4_i137;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_b_u), c4_dv7, 1, 0, 0U, 1, 0U, 1, 10);
  for (c4_i137 = 0; c4_i137 < 10; c4_i137++) {
    c4_y[c4_i137] = c4_dv7[c4_i137];
  }

  sf_mex_destroy(&c4_b_u);
}

static void c4_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_p;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  real_T c4_y[10];
  int32_T c4_i138;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_p = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_p), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_p);
  for (c4_i138 = 0; c4_i138 < 10; c4_i138++) {
    (*(real_T (*)[10])c4_outData)[c4_i138] = c4_y[c4_i138];
  }

  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_o_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData;
  c4_sTH1uaqaUOn3AI0zmFyKbPF c4_b_u;
  const mxArray *c4_y = NULL;
  int32_T c4_i139;
  char_T c4_c_u[912];
  const mxArray *c4_b_y = NULL;
  int32_T c4_i140;
  char_T c4_d_u[21];
  const mxArray *c4_c_y = NULL;
  real_T c4_e_u;
  const mxArray *c4_d_y = NULL;
  real_T c4_f_u;
  const mxArray *c4_e_y = NULL;
  real_T c4_g_u;
  const mxArray *c4_f_y = NULL;
  const mxArray *c4_g_y = NULL;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_mxArrayOutData = NULL;
  c4_b_u = *(c4_sTH1uaqaUOn3AI0zmFyKbPF *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  for (c4_i139 = 0; c4_i139 < 912; c4_i139++) {
    c4_c_u[c4_i139] = c4_b_u.message[c4_i139];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_c_u, 10, 0U, 1U, 0U, 2, 1, 912),
                false);
  sf_mex_addfield(c4_y, c4_b_y, "message", "message", 0);
  for (c4_i140 = 0; c4_i140 < 21; c4_i140++) {
    c4_d_u[c4_i140] = c4_b_u.algorithm[c4_i140];
  }

  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", c4_d_u, 10, 0U, 1U, 0U, 2, 1, 21),
                false);
  sf_mex_addfield(c4_y, c4_c_y, "algorithm", "algorithm", 0);
  c4_e_u = c4_b_u.firstorderopt;
  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", &c4_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_d_y, "firstorderopt", "firstorderopt", 0);
  c4_f_u = c4_b_u.constrviolation;
  c4_e_y = NULL;
  sf_mex_assign(&c4_e_y, sf_mex_create("y", &c4_f_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_e_y, "constrviolation", "constrviolation", 0);
  c4_g_u = c4_b_u.iterations;
  c4_f_y = NULL;
  sf_mex_assign(&c4_f_y, sf_mex_create("y", &c4_g_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_f_y, "iterations", "iterations", 0);
  c4_g_y = NULL;
  sf_mex_assign(&c4_g_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  sf_mex_addfield(c4_y, c4_g_y, "cgiterations", "cgiterations", 0);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static void c4_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_output;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  c4_sTH1uaqaUOn3AI0zmFyKbPF c4_y;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_output = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_output), &c4_thisId, &c4_y);
  sf_mex_destroy(&c4_output);
  *(c4_sTH1uaqaUOn3AI0zmFyKbPF *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static const mxArray *c4_p_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_i141;
  real_T c4_b_u[912];
  const mxArray *c4_y = NULL;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  for (c4_i141 = 0; c4_i141 < 912; c4_i141++) {
    c4_b_u[c4_i141] = (*(real_T (*)[912])c4_inData)[c4_i141];
  }

  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 2, 1, 912),
                false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static const mxArray *c4_q_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData;
  c4_sflJsObR9dsqNm7nhVXYguC c4_b_u;
  const mxArray *c4_y = NULL;
  int32_T c4_i142;
  char_T c4_c_u[21];
  const mxArray *c4_b_y = NULL;
  real_T c4_d_u;
  const mxArray *c4_c_y = NULL;
  real_T c4_e_u;
  const mxArray *c4_d_y = NULL;
  real_T c4_f_u;
  const mxArray *c4_e_y = NULL;
  real_T c4_g_u;
  const mxArray *c4_f_y = NULL;
  int32_T c4_i143;
  char_T c4_h_u[4];
  const mxArray *c4_g_y = NULL;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_mxArrayOutData = NULL;
  c4_b_u = *(c4_sflJsObR9dsqNm7nhVXYguC *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  for (c4_i142 = 0; c4_i142 < 21; c4_i142++) {
    c4_c_u[c4_i142] = c4_b_u.Algorithm[c4_i142];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_c_u, 10, 0U, 1U, 0U, 2, 1, 21),
                false);
  sf_mex_addfield(c4_y, c4_b_y, "Algorithm", "Algorithm", 0);
  c4_d_u = c4_b_u.MaxIter;
  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", &c4_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_c_y, "MaxIter", "MaxIter", 0);
  c4_e_u = c4_b_u.TolCon;
  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", &c4_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_d_y, "TolCon", "TolCon", 0);
  c4_f_u = c4_b_u.TolFun;
  c4_e_y = NULL;
  sf_mex_assign(&c4_e_y, sf_mex_create("y", &c4_f_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_e_y, "TolFun", "TolFun", 0);
  c4_g_u = c4_b_u.TolX;
  c4_f_y = NULL;
  sf_mex_assign(&c4_f_y, sf_mex_create("y", &c4_g_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_f_y, "TolX", "TolX", 0);
  for (c4_i143 = 0; c4_i143 < 4; c4_i143++) {
    c4_h_u[c4_i143] = c4_b_u.Display[c4_i143];
  }

  c4_g_y = NULL;
  sf_mex_assign(&c4_g_y, sf_mex_create("y", c4_h_u, 10, 0U, 1U, 0U, 2, 1, 4),
                false);
  sf_mex_addfield(c4_y, c4_g_y, "Display", "Display", 0);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static c4_sflJsObR9dsqNm7nhVXYguC c4_h_emlrt_marshallIn
  (SFc4_mpc_aircraftInstanceStruct *chartInstance, const mxArray *c4_b_u, const
   emlrtMsgIdentifier *c4_parentId)
{
  c4_sflJsObR9dsqNm7nhVXYguC c4_y;
  emlrtMsgIdentifier c4_thisId;
  static const char * c4_fieldNames[6] = { "Algorithm", "MaxIter", "TolCon",
    "TolFun", "TolX", "Display" };

  c4_thisId.fParent = c4_parentId;
  sf_mex_check_struct(c4_parentId, c4_b_u, 6, c4_fieldNames, 0U, NULL);
  c4_thisId.fIdentifier = "Algorithm";
  c4_o_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c4_b_u,
    "Algorithm", "Algorithm", 0)), &c4_thisId, c4_y.Algorithm);
  c4_thisId.fIdentifier = "MaxIter";
  c4_y.MaxIter = c4_p_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c4_b_u, "MaxIter", "MaxIter", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "TolCon";
  c4_y.TolCon = c4_p_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c4_b_u, "TolCon", "TolCon", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "TolFun";
  c4_y.TolFun = c4_p_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c4_b_u, "TolFun", "TolFun", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "TolX";
  c4_y.TolX = c4_p_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield
    (c4_b_u, "TolX", "TolX", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "Display";
  c4_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c4_b_u,
    "Display", "Display", 0)), &c4_thisId, c4_y.Display);
  sf_mex_destroy(&c4_b_u);
  return c4_y;
}

static void c4_i_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId, char_T c4_y[4])
{
  char_T c4_cv2[4];
  int32_T c4_i144;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_b_u), c4_cv2, 1, 10, 0U, 1, 0U, 2, 1,
                4);
  for (c4_i144 = 0; c4_i144 < 4; c4_i144++) {
    c4_y[c4_i144] = c4_cv2[c4_i144];
  }

  sf_mex_destroy(&c4_b_u);
}

static void c4_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_options;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  c4_sflJsObR9dsqNm7nhVXYguC c4_y;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_options = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_options), &c4_thisId);
  sf_mex_destroy(&c4_options);
  *(c4_sflJsObR9dsqNm7nhVXYguC *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

const mxArray *sf_c4_mpc_aircraft_get_eml_resolved_functions_info(void)
{
  const mxArray *c4_nameCaptureInfo = NULL;
  c4_nameCaptureInfo = NULL;
  sf_mex_assign(&c4_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c4_nameCaptureInfo;
}

static void c4_char(SFc4_mpc_aircraftInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c4_eml_scalar_eg(SFc4_mpc_aircraftInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c4_threshold(SFc4_mpc_aircraftInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c4_b_eml_scalar_eg(SFc4_mpc_aircraftInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c4_c_eml_scalar_eg(SFc4_mpc_aircraftInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c4_d_eml_scalar_eg(SFc4_mpc_aircraftInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c4_e_eml_scalar_eg(SFc4_mpc_aircraftInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c4_f_eml_scalar_eg(SFc4_mpc_aircraftInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *c4_emlrt_marshallOut(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const real_T c4_b_u[25])
{
  const mxArray *c4_y = NULL;
  (void)chartInstance;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 2, 5, 5), false);
  return c4_y;
}

static const mxArray *c4_b_emlrt_marshallOut(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const real_T c4_b_u[5])
{
  const mxArray *c4_y = NULL;
  (void)chartInstance;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 1, 5), false);
  return c4_y;
}

static const mxArray *c4_c_emlrt_marshallOut(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const real_T c4_b_u[60])
{
  const mxArray *c4_y = NULL;
  (void)chartInstance;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 2, 12, 5),
                false);
  return c4_y;
}

static const mxArray *c4_d_emlrt_marshallOut(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const real_T c4_b_u[12])
{
  const mxArray *c4_y = NULL;
  (void)chartInstance;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", c4_b_u, 0, 0U, 1U, 0U, 1, 12), false);
  return c4_y;
}

static const mxArray *c4_e_emlrt_marshallOut(SFc4_mpc_aircraftInstanceStruct
  *chartInstance)
{
  const mxArray *c4_y = NULL;
  (void)chartInstance;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), false);
  return c4_y;
}

static const mxArray *c4_f_emlrt_marshallOut(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const c4_sflJsObR9dsqNm7nhVXYguC c4_b_u)
{
  const mxArray *c4_y;
  int32_T c4_i145;
  char_T c4_c_u[21];
  const mxArray *c4_b_y = NULL;
  real_T c4_d_u;
  const mxArray *c4_c_y = NULL;
  real_T c4_e_u;
  const mxArray *c4_d_y = NULL;
  real_T c4_f_u;
  const mxArray *c4_e_y = NULL;
  real_T c4_g_u;
  const mxArray *c4_f_y = NULL;
  int32_T c4_i146;
  char_T c4_h_u[4];
  const mxArray *c4_g_y = NULL;
  (void)chartInstance;
  c4_y = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createstruct("structure", 2, 1, 1), false);
  for (c4_i145 = 0; c4_i145 < 21; c4_i145++) {
    c4_c_u[c4_i145] = c4_b_u.Algorithm[c4_i145];
  }

  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", c4_c_u, 10, 0U, 1U, 0U, 2, 1, 21),
                false);
  sf_mex_addfield(c4_y, c4_b_y, "Algorithm", "Algorithm", 0);
  c4_d_u = c4_b_u.MaxIter;
  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", &c4_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_c_y, "MaxIter", "MaxIter", 0);
  c4_e_u = c4_b_u.TolCon;
  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", &c4_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_d_y, "TolCon", "TolCon", 0);
  c4_f_u = c4_b_u.TolFun;
  c4_e_y = NULL;
  sf_mex_assign(&c4_e_y, sf_mex_create("y", &c4_f_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_e_y, "TolFun", "TolFun", 0);
  c4_g_u = c4_b_u.TolX;
  c4_f_y = NULL;
  sf_mex_assign(&c4_f_y, sf_mex_create("y", &c4_g_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_addfield(c4_y, c4_f_y, "TolX", "TolX", 0);
  for (c4_i146 = 0; c4_i146 < 4; c4_i146++) {
    c4_h_u[c4_i146] = c4_b_u.Display[c4_i146];
  }

  c4_g_y = NULL;
  sf_mex_assign(&c4_g_y, sf_mex_create("y", c4_h_u, 10, 0U, 1U, 0U, 2, 1, 4),
                false);
  sf_mex_addfield(c4_y, c4_g_y, "Display", "Display", 0);
  return c4_y;
}

static void c4_j_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_zopt, const char_T *c4_identifier, real_T c4_y[5])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_zopt), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_zopt);
}

static void c4_k_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[5])
{
  real_T c4_dv8[5];
  int32_T c4_i147;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_b_u), c4_dv8, 1, 0, 0U, 1, 0U, 1, 5);
  for (c4_i147 = 0; c4_i147 < 5; c4_i147++) {
    c4_y[c4_i147] = c4_dv8[c4_i147];
  }

  sf_mex_destroy(&c4_b_u);
}

static void c4_l_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_output, const char_T *c4_identifier,
  c4_sTH1uaqaUOn3AI0zmFyKbPF *c4_y)
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_output), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_output);
}

static void c4_m_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId,
  c4_sTH1uaqaUOn3AI0zmFyKbPF *c4_y)
{
  emlrtMsgIdentifier c4_thisId;
  static const char * c4_fieldNames[6] = { "message", "algorithm",
    "firstorderopt", "constrviolation", "iterations", "cgiterations" };

  c4_thisId.fParent = c4_parentId;
  sf_mex_check_struct(c4_parentId, c4_b_u, 6, c4_fieldNames, 0U, NULL);
  c4_thisId.fIdentifier = "message";
  c4_n_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c4_b_u,
    "message", "message", 0)), &c4_thisId, c4_y->message);
  c4_thisId.fIdentifier = "algorithm";
  c4_o_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c4_b_u,
    "algorithm", "algorithm", 0)), &c4_thisId, c4_y->algorithm);
  c4_thisId.fIdentifier = "firstorderopt";
  c4_y->firstorderopt = c4_p_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c4_b_u, "firstorderopt", "firstorderopt", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "constrviolation";
  c4_y->constrviolation = c4_p_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c4_b_u, "constrviolation", "constrviolation", 0)),
    &c4_thisId);
  c4_thisId.fIdentifier = "iterations";
  c4_y->iterations = c4_p_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getfield(c4_b_u, "iterations", "iterations", 0)), &c4_thisId);
  c4_thisId.fIdentifier = "cgiterations";
  c4_q_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c4_b_u,
    "cgiterations", "cgiterations", 0)), &c4_thisId);
  sf_mex_destroy(&c4_b_u);
}

static void c4_n_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId, char_T c4_y[912])
{
  char_T c4_cv3[912];
  int32_T c4_i148;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_b_u), c4_cv3, 1, 10, 0U, 1, 0U, 2, 1,
                912);
  for (c4_i148 = 0; c4_i148 < 912; c4_i148++) {
    c4_y[c4_i148] = c4_cv3[c4_i148];
  }

  sf_mex_destroy(&c4_b_u);
}

static void c4_o_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId, char_T c4_y[21])
{
  char_T c4_cv4[21];
  int32_T c4_i149;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_b_u), c4_cv4, 1, 10, 0U, 1, 0U, 2, 1,
                21);
  for (c4_i149 = 0; c4_i149 < 21; c4_i149++) {
    c4_y[c4_i149] = c4_cv4[c4_i149];
  }

  sf_mex_destroy(&c4_b_u);
}

static real_T c4_p_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId)
{
  real_T c4_y;
  real_T c4_d0;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_b_u), &c4_d0, 1, 0, 0U, 0, 0U, 0);
  c4_y = c4_d0;
  sf_mex_destroy(&c4_b_u);
  return c4_y;
}

static void c4_q_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct *chartInstance,
  const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId)
{
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_b_u), NULL, 1, 0, 0U, 1, 0U, 2, 0, 0);
  sf_mex_destroy(&c4_b_u);
}

static real_T c4_r_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c4_toc, const char_T *c4_identifier)
{
  real_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_toc), &c4_thisId);
  sf_mex_destroy(&c4_toc);
  return c4_y;
}

static const mxArray *c4_r_sf_marshallOut(void *chartInstanceVoid, void
  *c4_inData)
{
  const mxArray *c4_mxArrayOutData = NULL;
  int32_T c4_b_u;
  const mxArray *c4_y = NULL;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_mxArrayOutData = NULL;
  c4_b_u = *(int32_T *)c4_inData;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_create("y", &c4_b_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c4_mxArrayOutData, c4_y, false);
  return c4_mxArrayOutData;
}

static int32_T c4_s_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId)
{
  int32_T c4_y;
  int32_T c4_i150;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_b_u), &c4_i150, 1, 6, 0U, 0, 0U, 0);
  c4_y = c4_i150;
  sf_mex_destroy(&c4_b_u);
  return c4_y;
}

static void c4_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c4_mxArrayInData, const char_T *c4_varName, void *c4_outData)
{
  const mxArray *c4_b_sfEvent;
  const char_T *c4_identifier;
  emlrtMsgIdentifier c4_thisId;
  int32_T c4_y;
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)chartInstanceVoid;
  c4_b_sfEvent = sf_mex_dup(c4_mxArrayInData);
  c4_identifier = c4_varName;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_s_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_b_sfEvent),
    &c4_thisId);
  sf_mex_destroy(&c4_b_sfEvent);
  *(int32_T *)c4_outData = c4_y;
  sf_mex_destroy(&c4_mxArrayInData);
}

static uint8_T c4_t_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c4_b_is_active_c4_mpc_aircraft, const char_T
  *c4_identifier)
{
  uint8_T c4_y;
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = c4_identifier;
  c4_thisId.fParent = NULL;
  c4_y = c4_u_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c4_b_is_active_c4_mpc_aircraft), &c4_thisId);
  sf_mex_destroy(&c4_b_is_active_c4_mpc_aircraft);
  return c4_y;
}

static uint8_T c4_u_emlrt_marshallIn(SFc4_mpc_aircraftInstanceStruct
  *chartInstance, const mxArray *c4_b_u, const emlrtMsgIdentifier *c4_parentId)
{
  uint8_T c4_y;
  uint8_T c4_u0;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_b_u), &c4_u0, 1, 3, 0U, 0, 0U, 0);
  c4_y = c4_u0;
  sf_mex_destroy(&c4_b_u);
  return c4_y;
}

static void init_dsm_address_info(SFc4_mpc_aircraftInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc4_mpc_aircraftInstanceStruct
  *chartInstance)
{
  chartInstance->c4_f = (real_T (*)[6])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c4_H = (real_T (*)[25])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c4_F = (real_T (*)[50])ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c4_G = (real_T (*)[60])ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c4_S = (real_T (*)[120])ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c4_s = (real_T (*)[12])ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c4_u = (real_T (*)[2])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c4_feasRes = (real_T (*)[12])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c4_M = (real_T (*)[12])ssGetInputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c4_L = (real_T (*)[12])ssGetInputPortSignal_wrapper
    (chartInstance->S, 7);
  chartInstance->c4_xk1k = (real_T (*)[6])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c4_A = (real_T (*)[36])ssGetInputPortSignal_wrapper
    (chartInstance->S, 8);
  chartInstance->c4_B = (real_T (*)[12])ssGetInputPortSignal_wrapper
    (chartInstance->S, 9);
  chartInstance->c4_C = (real_T (*)[12])ssGetInputPortSignal_wrapper
    (chartInstance->S, 10);
  chartInstance->c4_xkk1 = (real_T (*)[6])ssGetInputPortSignal_wrapper
    (chartInstance->S, 11);
  chartInstance->c4_time = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c4_iter = (real_T *)ssGetOutputPortSignal_wrapper
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

void sf_c4_mpc_aircraft_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3593990232U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2849595378U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(898907529U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3001444658U);
}

mxArray* sf_c4_mpc_aircraft_get_post_codegen_info(void);
mxArray *sf_c4_mpc_aircraft_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("DLZjAukdzobT6HOJ76OYmE");
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
    mxArray* mxPostCodegenInfo = sf_c4_mpc_aircraft_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c4_mpc_aircraft_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c4_mpc_aircraft_jit_fallback_info(void)
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

mxArray *sf_c4_mpc_aircraft_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c4_mpc_aircraft_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c4_mpc_aircraft(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x6'type','srcId','name','auxInfo'{{M[1],M[13],T\"feasRes\",},{M[1],M[22],T\"iter\",},{M[1],M[21],T\"time\",},{M[1],M[12],T\"u\",},{M[1],M[16],T\"xk1k\",},{M[8],M[0],T\"is_active_c4_mpc_aircraft\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 6, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c4_mpc_aircraft_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc4_mpc_aircraftInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc4_mpc_aircraftInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _mpc_aircraftMachineNumber_,
           4,
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",62,-1,1163);

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 5;
          dimVector[1]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_k_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 5;
          dimVector[1]= 10;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_j_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 12;
          dimVector[1]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_i_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 12;
          dimVector[1]= 10;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_h_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 12;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_g_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 2;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_d_sf_marshallOut,(MexInFcnForType)
            c4_d_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 12;
          _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_c_sf_marshallOut,(MexInFcnForType)
            c4_c_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c4_b_sf_marshallOut,(MexInFcnForType)
            c4_b_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(15,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)c4_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(16,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c4_sf_marshallOut,(MexInFcnForType)c4_sf_marshallIn);
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
    SFc4_mpc_aircraftInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc4_mpc_aircraftInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, *chartInstance->c4_f);
        _SFD_SET_DATA_VALUE_PTR(1U, *chartInstance->c4_H);
        _SFD_SET_DATA_VALUE_PTR(2U, *chartInstance->c4_F);
        _SFD_SET_DATA_VALUE_PTR(3U, *chartInstance->c4_G);
        _SFD_SET_DATA_VALUE_PTR(4U, *chartInstance->c4_S);
        _SFD_SET_DATA_VALUE_PTR(5U, *chartInstance->c4_s);
        _SFD_SET_DATA_VALUE_PTR(12U, *chartInstance->c4_u);
        _SFD_SET_DATA_VALUE_PTR(13U, *chartInstance->c4_feasRes);
        _SFD_SET_DATA_VALUE_PTR(6U, *chartInstance->c4_M);
        _SFD_SET_DATA_VALUE_PTR(7U, *chartInstance->c4_L);
        _SFD_SET_DATA_VALUE_PTR(14U, *chartInstance->c4_xk1k);
        _SFD_SET_DATA_VALUE_PTR(8U, *chartInstance->c4_A);
        _SFD_SET_DATA_VALUE_PTR(9U, *chartInstance->c4_B);
        _SFD_SET_DATA_VALUE_PTR(10U, *chartInstance->c4_C);
        _SFD_SET_DATA_VALUE_PTR(11U, *chartInstance->c4_xkk1);
        _SFD_SET_DATA_VALUE_PTR(15U, chartInstance->c4_time);
        _SFD_SET_DATA_VALUE_PTR(16U, chartInstance->c4_iter);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "s7vD8N7O4lXxmGfAGXsJheE";
}

static void sf_opaque_initialize_c4_mpc_aircraft(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc4_mpc_aircraftInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c4_mpc_aircraft((SFc4_mpc_aircraftInstanceStruct*)
    chartInstanceVar);
  initialize_c4_mpc_aircraft((SFc4_mpc_aircraftInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c4_mpc_aircraft(void *chartInstanceVar)
{
  enable_c4_mpc_aircraft((SFc4_mpc_aircraftInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c4_mpc_aircraft(void *chartInstanceVar)
{
  disable_c4_mpc_aircraft((SFc4_mpc_aircraftInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c4_mpc_aircraft(void *chartInstanceVar)
{
  sf_gateway_c4_mpc_aircraft((SFc4_mpc_aircraftInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c4_mpc_aircraft(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c4_mpc_aircraft((SFc4_mpc_aircraftInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c4_mpc_aircraft(SimStruct* S, const mxArray *
  st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c4_mpc_aircraft((SFc4_mpc_aircraftInstanceStruct*)
    chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c4_mpc_aircraft(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc4_mpc_aircraftInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_mpc_aircraft_optimization_info();
    }

    finalize_c4_mpc_aircraft((SFc4_mpc_aircraftInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc4_mpc_aircraft((SFc4_mpc_aircraftInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c4_mpc_aircraft(SimStruct *S)
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
    initialize_params_c4_mpc_aircraft((SFc4_mpc_aircraftInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c4_mpc_aircraft(SimStruct *S)
{
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_mpc_aircraft_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,4);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,4,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,4);
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
        infoStruct,4,12);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,4,5);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,4);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1476820727U));
  ssSetChecksum1(S,(2375845311U));
  ssSetChecksum2(S,(213096042U));
  ssSetChecksum3(S,(1880532373U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c4_mpc_aircraft(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c4_mpc_aircraft(SimStruct *S)
{
  SFc4_mpc_aircraftInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc4_mpc_aircraftInstanceStruct *)utMalloc(sizeof
    (SFc4_mpc_aircraftInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc4_mpc_aircraftInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c4_mpc_aircraft;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c4_mpc_aircraft;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c4_mpc_aircraft;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c4_mpc_aircraft;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c4_mpc_aircraft;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c4_mpc_aircraft;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c4_mpc_aircraft;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c4_mpc_aircraft;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c4_mpc_aircraft;
  chartInstance->chartInfo.mdlStart = mdlStart_c4_mpc_aircraft;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c4_mpc_aircraft;
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

void c4_mpc_aircraft_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c4_mpc_aircraft(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c4_mpc_aircraft(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c4_mpc_aircraft(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c4_mpc_aircraft_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
