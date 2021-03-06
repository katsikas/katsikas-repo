#ifndef __c3_commdvbc_h__
#define __c3_commdvbc_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
typedef struct {
  int32_T c3_sfEvent;
  boolean_T c3_isStable;
  boolean_T c3_doneDoubleBufferReInit;
  uint8_T c3_is_active_c3_commdvbc;
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  boolean_T c3_I_kMinusOne;
  boolean_T c3_I_kMinusOne_not_empty;
  boolean_T c3_Q_kMinusOne;
  boolean_T c3_Q_kMinusOne_not_empty;
} SFc3_commdvbcInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c3_commdvbc_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c3_commdvbc_get_check_sum(mxArray *plhs[]);
extern void c3_commdvbc_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
