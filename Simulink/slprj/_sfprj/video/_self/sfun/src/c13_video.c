/* Include files */

#include "blascompat32.h"
#include "video_sfun.h"
#include "c13_video.h"
#include "mwmathutil.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void initialize_c13_video(SFc13_videoInstanceStruct *chartInstance);
static void initialize_params_c13_video(SFc13_videoInstanceStruct *chartInstance);
static void enable_c13_video(SFc13_videoInstanceStruct *chartInstance);
static void disable_c13_video(SFc13_videoInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c13_video(SFc13_videoInstanceStruct
  *chartInstance);
static void set_sim_state_c13_video(SFc13_videoInstanceStruct *chartInstance,
  const mxArray *c13_st);
static void finalize_c13_video(SFc13_videoInstanceStruct *chartInstance);
static void sf_c13_video(SFc13_videoInstanceStruct *chartInstance);
static void c13_chartstep_c13_video(SFc13_videoInstanceStruct *chartInstance);
static void initSimStructsc13_video(SFc13_videoInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c13_machineNumber, uint32_T
  c13_chartNumber);
static void c13_info_helper(c13_ResolvedFunctionInfo c13_info[16]);
static void c13_eml_error(SFc13_videoInstanceStruct *chartInstance);
static void c13_emlrt_marshallIn(SFc13_videoInstanceStruct *chartInstance, const
  mxArray *c13_out, const char_T *c13_identifier, uint32_T c13_y[20]);
static void c13_b_emlrt_marshallIn(SFc13_videoInstanceStruct *chartInstance,
  const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId, uint32_T c13_y
  [20]);
static void c13_c_emlrt_marshallIn(SFc13_videoInstanceStruct *chartInstance,
  const mxArray *c13_b_prev_out, const char_T *c13_identifier, uint32_T c13_y[20]);
static void c13_d_emlrt_marshallIn(SFc13_videoInstanceStruct *chartInstance,
  const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId, uint32_T c13_y
  [20]);
static uint8_T c13_e_emlrt_marshallIn(SFc13_videoInstanceStruct *chartInstance,
  const mxArray *c13_b_is_active_c13_video, const char_T *c13_identifier);
static uint8_T c13_f_emlrt_marshallIn(SFc13_videoInstanceStruct *chartInstance,
  const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId);
static void c13_putbits(SFc13_videoInstanceStruct *chartInstance, int32_T
  c13_bitpos, uint32_T c13_out[20], uint32_T c13_Temp, real_T c13_outpos,
  uint32_T c13_val, real_T c13_bits, real_T *c13_flag, int32_T *c13_bitposO,
  uint32_T *c13_TempO, real_T *c13_outposO);
static void init_dsm_address_info(SFc13_videoInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c13_video(SFc13_videoInstanceStruct *chartInstance)
{
  int32_T c13_i0;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c13_prev_out_not_empty = FALSE;
  chartInstance->c13_is_active_c13_video = 0U;
  for (c13_i0 = 0; c13_i0 < 20; c13_i0++) {
    chartInstance->c13_prev_out[c13_i0] = 0U;
  }
}

static void initialize_params_c13_video(SFc13_videoInstanceStruct *chartInstance)
{
}

static void enable_c13_video(SFc13_videoInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c13_video(SFc13_videoInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static const mxArray *get_sim_state_c13_video(SFc13_videoInstanceStruct
  *chartInstance)
{
  const mxArray *c13_st;
  const mxArray *c13_y = NULL;
  int32_T c13_i1;
  uint32_T c13_u[20];
  const mxArray *c13_b_y = NULL;
  uint32_T c13_b_u[20];
  const mxArray *c13_c_y = NULL;
  uint8_T c13_c_u;
  const mxArray *c13_d_y = NULL;
  uint32_T (*c13_out)[20];
  c13_out = (uint32_T (*)[20])ssGetOutputPortSignal(chartInstance->S, 1);
  c13_st = NULL;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_createcellarray(3));
  for (c13_i1 = 0; c13_i1 < 20; c13_i1++) {
    c13_u[c13_i1] = (*c13_out)[c13_i1];
  }

  c13_b_y = NULL;
  sf_mex_assign(&c13_b_y, sf_mex_create("y", c13_u, 7, 0U, 1U, 0U, 1, 20));
  sf_mex_setcell(c13_y, 0, c13_b_y);
  for (c13_i1 = 0; c13_i1 < 20; c13_i1++) {
    c13_b_u[c13_i1] = chartInstance->c13_prev_out[c13_i1];
  }

  c13_c_y = NULL;
  if (!chartInstance->c13_prev_out_not_empty) {
    sf_mex_assign(&c13_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c13_c_y, sf_mex_create("y", c13_b_u, 7, 0U, 1U, 0U, 1, 20));
  }

  sf_mex_setcell(c13_y, 1, c13_c_y);
  c13_c_u = chartInstance->c13_is_active_c13_video;
  c13_d_y = NULL;
  sf_mex_assign(&c13_d_y, sf_mex_create("y", &c13_c_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c13_y, 2, c13_d_y);
  sf_mex_assign(&c13_st, c13_y);
  return c13_st;
}

static void set_sim_state_c13_video(SFc13_videoInstanceStruct *chartInstance,
  const mxArray *c13_st)
{
  const mxArray *c13_u;
  uint32_T c13_uv0[20];
  int32_T c13_i2;
  uint32_T (*c13_out)[20];
  c13_out = (uint32_T (*)[20])ssGetOutputPortSignal(chartInstance->S, 1);
  c13_u = sf_mex_dup(c13_st);
  c13_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c13_u, 0)),
                       "out", c13_uv0);
  for (c13_i2 = 0; c13_i2 < 20; c13_i2++) {
    (*c13_out)[c13_i2] = c13_uv0[c13_i2];
  }

  c13_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c13_u, 1)),
    "prev_out", c13_uv0);
  for (c13_i2 = 0; c13_i2 < 20; c13_i2++) {
    chartInstance->c13_prev_out[c13_i2] = c13_uv0[c13_i2];
  }

  chartInstance->c13_is_active_c13_video = c13_e_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c13_u, 2)), "is_active_c13_video");
  sf_mex_destroy(&c13_u);
  sf_mex_destroy(&c13_st);
}

static void finalize_c13_video(SFc13_videoInstanceStruct *chartInstance)
{
}

