#ifndef __c1_mpc_tmpdemo2_h__
#define __c1_mpc_tmpdemo2_h__

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

#ifndef typedef_c1_sflJsObR9dsqNm7nhVXYguC
#define typedef_c1_sflJsObR9dsqNm7nhVXYguC

typedef struct sflJsObR9dsqNm7nhVXYguC c1_sflJsObR9dsqNm7nhVXYguC;

#endif                                 /*typedef_c1_sflJsObR9dsqNm7nhVXYguC*/

#ifndef typedef_SFc1_mpc_tmpdemo2InstanceStruct
#define typedef_SFc1_mpc_tmpdemo2InstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  boolean_T c1_isStable;
  boolean_T c1_doneDoubleBufferReInit;
  uint8_T c1_is_active_c1_mpc_tmpdemo2;
  real_T c1_G[5070];
  real_T (*c1_f)[17];
  real_T (*c1_H)[676];
  real_T (*c1_F)[468];
  real_T (*c1_b_G)[5070];
  real_T (*c1_S)[3510];
  real_T (*c1_s)[195];
  real_T (*c1_u)[5];
  real_T (*c1_feasRes)[195];
  real_T (*c1_M)[42];
  real_T (*c1_L)[42];
  real_T (*c1_xk1k)[7];
  real_T (*c1_A)[49];
  real_T (*c1_B)[35];
  real_T (*c1_C)[42];
  real_T (*c1_xkk1)[7];
  real_T *c1_time;
} SFc1_mpc_tmpdemo2InstanceStruct;

#endif                                 /*typedef_SFc1_mpc_tmpdemo2InstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_mpc_tmpdemo2_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_mpc_tmpdemo2_get_check_sum(mxArray *plhs[]);
extern void c1_mpc_tmpdemo2_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
