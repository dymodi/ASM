#ifndef __c2_mpc_tmpdemo_2014b_h__
#define __c2_mpc_tmpdemo_2014b_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef struct_sflJsObR9dsqNm7nhVXYguC
#define struct_sflJsObR9dsqNm7nhVXYguC

struct sflJsObR9dsqNm7nhVXYguC
{
  char_T Algorithm[21];
  real_T MaxIter;
  real_T TolCon;
  real_T TolFun;
  real_T TolX;
  char_T Display[4];
};

#endif                                 /*struct_sflJsObR9dsqNm7nhVXYguC*/

#ifndef typedef_c2_sflJsObR9dsqNm7nhVXYguC
#define typedef_c2_sflJsObR9dsqNm7nhVXYguC

typedef struct sflJsObR9dsqNm7nhVXYguC c2_sflJsObR9dsqNm7nhVXYguC;

#endif                                 /*typedef_c2_sflJsObR9dsqNm7nhVXYguC*/

#ifndef typedef_SFc2_mpc_tmpdemo_2014bInstanceStruct
#define typedef_SFc2_mpc_tmpdemo_2014bInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_isStable;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_mpc_tmpdemo_2014b;
  real_T c2_G[5070];
  real_T c2_u[5070];
  real_T (*c2_f)[17];
  real_T (*c2_H)[676];
  real_T (*c2_F)[468];
  real_T (*c2_b_G)[5070];
  real_T (*c2_S)[3510];
  real_T (*c2_s)[195];
  real_T (*c2_b_u)[5];
  real_T (*c2_feasRes)[195];
  real_T (*c2_M)[42];
  real_T (*c2_L)[42];
  real_T (*c2_xk1k)[7];
  real_T (*c2_A)[49];
  real_T (*c2_B)[35];
  real_T (*c2_C)[42];
  real_T (*c2_xkk1)[7];
  real_T *c2_time;
} SFc2_mpc_tmpdemo_2014bInstanceStruct;

#endif                                 /*typedef_SFc2_mpc_tmpdemo_2014bInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_mpc_tmpdemo_2014b_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c2_mpc_tmpdemo_2014b_get_check_sum(mxArray *plhs[]);
extern void c2_mpc_tmpdemo_2014b_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
