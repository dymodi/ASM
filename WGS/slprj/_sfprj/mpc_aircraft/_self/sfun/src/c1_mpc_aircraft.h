#ifndef __c1_mpc_aircraft_h__
#define __c1_mpc_aircraft_h__

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

#ifndef typedef_SFc1_mpc_aircraftInstanceStruct
#define typedef_SFc1_mpc_aircraftInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  boolean_T c1_isStable;
  boolean_T c1_doneDoubleBufferReInit;
  uint8_T c1_is_active_c1_mpc_aircraft;
  real_T (*c1_f)[6];
  real_T (*c1_H)[25];
  real_T (*c1_F)[50];
  real_T (*c1_G)[60];
  real_T (*c1_S)[120];
  real_T (*c1_s)[12];
  real_T (*c1_u)[2];
  real_T (*c1_feasRes)[12];
  real_T (*c1_M)[12];
  real_T (*c1_L)[12];
  real_T (*c1_xk1k)[6];
  real_T (*c1_A)[36];
  real_T (*c1_B)[12];
  real_T (*c1_C)[12];
  real_T (*c1_xkk1)[6];
  real_T *c1_time;
  real_T *c1_iter;
} SFc1_mpc_aircraftInstanceStruct;

#endif                                 /*typedef_SFc1_mpc_aircraftInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_mpc_aircraft_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_mpc_aircraft_get_check_sum(mxArray *plhs[]);
extern void c1_mpc_aircraft_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
