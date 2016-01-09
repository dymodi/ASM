/* Include files */

#include <stddef.h>
#include "blas.h"
#include "mpclib_sfun.h"
#include "c3_mpclib.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "mpclib_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c3_b_p                         (20.0)
#define c3_b_ny                        (6.0)
#define c3_b_nv                        (1.0)
#define c3_b_nx                        (13.0)
#define c3_b_nu                        (5.0)
#define c3_b_voff                      (0.0)
#define c3_b_no_md                     (1.0)
#define c3_b_no_ref                    (0.0)
#define c3_b_openloopflag              (false)
#define c3_b_MDscale                   (0.0)
#define c3_b_no_mv                     (1.0)
#define c3_b_CustomEstimation          (0.0)
#define c3_b_no_uref                   (1.0)
#define c3_b_isQP                      (true)
#define c3_b_degrees                   (26.0)
#define c3_b_maxiter                   (200.0)
#define c3_b_nxQP                      (13.0)
#define c3_b_lims_inport               (0.0)
#define c3_b_no_umin                   (1.0)
#define c3_b_no_umax                   (1.0)
#define c3_b_no_ymin                   (1.0)
#define c3_b_no_ymax                   (1.0)
#define c3_b_switch_inport             (0.0)
#define c3_b_no_switch                 (1.0)
#define c3_b_enable_value              (0.0)
#define c3_b_return_cost               (0.0)
#define c3_b_return_sequence           (0.0)
#define c3_b_no_ywt                    (1.0)
#define c3_b_no_uwt                    (1.0)
#define c3_b_no_duwt                   (1.0)
#define c3_b_no_rhoeps                 (1.0)
#define c3_b_Wy                        (0.0)
#define c3_b_Wdu                       (0.0)
#define c3_b_Jm                        (0.0)
#define c3_b_SuJm                      (0.0)
#define c3_b_Su1                       (0.0)
#define c3_b_Sx                        (0.0)
#define c3_b_Hv                        (0.0)
#define c3_b_Wu                        (0.0)
#define c3_b_nCC                       (0.0)
#define c3_b_Scc                       (0.0)
#define c3_b_Gcc                       (0.0)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c3_debug_family_names[112] = { "isSimulation", "isAdaptive",
  "isDouble", "ZERO", "ONE", "rseq", "vseq", "v", "delmv", "ym_est", "y_innov",
  "utargetValue", "isQP", "nx", "nu", "ny", "degrees", "Hinv", "Kx", "Ku1",
  "Kut", "Kr", "Kv", "Mlim", "Mx", "Mu1", "Mv", "z_degrees", "utarget", "p",
  "uoff", "voff", "yoff", "maxiter", "nxQP", "openloopflag", "lims_inport",
  "no_umin", "no_umax", "no_ymin", "no_ymax", "switch_inport", "no_switch",
  "enable_value", "return_cost", "H", "return_sequence", "Linv", "Ac", "no_ywt",
  "no_uwt", "no_duwt", "no_rhoeps", "Wy", "Wdu", "Jm", "SuJm", "Su1", "Sx", "Hv",
  "Wu", "I1", "A", "Bu", "Bv", "C", "Dv", "Mrows", "nCC", "Ecc", "Fcc", "Scc",
  "Gcc", "nv", "no_md", "no_ref", "no_uref", "no_mv", "Rscale", "MDscale",
  "myindex", "myoff", "xoff", "CustomEstimation", "M", "L", "nargin", "nargout",
  "xk", "old_u", "ym", "ref", "md", "umin", "umax", "ymin", "ymax", "switch_in",
  "ext_mv", "MVtarget", "ywt", "uwt", "duwt", "rhoeps", "iA", "xk1", "u", "cost",
  "useq", "status", "xest", "iAout" };

/* Function Declarations */
static void initialize_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance);
static void initialize_params_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance);
static void enable_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance);
static void disable_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance);
static void c3_update_debugger_state_c3_mpclib(SFc3_mpclibInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c3_mpclib(SFc3_mpclibInstanceStruct
  *chartInstance);
static void set_sim_state_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_st);
static void finalize_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance);
static void sf_gateway_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance);
static void mdl_start_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance);
static void c3_chartstep_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance);
static void initSimStructsc3_mpclib(SFc3_mpclibInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber, uint32_T c3_instanceNumber);
static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData);
static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance, const
  mxArray *c3_b_xest, const char_T *c3_identifier, real_T c3_y[13]);
static void c3_b_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[13]);
static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_g_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_h_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_i_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_j_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_k_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_l_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_m_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_n_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_o_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_p_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_q_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_r_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_s_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_t_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_u_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_v_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_w_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_x_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_y_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_ab_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_bb_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_c_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[100]);
static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_d_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[6]);
static void c3_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_cb_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_db_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static boolean_T c3_e_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_info_helper(const mxArray **c3_info);
static const mxArray *c3_emlrt_marshallOut(const char * c3_e_u);
static const mxArray *c3_b_emlrt_marshallOut(const uint32_T c3_e_u);
static void c3_eml_scalar_eg(SFc3_mpclibInstanceStruct *chartInstance);
static void c3_threshold(SFc3_mpclibInstanceStruct *chartInstance);
static void c3_b_eml_scalar_eg(SFc3_mpclibInstanceStruct *chartInstance);
static void c3_c_eml_scalar_eg(SFc3_mpclibInstanceStruct *chartInstance);
static void c3_d_eml_scalar_eg(SFc3_mpclibInstanceStruct *chartInstance);
static void c3_f_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_rseq, const char_T *c3_identifier, real_T c3_y[120]);
static void c3_g_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[120]);
static void c3_h_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_vseq, const char_T *c3_identifier, real_T c3_y[21]);
static void c3_i_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[21]);
static real_T c3_j_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_v, const char_T *c3_identifier);
static real_T c3_k_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_l_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const char_T *c3_identifier, real_T c3_y[5]);
static void c3_m_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[5]);
static void c3_n_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_b_useq, const char_T *c3_identifier, real_T c3_y[100]);
static void c3_o_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[100]);
static void c3_p_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_b_iAout, const char_T *c3_identifier, boolean_T c3_y[221]);
static void c3_q_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, boolean_T c3_y
  [221]);
static const mxArray *c3_eb_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static int32_T c3_r_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_s_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[676]);
static void c3_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_t_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[325]);
static void c3_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_u_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[125]);
static void c3_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_v_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[2500]);
static void c3_o_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_w_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[3000]);
static void c3_p_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_x_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[525]);
static void c3_q_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_y_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[195]);
static void c3_r_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_ab_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[2535]);
static void c3_s_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_bb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[975]);
static void c3_t_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_cb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[4095]);
static void c3_u_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_db_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[26]);
static void c3_v_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_eb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[5070]);
static void c3_w_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_fb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[500]);
static void c3_x_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_gb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[169]);
static void c3_y_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_hb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[65]);
static void c3_ab_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_ib_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[78]);
static void c3_bb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_jb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[5]);
static void c3_cb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_kb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[6]);
static void c3_db_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_lb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[78]);
static void c3_eb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static uint8_T c3_mb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_b_is_active_c3_mpclib, const char_T *c3_identifier);
static uint8_T c3_nb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId);
static void init_dsm_address_info(SFc3_mpclibInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc3_mpclibInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance)
{
  chartInstance->c3_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c3_is_active_c3_mpclib = 0U;
}

static void initialize_params_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance)
{
  real_T c3_d0;
  real_T c3_d1;
  real_T c3_d2;
  real_T c3_d3;
  real_T c3_d4;
  real_T c3_dv0[676];
  int32_T c3_i0;
  real_T c3_dv1[325];
  int32_T c3_i1;
  real_T c3_dv2[125];
  int32_T c3_i2;
  real_T c3_dv3[2500];
  int32_T c3_i3;
  real_T c3_dv4[3000];
  int32_T c3_i4;
  real_T c3_dv5[525];
  int32_T c3_i5;
  real_T c3_dv6[195];
  int32_T c3_i6;
  real_T c3_dv7[2535];
  int32_T c3_i7;
  real_T c3_dv8[975];
  int32_T c3_i8;
  real_T c3_dv9[4095];
  int32_T c3_i9;
  real_T c3_dv10[26];
  int32_T c3_i10;
  real_T c3_dv11[100];
  int32_T c3_i11;
  real_T c3_d5;
  real_T c3_dv12[5];
  int32_T c3_i12;
  real_T c3_d6;
  real_T c3_dv13[6];
  int32_T c3_i13;
  real_T c3_d7;
  real_T c3_d8;
  real_T c3_d9;
  real_T c3_d10;
  real_T c3_d11;
  real_T c3_d12;
  real_T c3_d13;
  real_T c3_d14;
  real_T c3_d15;
  real_T c3_d16;
  real_T c3_d17;
  real_T c3_d18;
  real_T c3_dv14[676];
  int32_T c3_i14;
  real_T c3_d19;
  real_T c3_dv15[676];
  int32_T c3_i15;
  real_T c3_dv16[5070];
  int32_T c3_i16;
  real_T c3_d20;
  real_T c3_d21;
  real_T c3_d22;
  real_T c3_d23;
  real_T c3_d24;
  real_T c3_d25;
  real_T c3_d26;
  real_T c3_d27;
  real_T c3_d28;
  real_T c3_d29;
  real_T c3_d30;
  real_T c3_d31;
  real_T c3_dv17[500];
  int32_T c3_i17;
  real_T c3_dv18[169];
  int32_T c3_i18;
  real_T c3_dv19[65];
  int32_T c3_i19;
  real_T c3_dv20[13];
  int32_T c3_i20;
  real_T c3_dv21[78];
  int32_T c3_i21;
  real_T c3_dv22[6];
  int32_T c3_i22;
  real_T c3_dv23[195];
  int32_T c3_i23;
  real_T c3_d32;
  real_T c3_dv24[5];
  int32_T c3_i24;
  real_T c3_dv25[6];
  int32_T c3_i25;
  real_T c3_d33;
  real_T c3_d34;
  real_T c3_d35;
  real_T c3_d36;
  real_T c3_d37;
  real_T c3_d38;
  real_T c3_d39;
  real_T c3_dv26[6];
  int32_T c3_i26;
  real_T c3_d40;
  real_T c3_dv27[6];
  int32_T c3_i27;
  real_T c3_dv28[6];
  int32_T c3_i28;
  real_T c3_dv29[13];
  int32_T c3_i29;
  real_T c3_d41;
  real_T c3_dv30[78];
  int32_T c3_i30;
  real_T c3_dv31[78];
  int32_T c3_i31;
  sf_mex_import_named("isQP", sf_mex_get_sfun_param(chartInstance->S, 39, 0),
                      &c3_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_isQP = (c3_d0 != 0.0);
  sf_mex_import_named("nx", sf_mex_get_sfun_param(chartInstance->S, 60, 0),
                      &c3_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_nx = c3_d1;
  sf_mex_import_named("nu", sf_mex_get_sfun_param(chartInstance->S, 58, 0),
                      &c3_d2, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_nu = c3_d2;
  sf_mex_import_named("ny", sf_mex_get_sfun_param(chartInstance->S, 62, 0),
                      &c3_d3, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_ny = c3_d3;
  sf_mex_import_named("degrees", sf_mex_get_sfun_param(chartInstance->S, 37, 0),
                      &c3_d4, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_degrees = c3_d4;
  sf_mex_import_named("Hinv", sf_mex_get_sfun_param(chartInstance->S, 11, 0),
                      c3_dv0, 0, 0, 0U, 1, 0U, 2, 26, 26);
  for (c3_i0 = 0; c3_i0 < 676; c3_i0++) {
    chartInstance->c3_Hinv[c3_i0] = c3_dv0[c3_i0];
  }

  sf_mex_import_named("Kx", sf_mex_get_sfun_param(chartInstance->S, 19, 0),
                      c3_dv1, 0, 0, 0U, 1, 0U, 2, 13, 25);
  for (c3_i1 = 0; c3_i1 < 325; c3_i1++) {
    chartInstance->c3_Kx[c3_i1] = c3_dv1[c3_i1];
  }

  sf_mex_import_named("Ku1", sf_mex_get_sfun_param(chartInstance->S, 16, 0),
                      c3_dv2, 0, 0, 0U, 1, 0U, 2, 5, 25);
  for (c3_i2 = 0; c3_i2 < 125; c3_i2++) {
    chartInstance->c3_Ku1[c3_i2] = c3_dv2[c3_i2];
  }

  sf_mex_import_named("Kut", sf_mex_get_sfun_param(chartInstance->S, 17, 0),
                      c3_dv3, 0, 0, 0U, 1, 0U, 2, 100, 25);
  for (c3_i3 = 0; c3_i3 < 2500; c3_i3++) {
    chartInstance->c3_Kut[c3_i3] = c3_dv3[c3_i3];
  }

  sf_mex_import_named("Kr", sf_mex_get_sfun_param(chartInstance->S, 15, 0),
                      c3_dv4, 0, 0, 0U, 1, 0U, 2, 120, 25);
  for (c3_i4 = 0; c3_i4 < 3000; c3_i4++) {
    chartInstance->c3_Kr[c3_i4] = c3_dv4[c3_i4];
  }

  sf_mex_import_named("Kv", sf_mex_get_sfun_param(chartInstance->S, 18, 0),
                      c3_dv5, 0, 0, 0U, 1, 0U, 2, 21, 25);
  for (c3_i5 = 0; c3_i5 < 525; c3_i5++) {
    chartInstance->c3_Kv[c3_i5] = c3_dv5[c3_i5];
  }

  sf_mex_import_named("Mlim", sf_mex_get_sfun_param(chartInstance->S, 24, 0),
                      c3_dv6, 0, 0, 0U, 1, 0U, 1, 195);
  for (c3_i6 = 0; c3_i6 < 195; c3_i6++) {
    chartInstance->c3_Mlim[c3_i6] = c3_dv6[c3_i6];
  }

  sf_mex_import_named("Mx", sf_mex_get_sfun_param(chartInstance->S, 28, 0),
                      c3_dv7, 0, 0, 0U, 1, 0U, 2, 195, 13);
  for (c3_i7 = 0; c3_i7 < 2535; c3_i7++) {
    chartInstance->c3_Mx[c3_i7] = c3_dv7[c3_i7];
  }

  sf_mex_import_named("Mu1", sf_mex_get_sfun_param(chartInstance->S, 26, 0),
                      c3_dv8, 0, 0, 0U, 1, 0U, 2, 195, 5);
  for (c3_i8 = 0; c3_i8 < 975; c3_i8++) {
    chartInstance->c3_Mu1[c3_i8] = c3_dv8[c3_i8];
  }

  sf_mex_import_named("Mv", sf_mex_get_sfun_param(chartInstance->S, 27, 0),
                      c3_dv9, 0, 0, 0U, 1, 0U, 2, 195, 21);
  for (c3_i9 = 0; c3_i9 < 4095; c3_i9++) {
    chartInstance->c3_Mv[c3_i9] = c3_dv9[c3_i9];
  }

  sf_mex_import_named("z_degrees", sf_mex_get_sfun_param(chartInstance->S, 73, 0),
                      c3_dv10, 0, 0, 0U, 1, 0U, 1, 26);
  for (c3_i10 = 0; c3_i10 < 26; c3_i10++) {
    chartInstance->c3_z_degrees[c3_i10] = c3_dv10[c3_i10];
  }

  sf_mex_import_named("utarget", sf_mex_get_sfun_param(chartInstance->S, 69, 0),
                      c3_dv11, 0, 0, 0U, 1, 0U, 1, 100);
  for (c3_i11 = 0; c3_i11 < 100; c3_i11++) {
    chartInstance->c3_utarget[c3_i11] = c3_dv11[c3_i11];
  }

  sf_mex_import_named("p", sf_mex_get_sfun_param(chartInstance->S, 64, 0),
                      &c3_d5, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_p = c3_d5;
  sf_mex_import_named("uoff", sf_mex_get_sfun_param(chartInstance->S, 68, 0),
                      c3_dv12, 0, 0, 0U, 1, 0U, 1, 5);
  for (c3_i12 = 0; c3_i12 < 5; c3_i12++) {
    chartInstance->c3_uoff[c3_i12] = c3_dv12[c3_i12];
  }

  sf_mex_import_named("voff", sf_mex_get_sfun_param(chartInstance->S, 70, 0),
                      &c3_d6, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_voff = c3_d6;
  sf_mex_import_named("yoff", sf_mex_get_sfun_param(chartInstance->S, 72, 0),
                      c3_dv13, 0, 0, 0U, 1, 0U, 1, 6);
  for (c3_i13 = 0; c3_i13 < 6; c3_i13++) {
    chartInstance->c3_yoff[c3_i13] = c3_dv13[c3_i13];
  }

  sf_mex_import_named("maxiter", sf_mex_get_sfun_param(chartInstance->S, 41, 0),
                      &c3_d7, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_maxiter = c3_d7;
  sf_mex_import_named("nxQP", sf_mex_get_sfun_param(chartInstance->S, 61, 0),
                      &c3_d8, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_nxQP = c3_d8;
  sf_mex_import_named("openloopflag", sf_mex_get_sfun_param(chartInstance->S, 63,
    0), &c3_d9, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_openloopflag = (c3_d9 != 0.0);
  sf_mex_import_named("lims_inport", sf_mex_get_sfun_param(chartInstance->S, 40,
    0), &c3_d10, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_lims_inport = c3_d10;
  sf_mex_import_named("no_umin", sf_mex_get_sfun_param(chartInstance->S, 52, 0),
                      &c3_d11, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_umin = c3_d11;
  sf_mex_import_named("no_umax", sf_mex_get_sfun_param(chartInstance->S, 51, 0),
                      &c3_d12, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_umax = c3_d12;
  sf_mex_import_named("no_ymin", sf_mex_get_sfun_param(chartInstance->S, 56, 0),
                      &c3_d13, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_ymin = c3_d13;
  sf_mex_import_named("no_ymax", sf_mex_get_sfun_param(chartInstance->S, 55, 0),
                      &c3_d14, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_ymax = c3_d14;
  sf_mex_import_named("switch_inport", sf_mex_get_sfun_param(chartInstance->S,
    67, 0), &c3_d15, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_switch_inport = c3_d15;
  sf_mex_import_named("no_switch", sf_mex_get_sfun_param(chartInstance->S, 50, 0),
                      &c3_d16, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_switch = c3_d16;
  sf_mex_import_named("enable_value", sf_mex_get_sfun_param(chartInstance->S, 38,
    0), &c3_d17, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_enable_value = c3_d17;
  sf_mex_import_named("return_cost", sf_mex_get_sfun_param(chartInstance->S, 65,
    0), &c3_d18, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_return_cost = c3_d18;
  sf_mex_import_named("H", sf_mex_get_sfun_param(chartInstance->S, 10, 0),
                      c3_dv14, 0, 0, 0U, 1, 0U, 2, 26, 26);
  for (c3_i14 = 0; c3_i14 < 676; c3_i14++) {
    chartInstance->c3_H[c3_i14] = c3_dv14[c3_i14];
  }

  sf_mex_import_named("return_sequence", sf_mex_get_sfun_param(chartInstance->S,
    66, 0), &c3_d19, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_return_sequence = c3_d19;
  sf_mex_import_named("Linv", sf_mex_get_sfun_param(chartInstance->S, 21, 0),
                      c3_dv15, 0, 0, 0U, 1, 0U, 2, 26, 26);
  for (c3_i15 = 0; c3_i15 < 676; c3_i15++) {
    chartInstance->c3_Linv[c3_i15] = c3_dv15[c3_i15];
  }

  sf_mex_import_named("Ac", sf_mex_get_sfun_param(chartInstance->S, 1, 0),
                      c3_dv16, 0, 0, 0U, 1, 0U, 2, 195, 26);
  for (c3_i16 = 0; c3_i16 < 5070; c3_i16++) {
    chartInstance->c3_Ac[c3_i16] = c3_dv16[c3_i16];
  }

  sf_mex_import_named("no_ywt", sf_mex_get_sfun_param(chartInstance->S, 57, 0),
                      &c3_d20, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_ywt = c3_d20;
  sf_mex_import_named("no_uwt", sf_mex_get_sfun_param(chartInstance->S, 54, 0),
                      &c3_d21, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_uwt = c3_d21;
  sf_mex_import_named("no_duwt", sf_mex_get_sfun_param(chartInstance->S, 45, 0),
                      &c3_d22, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_duwt = c3_d22;
  sf_mex_import_named("no_rhoeps", sf_mex_get_sfun_param(chartInstance->S, 49, 0),
                      &c3_d23, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_rhoeps = c3_d23;
  sf_mex_import_named("Wy", sf_mex_get_sfun_param(chartInstance->S, 36, 0),
                      &c3_d24, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_Wy = c3_d24;
  sf_mex_import_named("Wdu", sf_mex_get_sfun_param(chartInstance->S, 34, 0),
                      &c3_d25, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_Wdu = c3_d25;
  sf_mex_import_named("Jm", sf_mex_get_sfun_param(chartInstance->S, 14, 0),
                      &c3_d26, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_Jm = c3_d26;
  sf_mex_import_named("SuJm", sf_mex_get_sfun_param(chartInstance->S, 32, 0),
                      &c3_d27, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_SuJm = c3_d27;
  sf_mex_import_named("Su1", sf_mex_get_sfun_param(chartInstance->S, 31, 0),
                      &c3_d28, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_Su1 = c3_d28;
  sf_mex_import_named("Sx", sf_mex_get_sfun_param(chartInstance->S, 33, 0),
                      &c3_d29, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_Sx = c3_d29;
  sf_mex_import_named("Hv", sf_mex_get_sfun_param(chartInstance->S, 12, 0),
                      &c3_d30, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_Hv = c3_d30;
  sf_mex_import_named("Wu", sf_mex_get_sfun_param(chartInstance->S, 35, 0),
                      &c3_d31, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_Wu = c3_d31;
  sf_mex_import_named("I1", sf_mex_get_sfun_param(chartInstance->S, 13, 0),
                      c3_dv17, 0, 0, 0U, 1, 0U, 2, 100, 5);
  for (c3_i17 = 0; c3_i17 < 500; c3_i17++) {
    chartInstance->c3_I1[c3_i17] = c3_dv17[c3_i17];
  }

  sf_mex_import_named("A", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      c3_dv18, 0, 0, 0U, 1, 0U, 2, 13, 13);
  for (c3_i18 = 0; c3_i18 < 169; c3_i18++) {
    chartInstance->c3_A[c3_i18] = c3_dv18[c3_i18];
  }

  sf_mex_import_named("Bu", sf_mex_get_sfun_param(chartInstance->S, 2, 0),
                      c3_dv19, 0, 0, 0U, 1, 0U, 2, 13, 5);
  for (c3_i19 = 0; c3_i19 < 65; c3_i19++) {
    chartInstance->c3_Bu[c3_i19] = c3_dv19[c3_i19];
  }

  sf_mex_import_named("Bv", sf_mex_get_sfun_param(chartInstance->S, 3, 0),
                      c3_dv20, 0, 0, 0U, 1, 0U, 1, 13);
  for (c3_i20 = 0; c3_i20 < 13; c3_i20++) {
    chartInstance->c3_Bv[c3_i20] = c3_dv20[c3_i20];
  }

  sf_mex_import_named("C", sf_mex_get_sfun_param(chartInstance->S, 4, 0),
                      c3_dv21, 0, 0, 0U, 1, 0U, 2, 6, 13);
  for (c3_i21 = 0; c3_i21 < 78; c3_i21++) {
    chartInstance->c3_C[c3_i21] = c3_dv21[c3_i21];
  }

  sf_mex_import_named("Dv", sf_mex_get_sfun_param(chartInstance->S, 6, 0),
                      c3_dv22, 0, 0, 0U, 1, 0U, 1, 6);
  for (c3_i22 = 0; c3_i22 < 6; c3_i22++) {
    chartInstance->c3_Dv[c3_i22] = c3_dv22[c3_i22];
  }

  sf_mex_import_named("Mrows", sf_mex_get_sfun_param(chartInstance->S, 25, 0),
                      c3_dv23, 0, 0, 0U, 1, 0U, 1, 195);
  for (c3_i23 = 0; c3_i23 < 195; c3_i23++) {
    chartInstance->c3_Mrows[c3_i23] = c3_dv23[c3_i23];
  }

  sf_mex_import_named("nCC", sf_mex_get_sfun_param(chartInstance->S, 44, 0),
                      &c3_d32, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_nCC = c3_d32;
  sf_mex_import_named("Ecc", sf_mex_get_sfun_param(chartInstance->S, 7, 0),
                      c3_dv24, 0, 0, 0U, 1, 0U, 2, 1, 5);
  for (c3_i24 = 0; c3_i24 < 5; c3_i24++) {
    chartInstance->c3_Ecc[c3_i24] = c3_dv24[c3_i24];
  }

  sf_mex_import_named("Fcc", sf_mex_get_sfun_param(chartInstance->S, 8, 0),
                      c3_dv25, 0, 0, 0U, 1, 0U, 2, 1, 6);
  for (c3_i25 = 0; c3_i25 < 6; c3_i25++) {
    chartInstance->c3_Fcc[c3_i25] = c3_dv25[c3_i25];
  }

  sf_mex_import_named("Scc", sf_mex_get_sfun_param(chartInstance->S, 30, 0),
                      &c3_d33, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_Scc = c3_d33;
  sf_mex_import_named("Gcc", sf_mex_get_sfun_param(chartInstance->S, 9, 0),
                      &c3_d34, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_Gcc = c3_d34;
  sf_mex_import_named("nv", sf_mex_get_sfun_param(chartInstance->S, 59, 0),
                      &c3_d35, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_nv = c3_d35;
  sf_mex_import_named("no_md", sf_mex_get_sfun_param(chartInstance->S, 46, 0),
                      &c3_d36, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_md = c3_d36;
  sf_mex_import_named("no_ref", sf_mex_get_sfun_param(chartInstance->S, 48, 0),
                      &c3_d37, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_ref = c3_d37;
  sf_mex_import_named("no_uref", sf_mex_get_sfun_param(chartInstance->S, 53, 0),
                      &c3_d38, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_uref = c3_d38;
  sf_mex_import_named("no_mv", sf_mex_get_sfun_param(chartInstance->S, 47, 0),
                      &c3_d39, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_mv = c3_d39;
  sf_mex_import_named("Rscale", sf_mex_get_sfun_param(chartInstance->S, 29, 0),
                      c3_dv26, 0, 0, 0U, 1, 0U, 1, 6);
  for (c3_i26 = 0; c3_i26 < 6; c3_i26++) {
    chartInstance->c3_Rscale[c3_i26] = c3_dv26[c3_i26];
  }

  sf_mex_import_named("MDscale", sf_mex_get_sfun_param(chartInstance->S, 23, 0),
                      &c3_d40, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_MDscale = c3_d40;
  sf_mex_import_named("myindex", sf_mex_get_sfun_param(chartInstance->S, 42, 0),
                      c3_dv27, 0, 0, 0U, 1, 0U, 1, 6);
  for (c3_i27 = 0; c3_i27 < 6; c3_i27++) {
    chartInstance->c3_myindex[c3_i27] = c3_dv27[c3_i27];
  }

  sf_mex_import_named("myoff", sf_mex_get_sfun_param(chartInstance->S, 43, 0),
                      c3_dv28, 0, 0, 0U, 1, 0U, 1, 6);
  for (c3_i28 = 0; c3_i28 < 6; c3_i28++) {
    chartInstance->c3_myoff[c3_i28] = c3_dv28[c3_i28];
  }

  sf_mex_import_named("xoff", sf_mex_get_sfun_param(chartInstance->S, 71, 0),
                      c3_dv29, 0, 0, 0U, 1, 0U, 1, 13);
  for (c3_i29 = 0; c3_i29 < 13; c3_i29++) {
    chartInstance->c3_xoff[c3_i29] = c3_dv29[c3_i29];
  }

  sf_mex_import_named("CustomEstimation", sf_mex_get_sfun_param(chartInstance->S,
    5, 0), &c3_d41, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_CustomEstimation = c3_d41;
  sf_mex_import_named("M", sf_mex_get_sfun_param(chartInstance->S, 22, 0),
                      c3_dv30, 0, 0, 0U, 1, 0U, 2, 13, 6);
  for (c3_i30 = 0; c3_i30 < 78; c3_i30++) {
    chartInstance->c3_M[c3_i30] = c3_dv30[c3_i30];
  }

  sf_mex_import_named("L", sf_mex_get_sfun_param(chartInstance->S, 20, 0),
                      c3_dv31, 0, 0, 0U, 1, 0U, 2, 13, 6);
  for (c3_i31 = 0; c3_i31 < 78; c3_i31++) {
    chartInstance->c3_L[c3_i31] = c3_dv31[c3_i31];
  }
}

static void enable_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c3_update_debugger_state_c3_mpclib(SFc3_mpclibInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c3_mpclib(SFc3_mpclibInstanceStruct
  *chartInstance)
{
  const mxArray *c3_st;
  const mxArray *c3_y = NULL;
  real_T c3_hoistedGlobal;
  real_T c3_e_u;
  const mxArray *c3_b_y = NULL;
  int32_T c3_i32;
  boolean_T c3_f_u[221];
  const mxArray *c3_c_y = NULL;
  real_T c3_b_hoistedGlobal;
  real_T c3_g_u;
  const mxArray *c3_d_y = NULL;
  int32_T c3_i33;
  real_T c3_h_u[5];
  const mxArray *c3_e_y = NULL;
  int32_T c3_i34;
  real_T c3_i_u[100];
  const mxArray *c3_f_y = NULL;
  int32_T c3_i35;
  real_T c3_j_u[13];
  const mxArray *c3_g_y = NULL;
  int32_T c3_i36;
  real_T c3_k_u[13];
  const mxArray *c3_h_y = NULL;
  uint8_T c3_c_hoistedGlobal;
  uint8_T c3_l_u;
  const mxArray *c3_i_y = NULL;
  c3_st = NULL;
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellmatrix(8, 1), false);
  c3_hoistedGlobal = *chartInstance->c3_cost;
  c3_e_u = c3_hoistedGlobal;
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c3_y, 0, c3_b_y);
  for (c3_i32 = 0; c3_i32 < 221; c3_i32++) {
    c3_f_u[c3_i32] = (*chartInstance->c3_iAout)[c3_i32];
  }

  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_f_u, 11, 0U, 1U, 0U, 1, 221),
                false);
  sf_mex_setcell(c3_y, 1, c3_c_y);
  c3_b_hoistedGlobal = *chartInstance->c3_status;
  c3_g_u = c3_b_hoistedGlobal;
  c3_d_y = NULL;
  sf_mex_assign(&c3_d_y, sf_mex_create("y", &c3_g_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c3_y, 2, c3_d_y);
  for (c3_i33 = 0; c3_i33 < 5; c3_i33++) {
    c3_h_u[c3_i33] = (*chartInstance->c3_d_u)[c3_i33];
  }

  c3_e_y = NULL;
  sf_mex_assign(&c3_e_y, sf_mex_create("y", c3_h_u, 0, 0U, 1U, 0U, 1, 5), false);
  sf_mex_setcell(c3_y, 3, c3_e_y);
  for (c3_i34 = 0; c3_i34 < 100; c3_i34++) {
    c3_i_u[c3_i34] = (*chartInstance->c3_useq)[c3_i34];
  }

  c3_f_y = NULL;
  sf_mex_assign(&c3_f_y, sf_mex_create("y", c3_i_u, 0, 0U, 1U, 0U, 2, 20, 5),
                false);
  sf_mex_setcell(c3_y, 4, c3_f_y);
  for (c3_i35 = 0; c3_i35 < 13; c3_i35++) {
    c3_j_u[c3_i35] = (*chartInstance->c3_xest)[c3_i35];
  }

  c3_g_y = NULL;
  sf_mex_assign(&c3_g_y, sf_mex_create("y", c3_j_u, 0, 0U, 1U, 0U, 1, 13), false);
  sf_mex_setcell(c3_y, 5, c3_g_y);
  for (c3_i36 = 0; c3_i36 < 13; c3_i36++) {
    c3_k_u[c3_i36] = (*chartInstance->c3_xk1)[c3_i36];
  }

  c3_h_y = NULL;
  sf_mex_assign(&c3_h_y, sf_mex_create("y", c3_k_u, 0, 0U, 1U, 0U, 1, 13), false);
  sf_mex_setcell(c3_y, 6, c3_h_y);
  c3_c_hoistedGlobal = chartInstance->c3_is_active_c3_mpclib;
  c3_l_u = c3_c_hoistedGlobal;
  c3_i_y = NULL;
  sf_mex_assign(&c3_i_y, sf_mex_create("y", &c3_l_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c3_y, 7, c3_i_y);
  sf_mex_assign(&c3_st, c3_y, false);
  return c3_st;
}

static void set_sim_state_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_st)
{
  const mxArray *c3_e_u;
  boolean_T c3_bv0[221];
  int32_T c3_i37;
  real_T c3_dv32[5];
  int32_T c3_i38;
  real_T c3_dv33[100];
  int32_T c3_i39;
  real_T c3_dv34[13];
  int32_T c3_i40;
  real_T c3_dv35[13];
  int32_T c3_i41;
  chartInstance->c3_doneDoubleBufferReInit = true;
  c3_e_u = sf_mex_dup(c3_st);
  *chartInstance->c3_cost = c3_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c3_e_u, 0)), "cost");
  c3_p_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_e_u, 1)),
                        "iAout", c3_bv0);
  for (c3_i37 = 0; c3_i37 < 221; c3_i37++) {
    (*chartInstance->c3_iAout)[c3_i37] = c3_bv0[c3_i37];
  }

  *chartInstance->c3_status = c3_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c3_e_u, 2)), "status");
  c3_l_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_e_u, 3)),
                        "u", c3_dv32);
  for (c3_i38 = 0; c3_i38 < 5; c3_i38++) {
    (*chartInstance->c3_d_u)[c3_i38] = c3_dv32[c3_i38];
  }

  c3_n_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_e_u, 4)),
                        "useq", c3_dv33);
  for (c3_i39 = 0; c3_i39 < 100; c3_i39++) {
    (*chartInstance->c3_useq)[c3_i39] = c3_dv33[c3_i39];
  }

  c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_e_u, 5)),
                      "xest", c3_dv34);
  for (c3_i40 = 0; c3_i40 < 13; c3_i40++) {
    (*chartInstance->c3_xest)[c3_i40] = c3_dv34[c3_i40];
  }

  c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_e_u, 6)),
                      "xk1", c3_dv35);
  for (c3_i41 = 0; c3_i41 < 13; c3_i41++) {
    (*chartInstance->c3_xk1)[c3_i41] = c3_dv35[c3_i41];
  }

  chartInstance->c3_is_active_c3_mpclib = c3_mb_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c3_e_u, 7)), "is_active_c3_mpclib");
  sf_mex_destroy(&c3_e_u);
  c3_update_debugger_state_c3_mpclib(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance)
{
  int32_T c3_i42;
  int32_T c3_i43;
  int32_T c3_i44;
  int32_T c3_i45;
  int32_T c3_i46;
  int32_T c3_i47;
  int32_T c3_i48;
  int32_T c3_i49;
  int32_T c3_i50;
  int32_T c3_i51;
  int32_T c3_i52;
  int32_T c3_i53;
  int32_T c3_i54;
  int32_T c3_i55;
  int32_T c3_i56;
  int32_T c3_i57;
  int32_T c3_i58;
  int32_T c3_i59;
  int32_T c3_i60;
  int32_T c3_i61;
  int32_T c3_i62;
  int32_T c3_i63;
  int32_T c3_i64;
  int32_T c3_i65;
  int32_T c3_i66;
  int32_T c3_i67;
  int32_T c3_i68;
  int32_T c3_i69;
  int32_T c3_i70;
  int32_T c3_i71;
  int32_T c3_i72;
  int32_T c3_i73;
  int32_T c3_i74;
  int32_T c3_i75;
  int32_T c3_i76;
  int32_T c3_i77;
  int32_T c3_i78;
  int32_T c3_i79;
  int32_T c3_i80;
  int32_T c3_i81;
  int32_T c3_i82;
  int32_T c3_i83;
  int32_T c3_i84;
  int32_T c3_i85;
  int32_T c3_i86;
  int32_T c3_i87;
  int32_T c3_i88;
  int32_T c3_i89;
  int32_T c3_i90;
  int32_T c3_i91;
  int32_T c3_i92;
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c3_sfEvent);
  chartInstance->c3_sfEvent = CALL_EVENT;
  c3_chartstep_c3_mpclib(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_mpclibMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  for (c3_i42 = 0; c3_i42 < 13; c3_i42++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_xk1)[c3_i42], 0U);
  }

  for (c3_i43 = 0; c3_i43 < 13; c3_i43++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_xk)[c3_i43], 1U);
  }

  for (c3_i44 = 0; c3_i44 < 5; c3_i44++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_old_u)[c3_i44], 2U);
  }

  for (c3_i45 = 0; c3_i45 < 6; c3_i45++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_ym)[c3_i45], 3U);
  }

  for (c3_i46 = 0; c3_i46 < 6; c3_i46++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_ref)[c3_i46], 4U);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c3_md, 5U);
  for (c3_i47 = 0; c3_i47 < 5; c3_i47++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_umin)[c3_i47], 6U);
  }

  for (c3_i48 = 0; c3_i48 < 5; c3_i48++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_umax)[c3_i48], 7U);
  }

  for (c3_i49 = 0; c3_i49 < 6; c3_i49++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_ymin)[c3_i49], 8U);
  }

  for (c3_i50 = 0; c3_i50 < 6; c3_i50++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_ymax)[c3_i50], 9U);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c3_switch_in, 10U);
  for (c3_i51 = 0; c3_i51 < 5; c3_i51++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_ext_mv)[c3_i51], 11U);
  }

  for (c3_i52 = 0; c3_i52 < 5; c3_i52++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_MVtarget)[c3_i52], 12U);
  }

  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c3_isQP, 13U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_nx, 14U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_nu, 15U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_ny, 16U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_degrees, 17U);
  for (c3_i53 = 0; c3_i53 < 676; c3_i53++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Hinv[c3_i53], 18U);
  }

  for (c3_i54 = 0; c3_i54 < 325; c3_i54++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Kx[c3_i54], 19U);
  }

  for (c3_i55 = 0; c3_i55 < 125; c3_i55++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Ku1[c3_i55], 20U);
  }

  for (c3_i56 = 0; c3_i56 < 2500; c3_i56++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Kut[c3_i56], 21U);
  }

  for (c3_i57 = 0; c3_i57 < 3000; c3_i57++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Kr[c3_i57], 22U);
  }

  for (c3_i58 = 0; c3_i58 < 525; c3_i58++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Kv[c3_i58], 23U);
  }

  for (c3_i59 = 0; c3_i59 < 195; c3_i59++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Mlim[c3_i59], 24U);
  }

  for (c3_i60 = 0; c3_i60 < 2535; c3_i60++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Mx[c3_i60], 25U);
  }

  for (c3_i61 = 0; c3_i61 < 975; c3_i61++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Mu1[c3_i61], 26U);
  }

  for (c3_i62 = 0; c3_i62 < 4095; c3_i62++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Mv[c3_i62], 27U);
  }

  for (c3_i63 = 0; c3_i63 < 26; c3_i63++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_z_degrees[c3_i63], 28U);
  }

  for (c3_i64 = 0; c3_i64 < 100; c3_i64++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_utarget[c3_i64], 29U);
  }

  _SFD_DATA_RANGE_CHECK(chartInstance->c3_p, 30U);
  for (c3_i65 = 0; c3_i65 < 5; c3_i65++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_uoff[c3_i65], 31U);
  }

  _SFD_DATA_RANGE_CHECK(chartInstance->c3_voff, 32U);
  for (c3_i66 = 0; c3_i66 < 6; c3_i66++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_yoff[c3_i66], 33U);
  }

  _SFD_DATA_RANGE_CHECK(chartInstance->c3_maxiter, 34U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_nxQP, 35U);
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c3_openloopflag, 36U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_lims_inport, 37U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_umin, 38U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_umax, 39U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_ymin, 40U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_ymax, 41U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_switch_inport, 42U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_switch, 43U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_enable_value, 44U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_return_cost, 45U);
  for (c3_i67 = 0; c3_i67 < 676; c3_i67++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_H[c3_i67], 46U);
  }

  _SFD_DATA_RANGE_CHECK(chartInstance->c3_return_sequence, 47U);
  for (c3_i68 = 0; c3_i68 < 676; c3_i68++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Linv[c3_i68], 48U);
  }

  for (c3_i69 = 0; c3_i69 < 5070; c3_i69++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Ac[c3_i69], 49U);
  }

  for (c3_i70 = 0; c3_i70 < 6; c3_i70++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_ywt)[c3_i70], 50U);
  }

  for (c3_i71 = 0; c3_i71 < 5; c3_i71++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_uwt)[c3_i71], 51U);
  }

  for (c3_i72 = 0; c3_i72 < 5; c3_i72++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_duwt)[c3_i72], 52U);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c3_rhoeps, 53U);
  for (c3_i73 = 0; c3_i73 < 221; c3_i73++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c3_iA)[c3_i73], 54U);
  }

  for (c3_i74 = 0; c3_i74 < 5; c3_i74++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_d_u)[c3_i74], 55U);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c3_cost, 56U);
  for (c3_i75 = 0; c3_i75 < 100; c3_i75++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_useq)[c3_i75], 57U);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c3_status, 58U);
  for (c3_i76 = 0; c3_i76 < 13; c3_i76++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_xest)[c3_i76], 59U);
  }

  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_ywt, 60U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_uwt, 61U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_duwt, 62U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_rhoeps, 63U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_Wy, 64U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_Wdu, 65U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_Jm, 66U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_SuJm, 67U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_Su1, 68U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_Sx, 69U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_Hv, 70U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_Wu, 71U);
  for (c3_i77 = 0; c3_i77 < 500; c3_i77++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_I1[c3_i77], 72U);
  }

  for (c3_i78 = 0; c3_i78 < 221; c3_i78++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*chartInstance->c3_iAout)[c3_i78], 73U);
  }

  for (c3_i79 = 0; c3_i79 < 169; c3_i79++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_A[c3_i79], 74U);
  }

  for (c3_i80 = 0; c3_i80 < 65; c3_i80++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Bu[c3_i80], 75U);
  }

  for (c3_i81 = 0; c3_i81 < 13; c3_i81++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Bv[c3_i81], 76U);
  }

  for (c3_i82 = 0; c3_i82 < 78; c3_i82++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_C[c3_i82], 77U);
  }

  for (c3_i83 = 0; c3_i83 < 6; c3_i83++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Dv[c3_i83], 78U);
  }

  for (c3_i84 = 0; c3_i84 < 195; c3_i84++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Mrows[c3_i84], 79U);
  }

  _SFD_DATA_RANGE_CHECK(chartInstance->c3_nCC, 80U);
  for (c3_i85 = 0; c3_i85 < 5; c3_i85++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Ecc[c3_i85], 81U);
  }

  for (c3_i86 = 0; c3_i86 < 6; c3_i86++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Fcc[c3_i86], 82U);
  }

  _SFD_DATA_RANGE_CHECK(chartInstance->c3_Scc, 83U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_Gcc, 84U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_nv, 85U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_md, 86U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_ref, 87U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_uref, 88U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_mv, 89U);
  for (c3_i87 = 0; c3_i87 < 6; c3_i87++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Rscale[c3_i87], 90U);
  }

  _SFD_DATA_RANGE_CHECK(chartInstance->c3_MDscale, 91U);
  for (c3_i88 = 0; c3_i88 < 6; c3_i88++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_myindex[c3_i88], 92U);
  }

  for (c3_i89 = 0; c3_i89 < 6; c3_i89++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_myoff[c3_i89], 93U);
  }

  for (c3_i90 = 0; c3_i90 < 13; c3_i90++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_xoff[c3_i90], 94U);
  }

  _SFD_DATA_RANGE_CHECK(chartInstance->c3_CustomEstimation, 95U);
  for (c3_i91 = 0; c3_i91 < 78; c3_i91++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_M[c3_i91], 96U);
  }

  for (c3_i92 = 0; c3_i92 < 78; c3_i92++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_L[c3_i92], 97U);
  }
}

static void mdl_start_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c3_chartstep_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance)
{
  real_T c3_hoistedGlobal;
  real_T c3_b_hoistedGlobal;
  real_T c3_c_hoistedGlobal;
  int32_T c3_i93;
  real_T c3_b_xk[13];
  int32_T c3_i94;
  real_T c3_b_old_u[5];
  int32_T c3_i95;
  real_T c3_b_ym[6];
  int32_T c3_i96;
  real_T c3_b_ref[6];
  real_T c3_b_md;
  int32_T c3_i97;
  real_T c3_b_umin[5];
  int32_T c3_i98;
  real_T c3_b_umax[5];
  int32_T c3_i99;
  real_T c3_b_ymin[6];
  int32_T c3_i100;
  real_T c3_b_ymax[6];
  real_T c3_b_switch_in;
  int32_T c3_i101;
  real_T c3_b_ext_mv[5];
  int32_T c3_i102;
  real_T c3_b_MVtarget[5];
  int32_T c3_i103;
  real_T c3_b_ywt[6];
  int32_T c3_i104;
  real_T c3_b_uwt[5];
  int32_T c3_i105;
  real_T c3_b_duwt[5];
  real_T c3_b_rhoeps;
  int32_T c3_i106;
  boolean_T c3_b_iA[221];
  uint32_T c3_debug_family_var_map[112];
  boolean_T c3_isSimulation;
  boolean_T c3_isAdaptive;
  boolean_T c3_isDouble;
  real_T c3_ZERO;
  real_T c3_ONE;
  real_T c3_rseq[120];
  real_T c3_vseq[21];
  real_T c3_v;
  real_T c3_delmv[5];
  real_T c3_ym_est[6];
  real_T c3_y_innov[6];
  real_T c3_utargetValue[100];
  boolean_T c3_c_isQP;
  real_T c3_c_nx;
  real_T c3_c_nu;
  real_T c3_c_ny;
  real_T c3_c_degrees;
  real_T c3_c_Hinv[676];
  real_T c3_c_Kx[325];
  real_T c3_c_Ku1[125];
  real_T c3_c_Kut[2500];
  real_T c3_c_Kv[525];
  real_T c3_c_Mlim[195];
  real_T c3_c_Mx[2535];
  real_T c3_c_Mu1[975];
  real_T c3_c_z_degrees[26];
  real_T c3_c_utarget[100];
  real_T c3_c_p;
  real_T c3_c_uoff[5];
  real_T c3_c_voff;
  real_T c3_c_yoff[6];
  real_T c3_c_maxiter;
  real_T c3_c_nxQP;
  boolean_T c3_c_openloopflag;
  real_T c3_c_lims_inport;
  real_T c3_c_no_umin;
  real_T c3_c_no_umax;
  real_T c3_c_no_ymin;
  real_T c3_c_no_ymax;
  real_T c3_c_switch_inport;
  real_T c3_c_no_switch;
  real_T c3_c_enable_value;
  real_T c3_c_return_cost;
  real_T c3_c_H[676];
  real_T c3_c_return_sequence;
  real_T c3_c_Linv[676];
  real_T c3_c_no_ywt;
  real_T c3_c_no_uwt;
  real_T c3_c_no_duwt;
  real_T c3_c_no_rhoeps;
  real_T c3_c_Wy;
  real_T c3_c_Wdu;
  real_T c3_c_Jm;
  real_T c3_c_SuJm;
  real_T c3_c_Su1;
  real_T c3_c_Sx;
  real_T c3_c_Hv;
  real_T c3_c_Wu;
  real_T c3_c_I1[500];
  real_T c3_c_A[169];
  real_T c3_c_Bu[65];
  real_T c3_b_Bv[13];
  real_T c3_c_C[78];
  real_T c3_c_Dv[6];
  real_T c3_c_Mrows[195];
  real_T c3_c_nCC;
  real_T c3_c_Ecc[5];
  real_T c3_c_Fcc[6];
  real_T c3_c_Scc;
  real_T c3_c_Gcc;
  real_T c3_c_nv;
  real_T c3_c_no_md;
  real_T c3_c_no_ref;
  real_T c3_c_no_uref;
  real_T c3_c_no_mv;
  real_T c3_c_Rscale[6];
  real_T c3_c_MDscale;
  real_T c3_c_myindex[6];
  real_T c3_b_myoff[6];
  real_T c3_b_xoff[13];
  real_T c3_c_CustomEstimation;
  real_T c3_c_M[78];
  real_T c3_c_L[78];
  real_T c3_nargin = 91.0;
  real_T c3_nargout = 7.0;
  real_T c3_b_xk1[13];
  real_T c3_e_u[5];
  real_T c3_b_cost;
  real_T c3_b_useq[100];
  real_T c3_b_status;
  real_T c3_b_xest[13];
  boolean_T c3_b_iAout[221];
  int32_T c3_i107;
  static real_T c3_d_L[78] = { -7.5457530993109069E-6, -0.02030144506285881,
    0.12680419517635366, 9.0296644295151225E-5, -0.0094130519265720261,
    -2.6516803380787974E-6, -0.00017334122721624222, 0.38630158066691817,
    0.0005082932057940702, -0.0011576329989365318, 0.028653823893971104,
    0.000541861095094848, 0.0086397025639397065, -0.00012431924979271398,
    -0.00053186763349831391, 0.0074851603254325249, 0.0003384503272822444,
    0.0028037378714959203, 2.1867895474241272E-7, -1.5133271147006706E-6,
    -0.00033226441659012066, 0.39033795538552118, -3.002809720583545E-5,
    -0.0027477109861388607, -3.3180483937537752E-5, 0.00061624499312249858,
    -1.1026863305519847E-5, -0.00020557608032760862, 0.0041674188560540887,
    0.00014007497715422875, 0.37331267558360676, -8.6873446277193622E-6,
    -0.082097337764839268, -0.000303108499695182, -0.00014982863687401892,
    0.25218710074152867, -0.008175822175618545, 0.00099694967388806884,
    0.079310107043954275, -0.00034159405840002307, -0.029797713312691983,
    0.40654943985465608, 0.0038972113825321217, 0.14677570830794961,
    1.2775312200967605E-5, 9.12385611191258E-7, -0.018535610840701391,
    -0.0028296493302629394, -0.0010324146678003352, 0.2334954302913976,
    -0.0019171621579430829, 0.0305717874617006, -0.000109735161509631,
    -0.00044673872001862064, 0.0067371890324870532, 0.00045225510209358249,
    0.0049564182901952808, -0.00010443573481056457, -0.00025225799538094551,
    -0.0003032199765172345, -5.5789583875378558E-5, -0.0014255976465785505,
    -0.0030188018641687693, 0.39033115441988708, -0.00072497538920502844,
    -0.00049034711462626337, -0.00047187842076652493, 0.033734234357794976,
    0.0064109967791707943, 0.182143213868051, -0.00048559472230845,
    -0.017706299034664731, -0.0019711820759934981, -0.0010116137317631834,
    -0.098742336973021649, -0.05375625992510874, -0.0021106249201593907,
    0.30154731544718077 };

  int32_T c3_i108;
  static real_T c3_d_M[78] = { -2.0511483531895358E-5, -0.055185049205828687,
    -0.027826025309706435, 0.00024545172735833962, -0.010304244497356334,
    -7.2080144778817318E-6, -0.0004711903080647017, 0.38630158066691811,
    0.00050829320579407009, -0.0011576329989365318, 0.028653823893971104,
    0.000541861095094848, 0.0086397025639397031, -0.00033793475763919527,
    -0.0014457661232839814, 0.00963172876362282, 0.00092000337448734128,
    -0.00038565492640083731, 5.94431028942718E-7, -4.1136495964051966E-6,
    -0.00033226441659012066, 0.39033795538552124, -3.0028097205835427E-5,
    -0.002747710986138862, -3.3180483937537806E-5, 0.00061624499312249933,
    -2.9974122148296423E-5, -0.00055881372352037557, 0.0071382065480269149,
    0.00038076326502015551, -0.077119517728960946, -2.3614651039090827E-5,
    -0.223163701411027, -0.00030310849969518195, -0.00014982863687401892,
    0.25218710074152861, -0.0081758221756185433, 0.00099694967388806862,
    0.079310107043954262, -0.00092854892165836059, -0.0809985826275228,
    0.543260300386222, 0.010593718882800817, -0.017821341136404146,
    3.4726899008781372E-5, 2.4801212274488675E-6, -0.018535610840701388,
    -0.00282964933026294, -0.0010324146678003362, 0.23349543029139763,
    -0.0019171621579430818, 0.030571787461700597, -0.00029829109547464832,
    -0.0012143617446956692, 0.0088912751110261368, 0.0012293568258488752,
    0.0036800016445915772, -0.00028388576017732538, -0.00068570832492753,
    -0.00030321997651723434, -5.5789583875378531E-5, -0.0014255976465785507,
    -0.0030188018641687719, 0.39033115441988708, -0.00072497538920502963,
    -0.0013329016513258963, -0.0012826985364115973, 0.066506706250653261,
    0.01742689604712944, 0.28413295773776848, -0.0013199833096466755,
    -0.048130710915191069, -0.0019711820759934981, -0.0010116137317631837,
    -0.098742336973021635, -0.05375625992510874, -0.0021106249201593903,
    0.30154731544718077 };

  int32_T c3_i109;
  int32_T c3_i110;
  static real_T c3_d_yoff[6] = { 0.0, 0.3, 0.0, 8.0, 0.3, 7.0 };

  int32_T c3_i111;
  int32_T c3_i112;
  int32_T c3_i113;
  int32_T c3_i114;
  int32_T c3_i115;
  static real_T c3_d_Mrows[195] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0,
    10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0, 21.0, 22.0,
    23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0, 33.0, 34.0, 35.0,
    36.0, 37.0, 38.0, 39.0, 40.0, 41.0, 42.0, 43.0, 44.0, 45.0, 46.0, 47.0, 48.0,
    49.0, 50.0, 51.0, 52.0, 53.0, 54.0, 55.0, 56.0, 57.0, 58.0, 59.0, 60.0, 61.0,
    62.0, 63.0, 64.0, 65.0, 66.0, 67.0, 68.0, 69.0, 70.0, 71.0, 72.0, 73.0, 74.0,
    75.0, 76.0, 77.0, 78.0, 79.0, 80.0, 81.0, 82.0, 83.0, 84.0, 85.0, 86.0, 87.0,
    88.0, 89.0, 90.0, 91.0, 92.0, 93.0, 94.0, 95.0, 96.0, 97.0, 98.0, 99.0,
    100.0, 101.0, 102.0, 103.0, 104.0, 105.0, 106.0, 107.0, 108.0, 109.0, 110.0,
    111.0, 112.0, 113.0, 114.0, 115.0, 116.0, 117.0, 118.0, 119.0, 120.0, 241.0,
    242.0, 243.0, 244.0, 245.0, 246.0, 247.0, 248.0, 249.0, 250.0, 251.0, 252.0,
    253.0, 254.0, 255.0, 256.0, 257.0, 258.0, 259.0, 260.0, 261.0, 262.0, 263.0,
    264.0, 265.0, 341.0, 342.0, 343.0, 344.0, 345.0, 346.0, 347.0, 348.0, 349.0,
    350.0, 351.0, 352.0, 353.0, 354.0, 355.0, 356.0, 357.0, 358.0, 359.0, 360.0,
    361.0, 362.0, 363.0, 364.0, 365.0, 466.0, 467.0, 468.0, 469.0, 470.0, 471.0,
    472.0, 473.0, 474.0, 475.0, 476.0, 477.0, 478.0, 479.0, 480.0, 481.0, 482.0,
    483.0, 484.0, 485.0, 486.0, 487.0, 488.0, 489.0, 490.0 };

  int32_T c3_i116;
  int32_T c3_i117;
  static real_T c3_d_C[78] = { 0.0, -0.0013998178359061748, 0.0, 0.0,
    -0.0011574167693600053, 0.0, -0.23905862049559551, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.017815863366045428, 0.0, 0.99999999999755462, 0.014730758882736285,
    0.0, 0.0, 0.00318264292988869, 0.0, 0.0, 0.0035981317144209309, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.014148947002773063, 0.99999999999520528, 0.0, 0.0, 0.0, 0.0,
    -0.0011574167693600053, 0.0, 0.0, 0.0, -2.0970587047059008, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  int32_T c3_i118;
  int32_T c3_i119;
  static real_T c3_d_Bu[65] = { 0.0, 0.0, 0.0, 0.63212055882855767, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.63212055882855767, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.63212055882855767, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.63212055882855767, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.63212055882855767, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  int32_T c3_i120;
  static real_T c3_d_A[169] = { 0.36787944117144233, 0.0, -0.029189778782213922,
    0.0, -0.021472319676402136, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.36787944117144233, -2.4836332211889123, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.37150627540930387, 0.0, 0.27328406860824583, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.33292881365909793,
    0.36787944117144233, 0.28077121553415035, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.26249033292995011, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.021472319676402136, 0.36787944117144233,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.754304059415928,
    0.0, 0.36787944117144233, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  int32_T c3_i121;
  static real_T c3_d_I1[500] = { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  int32_T c3_i122;
  static real_T c3_d_Ac[5070] = { -0.0, -0.0020118140273929969, -0.0, -0.0,
    -0.0022744530300585152, -0.0, -0.0, -0.0065012879409001422, -0.0,
    -0.21045114773980311, -0.0087224555623925618, -0.17748125766556958, -0.0,
    -0.0095457871680659171, -0.0, -0.36605572041663792, -0.013719157871255388,
    -0.34687302386491903, -0.0, -0.011183272161520617, -0.0,
    -0.45234526133530162, -0.016674144858187984, -0.45788045196061161, -0.0,
    -0.011977914925767425, -0.0, -0.49488011296939011, -0.018213329045585095,
    -0.51943665704909237, -0.0, -0.012341668145753203, -0.0,
    -0.51453662450077953, -0.018957289389237117, -0.55046934575377737, -0.0,
    -0.012502018635023749, -0.0, -0.52325715056671351, -0.019299567007558142,
    -0.56518279729699372, -0.0, -0.012570865518103368, -0.0, -0.5270185369656204,
    -0.019451638388249818, -0.57186804898857435, -0.0, -0.012599854895524544,
    -0.0, -0.52860782222330771, -0.019517475507268144, -0.57481263186760556,
    -0.0, -0.012611879956590235, -0.0, -0.5292688501650199,
    -0.019545417373701877, -0.57607942107836108, -0.0, -0.01261680915065729,
    -0.0, -0.52954039792849927, -0.019557091433158428, -0.57661449233265638,
    -0.0, -0.01261881026700901, -0.0, -0.529650834094031, -0.019561907458992025,
    -0.57683721067859473, -0.0, -0.01261961619326468, -0.0, -0.52969537671465872,
    -0.019563873710120225, -0.57692881677486907, -0.0, -0.012619938592013507,
    -0.0, -0.5297132176342868, -0.019564669544281918, -0.57696612576070594, -0.0,
    -0.012620066823488117, -0.0, -0.52972032133680569, -0.019564989303869712,
    -0.57698119581402907, -0.0, -0.01262011757392629, -0.0, -0.52972313540304339,
    -0.019565116978433567, -0.57698724046683247, -0.0, -0.012620137572741176,
    -0.0, -0.52972424522380457, -0.01956516768177357, -0.57698965046115869, -0.0,
    -0.012620145423541175, -0.0, -0.52972468121233862, -0.01956518772292239,
    -0.57699060633058907, -0.0, -0.012620148495082108, -0.0,
    -0.52972485189736152, -0.019565195611734663, -0.57699098373340807, -0.0,
    -0.012620149693170527, -0.0, -0.52972491851308534, -0.019565198705667568,
    -0.57699113214653308, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0,
    -0.0, -0.0, -0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.15111386878045993, -0.0, -0.0,
    -0.0, -0.0, -0.0, 0.2067055543806702, 0.027970114811385716, -0.0,
    1.569955619699267, 0.023126637690443281, -0.0, 0.22715659261305407,
    0.048650818194047887, -0.0, 2.7307583805705788, 0.046296662098209762,
    0.42904385928478755, 0.23468010912935924, 0.060119172690744765, -0.0,
    3.3744742792076288, 0.061860993210828941, 0.85889262609185368,
    0.23744785618102171, 0.065772288373257631, -0.0, 3.6917822629045118,
    0.070620667065829756, 1.1476410718075019, 0.23846605341969121,
    0.068384746847487687, -0.0, 3.8384189102871278, 0.075080065868358123,
    1.3101499642427674, 0.23884062725085525, 0.069543752716067816, -0.0,
    3.9034736227512008, 0.077208920228197558, 1.3928804371258774,
    0.23897842526254132, 0.070043661652451877, -0.0, 3.9315333875861511,
    0.078181065547962128, 1.4323748030006969, 0.23902911831807491,
    0.070254886402722733, -0.0, 3.943389380525169, 0.078610892069903945,
    1.4504099789463032, 0.2390477672510159, 0.07034274065118748, -0.0,
    3.9483206177410972, 0.078796358243172174, 1.4583840922724736,
    0.23905462781004466, 0.070378830842202658, -0.0, 3.9503463512277985,
    0.078874881912293943, 1.4618248485039194, 0.23905715166866628,
    0.0703935084158934, -0.0, 3.9511701998052793, 0.078907629531095383,
    1.4632816144418026, 0.23905808014436561, 0.070399428375115938, -0.0,
    3.9515024856508147, 0.078921120287127972, 1.4638891461090091,
    0.23905842171148703, 0.070401799531442225, -0.0, 3.9516355780683736,
    0.07892662203248263, 1.4641394257264082, 0.23905854736700877,
    0.070402743652570446, -0.0, 3.9516885713535608, 0.078928846818758974,
    1.4642414937438761, 0.23905859359309189, 0.070403117657448069, -0.0,
    3.9517095641547479, 0.0789297400435419, 1.4642827678323478,
    0.23905861059871752, 0.070403265158730161, -0.0, 3.9517178433651945,
    0.0789300964654654, 1.4642993388796919, 0.23905861685473759,
    0.070403323104003851, -0.0, 3.9517210958190607, 0.078930237933888439,
    1.4643059511957419, 0.23905861915619875, 0.070403345788981983, -0.0,
    3.9517223691212675, 0.07893029382468969, 1.464308575708609,
    0.239058620002859, 0.070403354642578, -0.0, 3.95172286607142,
    0.0789303158159376, 1.4643096125910728, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0,
    -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0,
    -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0,
    0.0008848536326911935, -0.0, -0.0, 0.00073162693504539038, -0.0, -0.0,
    0.001539101769967648, -0.0, 0.018451459275849919, 0.0014646264384442849,
    0.013573094713127674, -0.0, 0.001901910975643907, -0.0, 0.032094204714484667,
    0.0019570146541624217, 0.027171653223950546, -0.0, 0.0020807511406352513,
    -0.0, 0.039659703725975104, 0.0022341329028380532, 0.036306406972670284,
    -0.0, 0.0021633980438305277, -0.0, 0.043388978149800285,
    0.0023752090212825054, 0.04144748647075773, -0.0, 0.0022000639838897396,
    -0.0, 0.045112377266041406, 0.0024425567789330247, 0.0440647213286955, -0.0,
    0.0022158789435835825, -0.0, 0.045876955807416291, 0.0024733112582584816,
    0.0453141524930232, -0.0, 0.0022225611824249971, -0.0, 0.046206738128423033,
    0.0024869091130378415, 0.0458847075679419, -0.0, 0.0022253405114132981, -0.0,
    0.046346079883147893, 0.0024927764617514378, 0.046136974074237426, -0.0,
    0.0022264822491873345, -0.0, 0.046404035994472036, 0.0024952606115071032,
    0.046245824741141382, -0.0, 0.0022269465842280354, -0.0,
    0.046427844144501622, 0.00249629660473251, 0.046291910523799384, -0.0,
    0.0022271338661701643, -0.0, 0.046437526716598641, 0.0024967233939882454,
    0.046311130201885362, -0.0, 0.0022272088793155571, -0.0,
    0.046441432023646756, 0.0024968974454498156, 0.046319047968048914, -0.0,
    0.0022272387472304957, -0.0, 0.04644299623940655, 0.0024969678280789844,
    0.046322276959300725, -0.0, 0.0022272505791295365, -0.0,
    0.046443619061753413, 0.0024969960858533739, 0.046323582693201582, -0.0,
    0.0022272552454330598, -0.0, 0.046443865787082032, 0.0024970073615036845,
    0.046324106929570966, -0.0, 0.0022272570785712596, -0.0,
    0.046443963091434129, 0.0024970118369536023, 0.046324316114692905, -0.0,
    0.0022272577962259938, -0.0, 0.046444001317049753, 0.0024970136050971674,
    0.046324399142945026, -0.0, 0.0022272580763155339, -0.0, 0.04644401628198476,
    0.0024970143008052731, 0.046324431945428, -0.0, 0.0022272581853282104, -0.0,
    0.046444022122567374, 0.0024970145735572964, 0.046324444852158961, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0,
    -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, -0.0, -0.0, 1.3255939203149854, -0.0, -0.0, -0.0, -0.0, -0.0,
    1.8132526709407237, -0.0, 0.015690215320898468, 1.1089316623878867, -0.0,
    -0.0, 1.992652299603284, -0.0, 0.025580852808335441, 1.8079686639012205,
    -0.0, -0.0, 2.0586497347420312, -0.0, 0.030300489269799454,
    2.141536699778122, -0.0, -0.0, 2.0829288342996217, -0.0,
    0.032320518038765553, 2.2843055410608342, -0.0, -0.0, 2.0918606158770139,
    -0.0, 0.0331381323807636, 2.3420917736217368, -0.0, -0.0, 2.0951464346923703,
    -0.0, 0.033458468080839424, 2.3647320238121932, -0.0, -0.0,
    2.0963552198819544, -0.0, 0.033581445260780718, 2.3734236373942217, -0.0,
    -0.0, 2.0967999071019947, -0.0, 0.033628033206073091, 2.3767163167210308,
    -0.0, -0.0, 2.0969634983879994, -0.0, 0.033645525572207312,
    2.3779526183433854, -0.0, -0.0, 2.0970236802588755, -0.0,
    0.033652053475616443, 2.37841398860704, -0.0, -0.0, 2.097045819931902, -0.0,
    0.033654479321829169, 2.3785854392607342, -0.0, -0.0, 2.0970539646624426,
    -0.0, 0.033655378136290805, 2.3786489644447255, -0.0, -0.0,
    2.0970569609413623, -0.0, 0.033655710470412881, 2.37867245270304, -0.0, -0.0,
    2.0970580632107767, -0.0, 0.033655833169962318, 2.3786811246946313, -0.0,
    -0.0, 2.0970584687130329, -0.0, 0.033655878424272548, 2.3786843231171164,
    -0.0, -0.0, 2.0970586178889765, -0.0, 0.033655895102764781,
    2.378685501896868, -0.0, -0.0, 2.0970586727677394, -0.0,
    0.033655901246408881, 2.3786859361089761, -0.0, -0.0, 2.0970586929565078,
    -0.0, 0.033655903508621209, 2.3786860959945368, -0.0, -0.0,
    2.0970587003835406, -0.0, 0.033655904341391735, 2.3786861548519576, -0.0,
    -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0,
    -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, 0.00073162693504539038, -0.0, -0.0,
    -0.0, -0.0, -0.0, 0.0011928224408164472, 0.013573094713127674, -0.0, -0.0,
    -0.0, -0.0, 0.0014128967411499915, 0.022129163361298769, -0.0, -0.0, -0.0,
    -0.0, 0.001507089677748745, 0.026211967286727214, -0.0, -0.0, -0.0, -0.0,
    0.0015452146277797642, 0.027959428442846615, -0.0, -0.0, -0.0, -0.0,
    0.0015601517221177834, 0.028666720004866784, -0.0, -0.0, -0.0, -0.0,
    0.0015658860868413276, 0.028943831995250625, -0.0, -0.0, -0.0, -0.0,
    0.0015680584595543343, 0.029050215551929624, -0.0, -0.0, -0.0, -0.0,
    0.0015688741198852938, 0.02909051726742623, -0.0, -0.0, -0.0, -0.0,
    0.0015691785127738436, 0.029105649344165818, -0.0, -0.0, -0.0, -0.0,
    0.001569291628775964, 0.029111296420986511, -0.0, -0.0, -0.0, -0.0,
    0.0015693335400471795, 0.029113394941607893, -0.0, -0.0, -0.0, -0.0,
    0.0015693490366219668, 0.029114172476751157, -0.0, -0.0, -0.0, -0.0,
    0.0015693547580409182, 0.029114459968185985, -0.0, -0.0, -0.0, -0.0,
    0.0015693568682268917, 0.02911456611157355, -0.0, -0.0, -0.0, -0.0,
    0.0015693576459366876, 0.029114605259604753, -0.0, -0.0, -0.0, -0.0,
    0.0015693579324117558, 0.029114619687625666, -0.0, -0.0, -0.0, -0.0,
    0.0015693580378975914, 0.029114625002292265, -0.0, -0.0, -0.0, -0.0,
    0.0015693580767292669, 0.029114626959258538, -0.0, -0.0, -0.0, -0.0,
    0.0015693580910213631, 0.029114627679661224, -0.0, -0.0, -0.0, -0.0, -1.0,
    -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0020118140273929969, -0.0, -0.0,
    -0.0022744530300585152, -0.0, -0.0, -0.0065012879409001422, -0.0,
    -0.21045114773980311, -0.0087224555623925618, -0.17748125766556958, -0.0,
    -0.0095457871680659171, -0.0, -0.36605572041663792, -0.013719157871255388,
    -0.34687302386491903, -0.0, -0.011183272161520617, -0.0,
    -0.45234526133530162, -0.016674144858187984, -0.45788045196061161, -0.0,
    -0.011977914925767425, -0.0, -0.49488011296939011, -0.018213329045585095,
    -0.51943665704909237, -0.0, -0.012341668145753203, -0.0,
    -0.51453662450077953, -0.018957289389237117, -0.55046934575377737, -0.0,
    -0.012502018635023749, -0.0, -0.52325715056671351, -0.019299567007558142,
    -0.56518279729699372, -0.0, -0.012570865518103368, -0.0, -0.5270185369656204,
    -0.019451638388249818, -0.57186804898857435, -0.0, -0.012599854895524544,
    -0.0, -0.52860782222330771, -0.019517475507268144, -0.57481263186760556,
    -0.0, -0.012611879956590235, -0.0, -0.5292688501650199,
    -0.019545417373701877, -0.57607942107836108, -0.0, -0.01261680915065729,
    -0.0, -0.52954039792849927, -0.019557091433158428, -0.57661449233265638,
    -0.0, -0.01261881026700901, -0.0, -0.529650834094031, -0.019561907458992025,
    -0.57683721067859473, -0.0, -0.01261961619326468, -0.0, -0.52969537671465872,
    -0.019563873710120225, -0.57692881677486907, -0.0, -0.012619938592013507,
    -0.0, -0.5297132176342868, -0.019564669544281918, -0.57696612576070594, -0.0,
    -0.012620066823488117, -0.0, -0.52972032133680569, -0.019564989303869712,
    -0.57698119581402907, -0.0, -0.01262011757392629, -0.0, -0.52972313540304339,
    -0.019565116978433567, -0.57698724046683247, -0.0, -0.012620137572741176,
    -0.0, -0.52972424522380457, -0.01956516768177357, -0.57698965046115869, -0.0,
    -0.012620145423541175, -0.0, -0.52972468121233862, -0.01956518772292239,
    -0.57699060633058907, -0.0, -0.012620148495082108, -0.0,
    -0.52972485189736152, -0.019565195611734663, -0.57699098373340807, -0.0,
    -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.15111386878045993, -0.0,
    -0.0, -0.0, -0.0, -0.0, 0.2067055543806702, 0.027970114811385716, -0.0,
    1.569955619699267, 0.023126637690443281, -0.0, 0.22715659261305407,
    0.048650818194047887, -0.0, 2.7307583805705788, 0.046296662098209762,
    0.42904385928478755, 0.23468010912935924, 0.060119172690744765, -0.0,
    3.3744742792076288, 0.061860993210828941, 0.85889262609185368,
    0.23744785618102171, 0.065772288373257631, -0.0, 3.6917822629045118,
    0.070620667065829756, 1.1476410718075019, 0.23846605341969121,
    0.068384746847487687, -0.0, 3.8384189102871278, 0.075080065868358123,
    1.3101499642427674, 0.23884062725085525, 0.069543752716067816, -0.0,
    3.9034736227512008, 0.077208920228197558, 1.3928804371258774,
    0.23897842526254132, 0.070043661652451877, -0.0, 3.9315333875861511,
    0.078181065547962128, 1.4323748030006969, 0.23902911831807491,
    0.070254886402722733, -0.0, 3.943389380525169, 0.078610892069903945,
    1.4504099789463032, 0.2390477672510159, 0.07034274065118748, -0.0,
    3.9483206177410972, 0.078796358243172174, 1.4583840922724736,
    0.23905462781004466, 0.070378830842202658, -0.0, 3.9503463512277985,
    0.078874881912293943, 1.4618248485039194, 0.23905715166866628,
    0.0703935084158934, -0.0, 3.9511701998052793, 0.078907629531095383,
    1.4632816144418026, 0.23905808014436561, 0.070399428375115938, -0.0,
    3.9515024856508147, 0.078921120287127972, 1.4638891461090091,
    0.23905842171148703, 0.070401799531442225, -0.0, 3.9516355780683736,
    0.07892662203248263, 1.4641394257264082, 0.23905854736700877,
    0.070402743652570446, -0.0, 3.9516885713535608, 0.078928846818758974,
    1.4642414937438761, 0.23905859359309189, 0.070403117657448069, -0.0,
    3.9517095641547479, 0.0789297400435419, 1.4642827678323478,
    0.23905861059871752, 0.070403265158730161, -0.0, 3.9517178433651945,
    0.0789300964654654, 1.4642993388796919, 0.23905861685473759,
    0.070403323104003851, -0.0, 3.9517210958190607, 0.078930237933888439,
    1.4643059511957419, 0.23905861915619875, 0.070403345788981983, -0.0,
    3.9517223691212675, 0.07893029382468969, 1.464308575708609, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0,
    -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0008848536326911935, -0.0,
    -0.0, 0.00073162693504539038, -0.0, -0.0, 0.001539101769967648, -0.0,
    0.018451459275849919, 0.0014646264384442849, 0.013573094713127674, -0.0,
    0.001901910975643907, -0.0, 0.032094204714484667, 0.0019570146541624217,
    0.027171653223950546, -0.0, 0.0020807511406352513, -0.0,
    0.039659703725975104, 0.0022341329028380532, 0.036306406972670284, -0.0,
    0.0021633980438305277, -0.0, 0.043388978149800285, 0.0023752090212825054,
    0.04144748647075773, -0.0, 0.0022000639838897396, -0.0, 0.045112377266041406,
    0.0024425567789330247, 0.0440647213286955, -0.0, 0.0022158789435835825, -0.0,
    0.045876955807416291, 0.0024733112582584816, 0.0453141524930232, -0.0,
    0.0022225611824249971, -0.0, 0.046206738128423033, 0.0024869091130378415,
    0.0458847075679419, -0.0, 0.0022253405114132981, -0.0, 0.046346079883147893,
    0.0024927764617514378, 0.046136974074237426, -0.0, 0.0022264822491873345,
    -0.0, 0.046404035994472036, 0.0024952606115071032, 0.046245824741141382,
    -0.0, 0.0022269465842280354, -0.0, 0.046427844144501622, 0.00249629660473251,
    0.046291910523799384, -0.0, 0.0022271338661701643, -0.0,
    0.046437526716598641, 0.0024967233939882454, 0.046311130201885362, -0.0,
    0.0022272088793155571, -0.0, 0.046441432023646756, 0.0024968974454498156,
    0.046319047968048914, -0.0, 0.0022272387472304957, -0.0, 0.04644299623940655,
    0.0024969678280789844, 0.046322276959300725, -0.0, 0.0022272505791295365,
    -0.0, 0.046443619061753413, 0.0024969960858533739, 0.046323582693201582,
    -0.0, 0.0022272552454330598, -0.0, 0.046443865787082032,
    0.0024970073615036845, 0.046324106929570966, -0.0, 0.0022272570785712596,
    -0.0, 0.046443963091434129, 0.0024970118369536023, 0.046324316114692905,
    -0.0, 0.0022272577962259938, -0.0, 0.046444001317049753,
    0.0024970136050971674, 0.046324399142945026, -0.0, 0.0022272580763155339,
    -0.0, 0.04644401628198476, 0.0024970143008052731, 0.046324431945428, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0,
    -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    1.3255939203149854, -0.0, -0.0, -0.0, -0.0, -0.0, 1.8132526709407237, -0.0,
    0.015690215320898468, 1.1089316623878867, -0.0, -0.0, 1.992652299603284,
    -0.0, 0.025580852808335441, 1.8079686639012205, -0.0, -0.0,
    2.0586497347420312, -0.0, 0.030300489269799454, 2.141536699778122, -0.0,
    -0.0, 2.0829288342996217, -0.0, 0.032320518038765553, 2.2843055410608342,
    -0.0, -0.0, 2.0918606158770139, -0.0, 0.0331381323807636, 2.3420917736217368,
    -0.0, -0.0, 2.0951464346923703, -0.0, 0.033458468080839424,
    2.3647320238121932, -0.0, -0.0, 2.0963552198819544, -0.0,
    0.033581445260780718, 2.3734236373942217, -0.0, -0.0, 2.0967999071019947,
    -0.0, 0.033628033206073091, 2.3767163167210308, -0.0, -0.0,
    2.0969634983879994, -0.0, 0.033645525572207312, 2.3779526183433854, -0.0,
    -0.0, 2.0970236802588755, -0.0, 0.033652053475616443, 2.37841398860704, -0.0,
    -0.0, 2.097045819931902, -0.0, 0.033654479321829169, 2.3785854392607342,
    -0.0, -0.0, 2.0970539646624426, -0.0, 0.033655378136290805,
    2.3786489644447255, -0.0, -0.0, 2.0970569609413623, -0.0,
    0.033655710470412881, 2.37867245270304, -0.0, -0.0, 2.0970580632107767, -0.0,
    0.033655833169962318, 2.3786811246946313, -0.0, -0.0, 2.0970584687130329,
    -0.0, 0.033655878424272548, 2.3786843231171164, -0.0, -0.0,
    2.0970586178889765, -0.0, 0.033655895102764781, 2.378685501896868, -0.0,
    -0.0, 2.0970586727677394, -0.0, 0.033655901246408881, 2.3786859361089761,
    -0.0, -0.0, 2.0970586929565078, -0.0, 0.033655903508621209,
    2.3786860959945368, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0,
    -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, 0.00073162693504539038, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.0011928224408164472, 0.013573094713127674, -0.0, -0.0, -0.0, -0.0,
    0.0014128967411499915, 0.022129163361298769, -0.0, -0.0, -0.0, -0.0,
    0.001507089677748745, 0.026211967286727214, -0.0, -0.0, -0.0, -0.0,
    0.0015452146277797642, 0.027959428442846615, -0.0, -0.0, -0.0, -0.0,
    0.0015601517221177834, 0.028666720004866784, -0.0, -0.0, -0.0, -0.0,
    0.0015658860868413276, 0.028943831995250625, -0.0, -0.0, -0.0, -0.0,
    0.0015680584595543343, 0.029050215551929624, -0.0, -0.0, -0.0, -0.0,
    0.0015688741198852938, 0.02909051726742623, -0.0, -0.0, -0.0, -0.0,
    0.0015691785127738436, 0.029105649344165818, -0.0, -0.0, -0.0, -0.0,
    0.001569291628775964, 0.029111296420986511, -0.0, -0.0, -0.0, -0.0,
    0.0015693335400471795, 0.029113394941607893, -0.0, -0.0, -0.0, -0.0,
    0.0015693490366219668, 0.029114172476751157, -0.0, -0.0, -0.0, -0.0,
    0.0015693547580409182, 0.029114459968185985, -0.0, -0.0, -0.0, -0.0,
    0.0015693568682268917, 0.02911456611157355, -0.0, -0.0, -0.0, -0.0,
    0.0015693576459366876, 0.029114605259604753, -0.0, -0.0, -0.0, -0.0,
    0.0015693579324117558, 0.029114619687625666, -0.0, -0.0, -0.0, -0.0,
    0.0015693580378975914, 0.029114625002292265, -0.0, -0.0, -0.0, -0.0,
    0.0015693580767292669, 0.029114626959258538, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0020118140273929969, -0.0, -0.0, -0.0022744530300585152, -0.0, -0.0,
    -0.0065012879409001422, -0.0, -0.21045114773980311, -0.0087224555623925618,
    -0.17748125766556958, -0.0, -0.0095457871680659171, -0.0,
    -0.36605572041663792, -0.013719157871255388, -0.34687302386491903, -0.0,
    -0.011183272161520617, -0.0, -0.45234526133530162, -0.016674144858187984,
    -0.45788045196061161, -0.0, -0.011977914925767425, -0.0,
    -0.49488011296939011, -0.018213329045585095, -0.51943665704909237, -0.0,
    -0.012341668145753203, -0.0, -0.51453662450077953, -0.018957289389237117,
    -0.55046934575377737, -0.0, -0.012502018635023749, -0.0,
    -0.52325715056671351, -0.019299567007558142, -0.56518279729699372, -0.0,
    -0.012570865518103368, -0.0, -0.5270185369656204, -0.019451638388249818,
    -0.57186804898857435, -0.0, -0.012599854895524544, -0.0,
    -0.52860782222330771, -0.019517475507268144, -0.57481263186760556, -0.0,
    -0.012611879956590235, -0.0, -0.5292688501650199, -0.019545417373701877,
    -0.57607942107836108, -0.0, -0.01261680915065729, -0.0, -0.52954039792849927,
    -0.019557091433158428, -0.57661449233265638, -0.0, -0.01261881026700901,
    -0.0, -0.529650834094031, -0.019561907458992025, -0.57683721067859473, -0.0,
    -0.01261961619326468, -0.0, -0.52969537671465872, -0.019563873710120225,
    -0.57692881677486907, -0.0, -0.012619938592013507, -0.0, -0.5297132176342868,
    -0.019564669544281918, -0.57696612576070594, -0.0, -0.012620066823488117,
    -0.0, -0.52972032133680569, -0.019564989303869712, -0.57698119581402907,
    -0.0, -0.01262011757392629, -0.0, -0.52972313540304339,
    -0.019565116978433567, -0.57698724046683247, -0.0, -0.012620137572741176,
    -0.0, -0.52972424522380457, -0.01956516768177357, -0.57698965046115869, -0.0,
    -0.012620145423541175, -0.0, -0.52972468121233862, -0.01956518772292239,
    -0.57699060633058907, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0,
    -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.15111386878045993, -0.0, -0.0, -0.0,
    -0.0, -0.0, 0.2067055543806702, 0.027970114811385716, -0.0,
    1.569955619699267, 0.023126637690443281, -0.0, 0.22715659261305407,
    0.048650818194047887, -0.0, 2.7307583805705788, 0.046296662098209762,
    0.42904385928478755, 0.23468010912935924, 0.060119172690744765, -0.0,
    3.3744742792076288, 0.061860993210828941, 0.85889262609185368,
    0.23744785618102171, 0.065772288373257631, -0.0, 3.6917822629045118,
    0.070620667065829756, 1.1476410718075019, 0.23846605341969121,
    0.068384746847487687, -0.0, 3.8384189102871278, 0.075080065868358123,
    1.3101499642427674, 0.23884062725085525, 0.069543752716067816, -0.0,
    3.9034736227512008, 0.077208920228197558, 1.3928804371258774,
    0.23897842526254132, 0.070043661652451877, -0.0, 3.9315333875861511,
    0.078181065547962128, 1.4323748030006969, 0.23902911831807491,
    0.070254886402722733, -0.0, 3.943389380525169, 0.078610892069903945,
    1.4504099789463032, 0.2390477672510159, 0.07034274065118748, -0.0,
    3.9483206177410972, 0.078796358243172174, 1.4583840922724736,
    0.23905462781004466, 0.070378830842202658, -0.0, 3.9503463512277985,
    0.078874881912293943, 1.4618248485039194, 0.23905715166866628,
    0.0703935084158934, -0.0, 3.9511701998052793, 0.078907629531095383,
    1.4632816144418026, 0.23905808014436561, 0.070399428375115938, -0.0,
    3.9515024856508147, 0.078921120287127972, 1.4638891461090091,
    0.23905842171148703, 0.070401799531442225, -0.0, 3.9516355780683736,
    0.07892662203248263, 1.4641394257264082, 0.23905854736700877,
    0.070402743652570446, -0.0, 3.9516885713535608, 0.078928846818758974,
    1.4642414937438761, 0.23905859359309189, 0.070403117657448069, -0.0,
    3.9517095641547479, 0.0789297400435419, 1.4642827678323478,
    0.23905861059871752, 0.070403265158730161, -0.0, 3.9517178433651945,
    0.0789300964654654, 1.4642993388796919, 0.23905861685473759,
    0.070403323104003851, -0.0, 3.9517210958190607, 0.078930237933888439,
    1.4643059511957419, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0,
    -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0008848536326911935, -0.0, -0.0,
    0.00073162693504539038, -0.0, -0.0, 0.001539101769967648, -0.0,
    0.018451459275849919, 0.0014646264384442849, 0.013573094713127674, -0.0,
    0.001901910975643907, -0.0, 0.032094204714484667, 0.0019570146541624217,
    0.027171653223950546, -0.0, 0.0020807511406352513, -0.0,
    0.039659703725975104, 0.0022341329028380532, 0.036306406972670284, -0.0,
    0.0021633980438305277, -0.0, 0.043388978149800285, 0.0023752090212825054,
    0.04144748647075773, -0.0, 0.0022000639838897396, -0.0, 0.045112377266041406,
    0.0024425567789330247, 0.0440647213286955, -0.0, 0.0022158789435835825, -0.0,
    0.045876955807416291, 0.0024733112582584816, 0.0453141524930232, -0.0,
    0.0022225611824249971, -0.0, 0.046206738128423033, 0.0024869091130378415,
    0.0458847075679419, -0.0, 0.0022253405114132981, -0.0, 0.046346079883147893,
    0.0024927764617514378, 0.046136974074237426, -0.0, 0.0022264822491873345,
    -0.0, 0.046404035994472036, 0.0024952606115071032, 0.046245824741141382,
    -0.0, 0.0022269465842280354, -0.0, 0.046427844144501622, 0.00249629660473251,
    0.046291910523799384, -0.0, 0.0022271338661701643, -0.0,
    0.046437526716598641, 0.0024967233939882454, 0.046311130201885362, -0.0,
    0.0022272088793155571, -0.0, 0.046441432023646756, 0.0024968974454498156,
    0.046319047968048914, -0.0, 0.0022272387472304957, -0.0, 0.04644299623940655,
    0.0024969678280789844, 0.046322276959300725, -0.0, 0.0022272505791295365,
    -0.0, 0.046443619061753413, 0.0024969960858533739, 0.046323582693201582,
    -0.0, 0.0022272552454330598, -0.0, 0.046443865787082032,
    0.0024970073615036845, 0.046324106929570966, -0.0, 0.0022272570785712596,
    -0.0, 0.046443963091434129, 0.0024970118369536023, 0.046324316114692905,
    -0.0, 0.0022272577962259938, -0.0, 0.046444001317049753,
    0.0024970136050971674, 0.046324399142945026, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0,
    -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    1.3255939203149854, -0.0, -0.0, -0.0, -0.0, -0.0, 1.8132526709407237, -0.0,
    0.015690215320898468, 1.1089316623878867, -0.0, -0.0, 1.992652299603284,
    -0.0, 0.025580852808335441, 1.8079686639012205, -0.0, -0.0,
    2.0586497347420312, -0.0, 0.030300489269799454, 2.141536699778122, -0.0,
    -0.0, 2.0829288342996217, -0.0, 0.032320518038765553, 2.2843055410608342,
    -0.0, -0.0, 2.0918606158770139, -0.0, 0.0331381323807636, 2.3420917736217368,
    -0.0, -0.0, 2.0951464346923703, -0.0, 0.033458468080839424,
    2.3647320238121932, -0.0, -0.0, 2.0963552198819544, -0.0,
    0.033581445260780718, 2.3734236373942217, -0.0, -0.0, 2.0967999071019947,
    -0.0, 0.033628033206073091, 2.3767163167210308, -0.0, -0.0,
    2.0969634983879994, -0.0, 0.033645525572207312, 2.3779526183433854, -0.0,
    -0.0, 2.0970236802588755, -0.0, 0.033652053475616443, 2.37841398860704, -0.0,
    -0.0, 2.097045819931902, -0.0, 0.033654479321829169, 2.3785854392607342,
    -0.0, -0.0, 2.0970539646624426, -0.0, 0.033655378136290805,
    2.3786489644447255, -0.0, -0.0, 2.0970569609413623, -0.0,
    0.033655710470412881, 2.37867245270304, -0.0, -0.0, 2.0970580632107767, -0.0,
    0.033655833169962318, 2.3786811246946313, -0.0, -0.0, 2.0970584687130329,
    -0.0, 0.033655878424272548, 2.3786843231171164, -0.0, -0.0,
    2.0970586178889765, -0.0, 0.033655895102764781, 2.378685501896868, -0.0,
    -0.0, 2.0970586727677394, -0.0, 0.033655901246408881, 2.3786859361089761,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.00073162693504539038, -0.0, -0.0,
    -0.0, -0.0, -0.0, 0.0011928224408164472, 0.013573094713127674, -0.0, -0.0,
    -0.0, -0.0, 0.0014128967411499915, 0.022129163361298769, -0.0, -0.0, -0.0,
    -0.0, 0.001507089677748745, 0.026211967286727214, -0.0, -0.0, -0.0, -0.0,
    0.0015452146277797642, 0.027959428442846615, -0.0, -0.0, -0.0, -0.0,
    0.0015601517221177834, 0.028666720004866784, -0.0, -0.0, -0.0, -0.0,
    0.0015658860868413276, 0.028943831995250625, -0.0, -0.0, -0.0, -0.0,
    0.0015680584595543343, 0.029050215551929624, -0.0, -0.0, -0.0, -0.0,
    0.0015688741198852938, 0.02909051726742623, -0.0, -0.0, -0.0, -0.0,
    0.0015691785127738436, 0.029105649344165818, -0.0, -0.0, -0.0, -0.0,
    0.001569291628775964, 0.029111296420986511, -0.0, -0.0, -0.0, -0.0,
    0.0015693335400471795, 0.029113394941607893, -0.0, -0.0, -0.0, -0.0,
    0.0015693490366219668, 0.029114172476751157, -0.0, -0.0, -0.0, -0.0,
    0.0015693547580409182, 0.029114459968185985, -0.0, -0.0, -0.0, -0.0,
    0.0015693568682268917, 0.02911456611157355, -0.0, -0.0, -0.0, -0.0,
    0.0015693576459366876, 0.029114605259604753, -0.0, -0.0, -0.0, -0.0,
    0.0015693579324117558, 0.029114619687625666, -0.0, -0.0, -0.0, -0.0,
    0.0015693580378975914, 0.029114625002292265, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0020118140273929969, -0.0, -0.0,
    -0.0022744530300585152, -0.0, -0.0, -0.0065012879409001422, -0.0,
    -0.21045114773980311, -0.0087224555623925618, -0.17748125766556958, -0.0,
    -0.0095457871680659171, -0.0, -0.36605572041663792, -0.013719157871255388,
    -0.34687302386491903, -0.0, -0.011183272161520617, -0.0,
    -0.45234526133530162, -0.016674144858187984, -0.45788045196061161, -0.0,
    -0.011977914925767425, -0.0, -0.49488011296939011, -0.018213329045585095,
    -0.51943665704909237, -0.0, -0.012341668145753203, -0.0,
    -0.51453662450077953, -0.018957289389237117, -0.55046934575377737, -0.0,
    -0.012502018635023749, -0.0, -0.52325715056671351, -0.019299567007558142,
    -0.56518279729699372, -0.0, -0.012570865518103368, -0.0, -0.5270185369656204,
    -0.019451638388249818, -0.57186804898857435, -0.0, -0.012599854895524544,
    -0.0, -0.52860782222330771, -0.019517475507268144, -0.57481263186760556,
    -0.0, -0.012611879956590235, -0.0, -0.5292688501650199,
    -0.019545417373701877, -0.57607942107836108, -0.0, -0.01261680915065729,
    -0.0, -0.52954039792849927, -0.019557091433158428, -0.57661449233265638,
    -0.0, -0.01261881026700901, -0.0, -0.529650834094031, -0.019561907458992025,
    -0.57683721067859473, -0.0, -0.01261961619326468, -0.0, -0.52969537671465872,
    -0.019563873710120225, -0.57692881677486907, -0.0, -0.012619938592013507,
    -0.0, -0.5297132176342868, -0.019564669544281918, -0.57696612576070594, -0.0,
    -0.012620066823488117, -0.0, -0.52972032133680569, -0.019564989303869712,
    -0.57698119581402907, -0.0, -0.01262011757392629, -0.0, -0.52972313540304339,
    -0.019565116978433567, -0.57698724046683247, -0.0, -0.012620137572741176,
    -0.0, -0.52972424522380457, -0.01956516768177357, -0.57698965046115869, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.15111386878045993, -0.0,
    -0.0, -0.0, -0.0, -0.0, 0.2067055543806702, 0.027970114811385716, -0.0,
    1.569955619699267, 0.023126637690443281, -0.0, 0.22715659261305407,
    0.048650818194047887, -0.0, 2.7307583805705788, 0.046296662098209762,
    0.42904385928478755, 0.23468010912935924, 0.060119172690744765, -0.0,
    3.3744742792076288, 0.061860993210828941, 0.85889262609185368,
    0.23744785618102171, 0.065772288373257631, -0.0, 3.6917822629045118,
    0.070620667065829756, 1.1476410718075019, 0.23846605341969121,
    0.068384746847487687, -0.0, 3.8384189102871278, 0.075080065868358123,
    1.3101499642427674, 0.23884062725085525, 0.069543752716067816, -0.0,
    3.9034736227512008, 0.077208920228197558, 1.3928804371258774,
    0.23897842526254132, 0.070043661652451877, -0.0, 3.9315333875861511,
    0.078181065547962128, 1.4323748030006969, 0.23902911831807491,
    0.070254886402722733, -0.0, 3.943389380525169, 0.078610892069903945,
    1.4504099789463032, 0.2390477672510159, 0.07034274065118748, -0.0,
    3.9483206177410972, 0.078796358243172174, 1.4583840922724736,
    0.23905462781004466, 0.070378830842202658, -0.0, 3.9503463512277985,
    0.078874881912293943, 1.4618248485039194, 0.23905715166866628,
    0.0703935084158934, -0.0, 3.9511701998052793, 0.078907629531095383,
    1.4632816144418026, 0.23905808014436561, 0.070399428375115938, -0.0,
    3.9515024856508147, 0.078921120287127972, 1.4638891461090091,
    0.23905842171148703, 0.070401799531442225, -0.0, 3.9516355780683736,
    0.07892662203248263, 1.4641394257264082, 0.23905854736700877,
    0.070402743652570446, -0.0, 3.9516885713535608, 0.078928846818758974,
    1.4642414937438761, 0.23905859359309189, 0.070403117657448069, -0.0,
    3.9517095641547479, 0.0789297400435419, 1.4642827678323478,
    0.23905861059871752, 0.070403265158730161, -0.0, 3.9517178433651945,
    0.0789300964654654, 1.4642993388796919, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0,
    -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, 0.0008848536326911935, -0.0, -0.0, 0.00073162693504539038,
    -0.0, -0.0, 0.001539101769967648, -0.0, 0.018451459275849919,
    0.0014646264384442849, 0.013573094713127674, -0.0, 0.001901910975643907,
    -0.0, 0.032094204714484667, 0.0019570146541624217, 0.027171653223950546,
    -0.0, 0.0020807511406352513, -0.0, 0.039659703725975104,
    0.0022341329028380532, 0.036306406972670284, -0.0, 0.0021633980438305277,
    -0.0, 0.043388978149800285, 0.0023752090212825054, 0.04144748647075773, -0.0,
    0.0022000639838897396, -0.0, 0.045112377266041406, 0.0024425567789330247,
    0.0440647213286955, -0.0, 0.0022158789435835825, -0.0, 0.045876955807416291,
    0.0024733112582584816, 0.0453141524930232, -0.0, 0.0022225611824249971, -0.0,
    0.046206738128423033, 0.0024869091130378415, 0.0458847075679419, -0.0,
    0.0022253405114132981, -0.0, 0.046346079883147893, 0.0024927764617514378,
    0.046136974074237426, -0.0, 0.0022264822491873345, -0.0,
    0.046404035994472036, 0.0024952606115071032, 0.046245824741141382, -0.0,
    0.0022269465842280354, -0.0, 0.046427844144501622, 0.00249629660473251,
    0.046291910523799384, -0.0, 0.0022271338661701643, -0.0,
    0.046437526716598641, 0.0024967233939882454, 0.046311130201885362, -0.0,
    0.0022272088793155571, -0.0, 0.046441432023646756, 0.0024968974454498156,
    0.046319047968048914, -0.0, 0.0022272387472304957, -0.0, 0.04644299623940655,
    0.0024969678280789844, 0.046322276959300725, -0.0, 0.0022272505791295365,
    -0.0, 0.046443619061753413, 0.0024969960858533739, 0.046323582693201582,
    -0.0, 0.0022272552454330598, -0.0, 0.046443865787082032,
    0.0024970073615036845, 0.046324106929570966, -0.0, 0.0022272570785712596,
    -0.0, 0.046443963091434129, 0.0024970118369536023, 0.046324316114692905,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    1.3255939203149854, -0.0, -0.0, -0.0, -0.0, -0.0, 1.8132526709407237, -0.0,
    0.015690215320898468, 1.1089316623878867, -0.0, -0.0, 1.992652299603284,
    -0.0, 0.025580852808335441, 1.8079686639012205, -0.0, -0.0,
    2.0586497347420312, -0.0, 0.030300489269799454, 2.141536699778122, -0.0,
    -0.0, 2.0829288342996217, -0.0, 0.032320518038765553, 2.2843055410608342,
    -0.0, -0.0, 2.0918606158770139, -0.0, 0.0331381323807636, 2.3420917736217368,
    -0.0, -0.0, 2.0951464346923703, -0.0, 0.033458468080839424,
    2.3647320238121932, -0.0, -0.0, 2.0963552198819544, -0.0,
    0.033581445260780718, 2.3734236373942217, -0.0, -0.0, 2.0967999071019947,
    -0.0, 0.033628033206073091, 2.3767163167210308, -0.0, -0.0,
    2.0969634983879994, -0.0, 0.033645525572207312, 2.3779526183433854, -0.0,
    -0.0, 2.0970236802588755, -0.0, 0.033652053475616443, 2.37841398860704, -0.0,
    -0.0, 2.097045819931902, -0.0, 0.033654479321829169, 2.3785854392607342,
    -0.0, -0.0, 2.0970539646624426, -0.0, 0.033655378136290805,
    2.3786489644447255, -0.0, -0.0, 2.0970569609413623, -0.0,
    0.033655710470412881, 2.37867245270304, -0.0, -0.0, 2.0970580632107767, -0.0,
    0.033655833169962318, 2.3786811246946313, -0.0, -0.0, 2.0970584687130329,
    -0.0, 0.033655878424272548, 2.3786843231171164, -0.0, -0.0,
    2.0970586178889765, -0.0, 0.033655895102764781, 2.378685501896868, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.00073162693504539038, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0011928224408164472,
    0.013573094713127674, -0.0, -0.0, -0.0, -0.0, 0.0014128967411499915,
    0.022129163361298769, -0.0, -0.0, -0.0, -0.0, 0.001507089677748745,
    0.026211967286727214, -0.0, -0.0, -0.0, -0.0, 0.0015452146277797642,
    0.027959428442846615, -0.0, -0.0, -0.0, -0.0, 0.0015601517221177834,
    0.028666720004866784, -0.0, -0.0, -0.0, -0.0, 0.0015658860868413276,
    0.028943831995250625, -0.0, -0.0, -0.0, -0.0, 0.0015680584595543343,
    0.029050215551929624, -0.0, -0.0, -0.0, -0.0, 0.0015688741198852938,
    0.02909051726742623, -0.0, -0.0, -0.0, -0.0, 0.0015691785127738436,
    0.029105649344165818, -0.0, -0.0, -0.0, -0.0, 0.001569291628775964,
    0.029111296420986511, -0.0, -0.0, -0.0, -0.0, 0.0015693335400471795,
    0.029113394941607893, -0.0, -0.0, -0.0, -0.0, 0.0015693490366219668,
    0.029114172476751157, -0.0, -0.0, -0.0, -0.0, 0.0015693547580409182,
    0.029114459968185985, -0.0, -0.0, -0.0, -0.0, 0.0015693568682268917,
    0.02911456611157355, -0.0, -0.0, -0.0, -0.0, 0.0015693576459366876,
    0.029114605259604753, -0.0, -0.0, -0.0, -0.0, 0.0015693579324117558,
    0.029114619687625666, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0,
    -0.0, -0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0020118140273929969, -0.0, -0.0,
    -0.0022744530300585152, -0.0, -0.0, -0.0065012879409001422, -0.0,
    -0.21045114773980311, -0.0087224555623925618, -0.17748125766556958, -0.0,
    -0.0095457871680659171, -0.0, -0.36605572041663792, -0.013719157871255388,
    -0.34687302386491903, -0.0, -0.011183272161520617, -0.0,
    -0.45234526133530162, -0.016674144858187984, -0.45788045196061161, -0.0,
    -0.011977914925767425, -0.0, -0.49488011296939011, -0.018213329045585095,
    -0.51943665704909237, -0.0, -0.012341668145753203, -0.0,
    -0.51453662450077953, -0.018957289389237117, -0.55046934575377737, -0.0,
    -0.012502018635023749, -0.0, -0.52325715056671351, -0.019299567007558142,
    -0.56518279729699372, -0.0, -0.012570865518103368, -0.0, -0.5270185369656204,
    -0.019451638388249818, -0.57186804898857435, -0.0, -0.012599854895524544,
    -0.0, -0.52860782222330771, -0.019517475507268144, -0.57481263186760556,
    -0.0, -0.012611879956590235, -0.0, -0.5292688501650199,
    -0.019545417373701877, -0.57607942107836108, -0.0, -0.01261680915065729,
    -0.0, -0.52954039792849927, -0.019557091433158428, -0.57661449233265638,
    -0.0, -0.01261881026700901, -0.0, -0.529650834094031, -0.019561907458992025,
    -0.57683721067859473, -0.0, -0.01261961619326468, -0.0, -0.52969537671465872,
    -0.019563873710120225, -0.57692881677486907, -0.0, -0.012619938592013507,
    -0.0, -0.5297132176342868, -0.019564669544281918, -0.57696612576070594, -0.0,
    -0.012620066823488117, -0.0, -0.52972032133680569, -0.019564989303869712,
    -0.57698119581402907, -0.0, -0.01262011757392629, -0.0, -0.52972313540304339,
    -0.019565116978433567, -0.57698724046683247, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.15111386878045993,
    -0.0, -0.0, -0.0, -0.0, -0.0, 0.2067055543806702, 0.027970114811385716, -0.0,
    1.569955619699267, 0.023126637690443281, -0.0, 0.22715659261305407,
    0.048650818194047887, -0.0, 2.7307583805705788, 0.046296662098209762,
    0.42904385928478755, 0.23468010912935924, 0.060119172690744765, -0.0,
    3.3744742792076288, 0.061860993210828941, 0.85889262609185368,
    0.23744785618102171, 0.065772288373257631, -0.0, 3.6917822629045118,
    0.070620667065829756, 1.1476410718075019, 0.23846605341969121,
    0.068384746847487687, -0.0, 3.8384189102871278, 0.075080065868358123,
    1.3101499642427674, 0.23884062725085525, 0.069543752716067816, -0.0,
    3.9034736227512008, 0.077208920228197558, 1.3928804371258774,
    0.23897842526254132, 0.070043661652451877, -0.0, 3.9315333875861511,
    0.078181065547962128, 1.4323748030006969, 0.23902911831807491,
    0.070254886402722733, -0.0, 3.943389380525169, 0.078610892069903945,
    1.4504099789463032, 0.2390477672510159, 0.07034274065118748, -0.0,
    3.9483206177410972, 0.078796358243172174, 1.4583840922724736,
    0.23905462781004466, 0.070378830842202658, -0.0, 3.9503463512277985,
    0.078874881912293943, 1.4618248485039194, 0.23905715166866628,
    0.0703935084158934, -0.0, 3.9511701998052793, 0.078907629531095383,
    1.4632816144418026, 0.23905808014436561, 0.070399428375115938, -0.0,
    3.9515024856508147, 0.078921120287127972, 1.4638891461090091,
    0.23905842171148703, 0.070401799531442225, -0.0, 3.9516355780683736,
    0.07892662203248263, 1.4641394257264082, 0.23905854736700877,
    0.070402743652570446, -0.0, 3.9516885713535608, 0.078928846818758974,
    1.4642414937438761, 0.23905859359309189, 0.070403117657448069, -0.0,
    3.9517095641547479, 0.0789297400435419, 1.4642827678323478, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.0008848536326911935, -0.0, -0.0, 0.00073162693504539038, -0.0, -0.0,
    0.001539101769967648, -0.0, 0.018451459275849919, 0.0014646264384442849,
    0.013573094713127674, -0.0, 0.001901910975643907, -0.0, 0.032094204714484667,
    0.0019570146541624217, 0.027171653223950546, -0.0, 0.0020807511406352513,
    -0.0, 0.039659703725975104, 0.0022341329028380532, 0.036306406972670284,
    -0.0, 0.0021633980438305277, -0.0, 0.043388978149800285,
    0.0023752090212825054, 0.04144748647075773, -0.0, 0.0022000639838897396,
    -0.0, 0.045112377266041406, 0.0024425567789330247, 0.0440647213286955, -0.0,
    0.0022158789435835825, -0.0, 0.045876955807416291, 0.0024733112582584816,
    0.0453141524930232, -0.0, 0.0022225611824249971, -0.0, 0.046206738128423033,
    0.0024869091130378415, 0.0458847075679419, -0.0, 0.0022253405114132981, -0.0,
    0.046346079883147893, 0.0024927764617514378, 0.046136974074237426, -0.0,
    0.0022264822491873345, -0.0, 0.046404035994472036, 0.0024952606115071032,
    0.046245824741141382, -0.0, 0.0022269465842280354, -0.0,
    0.046427844144501622, 0.00249629660473251, 0.046291910523799384, -0.0,
    0.0022271338661701643, -0.0, 0.046437526716598641, 0.0024967233939882454,
    0.046311130201885362, -0.0, 0.0022272088793155571, -0.0,
    0.046441432023646756, 0.0024968974454498156, 0.046319047968048914, -0.0,
    0.0022272387472304957, -0.0, 0.04644299623940655, 0.0024969678280789844,
    0.046322276959300725, -0.0, 0.0022272505791295365, -0.0,
    0.046443619061753413, 0.0024969960858533739, 0.046323582693201582, -0.0,
    0.0022272552454330598, -0.0, 0.046443865787082032, 0.0024970073615036845,
    0.046324106929570966, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -1.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 1.3255939203149854, -0.0, -0.0,
    -0.0, -0.0, -0.0, 1.8132526709407237, -0.0, 0.015690215320898468,
    1.1089316623878867, -0.0, -0.0, 1.992652299603284, -0.0,
    0.025580852808335441, 1.8079686639012205, -0.0, -0.0, 2.0586497347420312,
    -0.0, 0.030300489269799454, 2.141536699778122, -0.0, -0.0,
    2.0829288342996217, -0.0, 0.032320518038765553, 2.2843055410608342, -0.0,
    -0.0, 2.0918606158770139, -0.0, 0.0331381323807636, 2.3420917736217368, -0.0,
    -0.0, 2.0951464346923703, -0.0, 0.033458468080839424, 2.3647320238121932,
    -0.0, -0.0, 2.0963552198819544, -0.0, 0.033581445260780718,
    2.3734236373942217, -0.0, -0.0, 2.0967999071019947, -0.0,
    0.033628033206073091, 2.3767163167210308, -0.0, -0.0, 2.0969634983879994,
    -0.0, 0.033645525572207312, 2.3779526183433854, -0.0, -0.0,
    2.0970236802588755, -0.0, 0.033652053475616443, 2.37841398860704, -0.0, -0.0,
    2.097045819931902, -0.0, 0.033654479321829169, 2.3785854392607342, -0.0,
    -0.0, 2.0970539646624426, -0.0, 0.033655378136290805, 2.3786489644447255,
    -0.0, -0.0, 2.0970569609413623, -0.0, 0.033655710470412881, 2.37867245270304,
    -0.0, -0.0, 2.0970580632107767, -0.0, 0.033655833169962318,
    2.3786811246946313, -0.0, -0.0, 2.0970584687130329, -0.0,
    0.033655878424272548, 2.3786843231171164, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.00073162693504539038, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0011928224408164472,
    0.013573094713127674, -0.0, -0.0, -0.0, -0.0, 0.0014128967411499915,
    0.022129163361298769, -0.0, -0.0, -0.0, -0.0, 0.001507089677748745,
    0.026211967286727214, -0.0, -0.0, -0.0, -0.0, 0.0015452146277797642,
    0.027959428442846615, -0.0, -0.0, -0.0, -0.0, 0.0015601517221177834,
    0.028666720004866784, -0.0, -0.0, -0.0, -0.0, 0.0015658860868413276,
    0.028943831995250625, -0.0, -0.0, -0.0, -0.0, 0.0015680584595543343,
    0.029050215551929624, -0.0, -0.0, -0.0, -0.0, 0.0015688741198852938,
    0.02909051726742623, -0.0, -0.0, -0.0, -0.0, 0.0015691785127738436,
    0.029105649344165818, -0.0, -0.0, -0.0, -0.0, 0.001569291628775964,
    0.029111296420986511, -0.0, -0.0, -0.0, -0.0, 0.0015693335400471795,
    0.029113394941607893, -0.0, -0.0, -0.0, -0.0, 0.0015693490366219668,
    0.029114172476751157, -0.0, -0.0, -0.0, -0.0, 0.0015693547580409182,
    0.029114459968185985, -0.0, -0.0, -0.0, -0.0, 0.0015693568682268917,
    0.02911456611157355, -0.0, -0.0, -0.0, -0.0, 0.0015693576459366876,
    0.029114605259604753, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  int32_T c3_i123;
  static real_T c3_d_Linv[676] = { 0.29712467814611188, 0.36687421536743942,
    0.72780771462029814, 0.39460138755235113, 0.300152949625866,
    -2.3137798140875825, -0.025797467644069549, -0.11669494578165823,
    0.077971528881255414, 0.0027985884109650713, 1.5738194222526065,
    0.0046180424629101288, -0.20361507832930947, -0.0012653837952872804,
    -0.094934244705118673, 0.10438038673806628, 0.030015308476722367,
    -0.13532627510309614, 0.0010291482878993594, -0.079651103363127876,
    -0.155734718154074, 0.020923035097814582, -0.10067090474354742,
    0.007223706301166438, -0.056164638103425021, 0.0, 0.0, 0.077517596515919343,
    -0.0050148664136989256, 0.028748972464855166, 0.027617021379426329,
    0.0027291945148897163, -0.020379964759084344, -0.0018409205912863641,
    0.014277247198326962, 0.01393882058827748, -0.0012567437523685694,
    -0.012360329582170352, -0.00082381350693877466, 0.0092051165637046638,
    0.0083725105011779061, -0.00095213265950272062, -0.0083733098911752749,
    -0.00035596089133772352, 0.0063908801331844086, 0.0052011583024000928,
    -0.00054338783306294967, -0.0059169387945764117, -8.5587129599924182E-5,
    0.0045739321882051669, 0.0031835218248334792, 0.0, 0.0, 0.0,
    8.48677302245032, 0.75699611815647216, -0.32736801054467807,
    0.0482351738961819, -0.2324931237049456, -2.2816763511700393,
    0.51172673423880943, -0.2521416597217313, -0.18013627797637413,
    -0.1125104044624497, -1.7271744226706334, 0.37266854942715011,
    -0.19615307564270765, -0.03527686136762484, -0.057048046152843972,
    -1.3641958104273957, 0.27692154515198975, -0.16110282324579159,
    -0.012984601197030691, -0.023714250604001071, -1.0995640744847974,
    0.20923258757516522, -0.1344054402593719, 0.0, 0.0, 0.0, 0.0,
    0.088272229994219714, -0.021032192676197475, -0.00049176280330726638,
    0.017053632746715123, 0.0061376465515989281, -0.012739641134683411,
    -0.010138085293768818, 0.00014605947463867223, 0.010355528189636984,
    0.0042548829857047563, -0.0083288373033555858, -0.0057957217451265431,
    0.00075295589066506951, 0.0070113177048685147, 0.0030871234322724789,
    -0.0058663866913335949, -0.0033956754846083907, 0.00058372374554103729,
    0.0049631900979966647, 0.0023070260187175, -0.0042607096095766761,
    -0.0018979094095671334, 0.0, 0.0, 0.0, 0.0, 0.0, 8.103679501369955,
    -0.14983678992185706, 1.9432566877746593, -0.24852238677289981,
    -1.2248885305820423, -2.4206850346437463, 0.0076477928188238833,
    1.0583289127327018, -0.2108457289066456, -0.67627242417856193,
    -1.6458561515199379, 0.09477081545849686, 0.63821951462777,
    -0.1762066606061817, -0.39877857788120458, -1.1898978558072617,
    0.067460807289852223, 0.39345068643401077, -0.1460561321442603,
    -0.23243402869064109, -0.88567109409756628, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    2.4166547709857511, 0.42924167217297204, 0.68722528131150606,
    0.28605684124883707, 0.23269622285273231, -4.4015115214617913,
    -0.047784053507167017, 0.0065478726680805255, 0.12940532019772175,
    0.10113582097946824, 1.4046309118608893, -0.051817309433252315,
    -0.15018630125171464, 0.034413150265125383, -0.019117843048500085,
    0.345146700296659, -0.0086752989570860559, -0.10832985651332383,
    0.019135632178705963, -0.034130859980715883, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.090034554742055919, -0.0022006174035403567, 0.014476682069853872,
    0.014244798796930639, 0.0034262059604791293, -0.013207838030864909,
    -0.0010626185040225704, 0.009747012460396668, 0.0090690747653051074,
    -0.000806124744460449, -0.0091323435030439219, -0.00048598335025100349,
    0.0069621711185568957, 0.0059322758800091427, -0.00077293938507778069,
    -0.00653451881662323, -0.00018502645713392861, 0.0050505390885314441,
    0.0037944674396918556, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    8.89775920079816, 0.49380984066157446, -0.2707243973165383,
    0.31158497294828341, -0.1175829572674815, -1.7652647136493496,
    0.37232496976813773, -0.21051569204175502, -0.15061370149135217,
    -0.060251178650886188, -1.3897759383058057, 0.28645062145244204,
    -0.16396217261589111, -0.053857612455363753, -0.029595146579841265,
    -1.1246312849236808, 0.2190797773123016, -0.13500140713655287, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0937012913893807, -0.010528746139757688,
    3.3094054843559136E-5, 0.011084508293764415, 0.0043617447185901187,
    -0.0088631105211395816, -0.0064770908747715959, -0.00014349958875356375,
    0.0076899375369481665, 0.0032561274997822817, -0.0063699252360494164,
    -0.0040215525276357158, 0.000460794044765196, 0.0054937582616795561,
    0.002444618537844113, -0.0046727399982319159, -0.0024019259937881174, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 8.8418819206829138,
    -0.029399102764558718, 1.15916868622153, -0.20800084570621116,
    -0.74775588357700873, -1.7413780209089031, -0.026264053674691909,
    0.72907298920994379, -0.16855485763610795, -0.46332215971293056,
    -1.2799127050453663, 0.053559329909606213, 0.46353286257315168,
    -0.14184136024889293, -0.28412443461152703, -0.95932270265136765, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.9310060185086693,
    0.45351062541559195, 0.68385552240459291, 0.23717064531813448,
    0.1992289577960458, -4.340401689633171, -0.03464019379022968,
    0.027166553041370698, 0.11647574305032729, 0.09805010290194284,
    1.3210468125812225, -0.04481630151918066, -0.13002296178781625,
    0.028003907569031972, -0.018276895449589294, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.093067720953149247, -0.0014587789915538002,
    0.010362315101416612, 0.00991783569696651, 0.0037724862187972319,
    -0.010355159069452294, -0.00076549054981417332, 0.0077998514912961409,
    0.0070213532267854838, -0.00059235138241849246, -0.0075742052328772961,
    -0.00034902703953003595, 0.0058399350258974813, 0.0048117386288248276, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    9.1238602955886119, 0.37415761177177526, -0.21517284327838743,
    0.31603942572455929, -0.077873899067423619, -1.4438574765072911,
    0.29883871918122829, -0.16971131820404781, -0.13536217061423617,
    -0.041501882536477019, -1.1654553611364071, 0.23716278175998171,
    -0.13341826739589027, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.095391551781934883, -0.0072256504323097151,
    -0.00030052417597617329, 0.0086909691948361331, 0.0034539659597756876,
    -0.007129426418669902, -0.004971454091018619, -0.00028075498591974762,
    0.0063794991396118085, 0.0026774600453255263, -0.0053495888912734272,
    -0.0032296370714846377, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 9.120664871954661, -0.07237300966893781,
    0.86567897129901106, -0.16347765532918021, -0.562378206752701,
    -1.4165729229457635, -0.0419297676898925, 0.58148900790161562,
    -0.13409327656144807, -0.36972659958275544, -1.080844294319655, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    2.9406114059330468, 0.46909586586853036, 0.69741547519188241,
    0.21713704171386705, 0.18889350165692503, -4.3488142074266527,
    -0.028537647738933889, 0.044190413988208395, 0.1099778564750125,
    0.099547169564846369, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0942937311635701, -0.0011955714044736953,
    0.0086068520202008791, 0.0081205617716697039, 0.0038966140441117156,
    -0.0089807088622557516, -0.00065364650599328234, 0.0068290983984561288,
    0.0060958791722903194, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 9.2640523434316773, 0.30775738959662208,
    -0.17310560607692324, 0.3253480244127811, -0.062461962880258994,
    -1.232490659482407, 0.25473636483148876, -0.1391017678810941, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.096143154511082712, -0.0059155328023466859, -0.00041258769516994511,
    0.0075352279549351234, 0.0029243711159337828, -0.0062411012067736353,
    -0.0043347898313161526, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 9.2551482158886067,
    -0.083462761632394841, 0.73834213151840544, -0.12940299696412561,
    -0.48463059434442868, -1.2423637736556525, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    2.9534740614474808, 0.474604989408461, 0.70649117047629606,
    0.20761388981516968, 0.18692022120001789, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.094894134847229292, -0.0010954939154774047, 0.0077266578522594311,
    0.0073113042915332891, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    9.3578307317261142, 0.267440101398483, -0.14263470503234765, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0965331635878268, -0.00536756932003923, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 9.3288016209654234, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.001 };

  int32_T c3_i124;
  static real_T c3_d_H[676] = { 11.327199547711144, -53.609214335270529,
    -1.0030745775553456, -24.573926256685418, -0.34115164809652343,
    10.89942089353165, -51.424861321476847, -0.966876772001972,
    -23.8137807180428, -0.33121056887659878, 10.362859095622113,
    -48.7400076543901, -0.91992416418164225, -22.750524055643712,
    -0.31691716854403823, 9.7588583195317078, -45.790126887203492,
    -0.8667867861993962, -21.501625555369564, -0.29988794671456492,
    9.1205596773652111, -42.712192906915959, -0.81048570907498951,
    -20.1533564112801, -0.28137597143814852, 0.0, -53.609214335270529,
    420.13860955611517, 4.8456743996000791, 61.2600399326549,
    0.90856734861464261, -51.829507960312974, 308.13850312012113,
    4.6888466177729251, 60.246733355741839, 0.89470457392442493,
    -49.424795115409296, 292.73485337740522, 4.4744596519447892,
    58.274790041937962, 0.86659940069691954, -46.636258773153365,
    275.49303443155077, 4.2243796799737572, 55.519820476002842,
    0.82668964964512859, -43.641828724017749, 257.35161801865542,
    3.9550935046942293, 52.2771583600203, 0.77938268361725449, 0.0,
    -1.0030745775553456, 4.84567439960008, 0.10276888988054142,
    2.0245416881272189, 0.030045178552170707, -0.96562327952374727,
    4.6464984201968251, 0.089372949912823338, 1.962157915356721,
    0.029156052217555378, -0.91792440216939553, 4.4033068633943016,
    0.08501397751377765, 1.8750025687386056, 0.027893479959880851,
    -0.86440897979097242, 4.1368558496073007, 0.080108517534011728,
    1.7724187224518455, 0.026396891595957889, -0.80793100885731139,
    3.8591760843612963, 0.074924949937385132, 1.6614827039816784,
    0.024773202073116944, 0.0, -24.573926256685418, 61.2600399326549,
    2.0245416881272189, 200.87589392261881, 1.3045613792119628,
    -23.515665253973609, 57.9595973129627, 1.9380030878940733,
    97.044640061294643, 1.2568123994148355, -22.243516588468275,
    54.395588373939916, 1.8335913376664812, 92.126278073671713,
    1.1942879261089576, -20.873242385669922, 50.719996147731621,
    1.7208414874100755, 86.705248800049475, 1.1247367748638677,
    -19.461768622456486, 46.99952881426568, 1.6045616238634315,
    81.072330461208438, 1.0521830209149754, 0.0, -0.34115164809652343,
    0.90856734861464261, 0.030045178552170707, 1.3045613792119628,
    0.029366919102046043, -0.32616860221797628, 0.85957222983404957,
    0.028743146904746039, 1.2540868507559264, 0.018640719935203675,
    -0.30841947249497337, 0.80701157588367478, 0.027193152951217582,
    1.1901074661155815, 0.01770846367674659, -0.28941480846566425,
    0.75296026207688249, 0.025530360864083165, 1.1199023750714661,
    0.016680928792426133, -0.26988582361642416, 0.6983137508011843,
    0.023820410737092516, 1.0470768912098223, 0.015613231137237175, 0.0,
    10.89942089353165, -51.829507960312974, -0.96562327952374727,
    -23.515665253973609, -0.32616860221797628, 10.659465773974683,
    -50.427715782139515, -0.9440469360390642, -23.135596993570278,
    -0.3212822858204929, 10.2316872482816, -48.243363684064377,
    -0.90784914169788233, -22.3754514905172, -0.311341207044197,
    9.6951257778572035, -45.558512343778439, -0.86089656244623725,
    -21.312194924796724, -0.29704780791676355, 9.0911258333677054,
    -42.60863746465899, -0.80775925698471651, -20.063296687079276,
    -0.28001858936019086, 0.0, -51.424861321476847, 308.13850312012113,
    4.6464984201968251, 57.9595973129627, 0.85957222983404957,
    -50.427715782139515, 401.25963059438368, 4.5589175058120288,
    57.511259814894174, 0.85354752646104326, -48.648009920607052,
    289.25952787642575, 4.4020897688850154, 56.497953330739691,
    0.83968475293852607, -46.243298386729187, 273.85588760940436,
    4.1877029176903156, 54.526010268913488, 0.81157958288312493,
    -43.454765380525593, 256.61409272339307, 3.9376232373639342,
    51.771041387291312, 0.77166984044625431, 0.0, -0.966876772001972,
    4.6888466177729251, 0.089372949912823338, 1.9380030878940733,
    0.028743146904746039, -0.9440469360390642, 4.55891750581203,
    0.097346312418292252, 1.9059464441635148, 0.02830458858539206,
    -0.90659564901592826, 4.3597416049853139, 0.083950373412118,
    1.8435626743274982, 0.027415462287717744, -0.858896799725811,
    4.1165502479077132, 0.0795914034637634, 1.7564073356808703,
    0.026152890130394919, -0.8053814486294496, 3.8500997397204024,
    0.074685949706934762, 1.6538235110428219, 0.024656302039010904, 0.0,
    -23.8137807180428, 60.246733355741839, 1.962157915356721, 97.044640061294643,
    1.2540868507559264, -23.135596993570278, 57.511259814894174,
    1.9059464441635148, 195.10447410963073, 1.2300250008678026,
    -22.077336354299625, 54.210819735633471, 1.819407875549403,
    91.273220391112659, 1.1822760228323885, -20.80518861306766,
    50.646817227608651, 1.7149962056900916, 86.35485879142098,
    1.1197515543122107, -19.43491675143299, 46.971241206149777,
    1.6022465588826869, 80.933830571330063, 1.050200416064067, 0.0,
    -0.33121056887659878, 0.89470457392442493, 0.029156052217555378,
    1.2568123994148357, 0.018640719935203675, -0.3212822858204929,
    0.85354752646104326, 0.02830458858539206, 1.2300250008678026,
    0.028272969075335327, -0.30629924474848746, 0.80455244132011139,
    0.027002557356546619, 1.1795504742560696, 0.017546769931710157,
    -0.28855012725146428, 0.75199187255271971, 0.025452564467231754,
    1.1155710946257555, 0.016614513736323496, -0.26954549419711166,
    0.69794077346250871, 0.023789775074919025, 1.0453660171877217,
    0.015586979023292081, 0.0, 10.362859095622113, -49.424795115409296,
    -0.91792440216939553, -22.243516588468275, -0.30841947249497337,
    10.2316872482816, -48.648009920607052, -0.90659564901592826,
    -22.077336354299625, -0.30629924474848746, 9.9917322572110177,
    -47.246218658151953, -0.8850193167434347, -21.697268129485828,
    -0.30141292879463272, 9.5639540590030059, -45.061868886877129,
    -0.84882155097093137, -20.937122723111337, -0.2914718512234637,
    9.0273934201793367, -42.377023434657104, -0.80186904423999616,
    -19.873866419947493, -0.27717845536893004, 0.0, -48.7400076543901,
    292.73485337740522, 4.4033068633943016, 54.395588373939916,
    0.80701157588367478, -48.243363684064377, 289.25952787642575,
    4.3597416049853139, 54.210819735633471, 0.80455244132011139,
    -47.246218658151953, 382.380659068723, 4.27216073550064, 53.762482330323451,
    0.7985277391148049, -45.4665141076448, 270.38056582645618,
    4.1153331132070221, 52.749176098146478, 0.78466496876438963,
    -43.06180590981802, 254.97694961926908, 3.9009465536568619,
    50.777233720632751, 0.75655980732390327, 0.0, -0.91992416418164225,
    4.4744596519447883, 0.08501397751377765, 1.8335913376664812,
    0.027193152951217582, -0.90784914169788233, 4.4020897688850154,
    0.083950373412118, 1.819407875549403, 0.027002557356546619,
    -0.8850193167434347, 4.2721607355006412, 0.091923736879130524,
    1.7873512347533251, 0.026563999074133642, -0.847568057784527,
    4.0729850343988057, 0.07852780032364684, 1.7249674728887938,
    0.025674872876811, -0.799869279776456, 3.8297941829207849,
    0.074168836598228136, 1.637812155890872, 0.024412300992027049, 0.0,
    -22.750524055643712, 58.274790041937962, 1.8750025687386056,
    92.126278073671713, 1.1901074661155815, -22.3754514905172,
    56.497953330739691, 1.8435626743274982, 91.273220391112659,
    1.1795504742560696, -21.697268129485828, 53.762482330323451,
    1.7873512347533251, 189.33305458225482, 1.1554886261296591,
    -20.639008414488522, 50.462048682060562, 1.7008127465074918, 85.501801251668,
    1.107739652879945, -19.366863014420176, 46.898062378784743,
    1.5964012800971763, 80.583440705507627, 1.0452151973567128, 0.0,
    -0.31691716854403823, 0.86659940069691954, 0.027893479959880844,
    1.1942879261089576, 0.01770846367674659, -0.311341207044197,
    0.83968475293852607, 0.027415462287717744, 1.1822760228323888,
    0.017546769931710157, -0.30141292879463272, 0.7985277391148049,
    0.026563999074133642, 1.1554886261296591, 0.027179019095059005,
    -0.28642989994860674, 0.74953273915685414, 0.025261968909501768,
    1.1050141045279567, 0.016452820014504259, -0.26868081342653932,
    0.69697238510603876, 0.02371197871500853, 1.0410347385037237,
    0.015520563990406636, 0.0, 9.7588583195317078, -46.636258773153365,
    -0.86440897979097242, -20.873242385669922, -0.28941480846566425,
    9.6951257778572035, -46.243298386729187, -0.858896799725811,
    -20.80518861306766, -0.28855012725146428, 9.5639540590030059,
    -45.4665141076448, -0.847568057784527, -20.639008414488522,
    -0.28642989994860674, 9.3239993954173137, -44.064725171988755,
    -0.82599175408069647, -20.258940286353255, -0.281543585199878,
    8.8962220288095786, -41.880381288776661, -0.7897940608288635,
    -19.498795142535226, -0.2716025109016067, 0.0, -45.790126887203492,
    275.49303443155077, 4.1368558496073007, 50.719996147731621,
    0.75296026207688249, -45.558512343778439, 273.85588760940436,
    4.1165502479077132, 50.646817227608651, 0.75199187255271971,
    -45.061868886877129, 270.38056582645618, 4.0729850343988057,
    50.462048682060562, 0.74953273915685414, -44.064725171988755,
    363.50170649443561, 3.9854042795474163, 50.013711528727612,
    0.74350804012364424, -42.285023957529489, 251.50163731198074,
    3.8285769488980606, 49.000405980861942, 0.72964527838812909, 0.0,
    -0.8667867861993962, 4.2243796799737572, 0.080108517534011728,
    1.7208414874100755, 0.025530360864083165, -0.86089656244623725,
    4.1877029176903147, 0.0795914034637634, 1.7149962056900916,
    0.025452564467231754, -0.84882155097093137, 4.1153331132070221,
    0.07852780032364684, 1.7008127465074918, 0.025261968909501768,
    -0.82599175408069647, 3.9854042795474167, 0.086501166241348543,
    1.6687561136828941, 0.0248234107274404, -0.78854056640379555,
    3.7862290840448853, 0.073105235908797347, 1.6063723734670541,
    0.023934284802656452, 0.0, -21.501625555369564, 55.519820476002842,
    1.7724187224518455, 86.705248800049475, 1.1199023750714661,
    -21.312194924796724, 54.526010268913488, 1.7564073356808703,
    86.35485879142098, 1.1155710946257555, -20.937122723111337,
    52.749176098146478, 1.7249674728887938, 85.501801251668, 1.1050141045279567,
    -20.258940286353255, 50.013711528727612, 1.6687561136828941,
    183.56163583074141, 1.0809522611872457, -19.200682912519408,
    46.713294085212645, 1.5822178288860429, 79.730383553685783,
    1.0332033009344763, 0.0, -0.29988794671456492, 0.82668964964512859,
    0.026396891595957889, 1.1247367748638677, 0.016680928792426133,
    -0.29704780791676355, 0.81157958288312493, 0.026152890130394912,
    1.1197515543122107, 0.016614513736323496, -0.2914718512234637,
    0.78466496876438963, 0.025674872876811, 1.1077396528799452,
    0.016452820014504259, -0.281543585199878, 0.74350804012364424,
    0.0248234107274404, 1.0809522611872457, 0.026085069240923527,
    -0.26656058732880583, 0.69451325488225635, 0.023521383257629983,
    1.0304777531916236, 0.015358870331657807, 0.0, 9.1205596773652111,
    -43.641828724017749, -0.80793100885731139, -19.461768622456486,
    -0.26988582361642416, 9.0911258333677054, -43.454765380525593,
    -0.8053814486294496, -19.43491675143299, -0.26954549419711166,
    9.0273934201793367, -43.06180590981802, -0.799869279776456,
    -19.366863014420176, -0.26868081342653932, 8.8962220288095786,
    -42.285023957529489, -0.78854056640379555, -19.200682912519408,
    -0.26656058732880583, 8.656268196823012, -40.883240909928112,
    -0.7669643352205352, -18.82061504694018, -0.2616742758529696, 0.0,
    -42.712192906915959, 257.35161801865542, 3.8591760843612963,
    46.99952881426568, 0.6983137508011843, -42.60863746465899,
    256.61409272339307, 3.8500997397204024, 46.971241206149777,
    0.69794077346250871, -42.377023434657104, 254.97694961926908,
    3.8297941829207849, 46.898062378784743, 0.69697238510603876,
    -41.880381288776661, 251.50163731198074, 3.7862290840448853,
    46.713294085212645, 0.69451325488225635, -40.883240909928112,
    344.62280203971545, 3.6986486208370564, 46.264957616188042, 0.68848856446391,
    0.0, -0.81048570907498951, 3.9550935046942293, 0.074924949937385132,
    1.6045616238634315, 0.023820410737092516, -0.80775925698471651,
    3.9376232373639342, 0.074685949706934762, 1.6022465588826869,
    0.023789775074919025, -0.80186904423999616, 3.9009465536568615,
    0.074168836598228136, 1.5964012800971763, 0.02371197871500853,
    -0.7897940608288635, 3.8285769488980606, 0.073105235908797347,
    1.5822178288860429, 0.023521383257629983, -0.7669643352205352,
    3.6986486208370568, 0.0810786080494228, 1.5501612177100994,
    0.02308282534810685, 0.0, -20.1533564112801, 52.2771583600203,
    1.6614827039816784, 81.072330461208438, 1.0470768912098223,
    -20.063296687079276, 51.771041387291312, 1.6538235110428219,
    80.933830571330063, 1.0453660171877217, -19.873866419947493,
    50.777233720632751, 1.637812155890872, 80.583440705507627,
    1.0410347385037237, -19.498795142535226, 49.000405980861942,
    1.6063723734670541, 79.730383553685783, 1.0304777531916236,
    -18.82061504694018, 46.264957616188042, 1.5501612177100994,
    177.79021918629019, 1.0064159228478551, 0.0, -0.28137597143814852,
    0.77938268361725449, 0.024773202073116944, 1.0521830209149754,
    0.015613231137237175, -0.28001858936019086, 0.77166984044625431,
    0.024656302039010904, 1.050200416064067, 0.015586979023292081,
    -0.27717845536893004, 0.75655980732390327, 0.024412300992027042,
    1.0452151973567128, 0.015520563990406636, -0.2716025109016067,
    0.72964527838812909, 0.023934284802656452, 1.0332033009344765,
    0.015358870331657807, -0.2616742758529696, 0.68848856446391,
    0.02308282534810685, 1.0064159228478551, 0.024991119729366081, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0E+6 };

  int32_T c3_i125;
  int32_T c3_i126;
  static real_T c3_d_uoff[5] = { 30.0, 0.8, 170.0, 0.8, 120.0 };

  int32_T c3_i127;
  int32_T c3_i128;
  int32_T c3_i129;
  int32_T c3_i130;
  static real_T c3_d_Mu1[975] = { -0.0, -0.0020118140273929969, -0.0, -0.0,
    -0.0022744530300585152, -0.0, -0.0, -0.0065012879409001422, -0.0,
    -0.21045114773980311, -0.0087224555623925618, -0.17748125766556958, -0.0,
    -0.0095457871680659171, -0.0, -0.36605572041663792, -0.013719157871255388,
    -0.34687302386491903, -0.0, -0.011183272161520617, -0.0,
    -0.45234526133530162, -0.016674144858187984, -0.45788045196061161, -0.0,
    -0.011977914925767425, -0.0, -0.49488011296939011, -0.018213329045585095,
    -0.51943665704909237, -0.0, -0.012341668145753203, -0.0,
    -0.51453662450077953, -0.018957289389237117, -0.55046934575377737, -0.0,
    -0.012502018635023749, -0.0, -0.52325715056671351, -0.019299567007558142,
    -0.56518279729699372, -0.0, -0.012570865518103368, -0.0, -0.5270185369656204,
    -0.019451638388249818, -0.57186804898857435, -0.0, -0.012599854895524544,
    -0.0, -0.52860782222330771, -0.019517475507268144, -0.57481263186760556,
    -0.0, -0.012611879956590235, -0.0, -0.5292688501650199,
    -0.019545417373701877, -0.57607942107836108, -0.0, -0.01261680915065729,
    -0.0, -0.52954039792849927, -0.019557091433158428, -0.57661449233265638,
    -0.0, -0.01261881026700901, -0.0, -0.529650834094031, -0.019561907458992025,
    -0.57683721067859473, -0.0, -0.01261961619326468, -0.0, -0.52969537671465872,
    -0.019563873710120225, -0.57692881677486907, -0.0, -0.012619938592013507,
    -0.0, -0.5297132176342868, -0.019564669544281918, -0.57696612576070594, -0.0,
    -0.012620066823488117, -0.0, -0.52972032133680569, -0.019564989303869712,
    -0.57698119581402907, -0.0, -0.01262011757392629, -0.0, -0.52972313540304339,
    -0.019565116978433567, -0.57698724046683247, -0.0, -0.012620137572741176,
    -0.0, -0.52972424522380457, -0.01956516768177357, -0.57698965046115869, -0.0,
    -0.012620145423541175, -0.0, -0.52972468121233862, -0.01956518772292239,
    -0.57699060633058907, -0.0, -0.012620148495082108, -0.0,
    -0.52972485189736152, -0.019565195611734663, -0.57699098373340807, -0.0,
    -0.012620149693170527, -0.0, -0.52972491851308534, -0.019565198705667568,
    -0.57699113214653308, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0,
    -0.0, -0.0, -0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.15111386878045993, -0.0, -0.0,
    -0.0, -0.0, -0.0, 0.2067055543806702, 0.027970114811385716, -0.0,
    1.569955619699267, 0.023126637690443281, -0.0, 0.22715659261305407,
    0.048650818194047887, -0.0, 2.7307583805705788, 0.046296662098209762,
    0.42904385928478755, 0.23468010912935924, 0.060119172690744765, -0.0,
    3.3744742792076288, 0.061860993210828941, 0.85889262609185368,
    0.23744785618102171, 0.065772288373257631, -0.0, 3.6917822629045118,
    0.070620667065829756, 1.1476410718075019, 0.23846605341969121,
    0.068384746847487687, -0.0, 3.8384189102871278, 0.075080065868358123,
    1.3101499642427674, 0.23884062725085525, 0.069543752716067816, -0.0,
    3.9034736227512008, 0.077208920228197558, 1.3928804371258774,
    0.23897842526254132, 0.070043661652451877, -0.0, 3.9315333875861511,
    0.078181065547962128, 1.4323748030006969, 0.23902911831807491,
    0.070254886402722733, -0.0, 3.943389380525169, 0.078610892069903945,
    1.4504099789463032, 0.2390477672510159, 0.07034274065118748, -0.0,
    3.9483206177410972, 0.078796358243172174, 1.4583840922724736,
    0.23905462781004466, 0.070378830842202658, -0.0, 3.9503463512277985,
    0.078874881912293943, 1.4618248485039194, 0.23905715166866628,
    0.0703935084158934, -0.0, 3.9511701998052793, 0.078907629531095383,
    1.4632816144418026, 0.23905808014436561, 0.070399428375115938, -0.0,
    3.9515024856508147, 0.078921120287127972, 1.4638891461090091,
    0.23905842171148703, 0.070401799531442225, -0.0, 3.9516355780683736,
    0.07892662203248263, 1.4641394257264082, 0.23905854736700877,
    0.070402743652570446, -0.0, 3.9516885713535608, 0.078928846818758974,
    1.4642414937438761, 0.23905859359309189, 0.070403117657448069, -0.0,
    3.9517095641547479, 0.0789297400435419, 1.4642827678323478,
    0.23905861059871752, 0.070403265158730161, -0.0, 3.9517178433651945,
    0.0789300964654654, 1.4642993388796919, 0.23905861685473759,
    0.070403323104003851, -0.0, 3.9517210958190607, 0.078930237933888439,
    1.4643059511957419, 0.23905861915619875, 0.070403345788981983, -0.0,
    3.9517223691212675, 0.07893029382468969, 1.464308575708609,
    0.239058620002859, 0.070403354642578, -0.0, 3.95172286607142,
    0.0789303158159376, 1.4643096125910728, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0,
    -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0,
    -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0,
    0.0008848536326911935, -0.0, -0.0, 0.00073162693504539038, -0.0, -0.0,
    0.001539101769967648, -0.0, 0.018451459275849919, 0.0014646264384442849,
    0.013573094713127674, -0.0, 0.001901910975643907, -0.0, 0.032094204714484667,
    0.0019570146541624217, 0.027171653223950546, -0.0, 0.0020807511406352513,
    -0.0, 0.039659703725975104, 0.0022341329028380532, 0.036306406972670284,
    -0.0, 0.0021633980438305277, -0.0, 0.043388978149800285,
    0.0023752090212825054, 0.04144748647075773, -0.0, 0.0022000639838897396,
    -0.0, 0.045112377266041406, 0.0024425567789330247, 0.0440647213286955, -0.0,
    0.0022158789435835825, -0.0, 0.045876955807416291, 0.0024733112582584816,
    0.0453141524930232, -0.0, 0.0022225611824249971, -0.0, 0.046206738128423033,
    0.0024869091130378415, 0.0458847075679419, -0.0, 0.0022253405114132981, -0.0,
    0.046346079883147893, 0.0024927764617514378, 0.046136974074237426, -0.0,
    0.0022264822491873345, -0.0, 0.046404035994472036, 0.0024952606115071032,
    0.046245824741141382, -0.0, 0.0022269465842280354, -0.0,
    0.046427844144501622, 0.00249629660473251, 0.046291910523799384, -0.0,
    0.0022271338661701643, -0.0, 0.046437526716598641, 0.0024967233939882454,
    0.046311130201885362, -0.0, 0.0022272088793155571, -0.0,
    0.046441432023646756, 0.0024968974454498156, 0.046319047968048914, -0.0,
    0.0022272387472304957, -0.0, 0.04644299623940655, 0.0024969678280789844,
    0.046322276959300725, -0.0, 0.0022272505791295365, -0.0,
    0.046443619061753413, 0.0024969960858533739, 0.046323582693201582, -0.0,
    0.0022272552454330598, -0.0, 0.046443865787082032, 0.0024970073615036845,
    0.046324106929570966, -0.0, 0.0022272570785712596, -0.0,
    0.046443963091434129, 0.0024970118369536023, 0.046324316114692905, -0.0,
    0.0022272577962259938, -0.0, 0.046444001317049753, 0.0024970136050971674,
    0.046324399142945026, -0.0, 0.0022272580763155339, -0.0, 0.04644401628198476,
    0.0024970143008052731, 0.046324431945428, -0.0, 0.0022272581853282104, -0.0,
    0.046444022122567374, 0.0024970145735572964, 0.046324444852158961, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0,
    -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, -0.0, -0.0, 1.3255939203149854, -0.0, -0.0, -0.0, -0.0, -0.0,
    1.8132526709407237, -0.0, 0.015690215320898468, 1.1089316623878867, -0.0,
    -0.0, 1.992652299603284, -0.0, 0.025580852808335441, 1.8079686639012205,
    -0.0, -0.0, 2.0586497347420312, -0.0, 0.030300489269799454,
    2.141536699778122, -0.0, -0.0, 2.0829288342996217, -0.0,
    0.032320518038765553, 2.2843055410608342, -0.0, -0.0, 2.0918606158770139,
    -0.0, 0.0331381323807636, 2.3420917736217368, -0.0, -0.0, 2.0951464346923703,
    -0.0, 0.033458468080839424, 2.3647320238121932, -0.0, -0.0,
    2.0963552198819544, -0.0, 0.033581445260780718, 2.3734236373942217, -0.0,
    -0.0, 2.0967999071019947, -0.0, 0.033628033206073091, 2.3767163167210308,
    -0.0, -0.0, 2.0969634983879994, -0.0, 0.033645525572207312,
    2.3779526183433854, -0.0, -0.0, 2.0970236802588755, -0.0,
    0.033652053475616443, 2.37841398860704, -0.0, -0.0, 2.097045819931902, -0.0,
    0.033654479321829169, 2.3785854392607342, -0.0, -0.0, 2.0970539646624426,
    -0.0, 0.033655378136290805, 2.3786489644447255, -0.0, -0.0,
    2.0970569609413623, -0.0, 0.033655710470412881, 2.37867245270304, -0.0, -0.0,
    2.0970580632107767, -0.0, 0.033655833169962318, 2.3786811246946313, -0.0,
    -0.0, 2.0970584687130329, -0.0, 0.033655878424272548, 2.3786843231171164,
    -0.0, -0.0, 2.0970586178889765, -0.0, 0.033655895102764781,
    2.378685501896868, -0.0, -0.0, 2.0970586727677394, -0.0,
    0.033655901246408881, 2.3786859361089761, -0.0, -0.0, 2.0970586929565078,
    -0.0, 0.033655903508621209, 2.3786860959945368, -0.0, -0.0,
    2.0970587003835406, -0.0, 0.033655904341391735, 2.3786861548519576, -0.0,
    -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0,
    -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, 0.00073162693504539038, -0.0, -0.0,
    -0.0, -0.0, -0.0, 0.0011928224408164472, 0.013573094713127674, -0.0, -0.0,
    -0.0, -0.0, 0.0014128967411499915, 0.022129163361298769, -0.0, -0.0, -0.0,
    -0.0, 0.001507089677748745, 0.026211967286727214, -0.0, -0.0, -0.0, -0.0,
    0.0015452146277797642, 0.027959428442846615, -0.0, -0.0, -0.0, -0.0,
    0.0015601517221177834, 0.028666720004866784, -0.0, -0.0, -0.0, -0.0,
    0.0015658860868413276, 0.028943831995250625, -0.0, -0.0, -0.0, -0.0,
    0.0015680584595543343, 0.029050215551929624, -0.0, -0.0, -0.0, -0.0,
    0.0015688741198852938, 0.02909051726742623, -0.0, -0.0, -0.0, -0.0,
    0.0015691785127738436, 0.029105649344165818, -0.0, -0.0, -0.0, -0.0,
    0.001569291628775964, 0.029111296420986511, -0.0, -0.0, -0.0, -0.0,
    0.0015693335400471795, 0.029113394941607893, -0.0, -0.0, -0.0, -0.0,
    0.0015693490366219668, 0.029114172476751157, -0.0, -0.0, -0.0, -0.0,
    0.0015693547580409182, 0.029114459968185985, -0.0, -0.0, -0.0, -0.0,
    0.0015693568682268917, 0.02911456611157355, -0.0, -0.0, -0.0, -0.0,
    0.0015693576459366876, 0.029114605259604753, -0.0, -0.0, -0.0, -0.0,
    0.0015693579324117558, 0.029114619687625666, -0.0, -0.0, -0.0, -0.0,
    0.0015693580378975914, 0.029114625002292265, -0.0, -0.0, -0.0, -0.0,
    0.0015693580767292669, 0.029114626959258538, -0.0, -0.0, -0.0, -0.0,
    0.0015693580910213631, 0.029114627679661224, -0.0, -0.0, -0.0, -0.0, -1.0,
    -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  int32_T c3_i131;
  static real_T c3_d_Mx[2535] = { -0.0, 0.0010350053136839966, -0.0,
    0.029189778782142541, 0.0011595881405238348, 0.021472319676299183, -0.0,
    0.0005739557124176042, -0.0, 0.021582505501667924, 0.00077894668800304178,
    0.021512602811121419, -0.0, 0.00028292097526897374, -0.0,
    0.011968443212020789, 0.00043839461445327037, 0.014450967653461887, -0.0,
    0.00013074547574981106, -0.0, 0.005899625272014963, 0.00022317913327466168,
    0.0081330680141377884, -0.0, 5.8004663109140089E-5, -0.0,
    0.0027263772585326375, 0.00010654258386300217, 0.0041404045816640046, -0.0,
    2.5018897855736909E-5, -0.0, 0.0012095454430271948, 4.8652869924767456E-5,
    0.0019765709988030433, -0.0, 1.057114619685503E-5, -0.0,
    0.00052170795016997476, 2.1511489524338814E-5, 0.000902604838507456, -0.0,
    4.3968337202187322E-6, -0.0, 0.00022043541026903166, 9.2820089959888686E-6,
    0.0003990797368828284, -0.0, 1.8062025638787152E-6, -0.0,
    9.1685218135520281E-5, 3.9298670498379981E-6, 0.00017219921956925202, -0.0,
    7.3456721857173063E-7, -0.0, 3.7663938780454431E-5, 1.6389171510676548E-6,
    7.2906634682799842E-5, -0.0, 2.9627567006550981E-7, -0.0,
    1.5317603520062406E-5, 6.7517066131576128E-7, 3.040508304554229E-5, -0.0,
    1.1866904872021722E-7, -0.0, 6.1781047832876323E-6, 2.753453580006721E-7,
    1.2525721641174041E-5, -0.0, 4.725034571532842E-8, -0.0,
    2.4745528965117504E-6, 1.1134367991341056E-7, 5.1081889470503293E-6, -0.0,
    1.8717788680573011E-8, -0.0, 9.8529044525093338E-7, 4.4703140872302718E-8,
    2.0656406165242314E-6, -0.0, 7.3819834809016512E-9, -0.0,
    3.9031372287318039E-7, 1.7837816146402185E-8, 8.2932972526006112E-7, -0.0,
    2.8999819328616171E-9, -0.0, 1.5393321849014684E-7, 7.0800575230027386E-9,
    3.30925990327918E-7, -0.0, 1.1353130732146554E-9, -0.0,
    6.0472033518305973E-8, 2.7971619346835562E-9, 1.3134876086559932E-7, -0.0,
    4.4309512854060547E-10, -0.0, 2.3674178600644302E-8, 1.1005940181613927E-9,
    5.1892763987782858E-8, -0.0, 1.7245551524034332E-10, -0.0,
    9.2396656549046835E-9, 4.3148734771984506E-10, 2.0418147738477623E-8, -0.0,
    6.6953545743964508E-11, -0.0, 3.5961381620539945E-9, 1.6862071549923414E-10,
    8.0049248566202238E-9, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.087944751715135591, 0.044248070120072945, -0.0,
    2.4836332211828389, 0.036585802134487505, -0.0, 0.032353066114925326,
    0.032716391033045238, -0.0, 1.8363629289680201, 0.036654438910680341,
    0.67873739161385493, 0.011902027882541456, 0.018142669679894554, -0.0,
    1.0183435574852693, 0.024622409278165086, 0.68001073656528344,
    0.0043785113662362755, 0.0089430973309730429, -0.0, 0.50197383911214088,
    0.013857599998383534, 0.45679331526687761, 0.0016107643145738095,
    0.0041328484538953264, -0.0, 0.23197576053270916, 0.0070546650322408375,
    0.25708528249172297, 0.00059256707590431442, 0.0018335202872186217, -0.0,
    0.10291503979024526, 0.0033677980095831953, 0.13087768104936459,
    0.00021799324474027485, 0.0007908442929154037, -0.0, 0.044389894369122163,
    0.0015379112515595871, 0.0624791668665392, 8.0195233054201778E-5,
    0.00033415263484279232, -0.0, 0.018755904666333707, 0.00067997554570661811,
    0.028531228250239252, 2.9502177520593331E-5, 0.00013898337467074524, -0.0,
    0.0078011024116455933, 0.00029340316602251949, 0.012614861539937716,
    1.0853244579616563E-5, 5.7093841532476208E-5, -0.0, 0.0032046631902863357,
    0.00012422261548855645, 0.0054431962121625722, 3.9926855508463267E-6,
    2.3219579692116076E-5, -0.0, 0.0013033092595620486, 5.1805970149313406E-5,
    0.0023045697810920706, 1.4688269292186391E-6, 9.3652375956788213E-6, -0.0,
    0.00052566846765926415, 2.1342061801617345E-5, 0.00096110094620624009,
    5.4035122989851863E-7, 3.7511140765365079E-6, -0.0, 0.00021054910443893727,
    8.7036329981917365E-6, 0.00039593652492961431, 1.9878410849136859E-7,
    1.4935776333040491E-6, -0.0, 8.3834142786868765E-5, 3.5195600669327174E-6,
    0.00016146922615066202, 7.3128586745568035E-8, 5.9166700465317944E-7, -0.0,
    3.3210122490014607E-5, 1.4130608006038654E-6, 6.5294646559254976E-5,
    2.6902503625616913E-8, 2.333435925087398E-7, -0.0, 1.3097518077787337E-5,
    5.6385118076740725E-7, 2.6215010906910336E-5, 9.8968779999046509E-9,
    9.16680732455007E-8, -0.0, 5.1453062566691657E-6, 2.2379975000759545E-7,
    1.0460529969676533E-5, 3.6408579479468649E-9, 3.5887107010118629E-8, -0.0,
    2.0143344317753769E-6, 8.8417945712882573E-8, 4.1519182224188242E-6,
    1.339396787275297E-9, 1.4006182672215627E-8, -0.0, 7.8616356582949678E-7,
    3.478964193781161E-8, 1.6403239055526047E-6, 4.9273654160966151E-10,
    5.4512976868938022E-9, -0.0, 3.0597998956760583E-7, 1.3639262144043511E-8,
    6.4541514594240588E-7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, -0.0, -0.0066187050423206, -0.0, -0.37150627540839537,
    -0.0093392511699181436, -0.27328406860693549, -0.0, -0.0024588904583053052,
    -0.0, -0.13801691266815602, -0.0044845570111674889, -0.17326117260994911,
    -0.0, -0.00091349323580448014, -0.0, -0.05127414916883781,
    -0.001932459991230146, -0.083197206312833116, -0.0, -0.00033936846964531536,
    -0.0, -0.019048668182495988, -0.00078785340450609456, -0.0358508704831505,
    -0.0, -0.0001260775161492865, -0.0, -0.007076699767986798,
    -0.00031104906041678365, -0.014616204471419409, -0.0, -4.6838588437477789E-5,
    -0.0, -0.00262903837299466, -0.00012037510179249004, -0.0057705616827850251,
    -0.0, -1.7400829535836658E-5, -0.0, -0.00097670425385938241,
    -4.5984895409367941E-5, -0.00223319096040455, -0.0, -6.4645173698908825E-6,
    -0.0, -0.00036285175952772237, -1.7415672285546482E-5,
    -0.0008531087510137914, -0.0, -2.4016087704069107E-6, -0.0,
    -0.00013480170570785653, -6.5571770402008673E-6, -0.00032309440522422788,
    -0.0, -8.9221272928418942E-7, -0.0, -5.0079679606346879E-5,
    -2.4589072695705359E-6, -0.00012164831658619968, -0.0,
    -3.3146262792913874E-7, -0.0, -1.8604915244245203E-5, -9.1950390833083544E-7,
    -4.5617485718467245E-5, -0.0, -1.2314044633933424E-7, -0.0,
    -6.9118427666953141E-6, -3.4317757625997382E-7, -1.7058575947714673E-5, -0.0,
    -4.5747448571765308E-8, -0.0, -2.567792962469714E-6, -1.2790633523759481E-7,
    -6.366607792684996E-6, -0.0, -1.6995464228375207E-8, -0.0,
    -9.53951199509346E-7, -4.762660162626966E-8, -2.3729099072619951E-6, -0.0,
    -6.3139216143357317E-9, -0.0, -3.5439885705195481E-7, -1.772208662876406E-8,
    -8.8356557662499613E-7, -0.0, -2.345661502168167E-9, -0.0,
    -1.3166139939268603E-7, -6.5913487480197367E-9, -3.2877898393878141E-7, -0.0,
    -8.7142796804148841E-10, -0.0, -4.891303610355357E-8, -2.4506914683908947E-9,
    -1.2228226785906539E-7, -0.0, -3.2374095869459122E-10, -0.0,
    -1.8171499861791995E-8, -9.1096280244890231E-10, -4.5465066716085146E-8,
    -0.0, -1.2027179776206486E-10, -0.0, -6.7508262322550241E-9,
    -3.3856372278845567E-10, -1.6900121913920609E-8, -0.0,
    -4.4681727623365768E-11, -0.0, -2.5079743094804883E-9,
    -1.2581406914988951E-10, -6.28101188695536E-9, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0071022431572657805,
    -0.0, -0.33292881365828381, -0.010200589811986894, -0.28077121553280415,
    -0.0, -0.0048163268614579225, -0.0, -0.24616280945710789,
    -0.0079046666637811736, -0.26797382846282569, -0.0, -0.0025904631174934081,
    -0.0, -0.1365080437797736, -0.00467472058242934, -0.17561116553685732, -0.0,
    -0.0012571063433207035, -0.0, -0.0672891445152707, -0.0024349535320438206,
    -0.097380482613247665, -0.0, -0.00057544912106621414, -0.0,
    -0.031096143380966404, -0.001176927934492, -0.049092990682338591, -0.0,
    -0.00025367073896110422, -0.0, -0.013795669107954425,
    -0.00054147521946656843, -0.023276337619018737, -0.0,
    -0.00010891416537251407, -0.0, -0.0059504256686057615,
    -0.00024057338203568721, -0.010575912455639366, -0.0, -4.586051982694482E-5,
    -0.0, -0.0025142122582320924, -0.00010415278873437558,
    -0.0046582615260736711, -0.0, -1.9023366504604715E-5, -0.0,
    -0.0010457308063784932, -4.4203381844618841E-5, -0.00200403102392865, -0.0,
    -7.7978701977183743E-6, -0.0, -0.00042958223662682135,
    -1.8468090134871121E-5, -0.00084647026081048735, -0.0, -3.165719456156211E-6,
    -0.0, -0.00017470744146722215, -7.61884068843243E-6, -0.0003523352354668955,
    -0.0, -1.2749565639250844E-6, -0.0, -7.0465388295948777E-5,
    -3.110563484668326E-6, -0.00014491871051318749, -0.0, -5.1002731096782869E-7,
    -0.0, -2.8223919280756417E-5, -1.258991106328472E-6, -5.9021946550852784E-5,
    -0.0, -2.0285920592194669E-7, -0.0, -1.1237891917389789E-5,
    -5.05852219689076E-7, -2.3840473328507389E-5, -0.0, -8.0286011054186877E-8,
    -0.0, -4.4517872396557444E-6, -2.0197818607732778E-7, -9.5624999361774332E-6,
    -0.0, -3.1637659313095845E-8, -0.0, -1.7557105929791606E-6,
    -8.0211502845456524E-8, -3.81255488767998E-6, -0.0, -1.2419782729236843E-8,
    -0.0, -6.89723705308459E-7, -3.1704630615313307E-8, -1.5121631737237632E-6,
    -0.0, -4.8591062094917915E-9, -0.0, -2.7001973035399318E-7,
    -1.2479917263669902E-8, -5.9704246877230236E-7, -0.0, -1.8953479702515749E-9,
    -0.0, -1.0538452339928342E-7, -4.8945297864369867E-9, -2.3478610684229132E-7,
    -0.0, -7.3730149906714809E-10, -0.0, -4.1016344144970554E-8,
    -1.913350995896013E-9, -9.2002098641339483E-8, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0,
    -0.003713961809366121, -0.26249033292869156, -0.0, -0.0, -0.0, -0.0,
    -0.000974879071829633, -0.0689011748813457, -0.0, -0.0, -0.0, -0.0,
    -0.00025589633213100112, -0.01808589233386915, -0.0, -0.0, -0.0, -0.0,
    -6.7170313416619571E-5, -0.0047473719000525457, -0.0, -0.0, -0.0, -0.0,
    -1.7631557931737565E-5, -0.0012461392305870825, -0.0, -0.0, -0.0, -0.0,
    -4.6281135115754956E-6, -0.00032709950151387515, -0.0, -0.0, -0.0, -0.0,
    -1.2148350564910524E-6, -8.58604570535978E-5, -0.0, -0.0, -0.0, -0.0,
    -3.1888245843331112E-7, -2.253753995751657E-5, -0.0, -0.0, -0.0, -0.0,
    -8.3703562679680815E-8, -5.9158863668705782E-6, -0.0, -0.0, -0.0, -0.0,
    -2.1971376035212363E-8, -1.552862982015611E-6, -0.0, -0.0, -0.0, -0.0,
    -5.76727381041202E-9, -4.0761152114387288E-7, -0.0, -0.0, -0.0, -0.0,
    -1.5138536225932332E-9, -1.069940838911386E-7, -0.0, -0.0, -0.0, -0.0,
    -3.9737194140170884E-10, -2.8084912702119981E-8, -0.0, -0.0, -0.0, -0.0,
    -1.0430629319555518E-10, -7.3720180854880589E-9, -0.0, -0.0, -0.0, -0.0,
    -2.7379393627590269E-11, -1.935083481625374E-9, -0.0, -0.0, -0.0, -0.0,
    -7.1868261487263242E-12, -5.0794070733909145E-10, -0.0, -0.0, -0.0, -0.0,
    -1.8864723884888438E-12, -1.3332952537811248E-10, -0.0, -0.0, -0.0, -0.0,
    -4.9518076531759482E-13, -3.4997711505892973E-11, -0.0, -0.0, -0.0, -0.0,
    -1.2998016394872294E-13, -9.1865609449681922E-12, -0.0, -0.0, -0.0, -0.0,
    -3.4118536509189787E-14, -2.4113834409259779E-12, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0,
    0.00072960054744263, 0.021472319676299183, -0.0, -0.0, -0.0, -0.0,
    0.00034815241690823136, 0.0135355013037816, -0.0, -0.0, -0.0, -0.0,
    0.00014901103165084725, 0.0064589007087424476, -0.0, -0.0, -0.0, -0.0,
    6.0312782899629425E-5, 0.0027644428451398338, -0.0, -0.0, -0.0, -0.0,
    2.3630135311055975E-5, 0.001118918776081131, -0.0, -0.0, -0.0, -0.0,
    9.0716314213401117E-6, 0.00043838471398143235, -0.0, -0.0, -0.0, -0.0,
    3.4366430306151228E-6, 0.00016829630866008961, -0.0, -0.0, -0.0, -0.0,
    1.2903556442954993E-6, 6.3756375162507184E-5, -0.0, -0.0, -0.0, -0.0,
    4.8154245942252177E-7, 2.3938592928587451E-5, -0.0, -0.0, -0.0, -0.0,
    1.7894688052859113E-7, 8.9335439922381073E-6, -0.0, -0.0, -0.0, -0.0,
    6.6302654818189487E-8, 3.3198107419085409E-6, -0.0, -0.0, -0.0, -0.0,
    2.4515220349617096E-8, 1.2300424854140512E-6, -0.0, -0.0, -0.0, -0.0,
    9.05115151133951E-9, 4.5480475332404744E-7, -0.0, -0.0, -0.0, -0.0,
    3.3382650573058444E-9, 1.6791636671859002E-7, -0.0, -0.0, -0.0, -0.0,
    1.2303187818355823E-9, 6.19312734809657E-8, -0.0, -0.0, -0.0, -0.0,
    4.5319688501692135E-10, 2.2824793010331411E-8, -0.0, -0.0, -0.0, -0.0,
    1.6687613462918762E-10, 8.4076787627392044E-9, -0.0, -0.0, -0.0, -0.0,
    6.1430806090422255E-11, 3.095875058976724E-9, -0.0, -0.0, -0.0, -0.0,
    2.2609763294946281E-11, 1.1396602686823604E-9, -0.0, -0.0, -0.0, -0.0,
    8.3204580615953237E-12, 4.1945483954149967E-10, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, 0.77146478439091548,
    -0.0, 0.024821555163425612, 1.7543040594075165, -0.0, -0.0,
    0.28380603376517721, -0.0, 0.015646758121213855, 1.105860253633872, -0.0,
    -0.0, 0.10440640510261688, -0.0, 0.0074663549469272368, 0.52769686291340989,
    -0.0, -0.0, 0.038408969963869923, -0.0, 0.0031956384597102878,
    0.22585698137597449, -0.0, -0.0, 0.014129870406279181, -0.0,
    0.0012934468442432055, 0.09141647388908164, -0.0, -0.0,
    0.0051980888288868862, -0.0, 0.0005067636158986303, 0.035816348438995463,
    -0.0, -0.0, 0.0019122700135304248, -0.0, 0.00019454703414360216,
    0.013749930231878029, -0.0, -0.0, 0.00070348482394647918, -0.0,
    7.37010442734329E-5, 0.0052089419982020435, -0.0, -0.0,
    0.00025879760390602123, -0.0, 2.7672515772368315E-5, 0.0019558003692297442,
    -0.0, -0.0, 9.5206317901455373E-5, -0.0, 1.0326991137943318E-5,
    0.00072987701034358328, -0.0, -0.0, 3.5024447025578089E-5, -0.0,
    3.8376322029785526E-6, 0.00027123094052214716, -0.0, -0.0,
    1.2884773999108453E-5, -0.0, 1.42190354211065E-6, 0.0001004953613738996,
    -0.0, -0.0, 4.7400434584123477E-6, -0.0, 5.2574484002683721E-7,
    3.7157877538256054E-5, -0.0, -0.0, 1.7437645386090853E-6, -0.0,
    1.9410782915774122E-7, 1.3718888700252197E-5, -0.0, -0.0,
    6.4149512399808826E-7, -0.0, 7.1591264671127233E-8, 5.0598298697954529E-6,
    -0.0, -0.0, 2.359928677306218E-7, -0.0, 2.6384986221356338E-8,
    1.8648021097300472E-6, -0.0, -0.0, 8.6816924301187252E-8, -0.0,
    9.7191018647158023E-9, 6.8691344046764391E-7, -0.0, -0.0,
    3.1938161596144177E-8, -0.0, 3.5787672088490744E-9, 2.5293523314000047E-7,
    -0.0, -0.0, 1.174939304003274E-8, -0.0, 1.3174235785008212E-9,
    9.3111068847476913E-8, -0.0, -0.0, 4.3223601456708787E-9, -0.0,
    4.8488107457422275E-10, 3.4269763995643325E-8, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -1.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0,
    -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -1.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -1.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -1.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0 };

  int32_T c3_i132;
  static real_T c3_d_Mlim[195] = { 1.0, 0.15000000000000002, 1.0, 1.0,
    0.10000000000000003, 2.0, 1.0, 0.15000000000000002, 1.0, 1.0,
    0.10000000000000003, 2.0, 1.0, 0.15000000000000002, 1.0, 1.0,
    0.10000000000000003, 2.0, 1.0, 0.15000000000000002, 1.0, 1.0,
    0.10000000000000003, 2.0, 1.0, 0.15000000000000002, 1.0, 1.0,
    0.10000000000000003, 2.0, 1.0, 0.15000000000000002, 1.0, 1.0,
    0.10000000000000003, 2.0, 1.0, 0.15000000000000002, 1.0, 1.0,
    0.10000000000000003, 2.0, 1.0, 0.15000000000000002, 1.0, 1.0,
    0.10000000000000003, 2.0, 1.0, 0.15000000000000002, 1.0, 1.0,
    0.10000000000000003, 2.0, 1.0, 0.15000000000000002, 1.0, 1.0,
    0.10000000000000003, 2.0, 1.0, 0.15000000000000002, 1.0, 1.0,
    0.10000000000000003, 2.0, 1.0, 0.15000000000000002, 1.0, 1.0,
    0.10000000000000003, 2.0, 1.0, 0.15000000000000002, 1.0, 1.0,
    0.10000000000000003, 2.0, 1.0, 0.15000000000000002, 1.0, 1.0,
    0.10000000000000003, 2.0, 1.0, 0.15000000000000002, 1.0, 1.0,
    0.10000000000000003, 2.0, 1.0, 0.15000000000000002, 1.0, 1.0,
    0.10000000000000003, 2.0, 1.0, 0.15000000000000002, 1.0, 1.0,
    0.10000000000000003, 2.0, 1.0, 0.15000000000000002, 1.0, 1.0,
    0.10000000000000003, 2.0, 1.0, 0.15000000000000002, 1.0, 1.0,
    0.10000000000000003, 2.0, 1.0, 0.15000000000000002, 1.0, 1.0,
    0.10000000000000003, 2.0, 5.0, 0.19999999999999996, 80.0,
    0.19999999999999996, 130.0, 5.0, 0.19999999999999996, 80.0,
    0.19999999999999996, 130.0, 5.0, 0.19999999999999996, 80.0,
    0.19999999999999996, 130.0, 5.0, 0.19999999999999996, 80.0,
    0.19999999999999996, 130.0, 5.0, 0.19999999999999996, 80.0,
    0.19999999999999996, 130.0, 30.0, 0.8, 100.0, 0.8, 50.0, 30.0, 0.8, 100.0,
    0.8, 50.0, 30.0, 0.8, 100.0, 0.8, 50.0, 30.0, 0.8, 100.0, 0.8, 50.0, 30.0,
    0.8, 100.0, 0.8, 50.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0,
    10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0,
    10.0, 10.0, 10.0 };

  int32_T c3_i133;
  int32_T c3_i134;
  static real_T c3_d_Kr[3000] = { -0.0, -0.20118140273929969, -0.0, -0.0,
    -0.22744530300585153, -0.0, -0.0, -0.65012879409001423, -0.0,
    -0.21045114773980311, -0.87224555623925615, -0.17748125766556958, -0.0,
    -0.95457871680659168, -0.0, -0.36605572041663792, -1.3719157871255387,
    -0.34687302386491903, -0.0, -1.1183272161520617, -0.0, -0.45234526133530162,
    -1.6674144858187985, -0.45788045196061161, -0.0, -1.1977914925767426, -0.0,
    -0.49488011296939011, -1.8213329045585096, -0.51943665704909237, -0.0,
    -1.2341668145753204, -0.0, -0.51453662450077953, -1.8957289389237117,
    -0.55046934575377737, -0.0, -1.2502018635023748, -0.0, -0.52325715056671351,
    -1.9299567007558143, -0.56518279729699372, -0.0, -1.2570865518103369, -0.0,
    -0.5270185369656204, -1.9451638388249819, -0.57186804898857435, -0.0,
    -1.2599854895524545, -0.0, -0.52860782222330771, -1.9517475507268143,
    -0.57481263186760556, -0.0, -1.2611879956590235, -0.0, -0.5292688501650199,
    -1.9545417373701877, -0.57607942107836108, -0.0, -1.2616809150657291, -0.0,
    -0.52954039792849927, -1.9557091433158429, -0.57661449233265638, -0.0,
    -1.2618810267009011, -0.0, -0.529650834094031, -1.9561907458992025,
    -0.57683721067859473, -0.0, -1.261961619326468, -0.0, -0.52969537671465872,
    -1.9563873710120225, -0.57692881677486907, -0.0, -1.2619938592013507, -0.0,
    -0.5297132176342868, -1.9564669544281919, -0.57696612576070594, -0.0,
    -1.2620066823488116, -0.0, -0.52972032133680569, -1.9564989303869713,
    -0.57698119581402907, -0.0, -1.2620117573926291, -0.0, -0.52972313540304339,
    -1.9565116978433568, -0.57698724046683247, -0.0, -1.2620137572741175, -0.0,
    -0.52972424522380457, -1.956516768177357, -0.57698965046115869, -0.0,
    -1.2620145423541176, -0.0, -0.52972468121233862, -1.956518772292239,
    -0.57699060633058907, -0.0, -1.2620148495082109, -0.0, -0.52972485189736152,
    -1.9565195611734663, -0.57699098373340807, -0.0, -1.2620149693170526, -0.0,
    -0.52972491851308534, -1.9565198705667568, -0.57699113214653308, 0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, 0.0, 2.7970114811385716, -0.0, 1.569955619699267,
    2.3126637690443279, -0.0, 0.0, 4.8650818194047885, -0.0, 2.7307583805705788,
    4.629666209820976, 0.42904385928478755, 0.0, 6.0119172690744769, -0.0,
    3.3744742792076288, 6.1860993210828941, 0.85889262609185368, 0.0,
    6.5772288373257632, -0.0, 3.6917822629045118, 7.0620667065829759,
    1.1476410718075019, 0.0, 6.8384746847487685, -0.0, 3.8384189102871278,
    7.5080065868358119, 1.3101499642427674, 0.0, 6.9543752716067813, -0.0,
    3.9034736227512008, 7.720892022819756, 1.3928804371258774, 0.0,
    7.0043661652451874, -0.0, 3.9315333875861511, 7.8181065547962127,
    1.4323748030006969, 0.0, 7.0254886402722736, -0.0, 3.943389380525169,
    7.8610892069903944, 1.4504099789463032, 0.0, 7.0342740651187476, -0.0,
    3.9483206177410972, 7.8796358243172175, 1.4583840922724736, 0.0,
    7.0378830842202662, -0.0, 3.9503463512277985, 7.8874881912293944,
    1.4618248485039194, 0.0, 7.0393508415893393, -0.0, 3.9511701998052793,
    7.8907629531095385, 1.4632816144418026, 0.0, 7.0399428375115942, -0.0,
    3.9515024856508147, 7.8921120287127975, 1.4638891461090091, 0.0,
    7.0401799531442224, -0.0, 3.9516355780683736, 7.8926622032482632,
    1.4641394257264082, 0.0, 7.0402743652570443, -0.0, 3.9516885713535608,
    7.8928846818758975, 1.4642414937438761, 0.0, 7.0403117657448071, -0.0,
    3.9517095641547479, 7.8929740043541905, 1.4642827678323478, 0.0,
    7.0403265158730157, -0.0, 3.9517178433651945, 7.8930096465465391,
    1.4642993388796919, 0.0, 7.0403323104003848, -0.0, 3.9517210958190607,
    7.8930237933888439, 1.4643059511957419, 0.0, 7.0403345788981984, -0.0,
    3.9517223691212675, 7.8930293824689688, 1.464308575708609, 0.0,
    7.0403354642578009, -0.0, 3.95172286607142, 7.8930315815937595,
    1.4643096125910728, -0.0, 0.088485363269119349, -0.0, -0.0,
    0.073162693504539036, -0.0, -0.0, 0.15391017699676479, -0.0,
    0.018451459275849919, 0.1464626438444285, 0.013573094713127674, -0.0,
    0.1901910975643907, -0.0, 0.032094204714484667, 0.19570146541624217,
    0.027171653223950546, -0.0, 0.20807511406352514, -0.0, 0.039659703725975104,
    0.22341329028380533, 0.036306406972670284, -0.0, 0.21633980438305278, -0.0,
    0.043388978149800285, 0.23752090212825053, 0.04144748647075773, -0.0,
    0.22000639838897396, -0.0, 0.045112377266041406, 0.24425567789330246,
    0.0440647213286955, -0.0, 0.22158789435835824, -0.0, 0.045876955807416291,
    0.24733112582584815, 0.0453141524930232, -0.0, 0.22225611824249972, -0.0,
    0.046206738128423033, 0.24869091130378415, 0.0458847075679419, -0.0,
    0.22253405114132982, -0.0, 0.046346079883147893, 0.24927764617514378,
    0.046136974074237426, -0.0, 0.22264822491873346, -0.0, 0.046404035994472036,
    0.24952606115071033, 0.046245824741141382, -0.0, 0.22269465842280353, -0.0,
    0.046427844144501622, 0.249629660473251, 0.046291910523799384, -0.0,
    0.22271338661701642, -0.0, 0.046437526716598641, 0.24967233939882455,
    0.046311130201885362, -0.0, 0.2227208879315557, -0.0, 0.046441432023646756,
    0.24968974454498155, 0.046319047968048914, -0.0, 0.22272387472304955, -0.0,
    0.04644299623940655, 0.24969678280789845, 0.046322276959300725, -0.0,
    0.22272505791295366, -0.0, 0.046443619061753413, 0.24969960858533738,
    0.046323582693201582, -0.0, 0.22272552454330596, -0.0, 0.046443865787082032,
    0.24970073615036845, 0.046324106929570966, -0.0, 0.22272570785712595, -0.0,
    0.046443963091434129, 0.24970118369536023, 0.046324316114692905, -0.0,
    0.22272577962259937, -0.0, 0.046444001317049753, 0.24970136050971675,
    0.046324399142945026, -0.0, 0.22272580763155339, -0.0, 0.04644401628198476,
    0.24970143008052731, 0.046324431945428, -0.0, 0.22272581853282103, -0.0,
    0.046444022122567374, 0.24970145735572963, 0.046324444852158961, -0.0, -0.0,
    0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, -0.0, 1.5690215320898468,
    1.1089316623878867, -0.0, -0.0, 0.0, -0.0, 2.5580852808335441,
    1.8079686639012205, -0.0, -0.0, 0.0, -0.0, 3.0300489269799455,
    2.141536699778122, -0.0, -0.0, 0.0, -0.0, 3.2320518038765553,
    2.2843055410608342, -0.0, -0.0, 0.0, -0.0, 3.31381323807636,
    2.3420917736217368, -0.0, -0.0, 0.0, -0.0, 3.3458468080839423,
    2.3647320238121932, -0.0, -0.0, 0.0, -0.0, 3.358144526078072,
    2.3734236373942217, -0.0, -0.0, 0.0, -0.0, 3.3628033206073091,
    2.3767163167210308, -0.0, -0.0, 0.0, -0.0, 3.3645525572207311,
    2.3779526183433854, -0.0, -0.0, 0.0, -0.0, 3.3652053475616444,
    2.37841398860704, -0.0, -0.0, 0.0, -0.0, 3.3654479321829167,
    2.3785854392607342, -0.0, -0.0, 0.0, -0.0, 3.3655378136290803,
    2.3786489644447255, -0.0, -0.0, 0.0, -0.0, 3.3655710470412883,
    2.37867245270304, -0.0, -0.0, 0.0, -0.0, 3.3655833169962319,
    2.3786811246946313, -0.0, -0.0, 0.0, -0.0, 3.3655878424272547,
    2.3786843231171164, -0.0, -0.0, 0.0, -0.0, 3.3655895102764779,
    2.378685501896868, -0.0, -0.0, 0.0, -0.0, 3.3655901246408879,
    2.3786859361089761, -0.0, -0.0, 0.0, -0.0, 3.3655903508621208,
    2.3786860959945368, -0.0, -0.0, 0.0, -0.0, 3.3655904341391736,
    2.3786861548519576, -0.0, -0.0, -0.0, -0.0, 0.073162693504539036, -0.0, -0.0,
    -0.0, -0.0, -0.0, 0.11928224408164473, 0.013573094713127674, -0.0, -0.0,
    -0.0, -0.0, 0.14128967411499915, 0.022129163361298769, -0.0, -0.0, -0.0,
    -0.0, 0.1507089677748745, 0.026211967286727214, -0.0, -0.0, -0.0, -0.0,
    0.15452146277797643, 0.027959428442846615, -0.0, -0.0, -0.0, -0.0,
    0.15601517221177835, 0.028666720004866784, -0.0, -0.0, -0.0, -0.0,
    0.15658860868413277, 0.028943831995250625, -0.0, -0.0, -0.0, -0.0,
    0.15680584595543343, 0.029050215551929624, -0.0, -0.0, -0.0, -0.0,
    0.15688741198852937, 0.02909051726742623, -0.0, -0.0, -0.0, -0.0,
    0.15691785127738436, 0.029105649344165818, -0.0, -0.0, -0.0, -0.0,
    0.1569291628775964, 0.029111296420986511, -0.0, -0.0, -0.0, -0.0,
    0.15693335400471795, 0.029113394941607893, -0.0, -0.0, -0.0, -0.0,
    0.15693490366219667, 0.029114172476751157, -0.0, -0.0, -0.0, -0.0,
    0.15693547580409181, 0.029114459968185985, -0.0, -0.0, -0.0, -0.0,
    0.15693568682268916, 0.02911456611157355, -0.0, -0.0, -0.0, -0.0,
    0.15693576459366876, 0.029114605259604753, -0.0, -0.0, -0.0, -0.0,
    0.15693579324117557, 0.029114619687625666, -0.0, -0.0, -0.0, -0.0,
    0.15693580378975913, 0.029114625002292265, -0.0, -0.0, -0.0, -0.0,
    0.1569358076729267, 0.029114626959258538, -0.0, -0.0, -0.0, -0.0,
    0.15693580910213631, 0.029114627679661224, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.20118140273929969, -0.0, -0.0, -0.22744530300585153, -0.0,
    -0.0, -0.65012879409001423, -0.0, -0.21045114773980311, -0.87224555623925615,
    -0.17748125766556958, -0.0, -0.95457871680659168, -0.0, -0.36605572041663792,
    -1.3719157871255387, -0.34687302386491903, -0.0, -1.1183272161520617, -0.0,
    -0.45234526133530162, -1.6674144858187985, -0.45788045196061161, -0.0,
    -1.1977914925767426, -0.0, -0.49488011296939011, -1.8213329045585096,
    -0.51943665704909237, -0.0, -1.2341668145753204, -0.0, -0.51453662450077953,
    -1.8957289389237117, -0.55046934575377737, -0.0, -1.2502018635023748, -0.0,
    -0.52325715056671351, -1.9299567007558143, -0.56518279729699372, -0.0,
    -1.2570865518103369, -0.0, -0.5270185369656204, -1.9451638388249819,
    -0.57186804898857435, -0.0, -1.2599854895524545, -0.0, -0.52860782222330771,
    -1.9517475507268143, -0.57481263186760556, -0.0, -1.2611879956590235, -0.0,
    -0.5292688501650199, -1.9545417373701877, -0.57607942107836108, -0.0,
    -1.2616809150657291, -0.0, -0.52954039792849927, -1.9557091433158429,
    -0.57661449233265638, -0.0, -1.2618810267009011, -0.0, -0.529650834094031,
    -1.9561907458992025, -0.57683721067859473, -0.0, -1.261961619326468, -0.0,
    -0.52969537671465872, -1.9563873710120225, -0.57692881677486907, -0.0,
    -1.2619938592013507, -0.0, -0.5297132176342868, -1.9564669544281919,
    -0.57696612576070594, -0.0, -1.2620066823488116, -0.0, -0.52972032133680569,
    -1.9564989303869713, -0.57698119581402907, -0.0, -1.2620117573926291, -0.0,
    -0.52972313540304339, -1.9565116978433568, -0.57698724046683247, -0.0,
    -1.2620137572741175, -0.0, -0.52972424522380457, -1.956516768177357,
    -0.57698965046115869, -0.0, -1.2620145423541176, -0.0, -0.52972468121233862,
    -1.956518772292239, -0.57699060633058907, -0.0, -1.2620148495082109, -0.0,
    -0.52972485189736152, -1.9565195611734663, -0.57699098373340807, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0,
    2.7970114811385716, -0.0, 1.569955619699267, 2.3126637690443279, -0.0, 0.0,
    4.8650818194047885, -0.0, 2.7307583805705788, 4.629666209820976,
    0.42904385928478755, 0.0, 6.0119172690744769, -0.0, 3.3744742792076288,
    6.1860993210828941, 0.85889262609185368, 0.0, 6.5772288373257632, -0.0,
    3.6917822629045118, 7.0620667065829759, 1.1476410718075019, 0.0,
    6.8384746847487685, -0.0, 3.8384189102871278, 7.5080065868358119,
    1.3101499642427674, 0.0, 6.9543752716067813, -0.0, 3.9034736227512008,
    7.720892022819756, 1.3928804371258774, 0.0, 7.0043661652451874, -0.0,
    3.9315333875861511, 7.8181065547962127, 1.4323748030006969, 0.0,
    7.0254886402722736, -0.0, 3.943389380525169, 7.8610892069903944,
    1.4504099789463032, 0.0, 7.0342740651187476, -0.0, 3.9483206177410972,
    7.8796358243172175, 1.4583840922724736, 0.0, 7.0378830842202662, -0.0,
    3.9503463512277985, 7.8874881912293944, 1.4618248485039194, 0.0,
    7.0393508415893393, -0.0, 3.9511701998052793, 7.8907629531095385,
    1.4632816144418026, 0.0, 7.0399428375115942, -0.0, 3.9515024856508147,
    7.8921120287127975, 1.4638891461090091, 0.0, 7.0401799531442224, -0.0,
    3.9516355780683736, 7.8926622032482632, 1.4641394257264082, 0.0,
    7.0402743652570443, -0.0, 3.9516885713535608, 7.8928846818758975,
    1.4642414937438761, 0.0, 7.0403117657448071, -0.0, 3.9517095641547479,
    7.8929740043541905, 1.4642827678323478, 0.0, 7.0403265158730157, -0.0,
    3.9517178433651945, 7.8930096465465391, 1.4642993388796919, 0.0,
    7.0403323104003848, -0.0, 3.9517210958190607, 7.8930237933888439,
    1.4643059511957419, 0.0, 7.0403345788981984, -0.0, 3.9517223691212675,
    7.8930293824689688, 1.464308575708609, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, 0.088485363269119349, -0.0, -0.0, 0.073162693504539036, -0.0, -0.0,
    0.15391017699676479, -0.0, 0.018451459275849919, 0.1464626438444285,
    0.013573094713127674, -0.0, 0.1901910975643907, -0.0, 0.032094204714484667,
    0.19570146541624217, 0.027171653223950546, -0.0, 0.20807511406352514, -0.0,
    0.039659703725975104, 0.22341329028380533, 0.036306406972670284, -0.0,
    0.21633980438305278, -0.0, 0.043388978149800285, 0.23752090212825053,
    0.04144748647075773, -0.0, 0.22000639838897396, -0.0, 0.045112377266041406,
    0.24425567789330246, 0.0440647213286955, -0.0, 0.22158789435835824, -0.0,
    0.045876955807416291, 0.24733112582584815, 0.0453141524930232, -0.0,
    0.22225611824249972, -0.0, 0.046206738128423033, 0.24869091130378415,
    0.0458847075679419, -0.0, 0.22253405114132982, -0.0, 0.046346079883147893,
    0.24927764617514378, 0.046136974074237426, -0.0, 0.22264822491873346, -0.0,
    0.046404035994472036, 0.24952606115071033, 0.046245824741141382, -0.0,
    0.22269465842280353, -0.0, 0.046427844144501622, 0.249629660473251,
    0.046291910523799384, -0.0, 0.22271338661701642, -0.0, 0.046437526716598641,
    0.24967233939882455, 0.046311130201885362, -0.0, 0.2227208879315557, -0.0,
    0.046441432023646756, 0.24968974454498155, 0.046319047968048914, -0.0,
    0.22272387472304955, -0.0, 0.04644299623940655, 0.24969678280789845,
    0.046322276959300725, -0.0, 0.22272505791295366, -0.0, 0.046443619061753413,
    0.24969960858533738, 0.046323582693201582, -0.0, 0.22272552454330596, -0.0,
    0.046443865787082032, 0.24970073615036845, 0.046324106929570966, -0.0,
    0.22272570785712595, -0.0, 0.046443963091434129, 0.24970118369536023,
    0.046324316114692905, -0.0, 0.22272577962259937, -0.0, 0.046444001317049753,
    0.24970136050971675, 0.046324399142945026, -0.0, 0.22272580763155339, -0.0,
    0.04644401628198476, 0.24970143008052731, 0.046324431945428, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0,
    -0.0, 1.5690215320898468, 1.1089316623878867, -0.0, -0.0, 0.0, -0.0,
    2.5580852808335441, 1.8079686639012205, -0.0, -0.0, 0.0, -0.0,
    3.0300489269799455, 2.141536699778122, -0.0, -0.0, 0.0, -0.0,
    3.2320518038765553, 2.2843055410608342, -0.0, -0.0, 0.0, -0.0,
    3.31381323807636, 2.3420917736217368, -0.0, -0.0, 0.0, -0.0,
    3.3458468080839423, 2.3647320238121932, -0.0, -0.0, 0.0, -0.0,
    3.358144526078072, 2.3734236373942217, -0.0, -0.0, 0.0, -0.0,
    3.3628033206073091, 2.3767163167210308, -0.0, -0.0, 0.0, -0.0,
    3.3645525572207311, 2.3779526183433854, -0.0, -0.0, 0.0, -0.0,
    3.3652053475616444, 2.37841398860704, -0.0, -0.0, 0.0, -0.0,
    3.3654479321829167, 2.3785854392607342, -0.0, -0.0, 0.0, -0.0,
    3.3655378136290803, 2.3786489644447255, -0.0, -0.0, 0.0, -0.0,
    3.3655710470412883, 2.37867245270304, -0.0, -0.0, 0.0, -0.0,
    3.3655833169962319, 2.3786811246946313, -0.0, -0.0, 0.0, -0.0,
    3.3655878424272547, 2.3786843231171164, -0.0, -0.0, 0.0, -0.0,
    3.3655895102764779, 2.378685501896868, -0.0, -0.0, 0.0, -0.0,
    3.3655901246408879, 2.3786859361089761, -0.0, -0.0, 0.0, -0.0,
    3.3655903508621208, 2.3786860959945368, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, 0.073162693504539036, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.11928224408164473, 0.013573094713127674, -0.0, -0.0, -0.0, -0.0,
    0.14128967411499915, 0.022129163361298769, -0.0, -0.0, -0.0, -0.0,
    0.1507089677748745, 0.026211967286727214, -0.0, -0.0, -0.0, -0.0,
    0.15452146277797643, 0.027959428442846615, -0.0, -0.0, -0.0, -0.0,
    0.15601517221177835, 0.028666720004866784, -0.0, -0.0, -0.0, -0.0,
    0.15658860868413277, 0.028943831995250625, -0.0, -0.0, -0.0, -0.0,
    0.15680584595543343, 0.029050215551929624, -0.0, -0.0, -0.0, -0.0,
    0.15688741198852937, 0.02909051726742623, -0.0, -0.0, -0.0, -0.0,
    0.15691785127738436, 0.029105649344165818, -0.0, -0.0, -0.0, -0.0,
    0.1569291628775964, 0.029111296420986511, -0.0, -0.0, -0.0, -0.0,
    0.15693335400471795, 0.029113394941607893, -0.0, -0.0, -0.0, -0.0,
    0.15693490366219667, 0.029114172476751157, -0.0, -0.0, -0.0, -0.0,
    0.15693547580409181, 0.029114459968185985, -0.0, -0.0, -0.0, -0.0,
    0.15693568682268916, 0.02911456611157355, -0.0, -0.0, -0.0, -0.0,
    0.15693576459366876, 0.029114605259604753, -0.0, -0.0, -0.0, -0.0,
    0.15693579324117557, 0.029114619687625666, -0.0, -0.0, -0.0, -0.0,
    0.15693580378975913, 0.029114625002292265, -0.0, -0.0, -0.0, -0.0,
    0.1569358076729267, 0.029114626959258538, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.20118140273929969, -0.0, -0.0,
    -0.22744530300585153, -0.0, -0.0, -0.65012879409001423, -0.0,
    -0.21045114773980311, -0.87224555623925615, -0.17748125766556958, -0.0,
    -0.95457871680659168, -0.0, -0.36605572041663792, -1.3719157871255387,
    -0.34687302386491903, -0.0, -1.1183272161520617, -0.0, -0.45234526133530162,
    -1.6674144858187985, -0.45788045196061161, -0.0, -1.1977914925767426, -0.0,
    -0.49488011296939011, -1.8213329045585096, -0.51943665704909237, -0.0,
    -1.2341668145753204, -0.0, -0.51453662450077953, -1.8957289389237117,
    -0.55046934575377737, -0.0, -1.2502018635023748, -0.0, -0.52325715056671351,
    -1.9299567007558143, -0.56518279729699372, -0.0, -1.2570865518103369, -0.0,
    -0.5270185369656204, -1.9451638388249819, -0.57186804898857435, -0.0,
    -1.2599854895524545, -0.0, -0.52860782222330771, -1.9517475507268143,
    -0.57481263186760556, -0.0, -1.2611879956590235, -0.0, -0.5292688501650199,
    -1.9545417373701877, -0.57607942107836108, -0.0, -1.2616809150657291, -0.0,
    -0.52954039792849927, -1.9557091433158429, -0.57661449233265638, -0.0,
    -1.2618810267009011, -0.0, -0.529650834094031, -1.9561907458992025,
    -0.57683721067859473, -0.0, -1.261961619326468, -0.0, -0.52969537671465872,
    -1.9563873710120225, -0.57692881677486907, -0.0, -1.2619938592013507, -0.0,
    -0.5297132176342868, -1.9564669544281919, -0.57696612576070594, -0.0,
    -1.2620066823488116, -0.0, -0.52972032133680569, -1.9564989303869713,
    -0.57698119581402907, -0.0, -1.2620117573926291, -0.0, -0.52972313540304339,
    -1.9565116978433568, -0.57698724046683247, -0.0, -1.2620137572741175, -0.0,
    -0.52972424522380457, -1.956516768177357, -0.57698965046115869, -0.0,
    -1.2620145423541176, -0.0, -0.52972468121233862, -1.956518772292239,
    -0.57699060633058907, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 2.7970114811385716,
    -0.0, 1.569955619699267, 2.3126637690443279, -0.0, 0.0, 4.8650818194047885,
    -0.0, 2.7307583805705788, 4.629666209820976, 0.42904385928478755, 0.0,
    6.0119172690744769, -0.0, 3.3744742792076288, 6.1860993210828941,
    0.85889262609185368, 0.0, 6.5772288373257632, -0.0, 3.6917822629045118,
    7.0620667065829759, 1.1476410718075019, 0.0, 6.8384746847487685, -0.0,
    3.8384189102871278, 7.5080065868358119, 1.3101499642427674, 0.0,
    6.9543752716067813, -0.0, 3.9034736227512008, 7.720892022819756,
    1.3928804371258774, 0.0, 7.0043661652451874, -0.0, 3.9315333875861511,
    7.8181065547962127, 1.4323748030006969, 0.0, 7.0254886402722736, -0.0,
    3.943389380525169, 7.8610892069903944, 1.4504099789463032, 0.0,
    7.0342740651187476, -0.0, 3.9483206177410972, 7.8796358243172175,
    1.4583840922724736, 0.0, 7.0378830842202662, -0.0, 3.9503463512277985,
    7.8874881912293944, 1.4618248485039194, 0.0, 7.0393508415893393, -0.0,
    3.9511701998052793, 7.8907629531095385, 1.4632816144418026, 0.0,
    7.0399428375115942, -0.0, 3.9515024856508147, 7.8921120287127975,
    1.4638891461090091, 0.0, 7.0401799531442224, -0.0, 3.9516355780683736,
    7.8926622032482632, 1.4641394257264082, 0.0, 7.0402743652570443, -0.0,
    3.9516885713535608, 7.8928846818758975, 1.4642414937438761, 0.0,
    7.0403117657448071, -0.0, 3.9517095641547479, 7.8929740043541905,
    1.4642827678323478, 0.0, 7.0403265158730157, -0.0, 3.9517178433651945,
    7.8930096465465391, 1.4642993388796919, 0.0, 7.0403323104003848, -0.0,
    3.9517210958190607, 7.8930237933888439, 1.4643059511957419, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.088485363269119349, -0.0, -0.0, 0.073162693504539036, -0.0, -0.0,
    0.15391017699676479, -0.0, 0.018451459275849919, 0.1464626438444285,
    0.013573094713127674, -0.0, 0.1901910975643907, -0.0, 0.032094204714484667,
    0.19570146541624217, 0.027171653223950546, -0.0, 0.20807511406352514, -0.0,
    0.039659703725975104, 0.22341329028380533, 0.036306406972670284, -0.0,
    0.21633980438305278, -0.0, 0.043388978149800285, 0.23752090212825053,
    0.04144748647075773, -0.0, 0.22000639838897396, -0.0, 0.045112377266041406,
    0.24425567789330246, 0.0440647213286955, -0.0, 0.22158789435835824, -0.0,
    0.045876955807416291, 0.24733112582584815, 0.0453141524930232, -0.0,
    0.22225611824249972, -0.0, 0.046206738128423033, 0.24869091130378415,
    0.0458847075679419, -0.0, 0.22253405114132982, -0.0, 0.046346079883147893,
    0.24927764617514378, 0.046136974074237426, -0.0, 0.22264822491873346, -0.0,
    0.046404035994472036, 0.24952606115071033, 0.046245824741141382, -0.0,
    0.22269465842280353, -0.0, 0.046427844144501622, 0.249629660473251,
    0.046291910523799384, -0.0, 0.22271338661701642, -0.0, 0.046437526716598641,
    0.24967233939882455, 0.046311130201885362, -0.0, 0.2227208879315557, -0.0,
    0.046441432023646756, 0.24968974454498155, 0.046319047968048914, -0.0,
    0.22272387472304955, -0.0, 0.04644299623940655, 0.24969678280789845,
    0.046322276959300725, -0.0, 0.22272505791295366, -0.0, 0.046443619061753413,
    0.24969960858533738, 0.046323582693201582, -0.0, 0.22272552454330596, -0.0,
    0.046443865787082032, 0.24970073615036845, 0.046324106929570966, -0.0,
    0.22272570785712595, -0.0, 0.046443963091434129, 0.24970118369536023,
    0.046324316114692905, -0.0, 0.22272577962259937, -0.0, 0.046444001317049753,
    0.24970136050971675, 0.046324399142945026, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, 0.0, -0.0, 1.5690215320898468, 1.1089316623878867, -0.0, -0.0,
    0.0, -0.0, 2.5580852808335441, 1.8079686639012205, -0.0, -0.0, 0.0, -0.0,
    3.0300489269799455, 2.141536699778122, -0.0, -0.0, 0.0, -0.0,
    3.2320518038765553, 2.2843055410608342, -0.0, -0.0, 0.0, -0.0,
    3.31381323807636, 2.3420917736217368, -0.0, -0.0, 0.0, -0.0,
    3.3458468080839423, 2.3647320238121932, -0.0, -0.0, 0.0, -0.0,
    3.358144526078072, 2.3734236373942217, -0.0, -0.0, 0.0, -0.0,
    3.3628033206073091, 2.3767163167210308, -0.0, -0.0, 0.0, -0.0,
    3.3645525572207311, 2.3779526183433854, -0.0, -0.0, 0.0, -0.0,
    3.3652053475616444, 2.37841398860704, -0.0, -0.0, 0.0, -0.0,
    3.3654479321829167, 2.3785854392607342, -0.0, -0.0, 0.0, -0.0,
    3.3655378136290803, 2.3786489644447255, -0.0, -0.0, 0.0, -0.0,
    3.3655710470412883, 2.37867245270304, -0.0, -0.0, 0.0, -0.0,
    3.3655833169962319, 2.3786811246946313, -0.0, -0.0, 0.0, -0.0,
    3.3655878424272547, 2.3786843231171164, -0.0, -0.0, 0.0, -0.0,
    3.3655895102764779, 2.378685501896868, -0.0, -0.0, 0.0, -0.0,
    3.3655901246408879, 2.3786859361089761, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.073162693504539036, -0.0, -0.0, -0.0, -0.0, -0.0, 0.11928224408164473,
    0.013573094713127674, -0.0, -0.0, -0.0, -0.0, 0.14128967411499915,
    0.022129163361298769, -0.0, -0.0, -0.0, -0.0, 0.1507089677748745,
    0.026211967286727214, -0.0, -0.0, -0.0, -0.0, 0.15452146277797643,
    0.027959428442846615, -0.0, -0.0, -0.0, -0.0, 0.15601517221177835,
    0.028666720004866784, -0.0, -0.0, -0.0, -0.0, 0.15658860868413277,
    0.028943831995250625, -0.0, -0.0, -0.0, -0.0, 0.15680584595543343,
    0.029050215551929624, -0.0, -0.0, -0.0, -0.0, 0.15688741198852937,
    0.02909051726742623, -0.0, -0.0, -0.0, -0.0, 0.15691785127738436,
    0.029105649344165818, -0.0, -0.0, -0.0, -0.0, 0.1569291628775964,
    0.029111296420986511, -0.0, -0.0, -0.0, -0.0, 0.15693335400471795,
    0.029113394941607893, -0.0, -0.0, -0.0, -0.0, 0.15693490366219667,
    0.029114172476751157, -0.0, -0.0, -0.0, -0.0, 0.15693547580409181,
    0.029114459968185985, -0.0, -0.0, -0.0, -0.0, 0.15693568682268916,
    0.02911456611157355, -0.0, -0.0, -0.0, -0.0, 0.15693576459366876,
    0.029114605259604753, -0.0, -0.0, -0.0, -0.0, 0.15693579324117557,
    0.029114619687625666, -0.0, -0.0, -0.0, -0.0, 0.15693580378975913,
    0.029114625002292265, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.20118140273929969, -0.0, -0.0, -0.22744530300585153, -0.0, -0.0,
    -0.65012879409001423, -0.0, -0.21045114773980311, -0.87224555623925615,
    -0.17748125766556958, -0.0, -0.95457871680659168, -0.0, -0.36605572041663792,
    -1.3719157871255387, -0.34687302386491903, -0.0, -1.1183272161520617, -0.0,
    -0.45234526133530162, -1.6674144858187985, -0.45788045196061161, -0.0,
    -1.1977914925767426, -0.0, -0.49488011296939011, -1.8213329045585096,
    -0.51943665704909237, -0.0, -1.2341668145753204, -0.0, -0.51453662450077953,
    -1.8957289389237117, -0.55046934575377737, -0.0, -1.2502018635023748, -0.0,
    -0.52325715056671351, -1.9299567007558143, -0.56518279729699372, -0.0,
    -1.2570865518103369, -0.0, -0.5270185369656204, -1.9451638388249819,
    -0.57186804898857435, -0.0, -1.2599854895524545, -0.0, -0.52860782222330771,
    -1.9517475507268143, -0.57481263186760556, -0.0, -1.2611879956590235, -0.0,
    -0.5292688501650199, -1.9545417373701877, -0.57607942107836108, -0.0,
    -1.2616809150657291, -0.0, -0.52954039792849927, -1.9557091433158429,
    -0.57661449233265638, -0.0, -1.2618810267009011, -0.0, -0.529650834094031,
    -1.9561907458992025, -0.57683721067859473, -0.0, -1.261961619326468, -0.0,
    -0.52969537671465872, -1.9563873710120225, -0.57692881677486907, -0.0,
    -1.2619938592013507, -0.0, -0.5297132176342868, -1.9564669544281919,
    -0.57696612576070594, -0.0, -1.2620066823488116, -0.0, -0.52972032133680569,
    -1.9564989303869713, -0.57698119581402907, -0.0, -1.2620117573926291, -0.0,
    -0.52972313540304339, -1.9565116978433568, -0.57698724046683247, -0.0,
    -1.2620137572741175, -0.0, -0.52972424522380457, -1.956516768177357,
    -0.57698965046115869, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, 0.0, 2.7970114811385716, -0.0, 1.569955619699267,
    2.3126637690443279, -0.0, 0.0, 4.8650818194047885, -0.0, 2.7307583805705788,
    4.629666209820976, 0.42904385928478755, 0.0, 6.0119172690744769, -0.0,
    3.3744742792076288, 6.1860993210828941, 0.85889262609185368, 0.0,
    6.5772288373257632, -0.0, 3.6917822629045118, 7.0620667065829759,
    1.1476410718075019, 0.0, 6.8384746847487685, -0.0, 3.8384189102871278,
    7.5080065868358119, 1.3101499642427674, 0.0, 6.9543752716067813, -0.0,
    3.9034736227512008, 7.720892022819756, 1.3928804371258774, 0.0,
    7.0043661652451874, -0.0, 3.9315333875861511, 7.8181065547962127,
    1.4323748030006969, 0.0, 7.0254886402722736, -0.0, 3.943389380525169,
    7.8610892069903944, 1.4504099789463032, 0.0, 7.0342740651187476, -0.0,
    3.9483206177410972, 7.8796358243172175, 1.4583840922724736, 0.0,
    7.0378830842202662, -0.0, 3.9503463512277985, 7.8874881912293944,
    1.4618248485039194, 0.0, 7.0393508415893393, -0.0, 3.9511701998052793,
    7.8907629531095385, 1.4632816144418026, 0.0, 7.0399428375115942, -0.0,
    3.9515024856508147, 7.8921120287127975, 1.4638891461090091, 0.0,
    7.0401799531442224, -0.0, 3.9516355780683736, 7.8926622032482632,
    1.4641394257264082, 0.0, 7.0402743652570443, -0.0, 3.9516885713535608,
    7.8928846818758975, 1.4642414937438761, 0.0, 7.0403117657448071, -0.0,
    3.9517095641547479, 7.8929740043541905, 1.4642827678323478, 0.0,
    7.0403265158730157, -0.0, 3.9517178433651945, 7.8930096465465391,
    1.4642993388796919, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.088485363269119349, -0.0, -0.0, 0.073162693504539036, -0.0, -0.0,
    0.15391017699676479, -0.0, 0.018451459275849919, 0.1464626438444285,
    0.013573094713127674, -0.0, 0.1901910975643907, -0.0, 0.032094204714484667,
    0.19570146541624217, 0.027171653223950546, -0.0, 0.20807511406352514, -0.0,
    0.039659703725975104, 0.22341329028380533, 0.036306406972670284, -0.0,
    0.21633980438305278, -0.0, 0.043388978149800285, 0.23752090212825053,
    0.04144748647075773, -0.0, 0.22000639838897396, -0.0, 0.045112377266041406,
    0.24425567789330246, 0.0440647213286955, -0.0, 0.22158789435835824, -0.0,
    0.045876955807416291, 0.24733112582584815, 0.0453141524930232, -0.0,
    0.22225611824249972, -0.0, 0.046206738128423033, 0.24869091130378415,
    0.0458847075679419, -0.0, 0.22253405114132982, -0.0, 0.046346079883147893,
    0.24927764617514378, 0.046136974074237426, -0.0, 0.22264822491873346, -0.0,
    0.046404035994472036, 0.24952606115071033, 0.046245824741141382, -0.0,
    0.22269465842280353, -0.0, 0.046427844144501622, 0.249629660473251,
    0.046291910523799384, -0.0, 0.22271338661701642, -0.0, 0.046437526716598641,
    0.24967233939882455, 0.046311130201885362, -0.0, 0.2227208879315557, -0.0,
    0.046441432023646756, 0.24968974454498155, 0.046319047968048914, -0.0,
    0.22272387472304955, -0.0, 0.04644299623940655, 0.24969678280789845,
    0.046322276959300725, -0.0, 0.22272505791295366, -0.0, 0.046443619061753413,
    0.24969960858533738, 0.046323582693201582, -0.0, 0.22272552454330596, -0.0,
    0.046443865787082032, 0.24970073615036845, 0.046324106929570966, -0.0,
    0.22272570785712595, -0.0, 0.046443963091434129, 0.24970118369536023,
    0.046324316114692905, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, 0.0, -0.0, 1.5690215320898468, 1.1089316623878867,
    -0.0, -0.0, 0.0, -0.0, 2.5580852808335441, 1.8079686639012205, -0.0, -0.0,
    0.0, -0.0, 3.0300489269799455, 2.141536699778122, -0.0, -0.0, 0.0, -0.0,
    3.2320518038765553, 2.2843055410608342, -0.0, -0.0, 0.0, -0.0,
    3.31381323807636, 2.3420917736217368, -0.0, -0.0, 0.0, -0.0,
    3.3458468080839423, 2.3647320238121932, -0.0, -0.0, 0.0, -0.0,
    3.358144526078072, 2.3734236373942217, -0.0, -0.0, 0.0, -0.0,
    3.3628033206073091, 2.3767163167210308, -0.0, -0.0, 0.0, -0.0,
    3.3645525572207311, 2.3779526183433854, -0.0, -0.0, 0.0, -0.0,
    3.3652053475616444, 2.37841398860704, -0.0, -0.0, 0.0, -0.0,
    3.3654479321829167, 2.3785854392607342, -0.0, -0.0, 0.0, -0.0,
    3.3655378136290803, 2.3786489644447255, -0.0, -0.0, 0.0, -0.0,
    3.3655710470412883, 2.37867245270304, -0.0, -0.0, 0.0, -0.0,
    3.3655833169962319, 2.3786811246946313, -0.0, -0.0, 0.0, -0.0,
    3.3655878424272547, 2.3786843231171164, -0.0, -0.0, 0.0, -0.0,
    3.3655895102764779, 2.378685501896868, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, 0.073162693504539036, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.11928224408164473, 0.013573094713127674, -0.0, -0.0, -0.0, -0.0,
    0.14128967411499915, 0.022129163361298769, -0.0, -0.0, -0.0, -0.0,
    0.1507089677748745, 0.026211967286727214, -0.0, -0.0, -0.0, -0.0,
    0.15452146277797643, 0.027959428442846615, -0.0, -0.0, -0.0, -0.0,
    0.15601517221177835, 0.028666720004866784, -0.0, -0.0, -0.0, -0.0,
    0.15658860868413277, 0.028943831995250625, -0.0, -0.0, -0.0, -0.0,
    0.15680584595543343, 0.029050215551929624, -0.0, -0.0, -0.0, -0.0,
    0.15688741198852937, 0.02909051726742623, -0.0, -0.0, -0.0, -0.0,
    0.15691785127738436, 0.029105649344165818, -0.0, -0.0, -0.0, -0.0,
    0.1569291628775964, 0.029111296420986511, -0.0, -0.0, -0.0, -0.0,
    0.15693335400471795, 0.029113394941607893, -0.0, -0.0, -0.0, -0.0,
    0.15693490366219667, 0.029114172476751157, -0.0, -0.0, -0.0, -0.0,
    0.15693547580409181, 0.029114459968185985, -0.0, -0.0, -0.0, -0.0,
    0.15693568682268916, 0.02911456611157355, -0.0, -0.0, -0.0, -0.0,
    0.15693576459366876, 0.029114605259604753, -0.0, -0.0, -0.0, -0.0,
    0.15693579324117557, 0.029114619687625666, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.20118140273929969, -0.0, -0.0,
    -0.22744530300585153, -0.0, -0.0, -0.65012879409001423, -0.0,
    -0.21045114773980311, -0.87224555623925615, -0.17748125766556958, -0.0,
    -0.95457871680659168, -0.0, -0.36605572041663792, -1.3719157871255387,
    -0.34687302386491903, -0.0, -1.1183272161520617, -0.0, -0.45234526133530162,
    -1.6674144858187985, -0.45788045196061161, -0.0, -1.1977914925767426, -0.0,
    -0.49488011296939011, -1.8213329045585096, -0.51943665704909237, -0.0,
    -1.2341668145753204, -0.0, -0.51453662450077953, -1.8957289389237117,
    -0.55046934575377737, -0.0, -1.2502018635023748, -0.0, -0.52325715056671351,
    -1.9299567007558143, -0.56518279729699372, -0.0, -1.2570865518103369, -0.0,
    -0.5270185369656204, -1.9451638388249819, -0.57186804898857435, -0.0,
    -1.2599854895524545, -0.0, -0.52860782222330771, -1.9517475507268143,
    -0.57481263186760556, -0.0, -1.2611879956590235, -0.0, -0.5292688501650199,
    -1.9545417373701877, -0.57607942107836108, -0.0, -1.2616809150657291, -0.0,
    -0.52954039792849927, -1.9557091433158429, -0.57661449233265638, -0.0,
    -1.2618810267009011, -0.0, -0.529650834094031, -1.9561907458992025,
    -0.57683721067859473, -0.0, -1.261961619326468, -0.0, -0.52969537671465872,
    -1.9563873710120225, -0.57692881677486907, -0.0, -1.2619938592013507, -0.0,
    -0.5297132176342868, -1.9564669544281919, -0.57696612576070594, -0.0,
    -1.2620066823488116, -0.0, -0.52972032133680569, -1.9564989303869713,
    -0.57698119581402907, -0.0, -1.2620117573926291, -0.0, -0.52972313540304339,
    -1.9565116978433568, -0.57698724046683247, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0,
    2.7970114811385716, -0.0, 1.569955619699267, 2.3126637690443279, -0.0, 0.0,
    4.8650818194047885, -0.0, 2.7307583805705788, 4.629666209820976,
    0.42904385928478755, 0.0, 6.0119172690744769, -0.0, 3.3744742792076288,
    6.1860993210828941, 0.85889262609185368, 0.0, 6.5772288373257632, -0.0,
    3.6917822629045118, 7.0620667065829759, 1.1476410718075019, 0.0,
    6.8384746847487685, -0.0, 3.8384189102871278, 7.5080065868358119,
    1.3101499642427674, 0.0, 6.9543752716067813, -0.0, 3.9034736227512008,
    7.720892022819756, 1.3928804371258774, 0.0, 7.0043661652451874, -0.0,
    3.9315333875861511, 7.8181065547962127, 1.4323748030006969, 0.0,
    7.0254886402722736, -0.0, 3.943389380525169, 7.8610892069903944,
    1.4504099789463032, 0.0, 7.0342740651187476, -0.0, 3.9483206177410972,
    7.8796358243172175, 1.4583840922724736, 0.0, 7.0378830842202662, -0.0,
    3.9503463512277985, 7.8874881912293944, 1.4618248485039194, 0.0,
    7.0393508415893393, -0.0, 3.9511701998052793, 7.8907629531095385,
    1.4632816144418026, 0.0, 7.0399428375115942, -0.0, 3.9515024856508147,
    7.8921120287127975, 1.4638891461090091, 0.0, 7.0401799531442224, -0.0,
    3.9516355780683736, 7.8926622032482632, 1.4641394257264082, 0.0,
    7.0402743652570443, -0.0, 3.9516885713535608, 7.8928846818758975,
    1.4642414937438761, 0.0, 7.0403117657448071, -0.0, 3.9517095641547479,
    7.8929740043541905, 1.4642827678323478, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.088485363269119349, -0.0, -0.0,
    0.073162693504539036, -0.0, -0.0, 0.15391017699676479, -0.0,
    0.018451459275849919, 0.1464626438444285, 0.013573094713127674, -0.0,
    0.1901910975643907, -0.0, 0.032094204714484667, 0.19570146541624217,
    0.027171653223950546, -0.0, 0.20807511406352514, -0.0, 0.039659703725975104,
    0.22341329028380533, 0.036306406972670284, -0.0, 0.21633980438305278, -0.0,
    0.043388978149800285, 0.23752090212825053, 0.04144748647075773, -0.0,
    0.22000639838897396, -0.0, 0.045112377266041406, 0.24425567789330246,
    0.0440647213286955, -0.0, 0.22158789435835824, -0.0, 0.045876955807416291,
    0.24733112582584815, 0.0453141524930232, -0.0, 0.22225611824249972, -0.0,
    0.046206738128423033, 0.24869091130378415, 0.0458847075679419, -0.0,
    0.22253405114132982, -0.0, 0.046346079883147893, 0.24927764617514378,
    0.046136974074237426, -0.0, 0.22264822491873346, -0.0, 0.046404035994472036,
    0.24952606115071033, 0.046245824741141382, -0.0, 0.22269465842280353, -0.0,
    0.046427844144501622, 0.249629660473251, 0.046291910523799384, -0.0,
    0.22271338661701642, -0.0, 0.046437526716598641, 0.24967233939882455,
    0.046311130201885362, -0.0, 0.2227208879315557, -0.0, 0.046441432023646756,
    0.24968974454498155, 0.046319047968048914, -0.0, 0.22272387472304955, -0.0,
    0.04644299623940655, 0.24969678280789845, 0.046322276959300725, -0.0,
    0.22272505791295366, -0.0, 0.046443619061753413, 0.24969960858533738,
    0.046323582693201582, -0.0, 0.22272552454330596, -0.0, 0.046443865787082032,
    0.24970073615036845, 0.046324106929570966, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, 0.0, -0.0, 1.5690215320898468, 1.1089316623878867, -0.0, -0.0, 0.0,
    -0.0, 2.5580852808335441, 1.8079686639012205, -0.0, -0.0, 0.0, -0.0,
    3.0300489269799455, 2.141536699778122, -0.0, -0.0, 0.0, -0.0,
    3.2320518038765553, 2.2843055410608342, -0.0, -0.0, 0.0, -0.0,
    3.31381323807636, 2.3420917736217368, -0.0, -0.0, 0.0, -0.0,
    3.3458468080839423, 2.3647320238121932, -0.0, -0.0, 0.0, -0.0,
    3.358144526078072, 2.3734236373942217, -0.0, -0.0, 0.0, -0.0,
    3.3628033206073091, 2.3767163167210308, -0.0, -0.0, 0.0, -0.0,
    3.3645525572207311, 2.3779526183433854, -0.0, -0.0, 0.0, -0.0,
    3.3652053475616444, 2.37841398860704, -0.0, -0.0, 0.0, -0.0,
    3.3654479321829167, 2.3785854392607342, -0.0, -0.0, 0.0, -0.0,
    3.3655378136290803, 2.3786489644447255, -0.0, -0.0, 0.0, -0.0,
    3.3655710470412883, 2.37867245270304, -0.0, -0.0, 0.0, -0.0,
    3.3655833169962319, 2.3786811246946313, -0.0, -0.0, 0.0, -0.0,
    3.3655878424272547, 2.3786843231171164, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.073162693504539036,
    -0.0, -0.0, -0.0, -0.0, -0.0, 0.11928224408164473, 0.013573094713127674,
    -0.0, -0.0, -0.0, -0.0, 0.14128967411499915, 0.022129163361298769, -0.0,
    -0.0, -0.0, -0.0, 0.1507089677748745, 0.026211967286727214, -0.0, -0.0, -0.0,
    -0.0, 0.15452146277797643, 0.027959428442846615, -0.0, -0.0, -0.0, -0.0,
    0.15601517221177835, 0.028666720004866784, -0.0, -0.0, -0.0, -0.0,
    0.15658860868413277, 0.028943831995250625, -0.0, -0.0, -0.0, -0.0,
    0.15680584595543343, 0.029050215551929624, -0.0, -0.0, -0.0, -0.0,
    0.15688741198852937, 0.02909051726742623, -0.0, -0.0, -0.0, -0.0,
    0.15691785127738436, 0.029105649344165818, -0.0, -0.0, -0.0, -0.0,
    0.1569291628775964, 0.029111296420986511, -0.0, -0.0, -0.0, -0.0,
    0.15693335400471795, 0.029113394941607893, -0.0, -0.0, -0.0, -0.0,
    0.15693490366219667, 0.029114172476751157, -0.0, -0.0, -0.0, -0.0,
    0.15693547580409181, 0.029114459968185985, -0.0, -0.0, -0.0, -0.0,
    0.15693568682268916, 0.02911456611157355, -0.0, -0.0, -0.0, -0.0,
    0.15693576459366876, 0.029114605259604753 };

  int32_T c3_i135;
  int32_T c3_i136;
  static real_T c3_d_Ku1[125] = { 11.31719954771115, -53.609214335270529,
    -1.0030745775553456, -24.573926256685429, -0.34115164809652343,
    -53.609214335270529, 320.13860955611517, 4.8456743996000782,
    61.2600399326549, 0.90856734861464283, -1.0030745775553456,
    4.8456743996000782, 0.092768889880541369, 2.0245416881272194,
    0.030045178552170707, -24.573926256685429, 61.2600399326549,
    2.0245416881272194, 100.87589392261879, 1.3045613792119624,
    -0.34115164809652343, 0.90856734861464283, 0.030045178552170711,
    1.3045613792119624, 0.019366919102046045, 10.899420893531657,
    -51.829507960312952, -0.96562327952374716, -23.5156652539736,
    -0.32616860221797628, -51.42486132147684, 308.13850312012113,
    4.6464984201968251, 57.959597312962714, 0.85957222983404935,
    -0.96687677200197208, 4.688846617772926, 0.089372949912823352,
    1.9380030878940731, 0.028743146904746039, -23.813780718042803,
    60.246733355741846, 1.9621579153567208, 97.044640061294643,
    1.2540868507559264, -0.33121056887659883, 0.8947045739244246,
    0.029156052217555378, 1.2568123994148352, 0.018640719935203675,
    10.362859095622115, -49.424795115409289, -0.91792440216939541,
    -22.243516588468275, -0.30841947249497331, -48.740007654390077,
    292.73485337740516, 4.4033068633943024, 54.3955883739399, 0.807011575883675,
    -0.91992416418164225, 4.4744596519447875, 0.085013977513777622,
    1.8335913376664812, 0.027193152951217586, -22.750524055643705,
    58.274790041937976, 1.8750025687386058, 92.126278073671727,
    1.1901074661155813, -0.31691716854403829, 0.86659940069691976,
    0.027893479959880844, 1.1942879261089576, 0.01770846367674659,
    9.7588583195317131, -46.636258773153372, -0.86440897979097253,
    -20.873242385669922, -0.28941480846566431, -45.790126887203506,
    275.49303443155083, 4.1368558496072989, 50.719996147731621,
    0.7529602620768826, -0.86678678619939609, 4.2243796799737572,
    0.080108517534011714, 1.7208414874100755, 0.025530360864083168,
    -21.501625555369561, 55.519820476002856, 1.7724187224518451,
    86.705248800049489, 1.1199023750714661, -0.299887946714565,
    0.82668964964512848, 0.026396891595957889, 1.1247367748638677,
    0.016680928792426133, 9.1205596773652129, -43.641828724017763,
    -0.80793100885731106, -19.461768622456486, -0.26988582361642421,
    -42.712192906915973, 257.35161801865542, 3.8591760843612959,
    46.999528814265673, 0.69831375080118441, -0.81048570907498907,
    3.95509350469423, 0.07492494993738516, 1.604561623863431,
    0.023820410737092512, -20.153356411280093, 52.277158360020294,
    1.6614827039816789, 81.072330461208452, 1.0470768912098221,
    -0.28137597143814852, 0.77938268361725438, 0.024773202073116941,
    1.0521830209149754, 0.015613231137237176 };

  int32_T c3_i137;
  static real_T c3_d_Kx[325] = { -0.034133279750320981, -2.2176031417911517,
    0.16630727372570267, 0.39542325638763426, 0.02377148107397737,
    -0.0077300389815131276, -0.60125915570042154, 0.0, 23.00423031595361, 0.0,
    9.44336320684049, 35.201332618444873, 10.10936109002488, 0.13855099425799852,
    10.882218405509979, -0.601756632203019, -1.5774613336880814,
    -0.01788615554738443, 0.0095309410817779171, 0.70925953276921516, 0.0,
    -125.50748995083202, 0.0, -70.447043385910249, -137.89920466881878,
    -24.118659607504739, 0.0032060939044762089, 0.20554487739568464,
    -0.015651184758814992, -0.036116275523860736, -0.0021556630556170231,
    0.00069378906733039494, 0.05071286539075448, 0.0, -4.1932407471215321, 0.0,
    -0.82795381973163562, -4.61223672112805, -0.80933466891657757,
    0.088925257695219223, 4.3274570050226178, -0.49078664872847122,
    -1.0728710803770811, -0.12562592788366558, 0.038065287072953133,
    3.0692974261422168, 0.0, 0.0, 0.0, 0.0, -60.789661713603373,
    -42.964088918700249, 0.0013469958923517536, 0.06510951134209457,
    -0.0074994665701811356, -0.015706315512845084, -0.0019454496798100706,
    0.00058177330776093886, 0.042377041612878315, 0.0, 0.0, 0.0, 0.0,
    -2.9915274939422503, -0.525871582475187, -0.017921830544796968,
    -1.2288566524671554, 0.068280560947324279, 0.20751088657545189,
    0.0062397839809635921, -0.0033541511664996137, -0.26289328031892523, 0.0,
    21.742215346636556, 0.0, 8.9136382883274035, 33.244812747878115,
    9.5323699578783465, 0.068919251766685563, 5.4978862916074549,
    -0.22844435890670492, -0.78567950976002232, -0.0046949429234722671,
    0.00389029427850023, 0.2922997359694115, 0.0, -118.46715448657423, 0.0,
    -66.495320519838828, -130.00617308722502, -22.654349994913666,
    0.0016825975090159981, 0.11448751800873193, -0.0064036215591081981,
    -0.019102411113122972, -0.00056584071312214821, 0.00030151781271001138,
    0.022437908400584287, 0.0, -3.9705149285887114, 0.0, -0.78150979760906825,
    -4.3625352637723207, -0.76301022406441865, 0.049737200233515334,
    2.8109158701701817, -0.21666187887504365, -0.59335628669952767,
    -0.032975591633281516, 0.016700916242111539, 1.3495174665733078, 0.0, 0.0,
    0.0, 0.0, -57.4240712794642, -40.585402763848293, 0.00075621308235695192,
    0.042578366758881672, -0.003317759221522644, -0.0088210441900290412,
    -0.00051066173413197584, 0.00025579575181215692, 0.019002552262546192, 0.0,
    0.0, 0.0, 0.0, -2.834591684840114, -0.49675695479552573,
    -0.008720147405290625, -0.62165474609414106, 0.027071888481225471,
    0.10082347588436276, 0.0016378829741913652, -0.0013679057980325003,
    -0.10765950379337182, 0.0, 20.480200497128344, 0.0, 8.3839134364300421,
    31.288293186704646, 8.9553789741449386, 0.0321230166426069,
    2.5899304386275945, -0.086151558434074918, -0.36640912976800172,
    -0.0012323771300718049, 0.00153197035028509, 0.11576740107700714, 0.0,
    -111.42681990767603, 0.0, -62.543598150717564, -122.11314370475606,
    -21.190041419205055, 0.00081806300878671989, 0.058021832345080807,
    -0.0025336206800517258, -0.009318203584633096, -0.00014852771714119508,
    0.00012307210920590973, 0.0092471012347051726, 0.0, -3.7477891209571581, 0.0,
    -0.73506578132708345, -4.1128338336917931, -0.71668579211899064,
    0.025329660525068288, 1.5721861798084384, -0.08950294578093719,
    -0.29967507041744879, -0.0086557740248463747, 0.0068519858017876975,
    0.55430891511895375, 0.0, 0.0, 0.0, 0.0, -54.05848092860208,
    -38.206716667853755, 0.00038600489448562469, 0.023903794588238474,
    -0.0013721240121858363, -0.0044930364012775569, -0.00013404376858705403,
    0.00010506708525783806, 0.0078865038651740847, 0.0, 0.0, 0.0, 0.0,
    -2.6776558771671874, -0.46764232783626719, -0.0040333518313631243,
    -0.29593042016162735, 0.010504981828321189, 0.046563735083269754,
    0.00042992844681305156, -0.00053839347231494331, -0.042479055217012847, 0.0,
    19.218185954774228, 0.0, 7.8541887552177032, 29.331774414412408,
    8.3783883678143489, 0.014358593540243996, 1.1667501380931609,
    -0.03234262604509227, -0.16382261461665473, -0.00032348708217026193,
    0.00059004214185601634, 0.044750391140776495, 0.0, -104.38648759727565, 0.0,
    -58.591877054898504, -114.22011991136721, -19.725735468009315,
    0.00037809339236761775, 0.027637604708530068, -0.00098184607421804683,
    -0.0043131905080845967, -3.8987089890159753E-5, 4.8464925466560986E-5,
    0.003662380583025327, 0.0, -3.5250633413345587, 0.0, -0.68862178001003371,
    -3.863132473182076, -0.67036139297604558, 0.012116684431396088,
    0.800666842952268, -0.035616385458281608, -0.14247261119638741,
    -0.0022720570040125729, 0.0027065638771048639, 0.21910368284044313, 0.0, 0.0,
    0.0, 0.0, -50.692890803961191, -35.828030731744782, 0.00018493339051095005,
    0.012201559171763268, -0.0005463846323248468, -0.0021473498085301627,
    -3.5185193423766996E-5, 4.1530246285262194E-5, 0.003136435766909721, 0.0,
    0.0, 0.0, 0.0, -2.5207200733774284, -0.43852770283397491,
    -0.0017996541686753497, -0.13495701742644686, 0.0040201573147141453,
    0.020747932520384971, 0.00011285206075727788, -0.00020729535571887447,
    -0.016381388688480741, 0.0, 17.956172197500109, 0.0, 7.3244645099938985,
    27.375257646235053, 7.8013987173531909, 0.0062332406860392325,
    0.50954971237050939, -0.012103884819321451, -0.071125466446146174,
    -8.4912230899872088E-5, 0.00022401014125733208, 0.017030223711258684, 0.0,
    -97.346161081402627, 0.0, -54.640159211533309, -106.32711026482066,
    -18.261436129129624, 0.00016858956691724109, 0.012605833062350686,
    -0.00037541636183721329, -0.0019245627607817474, -1.0233734173679989E-5,
    1.8666385039279781E-5, 0.0014157091035303514, 0.0, -3.3023376334774328, 0.0,
    -0.64217781691859954, -3.6134312894867158, -0.62403707686135268,
    0.0055458921820979628, 0.38300628906382361, -0.013852621977896933,
    -0.064908305759426327, -0.00059639299788331944, 0.0010444751634377345,
    0.084589588628275453, 0.0, 0.0, 0.0, 0.0, -47.327301293684712,
    -33.449345229847914, 8.4737445234698108E-5, 0.00584571359042843,
    -0.00021260079721647753, -0.00098175086118381543, -9.2357731161752749E-6,
    1.6033626541572185E-5, 0.0012155553696769725, 0.0, 0.0, 0.0, 0.0,
    -2.3637842801362527, -0.40941308314634922 };

  int32_T c3_i138;
  static real_T c3_d_Hinv[676] = { 8.9742227308950113, 0.036440838797920469,
    6.9764585162260335, 0.027443722462662697, 3.0803351874507707,
    -12.472452879818354, 0.0028448849982596644, 0.18225493764207729,
    0.0071050305975627719, 0.40332949119814376, 3.7987004424930997,
    -0.00085166692885956365, -1.4511874320405245, 0.00076638724927380829,
    -0.62282832508846, 0.87924045356707092, 0.0013321136370576993,
    -1.1578111012948644, 0.00069601727890802423, -0.62943315975069913,
    -0.53014994382292069, 0.001740936025013828, -0.9321183508650529,
    0.00099879481043596563, -0.52394876698016768, 0.0, 0.036440838797920469,
    0.0089629192351637, -0.0094489623620326764, 0.00084552844623282577,
    0.079748924474841, 0.011187201415618409, -0.0008730925895354554,
    -0.0059292227211149434, 0.00072555564669314133, 0.064912050783271766,
    -0.00070546015137407244, -0.0007137702226460037, -0.0029025844311467608,
    0.00059988339344821417, 0.04974108287516725, -0.001257720078262295,
    -0.00059016429519687813, -0.0012105572669273321, 0.00049671390581633966,
    0.037653433998941374, -0.0029288806385197384, -0.000502772121837824,
    -3.173767985618556E-5, 0.00042444837008698451, 0.029698443559885365, 0.0,
    6.9764585162260335, -0.0094489623620326764, 84.738776652938171,
    0.032230086870461888, -1.7440892013350229, -0.35388791049268392,
    -0.00443742794834211, -13.482376555287793, 0.030314261120641228,
    -1.4514283815949747, -1.4411524369634641, -0.0023582334741000053,
    -12.151971722829792, 0.026819395181837836, -1.3382723651791633,
    -1.0340237184321073, -0.0011824506723456124, -11.100414582057136,
    0.023465029102411994, -1.2995891835215005, -0.80812039772805566,
    -0.00041178799777898427, -10.214406422952711, 0.020919314121880292,
    -1.2538416889582, 0.0, 0.027443722462662697, 0.00084552844623282577,
    0.032230086870461888, 0.0092137331396855739, -0.058660940457452314,
    0.0015579473293478067, 0.00072937431895990328, 0.031100889647760272,
    -0.00066974307903580133, -0.045533037450281685, 0.00062486075727360263,
    0.00059928856542311275, 0.027278524271514861, -0.00055594739756537894,
    -0.033062254201048469, 0.0025051969275220166, 0.00049489388533118135,
    0.023596819304617659, -0.00046520260228578972, -0.023687438697209087,
    0.0044701210956103335, 0.00042165305889323309, 0.020719982115643416,
    -0.00040111261742248463, -0.017705220376415403, 0.0, 3.0803351874507707,
    0.079748924474841, -1.7440892013350229, -0.058660940457452314,
    84.262273132519013, -0.75501203040124865, 0.065261579075031509,
    -1.3253349929398091, -0.045126047441285108, -13.438613623421775,
    -0.63130428870978861, 0.0493031164476796, -1.2973779525197779,
    -0.0327462146572788, -11.238267334448363, -0.28095815057449391,
    0.037134512645606126, -1.3077624195215107, -0.023501323503767175,
    -9.4959398386980975, 0.068983665967758345, 0.029224817014208794,
    -1.3026033068758094, -0.017683691122647609, -8.2622499382595969, 0.0,
    -12.472452879818354, 0.011187201415618409, -0.35388791049268392,
    0.0015579473293478067, -0.75501203040124865, 28.167574051636016,
    0.031629496300267221, 4.9681134079237266, 0.020512862945759248,
    1.8735473140782608, -18.492434093857202, 0.00381855255832959,
    0.85371403825583625, 0.0096374610543719982, 0.83301711199389172,
    2.4984737004069228, -0.0031493029690716264, -1.1214610350472398,
    0.0029256333983415793, -0.16500326717921593, 0.93632347455845055,
    -0.00080624691081804842, -1.0037465798878151, 0.0020304228683625507,
    -0.31840002191304623, 0.0, 0.0028448849982596644, -0.0008730925895354554,
    -0.00443742794834211, 0.00072937431895990328, 0.065261579075031509,
    0.031629496300267221, 0.0091393067539556512, -0.0066659797387237305,
    0.00070112918819880147, 0.06218714178178137, 0.012006723883280883,
    -0.000751102731602354, -0.0044847855585815454, 0.00062308071786274085,
    0.052918150288027543, 0.00011178623039969938, -0.0006390309761683655,
    -0.0022429590081774857, 0.0005368421069435219, 0.043006081961612888,
    -0.0037570664579238385, -0.00055311852080596228, -0.00092195232481172566,
    0.00046717744902474175, 0.0353978340020979, 0.0, 0.18225493764207729,
    -0.0059292227211149434, -13.482376555287793, 0.031100889647760272,
    -1.3253349929398091, 4.9681134079237266, -0.0066659797387237305,
    86.2987946233806, 0.028423479653654219, -1.6022158094740417,
    0.41946202003532818, -0.0031167301628049005, -12.455068550430205,
    0.026611236414606464, -1.4621624315539081, -1.2131652217582118,
    -0.0014215594461411362, -11.313406793690907, 0.024238469199501712,
    -1.327771694217067, -0.94740562660409722, -0.00087066098630071481,
    -10.446262596174813, 0.021873093393181366, -1.2594013457280875, 0.0,
    0.0071050305975627719, 0.00072555564669314133, 0.030314261120641228,
    -0.00066974307903580133, -0.045126047441285108, 0.020512862945759248,
    0.00070112918819880147, 0.028423479653654219, 0.0093436667222943377,
    -0.044230474769060238, 0.0039806267525193378, 0.00062699743238243076,
    0.027379576566369617, -0.00058091709427579965, -0.036489970619042612,
    0.00050776244231055042, 0.00053804502503600323, 0.02483829066468889,
    -0.00050070461796487, -0.028269973020781311, 0.00427631548745728,
    0.00046498149754279451, 0.021969246427482603, -0.00043818187037944126,
    -0.022407091104289574, 0.0, 0.40332949119814376, 0.064912050783271766,
    -1.4514283815949747, -0.045533037450281685, -13.438613623421775,
    1.8735473140782608, 0.06218714178178137, -1.6022158094740417,
    -0.044230474769060238, 86.810581825112209, -0.24429390477688706,
    0.053276757412593592, -1.3463721112785743, -0.036138186649613054,
    -11.72003412272192, -0.57431260944069984, 0.042917507816890875,
    -1.2581747181349565, -0.027986245664067478, -10.160128292655404,
    0.039666441501316541, 0.034932703827684375, -1.2664809968457063,
    -0.022278199418884741, -8.94933118352301, 0.0, 3.7987004424930997,
    -0.00070546015137407244, -1.4411524369634641, 0.00062486075727360263,
    -0.63130428870978861, -18.492434093857202, 0.012006723883280883,
    0.41946202003532818, 0.0039806267525193378, -0.24429390477688706,
    29.989471265697279, 0.030881807464890665, 4.8788310292707138,
    0.019868122422498719, 1.8377860591583333, -18.465119253910881,
    0.0042147871947828932, 0.87307295030699472, 0.0092597939385912452,
    0.79008061948827624, 3.7909450589865505, -0.0040276161280285916,
    -1.2066365801769023, 0.0028014082937405245, -0.17050153189634418, 0.0,
    -0.00085166692885956365, -0.0007137702226460037, -0.0023582334741000053,
    0.00059928856542311275, 0.0493031164476796, 0.00381855255832959,
    -0.000751102731602354, -0.0031167301628049005, 0.00062699743238243076,
    0.053276757412593592, 0.030881807464890665, 0.00921675274524377,
    -0.0057790582105361954, 0.0006366563740748156, 0.055319803943869546,
    0.012619924370686521, -0.00071620691080428111, -0.0043776437837801368,
    0.00059321212983581048, 0.050677773437691975, -0.0034789716833972277,
    -0.00063806203061990646, -0.0023906240612461631, 0.00053792006255711346,
    0.044887755120243, 0.0, -1.4511874320405245, -0.0029025844311467608,
    -12.151971722829792, 0.027278524271514861, -1.2973779525197779,
    0.85371403825583625, -0.0044847855585815454, -12.455068550430205,
    0.027379576566369617, -1.3463721112785743, 4.8788310292707138,
    -0.0057790582105361954, 87.1922742926084, 0.026015542009207596,
    -1.5500778762127481, 0.46983044348943248, -0.0030095120515977,
    -11.780685411434813, 0.025168311872774088, -1.3884171928914883,
    -1.2185698669723526, -0.001804521861975922, -10.823677081279452,
    0.023610205407387352, -1.2446325491491794, 0.0, 0.00076638724927380829,
    0.00059988339344821417, 0.026819395181837836, -0.00055594739756537894,
    -0.0327462146572788, 0.0096374610543719982, 0.00062308071786274085,
    0.026611236414606464, -0.00058091709427579965, -0.036138186649613054,
    0.019868122422498719, 0.0006366563740748156, 0.026015542009207596,
    0.0094018496753989472, -0.039039210584926487, 0.00336226016968557,
    0.00059728465468724334, 0.025960924136656304, -0.00055263291924495918,
    -0.035019371692208132, 0.002375807999949285, 0.00053749660802956,
    0.024085181630646386, -0.00049907743870915647, -0.03012864354759591, 0.0,
    -0.62282832508846, 0.04974108287516725, -1.3382723651791633,
    -0.033062254201048469, -11.238267334448363, 0.83301711199389172,
    0.052918150288027543, -1.4621624315539081, -0.036489970619042612,
    -11.72003412272192, 1.8377860591583333, 0.055319803943869546,
    -1.5500778762127481, -0.039039210584926487, 87.95362940318131,
    -0.29887280326507243, 0.05106836191602384, -1.270854349311171,
    -0.03468948382058288, -11.138420262937315, -0.22138864483375117,
    0.044567662235183145, -1.1995359965005163, -0.02988937164636344,
    -10.082982004860426, 0.0, 0.87924045356707092, -0.001257720078262295,
    -1.0340237184321073, 0.0025051969275220166, -0.28095815057449391,
    2.4984737004069228, 0.00011178623039969938, -1.2131652217582118,
    0.00050776244231055042, -0.57431260944069984, -18.465119253910881,
    0.012619924370686521, 0.46983044348943248, 0.00336226016968557,
    -0.29887280326507243, 28.3734209355941, 0.031441407203073861,
    5.0416287785376639, 0.020349394175065729, 1.9074400475782856,
    -12.784993622858213, -0.0011788848060508611, 0.42874002198613426,
    0.010082184076887907, 0.92865579679905863, 0.0, 0.0013321136370576993,
    -0.00059016429519687813, -0.0011824506723456124, 0.00049489388533118135,
    0.037134512645606126, -0.0031493029690716264, -0.0006390309761683655,
    -0.0014215594461411362, 0.00053804502503600323, 0.042917507816890875,
    0.0042147871947828932, -0.00071620691080428111, -0.0030095120515977,
    0.00059728465468724334, 0.05106836191602384, 0.031441407203073861,
    0.0092128188671670858, -0.0063067347987153409, 0.00063921611635005867,
    0.057402639248955591, 0.0093417225529347347, -0.00075416559771109785,
    -0.0051598225209784718, 0.00062651441883167984, 0.056867247503671295, 0.0,
    -1.1578111012948644, -0.0012105572669273321, -11.100414582057136,
    0.023596819304617659, -1.3077624195215107, -1.1214610350472398,
    -0.0022429590081774857, -11.313406793690907, 0.02483829066468889,
    -1.2581747181349565, 0.87307295030699472, -0.0043776437837801368,
    -11.780685411434813, 0.025960924136656304, -1.270854349311171,
    5.0416287785376639, -0.0063067347987153409, 87.660371960451286,
    0.025416759840319249, -1.4665408382193006, 0.0874042975546799,
    -0.003625842528923881, -11.445471510998242, 0.025337145559688214,
    -1.2976527976883068, 0.0, 0.00069601727890802423, 0.00049671390581633966,
    0.023465029102411994, -0.00046520260228578972, -0.023501323503767175,
    0.0029256333983415793, 0.0005368421069435219, 0.024238469199501712,
    -0.00050070461796487, -0.027986245664067478, 0.0092597939385912452,
    0.00059321212983581048, 0.025168311872774088, -0.00055263291924495918,
    -0.03468948382058288, 0.020349394175065729, 0.00063921611635005867,
    0.025416759840319249, 0.0094017432701951863, -0.041119528830087786,
    0.0023177329281949934, 0.00063192948575346213, 0.026314940629046608,
    -0.000579205958854272, -0.04043839440492656, 0.0, -0.62943315975069913,
    0.037653433998941374, -1.2995891835215005, -0.023687438697209087,
    -9.4959398386980975, -0.16500326717921593, 0.043006081961612888,
    -1.327771694217067, -0.028269973020781311, -10.160128292655404,
    0.79008061948827624, 0.050677773437691975, -1.3884171928914883,
    -0.035019371692208132, -11.138420262937315, 1.9074400475782856,
    0.057402639248955591, -1.4665408382193006, -0.041119528830087786,
    88.004963328510357, -0.32034527105515248, 0.0573782236103064,
    -1.1633368066623881, -0.040114450767714221, -11.589765185507572, 0.0,
    -0.53014994382292069, -0.0029288806385197384, -0.80812039772805566,
    0.0044701210956103335, 0.068983665967758345, 0.93632347455845055,
    -0.0037570664579238385, -0.94740562660409722, 0.00427631548745728,
    0.039666441501316541, 3.7909450589865505, -0.0034789716833972277,
    -1.2185698669723526, 0.002375807999949285, -0.22138864483375117,
    -12.784993622858213, 0.0093417225529347347, 0.0874042975546799,
    0.0023177329281949934, -0.32034527105515248, 9.5254313979131,
    0.047234065192911588, 6.6400877559046929, 0.019038318344024661,
    1.7437416625219424, 0.0, 0.001740936025013828, -0.000502772121837824,
    -0.00041178799777898427, 0.00042165305889323309, 0.029224817014208794,
    -0.00080624691081804842, -0.00055311852080596228, -0.00087066098630071481,
    0.00046498149754279451, 0.034932703827684375, -0.0040276161280285916,
    -0.00063806203061990646, -0.001804521861975922, 0.00053749660802956,
    0.044567662235183145, -0.0011788848060508611, -0.00075416559771109785,
    -0.003625842528923881, 0.00063192948575346213, 0.0573782236103064,
    0.047234065192911588, 0.009119253347332261, -0.00922787420021837,
    0.00070663479383462091, 0.0682057073262272, 0.0, -0.9321183508650529,
    -3.173767985618556E-5, -10.214406422952711, 0.020719982115643416,
    -1.3026033068758094, -1.0037465798878151, -0.00092195232481172566,
    -10.446262596174813, 0.021969246427482603, -1.2664809968457063,
    -1.2066365801769023, -0.0023906240612461631, -10.823677081279452,
    0.024085181630646386, -1.1995359965005163, 0.42874002198613426,
    -0.0051598225209784718, -11.445471510998242, 0.026314940629046608,
    -1.1633368066623881, 6.6400877559046929, -0.00922787420021837,
    87.660864870553411, 0.026582440724949224, -1.3306108675116899, 0.0,
    0.00099879481043596563, 0.00042444837008698451, 0.020919314121880292,
    -0.00040111261742248463, -0.017683691122647609, 0.0020304228683625507,
    0.00046717744902474175, 0.021873093393181366, -0.00043818187037944126,
    -0.022278199418884741, 0.0028014082937405245, 0.00053792006255711346,
    0.023610205407387352, -0.00049907743870915647, -0.02988937164636344,
    0.010082184076887907, 0.00062651441883167984, 0.025337145559688214,
    -0.000579205958854272, -0.040114450767714221, 0.019038318344024661,
    0.00070663479383462091, 0.026582440724949224, 0.0093474624726795578,
    -0.050072989373426247, 0.0, -0.52394876698016768, 0.029698443559885365,
    -1.2538416889582, -0.017705220376415403, -8.2622499382595969,
    -0.31840002191304623, 0.0353978340020979, -1.2594013457280875,
    -0.022407091104289574, -8.94933118352301, -0.17050153189634418,
    0.044887755120243, -1.2446325491491794, -0.03012864354759591,
    -10.082982004860426, 0.92865579679905863, 0.056867247503671295,
    -1.2976527976883068, -0.04043839440492656, -11.589765185507572,
    1.7437416625219424, 0.0682057073262272, -1.3306108675116899,
    -0.050072989373426247, 87.026539683327115, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 1.0E-6 };

  int32_T c3_i139;
  int32_T c3_i140;
  int32_T c3_i141;
  int32_T c3_i142;
  int32_T c3_i143;
  int32_T c3_i144;
  int32_T c3_i145;
  int32_T c3_i146;
  real_T c3_f_u[6];
  const mxArray *c3_y = NULL;
  real_T c3_g_u;
  const mxArray *c3_b_y = NULL;
  real_T c3_h_u;
  const mxArray *c3_c_y = NULL;
  real_T c3_i_u;
  const mxArray *c3_d_y = NULL;
  real_T c3_j_u;
  const mxArray *c3_e_y = NULL;
  int32_T c3_i147;
  real_T c3_k_u[6];
  const mxArray *c3_f_y = NULL;
  real_T c3_l_u;
  const mxArray *c3_g_y = NULL;
  real_T c3_m_u;
  const mxArray *c3_h_y = NULL;
  real_T c3_n_u;
  const mxArray *c3_i_y = NULL;
  boolean_T c3_o_u;
  const mxArray *c3_j_y = NULL;
  int32_T c3_i148;
  real_T c3_p_u[6];
  const mxArray *c3_k_y = NULL;
  real_T c3_q_u;
  const mxArray *c3_l_y = NULL;
  const mxArray *c3_b_v = NULL;
  const mxArray *c3_b_vseq = NULL;
  const mxArray *c3_b_rseq = NULL;
  real_T c3_dv36[120];
  int32_T c3_i149;
  real_T c3_dv37[21];
  int32_T c3_i150;
  int32_T c3_i151;
  int32_T c3_i152;
  int32_T c3_i153;
  int32_T c3_i154;
  int32_T c3_i155;
  int32_T c3_i156;
  real_T c3_b[13];
  int32_T c3_i157;
  real_T c3_m_y[6];
  int32_T c3_i158;
  int32_T c3_i159;
  static real_T c3_b_a[78] = { 0.0, -0.0013998178359061748, 0.0, 0.0,
    -0.0011574167693600053, 0.0, -0.23905862049559551, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.017815863366045428, 0.0, 0.99999999999755462, 0.014730758882736285,
    0.0, 0.0, 0.00318264292988869, 0.0, 0.0, 0.0035981317144209309, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.014148947002773063, 0.99999999999520528, 0.0, 0.0, 0.0, 0.0,
    -0.0011574167693600053, 0.0, 0.0, 0.0, -2.0970587047059008, 0.0, 0.0, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  real_T c3_b_b;
  int32_T c3_i160;
  real_T c3_n_y[6];
  int32_T c3_i161;
  int32_T c3_i162;
  int32_T c3_i163;
  int32_T c3_i164;
  real_T c3_o_y[13];
  int32_T c3_i165;
  int32_T c3_i166;
  int32_T c3_i167;
  int32_T c3_i168;
  int32_T c3_i169;
  real_T c3_r_u[120];
  const mxArray *c3_p_y = NULL;
  int32_T c3_i170;
  real_T c3_s_u[21];
  const mxArray *c3_q_y = NULL;
  int32_T c3_i171;
  real_T c3_t_u[5];
  const mxArray *c3_r_y = NULL;
  int32_T c3_i172;
  real_T c3_u_u[5];
  const mxArray *c3_s_y = NULL;
  int32_T c3_i173;
  real_T c3_v_u[6];
  const mxArray *c3_t_y = NULL;
  int32_T c3_i174;
  real_T c3_w_u[6];
  const mxArray *c3_u_y = NULL;
  real_T c3_x_u;
  const mxArray *c3_v_y = NULL;
  int32_T c3_i175;
  real_T c3_y_u[13];
  const mxArray *c3_w_y = NULL;
  int32_T c3_i176;
  real_T c3_ab_u[5];
  const mxArray *c3_x_y = NULL;
  int32_T c3_i177;
  boolean_T c3_bb_u[221];
  const mxArray *c3_y_y = NULL;
  boolean_T c3_cb_u;
  const mxArray *c3_ab_y = NULL;
  real_T c3_db_u;
  const mxArray *c3_bb_y = NULL;
  real_T c3_eb_u;
  const mxArray *c3_cb_y = NULL;
  real_T c3_fb_u;
  const mxArray *c3_db_y = NULL;
  int32_T c3_i178;
  real_T c3_gb_u[676];
  const mxArray *c3_eb_y = NULL;
  int32_T c3_i179;
  real_T c3_hb_u[325];
  const mxArray *c3_fb_y = NULL;
  int32_T c3_i180;
  real_T c3_ib_u[125];
  const mxArray *c3_gb_y = NULL;
  int32_T c3_i181;
  real_T c3_jb_u[2500];
  const mxArray *c3_hb_y = NULL;
  int32_T c3_i182;
  const mxArray *c3_ib_y = NULL;
  int32_T c3_i183;
  real_T c3_kb_u[525];
  const mxArray *c3_jb_y = NULL;
  int32_T c3_i184;
  real_T c3_lb_u[195];
  const mxArray *c3_kb_y = NULL;
  int32_T c3_i185;
  real_T c3_mb_u[2535];
  const mxArray *c3_lb_y = NULL;
  int32_T c3_i186;
  real_T c3_nb_u[975];
  const mxArray *c3_mb_y = NULL;
  int32_T c3_i187;
  const mxArray *c3_nb_y = NULL;
  int32_T c3_i188;
  real_T c3_ob_u[26];
  const mxArray *c3_ob_y = NULL;
  int32_T c3_i189;
  real_T c3_pb_u[100];
  const mxArray *c3_pb_y = NULL;
  real_T c3_qb_u;
  const mxArray *c3_qb_y = NULL;
  int32_T c3_i190;
  real_T c3_rb_u[5];
  const mxArray *c3_rb_y = NULL;
  real_T c3_sb_u;
  const mxArray *c3_sb_y = NULL;
  int32_T c3_i191;
  real_T c3_tb_u[6];
  const mxArray *c3_tb_y = NULL;
  real_T c3_ub_u;
  const mxArray *c3_ub_y = NULL;
  real_T c3_vb_u;
  const mxArray *c3_vb_y = NULL;
  boolean_T c3_wb_u;
  const mxArray *c3_wb_y = NULL;
  real_T c3_xb_u;
  const mxArray *c3_xb_y = NULL;
  real_T c3_yb_u;
  const mxArray *c3_yb_y = NULL;
  real_T c3_ac_u;
  const mxArray *c3_ac_y = NULL;
  real_T c3_bc_u;
  const mxArray *c3_bc_y = NULL;
  real_T c3_cc_u;
  const mxArray *c3_cc_y = NULL;
  real_T c3_dc_u;
  const mxArray *c3_dc_y = NULL;
  real_T c3_ec_u;
  const mxArray *c3_ec_y = NULL;
  real_T c3_fc_u;
  const mxArray *c3_fc_y = NULL;
  real_T c3_gc_u;
  const mxArray *c3_gc_y = NULL;
  int32_T c3_i192;
  real_T c3_hc_u[676];
  const mxArray *c3_hc_y = NULL;
  real_T c3_ic_u;
  const mxArray *c3_ic_y = NULL;
  int32_T c3_i193;
  real_T c3_jc_u[676];
  const mxArray *c3_jc_y = NULL;
  int32_T c3_i194;
  const mxArray *c3_kc_y = NULL;
  int32_T c3_i195;
  real_T c3_kc_u[6];
  const mxArray *c3_lc_y = NULL;
  int32_T c3_i196;
  real_T c3_lc_u[5];
  const mxArray *c3_mc_y = NULL;
  int32_T c3_i197;
  real_T c3_mc_u[5];
  const mxArray *c3_nc_y = NULL;
  real_T c3_nc_u;
  const mxArray *c3_oc_y = NULL;
  real_T c3_oc_u;
  const mxArray *c3_pc_y = NULL;
  real_T c3_pc_u;
  const mxArray *c3_qc_y = NULL;
  real_T c3_qc_u;
  const mxArray *c3_rc_y = NULL;
  real_T c3_rc_u;
  const mxArray *c3_sc_y = NULL;
  real_T c3_sc_u;
  const mxArray *c3_tc_y = NULL;
  real_T c3_tc_u;
  const mxArray *c3_uc_y = NULL;
  real_T c3_uc_u;
  const mxArray *c3_vc_y = NULL;
  real_T c3_vc_u;
  const mxArray *c3_wc_y = NULL;
  real_T c3_wc_u;
  const mxArray *c3_xc_y = NULL;
  real_T c3_xc_u;
  const mxArray *c3_yc_y = NULL;
  real_T c3_yc_u;
  const mxArray *c3_ad_y = NULL;
  real_T c3_ad_u;
  const mxArray *c3_bd_y = NULL;
  int32_T c3_i198;
  real_T c3_bd_u[500];
  const mxArray *c3_cd_y = NULL;
  boolean_T c3_cd_u;
  const mxArray *c3_dd_y = NULL;
  int32_T c3_i199;
  real_T c3_dd_u[169];
  const mxArray *c3_ed_y = NULL;
  int32_T c3_i200;
  real_T c3_ed_u[65];
  const mxArray *c3_fd_y = NULL;
  int32_T c3_i201;
  real_T c3_fd_u[13];
  const mxArray *c3_gd_y = NULL;
  int32_T c3_i202;
  real_T c3_gd_u[78];
  const mxArray *c3_hd_y = NULL;
  int32_T c3_i203;
  real_T c3_hd_u[6];
  const mxArray *c3_id_y = NULL;
  int32_T c3_i204;
  real_T c3_id_u[195];
  const mxArray *c3_jd_y = NULL;
  real_T c3_jd_u;
  const mxArray *c3_kd_y = NULL;
  int32_T c3_i205;
  real_T c3_kd_u[5];
  const mxArray *c3_ld_y = NULL;
  int32_T c3_i206;
  real_T c3_ld_u[6];
  const mxArray *c3_md_y = NULL;
  real_T c3_md_u;
  const mxArray *c3_nd_y = NULL;
  real_T c3_nd_u;
  const mxArray *c3_od_y = NULL;
  const mxArray *c3_c_iAout = NULL;
  const mxArray *c3_c_status = NULL;
  const mxArray *c3_c_useq = NULL;
  const mxArray *c3_c_cost = NULL;
  const mxArray *c3_od_u = NULL;
  real_T c3_dv38[5];
  int32_T c3_i207;
  real_T c3_dv39[100];
  int32_T c3_i208;
  boolean_T c3_bv1[221];
  int32_T c3_i209;
  int32_T c3_i210;
  int32_T c3_i211;
  int32_T c3_i212;
  int32_T c3_i213;
  int32_T c3_i214;
  real_T c3_c_b[5];
  int32_T c3_i215;
  int32_T c3_i216;
  int32_T c3_i217;
  real_T c3_d_b;
  int32_T c3_i218;
  real_T c3_pd_y[13];
  int32_T c3_i219;
  int32_T c3_i220;
  real_T c3_qd_y[13];
  int32_T c3_i221;
  int32_T c3_i222;
  int32_T c3_i223;
  int32_T c3_i224;
  int32_T c3_i225;
  int32_T c3_i226;
  int32_T c3_i227;
  int32_T c3_i228;
  int32_T c3_i229;
  int32_T c3_i230;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c3_sfEvent);
  c3_hoistedGlobal = *chartInstance->c3_md;
  c3_b_hoistedGlobal = *chartInstance->c3_switch_in;
  c3_c_hoistedGlobal = *chartInstance->c3_rhoeps;
  for (c3_i93 = 0; c3_i93 < 13; c3_i93++) {
    c3_b_xk[c3_i93] = (*chartInstance->c3_xk)[c3_i93];
  }

  for (c3_i94 = 0; c3_i94 < 5; c3_i94++) {
    c3_b_old_u[c3_i94] = (*chartInstance->c3_old_u)[c3_i94];
  }

  for (c3_i95 = 0; c3_i95 < 6; c3_i95++) {
    c3_b_ym[c3_i95] = (*chartInstance->c3_ym)[c3_i95];
  }

  for (c3_i96 = 0; c3_i96 < 6; c3_i96++) {
    c3_b_ref[c3_i96] = (*chartInstance->c3_ref)[c3_i96];
  }

  c3_b_md = c3_hoistedGlobal;
  for (c3_i97 = 0; c3_i97 < 5; c3_i97++) {
    c3_b_umin[c3_i97] = (*chartInstance->c3_umin)[c3_i97];
  }

  for (c3_i98 = 0; c3_i98 < 5; c3_i98++) {
    c3_b_umax[c3_i98] = (*chartInstance->c3_umax)[c3_i98];
  }

  for (c3_i99 = 0; c3_i99 < 6; c3_i99++) {
    c3_b_ymin[c3_i99] = (*chartInstance->c3_ymin)[c3_i99];
  }

  for (c3_i100 = 0; c3_i100 < 6; c3_i100++) {
    c3_b_ymax[c3_i100] = (*chartInstance->c3_ymax)[c3_i100];
  }

  c3_b_switch_in = c3_b_hoistedGlobal;
  for (c3_i101 = 0; c3_i101 < 5; c3_i101++) {
    c3_b_ext_mv[c3_i101] = (*chartInstance->c3_ext_mv)[c3_i101];
  }

  for (c3_i102 = 0; c3_i102 < 5; c3_i102++) {
    c3_b_MVtarget[c3_i102] = (*chartInstance->c3_MVtarget)[c3_i102];
  }

  for (c3_i103 = 0; c3_i103 < 6; c3_i103++) {
    c3_b_ywt[c3_i103] = (*chartInstance->c3_ywt)[c3_i103];
  }

  for (c3_i104 = 0; c3_i104 < 5; c3_i104++) {
    c3_b_uwt[c3_i104] = (*chartInstance->c3_uwt)[c3_i104];
  }

  for (c3_i105 = 0; c3_i105 < 5; c3_i105++) {
    c3_b_duwt[c3_i105] = (*chartInstance->c3_duwt)[c3_i105];
  }

  c3_b_rhoeps = c3_c_hoistedGlobal;
  for (c3_i106 = 0; c3_i106 < 221; c3_i106++) {
    c3_b_iA[c3_i106] = (*chartInstance->c3_iA)[c3_i106];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 112U, 112U, c3_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_isSimulation, 0U, c3_q_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_isAdaptive, 1U, c3_q_sf_marshallOut,
    c3_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_isDouble, 2U, c3_q_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_ZERO, 3U, c3_c_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_ONE, 4U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_rseq, 5U, c3_db_sf_marshallOut,
    c3_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_vseq, 6U, c3_cb_sf_marshallOut,
    c3_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_v, 7U, c3_c_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_delmv, 8U, c3_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_ym_est, 9U, c3_f_sf_marshallOut,
    c3_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_y_innov, 10U, c3_f_sf_marshallOut,
    c3_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_utargetValue, 11U, c3_r_sf_marshallOut,
    c3_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_isQP, 12U, c3_q_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_nx, 13U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_nu, 14U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_ny, 15U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_degrees, 16U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Hinv, 17U, c3_p_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Kx, 18U, c3_bb_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Ku1, 19U, c3_ab_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Kut, 20U, c3_y_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(chartInstance->c3_c_Kr, 21U, c3_x_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Kv, 22U, c3_w_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Mlim, 23U, c3_j_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Mx, 24U, c3_v_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Mu1, 25U, c3_u_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(chartInstance->c3_c_Mv, 26U, c3_t_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_z_degrees, 27U, c3_s_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_utarget, 28U, c3_r_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_p, 29U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_uoff, 30U, c3_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_voff, 31U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_yoff, 32U, c3_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_maxiter, 33U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_nxQP, 34U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_openloopflag, 35U, c3_q_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_lims_inport, 36U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_umin, 37U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_umax, 38U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_ymin, 39U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_ymax, 40U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_switch_inport, 41U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_switch, 42U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_enable_value, 43U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_return_cost, 44U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_H, 45U, c3_p_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_return_sequence, 46U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Linv, 47U, c3_p_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(chartInstance->c3_c_Ac, 48U, c3_o_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_ywt, 49U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_uwt, 50U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_duwt, 51U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_rhoeps, 52U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_Wy, 53U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_Wdu, 54U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_Jm, 55U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_SuJm, 56U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_Su1, 57U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_Sx, 58U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_Hv, 59U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_Wu, 60U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_I1, 61U, c3_n_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_A, 62U, c3_m_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Bu, 63U, c3_l_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_b_Bv, 64U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_C, 65U, c3_k_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Dv, 66U, c3_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Mrows, 67U, c3_j_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_nCC, 68U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Ecc, 69U, c3_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Fcc, 70U, c3_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_Scc, 71U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_Gcc, 72U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_nv, 73U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_md, 74U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_ref, 75U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_uref, 76U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_mv, 77U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Rscale, 78U, c3_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_MDscale, 79U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_myindex, 80U, c3_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_b_myoff, 81U, c3_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_b_xoff, 82U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_CustomEstimation, 83U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_M, 84U, c3_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_L, 85U, c3_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 86U, c3_c_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 87U, c3_c_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_b_xk, 88U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_b_old_u, 89U, c3_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_b_ym, 90U, c3_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_b_ref, 91U, c3_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_b_md, 92U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_b_umin, 93U, c3_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_b_umax, 94U, c3_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_b_ymin, 95U, c3_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_b_ymax, 96U, c3_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_b_switch_in, 97U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_b_ext_mv, 98U, c3_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_b_MVtarget, 99U, c3_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_b_ywt, 100U, c3_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_b_uwt, 101U, c3_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_b_duwt, 102U, c3_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_b_rhoeps, 103U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_b_iA, 104U, c3_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_b_xk1, 105U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_e_u, 106U, c3_e_sf_marshallOut,
    c3_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_cost, 107U, c3_c_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_b_useq, 108U, c3_d_sf_marshallOut,
    c3_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_status, 109U, c3_c_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_b_xest, 110U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_b_iAout, 111U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  for (c3_i107 = 0; c3_i107 < 78; c3_i107++) {
    c3_c_L[c3_i107] = c3_d_L[c3_i107];
  }

  for (c3_i108 = 0; c3_i108 < 78; c3_i108++) {
    c3_c_M[c3_i108] = c3_d_M[c3_i108];
  }

  c3_c_CustomEstimation = c3_b_CustomEstimation;
  for (c3_i109 = 0; c3_i109 < 13; c3_i109++) {
    c3_b_xoff[c3_i109] = 0.0;
  }

  for (c3_i110 = 0; c3_i110 < 6; c3_i110++) {
    c3_b_myoff[c3_i110] = c3_d_yoff[c3_i110];
  }

  for (c3_i111 = 0; c3_i111 < 6; c3_i111++) {
    c3_c_myindex[c3_i111] = 1.0 + (real_T)c3_i111;
  }

  c3_c_MDscale = c3_b_MDscale;
  for (c3_i112 = 0; c3_i112 < 6; c3_i112++) {
    c3_c_Rscale[c3_i112] = 1.0;
  }

  c3_c_no_mv = c3_b_no_mv;
  c3_c_no_uref = c3_b_no_uref;
  c3_c_no_ref = c3_b_no_ref;
  c3_c_no_md = c3_b_no_md;
  c3_c_nv = c3_b_nv;
  c3_c_Gcc = c3_b_Gcc;
  c3_c_Scc = c3_b_Scc;
  for (c3_i113 = 0; c3_i113 < 6; c3_i113++) {
    c3_c_Fcc[c3_i113] = 0.0;
  }

  for (c3_i114 = 0; c3_i114 < 5; c3_i114++) {
    c3_c_Ecc[c3_i114] = 0.0;
  }

  c3_c_nCC = c3_b_nCC;
  for (c3_i115 = 0; c3_i115 < 195; c3_i115++) {
    c3_c_Mrows[c3_i115] = c3_d_Mrows[c3_i115];
  }

  for (c3_i116 = 0; c3_i116 < 6; c3_i116++) {
    c3_c_Dv[c3_i116] = 0.0;
  }

  for (c3_i117 = 0; c3_i117 < 78; c3_i117++) {
    c3_c_C[c3_i117] = c3_d_C[c3_i117];
  }

  for (c3_i118 = 0; c3_i118 < 13; c3_i118++) {
    c3_b_Bv[c3_i118] = 0.0;
  }

  for (c3_i119 = 0; c3_i119 < 65; c3_i119++) {
    c3_c_Bu[c3_i119] = c3_d_Bu[c3_i119];
  }

  for (c3_i120 = 0; c3_i120 < 169; c3_i120++) {
    c3_c_A[c3_i120] = c3_d_A[c3_i120];
  }

  for (c3_i121 = 0; c3_i121 < 500; c3_i121++) {
    c3_c_I1[c3_i121] = c3_d_I1[c3_i121];
  }

  c3_c_Wu = c3_b_Wu;
  c3_c_Hv = c3_b_Hv;
  c3_c_Sx = c3_b_Sx;
  c3_c_Su1 = c3_b_Su1;
  c3_c_SuJm = c3_b_SuJm;
  c3_c_Jm = c3_b_Jm;
  c3_c_Wdu = c3_b_Wdu;
  c3_c_Wy = c3_b_Wy;
  c3_c_no_rhoeps = c3_b_no_rhoeps;
  c3_c_no_duwt = c3_b_no_duwt;
  c3_c_no_uwt = c3_b_no_uwt;
  c3_c_no_ywt = c3_b_no_ywt;
  for (c3_i122 = 0; c3_i122 < 5070; c3_i122++) {
    chartInstance->c3_c_Ac[c3_i122] = c3_d_Ac[c3_i122];
  }

  for (c3_i123 = 0; c3_i123 < 676; c3_i123++) {
    c3_c_Linv[c3_i123] = c3_d_Linv[c3_i123];
  }

  c3_c_return_sequence = c3_b_return_sequence;
  for (c3_i124 = 0; c3_i124 < 676; c3_i124++) {
    c3_c_H[c3_i124] = c3_d_H[c3_i124];
  }

  c3_c_return_cost = c3_b_return_cost;
  c3_c_enable_value = c3_b_enable_value;
  c3_c_no_switch = c3_b_no_switch;
  c3_c_switch_inport = c3_b_switch_inport;
  c3_c_no_ymax = c3_b_no_ymax;
  c3_c_no_ymin = c3_b_no_ymin;
  c3_c_no_umax = c3_b_no_umax;
  c3_c_no_umin = c3_b_no_umin;
  c3_c_lims_inport = c3_b_lims_inport;
  c3_c_openloopflag = c3_b_openloopflag;
  c3_c_nxQP = c3_b_nxQP;
  c3_c_maxiter = c3_b_maxiter;
  for (c3_i125 = 0; c3_i125 < 6; c3_i125++) {
    c3_c_yoff[c3_i125] = c3_d_yoff[c3_i125];
  }

  c3_c_voff = c3_b_voff;
  for (c3_i126 = 0; c3_i126 < 5; c3_i126++) {
    c3_c_uoff[c3_i126] = c3_d_uoff[c3_i126];
  }

  c3_c_p = c3_b_p;
  for (c3_i127 = 0; c3_i127 < 100; c3_i127++) {
    c3_c_utarget[c3_i127] = 0.0;
  }

  for (c3_i128 = 0; c3_i128 < 26; c3_i128++) {
    c3_c_z_degrees[c3_i128] = 0.0;
  }

  for (c3_i129 = 0; c3_i129 < 4095; c3_i129++) {
    chartInstance->c3_c_Mv[c3_i129] = -0.0;
  }

  for (c3_i130 = 0; c3_i130 < 975; c3_i130++) {
    c3_c_Mu1[c3_i130] = c3_d_Mu1[c3_i130];
  }

  for (c3_i131 = 0; c3_i131 < 2535; c3_i131++) {
    c3_c_Mx[c3_i131] = c3_d_Mx[c3_i131];
  }

  for (c3_i132 = 0; c3_i132 < 195; c3_i132++) {
    c3_c_Mlim[c3_i132] = c3_d_Mlim[c3_i132];
  }

  for (c3_i133 = 0; c3_i133 < 525; c3_i133++) {
    c3_c_Kv[c3_i133] = 0.0;
  }

  for (c3_i134 = 0; c3_i134 < 3000; c3_i134++) {
    chartInstance->c3_c_Kr[c3_i134] = c3_d_Kr[c3_i134];
  }

  for (c3_i135 = 0; c3_i135 < 2500; c3_i135++) {
    c3_c_Kut[c3_i135] = -0.0;
  }

  for (c3_i136 = 0; c3_i136 < 125; c3_i136++) {
    c3_c_Ku1[c3_i136] = c3_d_Ku1[c3_i136];
  }

  for (c3_i137 = 0; c3_i137 < 325; c3_i137++) {
    c3_c_Kx[c3_i137] = c3_d_Kx[c3_i137];
  }

  for (c3_i138 = 0; c3_i138 < 676; c3_i138++) {
    c3_c_Hinv[c3_i138] = c3_d_Hinv[c3_i138];
  }

  c3_c_degrees = c3_b_degrees;
  c3_c_ny = c3_b_ny;
  c3_c_nu = c3_b_nu;
  c3_c_nx = c3_b_nx;
  c3_c_isQP = c3_b_isQP;
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 13);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 14);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 15);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 16);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 19);
  c3_isSimulation = true;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 20);
  c3_isAdaptive = false;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 21);
  c3_isDouble = true;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 22);
  c3_ZERO = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 23);
  c3_ONE = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 28);
  CV_EML_IF(0, 1, 0, c3_isSimulation);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 29);
  for (c3_i139 = 0; c3_i139 < 120; c3_i139++) {
    c3_rseq[c3_i139] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 30);
  for (c3_i140 = 0; c3_i140 < 21; c3_i140++) {
    c3_vseq[c3_i140] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 31);
  c3_v = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 32);
  for (c3_i141 = 0; c3_i141 < 13; c3_i141++) {
    c3_b_xk1[c3_i141] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 33);
  for (c3_i142 = 0; c3_i142 < 5; c3_i142++) {
    c3_e_u[c3_i142] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 34);
  c3_b_cost = c3_ZERO;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 35);
  for (c3_i143 = 0; c3_i143 < 100; c3_i143++) {
    c3_b_useq[c3_i143] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 36);
  c3_b_status = c3_ONE;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 37);
  for (c3_i144 = 0; c3_i144 < 13; c3_i144++) {
    c3_b_xest[c3_i144] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 38);
  for (c3_i145 = 0; c3_i145 < 221; c3_i145++) {
    c3_b_iAout[c3_i145] = c3_b_iA[c3_i145];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 42);
  CV_EML_IF(0, 1, 1, c3_isSimulation);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 44);
  CV_EML_IF(0, 1, 2, c3_isDouble);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 45);
  for (c3_i146 = 0; c3_i146 < 6; c3_i146++) {
    c3_f_u[c3_i146] = c3_b_ref[c3_i146];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_f_u, 0, 0U, 1U, 0U, 1, 6), false);
  c3_g_u = c3_b_md;
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_g_u, 0, 0U, 0U, 0U, 0), false);
  c3_h_u = c3_b_nv;
  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", &c3_h_u, 0, 0U, 0U, 0U, 0), false);
  c3_i_u = c3_b_ny;
  c3_d_y = NULL;
  sf_mex_assign(&c3_d_y, sf_mex_create("y", &c3_i_u, 0, 0U, 0U, 0U, 0), false);
  c3_j_u = c3_b_p;
  c3_e_y = NULL;
  sf_mex_assign(&c3_e_y, sf_mex_create("y", &c3_j_u, 0, 0U, 0U, 0U, 0), false);
  for (c3_i147 = 0; c3_i147 < 6; c3_i147++) {
    c3_k_u[c3_i147] = c3_d_yoff[c3_i147];
  }

  c3_f_y = NULL;
  sf_mex_assign(&c3_f_y, sf_mex_create("y", c3_k_u, 0, 0U, 1U, 0U, 1, 6), false);
  c3_l_u = c3_b_voff;
  c3_g_y = NULL;
  sf_mex_assign(&c3_g_y, sf_mex_create("y", &c3_l_u, 0, 0U, 0U, 0U, 0), false);
  c3_m_u = c3_b_no_md;
  c3_h_y = NULL;
  sf_mex_assign(&c3_h_y, sf_mex_create("y", &c3_m_u, 0, 0U, 0U, 0U, 0), false);
  c3_n_u = c3_b_no_ref;
  c3_i_y = NULL;
  sf_mex_assign(&c3_i_y, sf_mex_create("y", &c3_n_u, 0, 0U, 0U, 0U, 0), false);
  c3_o_u = c3_b_openloopflag;
  c3_j_y = NULL;
  sf_mex_assign(&c3_j_y, sf_mex_create("y", &c3_o_u, 11, 0U, 0U, 0U, 0), false);
  for (c3_i148 = 0; c3_i148 < 6; c3_i148++) {
    c3_p_u[c3_i148] = 1.0;
  }

  c3_k_y = NULL;
  sf_mex_assign(&c3_k_y, sf_mex_create("y", c3_p_u, 0, 0U, 1U, 0U, 1, 6), false);
  c3_q_u = c3_b_MDscale;
  c3_l_y = NULL;
  sf_mex_assign(&c3_l_y, sf_mex_create("y", &c3_q_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "mpcblock_refmd_double_mex", 3U,
                    12U, 14, c3_y, 14, c3_b_y, 14, c3_c_y, 14, c3_d_y, 14,
                    c3_e_y, 14, c3_f_y, 14, c3_g_y, 14, c3_h_y, 14, c3_i_y, 14,
                    c3_j_y, 14, c3_k_y, 14, c3_l_y, &c3_b_rseq, &c3_b_vseq,
                    &c3_b_v);
  c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_rseq), "rseq", c3_dv36);
  for (c3_i149 = 0; c3_i149 < 120; c3_i149++) {
    c3_rseq[c3_i149] = c3_dv36[c3_i149];
  }

  c3_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_vseq), "vseq", c3_dv37);
  for (c3_i150 = 0; c3_i150 < 21; c3_i150++) {
    c3_vseq[c3_i150] = c3_dv37[c3_i150];
  }

  c3_v = c3_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_v), "v");
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 56);
  for (c3_i151 = 0; c3_i151 < 5; c3_i151++) {
    c3_b_old_u[c3_i151] -= c3_d_uoff[c3_i151];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 57);
  CV_EML_IF(0, 1, 3, CV_RELATIONAL_EVAL(4U, 0U, 0, c3_b_no_mv, c3_ONE, -1, 0U,
             c3_b_no_mv == c3_ONE));
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 58);
  for (c3_i152 = 0; c3_i152 < 5; c3_i152++) {
    c3_delmv[c3_i152] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 66);
  for (c3_i153 = 0; c3_i153 < 13; c3_i153++) {
    c3_b_xk[c3_i153];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 67);
  CV_EML_IF(0, 1, 4, CV_RELATIONAL_EVAL(4U, 0U, 1, c3_b_CustomEstimation, c3_ONE,
             -1, 0U, c3_b_CustomEstimation == c3_ONE));
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 73);
  for (c3_i154 = 0; c3_i154 < 6; c3_i154++) {
    c3_b_ym[c3_i154] -= c3_d_yoff[c3_i154];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 76);
  c3_eml_scalar_eg(chartInstance);
  c3_eml_scalar_eg(chartInstance);
  c3_threshold(chartInstance);
  for (c3_i155 = 0; c3_i155 < 13; c3_i155++) {
    c3_b_xk[c3_i155];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 78);
  for (c3_i156 = 0; c3_i156 < 13; c3_i156++) {
    c3_b[c3_i156] = c3_b_xk[c3_i156];
  }

  c3_b_eml_scalar_eg(chartInstance);
  c3_b_eml_scalar_eg(chartInstance);
  c3_threshold(chartInstance);
  for (c3_i157 = 0; c3_i157 < 6; c3_i157++) {
    c3_m_y[c3_i157] = 0.0;
    c3_i158 = 0;
    for (c3_i159 = 0; c3_i159 < 13; c3_i159++) {
      c3_m_y[c3_i157] += c3_b_a[c3_i158 + c3_i157] * c3_b[c3_i159];
      c3_i158 += 6;
    }
  }

  c3_b_b = c3_v;
  for (c3_i160 = 0; c3_i160 < 6; c3_i160++) {
    c3_n_y[c3_i160] = 0.0 * c3_b_b;
  }

  for (c3_i161 = 0; c3_i161 < 6; c3_i161++) {
    c3_ym_est[c3_i161] = c3_m_y[c3_i161] + c3_n_y[c3_i161];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 79);
  for (c3_i162 = 0; c3_i162 < 6; c3_i162++) {
    c3_y_innov[c3_i162] = c3_b_ym[c3_i162] - c3_ym_est[c3_i162];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 80);
  for (c3_i163 = 0; c3_i163 < 6; c3_i163++) {
    c3_m_y[c3_i163] = c3_y_innov[c3_i163];
  }

  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  c3_threshold(chartInstance);
  for (c3_i164 = 0; c3_i164 < 13; c3_i164++) {
    c3_o_y[c3_i164] = 0.0;
    c3_i165 = 0;
    for (c3_i166 = 0; c3_i166 < 6; c3_i166++) {
      c3_o_y[c3_i164] += c3_d_M[c3_i165 + c3_i164] * c3_m_y[c3_i166];
      c3_i165 += 13;
    }
  }

  for (c3_i167 = 0; c3_i167 < 13; c3_i167++) {
    c3_b_xest[c3_i167] = c3_b_xk[c3_i167] + c3_o_y[c3_i167];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 85);
  CV_EML_IF(0, 1, 5, CV_RELATIONAL_EVAL(4U, 0U, 2, c3_b_no_uref, c3_ONE, -1, 0U,
             c3_b_no_uref == c3_ONE));
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 87);
  for (c3_i168 = 0; c3_i168 < 100; c3_i168++) {
    c3_utargetValue[c3_i168] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 95);
  CV_EML_IF(0, 1, 6, c3_isSimulation);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 97);
  CV_EML_IF(0, 1, 7, c3_isDouble);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 98);
  for (c3_i169 = 0; c3_i169 < 120; c3_i169++) {
    c3_r_u[c3_i169] = c3_rseq[c3_i169];
  }

  c3_p_y = NULL;
  sf_mex_assign(&c3_p_y, sf_mex_create("y", c3_r_u, 0, 0U, 1U, 0U, 1, 120),
                false);
  for (c3_i170 = 0; c3_i170 < 21; c3_i170++) {
    c3_s_u[c3_i170] = c3_vseq[c3_i170];
  }

  c3_q_y = NULL;
  sf_mex_assign(&c3_q_y, sf_mex_create("y", c3_s_u, 0, 0U, 1U, 0U, 1, 21), false);
  for (c3_i171 = 0; c3_i171 < 5; c3_i171++) {
    c3_t_u[c3_i171] = c3_b_umin[c3_i171];
  }

  c3_r_y = NULL;
  sf_mex_assign(&c3_r_y, sf_mex_create("y", c3_t_u, 0, 0U, 1U, 0U, 1, 5), false);
  for (c3_i172 = 0; c3_i172 < 5; c3_i172++) {
    c3_u_u[c3_i172] = c3_b_umax[c3_i172];
  }

  c3_s_y = NULL;
  sf_mex_assign(&c3_s_y, sf_mex_create("y", c3_u_u, 0, 0U, 1U, 0U, 1, 5), false);
  for (c3_i173 = 0; c3_i173 < 6; c3_i173++) {
    c3_v_u[c3_i173] = c3_b_ymin[c3_i173];
  }

  c3_t_y = NULL;
  sf_mex_assign(&c3_t_y, sf_mex_create("y", c3_v_u, 0, 0U, 1U, 0U, 1, 6), false);
  for (c3_i174 = 0; c3_i174 < 6; c3_i174++) {
    c3_w_u[c3_i174] = c3_b_ymax[c3_i174];
  }

  c3_u_y = NULL;
  sf_mex_assign(&c3_u_y, sf_mex_create("y", c3_w_u, 0, 0U, 1U, 0U, 1, 6), false);
  c3_x_u = c3_b_switch_in;
  c3_v_y = NULL;
  sf_mex_assign(&c3_v_y, sf_mex_create("y", &c3_x_u, 0, 0U, 0U, 0U, 0), false);
  for (c3_i175 = 0; c3_i175 < 13; c3_i175++) {
    c3_y_u[c3_i175] = c3_b_xest[c3_i175];
  }

  c3_w_y = NULL;
  sf_mex_assign(&c3_w_y, sf_mex_create("y", c3_y_u, 0, 0U, 1U, 0U, 1, 13), false);
  for (c3_i176 = 0; c3_i176 < 5; c3_i176++) {
    c3_ab_u[c3_i176] = c3_b_old_u[c3_i176];
  }

  c3_x_y = NULL;
  sf_mex_assign(&c3_x_y, sf_mex_create("y", c3_ab_u, 0, 0U, 1U, 0U, 1, 5), false);
  for (c3_i177 = 0; c3_i177 < 221; c3_i177++) {
    c3_bb_u[c3_i177] = c3_b_iA[c3_i177];
  }

  c3_y_y = NULL;
  sf_mex_assign(&c3_y_y, sf_mex_create("y", c3_bb_u, 11, 0U, 1U, 0U, 1, 221),
                false);
  c3_cb_u = c3_b_isQP;
  c3_ab_y = NULL;
  sf_mex_assign(&c3_ab_y, sf_mex_create("y", &c3_cb_u, 11, 0U, 0U, 0U, 0), false);
  c3_db_u = c3_b_nu;
  c3_bb_y = NULL;
  sf_mex_assign(&c3_bb_y, sf_mex_create("y", &c3_db_u, 0, 0U, 0U, 0U, 0), false);
  c3_eb_u = c3_b_ny;
  c3_cb_y = NULL;
  sf_mex_assign(&c3_cb_y, sf_mex_create("y", &c3_eb_u, 0, 0U, 0U, 0U, 0), false);
  c3_fb_u = c3_b_degrees;
  c3_db_y = NULL;
  sf_mex_assign(&c3_db_y, sf_mex_create("y", &c3_fb_u, 0, 0U, 0U, 0U, 0), false);
  for (c3_i178 = 0; c3_i178 < 676; c3_i178++) {
    c3_gb_u[c3_i178] = c3_d_Hinv[c3_i178];
  }

  c3_eb_y = NULL;
  sf_mex_assign(&c3_eb_y, sf_mex_create("y", c3_gb_u, 0, 0U, 1U, 0U, 2, 26, 26),
                false);
  for (c3_i179 = 0; c3_i179 < 325; c3_i179++) {
    c3_hb_u[c3_i179] = c3_d_Kx[c3_i179];
  }

  c3_fb_y = NULL;
  sf_mex_assign(&c3_fb_y, sf_mex_create("y", c3_hb_u, 0, 0U, 1U, 0U, 2, 13, 25),
                false);
  for (c3_i180 = 0; c3_i180 < 125; c3_i180++) {
    c3_ib_u[c3_i180] = c3_d_Ku1[c3_i180];
  }

  c3_gb_y = NULL;
  sf_mex_assign(&c3_gb_y, sf_mex_create("y", c3_ib_u, 0, 0U, 1U, 0U, 2, 5, 25),
                false);
  for (c3_i181 = 0; c3_i181 < 2500; c3_i181++) {
    c3_jb_u[c3_i181] = -0.0;
  }

  c3_hb_y = NULL;
  sf_mex_assign(&c3_hb_y, sf_mex_create("y", c3_jb_u, 0, 0U, 1U, 0U, 2, 100, 25),
                false);
  for (c3_i182 = 0; c3_i182 < 3000; c3_i182++) {
    chartInstance->c3_c_u[c3_i182] = c3_d_Kr[c3_i182];
  }

  c3_ib_y = NULL;
  sf_mex_assign(&c3_ib_y, sf_mex_create("y", chartInstance->c3_c_u, 0, 0U, 1U,
    0U, 2, 120, 25), false);
  for (c3_i183 = 0; c3_i183 < 525; c3_i183++) {
    c3_kb_u[c3_i183] = 0.0;
  }

  c3_jb_y = NULL;
  sf_mex_assign(&c3_jb_y, sf_mex_create("y", c3_kb_u, 0, 0U, 1U, 0U, 2, 21, 25),
                false);
  for (c3_i184 = 0; c3_i184 < 195; c3_i184++) {
    c3_lb_u[c3_i184] = c3_d_Mlim[c3_i184];
  }

  c3_kb_y = NULL;
  sf_mex_assign(&c3_kb_y, sf_mex_create("y", c3_lb_u, 0, 0U, 1U, 0U, 1, 195),
                false);
  for (c3_i185 = 0; c3_i185 < 2535; c3_i185++) {
    c3_mb_u[c3_i185] = c3_d_Mx[c3_i185];
  }

  c3_lb_y = NULL;
  sf_mex_assign(&c3_lb_y, sf_mex_create("y", c3_mb_u, 0, 0U, 1U, 0U, 2, 195, 13),
                false);
  for (c3_i186 = 0; c3_i186 < 975; c3_i186++) {
    c3_nb_u[c3_i186] = c3_d_Mu1[c3_i186];
  }

  c3_mb_y = NULL;
  sf_mex_assign(&c3_mb_y, sf_mex_create("y", c3_nb_u, 0, 0U, 1U, 0U, 2, 195, 5),
                false);
  for (c3_i187 = 0; c3_i187 < 4095; c3_i187++) {
    chartInstance->c3_b_u[c3_i187] = -0.0;
  }

  c3_nb_y = NULL;
  sf_mex_assign(&c3_nb_y, sf_mex_create("y", chartInstance->c3_b_u, 0, 0U, 1U,
    0U, 2, 195, 21), false);
  for (c3_i188 = 0; c3_i188 < 26; c3_i188++) {
    c3_ob_u[c3_i188] = 0.0;
  }

  c3_ob_y = NULL;
  sf_mex_assign(&c3_ob_y, sf_mex_create("y", c3_ob_u, 0, 0U, 1U, 0U, 1, 26),
                false);
  for (c3_i189 = 0; c3_i189 < 100; c3_i189++) {
    c3_pb_u[c3_i189] = c3_utargetValue[c3_i189];
  }

  c3_pb_y = NULL;
  sf_mex_assign(&c3_pb_y, sf_mex_create("y", c3_pb_u, 0, 0U, 1U, 0U, 1, 100),
                false);
  c3_qb_u = c3_b_p;
  c3_qb_y = NULL;
  sf_mex_assign(&c3_qb_y, sf_mex_create("y", &c3_qb_u, 0, 0U, 0U, 0U, 0), false);
  for (c3_i190 = 0; c3_i190 < 5; c3_i190++) {
    c3_rb_u[c3_i190] = c3_d_uoff[c3_i190];
  }

  c3_rb_y = NULL;
  sf_mex_assign(&c3_rb_y, sf_mex_create("y", c3_rb_u, 0, 0U, 1U, 0U, 1, 5),
                false);
  c3_sb_u = c3_b_voff;
  c3_sb_y = NULL;
  sf_mex_assign(&c3_sb_y, sf_mex_create("y", &c3_sb_u, 0, 0U, 0U, 0U, 0), false);
  for (c3_i191 = 0; c3_i191 < 6; c3_i191++) {
    c3_tb_u[c3_i191] = c3_d_yoff[c3_i191];
  }

  c3_tb_y = NULL;
  sf_mex_assign(&c3_tb_y, sf_mex_create("y", c3_tb_u, 0, 0U, 1U, 0U, 1, 6),
                false);
  c3_ub_u = c3_b_maxiter;
  c3_ub_y = NULL;
  sf_mex_assign(&c3_ub_y, sf_mex_create("y", &c3_ub_u, 0, 0U, 0U, 0U, 0), false);
  c3_vb_u = c3_b_nxQP;
  c3_vb_y = NULL;
  sf_mex_assign(&c3_vb_y, sf_mex_create("y", &c3_vb_u, 0, 0U, 0U, 0U, 0), false);
  c3_wb_u = c3_b_openloopflag;
  c3_wb_y = NULL;
  sf_mex_assign(&c3_wb_y, sf_mex_create("y", &c3_wb_u, 11, 0U, 0U, 0U, 0), false);
  c3_xb_u = c3_b_lims_inport;
  c3_xb_y = NULL;
  sf_mex_assign(&c3_xb_y, sf_mex_create("y", &c3_xb_u, 0, 0U, 0U, 0U, 0), false);
  c3_yb_u = c3_b_no_umin;
  c3_yb_y = NULL;
  sf_mex_assign(&c3_yb_y, sf_mex_create("y", &c3_yb_u, 0, 0U, 0U, 0U, 0), false);
  c3_ac_u = c3_b_no_umax;
  c3_ac_y = NULL;
  sf_mex_assign(&c3_ac_y, sf_mex_create("y", &c3_ac_u, 0, 0U, 0U, 0U, 0), false);
  c3_bc_u = c3_b_no_ymin;
  c3_bc_y = NULL;
  sf_mex_assign(&c3_bc_y, sf_mex_create("y", &c3_bc_u, 0, 0U, 0U, 0U, 0), false);
  c3_cc_u = c3_b_no_ymax;
  c3_cc_y = NULL;
  sf_mex_assign(&c3_cc_y, sf_mex_create("y", &c3_cc_u, 0, 0U, 0U, 0U, 0), false);
  c3_dc_u = c3_b_switch_inport;
  c3_dc_y = NULL;
  sf_mex_assign(&c3_dc_y, sf_mex_create("y", &c3_dc_u, 0, 0U, 0U, 0U, 0), false);
  c3_ec_u = c3_b_no_switch;
  c3_ec_y = NULL;
  sf_mex_assign(&c3_ec_y, sf_mex_create("y", &c3_ec_u, 0, 0U, 0U, 0U, 0), false);
  c3_fc_u = c3_b_enable_value;
  c3_fc_y = NULL;
  sf_mex_assign(&c3_fc_y, sf_mex_create("y", &c3_fc_u, 0, 0U, 0U, 0U, 0), false);
  c3_gc_u = c3_b_return_cost;
  c3_gc_y = NULL;
  sf_mex_assign(&c3_gc_y, sf_mex_create("y", &c3_gc_u, 0, 0U, 0U, 0U, 0), false);
  for (c3_i192 = 0; c3_i192 < 676; c3_i192++) {
    c3_hc_u[c3_i192] = c3_d_H[c3_i192];
  }

  c3_hc_y = NULL;
  sf_mex_assign(&c3_hc_y, sf_mex_create("y", c3_hc_u, 0, 0U, 1U, 0U, 2, 26, 26),
                false);
  c3_ic_u = c3_b_return_sequence;
  c3_ic_y = NULL;
  sf_mex_assign(&c3_ic_y, sf_mex_create("y", &c3_ic_u, 0, 0U, 0U, 0U, 0), false);
  for (c3_i193 = 0; c3_i193 < 676; c3_i193++) {
    c3_jc_u[c3_i193] = c3_d_Linv[c3_i193];
  }

  c3_jc_y = NULL;
  sf_mex_assign(&c3_jc_y, sf_mex_create("y", c3_jc_u, 0, 0U, 1U, 0U, 2, 26, 26),
                false);
  for (c3_i194 = 0; c3_i194 < 5070; c3_i194++) {
    chartInstance->c3_u[c3_i194] = c3_d_Ac[c3_i194];
  }

  c3_kc_y = NULL;
  sf_mex_assign(&c3_kc_y, sf_mex_create("y", chartInstance->c3_u, 0, 0U, 1U, 0U,
    2, 195, 26), false);
  for (c3_i195 = 0; c3_i195 < 6; c3_i195++) {
    c3_kc_u[c3_i195] = c3_b_ywt[c3_i195];
  }

  c3_lc_y = NULL;
  sf_mex_assign(&c3_lc_y, sf_mex_create("y", c3_kc_u, 0, 0U, 1U, 0U, 1, 6),
                false);
  for (c3_i196 = 0; c3_i196 < 5; c3_i196++) {
    c3_lc_u[c3_i196] = c3_b_uwt[c3_i196];
  }

  c3_mc_y = NULL;
  sf_mex_assign(&c3_mc_y, sf_mex_create("y", c3_lc_u, 0, 0U, 1U, 0U, 1, 5),
                false);
  for (c3_i197 = 0; c3_i197 < 5; c3_i197++) {
    c3_mc_u[c3_i197] = c3_b_duwt[c3_i197];
  }

  c3_nc_y = NULL;
  sf_mex_assign(&c3_nc_y, sf_mex_create("y", c3_mc_u, 0, 0U, 1U, 0U, 1, 5),
                false);
  c3_nc_u = c3_b_rhoeps;
  c3_oc_y = NULL;
  sf_mex_assign(&c3_oc_y, sf_mex_create("y", &c3_nc_u, 0, 0U, 0U, 0U, 0), false);
  c3_oc_u = c3_b_no_ywt;
  c3_pc_y = NULL;
  sf_mex_assign(&c3_pc_y, sf_mex_create("y", &c3_oc_u, 0, 0U, 0U, 0U, 0), false);
  c3_pc_u = c3_b_no_uwt;
  c3_qc_y = NULL;
  sf_mex_assign(&c3_qc_y, sf_mex_create("y", &c3_pc_u, 0, 0U, 0U, 0U, 0), false);
  c3_qc_u = c3_b_no_duwt;
  c3_rc_y = NULL;
  sf_mex_assign(&c3_rc_y, sf_mex_create("y", &c3_qc_u, 0, 0U, 0U, 0U, 0), false);
  c3_rc_u = c3_b_no_rhoeps;
  c3_sc_y = NULL;
  sf_mex_assign(&c3_sc_y, sf_mex_create("y", &c3_rc_u, 0, 0U, 0U, 0U, 0), false);
  c3_sc_u = c3_b_Wy;
  c3_tc_y = NULL;
  sf_mex_assign(&c3_tc_y, sf_mex_create("y", &c3_sc_u, 0, 0U, 0U, 0U, 0), false);
  c3_tc_u = c3_b_Wdu;
  c3_uc_y = NULL;
  sf_mex_assign(&c3_uc_y, sf_mex_create("y", &c3_tc_u, 0, 0U, 0U, 0U, 0), false);
  c3_uc_u = c3_b_Jm;
  c3_vc_y = NULL;
  sf_mex_assign(&c3_vc_y, sf_mex_create("y", &c3_uc_u, 0, 0U, 0U, 0U, 0), false);
  c3_vc_u = c3_b_SuJm;
  c3_wc_y = NULL;
  sf_mex_assign(&c3_wc_y, sf_mex_create("y", &c3_vc_u, 0, 0U, 0U, 0U, 0), false);
  c3_wc_u = c3_b_Su1;
  c3_xc_y = NULL;
  sf_mex_assign(&c3_xc_y, sf_mex_create("y", &c3_wc_u, 0, 0U, 0U, 0U, 0), false);
  c3_xc_u = c3_b_Sx;
  c3_yc_y = NULL;
  sf_mex_assign(&c3_yc_y, sf_mex_create("y", &c3_xc_u, 0, 0U, 0U, 0U, 0), false);
  c3_yc_u = c3_b_Hv;
  c3_ad_y = NULL;
  sf_mex_assign(&c3_ad_y, sf_mex_create("y", &c3_yc_u, 0, 0U, 0U, 0U, 0), false);
  c3_ad_u = c3_b_Wu;
  c3_bd_y = NULL;
  sf_mex_assign(&c3_bd_y, sf_mex_create("y", &c3_ad_u, 0, 0U, 0U, 0U, 0), false);
  for (c3_i198 = 0; c3_i198 < 500; c3_i198++) {
    c3_bd_u[c3_i198] = c3_d_I1[c3_i198];
  }

  c3_cd_y = NULL;
  sf_mex_assign(&c3_cd_y, sf_mex_create("y", c3_bd_u, 0, 0U, 1U, 0U, 2, 100, 5),
                false);
  c3_cd_u = c3_isAdaptive;
  c3_dd_y = NULL;
  sf_mex_assign(&c3_dd_y, sf_mex_create("y", &c3_cd_u, 11, 0U, 0U, 0U, 0), false);
  for (c3_i199 = 0; c3_i199 < 169; c3_i199++) {
    c3_dd_u[c3_i199] = c3_d_A[c3_i199];
  }

  c3_ed_y = NULL;
  sf_mex_assign(&c3_ed_y, sf_mex_create("y", c3_dd_u, 0, 0U, 1U, 0U, 2, 13, 13),
                false);
  for (c3_i200 = 0; c3_i200 < 65; c3_i200++) {
    c3_ed_u[c3_i200] = c3_d_Bu[c3_i200];
  }

  c3_fd_y = NULL;
  sf_mex_assign(&c3_fd_y, sf_mex_create("y", c3_ed_u, 0, 0U, 1U, 0U, 2, 13, 5),
                false);
  for (c3_i201 = 0; c3_i201 < 13; c3_i201++) {
    c3_fd_u[c3_i201] = 0.0;
  }

  c3_gd_y = NULL;
  sf_mex_assign(&c3_gd_y, sf_mex_create("y", c3_fd_u, 0, 0U, 1U, 0U, 1, 13),
                false);
  for (c3_i202 = 0; c3_i202 < 78; c3_i202++) {
    c3_gd_u[c3_i202] = c3_d_C[c3_i202];
  }

  c3_hd_y = NULL;
  sf_mex_assign(&c3_hd_y, sf_mex_create("y", c3_gd_u, 0, 0U, 1U, 0U, 2, 6, 13),
                false);
  for (c3_i203 = 0; c3_i203 < 6; c3_i203++) {
    c3_hd_u[c3_i203] = 0.0;
  }

  c3_id_y = NULL;
  sf_mex_assign(&c3_id_y, sf_mex_create("y", c3_hd_u, 0, 0U, 1U, 0U, 1, 6),
                false);
  for (c3_i204 = 0; c3_i204 < 195; c3_i204++) {
    c3_id_u[c3_i204] = c3_d_Mrows[c3_i204];
  }

  c3_jd_y = NULL;
  sf_mex_assign(&c3_jd_y, sf_mex_create("y", c3_id_u, 0, 0U, 1U, 0U, 1, 195),
                false);
  c3_jd_u = c3_b_nCC;
  c3_kd_y = NULL;
  sf_mex_assign(&c3_kd_y, sf_mex_create("y", &c3_jd_u, 0, 0U, 0U, 0U, 0), false);
  for (c3_i205 = 0; c3_i205 < 5; c3_i205++) {
    c3_kd_u[c3_i205] = 0.0;
  }

  c3_ld_y = NULL;
  sf_mex_assign(&c3_ld_y, sf_mex_create("y", c3_kd_u, 0, 0U, 1U, 0U, 2, 1, 5),
                false);
  for (c3_i206 = 0; c3_i206 < 6; c3_i206++) {
    c3_ld_u[c3_i206] = 0.0;
  }

  c3_md_y = NULL;
  sf_mex_assign(&c3_md_y, sf_mex_create("y", c3_ld_u, 0, 0U, 1U, 0U, 2, 1, 6),
                false);
  c3_md_u = c3_b_Scc;
  c3_nd_y = NULL;
  sf_mex_assign(&c3_nd_y, sf_mex_create("y", &c3_md_u, 0, 0U, 0U, 0U, 0), false);
  c3_nd_u = c3_b_Gcc;
  c3_od_y = NULL;
  sf_mex_assign(&c3_od_y, sf_mex_create("y", &c3_nd_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "mpcblock_optimizer_double_mex",
                    5U, 75U, 14, c3_p_y, 14, c3_q_y, 14, c3_r_y, 14, c3_s_y, 14,
                    c3_t_y, 14, c3_u_y, 14, c3_v_y, 14, c3_w_y, 14, c3_x_y, 14,
                    c3_y_y, 14, c3_ab_y, 14, c3_bb_y, 14, c3_cb_y, 14, c3_db_y,
                    14, c3_eb_y, 14, c3_fb_y, 14, c3_gb_y, 14, c3_hb_y, 14,
                    c3_ib_y, 14, c3_jb_y, 14, c3_kb_y, 14, c3_lb_y, 14, c3_mb_y,
                    14, c3_nb_y, 14, c3_ob_y, 14, c3_pb_y, 14, c3_qb_y, 14,
                    c3_rb_y, 14, c3_sb_y, 14, c3_tb_y, 14, c3_ub_y, 14, c3_vb_y,
                    14, c3_wb_y, 14, c3_xb_y, 14, c3_yb_y, 14, c3_ac_y, 14,
                    c3_bc_y, 14, c3_cc_y, 14, c3_dc_y, 14, c3_ec_y, 14, c3_fc_y,
                    14, c3_gc_y, 14, c3_hc_y, 14, c3_ic_y, 14, c3_jc_y, 14,
                    c3_kc_y, 14, c3_lc_y, 14, c3_mc_y, 14, c3_nc_y, 14, c3_oc_y,
                    14, c3_pc_y, 14, c3_qc_y, 14, c3_rc_y, 14, c3_sc_y, 14,
                    c3_tc_y, 14, c3_uc_y, 14, c3_vc_y, 14, c3_wc_y, 14, c3_xc_y,
                    14, c3_yc_y, 14, c3_ad_y, 14, c3_bd_y, 14, c3_cd_y, 14,
                    c3_dd_y, 14, c3_ed_y, 14, c3_fd_y, 14, c3_gd_y, 14, c3_hd_y,
                    14, c3_id_y, 14, c3_jd_y, 14, c3_kd_y, 14, c3_ld_y, 14,
                    c3_md_y, 14, c3_nd_y, 14, c3_od_y, &c3_od_u, &c3_c_cost,
                    &c3_c_useq, &c3_c_status, &c3_c_iAout);
  c3_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_od_u), "u", c3_dv38);
  for (c3_i207 = 0; c3_i207 < 5; c3_i207++) {
    c3_e_u[c3_i207] = c3_dv38[c3_i207];
  }

  c3_b_cost = c3_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_cost), "cost");
  c3_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_useq), "useq", c3_dv39);
  for (c3_i208 = 0; c3_i208 < 100; c3_i208++) {
    c3_b_useq[c3_i208] = c3_dv39[c3_i208];
  }

  c3_b_status = c3_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_status),
    "status");
  c3_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_iAout), "iAout", c3_bv1);
  for (c3_i209 = 0; c3_i209 < 221; c3_i209++) {
    c3_b_iAout[c3_i209] = c3_bv1[c3_i209];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 134U);
  CV_EML_IF(0, 1, 8, CV_RELATIONAL_EVAL(4U, 0U, 3, c3_b_CustomEstimation, c3_ONE,
             -1, 0U, c3_b_CustomEstimation == c3_ONE));
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 138U);
  for (c3_i210 = 0; c3_i210 < 13; c3_i210++) {
    c3_b[c3_i210] = c3_b_xk[c3_i210];
  }

  c3_d_eml_scalar_eg(chartInstance);
  c3_d_eml_scalar_eg(chartInstance);
  c3_threshold(chartInstance);
  for (c3_i211 = 0; c3_i211 < 13; c3_i211++) {
    c3_o_y[c3_i211] = 0.0;
    c3_i212 = 0;
    for (c3_i213 = 0; c3_i213 < 13; c3_i213++) {
      c3_o_y[c3_i211] += c3_d_A[c3_i212 + c3_i211] * c3_b[c3_i213];
      c3_i212 += 13;
    }
  }

  for (c3_i214 = 0; c3_i214 < 5; c3_i214++) {
    c3_c_b[c3_i214] = c3_e_u[c3_i214] - c3_d_uoff[c3_i214];
  }

  c3_eml_scalar_eg(chartInstance);
  c3_eml_scalar_eg(chartInstance);
  c3_threshold(chartInstance);
  for (c3_i215 = 0; c3_i215 < 13; c3_i215++) {
    c3_b[c3_i215] = 0.0;
    c3_i216 = 0;
    for (c3_i217 = 0; c3_i217 < 5; c3_i217++) {
      c3_b[c3_i215] += c3_d_Bu[c3_i216 + c3_i215] * c3_c_b[c3_i217];
      c3_i216 += 13;
    }
  }

  c3_d_b = c3_v;
  for (c3_i218 = 0; c3_i218 < 13; c3_i218++) {
    c3_pd_y[c3_i218] = 0.0 * c3_d_b;
  }

  for (c3_i219 = 0; c3_i219 < 6; c3_i219++) {
    c3_m_y[c3_i219] = c3_y_innov[c3_i219];
  }

  c3_c_eml_scalar_eg(chartInstance);
  c3_c_eml_scalar_eg(chartInstance);
  c3_threshold(chartInstance);
  for (c3_i220 = 0; c3_i220 < 13; c3_i220++) {
    c3_qd_y[c3_i220] = 0.0;
    c3_i221 = 0;
    for (c3_i222 = 0; c3_i222 < 6; c3_i222++) {
      c3_qd_y[c3_i220] += c3_d_L[c3_i221 + c3_i220] * c3_m_y[c3_i222];
      c3_i221 += 13;
    }
  }

  for (c3_i223 = 0; c3_i223 < 13; c3_i223++) {
    c3_b_xk1[c3_i223] = ((c3_o_y[c3_i223] + c3_b[c3_i223]) + c3_pd_y[c3_i223]) +
      c3_qd_y[c3_i223];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 140U);
  for (c3_i224 = 0; c3_i224 < 13; c3_i224++) {
    c3_b_xk1[c3_i224];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 142U);
  CV_EML_IF(0, 1, 9, CV_RELATIONAL_EVAL(4U, 0U, 4, c3_b_CustomEstimation, c3_ONE,
             -1, 0U, c3_b_CustomEstimation == c3_ONE));
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 146U);
  for (c3_i225 = 0; c3_i225 < 13; c3_i225++) {
    c3_b_xest[c3_i225];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, -146);
  _SFD_SYMBOL_SCOPE_POP();
  sf_mex_destroy(&c3_od_u);
  sf_mex_destroy(&c3_c_cost);
  sf_mex_destroy(&c3_c_useq);
  sf_mex_destroy(&c3_c_status);
  sf_mex_destroy(&c3_c_iAout);
  sf_mex_destroy(&c3_b_rseq);
  sf_mex_destroy(&c3_b_vseq);
  sf_mex_destroy(&c3_b_v);
  for (c3_i226 = 0; c3_i226 < 13; c3_i226++) {
    (*chartInstance->c3_xk1)[c3_i226] = c3_b_xk1[c3_i226];
  }

  for (c3_i227 = 0; c3_i227 < 5; c3_i227++) {
    (*chartInstance->c3_d_u)[c3_i227] = c3_e_u[c3_i227];
  }

  *chartInstance->c3_cost = c3_b_cost;
  for (c3_i228 = 0; c3_i228 < 100; c3_i228++) {
    (*chartInstance->c3_useq)[c3_i228] = c3_b_useq[c3_i228];
  }

  *chartInstance->c3_status = c3_b_status;
  for (c3_i229 = 0; c3_i229 < 13; c3_i229++) {
    (*chartInstance->c3_xest)[c3_i229] = c3_b_xest[c3_i229];
  }

  for (c3_i230 = 0; c3_i230 < 221; c3_i230++) {
    (*chartInstance->c3_iAout)[c3_i230] = c3_b_iAout[c3_i230];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c3_sfEvent);
}

static void initSimStructsc3_mpclib(SFc3_mpclibInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber, uint32_T c3_instanceNumber)
{
  (void)c3_machineNumber;
  (void)c3_chartNumber;
  (void)c3_instanceNumber;
}

static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i231;
  boolean_T c3_b_inData[221];
  int32_T c3_i232;
  boolean_T c3_e_u[221];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i231 = 0; c3_i231 < 221; c3_i231++) {
    c3_b_inData[c3_i231] = (*(boolean_T (*)[221])c3_inData)[c3_i231];
  }

  for (c3_i232 = 0; c3_i232 < 221; c3_i232++) {
    c3_e_u[c3_i232] = c3_b_inData[c3_i232];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 11, 0U, 1U, 0U, 1, 221), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_iAout;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  boolean_T c3_y[221];
  int32_T c3_i233;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_b_iAout = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_iAout), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_iAout);
  for (c3_i233 = 0; c3_i233 < 221; c3_i233++) {
    (*(boolean_T (*)[221])c3_outData)[c3_i233] = c3_y[c3_i233];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i234;
  real_T c3_b_inData[13];
  int32_T c3_i235;
  real_T c3_e_u[13];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i234 = 0; c3_i234 < 13; c3_i234++) {
    c3_b_inData[c3_i234] = (*(real_T (*)[13])c3_inData)[c3_i234];
  }

  for (c3_i235 = 0; c3_i235 < 13; c3_i235++) {
    c3_e_u[c3_i235] = c3_b_inData[c3_i235];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 1, 13), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance, const
  mxArray *c3_b_xest, const char_T *c3_identifier, real_T c3_y[13])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_xest), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_xest);
}

static void c3_b_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[13])
{
  real_T c3_dv40[13];
  int32_T c3_i236;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv40, 1, 0, 0U, 1, 0U, 1, 13);
  for (c3_i236 = 0; c3_i236 < 13; c3_i236++) {
    c3_y[c3_i236] = c3_dv40[c3_i236];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_xest;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[13];
  int32_T c3_i237;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_b_xest = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_xest), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_xest);
  for (c3_i237 = 0; c3_i237 < 13; c3_i237++) {
    (*(real_T (*)[13])c3_outData)[c3_i237] = c3_y[c3_i237];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_e_u;
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_e_u = *(real_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_v;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_v = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_v), &c3_thisId);
  sf_mex_destroy(&c3_v);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i238;
  int32_T c3_i239;
  int32_T c3_i240;
  real_T c3_b_inData[100];
  int32_T c3_i241;
  int32_T c3_i242;
  int32_T c3_i243;
  real_T c3_e_u[100];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i238 = 0;
  for (c3_i239 = 0; c3_i239 < 5; c3_i239++) {
    for (c3_i240 = 0; c3_i240 < 20; c3_i240++) {
      c3_b_inData[c3_i240 + c3_i238] = (*(real_T (*)[100])c3_inData)[c3_i240 +
        c3_i238];
    }

    c3_i238 += 20;
  }

  c3_i241 = 0;
  for (c3_i242 = 0; c3_i242 < 5; c3_i242++) {
    for (c3_i243 = 0; c3_i243 < 20; c3_i243++) {
      c3_e_u[c3_i243 + c3_i241] = c3_b_inData[c3_i243 + c3_i241];
    }

    c3_i241 += 20;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 2, 20, 5),
                false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_useq;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[100];
  int32_T c3_i244;
  int32_T c3_i245;
  int32_T c3_i246;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_b_useq = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_useq), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_useq);
  c3_i244 = 0;
  for (c3_i245 = 0; c3_i245 < 5; c3_i245++) {
    for (c3_i246 = 0; c3_i246 < 20; c3_i246++) {
      (*(real_T (*)[100])c3_outData)[c3_i246 + c3_i244] = c3_y[c3_i246 + c3_i244];
    }

    c3_i244 += 20;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i247;
  real_T c3_b_inData[5];
  int32_T c3_i248;
  real_T c3_e_u[5];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i247 = 0; c3_i247 < 5; c3_i247++) {
    c3_b_inData[c3_i247] = (*(real_T (*)[5])c3_inData)[c3_i247];
  }

  for (c3_i248 = 0; c3_i248 < 5; c3_i248++) {
    c3_e_u[c3_i248] = c3_b_inData[c3_i248];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 1, 5), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_e_u;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[5];
  int32_T c3_i249;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_e_u = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_e_u), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_e_u);
  for (c3_i249 = 0; c3_i249 < 5; c3_i249++) {
    (*(real_T (*)[5])c3_outData)[c3_i249] = c3_y[c3_i249];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i250;
  real_T c3_b_inData[6];
  int32_T c3_i251;
  real_T c3_e_u[6];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i250 = 0; c3_i250 < 6; c3_i250++) {
    c3_b_inData[c3_i250] = (*(real_T (*)[6])c3_inData)[c3_i250];
  }

  for (c3_i251 = 0; c3_i251 < 6; c3_i251++) {
    c3_e_u[c3_i251] = c3_b_inData[c3_i251];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 1, 6), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_g_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i252;
  int32_T c3_i253;
  int32_T c3_i254;
  real_T c3_b_inData[78];
  int32_T c3_i255;
  int32_T c3_i256;
  int32_T c3_i257;
  real_T c3_e_u[78];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i252 = 0;
  for (c3_i253 = 0; c3_i253 < 6; c3_i253++) {
    for (c3_i254 = 0; c3_i254 < 13; c3_i254++) {
      c3_b_inData[c3_i254 + c3_i252] = (*(real_T (*)[78])c3_inData)[c3_i254 +
        c3_i252];
    }

    c3_i252 += 13;
  }

  c3_i255 = 0;
  for (c3_i256 = 0; c3_i256 < 6; c3_i256++) {
    for (c3_i257 = 0; c3_i257 < 13; c3_i257++) {
      c3_e_u[c3_i257 + c3_i255] = c3_b_inData[c3_i257 + c3_i255];
    }

    c3_i255 += 13;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 2, 13, 6),
                false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_h_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i258;
  real_T c3_b_inData[6];
  int32_T c3_i259;
  real_T c3_e_u[6];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i258 = 0; c3_i258 < 6; c3_i258++) {
    c3_b_inData[c3_i258] = (*(real_T (*)[6])c3_inData)[c3_i258];
  }

  for (c3_i259 = 0; c3_i259 < 6; c3_i259++) {
    c3_e_u[c3_i259] = c3_b_inData[c3_i259];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 2, 1, 6), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_i_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i260;
  real_T c3_b_inData[5];
  int32_T c3_i261;
  real_T c3_e_u[5];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i260 = 0; c3_i260 < 5; c3_i260++) {
    c3_b_inData[c3_i260] = (*(real_T (*)[5])c3_inData)[c3_i260];
  }

  for (c3_i261 = 0; c3_i261 < 5; c3_i261++) {
    c3_e_u[c3_i261] = c3_b_inData[c3_i261];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 2, 1, 5), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_j_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i262;
  real_T c3_b_inData[195];
  int32_T c3_i263;
  real_T c3_e_u[195];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i262 = 0; c3_i262 < 195; c3_i262++) {
    c3_b_inData[c3_i262] = (*(real_T (*)[195])c3_inData)[c3_i262];
  }

  for (c3_i263 = 0; c3_i263 < 195; c3_i263++) {
    c3_e_u[c3_i263] = c3_b_inData[c3_i263];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 1, 195), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_k_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i264;
  int32_T c3_i265;
  int32_T c3_i266;
  real_T c3_b_inData[78];
  int32_T c3_i267;
  int32_T c3_i268;
  int32_T c3_i269;
  real_T c3_e_u[78];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i264 = 0;
  for (c3_i265 = 0; c3_i265 < 13; c3_i265++) {
    for (c3_i266 = 0; c3_i266 < 6; c3_i266++) {
      c3_b_inData[c3_i266 + c3_i264] = (*(real_T (*)[78])c3_inData)[c3_i266 +
        c3_i264];
    }

    c3_i264 += 6;
  }

  c3_i267 = 0;
  for (c3_i268 = 0; c3_i268 < 13; c3_i268++) {
    for (c3_i269 = 0; c3_i269 < 6; c3_i269++) {
      c3_e_u[c3_i269 + c3_i267] = c3_b_inData[c3_i269 + c3_i267];
    }

    c3_i267 += 6;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 2, 6, 13),
                false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_l_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i270;
  int32_T c3_i271;
  int32_T c3_i272;
  real_T c3_b_inData[65];
  int32_T c3_i273;
  int32_T c3_i274;
  int32_T c3_i275;
  real_T c3_e_u[65];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i270 = 0;
  for (c3_i271 = 0; c3_i271 < 5; c3_i271++) {
    for (c3_i272 = 0; c3_i272 < 13; c3_i272++) {
      c3_b_inData[c3_i272 + c3_i270] = (*(real_T (*)[65])c3_inData)[c3_i272 +
        c3_i270];
    }

    c3_i270 += 13;
  }

  c3_i273 = 0;
  for (c3_i274 = 0; c3_i274 < 5; c3_i274++) {
    for (c3_i275 = 0; c3_i275 < 13; c3_i275++) {
      c3_e_u[c3_i275 + c3_i273] = c3_b_inData[c3_i275 + c3_i273];
    }

    c3_i273 += 13;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 2, 13, 5),
                false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_m_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i276;
  int32_T c3_i277;
  int32_T c3_i278;
  real_T c3_b_inData[169];
  int32_T c3_i279;
  int32_T c3_i280;
  int32_T c3_i281;
  real_T c3_e_u[169];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i276 = 0;
  for (c3_i277 = 0; c3_i277 < 13; c3_i277++) {
    for (c3_i278 = 0; c3_i278 < 13; c3_i278++) {
      c3_b_inData[c3_i278 + c3_i276] = (*(real_T (*)[169])c3_inData)[c3_i278 +
        c3_i276];
    }

    c3_i276 += 13;
  }

  c3_i279 = 0;
  for (c3_i280 = 0; c3_i280 < 13; c3_i280++) {
    for (c3_i281 = 0; c3_i281 < 13; c3_i281++) {
      c3_e_u[c3_i281 + c3_i279] = c3_b_inData[c3_i281 + c3_i279];
    }

    c3_i279 += 13;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 2, 13, 13),
                false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_n_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i282;
  int32_T c3_i283;
  int32_T c3_i284;
  real_T c3_b_inData[500];
  int32_T c3_i285;
  int32_T c3_i286;
  int32_T c3_i287;
  real_T c3_e_u[500];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i282 = 0;
  for (c3_i283 = 0; c3_i283 < 5; c3_i283++) {
    for (c3_i284 = 0; c3_i284 < 100; c3_i284++) {
      c3_b_inData[c3_i284 + c3_i282] = (*(real_T (*)[500])c3_inData)[c3_i284 +
        c3_i282];
    }

    c3_i282 += 100;
  }

  c3_i285 = 0;
  for (c3_i286 = 0; c3_i286 < 5; c3_i286++) {
    for (c3_i287 = 0; c3_i287 < 100; c3_i287++) {
      c3_e_u[c3_i287 + c3_i285] = c3_b_inData[c3_i287 + c3_i285];
    }

    c3_i285 += 100;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 2, 100, 5),
                false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_o_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i288;
  int32_T c3_i289;
  int32_T c3_i290;
  real_T c3_b_inData[5070];
  int32_T c3_i291;
  int32_T c3_i292;
  int32_T c3_i293;
  real_T c3_e_u[5070];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i288 = 0;
  for (c3_i289 = 0; c3_i289 < 26; c3_i289++) {
    for (c3_i290 = 0; c3_i290 < 195; c3_i290++) {
      c3_b_inData[c3_i290 + c3_i288] = (*(real_T (*)[5070])c3_inData)[c3_i290 +
        c3_i288];
    }

    c3_i288 += 195;
  }

  c3_i291 = 0;
  for (c3_i292 = 0; c3_i292 < 26; c3_i292++) {
    for (c3_i293 = 0; c3_i293 < 195; c3_i293++) {
      c3_e_u[c3_i293 + c3_i291] = c3_b_inData[c3_i293 + c3_i291];
    }

    c3_i291 += 195;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 2, 195, 26),
                false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_p_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i294;
  int32_T c3_i295;
  int32_T c3_i296;
  real_T c3_b_inData[676];
  int32_T c3_i297;
  int32_T c3_i298;
  int32_T c3_i299;
  real_T c3_e_u[676];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i294 = 0;
  for (c3_i295 = 0; c3_i295 < 26; c3_i295++) {
    for (c3_i296 = 0; c3_i296 < 26; c3_i296++) {
      c3_b_inData[c3_i296 + c3_i294] = (*(real_T (*)[676])c3_inData)[c3_i296 +
        c3_i294];
    }

    c3_i294 += 26;
  }

  c3_i297 = 0;
  for (c3_i298 = 0; c3_i298 < 26; c3_i298++) {
    for (c3_i299 = 0; c3_i299 < 26; c3_i299++) {
      c3_e_u[c3_i299 + c3_i297] = c3_b_inData[c3_i299 + c3_i297];
    }

    c3_i297 += 26;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 2, 26, 26),
                false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_q_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  boolean_T c3_e_u;
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_e_u = *(boolean_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_e_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_r_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i300;
  real_T c3_b_inData[100];
  int32_T c3_i301;
  real_T c3_e_u[100];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i300 = 0; c3_i300 < 100; c3_i300++) {
    c3_b_inData[c3_i300] = (*(real_T (*)[100])c3_inData)[c3_i300];
  }

  for (c3_i301 = 0; c3_i301 < 100; c3_i301++) {
    c3_e_u[c3_i301] = c3_b_inData[c3_i301];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 1, 100), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_s_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i302;
  real_T c3_b_inData[26];
  int32_T c3_i303;
  real_T c3_e_u[26];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i302 = 0; c3_i302 < 26; c3_i302++) {
    c3_b_inData[c3_i302] = (*(real_T (*)[26])c3_inData)[c3_i302];
  }

  for (c3_i303 = 0; c3_i303 < 26; c3_i303++) {
    c3_e_u[c3_i303] = c3_b_inData[c3_i303];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 1, 26), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_t_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i304;
  int32_T c3_i305;
  int32_T c3_i306;
  real_T c3_b_inData[4095];
  int32_T c3_i307;
  int32_T c3_i308;
  int32_T c3_i309;
  real_T c3_e_u[4095];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i304 = 0;
  for (c3_i305 = 0; c3_i305 < 21; c3_i305++) {
    for (c3_i306 = 0; c3_i306 < 195; c3_i306++) {
      c3_b_inData[c3_i306 + c3_i304] = (*(real_T (*)[4095])c3_inData)[c3_i306 +
        c3_i304];
    }

    c3_i304 += 195;
  }

  c3_i307 = 0;
  for (c3_i308 = 0; c3_i308 < 21; c3_i308++) {
    for (c3_i309 = 0; c3_i309 < 195; c3_i309++) {
      c3_e_u[c3_i309 + c3_i307] = c3_b_inData[c3_i309 + c3_i307];
    }

    c3_i307 += 195;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 2, 195, 21),
                false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_u_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i310;
  int32_T c3_i311;
  int32_T c3_i312;
  real_T c3_b_inData[975];
  int32_T c3_i313;
  int32_T c3_i314;
  int32_T c3_i315;
  real_T c3_e_u[975];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i310 = 0;
  for (c3_i311 = 0; c3_i311 < 5; c3_i311++) {
    for (c3_i312 = 0; c3_i312 < 195; c3_i312++) {
      c3_b_inData[c3_i312 + c3_i310] = (*(real_T (*)[975])c3_inData)[c3_i312 +
        c3_i310];
    }

    c3_i310 += 195;
  }

  c3_i313 = 0;
  for (c3_i314 = 0; c3_i314 < 5; c3_i314++) {
    for (c3_i315 = 0; c3_i315 < 195; c3_i315++) {
      c3_e_u[c3_i315 + c3_i313] = c3_b_inData[c3_i315 + c3_i313];
    }

    c3_i313 += 195;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 2, 195, 5),
                false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_v_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i316;
  int32_T c3_i317;
  int32_T c3_i318;
  real_T c3_b_inData[2535];
  int32_T c3_i319;
  int32_T c3_i320;
  int32_T c3_i321;
  real_T c3_e_u[2535];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i316 = 0;
  for (c3_i317 = 0; c3_i317 < 13; c3_i317++) {
    for (c3_i318 = 0; c3_i318 < 195; c3_i318++) {
      c3_b_inData[c3_i318 + c3_i316] = (*(real_T (*)[2535])c3_inData)[c3_i318 +
        c3_i316];
    }

    c3_i316 += 195;
  }

  c3_i319 = 0;
  for (c3_i320 = 0; c3_i320 < 13; c3_i320++) {
    for (c3_i321 = 0; c3_i321 < 195; c3_i321++) {
      c3_e_u[c3_i321 + c3_i319] = c3_b_inData[c3_i321 + c3_i319];
    }

    c3_i319 += 195;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 2, 195, 13),
                false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_w_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i322;
  int32_T c3_i323;
  int32_T c3_i324;
  real_T c3_b_inData[525];
  int32_T c3_i325;
  int32_T c3_i326;
  int32_T c3_i327;
  real_T c3_e_u[525];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i322 = 0;
  for (c3_i323 = 0; c3_i323 < 25; c3_i323++) {
    for (c3_i324 = 0; c3_i324 < 21; c3_i324++) {
      c3_b_inData[c3_i324 + c3_i322] = (*(real_T (*)[525])c3_inData)[c3_i324 +
        c3_i322];
    }

    c3_i322 += 21;
  }

  c3_i325 = 0;
  for (c3_i326 = 0; c3_i326 < 25; c3_i326++) {
    for (c3_i327 = 0; c3_i327 < 21; c3_i327++) {
      c3_e_u[c3_i327 + c3_i325] = c3_b_inData[c3_i327 + c3_i325];
    }

    c3_i325 += 21;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 2, 21, 25),
                false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_x_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i328;
  int32_T c3_i329;
  int32_T c3_i330;
  real_T c3_b_inData[3000];
  int32_T c3_i331;
  int32_T c3_i332;
  int32_T c3_i333;
  real_T c3_e_u[3000];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i328 = 0;
  for (c3_i329 = 0; c3_i329 < 25; c3_i329++) {
    for (c3_i330 = 0; c3_i330 < 120; c3_i330++) {
      c3_b_inData[c3_i330 + c3_i328] = (*(real_T (*)[3000])c3_inData)[c3_i330 +
        c3_i328];
    }

    c3_i328 += 120;
  }

  c3_i331 = 0;
  for (c3_i332 = 0; c3_i332 < 25; c3_i332++) {
    for (c3_i333 = 0; c3_i333 < 120; c3_i333++) {
      c3_e_u[c3_i333 + c3_i331] = c3_b_inData[c3_i333 + c3_i331];
    }

    c3_i331 += 120;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 2, 120, 25),
                false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_y_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i334;
  int32_T c3_i335;
  int32_T c3_i336;
  real_T c3_b_inData[2500];
  int32_T c3_i337;
  int32_T c3_i338;
  int32_T c3_i339;
  real_T c3_e_u[2500];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i334 = 0;
  for (c3_i335 = 0; c3_i335 < 25; c3_i335++) {
    for (c3_i336 = 0; c3_i336 < 100; c3_i336++) {
      c3_b_inData[c3_i336 + c3_i334] = (*(real_T (*)[2500])c3_inData)[c3_i336 +
        c3_i334];
    }

    c3_i334 += 100;
  }

  c3_i337 = 0;
  for (c3_i338 = 0; c3_i338 < 25; c3_i338++) {
    for (c3_i339 = 0; c3_i339 < 100; c3_i339++) {
      c3_e_u[c3_i339 + c3_i337] = c3_b_inData[c3_i339 + c3_i337];
    }

    c3_i337 += 100;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 2, 100, 25),
                false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_ab_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i340;
  int32_T c3_i341;
  int32_T c3_i342;
  real_T c3_b_inData[125];
  int32_T c3_i343;
  int32_T c3_i344;
  int32_T c3_i345;
  real_T c3_e_u[125];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i340 = 0;
  for (c3_i341 = 0; c3_i341 < 25; c3_i341++) {
    for (c3_i342 = 0; c3_i342 < 5; c3_i342++) {
      c3_b_inData[c3_i342 + c3_i340] = (*(real_T (*)[125])c3_inData)[c3_i342 +
        c3_i340];
    }

    c3_i340 += 5;
  }

  c3_i343 = 0;
  for (c3_i344 = 0; c3_i344 < 25; c3_i344++) {
    for (c3_i345 = 0; c3_i345 < 5; c3_i345++) {
      c3_e_u[c3_i345 + c3_i343] = c3_b_inData[c3_i345 + c3_i343];
    }

    c3_i343 += 5;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 2, 5, 25),
                false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_bb_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i346;
  int32_T c3_i347;
  int32_T c3_i348;
  real_T c3_b_inData[325];
  int32_T c3_i349;
  int32_T c3_i350;
  int32_T c3_i351;
  real_T c3_e_u[325];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i346 = 0;
  for (c3_i347 = 0; c3_i347 < 25; c3_i347++) {
    for (c3_i348 = 0; c3_i348 < 13; c3_i348++) {
      c3_b_inData[c3_i348 + c3_i346] = (*(real_T (*)[325])c3_inData)[c3_i348 +
        c3_i346];
    }

    c3_i346 += 13;
  }

  c3_i349 = 0;
  for (c3_i350 = 0; c3_i350 < 25; c3_i350++) {
    for (c3_i351 = 0; c3_i351 < 13; c3_i351++) {
      c3_e_u[c3_i351 + c3_i349] = c3_b_inData[c3_i351 + c3_i349];
    }

    c3_i349 += 13;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 2, 13, 25),
                false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_c_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[100])
{
  real_T c3_dv41[100];
  int32_T c3_i352;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv41, 1, 0, 0U, 1, 0U, 1,
                100);
  for (c3_i352 = 0; c3_i352 < 100; c3_i352++) {
    c3_y[c3_i352] = c3_dv41[c3_i352];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_utargetValue;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[100];
  int32_T c3_i353;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_utargetValue = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_utargetValue), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_utargetValue);
  for (c3_i353 = 0; c3_i353 < 100; c3_i353++) {
    (*(real_T (*)[100])c3_outData)[c3_i353] = c3_y[c3_i353];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_d_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[6])
{
  real_T c3_dv42[6];
  int32_T c3_i354;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv42, 1, 0, 0U, 1, 0U, 1, 6);
  for (c3_i354 = 0; c3_i354 < 6; c3_i354++) {
    c3_y[c3_i354] = c3_dv42[c3_i354];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_y_innov;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[6];
  int32_T c3_i355;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_y_innov = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_y_innov), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_y_innov);
  for (c3_i355 = 0; c3_i355 < 6; c3_i355++) {
    (*(real_T (*)[6])c3_outData)[c3_i355] = c3_y[c3_i355];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_cb_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i356;
  real_T c3_b_inData[21];
  int32_T c3_i357;
  real_T c3_e_u[21];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i356 = 0; c3_i356 < 21; c3_i356++) {
    c3_b_inData[c3_i356] = (*(real_T (*)[21])c3_inData)[c3_i356];
  }

  for (c3_i357 = 0; c3_i357 < 21; c3_i357++) {
    c3_e_u[c3_i357] = c3_b_inData[c3_i357];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 1, 21), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_vseq;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[21];
  int32_T c3_i358;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_vseq = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_vseq), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_vseq);
  for (c3_i358 = 0; c3_i358 < 21; c3_i358++) {
    (*(real_T (*)[21])c3_outData)[c3_i358] = c3_y[c3_i358];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_db_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i359;
  real_T c3_b_inData[120];
  int32_T c3_i360;
  real_T c3_e_u[120];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i359 = 0; c3_i359 < 120; c3_i359++) {
    c3_b_inData[c3_i359] = (*(real_T (*)[120])c3_inData)[c3_i359];
  }

  for (c3_i360 = 0; c3_i360 < 120; c3_i360++) {
    c3_e_u[c3_i360] = c3_b_inData[c3_i360];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 1, 120), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_rseq;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[120];
  int32_T c3_i361;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_rseq = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_rseq), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_rseq);
  for (c3_i361 = 0; c3_i361 < 120; c3_i361++) {
    (*(real_T (*)[120])c3_outData)[c3_i361] = c3_y[c3_i361];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static boolean_T c3_e_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId)
{
  boolean_T c3_y;
  boolean_T c3_b0;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), &c3_b0, 1, 11, 0U, 0, 0U, 0);
  c3_y = c3_b0;
  sf_mex_destroy(&c3_e_u);
  return c3_y;
}

static void c3_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_isAdaptive;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  boolean_T c3_y;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_isAdaptive = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_isAdaptive),
    &c3_thisId);
  sf_mex_destroy(&c3_isAdaptive);
  *(boolean_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

const mxArray *sf_c3_mpclib_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo = NULL;
  c3_nameCaptureInfo = NULL;
  sf_mex_assign(&c3_nameCaptureInfo, sf_mex_createstruct("structure", 2, 13, 1),
                false);
  c3_info_helper(&c3_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c3_nameCaptureInfo);
  return c3_nameCaptureInfo;
}

static void c3_info_helper(const mxArray **c3_info)
{
  const mxArray *c3_rhs0 = NULL;
  const mxArray *c3_lhs0 = NULL;
  const mxArray *c3_rhs1 = NULL;
  const mxArray *c3_lhs1 = NULL;
  const mxArray *c3_rhs2 = NULL;
  const mxArray *c3_lhs2 = NULL;
  const mxArray *c3_rhs3 = NULL;
  const mxArray *c3_lhs3 = NULL;
  const mxArray *c3_rhs4 = NULL;
  const mxArray *c3_lhs4 = NULL;
  const mxArray *c3_rhs5 = NULL;
  const mxArray *c3_lhs5 = NULL;
  const mxArray *c3_rhs6 = NULL;
  const mxArray *c3_lhs6 = NULL;
  const mxArray *c3_rhs7 = NULL;
  const mxArray *c3_lhs7 = NULL;
  const mxArray *c3_rhs8 = NULL;
  const mxArray *c3_lhs8 = NULL;
  const mxArray *c3_rhs9 = NULL;
  const mxArray *c3_lhs9 = NULL;
  const mxArray *c3_rhs10 = NULL;
  const mxArray *c3_lhs10 = NULL;
  const mxArray *c3_rhs11 = NULL;
  const mxArray *c3_lhs11 = NULL;
  const mxArray *c3_rhs12 = NULL;
  const mxArray *c3_lhs12 = NULL;
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_mtimes_helper"), "name",
                  "name", 0);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "resolved", "resolved", 0);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1383852094U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c3_rhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs0, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m!common_checks"),
                  "context", "context", 1);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 1);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 1);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1395906656U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c3_rhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs1, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 2);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 2);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1323145378U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c3_rhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs2, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 3);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 3);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 3);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1375959088U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c3_rhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs3, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "context",
                  "context", 4);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 4);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 4);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c3_rhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs4, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/eml_mtimes_helper.m"),
                  "context", "context", 5);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_xgemm"), "name", "name", 5);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1375959090U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c3_rhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs5, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 6);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.blas.inline"),
                  "name", "name", 6);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/inline.p"),
                  "resolved", "resolved", 6);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c3_rhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs6, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.blas.xgemm"),
                  "name", "name", 7);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c3_rhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs7, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 8);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "coder.internal.blas.use_refblas"), "name", "name", 8);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/use_refblas.p"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c3_rhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs8, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p!below_threshold"),
                  "context", "context", 9);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.blas.threshold"),
                  "name", "name", 9);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "resolved", "resolved", 9);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c3_rhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs9, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/threshold.p"),
                  "context", "context", 10);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("eml_switch_helper"), "name",
                  "name", 10);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_switch_helper.m"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1393305658U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c3_rhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs10, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 11);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.scalarEg"),
                  "name", "name", 11);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/scalarEg.p"),
                  "resolved", "resolved", 11);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1410786170U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c3_rhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs11, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+blas/xgemm.p"),
                  "context", "context", 12);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("coder.internal.refblas.xgemm"),
                  "name", "name", 12);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c3_info, c3_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/coder/coder/+coder/+internal/+refblas/xgemm.p"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(1410786172U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c3_info, c3_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c3_rhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_assign(&c3_lhs12, sf_mex_createcellmatrix(0, 1), false);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c3_info, sf_mex_duplicatearraysafe(&c3_lhs12), "lhs", "lhs",
                  12);
  sf_mex_destroy(&c3_rhs0);
  sf_mex_destroy(&c3_lhs0);
  sf_mex_destroy(&c3_rhs1);
  sf_mex_destroy(&c3_lhs1);
  sf_mex_destroy(&c3_rhs2);
  sf_mex_destroy(&c3_lhs2);
  sf_mex_destroy(&c3_rhs3);
  sf_mex_destroy(&c3_lhs3);
  sf_mex_destroy(&c3_rhs4);
  sf_mex_destroy(&c3_lhs4);
  sf_mex_destroy(&c3_rhs5);
  sf_mex_destroy(&c3_lhs5);
  sf_mex_destroy(&c3_rhs6);
  sf_mex_destroy(&c3_lhs6);
  sf_mex_destroy(&c3_rhs7);
  sf_mex_destroy(&c3_lhs7);
  sf_mex_destroy(&c3_rhs8);
  sf_mex_destroy(&c3_lhs8);
  sf_mex_destroy(&c3_rhs9);
  sf_mex_destroy(&c3_lhs9);
  sf_mex_destroy(&c3_rhs10);
  sf_mex_destroy(&c3_lhs10);
  sf_mex_destroy(&c3_rhs11);
  sf_mex_destroy(&c3_lhs11);
  sf_mex_destroy(&c3_rhs12);
  sf_mex_destroy(&c3_lhs12);
}

static const mxArray *c3_emlrt_marshallOut(const char * c3_e_u)
{
  const mxArray *c3_y = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_e_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c3_e_u)), false);
  return c3_y;
}

static const mxArray *c3_b_emlrt_marshallOut(const uint32_T c3_e_u)
{
  const mxArray *c3_y = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_e_u, 7, 0U, 0U, 0U, 0), false);
  return c3_y;
}

static void c3_eml_scalar_eg(SFc3_mpclibInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c3_threshold(SFc3_mpclibInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c3_b_eml_scalar_eg(SFc3_mpclibInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c3_c_eml_scalar_eg(SFc3_mpclibInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c3_d_eml_scalar_eg(SFc3_mpclibInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c3_f_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_rseq, const char_T *c3_identifier, real_T c3_y[120])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_rseq), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_rseq);
}

static void c3_g_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[120])
{
  real_T c3_dv43[120];
  int32_T c3_i362;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv43, 1, 0, 0U, 1, 0U, 1,
                120);
  for (c3_i362 = 0; c3_i362 < 120; c3_i362++) {
    c3_y[c3_i362] = c3_dv43[c3_i362];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_h_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_vseq, const char_T *c3_identifier, real_T c3_y[21])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_vseq), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_vseq);
}

static void c3_i_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[21])
{
  real_T c3_dv44[21];
  int32_T c3_i363;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv44, 1, 0, 0U, 1, 0U, 1, 21);
  for (c3_i363 = 0; c3_i363 < 21; c3_i363++) {
    c3_y[c3_i363] = c3_dv44[c3_i363];
  }

  sf_mex_destroy(&c3_e_u);
}

static real_T c3_j_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_v, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_v), &c3_thisId);
  sf_mex_destroy(&c3_v);
  return c3_y;
}

static real_T c3_k_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d42;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), &c3_d42, 1, 0, 0U, 0, 0U, 0);
  c3_y = c3_d42;
  sf_mex_destroy(&c3_e_u);
  return c3_y;
}

static void c3_l_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const char_T *c3_identifier, real_T c3_y[5])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_e_u), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_e_u);
}

static void c3_m_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[5])
{
  real_T c3_dv45[5];
  int32_T c3_i364;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv45, 1, 0, 0U, 1, 0U, 1, 5);
  for (c3_i364 = 0; c3_i364 < 5; c3_i364++) {
    c3_y[c3_i364] = c3_dv45[c3_i364];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_n_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_b_useq, const char_T *c3_identifier, real_T c3_y[100])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_useq), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_useq);
}

static void c3_o_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[100])
{
  real_T c3_dv46[100];
  int32_T c3_i365;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv46, 1, 0, 0U, 1, 0U, 2, 20,
                5);
  for (c3_i365 = 0; c3_i365 < 100; c3_i365++) {
    c3_y[c3_i365] = c3_dv46[c3_i365];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_p_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_b_iAout, const char_T *c3_identifier, boolean_T c3_y[221])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_iAout), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_iAout);
}

static void c3_q_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, boolean_T c3_y
  [221])
{
  boolean_T c3_bv2[221];
  int32_T c3_i366;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_bv2, 1, 11, 0U, 1, 0U, 1,
                221);
  for (c3_i366 = 0; c3_i366 < 221; c3_i366++) {
    c3_y[c3_i366] = c3_bv2[c3_i366];
  }

  sf_mex_destroy(&c3_e_u);
}

static const mxArray *c3_eb_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_e_u;
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_e_u = *(int32_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_e_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static int32_T c3_r_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId)
{
  int32_T c3_y;
  int32_T c3_i367;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), &c3_i367, 1, 6, 0U, 0, 0U, 0);
  c3_y = c3_i367;
  sf_mex_destroy(&c3_e_u);
  return c3_y;
}

static void c3_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_sfEvent;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  int32_T c3_y;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_b_sfEvent = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_r_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_sfEvent),
    &c3_thisId);
  sf_mex_destroy(&c3_b_sfEvent);
  *(int32_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_s_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[676])
{
  real_T c3_dv47[676];
  int32_T c3_i368;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv47, 1, 0, 0U, 1, 0U, 2, 26,
                26);
  for (c3_i368 = 0; c3_i368 < 676; c3_i368++) {
    c3_y[c3_i368] = c3_dv47[c3_i368];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Hinv;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[676];
  int32_T c3_i369;
  int32_T c3_i370;
  int32_T c3_i371;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Hinv = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_s_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Hinv), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Hinv);
  c3_i369 = 0;
  for (c3_i370 = 0; c3_i370 < 26; c3_i370++) {
    for (c3_i371 = 0; c3_i371 < 26; c3_i371++) {
      (*(real_T (*)[676])c3_outData)[c3_i371 + c3_i369] = c3_y[c3_i371 + c3_i369];
    }

    c3_i369 += 26;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_t_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[325])
{
  real_T c3_dv48[325];
  int32_T c3_i372;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv48, 1, 0, 0U, 1, 0U, 2, 13,
                25);
  for (c3_i372 = 0; c3_i372 < 325; c3_i372++) {
    c3_y[c3_i372] = c3_dv48[c3_i372];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Kx;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[325];
  int32_T c3_i373;
  int32_T c3_i374;
  int32_T c3_i375;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Kx = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_t_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Kx), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Kx);
  c3_i373 = 0;
  for (c3_i374 = 0; c3_i374 < 25; c3_i374++) {
    for (c3_i375 = 0; c3_i375 < 13; c3_i375++) {
      (*(real_T (*)[325])c3_outData)[c3_i375 + c3_i373] = c3_y[c3_i375 + c3_i373];
    }

    c3_i373 += 13;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_u_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[125])
{
  real_T c3_dv49[125];
  int32_T c3_i376;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv49, 1, 0, 0U, 1, 0U, 2, 5,
                25);
  for (c3_i376 = 0; c3_i376 < 125; c3_i376++) {
    c3_y[c3_i376] = c3_dv49[c3_i376];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Ku1;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[125];
  int32_T c3_i377;
  int32_T c3_i378;
  int32_T c3_i379;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Ku1 = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_u_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Ku1), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Ku1);
  c3_i377 = 0;
  for (c3_i378 = 0; c3_i378 < 25; c3_i378++) {
    for (c3_i379 = 0; c3_i379 < 5; c3_i379++) {
      (*(real_T (*)[125])c3_outData)[c3_i379 + c3_i377] = c3_y[c3_i379 + c3_i377];
    }

    c3_i377 += 5;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_v_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[2500])
{
  real_T c3_dv50[2500];
  int32_T c3_i380;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv50, 1, 0, 0U, 1, 0U, 2,
                100, 25);
  for (c3_i380 = 0; c3_i380 < 2500; c3_i380++) {
    c3_y[c3_i380] = c3_dv50[c3_i380];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_o_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Kut;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[2500];
  int32_T c3_i381;
  int32_T c3_i382;
  int32_T c3_i383;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Kut = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_v_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Kut), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Kut);
  c3_i381 = 0;
  for (c3_i382 = 0; c3_i382 < 25; c3_i382++) {
    for (c3_i383 = 0; c3_i383 < 100; c3_i383++) {
      (*(real_T (*)[2500])c3_outData)[c3_i383 + c3_i381] = c3_y[c3_i383 +
        c3_i381];
    }

    c3_i381 += 100;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_w_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[3000])
{
  real_T c3_dv51[3000];
  int32_T c3_i384;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv51, 1, 0, 0U, 1, 0U, 2,
                120, 25);
  for (c3_i384 = 0; c3_i384 < 3000; c3_i384++) {
    c3_y[c3_i384] = c3_dv51[c3_i384];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_p_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_d_Kr;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[3000];
  int32_T c3_i385;
  int32_T c3_i386;
  int32_T c3_i387;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_d_Kr = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_w_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_d_Kr), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_d_Kr);
  c3_i385 = 0;
  for (c3_i386 = 0; c3_i386 < 25; c3_i386++) {
    for (c3_i387 = 0; c3_i387 < 120; c3_i387++) {
      (*(real_T (*)[3000])c3_outData)[c3_i387 + c3_i385] = c3_y[c3_i387 +
        c3_i385];
    }

    c3_i385 += 120;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_x_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[525])
{
  real_T c3_dv52[525];
  int32_T c3_i388;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv52, 1, 0, 0U, 1, 0U, 2, 21,
                25);
  for (c3_i388 = 0; c3_i388 < 525; c3_i388++) {
    c3_y[c3_i388] = c3_dv52[c3_i388];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_q_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Kv;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[525];
  int32_T c3_i389;
  int32_T c3_i390;
  int32_T c3_i391;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Kv = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_x_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Kv), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Kv);
  c3_i389 = 0;
  for (c3_i390 = 0; c3_i390 < 25; c3_i390++) {
    for (c3_i391 = 0; c3_i391 < 21; c3_i391++) {
      (*(real_T (*)[525])c3_outData)[c3_i391 + c3_i389] = c3_y[c3_i391 + c3_i389];
    }

    c3_i389 += 21;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_y_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[195])
{
  real_T c3_dv53[195];
  int32_T c3_i392;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv53, 1, 0, 0U, 1, 0U, 1,
                195);
  for (c3_i392 = 0; c3_i392 < 195; c3_i392++) {
    c3_y[c3_i392] = c3_dv53[c3_i392];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_r_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Mlim;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[195];
  int32_T c3_i393;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Mlim = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Mlim), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Mlim);
  for (c3_i393 = 0; c3_i393 < 195; c3_i393++) {
    (*(real_T (*)[195])c3_outData)[c3_i393] = c3_y[c3_i393];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_ab_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[2535])
{
  real_T c3_dv54[2535];
  int32_T c3_i394;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv54, 1, 0, 0U, 1, 0U, 2,
                195, 13);
  for (c3_i394 = 0; c3_i394 < 2535; c3_i394++) {
    c3_y[c3_i394] = c3_dv54[c3_i394];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_s_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Mx;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[2535];
  int32_T c3_i395;
  int32_T c3_i396;
  int32_T c3_i397;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Mx = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_ab_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Mx), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Mx);
  c3_i395 = 0;
  for (c3_i396 = 0; c3_i396 < 13; c3_i396++) {
    for (c3_i397 = 0; c3_i397 < 195; c3_i397++) {
      (*(real_T (*)[2535])c3_outData)[c3_i397 + c3_i395] = c3_y[c3_i397 +
        c3_i395];
    }

    c3_i395 += 195;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_bb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[975])
{
  real_T c3_dv55[975];
  int32_T c3_i398;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv55, 1, 0, 0U, 1, 0U, 2,
                195, 5);
  for (c3_i398 = 0; c3_i398 < 975; c3_i398++) {
    c3_y[c3_i398] = c3_dv55[c3_i398];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_t_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Mu1;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[975];
  int32_T c3_i399;
  int32_T c3_i400;
  int32_T c3_i401;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Mu1 = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_bb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Mu1), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Mu1);
  c3_i399 = 0;
  for (c3_i400 = 0; c3_i400 < 5; c3_i400++) {
    for (c3_i401 = 0; c3_i401 < 195; c3_i401++) {
      (*(real_T (*)[975])c3_outData)[c3_i401 + c3_i399] = c3_y[c3_i401 + c3_i399];
    }

    c3_i399 += 195;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_cb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[4095])
{
  real_T c3_dv56[4095];
  int32_T c3_i402;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv56, 1, 0, 0U, 1, 0U, 2,
                195, 21);
  for (c3_i402 = 0; c3_i402 < 4095; c3_i402++) {
    c3_y[c3_i402] = c3_dv56[c3_i402];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_u_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_d_Mv;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[4095];
  int32_T c3_i403;
  int32_T c3_i404;
  int32_T c3_i405;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_d_Mv = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_cb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_d_Mv), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_d_Mv);
  c3_i403 = 0;
  for (c3_i404 = 0; c3_i404 < 21; c3_i404++) {
    for (c3_i405 = 0; c3_i405 < 195; c3_i405++) {
      (*(real_T (*)[4095])c3_outData)[c3_i405 + c3_i403] = c3_y[c3_i405 +
        c3_i403];
    }

    c3_i403 += 195;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_db_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[26])
{
  real_T c3_dv57[26];
  int32_T c3_i406;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv57, 1, 0, 0U, 1, 0U, 1, 26);
  for (c3_i406 = 0; c3_i406 < 26; c3_i406++) {
    c3_y[c3_i406] = c3_dv57[c3_i406];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_v_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_z_degrees;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[26];
  int32_T c3_i407;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_z_degrees = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_db_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_z_degrees), &c3_thisId,
    c3_y);
  sf_mex_destroy(&c3_c_z_degrees);
  for (c3_i407 = 0; c3_i407 < 26; c3_i407++) {
    (*(real_T (*)[26])c3_outData)[c3_i407] = c3_y[c3_i407];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_eb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[5070])
{
  real_T c3_dv58[5070];
  int32_T c3_i408;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv58, 1, 0, 0U, 1, 0U, 2,
                195, 26);
  for (c3_i408 = 0; c3_i408 < 5070; c3_i408++) {
    c3_y[c3_i408] = c3_dv58[c3_i408];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_w_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_d_Ac;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[5070];
  int32_T c3_i409;
  int32_T c3_i410;
  int32_T c3_i411;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_d_Ac = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_eb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_d_Ac), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_d_Ac);
  c3_i409 = 0;
  for (c3_i410 = 0; c3_i410 < 26; c3_i410++) {
    for (c3_i411 = 0; c3_i411 < 195; c3_i411++) {
      (*(real_T (*)[5070])c3_outData)[c3_i411 + c3_i409] = c3_y[c3_i411 +
        c3_i409];
    }

    c3_i409 += 195;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_fb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[500])
{
  real_T c3_dv59[500];
  int32_T c3_i412;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv59, 1, 0, 0U, 1, 0U, 2,
                100, 5);
  for (c3_i412 = 0; c3_i412 < 500; c3_i412++) {
    c3_y[c3_i412] = c3_dv59[c3_i412];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_x_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_I1;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[500];
  int32_T c3_i413;
  int32_T c3_i414;
  int32_T c3_i415;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_I1 = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_fb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_I1), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_I1);
  c3_i413 = 0;
  for (c3_i414 = 0; c3_i414 < 5; c3_i414++) {
    for (c3_i415 = 0; c3_i415 < 100; c3_i415++) {
      (*(real_T (*)[500])c3_outData)[c3_i415 + c3_i413] = c3_y[c3_i415 + c3_i413];
    }

    c3_i413 += 100;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_gb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[169])
{
  real_T c3_dv60[169];
  int32_T c3_i416;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv60, 1, 0, 0U, 1, 0U, 2, 13,
                13);
  for (c3_i416 = 0; c3_i416 < 169; c3_i416++) {
    c3_y[c3_i416] = c3_dv60[c3_i416];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_y_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_A;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[169];
  int32_T c3_i417;
  int32_T c3_i418;
  int32_T c3_i419;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_A = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_gb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_A), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_A);
  c3_i417 = 0;
  for (c3_i418 = 0; c3_i418 < 13; c3_i418++) {
    for (c3_i419 = 0; c3_i419 < 13; c3_i419++) {
      (*(real_T (*)[169])c3_outData)[c3_i419 + c3_i417] = c3_y[c3_i419 + c3_i417];
    }

    c3_i417 += 13;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_hb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[65])
{
  real_T c3_dv61[65];
  int32_T c3_i420;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv61, 1, 0, 0U, 1, 0U, 2, 13,
                5);
  for (c3_i420 = 0; c3_i420 < 65; c3_i420++) {
    c3_y[c3_i420] = c3_dv61[c3_i420];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_ab_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Bu;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[65];
  int32_T c3_i421;
  int32_T c3_i422;
  int32_T c3_i423;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Bu = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_hb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Bu), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Bu);
  c3_i421 = 0;
  for (c3_i422 = 0; c3_i422 < 5; c3_i422++) {
    for (c3_i423 = 0; c3_i423 < 13; c3_i423++) {
      (*(real_T (*)[65])c3_outData)[c3_i423 + c3_i421] = c3_y[c3_i423 + c3_i421];
    }

    c3_i421 += 13;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_ib_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[78])
{
  real_T c3_dv62[78];
  int32_T c3_i424;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv62, 1, 0, 0U, 1, 0U, 2, 6,
                13);
  for (c3_i424 = 0; c3_i424 < 78; c3_i424++) {
    c3_y[c3_i424] = c3_dv62[c3_i424];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_bb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_C;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[78];
  int32_T c3_i425;
  int32_T c3_i426;
  int32_T c3_i427;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_C = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_ib_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_C), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_C);
  c3_i425 = 0;
  for (c3_i426 = 0; c3_i426 < 13; c3_i426++) {
    for (c3_i427 = 0; c3_i427 < 6; c3_i427++) {
      (*(real_T (*)[78])c3_outData)[c3_i427 + c3_i425] = c3_y[c3_i427 + c3_i425];
    }

    c3_i425 += 6;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_jb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[5])
{
  real_T c3_dv63[5];
  int32_T c3_i428;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv63, 1, 0, 0U, 1, 0U, 2, 1,
                5);
  for (c3_i428 = 0; c3_i428 < 5; c3_i428++) {
    c3_y[c3_i428] = c3_dv63[c3_i428];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_cb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Ecc;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[5];
  int32_T c3_i429;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Ecc = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_jb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Ecc), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Ecc);
  for (c3_i429 = 0; c3_i429 < 5; c3_i429++) {
    (*(real_T (*)[5])c3_outData)[c3_i429] = c3_y[c3_i429];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_kb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[6])
{
  real_T c3_dv64[6];
  int32_T c3_i430;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv64, 1, 0, 0U, 1, 0U, 2, 1,
                6);
  for (c3_i430 = 0; c3_i430 < 6; c3_i430++) {
    c3_y[c3_i430] = c3_dv64[c3_i430];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_db_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Fcc;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[6];
  int32_T c3_i431;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Fcc = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_kb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Fcc), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Fcc);
  for (c3_i431 = 0; c3_i431 < 6; c3_i431++) {
    (*(real_T (*)[6])c3_outData)[c3_i431] = c3_y[c3_i431];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_lb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[78])
{
  real_T c3_dv65[78];
  int32_T c3_i432;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), c3_dv65, 1, 0, 0U, 1, 0U, 2, 13,
                6);
  for (c3_i432 = 0; c3_i432 < 78; c3_i432++) {
    c3_y[c3_i432] = c3_dv65[c3_i432];
  }

  sf_mex_destroy(&c3_e_u);
}

static void c3_eb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_M;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[78];
  int32_T c3_i433;
  int32_T c3_i434;
  int32_T c3_i435;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_M = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_lb_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_M), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_M);
  c3_i433 = 0;
  for (c3_i434 = 0; c3_i434 < 6; c3_i434++) {
    for (c3_i435 = 0; c3_i435 < 13; c3_i435++) {
      (*(real_T (*)[78])c3_outData)[c3_i435 + c3_i433] = c3_y[c3_i435 + c3_i433];
    }

    c3_i433 += 13;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static uint8_T c3_mb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_b_is_active_c3_mpclib, const char_T *c3_identifier)
{
  uint8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_nb_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_b_is_active_c3_mpclib), &c3_thisId);
  sf_mex_destroy(&c3_b_is_active_c3_mpclib);
  return c3_y;
}

static uint8_T c3_nb_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_e_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_y;
  uint8_T c3_u0;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_e_u), &c3_u0, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u0;
  sf_mex_destroy(&c3_e_u);
  return c3_y;
}

static void init_dsm_address_info(SFc3_mpclibInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc3_mpclibInstanceStruct *chartInstance)
{
  chartInstance->c3_xk1 = (real_T (*)[13])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c3_xk = (real_T (*)[13])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c3_old_u = (real_T (*)[5])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c3_ym = (real_T (*)[6])ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c3_ref = (real_T (*)[6])ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c3_md = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    4);
  chartInstance->c3_umin = (real_T (*)[5])ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c3_umax = (real_T (*)[5])ssGetInputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c3_ymin = (real_T (*)[6])ssGetInputPortSignal_wrapper
    (chartInstance->S, 7);
  chartInstance->c3_ymax = (real_T (*)[6])ssGetInputPortSignal_wrapper
    (chartInstance->S, 8);
  chartInstance->c3_switch_in = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 9);
  chartInstance->c3_ext_mv = (real_T (*)[5])ssGetInputPortSignal_wrapper
    (chartInstance->S, 10);
  chartInstance->c3_MVtarget = (real_T (*)[5])ssGetInputPortSignal_wrapper
    (chartInstance->S, 11);
  chartInstance->c3_ywt = (real_T (*)[6])ssGetInputPortSignal_wrapper
    (chartInstance->S, 12);
  chartInstance->c3_uwt = (real_T (*)[5])ssGetInputPortSignal_wrapper
    (chartInstance->S, 13);
  chartInstance->c3_duwt = (real_T (*)[5])ssGetInputPortSignal_wrapper
    (chartInstance->S, 14);
  chartInstance->c3_rhoeps = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 15);
  chartInstance->c3_iA = (boolean_T (*)[221])ssGetInputPortSignal_wrapper
    (chartInstance->S, 16);
  chartInstance->c3_d_u = (real_T (*)[5])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c3_cost = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c3_useq = (real_T (*)[100])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c3_status = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c3_xest = (real_T (*)[13])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c3_iAout = (boolean_T (*)[221])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 7);
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

void sf_c3_mpclib_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2569216691U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(641204370U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1873773613U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2560885749U);
}

mxArray* sf_c3_mpclib_get_post_codegen_info(void);
mxArray *sf_c3_mpclib_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("2XK8KXSsA5PRk27gNsbLfB");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,17,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(13);
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
      pr[0] = (double)(5);
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
      pr[0] = (double)(6);
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
      pr[0] = (double)(6);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
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
      pr[0] = (double)(5);
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
      pr[0] = (double)(5);
      pr[1] = (double)(1);
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
      pr[0] = (double)(6);
      pr[1] = (double)(1);
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
      pr[0] = (double)(6);
      pr[1] = (double)(1);
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
      pr[0] = (double)(1);
      pr[1] = (double)(1);
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
      pr[0] = (double)(5);
      pr[1] = (double)(1);
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
      pr[0] = (double)(5);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,12,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,12,"type",mxType);
    }

    mxSetField(mxData,12,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(5);
      pr[1] = (double)(1);
      mxSetField(mxData,13,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,13,"type",mxType);
    }

    mxSetField(mxData,13,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(5);
      pr[1] = (double)(1);
      mxSetField(mxData,14,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,14,"type",mxType);
    }

    mxSetField(mxData,14,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,15,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,15,"type",mxType);
    }

    mxSetField(mxData,15,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(221);
      pr[1] = (double)(1);
      mxSetField(mxData,16,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,16,"type",mxType);
    }

    mxSetField(mxData,16,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,74,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(13);
      pr[1] = (double)(13);
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
      pr[0] = (double)(13);
      pr[1] = (double)(5);
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
      pr[0] = (double)(13);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(13);
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
      pr[0] = (double)(1);
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
      pr[0] = (double)(6);
      pr[1] = (double)(1);
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
      pr[0] = (double)(1);
      pr[1] = (double)(5);
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
      pr[0] = (double)(1);
      pr[1] = (double)(6);
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
      pr[0] = (double)(1);
      pr[1] = (double)(1);
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
      pr[0] = (double)(26);
      pr[1] = (double)(26);
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
      pr[0] = (double)(26);
      pr[1] = (double)(26);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,12,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,12,"type",mxType);
    }

    mxSetField(mxData,12,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(100);
      pr[1] = (double)(5);
      mxSetField(mxData,13,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,13,"type",mxType);
    }

    mxSetField(mxData,13,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,14,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,14,"type",mxType);
    }

    mxSetField(mxData,14,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(120);
      pr[1] = (double)(25);
      mxSetField(mxData,15,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,15,"type",mxType);
    }

    mxSetField(mxData,15,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(5);
      pr[1] = (double)(25);
      mxSetField(mxData,16,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,16,"type",mxType);
    }

    mxSetField(mxData,16,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(100);
      pr[1] = (double)(25);
      mxSetField(mxData,17,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,17,"type",mxType);
    }

    mxSetField(mxData,17,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(21);
      pr[1] = (double)(25);
      mxSetField(mxData,18,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,18,"type",mxType);
    }

    mxSetField(mxData,18,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(13);
      pr[1] = (double)(25);
      mxSetField(mxData,19,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,19,"type",mxType);
    }

    mxSetField(mxData,19,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(13);
      pr[1] = (double)(6);
      mxSetField(mxData,20,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,20,"type",mxType);
    }

    mxSetField(mxData,20,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(26);
      pr[1] = (double)(26);
      mxSetField(mxData,21,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,21,"type",mxType);
    }

    mxSetField(mxData,21,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(13);
      pr[1] = (double)(6);
      mxSetField(mxData,22,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,22,"type",mxType);
    }

    mxSetField(mxData,22,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,23,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,23,"type",mxType);
    }

    mxSetField(mxData,23,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(195);
      pr[1] = (double)(1);
      mxSetField(mxData,24,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,24,"type",mxType);
    }

    mxSetField(mxData,24,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(195);
      pr[1] = (double)(1);
      mxSetField(mxData,25,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,25,"type",mxType);
    }

    mxSetField(mxData,25,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(195);
      pr[1] = (double)(5);
      mxSetField(mxData,26,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,26,"type",mxType);
    }

    mxSetField(mxData,26,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(195);
      pr[1] = (double)(21);
      mxSetField(mxData,27,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,27,"type",mxType);
    }

    mxSetField(mxData,27,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(195);
      pr[1] = (double)(13);
      mxSetField(mxData,28,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,28,"type",mxType);
    }

    mxSetField(mxData,28,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,29,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,29,"type",mxType);
    }

    mxSetField(mxData,29,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,30,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,30,"type",mxType);
    }

    mxSetField(mxData,30,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,31,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,31,"type",mxType);
    }

    mxSetField(mxData,31,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,32,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,32,"type",mxType);
    }

    mxSetField(mxData,32,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,33,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,33,"type",mxType);
    }

    mxSetField(mxData,33,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,34,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,34,"type",mxType);
    }

    mxSetField(mxData,34,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,35,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,35,"type",mxType);
    }

    mxSetField(mxData,35,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,36,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,36,"type",mxType);
    }

    mxSetField(mxData,36,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,37,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,37,"type",mxType);
    }

    mxSetField(mxData,37,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,38,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,38,"type",mxType);
    }

    mxSetField(mxData,38,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,39,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,39,"type",mxType);
    }

    mxSetField(mxData,39,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,40,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,40,"type",mxType);
    }

    mxSetField(mxData,40,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,41,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,41,"type",mxType);
    }

    mxSetField(mxData,41,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,42,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,42,"type",mxType);
    }

    mxSetField(mxData,42,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,43,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,43,"type",mxType);
    }

    mxSetField(mxData,43,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,44,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,44,"type",mxType);
    }

    mxSetField(mxData,44,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,45,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,45,"type",mxType);
    }

    mxSetField(mxData,45,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,46,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,46,"type",mxType);
    }

    mxSetField(mxData,46,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,47,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,47,"type",mxType);
    }

    mxSetField(mxData,47,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,48,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,48,"type",mxType);
    }

    mxSetField(mxData,48,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,49,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,49,"type",mxType);
    }

    mxSetField(mxData,49,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,50,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,50,"type",mxType);
    }

    mxSetField(mxData,50,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,51,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,51,"type",mxType);
    }

    mxSetField(mxData,51,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,52,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,52,"type",mxType);
    }

    mxSetField(mxData,52,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,53,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,53,"type",mxType);
    }

    mxSetField(mxData,53,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,54,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,54,"type",mxType);
    }

    mxSetField(mxData,54,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,55,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,55,"type",mxType);
    }

    mxSetField(mxData,55,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,56,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,56,"type",mxType);
    }

    mxSetField(mxData,56,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,57,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,57,"type",mxType);
    }

    mxSetField(mxData,57,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,58,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,58,"type",mxType);
    }

    mxSetField(mxData,58,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,59,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,59,"type",mxType);
    }

    mxSetField(mxData,59,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,60,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,60,"type",mxType);
    }

    mxSetField(mxData,60,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,61,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,61,"type",mxType);
    }

    mxSetField(mxData,61,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,62,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,62,"type",mxType);
    }

    mxSetField(mxData,62,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,63,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,63,"type",mxType);
    }

    mxSetField(mxData,63,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,64,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,64,"type",mxType);
    }

    mxSetField(mxData,64,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,65,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,65,"type",mxType);
    }

    mxSetField(mxData,65,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,66,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,66,"type",mxType);
    }

    mxSetField(mxData,66,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,67,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,67,"type",mxType);
    }

    mxSetField(mxData,67,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(5);
      pr[1] = (double)(1);
      mxSetField(mxData,68,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,68,"type",mxType);
    }

    mxSetField(mxData,68,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(100);
      pr[1] = (double)(1);
      mxSetField(mxData,69,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,69,"type",mxType);
    }

    mxSetField(mxData,69,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,70,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,70,"type",mxType);
    }

    mxSetField(mxData,70,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(13);
      pr[1] = (double)(1);
      mxSetField(mxData,71,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,71,"type",mxType);
    }

    mxSetField(mxData,71,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,72,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,72,"type",mxType);
    }

    mxSetField(mxData,72,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(26);
      pr[1] = (double)(1);
      mxSetField(mxData,73,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,73,"type",mxType);
    }

    mxSetField(mxData,73,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,7,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(13);
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
      pr[0] = (double)(5);
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
      pr[0] = (double)(1);
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
      pr[0] = (double)(20);
      pr[1] = (double)(5);
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
      pr[0] = (double)(1);
      pr[1] = (double)(1);
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
      pr[0] = (double)(13);
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
      pr[0] = (double)(221);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c3_mpclib_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c3_mpclib_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c3_mpclib_jit_fallback_info(void)
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

mxArray *sf_c3_mpclib_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c3_mpclib_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c3_mpclib(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x8'type','srcId','name','auxInfo'{{M[1],M[20],T\"cost\",},{M[1],M[145],T\"iAout\",},{M[1],M[126],T\"status\",},{M[1],M[19],T\"u\",},{M[1],M[21],T\"useq\",},{M[1],M[177],T\"xest\",},{M[1],M[174],T\"xk1\",},{M[8],M[0],T\"is_active_c3_mpclib\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 8, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_mpclib_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_mpclibInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc3_mpclibInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _mpclibMachineNumber_,
           3,
           1,
           1,
           0,
           98,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_mpclibMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_mpclibMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _mpclibMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,2,0,1,"xk1");
          _SFD_SET_DATA_PROPS(1,1,1,0,"xk");
          _SFD_SET_DATA_PROPS(2,1,1,0,"old_u");
          _SFD_SET_DATA_PROPS(3,1,1,0,"ym");
          _SFD_SET_DATA_PROPS(4,1,1,0,"ref");
          _SFD_SET_DATA_PROPS(5,1,1,0,"md");
          _SFD_SET_DATA_PROPS(6,1,1,0,"umin");
          _SFD_SET_DATA_PROPS(7,1,1,0,"umax");
          _SFD_SET_DATA_PROPS(8,1,1,0,"ymin");
          _SFD_SET_DATA_PROPS(9,1,1,0,"ymax");
          _SFD_SET_DATA_PROPS(10,1,1,0,"switch_in");
          _SFD_SET_DATA_PROPS(11,1,1,0,"ext_mv");
          _SFD_SET_DATA_PROPS(12,1,1,0,"MVtarget");
          _SFD_SET_DATA_PROPS(13,10,0,0,"isQP");
          _SFD_SET_DATA_PROPS(14,10,0,0,"nx");
          _SFD_SET_DATA_PROPS(15,10,0,0,"nu");
          _SFD_SET_DATA_PROPS(16,10,0,0,"ny");
          _SFD_SET_DATA_PROPS(17,10,0,0,"degrees");
          _SFD_SET_DATA_PROPS(18,10,0,0,"Hinv");
          _SFD_SET_DATA_PROPS(19,10,0,0,"Kx");
          _SFD_SET_DATA_PROPS(20,10,0,0,"Ku1");
          _SFD_SET_DATA_PROPS(21,10,0,0,"Kut");
          _SFD_SET_DATA_PROPS(22,10,0,0,"Kr");
          _SFD_SET_DATA_PROPS(23,10,0,0,"Kv");
          _SFD_SET_DATA_PROPS(24,10,0,0,"Mlim");
          _SFD_SET_DATA_PROPS(25,10,0,0,"Mx");
          _SFD_SET_DATA_PROPS(26,10,0,0,"Mu1");
          _SFD_SET_DATA_PROPS(27,10,0,0,"Mv");
          _SFD_SET_DATA_PROPS(28,10,0,0,"z_degrees");
          _SFD_SET_DATA_PROPS(29,10,0,0,"utarget");
          _SFD_SET_DATA_PROPS(30,10,0,0,"p");
          _SFD_SET_DATA_PROPS(31,10,0,0,"uoff");
          _SFD_SET_DATA_PROPS(32,10,0,0,"voff");
          _SFD_SET_DATA_PROPS(33,10,0,0,"yoff");
          _SFD_SET_DATA_PROPS(34,10,0,0,"maxiter");
          _SFD_SET_DATA_PROPS(35,10,0,0,"nxQP");
          _SFD_SET_DATA_PROPS(36,10,0,0,"openloopflag");
          _SFD_SET_DATA_PROPS(37,10,0,0,"lims_inport");
          _SFD_SET_DATA_PROPS(38,10,0,0,"no_umin");
          _SFD_SET_DATA_PROPS(39,10,0,0,"no_umax");
          _SFD_SET_DATA_PROPS(40,10,0,0,"no_ymin");
          _SFD_SET_DATA_PROPS(41,10,0,0,"no_ymax");
          _SFD_SET_DATA_PROPS(42,10,0,0,"switch_inport");
          _SFD_SET_DATA_PROPS(43,10,0,0,"no_switch");
          _SFD_SET_DATA_PROPS(44,10,0,0,"enable_value");
          _SFD_SET_DATA_PROPS(45,10,0,0,"return_cost");
          _SFD_SET_DATA_PROPS(46,10,0,0,"H");
          _SFD_SET_DATA_PROPS(47,10,0,0,"return_sequence");
          _SFD_SET_DATA_PROPS(48,10,0,0,"Linv");
          _SFD_SET_DATA_PROPS(49,10,0,0,"Ac");
          _SFD_SET_DATA_PROPS(50,1,1,0,"ywt");
          _SFD_SET_DATA_PROPS(51,1,1,0,"uwt");
          _SFD_SET_DATA_PROPS(52,1,1,0,"duwt");
          _SFD_SET_DATA_PROPS(53,1,1,0,"rhoeps");
          _SFD_SET_DATA_PROPS(54,1,1,0,"iA");
          _SFD_SET_DATA_PROPS(55,2,0,1,"u");
          _SFD_SET_DATA_PROPS(56,2,0,1,"cost");
          _SFD_SET_DATA_PROPS(57,2,0,1,"useq");
          _SFD_SET_DATA_PROPS(58,2,0,1,"status");
          _SFD_SET_DATA_PROPS(59,2,0,1,"xest");
          _SFD_SET_DATA_PROPS(60,10,0,0,"no_ywt");
          _SFD_SET_DATA_PROPS(61,10,0,0,"no_uwt");
          _SFD_SET_DATA_PROPS(62,10,0,0,"no_duwt");
          _SFD_SET_DATA_PROPS(63,10,0,0,"no_rhoeps");
          _SFD_SET_DATA_PROPS(64,10,0,0,"Wy");
          _SFD_SET_DATA_PROPS(65,10,0,0,"Wdu");
          _SFD_SET_DATA_PROPS(66,10,0,0,"Jm");
          _SFD_SET_DATA_PROPS(67,10,0,0,"SuJm");
          _SFD_SET_DATA_PROPS(68,10,0,0,"Su1");
          _SFD_SET_DATA_PROPS(69,10,0,0,"Sx");
          _SFD_SET_DATA_PROPS(70,10,0,0,"Hv");
          _SFD_SET_DATA_PROPS(71,10,0,0,"Wu");
          _SFD_SET_DATA_PROPS(72,10,0,0,"I1");
          _SFD_SET_DATA_PROPS(73,2,0,1,"iAout");
          _SFD_SET_DATA_PROPS(74,10,0,0,"A");
          _SFD_SET_DATA_PROPS(75,10,0,0,"Bu");
          _SFD_SET_DATA_PROPS(76,10,0,0,"Bv");
          _SFD_SET_DATA_PROPS(77,10,0,0,"C");
          _SFD_SET_DATA_PROPS(78,10,0,0,"Dv");
          _SFD_SET_DATA_PROPS(79,10,0,0,"Mrows");
          _SFD_SET_DATA_PROPS(80,10,0,0,"nCC");
          _SFD_SET_DATA_PROPS(81,10,0,0,"Ecc");
          _SFD_SET_DATA_PROPS(82,10,0,0,"Fcc");
          _SFD_SET_DATA_PROPS(83,10,0,0,"Scc");
          _SFD_SET_DATA_PROPS(84,10,0,0,"Gcc");
          _SFD_SET_DATA_PROPS(85,10,0,0,"nv");
          _SFD_SET_DATA_PROPS(86,10,0,0,"no_md");
          _SFD_SET_DATA_PROPS(87,10,0,0,"no_ref");
          _SFD_SET_DATA_PROPS(88,10,0,0,"no_uref");
          _SFD_SET_DATA_PROPS(89,10,0,0,"no_mv");
          _SFD_SET_DATA_PROPS(90,10,0,0,"Rscale");
          _SFD_SET_DATA_PROPS(91,10,0,0,"MDscale");
          _SFD_SET_DATA_PROPS(92,10,0,0,"myindex");
          _SFD_SET_DATA_PROPS(93,10,0,0,"myoff");
          _SFD_SET_DATA_PROPS(94,10,0,0,"xoff");
          _SFD_SET_DATA_PROPS(95,10,0,0,"CustomEstimation");
          _SFD_SET_DATA_PROPS(96,10,0,0,"M");
          _SFD_SET_DATA_PROPS(97,10,0,0,"L");
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
        _SFD_CV_INIT_EML(0,1,1,10,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,6128);
        _SFD_CV_INIT_EML_IF(0,1,0,1329,1344,-1,1652);
        _SFD_CV_INIT_EML_IF(0,1,1,1714,1729,2095,2264);
        _SFD_CV_INIT_EML_IF(0,1,2,1814,1825,1952,2094);
        _SFD_CV_INIT_EML_IF(0,1,3,2390,2403,2440,2546);
        _SFD_CV_INIT_EML_IF(0,1,4,2596,2620,2667,3068);
        _SFD_CV_INIT_EML_IF(0,1,5,3149,3164,3219,3437);
        _SFD_CV_INIT_EML_IF(0,1,6,3439,3454,5012,5785);
        _SFD_CV_INIT_EML_IF(0,1,7,3539,3550,4277,5011);
        _SFD_CV_INIT_EML_IF(0,1,8,5787,5811,5826,5954);
        _SFD_CV_INIT_EML_IF(0,1,9,6012,6036,6095,6127);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,0,2393,2403,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,1,2599,2620,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,2,3152,3164,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,3,5790,5811,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,4,6015,6036,-1,0);

        {
          unsigned int dimVector[1];
          dimVector[0]= 13;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)
            c3_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 13;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(13,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_q_sf_marshallOut,(MexInFcnForType)c3_j_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(15,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(16,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(17,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 26;
          dimVector[1]= 26;
          _SFD_SET_DATA_COMPILED_PROPS(18,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_p_sf_marshallOut,(MexInFcnForType)
            c3_l_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 13;
          dimVector[1]= 25;
          _SFD_SET_DATA_COMPILED_PROPS(19,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_bb_sf_marshallOut,(MexInFcnForType)
            c3_m_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 5;
          dimVector[1]= 25;
          _SFD_SET_DATA_COMPILED_PROPS(20,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_ab_sf_marshallOut,(MexInFcnForType)
            c3_n_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 100;
          dimVector[1]= 25;
          _SFD_SET_DATA_COMPILED_PROPS(21,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_y_sf_marshallOut,(MexInFcnForType)
            c3_o_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 120;
          dimVector[1]= 25;
          _SFD_SET_DATA_COMPILED_PROPS(22,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_x_sf_marshallOut,(MexInFcnForType)
            c3_p_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 21;
          dimVector[1]= 25;
          _SFD_SET_DATA_COMPILED_PROPS(23,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_w_sf_marshallOut,(MexInFcnForType)
            c3_q_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 195;
          _SFD_SET_DATA_COMPILED_PROPS(24,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_j_sf_marshallOut,(MexInFcnForType)
            c3_r_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 195;
          dimVector[1]= 13;
          _SFD_SET_DATA_COMPILED_PROPS(25,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_v_sf_marshallOut,(MexInFcnForType)
            c3_s_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 195;
          dimVector[1]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(26,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_u_sf_marshallOut,(MexInFcnForType)
            c3_t_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 195;
          dimVector[1]= 21;
          _SFD_SET_DATA_COMPILED_PROPS(27,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_t_sf_marshallOut,(MexInFcnForType)
            c3_u_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 26;
          _SFD_SET_DATA_COMPILED_PROPS(28,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_s_sf_marshallOut,(MexInFcnForType)
            c3_v_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 100;
          _SFD_SET_DATA_COMPILED_PROPS(29,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_r_sf_marshallOut,(MexInFcnForType)
            c3_f_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(30,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(31,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_e_sf_marshallOut,(MexInFcnForType)
            c3_e_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(32,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(33,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)
            c3_g_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(34,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(35,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(36,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_q_sf_marshallOut,(MexInFcnForType)c3_j_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(37,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(38,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(39,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(40,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(41,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(42,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(43,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(44,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(45,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 26;
          dimVector[1]= 26;
          _SFD_SET_DATA_COMPILED_PROPS(46,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_p_sf_marshallOut,(MexInFcnForType)
            c3_l_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(47,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 26;
          dimVector[1]= 26;
          _SFD_SET_DATA_COMPILED_PROPS(48,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_p_sf_marshallOut,(MexInFcnForType)
            c3_l_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 195;
          dimVector[1]= 26;
          _SFD_SET_DATA_COMPILED_PROPS(49,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_o_sf_marshallOut,(MexInFcnForType)
            c3_w_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(50,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(51,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(52,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(53,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 221;
          _SFD_SET_DATA_COMPILED_PROPS(54,SF_UINT8,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(55,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_e_sf_marshallOut,(MexInFcnForType)
            c3_e_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(56,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 20;
          dimVector[1]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(57,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_d_sf_marshallOut,(MexInFcnForType)
            c3_d_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(58,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 13;
          _SFD_SET_DATA_COMPILED_PROPS(59,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)
            c3_b_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(60,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(61,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(62,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(63,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(64,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(65,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(66,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(67,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(68,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(69,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(70,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(71,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 100;
          dimVector[1]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(72,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_n_sf_marshallOut,(MexInFcnForType)
            c3_x_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 221;
          _SFD_SET_DATA_COMPILED_PROPS(73,SF_UINT8,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)
            c3_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 13;
          dimVector[1]= 13;
          _SFD_SET_DATA_COMPILED_PROPS(74,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_m_sf_marshallOut,(MexInFcnForType)
            c3_y_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 13;
          dimVector[1]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(75,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_l_sf_marshallOut,(MexInFcnForType)
            c3_ab_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 13;
          _SFD_SET_DATA_COMPILED_PROPS(76,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)
            c3_b_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 6;
          dimVector[1]= 13;
          _SFD_SET_DATA_COMPILED_PROPS(77,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_k_sf_marshallOut,(MexInFcnForType)
            c3_bb_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(78,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)
            c3_g_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 195;
          _SFD_SET_DATA_COMPILED_PROPS(79,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_j_sf_marshallOut,(MexInFcnForType)
            c3_r_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(80,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 1;
          dimVector[1]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(81,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_i_sf_marshallOut,(MexInFcnForType)
            c3_cb_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(82,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_h_sf_marshallOut,(MexInFcnForType)
            c3_db_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(83,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(84,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(85,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(86,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(87,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(88,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(89,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(90,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)
            c3_g_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(91,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(92,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)
            c3_g_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(93,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)
            c3_g_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 13;
          _SFD_SET_DATA_COMPILED_PROPS(94,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)
            c3_b_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(95,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)c3_c_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 13;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(96,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_g_sf_marshallOut,(MexInFcnForType)
            c3_eb_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 13;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(97,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_g_sf_marshallOut,(MexInFcnForType)
            c3_eb_sf_marshallIn);
        }

        _SFD_SET_DATA_VALUE_PTR(0U, *chartInstance->c3_xk1);
        _SFD_SET_DATA_VALUE_PTR(1U, *chartInstance->c3_xk);
        _SFD_SET_DATA_VALUE_PTR(2U, *chartInstance->c3_old_u);
        _SFD_SET_DATA_VALUE_PTR(3U, *chartInstance->c3_ym);
        _SFD_SET_DATA_VALUE_PTR(4U, *chartInstance->c3_ref);
        _SFD_SET_DATA_VALUE_PTR(5U, chartInstance->c3_md);
        _SFD_SET_DATA_VALUE_PTR(6U, *chartInstance->c3_umin);
        _SFD_SET_DATA_VALUE_PTR(7U, *chartInstance->c3_umax);
        _SFD_SET_DATA_VALUE_PTR(8U, *chartInstance->c3_ymin);
        _SFD_SET_DATA_VALUE_PTR(9U, *chartInstance->c3_ymax);
        _SFD_SET_DATA_VALUE_PTR(10U, chartInstance->c3_switch_in);
        _SFD_SET_DATA_VALUE_PTR(11U, *chartInstance->c3_ext_mv);
        _SFD_SET_DATA_VALUE_PTR(12U, *chartInstance->c3_MVtarget);
        _SFD_SET_DATA_VALUE_PTR(13U, &chartInstance->c3_isQP);
        _SFD_SET_DATA_VALUE_PTR(14U, &chartInstance->c3_nx);
        _SFD_SET_DATA_VALUE_PTR(15U, &chartInstance->c3_nu);
        _SFD_SET_DATA_VALUE_PTR(16U, &chartInstance->c3_ny);
        _SFD_SET_DATA_VALUE_PTR(17U, &chartInstance->c3_degrees);
        _SFD_SET_DATA_VALUE_PTR(18U, chartInstance->c3_Hinv);
        _SFD_SET_DATA_VALUE_PTR(19U, chartInstance->c3_Kx);
        _SFD_SET_DATA_VALUE_PTR(20U, chartInstance->c3_Ku1);
        _SFD_SET_DATA_VALUE_PTR(21U, chartInstance->c3_Kut);
        _SFD_SET_DATA_VALUE_PTR(22U, chartInstance->c3_Kr);
        _SFD_SET_DATA_VALUE_PTR(23U, chartInstance->c3_Kv);
        _SFD_SET_DATA_VALUE_PTR(24U, chartInstance->c3_Mlim);
        _SFD_SET_DATA_VALUE_PTR(25U, chartInstance->c3_Mx);
        _SFD_SET_DATA_VALUE_PTR(26U, chartInstance->c3_Mu1);
        _SFD_SET_DATA_VALUE_PTR(27U, chartInstance->c3_Mv);
        _SFD_SET_DATA_VALUE_PTR(28U, chartInstance->c3_z_degrees);
        _SFD_SET_DATA_VALUE_PTR(29U, chartInstance->c3_utarget);
        _SFD_SET_DATA_VALUE_PTR(30U, &chartInstance->c3_p);
        _SFD_SET_DATA_VALUE_PTR(31U, chartInstance->c3_uoff);
        _SFD_SET_DATA_VALUE_PTR(32U, &chartInstance->c3_voff);
        _SFD_SET_DATA_VALUE_PTR(33U, chartInstance->c3_yoff);
        _SFD_SET_DATA_VALUE_PTR(34U, &chartInstance->c3_maxiter);
        _SFD_SET_DATA_VALUE_PTR(35U, &chartInstance->c3_nxQP);
        _SFD_SET_DATA_VALUE_PTR(36U, &chartInstance->c3_openloopflag);
        _SFD_SET_DATA_VALUE_PTR(37U, &chartInstance->c3_lims_inport);
        _SFD_SET_DATA_VALUE_PTR(38U, &chartInstance->c3_no_umin);
        _SFD_SET_DATA_VALUE_PTR(39U, &chartInstance->c3_no_umax);
        _SFD_SET_DATA_VALUE_PTR(40U, &chartInstance->c3_no_ymin);
        _SFD_SET_DATA_VALUE_PTR(41U, &chartInstance->c3_no_ymax);
        _SFD_SET_DATA_VALUE_PTR(42U, &chartInstance->c3_switch_inport);
        _SFD_SET_DATA_VALUE_PTR(43U, &chartInstance->c3_no_switch);
        _SFD_SET_DATA_VALUE_PTR(44U, &chartInstance->c3_enable_value);
        _SFD_SET_DATA_VALUE_PTR(45U, &chartInstance->c3_return_cost);
        _SFD_SET_DATA_VALUE_PTR(46U, chartInstance->c3_H);
        _SFD_SET_DATA_VALUE_PTR(47U, &chartInstance->c3_return_sequence);
        _SFD_SET_DATA_VALUE_PTR(48U, chartInstance->c3_Linv);
        _SFD_SET_DATA_VALUE_PTR(49U, chartInstance->c3_Ac);
        _SFD_SET_DATA_VALUE_PTR(50U, *chartInstance->c3_ywt);
        _SFD_SET_DATA_VALUE_PTR(51U, *chartInstance->c3_uwt);
        _SFD_SET_DATA_VALUE_PTR(52U, *chartInstance->c3_duwt);
        _SFD_SET_DATA_VALUE_PTR(53U, chartInstance->c3_rhoeps);
        _SFD_SET_DATA_VALUE_PTR(54U, *chartInstance->c3_iA);
        _SFD_SET_DATA_VALUE_PTR(55U, *chartInstance->c3_d_u);
        _SFD_SET_DATA_VALUE_PTR(56U, chartInstance->c3_cost);
        _SFD_SET_DATA_VALUE_PTR(57U, *chartInstance->c3_useq);
        _SFD_SET_DATA_VALUE_PTR(58U, chartInstance->c3_status);
        _SFD_SET_DATA_VALUE_PTR(59U, *chartInstance->c3_xest);
        _SFD_SET_DATA_VALUE_PTR(60U, &chartInstance->c3_no_ywt);
        _SFD_SET_DATA_VALUE_PTR(61U, &chartInstance->c3_no_uwt);
        _SFD_SET_DATA_VALUE_PTR(62U, &chartInstance->c3_no_duwt);
        _SFD_SET_DATA_VALUE_PTR(63U, &chartInstance->c3_no_rhoeps);
        _SFD_SET_DATA_VALUE_PTR(64U, &chartInstance->c3_Wy);
        _SFD_SET_DATA_VALUE_PTR(65U, &chartInstance->c3_Wdu);
        _SFD_SET_DATA_VALUE_PTR(66U, &chartInstance->c3_Jm);
        _SFD_SET_DATA_VALUE_PTR(67U, &chartInstance->c3_SuJm);
        _SFD_SET_DATA_VALUE_PTR(68U, &chartInstance->c3_Su1);
        _SFD_SET_DATA_VALUE_PTR(69U, &chartInstance->c3_Sx);
        _SFD_SET_DATA_VALUE_PTR(70U, &chartInstance->c3_Hv);
        _SFD_SET_DATA_VALUE_PTR(71U, &chartInstance->c3_Wu);
        _SFD_SET_DATA_VALUE_PTR(72U, chartInstance->c3_I1);
        _SFD_SET_DATA_VALUE_PTR(73U, *chartInstance->c3_iAout);
        _SFD_SET_DATA_VALUE_PTR(74U, chartInstance->c3_A);
        _SFD_SET_DATA_VALUE_PTR(75U, chartInstance->c3_Bu);
        _SFD_SET_DATA_VALUE_PTR(76U, chartInstance->c3_Bv);
        _SFD_SET_DATA_VALUE_PTR(77U, chartInstance->c3_C);
        _SFD_SET_DATA_VALUE_PTR(78U, chartInstance->c3_Dv);
        _SFD_SET_DATA_VALUE_PTR(79U, chartInstance->c3_Mrows);
        _SFD_SET_DATA_VALUE_PTR(80U, &chartInstance->c3_nCC);
        _SFD_SET_DATA_VALUE_PTR(81U, chartInstance->c3_Ecc);
        _SFD_SET_DATA_VALUE_PTR(82U, chartInstance->c3_Fcc);
        _SFD_SET_DATA_VALUE_PTR(83U, &chartInstance->c3_Scc);
        _SFD_SET_DATA_VALUE_PTR(84U, &chartInstance->c3_Gcc);
        _SFD_SET_DATA_VALUE_PTR(85U, &chartInstance->c3_nv);
        _SFD_SET_DATA_VALUE_PTR(86U, &chartInstance->c3_no_md);
        _SFD_SET_DATA_VALUE_PTR(87U, &chartInstance->c3_no_ref);
        _SFD_SET_DATA_VALUE_PTR(88U, &chartInstance->c3_no_uref);
        _SFD_SET_DATA_VALUE_PTR(89U, &chartInstance->c3_no_mv);
        _SFD_SET_DATA_VALUE_PTR(90U, chartInstance->c3_Rscale);
        _SFD_SET_DATA_VALUE_PTR(91U, &chartInstance->c3_MDscale);
        _SFD_SET_DATA_VALUE_PTR(92U, chartInstance->c3_myindex);
        _SFD_SET_DATA_VALUE_PTR(93U, chartInstance->c3_myoff);
        _SFD_SET_DATA_VALUE_PTR(94U, chartInstance->c3_xoff);
        _SFD_SET_DATA_VALUE_PTR(95U, &chartInstance->c3_CustomEstimation);
        _SFD_SET_DATA_VALUE_PTR(96U, chartInstance->c3_M);
        _SFD_SET_DATA_VALUE_PTR(97U, chartInstance->c3_L);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _mpclibMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "aYqxggvYP39bPQNJ8fS1OF";
}

static void sf_opaque_initialize_c3_mpclib(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc3_mpclibInstanceStruct*) chartInstanceVar)->S,
    0);
  initialize_params_c3_mpclib((SFc3_mpclibInstanceStruct*) chartInstanceVar);
  initialize_c3_mpclib((SFc3_mpclibInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c3_mpclib(void *chartInstanceVar)
{
  enable_c3_mpclib((SFc3_mpclibInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_mpclib(void *chartInstanceVar)
{
  disable_c3_mpclib((SFc3_mpclibInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c3_mpclib(void *chartInstanceVar)
{
  sf_gateway_c3_mpclib((SFc3_mpclibInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c3_mpclib(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c3_mpclib((SFc3_mpclibInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c3_mpclib(SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c3_mpclib((SFc3_mpclibInstanceStruct*)chartInfo->chartInstance,
    st);
}

static void sf_opaque_terminate_c3_mpclib(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_mpclibInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_mpclib_optimization_info();
    }

    finalize_c3_mpclib((SFc3_mpclibInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_mpclib((SFc3_mpclibInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_mpclib(SimStruct *S)
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
    initialize_params_c3_mpclib((SFc3_mpclibInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c3_mpclib(SimStruct *S)
{
  /* Actual parameters from chart:
     A Ac Bu Bv C CustomEstimation Dv Ecc Fcc Gcc H Hinv Hv I1 Jm Kr Ku1 Kut Kv Kx L Linv M MDscale Mlim Mrows Mu1 Mv Mx Rscale Scc Su1 SuJm Sx Wdu Wu Wy degrees enable_value isQP lims_inport maxiter myindex myoff nCC no_duwt no_md no_mv no_ref no_rhoeps no_switch no_umax no_umin no_uref no_uwt no_ymax no_ymin no_ywt nu nv nx nxQP ny openloopflag p return_cost return_sequence switch_inport uoff utarget voff xoff yoff z_degrees
   */
  const char_T *rtParamNames[] = { "A", "Ac", "Bu", "Bv", "C",
    "CustomEstimation", "Dv", "Ecc", "Fcc", "Gcc", "H", "Hinv", "Hv", "I1", "Jm",
    "Kr", "Ku1", "Kut", "Kv", "Kx", "L", "Linv", "M", "MDscale", "Mlim", "Mrows",
    "Mu1", "Mv", "Mx", "Rscale", "Scc", "Su1", "SuJm", "Sx", "Wdu", "Wu", "Wy",
    "degrees", "enable_value", "isQP", "lims_inport", "maxiter", "myindex",
    "myoff", "nCC", "no_duwt", "no_md", "no_mv", "no_ref", "no_rhoeps",
    "no_switch", "no_umax", "no_umin", "no_uref", "no_uwt", "no_ymax", "no_ymin",
    "no_ywt", "nu", "nv", "nx", "nxQP", "ny", "openloopflag", "p", "return_cost",
    "return_sequence", "switch_inport", "uoff", "utarget", "voff", "xoff",
    "yoff", "z_degrees" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for A*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_DOUBLE);

  /* registration for Ac*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_DOUBLE);

  /* registration for Bu*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_DOUBLE);

  /* registration for Bv*/
  ssRegDlgParamAsRunTimeParam(S, 3, 3, rtParamNames[3], SS_DOUBLE);

  /* registration for C*/
  ssRegDlgParamAsRunTimeParam(S, 4, 4, rtParamNames[4], SS_DOUBLE);

  /* registration for CustomEstimation*/
  ssRegDlgParamAsRunTimeParam(S, 5, 5, rtParamNames[5], SS_DOUBLE);

  /* registration for Dv*/
  ssRegDlgParamAsRunTimeParam(S, 6, 6, rtParamNames[6], SS_DOUBLE);

  /* registration for Ecc*/
  ssRegDlgParamAsRunTimeParam(S, 7, 7, rtParamNames[7], SS_DOUBLE);

  /* registration for Fcc*/
  ssRegDlgParamAsRunTimeParam(S, 8, 8, rtParamNames[8], SS_DOUBLE);

  /* registration for Gcc*/
  ssRegDlgParamAsRunTimeParam(S, 9, 9, rtParamNames[9], SS_DOUBLE);

  /* registration for H*/
  ssRegDlgParamAsRunTimeParam(S, 10, 10, rtParamNames[10], SS_DOUBLE);

  /* registration for Hinv*/
  ssRegDlgParamAsRunTimeParam(S, 11, 11, rtParamNames[11], SS_DOUBLE);

  /* registration for Hv*/
  ssRegDlgParamAsRunTimeParam(S, 12, 12, rtParamNames[12], SS_DOUBLE);

  /* registration for I1*/
  ssRegDlgParamAsRunTimeParam(S, 13, 13, rtParamNames[13], SS_DOUBLE);

  /* registration for Jm*/
  ssRegDlgParamAsRunTimeParam(S, 14, 14, rtParamNames[14], SS_DOUBLE);

  /* registration for Kr*/
  ssRegDlgParamAsRunTimeParam(S, 15, 15, rtParamNames[15], SS_DOUBLE);

  /* registration for Ku1*/
  ssRegDlgParamAsRunTimeParam(S, 16, 16, rtParamNames[16], SS_DOUBLE);

  /* registration for Kut*/
  ssRegDlgParamAsRunTimeParam(S, 17, 17, rtParamNames[17], SS_DOUBLE);

  /* registration for Kv*/
  ssRegDlgParamAsRunTimeParam(S, 18, 18, rtParamNames[18], SS_DOUBLE);

  /* registration for Kx*/
  ssRegDlgParamAsRunTimeParam(S, 19, 19, rtParamNames[19], SS_DOUBLE);

  /* registration for L*/
  ssRegDlgParamAsRunTimeParam(S, 20, 20, rtParamNames[20], SS_DOUBLE);

  /* registration for Linv*/
  ssRegDlgParamAsRunTimeParam(S, 21, 21, rtParamNames[21], SS_DOUBLE);

  /* registration for M*/
  ssRegDlgParamAsRunTimeParam(S, 22, 22, rtParamNames[22], SS_DOUBLE);

  /* registration for MDscale*/
  ssRegDlgParamAsRunTimeParam(S, 23, 23, rtParamNames[23], SS_DOUBLE);

  /* registration for Mlim*/
  ssRegDlgParamAsRunTimeParam(S, 24, 24, rtParamNames[24], SS_DOUBLE);

  /* registration for Mrows*/
  ssRegDlgParamAsRunTimeParam(S, 25, 25, rtParamNames[25], SS_DOUBLE);

  /* registration for Mu1*/
  ssRegDlgParamAsRunTimeParam(S, 26, 26, rtParamNames[26], SS_DOUBLE);

  /* registration for Mv*/
  ssRegDlgParamAsRunTimeParam(S, 27, 27, rtParamNames[27], SS_DOUBLE);

  /* registration for Mx*/
  ssRegDlgParamAsRunTimeParam(S, 28, 28, rtParamNames[28], SS_DOUBLE);

  /* registration for Rscale*/
  ssRegDlgParamAsRunTimeParam(S, 29, 29, rtParamNames[29], SS_DOUBLE);

  /* registration for Scc*/
  ssRegDlgParamAsRunTimeParam(S, 30, 30, rtParamNames[30], SS_DOUBLE);

  /* registration for Su1*/
  ssRegDlgParamAsRunTimeParam(S, 31, 31, rtParamNames[31], SS_DOUBLE);

  /* registration for SuJm*/
  ssRegDlgParamAsRunTimeParam(S, 32, 32, rtParamNames[32], SS_DOUBLE);

  /* registration for Sx*/
  ssRegDlgParamAsRunTimeParam(S, 33, 33, rtParamNames[33], SS_DOUBLE);

  /* registration for Wdu*/
  ssRegDlgParamAsRunTimeParam(S, 34, 34, rtParamNames[34], SS_DOUBLE);

  /* registration for Wu*/
  ssRegDlgParamAsRunTimeParam(S, 35, 35, rtParamNames[35], SS_DOUBLE);

  /* registration for Wy*/
  ssRegDlgParamAsRunTimeParam(S, 36, 36, rtParamNames[36], SS_DOUBLE);

  /* registration for degrees*/
  ssRegDlgParamAsRunTimeParam(S, 37, 37, rtParamNames[37], SS_DOUBLE);

  /* registration for enable_value*/
  ssRegDlgParamAsRunTimeParam(S, 38, 38, rtParamNames[38], SS_DOUBLE);

  /* registration for isQP*/
  ssRegDlgParamAsRunTimeParam(S, 39, 39, rtParamNames[39], SS_BOOLEAN);

  /* registration for lims_inport*/
  ssRegDlgParamAsRunTimeParam(S, 40, 40, rtParamNames[40], SS_DOUBLE);

  /* registration for maxiter*/
  ssRegDlgParamAsRunTimeParam(S, 41, 41, rtParamNames[41], SS_DOUBLE);

  /* registration for myindex*/
  ssRegDlgParamAsRunTimeParam(S, 42, 42, rtParamNames[42], SS_DOUBLE);

  /* registration for myoff*/
  ssRegDlgParamAsRunTimeParam(S, 43, 43, rtParamNames[43], SS_DOUBLE);

  /* registration for nCC*/
  ssRegDlgParamAsRunTimeParam(S, 44, 44, rtParamNames[44], SS_DOUBLE);

  /* registration for no_duwt*/
  ssRegDlgParamAsRunTimeParam(S, 45, 45, rtParamNames[45], SS_DOUBLE);

  /* registration for no_md*/
  ssRegDlgParamAsRunTimeParam(S, 46, 46, rtParamNames[46], SS_DOUBLE);

  /* registration for no_mv*/
  ssRegDlgParamAsRunTimeParam(S, 47, 47, rtParamNames[47], SS_DOUBLE);

  /* registration for no_ref*/
  ssRegDlgParamAsRunTimeParam(S, 48, 48, rtParamNames[48], SS_DOUBLE);

  /* registration for no_rhoeps*/
  ssRegDlgParamAsRunTimeParam(S, 49, 49, rtParamNames[49], SS_DOUBLE);

  /* registration for no_switch*/
  ssRegDlgParamAsRunTimeParam(S, 50, 50, rtParamNames[50], SS_DOUBLE);

  /* registration for no_umax*/
  ssRegDlgParamAsRunTimeParam(S, 51, 51, rtParamNames[51], SS_DOUBLE);

  /* registration for no_umin*/
  ssRegDlgParamAsRunTimeParam(S, 52, 52, rtParamNames[52], SS_DOUBLE);

  /* registration for no_uref*/
  ssRegDlgParamAsRunTimeParam(S, 53, 53, rtParamNames[53], SS_DOUBLE);

  /* registration for no_uwt*/
  ssRegDlgParamAsRunTimeParam(S, 54, 54, rtParamNames[54], SS_DOUBLE);

  /* registration for no_ymax*/
  ssRegDlgParamAsRunTimeParam(S, 55, 55, rtParamNames[55], SS_DOUBLE);

  /* registration for no_ymin*/
  ssRegDlgParamAsRunTimeParam(S, 56, 56, rtParamNames[56], SS_DOUBLE);

  /* registration for no_ywt*/
  ssRegDlgParamAsRunTimeParam(S, 57, 57, rtParamNames[57], SS_DOUBLE);

  /* registration for nu*/
  ssRegDlgParamAsRunTimeParam(S, 58, 58, rtParamNames[58], SS_DOUBLE);

  /* registration for nv*/
  ssRegDlgParamAsRunTimeParam(S, 59, 59, rtParamNames[59], SS_DOUBLE);

  /* registration for nx*/
  ssRegDlgParamAsRunTimeParam(S, 60, 60, rtParamNames[60], SS_DOUBLE);

  /* registration for nxQP*/
  ssRegDlgParamAsRunTimeParam(S, 61, 61, rtParamNames[61], SS_DOUBLE);

  /* registration for ny*/
  ssRegDlgParamAsRunTimeParam(S, 62, 62, rtParamNames[62], SS_DOUBLE);

  /* registration for openloopflag*/
  ssRegDlgParamAsRunTimeParam(S, 63, 63, rtParamNames[63], SS_BOOLEAN);

  /* registration for p*/
  ssRegDlgParamAsRunTimeParam(S, 64, 64, rtParamNames[64], SS_DOUBLE);

  /* registration for return_cost*/
  ssRegDlgParamAsRunTimeParam(S, 65, 65, rtParamNames[65], SS_DOUBLE);

  /* registration for return_sequence*/
  ssRegDlgParamAsRunTimeParam(S, 66, 66, rtParamNames[66], SS_DOUBLE);

  /* registration for switch_inport*/
  ssRegDlgParamAsRunTimeParam(S, 67, 67, rtParamNames[67], SS_DOUBLE);

  /* registration for uoff*/
  ssRegDlgParamAsRunTimeParam(S, 68, 68, rtParamNames[68], SS_DOUBLE);

  /* registration for utarget*/
  ssRegDlgParamAsRunTimeParam(S, 69, 69, rtParamNames[69], SS_DOUBLE);

  /* registration for voff*/
  ssRegDlgParamAsRunTimeParam(S, 70, 70, rtParamNames[70], SS_DOUBLE);

  /* registration for xoff*/
  ssRegDlgParamAsRunTimeParam(S, 71, 71, rtParamNames[71], SS_DOUBLE);

  /* registration for yoff*/
  ssRegDlgParamAsRunTimeParam(S, 72, 72, rtParamNames[72], SS_DOUBLE);

  /* registration for z_degrees*/
  ssRegDlgParamAsRunTimeParam(S, 73, 73, rtParamNames[73], SS_DOUBLE);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_mpclib_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,3,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,3,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,3);
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
      ssSetInputPortOptimOpts(S, 12, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 13, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 14, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 15, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 16, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,3,17);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,3,7);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=7; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 17; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2924856811U));
  ssSetChecksum1(S,(1899100543U));
  ssSetChecksum2(S,(3559350188U));
  ssSetChecksum3(S,(2700931736U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c3_mpclib(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_mpclib(SimStruct *S)
{
  SFc3_mpclibInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc3_mpclibInstanceStruct *)utMalloc(sizeof
    (SFc3_mpclibInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_mpclibInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c3_mpclib;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c3_mpclib;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c3_mpclib;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_mpclib;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_mpclib;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c3_mpclib;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c3_mpclib;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c3_mpclib;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_mpclib;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_mpclib;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_mpclib;
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

void c3_mpclib_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_mpclib(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_mpclib(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_mpclib(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_mpclib_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
