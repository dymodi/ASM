#ifndef __c4_mpc_aircraft_h__
#define __c4_mpc_aircraft_h__

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

#ifndef typedef_c4_sflJsObR9dsqNm7nhVXYguC
#define typedef_c4_sflJsObR9dsqNm7nhVXYguC

typedef struct sflJsObR9dsqNm7nhVXYguC c4_sflJsObR9dsqNm7nhVXYguC;

#endif                                 /*typedef_c4_sflJsObR9dsqNm7nhVXYguC*/

#ifndef struct_sTH1uaqaUOn3AI0zmFyKbPF
#define struct_sTH1uaqaUOn3AI0zmFyKbPF

struct sTH1uaqaUOn3AI0zmFyKbPF
{
  char_T message[912];
  char_T algorithm[21];
  real_T firstorderopt;
  real_T constrviolation;
  real_T iterations;
};

#endif                                 /*struct_sTH1uaqaUOn3AI0zmFyKbPF*/

#ifndef typedef_c4_sTH1uaqaUOn3AI0zmFyKbPF
#define typedef_c4_sTH1uaqaUOn3AI0zmFyKbPF

typedef struct sTH1uaqaUOn3AI0zmFyKbPF c4_sTH1uaqaUOn3AI0zmFyKbPF;

#endif                                 /*typedef_c4_sTH1uaqaUOn3AI0zmFyKbPF*/

#ifndef typedef_SFc4_mpc_aircraftInstanceStruct
#define typedef_SFc4_mpc_aircraftInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c4_sfEvent;
  boolean_T c4_isStable;
  boolean_T c4_doneDoubleBufferReInit;
  uint8_T c4_is_active_c4_mpc_aircraft;
  real_T (*c4_f)[6];
  real_T (*c4_H)[25];
  real_T (*c4_F)[50];
  real_T (*c4_G)[60];
  real_T (*c4_S)[120];
  real_T (*c4_s)[12];
  real_T (*c4_u)[2];
  real_T (*c4_feasRes)[12];
  real_T (*c4_M)[12];
  real_T (*c4_L)[12];
  real_T (*c4_xk1k)[6];
  real_T (*c4_A)[36];
  real_T (*c4_B)[12];
  real_T (*c4_C)[12];
  real_T (*c4_xkk1)[6];
  real_T *c4_time;
  real_T *c4_iter;
} SFc4_mpc_aircraftInstanceStruct;

#endif                                 /*typedef_SFc4_mpc_aircraftInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c4_mpc_aircraft_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c4_mpc_aircraft_get_check_sum(mxArray *plhs[]);
extern void c4_mpc_aircraft_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