static void sf_c13_video(SFc13_videoInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  c13_chartstep_c13_video(chartInstance);
}

static void c13_chartstep_c13_video(SFc13_videoInstanceStruct *chartInstance)
{
  int32_T c13_out1;
  real32_T c13_in[64];
  uint32_T c13_out[20];
  int32_T c13_bitpos;
  uint32_T c13_Temp;
  real_T c13_outpos;
  real32_T c13_cval;
  real32_T c13_pval;
  int32_T c13_bitsIn;
  int32_T c13_exitg1;
  boolean_T c13_guard1 = FALSE;
  real_T c13_b_outpos;
  uint32_T c13_b_Temp;
  int32_T c13_b_bitpos;
  real_T c13_flag;
  uint32_T c13_valIn;
  int64_T c13_i3;
  boolean_T c13_guard2 = FALSE;
  uint8_T c13_absk1;
  boolean_T c13_b_guard1 = FALSE;
  uint32_T (*c13_b_out)[20];
  real32_T (*c13_b_in)[64];
  c13_b_out = (uint32_T (*)[20])ssGetOutputPortSignal(chartInstance->S, 1);
  c13_b_in = (real32_T (*)[64])ssGetInputPortSignal(chartInstance->S, 0);
  for (c13_out1 = 0; c13_out1 < 64; c13_out1++) {
    c13_in[c13_out1] = (*c13_b_in)[c13_out1];
  }

  chartInstance->c13_prev_out_not_empty = TRUE;
  for (c13_out1 = 0; c13_out1 < 20; c13_out1++) {
    c13_out[c13_out1] = chartInstance->c13_prev_out[c13_out1];
  }

  c13_bitpos = 0;
  c13_Temp = 0U;
  c13_outpos = 2.0;
  if ((real_T)(*c13_b_in)[0] > 0.0) {
    c13_cval = muSingleScalarFloor((*c13_b_in)[0]);
  } else {
    c13_cval = muSingleScalarCeil((*c13_b_in)[0]);
  }

  if ((c13_cval < 8.388608E+6F) && (c13_cval > -8.388608E+6F)) {
    c13_cval = (real_T)c13_cval < 0.0 ? muSingleScalarCeil(c13_cval - 0.5F) :
      muSingleScalarFloor(c13_cval + 0.5F);
  }

  if (c13_cval < 2.14748365E+9F) {
    if (c13_cval >= -2.14748365E+9F) {
      c13_out1 = (int32_T)c13_cval;
    } else {
      c13_out1 = MIN_int32_T;
    }
  } else if (c13_cval >= 2.14748365E+9F) {
    c13_out1 = MAX_int32_T;
  } else {
    c13_out1 = 0;
  }

  if (c13_out1 >= -1) {
    if (c13_out1 <= 0) {
      c13_out1 = 0;
    }

    c13_out[0] = (uint32_T)c13_out1;
  } else {
    if (c13_out1 <= MIN_int32_T) {
      c13_out1 = MAX_int32_T;
    } else {
      c13_out1 = -c13_out1;
    }

    c13_out[0] = 1U - (uint32_T)c13_out1;
  }

  c13_cval = (*c13_b_in)[1] + 0.5F;
  if ((real_T)c13_cval > 0.0) {
    c13_pval = muSingleScalarFloor(c13_cval);
  } else {
    c13_pval = muSingleScalarCeil(c13_cval);
  }

  if ((real_T)c13_pval > 127.0) {
    c13_pval = 127.0F;
  }

  if ((real_T)c13_pval < -128.0) {
    c13_pval = -128.0F;
  }

  c13_out1 = 0;
  c13_bitsIn = 3;
  do {
    c13_exitg1 = 0U;
    if (c13_bitsIn <= 64) {
      c13_cval = c13_in[c13_bitsIn - 1] + 0.5F;
      c13_cval = muSingleScalarFloor(c13_cval);
      c13_guard1 = FALSE;
      if ((c13_pval == c13_cval) && (c13_out1 < 14)) {
        c13_out1 = (int32_T)((uint32_T)c13_out1 + 1U);
        c13_guard1 = TRUE;
      } else {
        c13_putbits(chartInstance, c13_bitpos, c13_out, c13_Temp, c13_outpos,
                    (uint32_T)c13_out1, 4.0, &c13_flag, &c13_b_bitpos,
                    &c13_b_Temp, &c13_b_outpos);
        if (!(c13_flag != 0.0)) {
          for (c13_out1 = 0; c13_out1 < 20; c13_out1++) {
            chartInstance->c13_prev_out[c13_out1] = c13_out[c13_out1];
          }

          c13_exitg1 = 1U;
        } else {
          if ((real_T)c13_pval > 127.0) {
            c13_pval = 127.0F;
          }

          if ((real_T)c13_pval < -128.0) {
            c13_pval = -128.0F;
          }

          c13_pval += 128.0F;
          if ((c13_pval < 8.388608E+6F) && (c13_pval > -8.388608E+6F)) {
            c13_pval = muSingleScalarFloor(c13_pval + 0.5F);
          }

          if (c13_pval < 4.2949673E+9F) {
            c13_valIn = (uint32_T)c13_pval;
          } else {
            c13_valIn = 0U;
          }

          c13_putbits(chartInstance, c13_b_bitpos, c13_out, c13_b_Temp,
                      c13_b_outpos, c13_valIn, 8.0, &c13_flag, &c13_bitpos,
                      &c13_Temp, &c13_outpos);
          if (!(c13_flag != 0.0)) {
            for (c13_out1 = 0; c13_out1 < 20; c13_out1++) {
              chartInstance->c13_prev_out[c13_out1] = c13_out[c13_out1];
            }

            c13_exitg1 = 1U;
          } else {
            c13_out1 = 0;
            c13_guard1 = TRUE;
          }
        }
      }

      if (c13_guard1 == TRUE) {
        c13_pval = c13_cval;
        c13_bitsIn++;
        sf_mex_listen_for_ctrl_c(chartInstance->S);
      }
    } else {
      c13_putbits(chartInstance, c13_bitpos, c13_out, c13_Temp, c13_outpos,
                  (uint32_T)c13_out1, 4.0, &c13_flag, &c13_b_bitpos, &c13_b_Temp,
                  &c13_b_outpos);
      if (!(c13_flag != 0.0)) {
        for (c13_out1 = 0; c13_out1 < 20; c13_out1++) {
          chartInstance->c13_prev_out[c13_out1] = c13_out[c13_out1];
        }
      } else {
        if ((real_T)c13_pval > 127.0) {
          c13_pval = 127.0F;
        }

        if ((real_T)c13_pval < -128.0) {
          c13_pval = -128.0F;
        }

        c13_pval += 128.0F;
        if ((c13_pval < 8.388608E+6F) && (c13_pval > -8.388608E+6F)) {
          c13_pval = muSingleScalarFloor(c13_pval + 0.5F);
        }

        if (c13_pval < 4.2949673E+9F) {
          c13_valIn = (uint32_T)c13_pval;
        } else {
          c13_valIn = 0U;
        }

        c13_bitsIn = 8;
        c13_i3 = (int64_T)c13_b_bitpos + (int64_T)8;
        if (c13_i3 > 2147483647L) {
          c13_i3 = 2147483647L;
        } else {
          if (c13_i3 <= -2147483648L) {
            c13_i3 = -2147483648L;
          }
        }

        c13_guard2 = FALSE;
        if ((int32_T)c13_i3 > 32) {
          c13_i3 = (int64_T)32 - (int64_T)c13_b_bitpos;
          if (c13_i3 > 2147483647L) {
            c13_i3 = 2147483647L;
          } else {
            if (c13_i3 <= -2147483648L) {
              c13_i3 = -2147483648L;
            }
          }

          c13_bitsIn = (int32_T)c13_i3 - 8;
          c13_out1 = -(-c13_bitsIn);
          c13_Temp = 0U;
          if (c13_out1 < 0) {
            c13_out1 = -c13_out1;
            if (c13_out1 <= 0) {
              c13_out1 = 0;
            } else {
              if (c13_out1 > 255) {
                c13_out1 = 255;
              }
            }

            c13_absk1 = (uint8_T)c13_out1;
            if (c13_absk1 < 32) {
              c13_Temp = c13_valIn >> (uint32_T)c13_absk1;
            }
          } else {
            if (c13_out1 <= 0) {
              c13_out1 = 0;
            } else {
              if (c13_out1 > 255) {
                c13_out1 = 255;
              }
            }

            c13_absk1 = (uint8_T)c13_out1;
            if (c13_absk1 < 32) {
              c13_Temp = c13_valIn << (uint32_T)c13_absk1;
            }
          }

          c13_b_Temp |= c13_Temp;
          c13_out[sf_mex_lw_bounds_check((int32_T)c13_b_outpos, 1, 20) - 1] =
            c13_b_Temp;
          c13_b_outpos++;
          if (c13_b_outpos > 20.0) {
            c13_out1 = 0;
          } else {
            c13_b_Temp = 0U;
            c13_b_bitpos = 0;
            c13_bitsIn = -c13_bitsIn;
            c13_Temp = c13_valIn;
            c13_i3 = (int64_T)32 - (int64_T)c13_bitsIn;
            if (c13_i3 > 2147483647L) {
              c13_i3 = 2147483647L;
            } else {
              if (c13_i3 <= -2147483648L) {
                c13_i3 = -2147483648L;
              }
            }

            c13_out1 = (int32_T)c13_i3;
            c13_valIn = 0U;
            if (c13_out1 < 0) {
              c13_out1 = -c13_out1;
              if (c13_out1 <= 0) {
                c13_out1 = 0;
              } else {
                if (c13_out1 > 255) {
                  c13_out1 = 255;
                }
              }

              c13_absk1 = (uint8_T)c13_out1;
              if (c13_absk1 < 32) {
                c13_valIn = c13_Temp >> (uint32_T)c13_absk1;
              }
            } else {
              if (c13_out1 <= 0) {
                c13_out1 = 0;
              } else {
                if (c13_out1 > 255) {
                  c13_out1 = 255;
                }
              }

              c13_absk1 = (uint8_T)c13_out1;
              if (c13_absk1 < 32) {
                c13_valIn = c13_Temp << (uint32_T)c13_absk1;
              }
            }

            c13_Temp = c13_valIn;
            c13_i3 = (int64_T)32 - (int64_T)c13_bitsIn;
            if (c13_i3 > 2147483647L) {
              c13_i3 = 2147483647L;
            } else {
              if (c13_i3 <= -2147483648L) {
                c13_i3 = -2147483648L;
              }
            }

            c13_out1 = -(int32_T)c13_i3;
            c13_valIn = 0U;
            if (c13_out1 < 0) {
              c13_out1 = -c13_out1;
              if (c13_out1 <= 0) {
                c13_out1 = 0;
              } else {
                if (c13_out1 > 255) {
                  c13_out1 = 255;
                }
              }

              c13_absk1 = (uint8_T)c13_out1;
              if (c13_absk1 < 32) {
                c13_valIn = c13_Temp >> (uint32_T)c13_absk1;
              }
            } else {
              if (c13_out1 <= 0) {
                c13_out1 = 0;
              } else {
                if (c13_out1 > 255) {
                  c13_out1 = 255;
                }
              }

              c13_absk1 = (uint8_T)c13_out1;
              if (c13_absk1 < 32) {
                c13_valIn = c13_Temp << (uint32_T)c13_absk1;
              }
            }

            c13_guard2 = TRUE;
          }
        } else {
          c13_guard2 = TRUE;
        }

        if (c13_guard2 == TRUE) {
          c13_Temp = c13_valIn;
          c13_i3 = (int64_T)c13_bitsIn + (int64_T)c13_b_bitpos;
          if (c13_i3 > 2147483647L) {
            c13_i3 = 2147483647L;
          } else {
            if (c13_i3 <= -2147483648L) {
              c13_i3 = -2147483648L;
            }
          }

          c13_i3 = (int64_T)32 - (int64_T)(int32_T)c13_i3;
          if (c13_i3 > 2147483647L) {
            c13_i3 = 2147483647L;
          } else {
            if (c13_i3 <= -2147483648L) {
              c13_i3 = -2147483648L;
            }
          }

          c13_out1 = (int32_T)c13_i3;
          c13_valIn = 0U;
          if (c13_out1 < 0) {
            c13_out1 = -c13_out1;
            if (c13_out1 <= 0) {
              c13_out1 = 0;
            } else {
              if (c13_out1 > 255) {
                c13_out1 = 255;
              }
            }

            c13_absk1 = (uint8_T)c13_out1;
            if (c13_absk1 < 32) {
              c13_valIn = c13_Temp >> (uint32_T)c13_absk1;
            }
          } else {
            if (c13_out1 <= 0) {
              c13_out1 = 0;
            } else {
              if (c13_out1 > 255) {
                c13_out1 = 255;
              }
            }

            c13_absk1 = (uint8_T)c13_out1;
            if (c13_absk1 < 32) {
              c13_valIn = c13_Temp << (uint32_T)c13_absk1;
            }
          }

          c13_b_Temp |= c13_valIn;
          c13_i3 = (int64_T)c13_b_bitpos + (int64_T)c13_bitsIn;
          if (c13_i3 > 2147483647L) {
            c13_i3 = 2147483647L;
          } else {
            if (c13_i3 <= -2147483648L) {
              c13_i3 = -2147483648L;
            }
          }

          c13_b_bitpos = (int32_T)c13_i3;
          c13_out1 = 1;
        }

        if (!(c13_out1 != 0)) {
          for (c13_out1 = 0; c13_out1 < 20; c13_out1++) {
            chartInstance->c13_prev_out[c13_out1] = c13_out[c13_out1];
          }
        } else {
          c13_valIn = 15U;
          c13_bitsIn = 4;
          c13_i3 = (int64_T)c13_b_bitpos + (int64_T)4;
          if (c13_i3 > 2147483647L) {
            c13_i3 = 2147483647L;
          } else {
            if (c13_i3 <= -2147483648L) {
              c13_i3 = -2147483648L;
            }
          }

          c13_b_guard1 = FALSE;
          if ((int32_T)c13_i3 > 32) {
            c13_i3 = (int64_T)32 - (int64_T)c13_b_bitpos;
            if (c13_i3 > 2147483647L) {
              c13_i3 = 2147483647L;
            } else {
              if (c13_i3 <= -2147483648L) {
                c13_i3 = -2147483648L;
              }
            }

            c13_bitsIn = (int32_T)c13_i3 - 4;
            c13_out1 = -(-c13_bitsIn);
            c13_Temp = 0U;
            if (c13_out1 < 0) {
              c13_out1 = -c13_out1;
              if (c13_out1 <= 0) {
                c13_out1 = 0;
              } else {
                if (c13_out1 > 255) {
                  c13_out1 = 255;
                }
              }

              c13_absk1 = (uint8_T)c13_out1;
              if (c13_absk1 < 32) {
                c13_Temp = 15U >> (uint32_T)c13_absk1;
              }
            } else {
              if (c13_out1 <= 0) {
                c13_out1 = 0;
              } else {
                if (c13_out1 > 255) {
                  c13_out1 = 255;
                }
              }

              c13_absk1 = (uint8_T)c13_out1;
              if (c13_absk1 < 32) {
                c13_Temp = 15U << (uint32_T)c13_absk1;
              }
            }

            c13_b_Temp |= c13_Temp;
            c13_out[sf_mex_lw_bounds_check((int32_T)c13_b_outpos, 1, 20) - 1] =
              c13_b_Temp;
            c13_b_outpos++;
            if (c13_b_outpos > 20.0) {
              c13_out1 = 0;
            } else {
              c13_b_Temp = 0U;
              c13_b_bitpos = 0;
              c13_bitsIn = -c13_bitsIn;
              c13_i3 = (int64_T)32 - (int64_T)c13_bitsIn;
              if (c13_i3 > 2147483647L) {
                c13_i3 = 2147483647L;
              } else {
                if (c13_i3 <= -2147483648L) {
                  c13_i3 = -2147483648L;
                }
              }

              c13_out1 = (int32_T)c13_i3;
              c13_valIn = 0U;
              if (c13_out1 < 0) {
                c13_out1 = -c13_out1;
                if (c13_out1 <= 0) {
                  c13_out1 = 0;
                } else {
                  if (c13_out1 > 255) {
                    c13_out1 = 255;
                  }
                }

                c13_absk1 = (uint8_T)c13_out1;
                if (c13_absk1 < 32) {
                  c13_valIn = 15U >> (uint32_T)c13_absk1;
                }
              } else {
                if (c13_out1 <= 0) {
                  c13_out1 = 0;
                } else {
                  if (c13_out1 > 255) {
                    c13_out1 = 255;
                  }
                }

                c13_absk1 = (uint8_T)c13_out1;
                if (c13_absk1 < 32) {
                  c13_valIn = 15U << (uint32_T)c13_absk1;
                }
              }

              c13_Temp = c13_valIn;
              c13_i3 = (int64_T)32 - (int64_T)c13_bitsIn;
              if (c13_i3 > 2147483647L) {
                c13_i3 = 2147483647L;
              } else {
                if (c13_i3 <= -2147483648L) {
                  c13_i3 = -2147483648L;
                }
              }

              c13_out1 = -(int32_T)c13_i3;
              c13_valIn = 0U;
              if (c13_out1 < 0) {
                c13_out1 = -c13_out1;
                if (c13_out1 <= 0) {
                  c13_out1 = 0;
                } else {
                  if (c13_out1 > 255) {
                    c13_out1 = 255;
                  }
                }

                c13_absk1 = (uint8_T)c13_out1;
                if (c13_absk1 < 32) {
                  c13_valIn = c13_Temp >> (uint32_T)c13_absk1;
                }
              } else {
                if (c13_out1 <= 0) {
                  c13_out1 = 0;
                } else {
                  if (c13_out1 > 255) {
                    c13_out1 = 255;
                  }
                }

                c13_absk1 = (uint8_T)c13_out1;
                if (c13_absk1 < 32) {
                  c13_valIn = c13_Temp << (uint32_T)c13_absk1;
                }
              }

              c13_b_guard1 = TRUE;
            }
          } else {
            c13_b_guard1 = TRUE;
          }

          if (c13_b_guard1 == TRUE) {
            c13_Temp = c13_valIn;
            c13_i3 = (int64_T)c13_bitsIn + (int64_T)c13_b_bitpos;
            if (c13_i3 > 2147483647L) {
              c13_i3 = 2147483647L;
            } else {
              if (c13_i3 <= -2147483648L) {
                c13_i3 = -2147483648L;
              }
            }

            c13_i3 = (int64_T)32 - (int64_T)(int32_T)c13_i3;
            if (c13_i3 > 2147483647L) {
              c13_i3 = 2147483647L;
            } else {
              if (c13_i3 <= -2147483648L) {
                c13_i3 = -2147483648L;
              }
            }

            c13_out1 = (int32_T)c13_i3;
            c13_valIn = 0U;
            if (c13_out1 < 0) {
              c13_out1 = -c13_out1;
              if (c13_out1 <= 0) {
                c13_out1 = 0;
              } else {
                if (c13_out1 > 255) {
                  c13_out1 = 255;
                }
              }

              c13_absk1 = (uint8_T)c13_out1;
              if (c13_absk1 < 32) {
                c13_valIn = c13_Temp >> (uint32_T)c13_absk1;
              }
            } else {
              if (c13_out1 <= 0) {
                c13_out1 = 0;
              } else {
                if (c13_out1 > 255) {
                  c13_out1 = 255;
                }
              }

              c13_absk1 = (uint8_T)c13_out1;
              if (c13_absk1 < 32) {
                c13_valIn = c13_Temp << (uint32_T)c13_absk1;
              }
            }

            c13_b_Temp |= c13_valIn;
            c13_out1 = 1;
          }

          if ((c13_out1 != 0) && (!(c13_b_outpos > 21.0))) {
            c13_out[sf_mex_lw_bounds_check((int32_T)c13_b_outpos, 1, 20) - 1] =
              c13_b_Temp;
          }

          for (c13_out1 = 0; c13_out1 < 20; c13_out1++) {
            chartInstance->c13_prev_out[c13_out1] = c13_out[c13_out1];
          }
        }
      }

      c13_exitg1 = 1U;
    }
  } while (c13_exitg1 == 0U);

  for (c13_out1 = 0; c13_out1 < 20; c13_out1++) {
    (*c13_b_out)[c13_out1] = c13_out[c13_out1];
  }
}

