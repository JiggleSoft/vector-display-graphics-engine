//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) Font.
// Filename:     vfont.c
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-03-06 09:45
// Version:      0.9.0
//-----------------------------------------------------------------------------
// Copyright (c) 2021 Justin Lane
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//-----------------------------------------------------------------------------


#include <assert.h>
#include "vfont.h"

#include "vfont-segs.h"



//-----------------------------------------------------------------------------
// Fonts Data.
//-----------------------------------------------------------------------------

// 7-segment font (disabled by default; enable if required).
#ifdef VFONT_7SEG_ENABLE


// Character glyphs.
static VedgeLines vfont_7seg_char_undefined = { .length = 3, .lines = { VFONT_7SEG_A, VFONT_7SEG_D, VFONT_7SEG_G } };

static VedgeLines vfont_7seg_char_space = { .length = 0, .lines = { } };
static VedgeLines vfont_7seg_char_exclamation = { .length = 3, .lines = { VFONT_7SEG_B, VFONT_7SEG_C, VFONT_7SEG_P } };
static VedgeLines vfont_7seg_char_quotation = { .length = 2, .lines = { VFONT_7SEG_B, VFONT_7SEG_F } };
#define vfont_7seg_char_hash vfont_7seg_char_undefined
#define vfont_7seg_char_dollar vfont_7seg_char_undefined
#define vfont_7seg_char_percent vfont_7seg_char_undefined
#define vfont_7seg_char_ampersand vfont_7seg_char_undefined
static VedgeLines vfont_7seg_char_apostrophe = { .length = 1, .lines = { VFONT_7SEG_F } };
#define vfont_7seg_char_left_parenthesis vfont_7seg_char_undefined
#define vfont_7seg_char_right_parenthesis vfont_7seg_char_undefined
#define vfont_7seg_char_asterisk vfont_7seg_char_undefined
#define vfont_7seg_char_plus vfont_7seg_char_undefined
#define vfont_7seg_char_comma vfont_7seg_char_undefined
static VedgeLines vfont_7seg_char_hyphen = { .length = 1, .lines = { VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_full_stop = { .length = 1, .lines = { VFONT_7SEG_P } };
#define vfont_7seg_char_slash vfont_7seg_char_undefined
static VedgeLines vfont_7seg_char_0 = { .length = 4, .lines = { VFONT_7SEG_A, VFONT_7SEG_BC, VFONT_7SEG_D, VFONT_7SEG_EF } };
static VedgeLines vfont_7seg_char_1 = { .length = 1, .lines = { VFONT_7SEG_BC } };
static VedgeLines vfont_7seg_char_2 = { .length = 5, .lines = { VFONT_7SEG_A, VFONT_7SEG_B, VFONT_7SEG_D, VFONT_7SEG_E, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_3 = { .length = 4, .lines = { VFONT_7SEG_A, VFONT_7SEG_BC, VFONT_7SEG_D, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_4 = { .length = 3, .lines = { VFONT_7SEG_BC, VFONT_7SEG_F, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_5 = { .length = 5, .lines = { VFONT_7SEG_A, VFONT_7SEG_C, VFONT_7SEG_D, VFONT_7SEG_F, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_6 = { .length = 5, .lines = { VFONT_7SEG_A, VFONT_7SEG_C, VFONT_7SEG_D, VFONT_7SEG_EF, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_7 = { .length = 3, .lines = { VFONT_7SEG_A, VFONT_7SEG_BC, VFONT_7SEG_F } };
static VedgeLines vfont_7seg_char_8 = { .length = 5, .lines = { VFONT_7SEG_A, VFONT_7SEG_BC, VFONT_7SEG_D, VFONT_7SEG_EF, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_9 = { .length = 5, .lines = { VFONT_7SEG_A, VFONT_7SEG_BC, VFONT_7SEG_D, VFONT_7SEG_F, VFONT_7SEG_G } };
#define vfont_7seg_char_colon vfont_7seg_char_undefined
#define vfont_7seg_char_semicolon vfont_7seg_char_undefined
#define vfont_7seg_char_less_than vfont_7seg_char_undefined
static VedgeLines vfont_7seg_char_equal = { .length = 2, .lines = { VFONT_7SEG_D, VFONT_7SEG_G } };
#define vfont_7seg_char_greater_than vfont_7seg_char_undefined
static VedgeLines vfont_7seg_char_question = { .length = 5, .lines = { VFONT_7SEG_A, VFONT_7SEG_B, VFONT_7SEG_G, VFONT_7SEG_E, VFONT_7SEG_P } };
#define vfont_7seg_char_at vfont_7seg_char_undefined
static VedgeLines vfont_7seg_char_A = { .length = 4, .lines = { VFONT_7SEG_A, VFONT_7SEG_BC, VFONT_7SEG_EF, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_B = { .length = 4, .lines = { VFONT_7SEG_C, VFONT_7SEG_D, VFONT_7SEG_EF, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_C = { .length = 3, .lines = { VFONT_7SEG_D, VFONT_7SEG_E, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_D = { .length = 4, .lines = { VFONT_7SEG_BC, VFONT_7SEG_D, VFONT_7SEG_E, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_E = { .length = 4, .lines = { VFONT_7SEG_A, VFONT_7SEG_D, VFONT_7SEG_EF, VFONT_7SEG_G  } };
static VedgeLines vfont_7seg_char_F = { .length = 3, .lines = { VFONT_7SEG_A, VFONT_7SEG_EF, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_G = { .length = 4, .lines = { VFONT_7SEG_A, VFONT_7SEG_C, VFONT_7SEG_D, VFONT_7SEG_EF } };
static VedgeLines vfont_7seg_char_H = { .length = 3, .lines = { VFONT_7SEG_C, VFONT_7SEG_EF, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_I = { .length = 1, .lines = { VFONT_7SEG_C } };
static VedgeLines vfont_7seg_char_J = { .length = 3, .lines = { VFONT_7SEG_BC, VFONT_7SEG_D, VFONT_7SEG_E } };
static VedgeLines vfont_7seg_char_K = { .length = 4, .lines = { VFONT_7SEG_A, VFONT_7SEG_C, VFONT_7SEG_EF, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_L = { .length = 2, .lines = { VFONT_7SEG_D, VFONT_7SEG_EF } };
static VedgeLines vfont_7seg_char_M = { .length = 4, .lines = { VFONT_7SEG_A, VFONT_7SEG_C, VFONT_7SEG_E, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_N = { .length = 3, .lines = { VFONT_7SEG_C, VFONT_7SEG_E, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_O = { .length = 4, .lines = { VFONT_7SEG_C, VFONT_7SEG_E, VFONT_7SEG_D, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_P = { .length = 4, .lines = { VFONT_7SEG_A, VFONT_7SEG_B, VFONT_7SEG_EF, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_Q = { .length = 4, .lines = { VFONT_7SEG_A, VFONT_7SEG_BC, VFONT_7SEG_F, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_R = { .length = 2, .lines = { VFONT_7SEG_E, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_S = { .length = 5, .lines = { VFONT_7SEG_A, VFONT_7SEG_C, VFONT_7SEG_D, VFONT_7SEG_F, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_T = { .length = 2, .lines = { VFONT_7SEG_A, VFONT_7SEG_BC } };
static VedgeLines vfont_7seg_char_U = { .length = 3, .lines = { VFONT_7SEG_BC, VFONT_7SEG_D, VFONT_7SEG_EF } };
static VedgeLines vfont_7seg_char_V = { .length = 3, .lines = { VFONT_7SEG_C, VFONT_7SEG_D, VFONT_7SEG_E } };
static VedgeLines vfont_7seg_char_W = { .length = 4, .lines = { VFONT_7SEG_B, VFONT_7SEG_D, VFONT_7SEG_F, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_X = { .length = 3, .lines = { VFONT_7SEG_C, VFONT_7SEG_F, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_Y = { .length = 4, .lines = { VFONT_7SEG_BC, VFONT_7SEG_D, VFONT_7SEG_F, VFONT_7SEG_G } };
static VedgeLines vfont_7seg_char_Z = { .length = 5, .lines = { VFONT_7SEG_A, VFONT_7SEG_B, VFONT_7SEG_D, VFONT_7SEG_E, VFONT_7SEG_G } };
#define vfont_7seg_char_left_square vfont_7seg_char_undefined
#define vfont_7seg_char_backslash vfont_7seg_char_undefined
#define vfont_7seg_char_right_square vfont_7seg_char_undefined
#define vfont_7seg_char_circumlex vfont_7seg_char_undefined
static VedgeLines vfont_7seg_char_underscore = { .length = 1, .lines = { VFONT_7SEG_D } };


// The font.
static Vfont vfont_7seg_data = {
        .char_min = 0x20,
        .char_max = 0x5F,
        .char_width = VMATHNUMBER_C( 12.0 ),
        .char_height = VMATHNUMBER_C( 12.0 ),
        .undefined_lines = &vfont_7seg_char_undefined,
        .char_lines = {
                &vfont_7seg_char_space,
                &vfont_7seg_char_exclamation,
                &vfont_7seg_char_quotation,
                &vfont_7seg_char_hash,
                &vfont_7seg_char_dollar,
                &vfont_7seg_char_percent,
                &vfont_7seg_char_ampersand,
                &vfont_7seg_char_apostrophe,
                &vfont_7seg_char_left_parenthesis,
                &vfont_7seg_char_right_parenthesis,
                &vfont_7seg_char_asterisk,
                &vfont_7seg_char_plus,
                &vfont_7seg_char_comma,
                &vfont_7seg_char_hyphen,
                &vfont_7seg_char_full_stop,
                &vfont_7seg_char_slash,
                &vfont_7seg_char_0,
                &vfont_7seg_char_1,
                &vfont_7seg_char_2,
                &vfont_7seg_char_3,
                &vfont_7seg_char_4,
                &vfont_7seg_char_5,
                &vfont_7seg_char_6,
                &vfont_7seg_char_7,
                &vfont_7seg_char_8,
                &vfont_7seg_char_9,
                &vfont_7seg_char_colon,
                &vfont_7seg_char_semicolon,
                &vfont_7seg_char_less_than,
                &vfont_7seg_char_equal,
                &vfont_7seg_char_greater_than,
                &vfont_7seg_char_question,
                &vfont_7seg_char_at,
                &vfont_7seg_char_A,
                &vfont_7seg_char_B,
                &vfont_7seg_char_C,
                &vfont_7seg_char_D,
                &vfont_7seg_char_E,
                &vfont_7seg_char_F,
                &vfont_7seg_char_G,
                &vfont_7seg_char_H,
                &vfont_7seg_char_I,
                &vfont_7seg_char_J,
                &vfont_7seg_char_K,
                &vfont_7seg_char_L,
                &vfont_7seg_char_M,
                &vfont_7seg_char_N,
                &vfont_7seg_char_O,
                &vfont_7seg_char_P,
                &vfont_7seg_char_Q,
                &vfont_7seg_char_R,
                &vfont_7seg_char_S,
                &vfont_7seg_char_T,
                &vfont_7seg_char_U,
                &vfont_7seg_char_V,
                &vfont_7seg_char_W,
                &vfont_7seg_char_X,
                &vfont_7seg_char_Y,
                &vfont_7seg_char_Z,
                &vfont_7seg_char_left_square,
                &vfont_7seg_char_backslash,
                &vfont_7seg_char_right_square,
                &vfont_7seg_char_circumlex,
                &vfont_7seg_char_underscore
        }
};


// The external reference to the font.
Vfont * vfont_7seg = &vfont_7seg_data;


#endif



// 16-segment font (disabled by default; enable if required).
#ifdef VFONT_16SEG_ENABLE


// Character glyphs.
static VedgeLines vfont_16seg_char_undefined = { .length = 8, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4_8, VFONT_16SEG_9_10, VFONT_16SEG_13_16, VFONT_16SEG_2_6, VFONT_16SEG_3_14, VFONT_16SEG_5_15, VFONT_16SEG_7_17 } };

static VedgeLines vfont_16seg_char_space = { .length = 0, .lines = { } };
static VedgeLines vfont_16seg_char_exclamation = { .length = 3, .lines = { VFONT_16SEG_12, VFONT_16SEG_13, VFONT_16SEG_16 } };
static VedgeLines vfont_16seg_char_quotation = { .length = 2, .lines = { VFONT_16SEG_2, VFONT_16SEG_16 } };
static VedgeLines vfont_16seg_char_hash = { .length = 4, .lines = { VFONT_16SEG_2_6, VFONT_16SEG_5_15, VFONT_16SEG_9_10, VFONT_16SEG_13_16 } };
static VedgeLines vfont_16seg_char_dollar = { .length = 6, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_2_6, VFONT_16SEG_4, VFONT_16SEG_5_15, VFONT_16SEG_9_10, VFONT_16SEG_13 } };
static VedgeLines vfont_16seg_char_percent = { .length = 7, .lines = { VFONT_16SEG_1, VFONT_16SEG_2_6, VFONT_16SEG_4, VFONT_16SEG_5_15, VFONT_16SEG_7_17, VFONT_16SEG_10, VFONT_16SEG_13 } };
static VedgeLines vfont_16seg_char_ampersand = { .length = 6, .lines = { VFONT_16SEG_1, VFONT_16SEG_2, VFONT_16SEG_3_14, VFONT_16SEG_5, VFONT_16SEG_8, VFONT_16SEG_9_10 } };
static VedgeLines vfont_16seg_char_apostrophe = { .length = 1, .lines = { VFONT_16SEG_2 }  };
static VedgeLines vfont_16seg_char_left_parenthesis = { .length = 2, .lines = { VFONT_16SEG_14, VFONT_16SEG_17 } };
static VedgeLines vfont_16seg_char_right_parenthesis = { .length = 2, .lines = { VFONT_16SEG_3, VFONT_16SEG_7 } };
static VedgeLines vfont_16seg_char_asterisk = { .length = 4, .lines = { VFONT_16SEG_2_6,VFONT_16SEG_3_14, VFONT_16SEG_5_15, VFONT_16SEG_7_17 } };
static VedgeLines vfont_16seg_char_plus = { .length = 2, .lines = { VFONT_16SEG_2_6, VFONT_16SEG_5_15 } };
static VedgeLines vfont_16seg_char_comma = { .length = 1, .lines = { VFONT_16SEG_7 } };
static VedgeLines vfont_16seg_char_hyphen = { .length = 1, .lines = { VFONT_16SEG_5_15 } };
static VedgeLines vfont_16seg_char_full_stop = { .length = 1, .lines = { VFONT_16SEG_12 } };
static VedgeLines vfont_16seg_char_slash = { .length = 1, .lines = { VFONT_16SEG_7_17 } };
static VedgeLines vfont_16seg_char_0 = { .length = 5, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4_8, VFONT_16SEG_7_17, VFONT_16SEG_9_10, VFONT_16SEG_13_16 } };
static VedgeLines vfont_16seg_char_1 = { .length = 2, .lines = { VFONT_16SEG_13_16, VFONT_16SEG_17 } };
static VedgeLines vfont_16seg_char_2 = { .length = 5, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_5_15, VFONT_16SEG_8, VFONT_16SEG_9_10, VFONT_16SEG_16 } };
static VedgeLines vfont_16seg_char_3 = { .length = 4, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_9_10, VFONT_16SEG_13_16, VFONT_16SEG_15 } };
static VedgeLines vfont_16seg_char_4 = { .length = 3, .lines = { VFONT_16SEG_4, VFONT_16SEG_5_15, VFONT_16SEG_13_16 } };
static VedgeLines vfont_16seg_char_5 = { .length = 5, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4, VFONT_16SEG_5, VFONT_16SEG_9_10, VFONT_16SEG_14 } };
static VedgeLines vfont_16seg_char_6 = { .length = 5, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4_8, VFONT_16SEG_5_15, VFONT_16SEG_9_10, VFONT_16SEG_13 } };
static VedgeLines vfont_16seg_char_7 = { .length = 2, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_13_16 } };
static VedgeLines vfont_16seg_char_8 = { .length = 5, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4_8, VFONT_16SEG_5_15, VFONT_16SEG_9_10, VFONT_16SEG_13_16 } };
static VedgeLines vfont_16seg_char_9 = { .length = 4, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4, VFONT_16SEG_5_15, VFONT_16SEG_13_16 } };
static VedgeLines vfont_16seg_char_colon = { .length = 1, .lines = { VFONT_16SEG_2_6 } };
static VedgeLines vfont_16seg_char_semicolon = { .length = 2, .lines = { VFONT_16SEG_2, VFONT_16SEG_7 } };
static VedgeLines vfont_16seg_char_less_than = { .length = 3, .lines = { VFONT_16SEG_5, VFONT_16SEG_14, VFONT_16SEG_17} };
static VedgeLines vfont_16seg_char_equal = { .length = 2, .lines = { VFONT_16SEG_5_15, VFONT_16SEG_9_10 } };
static VedgeLines vfont_16seg_char_greater_than = { .length = 3, .lines = { VFONT_16SEG_3, VFONT_16SEG_7, VFONT_16SEG_15 } };
static VedgeLines vfont_16seg_char_question = { .length = 5, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_6, VFONT_16SEG_12, VFONT_16SEG_15, VFONT_16SEG_16 } };
static VedgeLines vfont_16seg_char_at = { .length = 6, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_2, VFONT_16SEG_4_8, VFONT_16SEG_9_10, VFONT_16SEG_15, VFONT_16SEG_16 } };
static VedgeLines vfont_16seg_char_A = { .length = 4, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4_8, VFONT_16SEG_5_15, VFONT_16SEG_13_16 } };
static VedgeLines vfont_16seg_char_B = { .length = 5, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_2_6, VFONT_16SEG_9_10, VFONT_16SEG_13_16, VFONT_16SEG_15 } };
static VedgeLines vfont_16seg_char_C = { .length = 3, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4_8, VFONT_16SEG_9_10 } };
static VedgeLines vfont_16seg_char_D = { .length = 4, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_2_6, VFONT_16SEG_9_10, VFONT_16SEG_13_16 } };
static VedgeLines vfont_16seg_char_E = { .length = 4, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4_8, VFONT_16SEG_5, VFONT_16SEG_9_10 } };
static VedgeLines vfont_16seg_char_F = { .length = 3, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4_8, VFONT_16SEG_5 } };
static VedgeLines vfont_16seg_char_G = { .length = 5, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4_8, VFONT_16SEG_9_10, VFONT_16SEG_13, VFONT_16SEG_15 } };
static VedgeLines vfont_16seg_char_H = { .length = 3, .lines = { VFONT_16SEG_4_8, VFONT_16SEG_5_15, VFONT_16SEG_13_16 } };
static VedgeLines vfont_16seg_char_I = { .length = 3, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_2_6, VFONT_16SEG_9_10 } };
static VedgeLines vfont_16seg_char_J = { .length = 3, .lines = { VFONT_16SEG_8, VFONT_16SEG_9_10, VFONT_16SEG_13_16 } };
static VedgeLines vfont_16seg_char_K = { .length = 4, .lines = { VFONT_16SEG_4_8, VFONT_16SEG_5, VFONT_16SEG_14, VFONT_16SEG_17 } };
static VedgeLines vfont_16seg_char_L = { .length = 2, .lines = { VFONT_16SEG_4_8, VFONT_16SEG_9_10 } };
static VedgeLines vfont_16seg_char_M = { .length = 4, .lines = { VFONT_16SEG_3, VFONT_16SEG_4_8, VFONT_16SEG_13_16, VFONT_16SEG_17 } };
static VedgeLines vfont_16seg_char_N = { .length = 3, .lines = { VFONT_16SEG_3_14, VFONT_16SEG_4_8, VFONT_16SEG_13_16 } };
static VedgeLines vfont_16seg_char_O = { .length = 4, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4_8, VFONT_16SEG_9_10, VFONT_16SEG_13_16 } };
static VedgeLines vfont_16seg_char_P = { .length = 4, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4_8, VFONT_16SEG_5_15, VFONT_16SEG_16 } };
static VedgeLines vfont_16seg_char_Q = { .length = 5, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4_8, VFONT_16SEG_9_10, VFONT_16SEG_13_16, VFONT_16SEG_14 } };
static VedgeLines vfont_16seg_char_R = { .length = 5, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4_8, VFONT_16SEG_5_15, VFONT_16SEG_14, VFONT_16SEG_16 } };
static VedgeLines vfont_16seg_char_S = { .length = 5, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4, VFONT_16SEG_5_15, VFONT_16SEG_9_10, VFONT_16SEG_13 } };
static VedgeLines vfont_16seg_char_T = { .length = 2, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_2_6 } };
static VedgeLines vfont_16seg_char_U = { .length = 3, .lines = { VFONT_16SEG_4_8, VFONT_16SEG_9_10, VFONT_16SEG_13_16 } };
static VedgeLines vfont_16seg_char_V = { .length = 2, .lines = { VFONT_16SEG_4_8, VFONT_16SEG_7_17 } };
static VedgeLines vfont_16seg_char_W = { .length = 4, .lines = { VFONT_16SEG_4_8, VFONT_16SEG_7, VFONT_16SEG_13_16, VFONT_16SEG_14 } };
static VedgeLines vfont_16seg_char_X = { .length = 2, .lines = { VFONT_16SEG_3_14, VFONT_16SEG_7_17 } };
static VedgeLines vfont_16seg_char_Y = { .length = 3, .lines = { VFONT_16SEG_3, VFONT_16SEG_6, VFONT_16SEG_17 } };
static VedgeLines vfont_16seg_char_Z = { .length = 3, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_7_17, VFONT_16SEG_9_10 } };
static VedgeLines vfont_16seg_char_left_square = { .length = 3, .lines = { VFONT_16SEG_2_6, VFONT_16SEG_10, VFONT_16SEG_18 } };
static VedgeLines vfont_16seg_char_backslash = { .length = 1, .lines = { VFONT_16SEG_3_14 } };
static VedgeLines vfont_16seg_char_right_square = { .length = 3, .lines = { VFONT_16SEG_1, VFONT_16SEG_2_6,VFONT_16SEG_9 } };
static VedgeLines vfont_16seg_char_circumlex = { .length = 2, .lines = { VFONT_16SEG_7, VFONT_16SEG_14 } };
static VedgeLines vfont_16seg_char_underscore = { .length = 1, .lines = { VFONT_16SEG_9_10 } };
static VedgeLines vfont_16seg_char_grave_accent = { .length = 1, .lines = { VFONT_16SEG_3 } };
static VedgeLines vfont_16seg_char_a = { .length = 4, .lines = { VFONT_16SEG_5, VFONT_16SEG_6, VFONT_16SEG_8, VFONT_16SEG_9_10 } };
static VedgeLines vfont_16seg_char_b = { .length = 4, .lines = { VFONT_16SEG_4_8, VFONT_16SEG_5, VFONT_16SEG_6, VFONT_16SEG_9 } };
static VedgeLines vfont_16seg_char_c = { .length = 3, .lines = { VFONT_16SEG_5, VFONT_16SEG_8, VFONT_16SEG_9 } };
static VedgeLines vfont_16seg_char_d = { .length = 4, .lines = { VFONT_16SEG_6, VFONT_16SEG_10, VFONT_16SEG_13_16, VFONT_16SEG_15 } };
static VedgeLines vfont_16seg_char_e = { .length = 4, .lines = { VFONT_16SEG_5, VFONT_16SEG_7, VFONT_16SEG_8, VFONT_16SEG_9 } };
static VedgeLines vfont_16seg_char_f = { .length = 3, .lines = { VFONT_16SEG_2_6, VFONT_16SEG_5_15, VFONT_16SEG_18 } };
static VedgeLines vfont_16seg_char_g = { .length = 5, .lines = { VFONT_16SEG_1, VFONT_16SEG_2_6, VFONT_16SEG_4, VFONT_16SEG_5, VFONT_16SEG_9 } };
static VedgeLines vfont_16seg_char_h = { .length = 3, .lines = { VFONT_16SEG_4_8, VFONT_16SEG_5, VFONT_16SEG_6 } };
static VedgeLines vfont_16seg_char_i = { .length = 1, .lines = { VFONT_16SEG_6 } };
static VedgeLines vfont_16seg_char_j = { .length = 3, .lines = { VFONT_16SEG_2_6, VFONT_16SEG_8, VFONT_16SEG_9 } };
static VedgeLines vfont_16seg_char_k = { .length = 3, .lines = { VFONT_16SEG_2_6, VFONT_16SEG_14, VFONT_16SEG_17 } };
static VedgeLines vfont_16seg_char_l = { .length = 1, .lines = { VFONT_16SEG_4_8 } };
static VedgeLines vfont_16seg_char_m = { .length = 4, .lines = { VFONT_16SEG_5_15, VFONT_16SEG_6, VFONT_16SEG_8, VFONT_16SEG_13 } };
static VedgeLines vfont_16seg_char_n = { .length = 3, .lines = { VFONT_16SEG_5, VFONT_16SEG_6, VFONT_16SEG_8 } };
static VedgeLines vfont_16seg_char_o = { .length = 4, .lines = { VFONT_16SEG_5, VFONT_16SEG_6, VFONT_16SEG_8, VFONT_16SEG_9 } };
static VedgeLines vfont_16seg_char_p = { .length = 4, .lines = { VFONT_16SEG_1, VFONT_16SEG_2, VFONT_16SEG_4_8, VFONT_16SEG_5} };
static VedgeLines vfont_16seg_char_q = { .length = 4, .lines = { VFONT_16SEG_1, VFONT_16SEG_2_6, VFONT_16SEG_4, VFONT_16SEG_5 } };
static VedgeLines vfont_16seg_char_r = { .length = 2, .lines = { VFONT_16SEG_5, VFONT_16SEG_8 } };
static VedgeLines vfont_16seg_char_s = { .length = 5, .lines = { VFONT_16SEG_1, VFONT_16SEG_4, VFONT_16SEG_5, VFONT_16SEG_6, VFONT_16SEG_9 } };
static VedgeLines vfont_16seg_char_t = { .length = 3, .lines = { VFONT_16SEG_4_8, VFONT_16SEG_5, VFONT_16SEG_9 } };
static VedgeLines vfont_16seg_char_u = { .length = 3, .lines = { VFONT_16SEG_6, VFONT_16SEG_8, VFONT_16SEG_9 } };
static VedgeLines vfont_16seg_char_v = { .length = 2, .lines = { VFONT_16SEG_7, VFONT_16SEG_8 } };
static VedgeLines vfont_16seg_char_w = { .length = 4, .lines = { VFONT_16SEG_7, VFONT_16SEG_8, VFONT_16SEG_13, VFONT_16SEG_14} };
static VedgeLines vfont_16seg_char_x = { .length = 2, .lines = { VFONT_16SEG_3_14, VFONT_16SEG_7_17} };
static VedgeLines vfont_16seg_char_y = { .length = 4, .lines = { VFONT_16SEG_2, VFONT_16SEG_10, VFONT_16SEG_13_16, VFONT_16SEG_15} };
static VedgeLines vfont_16seg_char_z = { .length = 3, .lines = { VFONT_16SEG_5, VFONT_16SEG_7, VFONT_16SEG_9 } };
static VedgeLines vfont_16seg_char_left_brace = { .length = 4, .lines = { VFONT_16SEG_2_6, VFONT_16SEG_5, VFONT_16SEG_10, VFONT_16SEG_18 } };
static VedgeLines vfont_16seg_char_vertical_bar = { .length = 1, .lines = { VFONT_16SEG_2_6 } };
static VedgeLines vfont_16seg_char_right_brace = { .length = 4, .lines = { VFONT_16SEG_1, VFONT_16SEG_2_6, VFONT_16SEG_9, VFONT_16SEG_15 } };
static VedgeLines vfont_16seg_char_tilde = { .length = 2, .lines = { VFONT_16SEG_5_15, VFONT_16SEG_7_17 } };
static VedgeLines vfont_16seg_char_del = { .length = 0, .lines = { } };


// The font.
static Vfont vfont_16seg_data = {
        .char_min = 0x20,
        .char_max = 0x7F,
        .char_width = VMATHNUMBER_C( 12.0 ),
        .char_height = VMATHNUMBER_C( 12.0 ),
        .undefined_lines = &vfont_16seg_char_undefined,
        .char_lines = {
                &vfont_16seg_char_space,
                &vfont_16seg_char_exclamation,
                &vfont_16seg_char_quotation,
                &vfont_16seg_char_hash,
                &vfont_16seg_char_dollar,
                &vfont_16seg_char_percent,
                &vfont_16seg_char_ampersand,
                &vfont_16seg_char_apostrophe,
                &vfont_16seg_char_left_parenthesis,
                &vfont_16seg_char_right_parenthesis,
                &vfont_16seg_char_asterisk,
                &vfont_16seg_char_plus,
                &vfont_16seg_char_comma,
                &vfont_16seg_char_hyphen,
                &vfont_16seg_char_full_stop,
                &vfont_16seg_char_slash,
                &vfont_16seg_char_0,
                &vfont_16seg_char_1,
                &vfont_16seg_char_2,
                &vfont_16seg_char_3,
                &vfont_16seg_char_4,
                &vfont_16seg_char_5,
                &vfont_16seg_char_6,
                &vfont_16seg_char_7,
                &vfont_16seg_char_8,
                &vfont_16seg_char_9,
                &vfont_16seg_char_colon,
                &vfont_16seg_char_semicolon,
                &vfont_16seg_char_less_than,
                &vfont_16seg_char_equal,
                &vfont_16seg_char_greater_than,
                &vfont_16seg_char_question,
                &vfont_16seg_char_at,
                &vfont_16seg_char_A,
                &vfont_16seg_char_B,
                &vfont_16seg_char_C,
                &vfont_16seg_char_D,
                &vfont_16seg_char_E,
                &vfont_16seg_char_F,
                &vfont_16seg_char_G,
                &vfont_16seg_char_H,
                &vfont_16seg_char_I,
                &vfont_16seg_char_J,
                &vfont_16seg_char_K,
                &vfont_16seg_char_L,
                &vfont_16seg_char_M,
                &vfont_16seg_char_N,
                &vfont_16seg_char_O,
                &vfont_16seg_char_P,
                &vfont_16seg_char_Q,
                &vfont_16seg_char_R,
                &vfont_16seg_char_S,
                &vfont_16seg_char_T,
                &vfont_16seg_char_U,
                &vfont_16seg_char_V,
                &vfont_16seg_char_W,
                &vfont_16seg_char_X,
                &vfont_16seg_char_Y,
                &vfont_16seg_char_Z,
                &vfont_16seg_char_left_square,
                &vfont_16seg_char_backslash,
                &vfont_16seg_char_right_square,
                &vfont_16seg_char_circumlex,
                &vfont_16seg_char_underscore,
                &vfont_16seg_char_grave_accent,
                &vfont_16seg_char_a,
                &vfont_16seg_char_b,
                &vfont_16seg_char_c,
                &vfont_16seg_char_d,
                &vfont_16seg_char_e,
                &vfont_16seg_char_f,
                &vfont_16seg_char_g,
                &vfont_16seg_char_h,
                &vfont_16seg_char_i,
                &vfont_16seg_char_j,
                &vfont_16seg_char_k,
                &vfont_16seg_char_l,
                &vfont_16seg_char_m,
                &vfont_16seg_char_n,
                &vfont_16seg_char_o,
                &vfont_16seg_char_p,
                &vfont_16seg_char_q,
                &vfont_16seg_char_r,
                &vfont_16seg_char_s,
                &vfont_16seg_char_t,
                &vfont_16seg_char_u,
                &vfont_16seg_char_v,
                &vfont_16seg_char_w,
                &vfont_16seg_char_x,
                &vfont_16seg_char_y,
                &vfont_16seg_char_z,
                &vfont_16seg_char_left_brace,
                &vfont_16seg_char_vertical_bar,
                &vfont_16seg_char_right_brace,
                &vfont_16seg_char_tilde,
                &vfont_16seg_char_del
        }
};


// The external reference to the font.
Vfont * vfont_16seg = &vfont_16seg_data;


#endif



// Arcade font (enabled by default; disable if not required).
#ifndef VFONT_ARCADE_DISABLE


// Character glyphs.
static VedgeLines vfont_arcade_char_undefined = { .length = 8, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4_8, VFONT_16SEG_9_10, VFONT_16SEG_13_16, VFONT_16SEG_2_6, VFONT_16SEG_3_14, VFONT_16SEG_5_15, VFONT_16SEG_7_17 } };

static VedgeLines vfont_arcade_char_space = { .length = 0, .lines = { } };
static VedgeLines vfont_arcade_char_exclamation = { .length = 2, .lines = { VFONT_ARCADE_15_75, VFONT_ARCADE_85_95 } };
static VedgeLines vfont_arcade_char_quotation = { .length = 2, .lines = { VFONT_ARCADE_14_34, VFONT_ARCADE_16_36 } };
static VedgeLines vfont_arcade_char_hash = { .length = 4, .lines = { VFONT_ARCADE_13_93, VFONT_ARCADE_17_97, VFONT_ARCADE_31_39, VFONT_ARCADE_71_79 } };
static VedgeLines vfont_arcade_char_dollar = { .length = 7, .lines = { VFONT_ARCADE_22_28, VFONT_ARCADE_82_88, VFONT_ARCADE_52_58, VFONT_ARCADE_22_52, VFONT_ARCADE_58_88, VFONT_ARCADE_14_94, VFONT_ARCADE_16_96 } };
static VedgeLines vfont_arcade_char_percent = { .length = 9, .lines = { VFONT_ARCADE_19_91, VFONT_ARCADE_11_13, VFONT_ARCADE_11_31,VFONT_ARCADE_13_33, VFONT_ARCADE_31_33, VFONT_ARCADE_77_79, VFONT_ARCADE_77_97, VFONT_ARCADE_97_99, VFONT_ARCADE_79_99 } };
static VedgeLines vfont_arcade_char_ampersand = { .length = 0, .lines = {  } };//FIXME: !!!!!!!!!!!!!!!!!!!!
static VedgeLines vfont_arcade_char_apostrophe = { .length = 1, .lines = { VFONT_ARCADE_15_26 } };
static VedgeLines vfont_arcade_char_left_parenthesis = { .length = 3, .lines = { VFONT_ARCADE_17_23, VFONT_ARCADE_23_83, VFONT_ARCADE_83_97 } };
static VedgeLines vfont_arcade_char_right_parenthesis = { .length = 3, .lines = { VFONT_ARCADE_13_27, VFONT_ARCADE_27_87, VFONT_ARCADE_87_93 } };
static VedgeLines vfont_arcade_char_asterisk = { .length = 4, .lines = { VFONT_ARCADE_15_95, VFONT_ARCADE_51_59, VFONT_ARCADE_11_99, VFONT_ARCADE_19_91 } };
static VedgeLines vfont_arcade_char_plus = { .length = 2, .lines = { VFONT_ARCADE_15_95, VFONT_ARCADE_51_59 } };
static VedgeLines vfont_arcade_char_comma = { .length = 1, .lines = { VFONT_ARCADE_85_94 } };
static VedgeLines vfont_arcade_char_hyphen = { .length = 1, .lines = { VFONT_ARCADE_51_59 } };
static VedgeLines vfont_arcade_char_full_stop = { .length = 1, .lines = { VFONT_ARCADE_85_95 } };
static VedgeLines vfont_arcade_char_slash = { .length = 1, .lines = { VFONT_ARCADE_19_91 } };
static VedgeLines vfont_arcade_char_0 = { .length = 4, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_11_91, VFONT_ARCADE_91_99, VFONT_ARCADE_19_99 } };
static VedgeLines vfont_arcade_char_1 = { .length = 1, .lines = { VFONT_ARCADE_51_59 } };
static VedgeLines vfont_arcade_char_2 = { .length = 5, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_19_59, VFONT_ARCADE_51_59, VFONT_ARCADE_51_91, VFONT_ARCADE_91_99 } };
static VedgeLines vfont_arcade_char_3 = { .length = 4, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_51_59, VFONT_ARCADE_91_99, VFONT_ARCADE_19_99 } };
static VedgeLines vfont_arcade_char_4 = { .length = 3, .lines = { VFONT_ARCADE_11_51, VFONT_ARCADE_51_59, VFONT_ARCADE_19_99 } };
static VedgeLines vfont_arcade_char_5 = { .length = 5, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_11_51, VFONT_ARCADE_51_59, VFONT_ARCADE_91_99, VFONT_ARCADE_59_99 } };
static VedgeLines vfont_arcade_char_6 = { .length = 5, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_11_91, VFONT_ARCADE_91_99, VFONT_ARCADE_51_59, VFONT_ARCADE_59_99 } };
static VedgeLines vfont_arcade_char_7 = { .length = 2, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_19_99 } };
static VedgeLines vfont_arcade_char_8 = { .length = 5, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_11_91, VFONT_ARCADE_51_59, VFONT_ARCADE_91_99, VFONT_ARCADE_19_99 } };
static VedgeLines vfont_arcade_char_9 = { .length = 4, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_11_51, VFONT_ARCADE_51_59, VFONT_ARCADE_19_99 } };
static VedgeLines vfont_arcade_char_colon = { .length = 2, .lines = { VFONT_ARCADE_35_45, VFONT_ARCADE_65_75 } };
static VedgeLines vfont_arcade_char_semicolon = { .length = 2, .lines = { VFONT_ARCADE_35_45, VFONT_ARCADE_65_74 } };
static VedgeLines vfont_arcade_char_less_than = { .length = 2, .lines = { VFONT_ARCADE_19_51, VFONT_ARCADE_51_99 } };
static VedgeLines vfont_arcade_char_equal = { .length = 2, .lines = { VFONT_ARCADE_31_39, VFONT_ARCADE_71_79 } };
static VedgeLines vfont_arcade_char_greater_than = { .length = 2, .lines = { VFONT_ARCADE_11_59, VFONT_ARCADE_59_91 } };
static VedgeLines vfont_arcade_char_question = { .length = 5, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_55_59, VFONT_ARCADE_19_59, VFONT_ARCADE_55_75, VFONT_ARCADE_85_95 } };
//FIXME: !!!!!!!!!!!!!!!!!!!!
static VedgeLines vfont_arcade_char_at = { .length = 8, .lines = { { .x1 = 2, .y1 = 2, .x2 = 2, .y2 = -2 }, { .x1 = 2, .y1 = -2, .x2 = -2, .y2 = -2 }, { .x1 = -2, .y1 = -2, .x2 = -2, .y2 = 2 }, { .x1 = -2, .y1 = 2, .x2 = 4, .y2 = 2 }, { .x1 = 4, .y1 = 2, .x2 = 4, .y2 = -4 }, { .x1 = 4, .y1 = -4, .x2 = -4, .y2 = -4 }, { .x1 = -4, .y1 = -4, .x2 = -4, .y2 = 4 }, { .x1 = -4, .y1 = 4, .x2 = 4, .y2 = 4 } } };
static VedgeLines vfont_arcade_char_A = { .length = 5, .lines = { VFONT_ARCADE_15_31, VFONT_ARCADE_15_39, VFONT_ARCADE_51_59, VFONT_ARCADE_31_91, VFONT_ARCADE_39_99 } };
static VedgeLines vfont_arcade_char_B = { .length = 8, .lines = { VFONT_ARCADE_11_17, VFONT_ARCADE_51_57, VFONT_ARCADE_91_97, VFONT_ARCADE_17_39, VFONT_ARCADE_57_39, VFONT_ARCADE_57_79, VFONT_ARCADE_79_97, VFONT_ARCADE_11_91 } };
static VedgeLines vfont_arcade_char_C = { .length = 3, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_91_99, VFONT_ARCADE_11_91 } };
static VedgeLines vfont_arcade_char_D = { .length = 6, .lines = { VFONT_ARCADE_11_17, VFONT_ARCADE_91_97, VFONT_ARCADE_17_39, VFONT_ARCADE_79_97, VFONT_ARCADE_11_91, VFONT_ARCADE_39_79 } };
static VedgeLines vfont_arcade_char_E = { .length = 4, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_51_57, VFONT_ARCADE_91_99, VFONT_ARCADE_11_91 } };
static VedgeLines vfont_arcade_char_F = { .length = 3, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_51_57, VFONT_ARCADE_11_91 } };
static VedgeLines vfont_arcade_char_G = { .length = 5, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_55_59, VFONT_ARCADE_91_99, VFONT_ARCADE_11_91, VFONT_ARCADE_59_99 } };
static VedgeLines vfont_arcade_char_H = { .length = 3, .lines = { VFONT_ARCADE_51_59, VFONT_ARCADE_11_91, VFONT_ARCADE_19_99 } };
static VedgeLines vfont_arcade_char_I = { .length = 3, .lines = { VFONT_ARCADE_13_17, VFONT_ARCADE_93_97, VFONT_ARCADE_15_95 } };
static VedgeLines vfont_arcade_char_J = { .length = 3, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_91_95, VFONT_ARCADE_15_95 } };
static VedgeLines vfont_arcade_char_K = { .length = 4, .lines = { VFONT_ARCADE_51_53, VFONT_ARCADE_19_53, VFONT_ARCADE_53_99, VFONT_ARCADE_11_91 } };
static VedgeLines vfont_arcade_char_L = { .length = 2, .lines = { VFONT_ARCADE_91_99, VFONT_ARCADE_11_91 } };
static VedgeLines vfont_arcade_char_M = { .length = 4, .lines = { VFONT_ARCADE_11_55, VFONT_ARCADE_19_55, VFONT_ARCADE_11_91, VFONT_ARCADE_19_99 } };
static VedgeLines vfont_arcade_char_N = { .length = 3, .lines = { VFONT_ARCADE_11_91, VFONT_ARCADE_11_99, VFONT_ARCADE_19_99 } };
static VedgeLines vfont_arcade_char_O = { .length = 4, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_11_91, VFONT_ARCADE_91_99, VFONT_ARCADE_19_99 } };
static VedgeLines vfont_arcade_char_P = { .length = 4, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_11_91, VFONT_ARCADE_51_59, VFONT_ARCADE_19_59 } };
static VedgeLines vfont_arcade_char_Q = { .length = 5, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_11_91, VFONT_ARCADE_77_99, VFONT_ARCADE_91_99, VFONT_ARCADE_19_99 } };
static VedgeLines vfont_arcade_char_R = { .length = 5, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_11_91, VFONT_ARCADE_51_59, VFONT_ARCADE_19_59, VFONT_ARCADE_55_99 } };
static VedgeLines vfont_arcade_char_S = { .length = 5, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_11_51, VFONT_ARCADE_51_59, VFONT_ARCADE_91_99, VFONT_ARCADE_59_99 } };
static VedgeLines vfont_arcade_char_T = { .length = 2, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_15_95 } };
static VedgeLines vfont_arcade_char_U = { .length = 3, .lines = { VFONT_ARCADE_91_99, VFONT_ARCADE_11_91, VFONT_ARCADE_19_99 } };
static VedgeLines vfont_arcade_char_V = { .length = 2, .lines = { VFONT_ARCADE_11_95, VFONT_ARCADE_19_95 } };
static VedgeLines vfont_arcade_char_W = { .length = 4, .lines = { VFONT_ARCADE_11_93, VFONT_ARCADE_55_93, VFONT_ARCADE_55_97, VFONT_ARCADE_19_97 } };
static VedgeLines vfont_arcade_char_X = { .length = 2, .lines = { VFONT_ARCADE_11_99, VFONT_ARCADE_19_91 } };
static VedgeLines vfont_arcade_char_Y = { .length = 3, .lines = { VFONT_ARCADE_11_55, VFONT_ARCADE_55_19, VFONT_ARCADE_55_95 } };
static VedgeLines vfont_arcade_char_Z = { .length = 3, .lines = { VFONT_ARCADE_11_19, VFONT_ARCADE_19_91, VFONT_ARCADE_91_99 } };
static VedgeLines vfont_arcade_char_left_square = { .length = 3, .lines = { VFONT_ARCADE_13_17, VFONT_ARCADE_93_97, VFONT_ARCADE_13_93 } };
static VedgeLines vfont_arcade_char_backslash = { .length = 1, .lines = { VFONT_ARCADE_11_99 } };
static VedgeLines vfont_arcade_char_right_square = { .length = 3, .lines = { VFONT_ARCADE_13_17, VFONT_ARCADE_93_97, VFONT_ARCADE_17_97 } };
static VedgeLines vfont_arcade_char_circumlex = { .length = 2, .lines = { VFONT_ARCADE_15_33, VFONT_ARCADE_15_37 } };
static VedgeLines vfont_arcade_char_underscore = { .length = 1, .lines = { VFONT_ARCADE_91_99 } };


