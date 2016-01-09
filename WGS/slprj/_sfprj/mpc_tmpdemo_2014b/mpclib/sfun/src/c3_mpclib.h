#ifndef __c3_mpclib_h__
#define __c3_mpclib_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc3_mpclibInstanceStruct
#define typedef_SFc3_mpclibInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c3_sfEvent;
  boolean_T c3_isStable;
  boolean_T c3_doneDoubleBufferReInit;
  uint8_T c3_is_active_c3_mpclib;
  boolean_T c3_isQP;
  real_T c3_nx;
  real_T c3_nu;
  real_T c3_ny;
  real_T c3_degrees;
  real_T c3_Hinv[676];
  real_T c3_Kx[325];
  real_T c3_Ku1[125];
  real_T c3_Kut[2500];
  real_T c3_Kr[3000];
  real_T c3_Kv[525];
  real_T c3_Mlim[195];
  real_T c3_Mx[2535];
  real_T c3_Mu1[975];
  real_T c3_Mv[4095];
  real_T c3_z_degrees[26];
  real_T c3_utarget[100];
  real_T c3_p;
  real_T c3_uoff[5];
  real_T c3_voff;
  real_T c3_yoff[6];
  real_T c3_maxiter;
  real_T c3_nxQP;
  boolean_T c3_openloopflag;
  real_T c3_lims_inport;
  real_T c3_no_umin;
  real_T c3_no_umax;
  real_T c3_no_ymin;
  real_T c3_no_ymax;
  real_T c3_switch_inport;
  real_T c3_no_switch;
  real_T c3_enable_value;
  real_T c3_return_cost;
  real_T c3_H[676];
  real_T c3_return_sequence;
  real_T c3_Linv[676];
  real_T c3_Ac[5070];
  real_T c3_no_ywt;
  real_T c3_no_uwt;
  real_T c3_no_duwt;
  real_T c3_no_rhoeps;
  real_T c3_Wy;
  real_T c3_Wdu;
  real_T c3_Jm;
  real_T c3_SuJm;
  real_T c3_Su1;
  real_T c3_Sx;
  real_T c3_Hv;
  real_T c3_Wu;
  real_T c3_I1[500];
  real_T c3_A[169];
  real_T c3_Bu[65];
  real_T c3_Bv[13];
  real_T c3_C[78];
  real_T c3_Dv[6];
  real_T c3_Mrows[195];
  real_T c3_nCC;
  real_T c3_Ecc[5];
  real_T c3_Fcc[6];
  real_T c3_Scc;
  real_T c3_Gcc;
  real_T c3_nv;
  real_T c3_no_md;
  real_T c3_no_ref;
  real_T c3_no_uref;
  real_T c3_no_mv;
  real_T c3_Rscale[6];
  real_T c3_MDscale;
  real_T c3_myindex[6];
  real_T c3_myoff[6];
  real_T c3_xoff[13];
  real_T c3_CustomEstimation;
  real_T c3_M[78];
  real_T c3_L[78];
  real_T c3_c_Ac[5070];
  real_T c3_u[5070];
  real_T c3_c_Mv[4095];
  real_T c3_b_u[4095];
  real_T c3_c_Kr[3000];
  real_T c3_c_u[3000];
  real_T (*c3_xk1)[13];
  real_T (*c3_xk)[13];
  real_T (*c3_old_u)[5];
  real_T (*c3_ym)[6];
  real_T (*c3_ref)[6];
  real_T *c3_md;
  real_T (*c3_umin)[5];
  real_T (*c3_umax)[5];
  real_T (*c3_ymin)[6];
  real_T (*c3_ymax)[6];
  real_T *c3_switch_in;
  real_T (*c3_ext_mv)[5];
  real_T (*c3_MVtarget)[5];
  real_T (*c3_ywt)[6];
  real_T (*c3_uwt)[5];
  real_T (*c3_duwt)[5];
  real_T *c3_rhoeps;
  boolean_T (*c3_iA)[221];
  real_T (*c3_d_u)[5];
  real_T *c3_cost;
  real_T (*c3_useq)[100];
  real_T *c3_status;
  real_T (*c3_xest)[13];
  boolean_T (*c3_iAout)[221];
} SFc3_mpclibInstanceStruct;

#endif                                 /*typedef_SFc3_mpclibInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c3_mpclib_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c3_mpclib_get_check_sum(mxArray *plhs[]);
extern void c3_mpclib_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