static void initSimStructsc13_video(SFc13_videoInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c13_machineNumber, uint32_T
  c13_chartNumber)
{
}

const mxArray *sf_c13_video_get_eml_resolved_functions_info(void)
{
  const mxArray *c13_nameCaptureInfo;
  c13_ResolvedFunctionInfo c13_info[16];
  const mxArray *c13_m0 = NULL;
  int32_T c13_i4;
  c13_ResolvedFunctionInfo *c13_r0;
  c13_nameCaptureInfo = NULL;
  c13_info_helper(c13_info);
  sf_mex_assign(&c13_m0, sf_mex_createstruct("nameCaptureInfo", 1, 16));
  for (c13_i4 = 0; c13_i4 < 16; c13_i4++) {
    c13_r0 = &c13_info[c13_i4];
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo", c13_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c13_r0->context)), "context", "nameCaptureInfo",
                    c13_i4);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo", c13_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c13_r0->name)), "name", "nameCaptureInfo", c13_i4);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo",
      c13_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c13_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c13_i4);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo", c13_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c13_r0->resolved)), "resolved",
                    "nameCaptureInfo", c13_i4);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo", &c13_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c13_i4);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo", &c13_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c13_i4);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo",
      &c13_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c13_i4);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo",
      &c13_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c13_i4);
  }

  sf_mex_assign(&c13_nameCaptureInfo, c13_m0);
  return c13_nameCaptureInfo;
}