// The font.
static Vfont vfont_arcade_data = {
        .char_min = 0x20,
        .char_max = 0x5F,
        .char_width = VMATHNUMBER_C( 12.0 ),
        .char_height = VMATHNUMBER_C( 12.0 ),
        .undefined_lines = &vfont_arcade_char_undefined,
        .char_lines = {
                &vfont_arcade_char_space,
                &vfont_arcade_char_exclamation,
                &vfont_arcade_char_quotation,
                &vfont_arcade_char_hash,
                &vfont_arcade_char_dollar,
                &vfont_arcade_char_percent,
                &vfont_arcade_char_ampersand,
                &vfont_arcade_char_apostrophe,
                &vfont_arcade_char_left_parenthesis,
                &vfont_arcade_char_right_parenthesis,
                &vfont_arcade_char_asterisk,
                &vfont_arcade_char_plus,
                &vfont_arcade_char_comma,
                &vfont_arcade_char_hyphen,
                &vfont_arcade_char_full_stop,
                &vfont_arcade_char_slash,
                &vfont_arcade_char_0,
                &vfont_arcade_char_1,
                &vfont_arcade_char_2,
                &vfont_arcade_char_3,
                &vfont_arcade_char_4,
                &vfont_arcade_char_5,
                &vfont_arcade_char_6,
                &vfont_arcade_char_7,
                &vfont_arcade_char_8,
                &vfont_arcade_char_9,
                &vfont_arcade_char_colon,
                &vfont_arcade_char_semicolon,
                &vfont_arcade_char_less_than,
                &vfont_arcade_char_equal,
                &vfont_arcade_char_greater_than,
                &vfont_arcade_char_question,
                &vfont_arcade_char_at,
                &vfont_arcade_char_A,
                &vfont_arcade_char_B,
                &vfont_arcade_char_C,
                &vfont_arcade_char_D,
                &vfont_arcade_char_E,
                &vfont_arcade_char_F,
                &vfont_arcade_char_G,
                &vfont_arcade_char_H,
                &vfont_arcade_char_I,
                &vfont_arcade_char_J,
                &vfont_arcade_char_K,
                &vfont_arcade_char_L,
                &vfont_arcade_char_M,
                &vfont_arcade_char_N,
                &vfont_arcade_char_O,
                &vfont_arcade_char_P,
                &vfont_arcade_char_Q,
                &vfont_arcade_char_R,
                &vfont_arcade_char_S,
                &vfont_arcade_char_T,
                &vfont_arcade_char_U,
                &vfont_arcade_char_V,
                &vfont_arcade_char_W,
                &vfont_arcade_char_X,
                &vfont_arcade_char_Y,
                &vfont_arcade_char_Z,
                &vfont_arcade_char_left_square,
                &vfont_arcade_char_backslash,
                &vfont_arcade_char_right_square,
                &vfont_arcade_char_circumlex,
                &vfont_arcade_char_underscore
        }
};


// The external reference to the font.
Vfont * vfont_arcade = &vfont_arcade_data;


#endif



//-----------------------------------------------------------------------------
// Font Functions.
//-----------------------------------------------------------------------------

// Get a font character as vEDGE lines.
const VedgeLines * vfont_get_char(const Vfont * font, const char ch)
{
    assert (font != NULL);
    if ((ch < font->char_min) || (ch > font->char_max))
    {
        return font->undefined_lines;
    }
    return font->char_lines[ch - font->char_min];
}