static void c13_info_helper(c13_ResolvedFunctionInfo c13_info[16])
{
  c13_info[0].context = "";
  c13_info[0].name = "fix";
  c13_info[0].dominantType = "single";
  c13_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/fix.m";
  c13_info[0].fileTimeLo = 1286815142U;
  c13_info[0].fileTimeHi = 0U;
  c13_info[0].mFileTimeLo = 0U;
  c13_info[0].mFileTimeHi = 0U;
  c13_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/fix.m";
  c13_info[1].name = "eml_scalar_fix";
  c13_info[1].dominantType = "single";
  c13_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_fix.m";
  c13_info[1].fileTimeLo = 1286815126U;
  c13_info[1].fileTimeHi = 0U;
  c13_info[1].mFileTimeLo = 0U;
  c13_info[1].mFileTimeHi = 0U;
  c13_info[2].context = "";
  c13_info[2].name = "intmax";
  c13_info[2].dominantType = "char";
  c13_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c13_info[2].fileTimeLo = 1286815156U;
  c13_info[2].fileTimeHi = 0U;
  c13_info[2].mFileTimeLo = 0U;
  c13_info[2].mFileTimeHi = 0U;
  c13_info[3].context = "";
  c13_info[3].name = "abs";
  c13_info[3].dominantType = "int32";
  c13_info[3].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c13_info[3].fileTimeLo = 1286815094U;
  c13_info[3].fileTimeHi = 0U;
  c13_info[3].mFileTimeLo = 0U;
  c13_info[3].mFileTimeHi = 0U;
  c13_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c13_info[4].name = "eml_scalar_abs";
  c13_info[4].dominantType = "int32";
  c13_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c13_info[4].fileTimeLo = 1286815112U;
  c13_info[4].fileTimeHi = 0U;
  c13_info[4].mFileTimeLo = 0U;
  c13_info[4].mFileTimeHi = 0U;
  c13_info[5].context = "";
  c13_info[5].name = "floor";
  c13_info[5].dominantType = "single";
  c13_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c13_info[5].fileTimeLo = 1286815142U;
  c13_info[5].fileTimeHi = 0U;
  c13_info[5].mFileTimeLo = 0U;
  c13_info[5].mFileTimeHi = 0U;
  c13_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c13_info[6].name = "eml_scalar_floor";
  c13_info[6].dominantType = "single";
  c13_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c13_info[6].fileTimeLo = 1286815126U;
  c13_info[6].fileTimeHi = 0U;
  c13_info[6].mFileTimeLo = 0U;
  c13_info[6].mFileTimeHi = 0U;
  c13_info[7].context = "";
  c13_info[7].name = "bitshift";
  c13_info[7].dominantType = "uint32";
  c13_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c13_info[7].fileTimeLo = 1286815238U;
  c13_info[7].fileTimeHi = 0U;
  c13_info[7].mFileTimeLo = 0U;
  c13_info[7].mFileTimeHi = 0U;
  c13_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c13_info[8].name = "eml_isa_uint";
  c13_info[8].dominantType = "uint32";
  c13_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m";
  c13_info[8].fileTimeLo = 1286815184U;
  c13_info[8].fileTimeHi = 0U;
  c13_info[8].mFileTimeLo = 0U;
  c13_info[8].mFileTimeHi = 0U;
  c13_info[9].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c13_info[9].name = "eml_int_nbits";
  c13_info[9].dominantType = "char";
  c13_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_nbits.m";
  c13_info[9].fileTimeLo = 1286815180U;
  c13_info[9].fileTimeHi = 0U;
  c13_info[9].mFileTimeLo = 0U;
  c13_info[9].mFileTimeHi = 0U;
  c13_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c13_info[10].name = "eml_scalar_eg";
  c13_info[10].dominantType = "uint32";
  c13_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c13_info[10].fileTimeLo = 1286815196U;
  c13_info[10].fileTimeHi = 0U;
  c13_info[10].mFileTimeLo = 0U;
  c13_info[10].mFileTimeHi = 0U;
  c13_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c13_info[11].name = "eml_scalexp_alloc";
  c13_info[11].dominantType = "uint32";
  c13_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c13_info[11].fileTimeLo = 1286815196U;
  c13_info[11].fileTimeHi = 0U;
  c13_info[11].mFileTimeLo = 0U;
  c13_info[11].mFileTimeHi = 0U;
  c13_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitshift.m";
  c13_info[12].name = "eml_error";
  c13_info[12].dominantType = "char";
  c13_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c13_info[12].fileTimeLo = 1286815100U;
  c13_info[12].fileTimeHi = 0U;
  c13_info[12].mFileTimeLo = 0U;
  c13_info[12].mFileTimeHi = 0U;
  c13_info[13].context = "";
  c13_info[13].name = "bitor";
  c13_info[13].dominantType = "uint32";
  c13_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitor.m";
  c13_info[13].fileTimeLo = 1286815236U;
  c13_info[13].fileTimeHi = 0U;
  c13_info[13].mFileTimeLo = 0U;
  c13_info[13].mFileTimeHi = 0U;
  c13_info[14].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/bitor.m";
  c13_info[14].name = "eml_scalexp_compatible";
  c13_info[14].dominantType = "uint32";
  c13_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c13_info[14].fileTimeLo = 1286815196U;
  c13_info[14].fileTimeHi = 0U;
  c13_info[14].mFileTimeLo = 0U;
  c13_info[14].mFileTimeHi = 0U;
  c13_info[15].context = "";
  c13_info[15].name = "length";
  c13_info[15].dominantType = "uint32";
  c13_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c13_info[15].fileTimeLo = 1286815160U;
  c13_info[15].fileTimeHi = 0U;
  c13_info[15].mFileTimeLo = 0U;
  c13_info[15].mFileTimeHi = 0U;
}

static void c13_eml_error(SFc13_videoInstanceStruct *chartInstance)
{
  int32_T c13_i5;
  static char_T c13_varargin_1[42] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 'b', 'i', 't', 's', 'h', 'i', 'f', 't', '_', 'i',
    'n', 'p', 'u', 't', 's', 'M', 'u', 's', 't', 'B', 'e', 'I', 'n', 't', 'e',
    'g', 'e', 'r', 's' };

  char_T c13_u[42];
  const mxArray *c13_y = NULL;
  for (c13_i5 = 0; c13_i5 < 42; c13_i5++) {
    c13_u[c13_i5] = c13_varargin_1[c13_i5];
  }

  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u, 10, 0U, 1U, 0U, 2, 1, 42));
  sf_mex_call("error", 0U, 1U, 14, sf_mex_call("message", 1U, 1U, 14, c13_y));
}

static void c13_emlrt_marshallIn(SFc13_videoInstanceStruct *chartInstance, const
  mxArray *c13_out, const char_T *c13_identifier, uint32_T c13_y[20])
{
  emlrtMsgIdentifier c13_thisId;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_out), &c13_thisId, c13_y);
  sf_mex_destroy(&c13_out);
}

static void c13_b_emlrt_marshallIn(SFc13_videoInstanceStruct *chartInstance,
  const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId, uint32_T c13_y
  [20])
{
  uint32_T c13_uv1[20];
  int32_T c13_i6;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), c13_uv1, 1, 7, 0U, 1, 0U, 1, 20);
  for (c13_i6 = 0; c13_i6 < 20; c13_i6++) {
    c13_y[c13_i6] = c13_uv1[c13_i6];
  }

  sf_mex_destroy(&c13_u);
}

static void c13_c_emlrt_marshallIn(SFc13_videoInstanceStruct *chartInstance,
  const mxArray *c13_b_prev_out, const char_T *c13_identifier, uint32_T c13_y[20])
{
  emlrtMsgIdentifier c13_thisId;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_b_prev_out), &c13_thisId,
    c13_y);
  sf_mex_destroy(&c13_b_prev_out);
}

static void c13_d_emlrt_marshallIn(SFc13_videoInstanceStruct *chartInstance,
  const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId, uint32_T c13_y
  [20])
{
  uint32_T c13_uv2[20];
  int32_T c13_i7;
  if (mxIsEmpty(c13_u)) {
    chartInstance->c13_prev_out_not_empty = FALSE;
  } else {
    chartInstance->c13_prev_out_not_empty = TRUE;
    sf_mex_import(c13_parentId, sf_mex_dup(c13_u), c13_uv2, 1, 7, 0U, 1, 0U, 1,
                  20);
    for (c13_i7 = 0; c13_i7 < 20; c13_i7++) {
      c13_y[c13_i7] = c13_uv2[c13_i7];
    }
  }

  sf_mex_destroy(&c13_u);
}

static uint8_T c13_e_emlrt_marshallIn(SFc13_videoInstanceStruct *chartInstance,
  const mxArray *c13_b_is_active_c13_video, const char_T *c13_identifier)
{
  uint8_T c13_y;
  emlrtMsgIdentifier c13_thisId;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c13_b_is_active_c13_video), &c13_thisId);
  sf_mex_destroy(&c13_b_is_active_c13_video);
  return c13_y;
}

static uint8_T c13_f_emlrt_marshallIn(SFc13_videoInstanceStruct *chartInstance,
  const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId)
{
  uint8_T c13_y;
  uint8_T c13_u0;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), &c13_u0, 1, 3, 0U, 0, 0U, 0);
  c13_y = c13_u0;
  sf_mex_destroy(&c13_u);
  return c13_y;
}

static void c13_putbits(SFc13_videoInstanceStruct *chartInstance, int32_T
  c13_bitpos, uint32_T c13_out[20], uint32_T c13_Temp, real_T c13_outpos,
  uint32_T c13_val, real_T c13_bits, real_T *c13_flag, int32_T *c13_bitposO,
  uint32_T *c13_TempO, real_T *c13_outposO)
{
  uint32_T c13_valIn;
  real_T c13_d0;
  int32_T c13_bitsIn;
  int64_T c13_i8;
  boolean_T c13_guard1 = FALSE;
  int32_T c13_bitsleft;
  int32_T c13_saturatedUnaryMinus;
  uint8_T c13_absk1;
  uint32_T c13_a;
  c13_valIn = c13_val;
  c13_d0 = c13_bits;
  c13_d0 = c13_d0 < 0.0 ? muDoubleScalarCeil(c13_d0 - 0.5) : muDoubleScalarFloor
    (c13_d0 + 0.5);
  if (c13_d0 < 2.147483648E+9) {
    if (c13_d0 >= -2.147483648E+9) {
      c13_bitsIn = (int32_T)c13_d0;
    } else {
      c13_bitsIn = MIN_int32_T;
    }
  } else if (c13_d0 >= 2.147483648E+9) {
    c13_bitsIn = MAX_int32_T;
  } else {
    c13_bitsIn = 0;
  }

  *c13_bitposO = c13_bitpos;
  *c13_TempO = c13_Temp;
  *c13_outposO = c13_outpos;
  c13_i8 = (int64_T)c13_bitpos + (int64_T)c13_bitsIn;
  if (c13_i8 > 2147483647L) {
    c13_i8 = 2147483647L;
  } else {
    if (c13_i8 <= -2147483648L) {
      c13_i8 = -2147483648L;
    }
  }

  c13_guard1 = FALSE;
  if ((int32_T)c13_i8 > 32) {
    c13_i8 = (int64_T)32 - (int64_T)c13_bitpos;
    if (c13_i8 > 2147483647L) {
      c13_i8 = 2147483647L;
    } else {
      if (c13_i8 <= -2147483648L) {
        c13_i8 = -2147483648L;
      }
    }

    c13_bitsleft = (int32_T)c13_i8;
    c13_i8 = (int64_T)c13_bitsIn - (int64_T)c13_bitsleft;
    if (c13_i8 > 2147483647L) {
      c13_i8 = 2147483647L;
    } else {
      if (c13_i8 <= -2147483648L) {
        c13_i8 = -2147483648L;
      }
    }

    c13_saturatedUnaryMinus = (int32_T)c13_i8;
    if (c13_saturatedUnaryMinus <= MIN_int32_T) {
      c13_saturatedUnaryMinus = MAX_int32_T;
    } else {
      c13_saturatedUnaryMinus = -c13_saturatedUnaryMinus;
    }

    c13_valIn = 0U;
    if (c13_saturatedUnaryMinus < 0) {
      c13_saturatedUnaryMinus = -c13_saturatedUnaryMinus;
      if (c13_saturatedUnaryMinus > 255) {
        c13_saturatedUnaryMinus = 255;
      }

      c13_absk1 = (uint8_T)c13_saturatedUnaryMinus;
      if (c13_absk1 < 32) {
        c13_valIn = c13_val >> (uint32_T)c13_absk1;
      }
    } else {
      if (c13_saturatedUnaryMinus <= 0) {
        c13_saturatedUnaryMinus = 0;
      } else {
        if (c13_saturatedUnaryMinus > 255) {
          c13_saturatedUnaryMinus = 255;
        }
      }

      c13_absk1 = (uint8_T)c13_saturatedUnaryMinus;
      if (c13_absk1 < 32) {
        c13_valIn = c13_val << (uint32_T)c13_absk1;
      }
    }

    *c13_TempO = c13_Temp | c13_valIn;
    c13_out[sf_mex_lw_bounds_check((int32_T)c13_outpos, 1, 20) - 1] = *c13_TempO;
    *c13_outposO = c13_outpos + 1.0;
    if (*c13_outposO > 20.0) {
      *c13_flag = 0.0;
    } else {
      *c13_TempO = 0U;
      *c13_bitposO = 0;
      c13_i8 = (int64_T)c13_bitsIn - (int64_T)c13_bitsleft;
      if (c13_i8 > 2147483647L) {
        c13_i8 = 2147483647L;
      } else {
        if (c13_i8 <= -2147483648L) {
          c13_i8 = -2147483648L;
        }
      }

      c13_bitsIn = (int32_T)c13_i8;
      c13_i8 = (int64_T)32 - (int64_T)c13_bitsIn;
      if (c13_i8 > 2147483647L) {
        c13_i8 = 2147483647L;
      } else {
        if (c13_i8 <= -2147483648L) {
          c13_i8 = -2147483648L;
        }
      }

      c13_saturatedUnaryMinus = (int32_T)c13_i8;
      c13_valIn = 0U;
      if (c13_saturatedUnaryMinus < 0) {
        c13_saturatedUnaryMinus = -c13_saturatedUnaryMinus;
        if (c13_saturatedUnaryMinus <= 0) {
          c13_saturatedUnaryMinus = 0;
        } else {
          if (c13_saturatedUnaryMinus > 255) {
            c13_saturatedUnaryMinus = 255;
          }
        }

        c13_absk1 = (uint8_T)c13_saturatedUnaryMinus;
        if (c13_absk1 < 32) {
          c13_valIn = c13_val >> (uint32_T)c13_absk1;
        }
      } else {
        if (c13_saturatedUnaryMinus <= 0) {
          c13_saturatedUnaryMinus = 0;
        } else {
          if (c13_saturatedUnaryMinus > 255) {
            c13_saturatedUnaryMinus = 255;
          }
        }

        c13_absk1 = (uint8_T)c13_saturatedUnaryMinus;
        if (c13_absk1 < 32) {
          c13_valIn = c13_val << (uint32_T)c13_absk1;
        }
      }

      c13_a = c13_valIn;
      c13_i8 = (int64_T)32 - (int64_T)c13_bitsIn;
      if (c13_i8 > 2147483647L) {
        c13_i8 = 2147483647L;
      } else {
        if (c13_i8 <= -2147483648L) {
          c13_i8 = -2147483648L;
        }
      }

      c13_saturatedUnaryMinus = -(int32_T)c13_i8;
      c13_valIn = 0U;
      if (c13_saturatedUnaryMinus < 0) {
        c13_saturatedUnaryMinus = -c13_saturatedUnaryMinus;
        if (c13_saturatedUnaryMinus <= 0) {
          c13_saturatedUnaryMinus = 0;
        } else {
          if (c13_saturatedUnaryMinus > 255) {
            c13_saturatedUnaryMinus = 255;
          }
        }

        c13_absk1 = (uint8_T)c13_saturatedUnaryMinus;
        if (c13_absk1 < 32) {
          c13_valIn = c13_a >> (uint32_T)c13_absk1;
        }
      } else {
        if (c13_saturatedUnaryMinus <= 0) {
          c13_saturatedUnaryMinus = 0;
        } else {
          if (c13_saturatedUnaryMinus > 255) {
            c13_saturatedUnaryMinus = 255;
          }
        }

        c13_absk1 = (uint8_T)c13_saturatedUnaryMinus;
        if (c13_absk1 < 32) {
          c13_valIn = c13_a << (uint32_T)c13_absk1;
        }
      }

      c13_guard1 = TRUE;
    }
  } else {
    c13_guard1 = TRUE;
  }

  if (c13_guard1 == TRUE) {
    c13_a = c13_valIn;
    c13_i8 = (int64_T)c13_bitsIn + (int64_T)*c13_bitposO;
    if (c13_i8 > 2147483647L) {
      c13_i8 = 2147483647L;
    } else {
      if (c13_i8 <= -2147483648L) {
        c13_i8 = -2147483648L;
      }
    }

    c13_i8 = (int64_T)32 - (int64_T)(int32_T)c13_i8;
    if (c13_i8 > 2147483647L) {
      c13_i8 = 2147483647L;
    } else {
      if (c13_i8 <= -2147483648L) {
        c13_i8 = -2147483648L;
      }
    }

    c13_saturatedUnaryMinus = (int32_T)c13_i8;
    c13_valIn = 0U;
    if (c13_saturatedUnaryMinus < 0) {
      c13_saturatedUnaryMinus = -c13_saturatedUnaryMinus;
      if (c13_saturatedUnaryMinus <= 0) {
        c13_saturatedUnaryMinus = 0;
      } else {
        if (c13_saturatedUnaryMinus > 255) {
          c13_saturatedUnaryMinus = 255;
        }
      }

      c13_absk1 = (uint8_T)c13_saturatedUnaryMinus;
      if (c13_absk1 < 32) {
        c13_valIn = c13_a >> (uint32_T)c13_absk1;
      }
    } else {
      if (c13_saturatedUnaryMinus <= 0) {
        c13_saturatedUnaryMinus = 0;
      } else {
        if (c13_saturatedUnaryMinus > 255) {
          c13_saturatedUnaryMinus = 255;
        }
      }

      c13_absk1 = (uint8_T)c13_saturatedUnaryMinus;
      if (c13_absk1 < 32) {
        c13_valIn = c13_a << (uint32_T)c13_absk1;
      }
    }

    *c13_TempO |= c13_valIn;
    c13_i8 = (int64_T)*c13_bitposO + (int64_T)c13_bitsIn;
    if (c13_i8 > 2147483647L) {
      c13_i8 = 2147483647L;
    } else {
      if (c13_i8 <= -2147483648L) {
        c13_i8 = -2147483648L;
      }
    }

    *c13_bitposO = (int32_T)c13_i8;
    *c13_flag = 1.0;
  }
}

static void init_dsm_address_info(SFc13_videoInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c13_video_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3832975803U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2120001566U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4005946966U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2003834566U);
}

mxArray *sf_c13_video_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(4232487868U);
    pr[1] = (double)(1311394154U);
    pr[2] = (double)(2571272459U);
    pr[3] = (double)(2123894124U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(64);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(20);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(7));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c13_video(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"out\",},{M[4],M[0],T\"prev_out\",S'l','i','p'{{M1x2[264 272],M[0],}}},{M[8],M[0],T\"is_active_c13_video\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c13_video_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void sf_opaque_initialize_c13_video(void *chartInstanceVar)
{
  initialize_params_c13_video((SFc13_videoInstanceStruct*) chartInstanceVar);
  initialize_c13_video((SFc13_videoInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c13_video(void *chartInstanceVar)
{
  enable_c13_video((SFc13_videoInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c13_video(void *chartInstanceVar)
{
  disable_c13_video((SFc13_videoInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c13_video(void *chartInstanceVar)
{
  sf_c13_video((SFc13_videoInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c13_video(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c13_video((SFc13_videoInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c13_video();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c13_video(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c13_video();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c13_video((SFc13_videoInstanceStruct*)chartInfo->chartInstance,
    mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c13_video(SimStruct* S)
{
  return sf_internal_get_sim_state_c13_video(S);
}

static void sf_opaque_set_sim_state_c13_video(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c13_video(S, st);
}

static void sf_opaque_terminate_c13_video(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc13_videoInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c13_video((SFc13_videoInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc13_video((SFc13_videoInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c13_video(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c13_video((SFc13_videoInstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c13_video(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"video","video",13);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"video","video",13,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"video","video",13,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"video","video",13,1);
      sf_mark_chart_reusable_outputs(S,"video","video",13,1);
    }

    sf_set_rtw_dwork_info(S,"video","video",13);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3761957463U));
  ssSetChecksum1(S,(3661021555U));
  ssSetChecksum2(S,(1336052382U));
  ssSetChecksum3(S,(4069991243U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c13_video(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "video", "video",13);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c13_video(SimStruct *S)
{
  SFc13_videoInstanceStruct *chartInstance;
  chartInstance = (SFc13_videoInstanceStruct *)malloc(sizeof
    (SFc13_videoInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc13_videoInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c13_video;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c13_video;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c13_video;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c13_video;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c13_video;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c13_video;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c13_video;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c13_video;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c13_video;
  chartInstance->chartInfo.mdlStart = mdlStart_c13_video;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c13_video;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
}

void c13_video_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c13_video(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c13_video(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c13_video(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c13_video_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
