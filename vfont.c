//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) Font.
// Filename:     vfont.c
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (atari@jigglesoft.co.uk)
// Date:         2021-01-24 19:27
// Version:      0.0.1
//-----------------------------------------------------------------------------
// Copyright (c) 2020 Justin Lane
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


#include "vfont.h"



#define VFONT_7SEG_A { .x1 = -4, .y1 = -4, .x2 = 4, .y2 = -4 }
#define VFONT_7SEG_B { .x1 = 4, .y1 = -4, .x2 = 4, .y2 = 0 }
#define VFONT_7SEG_C { .x1 = 4, .y1 = 0, .x2 = 4, .y2 = 4 }
#define VFONT_7SEG_D { .x1 = -4, .y1 = 4, .x2 = 4, .y2 = 4 }
#define VFONT_7SEG_E { .x1 = -4, .y1 = 0, .x2 = -4, .y2 = 4 }
#define VFONT_7SEG_F { .x1 = -4, .y1 = -4, .x2 = -4, .y2 = 0 }
#define VFONT_7SEG_G { .x1 = -4, .y1 = 0, .x2 = 4, .y2 = 0 }
#define VFONT_7SEG_EF { .x1 = -4, .y1 = -4, .x2 = -4, .y2 = 4 }
#define VFONT_7SEG_BC { .x1 = 4, .y1 = -4, .x2 = 4, .y2 = 4 }


#define VFONT_16SEG_1 { .x1 = -4, .y1 = -4, .x2 = 0, .y2 = -4 }
#define VFONT_16SEG_2 { .x1 = 0, .y1 = -4, .x2 = 0, .y2 = 0 }
#define VFONT_16SEG_3 { .x1 = -4, .y1 = -4, .x2 = 0, .y2 = 0 }
#define VFONT_16SEG_4 VFONT_7SEG_F
#define VFONT_16SEG_5 { .x1 = -4, .y1 = 0, .x2 = 0, .y2 = 0 }
#define VFONT_16SEG_6 { .x1 = 0, .y1 = 0, .x2 = 0, .y2 = 4 }
#define VFONT_16SEG_7 { .x1 = 0, .y1 = 0, .x2 = -4, .y2 = 4 }
#define VFONT_16SEG_8 VFONT_7SEG_E
#define VFONT_16SEG_9 { .x1 = -4, .y1 = 4, .x2 = 0, .y2 = 4 }
#define VFONT_16SEG_10 { .x1 = 0, .y1 = 4, .x2 = 4, .y2 = 4 }
#define VFONT_16SEG_11 VFONT_7SEG_C
#define VFONT_16SEG_12 { .x1 = 0, .y1 = 0, .x2 = 4, .y2 = 4 }
#define VFONT_16SEG_13 { .x1 = 0, .y1 = 0, .x2 = 4, .y2 = 0 }
#define VFONT_16SEG_14 VFONT_7SEG_B
#define VFONT_16SEG_15 VFONT_7SEG_G
#define VFONT_16SEG_16 VFONT_7SEG_B
#define VFONT_16SEG_17 { .x1 = 0, .y1 = 0, .x2 = 4, .y2 = -4 }
#define VFONT_16SEG_18 { .x1 = 0, .y1 = -4, .x2 = 4, .y2 = -4 }

#define VFONT_16SEG_2_6 { .x1 = 0, .y1 = -4, .x2 = 0, .y2 = 4 }
#define VFONT_16SEG_3_14 { .x1 = -4, .y1 = -4, .x2 = 4, .y2 = 4 }
#define VFONT_16SEG_5_15 VFONT_7SEG_G
#define VFONT_16SEG_7_17 { .x1 = -4, .y1 = 4, .x2 = 4, .y2 = -4 }

#define VFONT_16SEG_1_18 VFONT_7SEG_A
#define VFONT_16SEG_4_8 VFONT_7SEG_EF
#define VFONT_16SEG_9_10 VFONT_7SEG_D
#define VFONT_16SEG_13_16 VFONT_7SEG_BC



VedgeLines vfont_ascii_lines_space = { .length = 0, .lines = {}};
VedgeLines vfont_ascii_lines_exclamation = { .length = 2, .lines = { { .x1 = 0, .y1 = -4, .x2 = 0, .y2 = 2 }, { .x1 = 0, .y1 = 3, .x2 = 0, .y2 = 4 } } };
VedgeLines vfont_ascii_lines_quotation = { .length = 0, .lines = {  } };
VedgeLines vfont_ascii_lines_hash = { .length = 0, .lines = {  } };
VedgeLines vfont_ascii_lines_dollar = { .length = 0, .lines = {  } };
VedgeLines vfont_ascii_lines_percent = { .length = 0, .lines = {  } };
VedgeLines vfont_ascii_lines_ampersand = { .length = 0, .lines = {  } };
VedgeLines vfont_ascii_lines_apostrophe = { .length = 0, .lines = {  } };
VedgeLines vfont_ascii_lines_left_parenthesis = { .length = 0, .lines = {  } };
VedgeLines vfont_ascii_lines_right_parenthesis = { .length = 0, .lines = {  } };
VedgeLines vfont_ascii_lines_asterisk = { .length = 4, .lines = { VFONT_16SEG_2_6, VFONT_16SEG_3_14, VFONT_16SEG_5_15, VFONT_16SEG_7_17 } };
VedgeLines vfont_ascii_lines_plus = { .length = 2, .lines = { VFONT_16SEG_2_6, VFONT_16SEG_5_15 } };
VedgeLines vfont_ascii_lines_comma = { .length = 0, .lines = {  } };
VedgeLines vfont_ascii_lines_hyphen = { .length = 1, .lines = { VFONT_16SEG_5_15 } };
VedgeLines vfont_ascii_lines_full_stop = { .length = 0, .lines = {  } };
VedgeLines vfont_ascii_lines_slash = { .length = 1, .lines = { VFONT_16SEG_7_17 } };
VedgeLines vfont_ascii_lines_0 = { .length = 4, .lines = { VFONT_7SEG_A, VFONT_7SEG_BC, VFONT_7SEG_D, VFONT_7SEG_EF } };
VedgeLines vfont_ascii_lines_1 = { .length = 1, .lines = { VFONT_16SEG_2_6 } };
VedgeLines vfont_ascii_lines_2 = { .length = 5, .lines = { VFONT_7SEG_A, VFONT_7SEG_B, VFONT_7SEG_D, VFONT_7SEG_E, VFONT_7SEG_G  } };
VedgeLines vfont_ascii_lines_3 = { .length = 4, .lines = { VFONT_7SEG_A, VFONT_7SEG_BC, VFONT_7SEG_D, VFONT_7SEG_G } };
VedgeLines vfont_ascii_lines_4 = { .length = 3, .lines = { VFONT_7SEG_BC, VFONT_7SEG_F, VFONT_7SEG_G } };
VedgeLines vfont_ascii_lines_5 = { .length = 5, .lines = { VFONT_7SEG_A, VFONT_7SEG_C, VFONT_7SEG_D, VFONT_7SEG_F, VFONT_7SEG_G } };
VedgeLines vfont_ascii_lines_6 = { .length = 5, .lines = { VFONT_7SEG_A, VFONT_7SEG_C, VFONT_7SEG_D, VFONT_7SEG_EF, VFONT_7SEG_G } };
VedgeLines vfont_ascii_lines_7 = { .length = 2, .lines = { VFONT_7SEG_A, VFONT_7SEG_BC } };
VedgeLines vfont_ascii_lines_8 = { .length = 5, .lines = { VFONT_7SEG_A, VFONT_7SEG_BC, VFONT_7SEG_D, VFONT_7SEG_EF, VFONT_7SEG_G } };
VedgeLines vfont_ascii_lines_9 = { .length = 4, .lines = { VFONT_7SEG_A, VFONT_7SEG_BC, VFONT_7SEG_F, VFONT_7SEG_G } };
VedgeLines vfont_ascii_lines_colon = { .length = 0, .lines = {  } };
VedgeLines vfont_ascii_lines_semicolon = { .length = 0, .lines = {  } };
VedgeLines vfont_ascii_lines_less_than = { .length = 2, .lines = { { .x1 = -4, .y1 = 0, .x2 = 4, .y2 = -4 }, { .x1 = -4, .y1 = 0, .x2 = 4, .y2 = 4 }  } };
VedgeLines vfont_ascii_lines_equal = { .length = 2, .lines = { { .x1 = -4, .y1 = -1, .x2 = 4, .y2 = -1 }, { .x1 = -4, .y1 = 1, .x2 = 4, .y2 = 1 } } };
VedgeLines vfont_ascii_lines_greater_than = { .length = 2, .lines = { { .x1 = -4, .y1 = -4, .x2 = 4, .y2 = 0 }, { .x1 = -4, .y1 = 4, .x2 = 4, .y2 = 0 } } };
VedgeLines vfont_ascii_lines_question = { .length = 0, .lines = {  } };
VedgeLines vfont_ascii_lines_at = { .length = 8, .lines = { { .x1 = 2, .y1 = 2, .x2 = 2, .y2 = -2 }, { .x1 = 2, .y1 = -2, .x2 = -2, .y2 = -2 }, { .x1 = -2, .y1 = -2, .x2 = -2, .y2 = 2 }, { .x1 = -2, .y1 = 2, .x2 = 4, .y2 = 2 }, { .x1 = 4, .y1 = 2, .x2 = 4, .y2 = -4 }, { .x1 = 4, .y1 = -4, .x2 = -4, .y2 = -4 }, { .x1 = -4, .y1 = -4, .x2 = -4, .y2 = 4 }, { .x1 = -4, .y1 = 4, .x2 = 4, .y2 = 4 } } };
VedgeLines vfont_ascii_lines_A = { .length = 4, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4_8, VFONT_16SEG_5_15, VFONT_16SEG_13_16 } };
VedgeLines vfont_ascii_lines_B = { .length = 5, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_2_6, VFONT_16SEG_9_10, VFONT_16SEG_13_16, VFONT_16SEG_15 } };
VedgeLines vfont_ascii_lines_C = { .length = 3, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4_8, VFONT_16SEG_9_10 } };
VedgeLines vfont_ascii_lines_D = { .length = 4, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_2_6, VFONT_16SEG_9_10, VFONT_16SEG_13_16 } };
VedgeLines vfont_ascii_lines_E = { .length = 4, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4_8, VFONT_16SEG_5, VFONT_16SEG_9_10 } };
VedgeLines vfont_ascii_lines_F = { .length = 3, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4_8, VFONT_16SEG_5 } };
VedgeLines vfont_ascii_lines_G = { .length = 0, .lines = {  } };
VedgeLines vfont_ascii_lines_H = { .length = 3, .lines = { VFONT_16SEG_4_8, VFONT_16SEG_5_15, VFONT_16SEG_13_16 } };
VedgeLines vfont_ascii_lines_I = { .length = 3, .lines = {  } };
VedgeLines vfont_ascii_lines_J = { .length = 0, .lines = {  } };
VedgeLines vfont_ascii_lines_K = {0};//{ .length = 3, .lines = { , VFONT_16SEG_, VFONT_16SEG_, VFONT_16SEG_ } };
VedgeLines vfont_ascii_lines_L = { .length = 2, .lines = { VFONT_16SEG_4_8, VFONT_16SEG_9_10 } };
VedgeLines vfont_ascii_lines_M = {0};//{ .length = 4, .lines = { , VFONT_16SEG_, VFONT_16SEG_, VFONT_16SEG_, VFONT_16SEG_ } };
VedgeLines vfont_ascii_lines_O = { .length = 4, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4_8, VFONT_16SEG_9_10, VFONT_16SEG_13_16 } };
VedgeLines vfont_ascii_lines_P = { .length = 4, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_4_8, VFONT_16SEG_5_15, VFONT_16SEG_16 } };
VedgeLines vfont_ascii_lines_Q = {0};//{ .length = 5, .lines = { , VFONT_16SEG_, VFONT_16SEG_, VFONT_16SEG_, VFONT_16SEG_, VFONT_16SEG_ } };
VedgeLines vfont_ascii_lines_R = {0};//{ .length = 5, .lines = { , VFONT_16SEG_, VFONT_16SEG_, VFONT_16SEG_, VFONT_16SEG_, VFONT_16SEG_ } };
VedgeLines vfont_ascii_lines_S = { .length = 5, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_5_15, VFONT_16SEG_8, VFONT_16SEG_9_10, VFONT_16SEG_16 } };
VedgeLines vfont_ascii_lines_T = { .length = 2, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_2_6 } };
VedgeLines vfont_ascii_lines_U = { .length = 3, .lines = { VFONT_16SEG_4_8, VFONT_16SEG_9_10, VFONT_16SEG_13_16 } };
VedgeLines vfont_ascii_lines_V = {0};//{ .length = 2, .lines = { , VFONT_16SEG_, VFONT_16SEG_ } };
VedgeLines vfont_ascii_lines_W = {0};//{ .length = 4, .lines = { , VFONT_16SEG_, VFONT_16SEG_, VFONT_16SEG_, VFONT_16SEG_ } };
VedgeLines vfont_ascii_lines_X = { .length = 2, .lines = { VFONT_16SEG_3_14, VFONT_16SEG_7_17 } };
VedgeLines vfont_ascii_lines_Y = { .length = 3, .lines = { VFONT_16SEG_3, VFONT_16SEG_6, VFONT_16SEG_17 } };
VedgeLines vfont_ascii_lines_Z = { .length = 3, .lines = { VFONT_16SEG_1_18, VFONT_16SEG_9_10, VFONT_16SEG_7_17 } };
VedgeLines vfont_ascii_lines_left_square = { .length = 3, .lines = { VFONT_16SEG_1, VFONT_16SEG_4_8, VFONT_16SEG_9 } };
VedgeLines vfont_ascii_lines_backslash = { .length = 1, .lines = { VFONT_16SEG_3_14 } };
VedgeLines vfont_ascii_lines_right_square = { .length = 3, .lines = { VFONT_16SEG_10, VFONT_16SEG_13_16, VFONT_16SEG_18 } };
VedgeLines vfont_ascii_lines_circumlex = { .length = 0, .lines = { } };
VedgeLines vfont_ascii_lines_underscore = { .length = 1, .lines = { VFONT_16SEG_9_10 } };

VedgeLines vfont_ascii_lines_undefined = { .length = 0, .lines = {  } };



VedgeLines* vfont_ascii_lines[64] = {
    &vfont_ascii_lines_space,
    &vfont_ascii_lines_exclamation,
    &vfont_ascii_lines_quotation,
    &vfont_ascii_lines_hash,
    &vfont_ascii_lines_dollar,
    &vfont_ascii_lines_percent,
    &vfont_ascii_lines_ampersand,
    &vfont_ascii_lines_apostrophe,
    &vfont_ascii_lines_left_parenthesis,
    &vfont_ascii_lines_right_parenthesis,
    &vfont_ascii_lines_asterisk,
    &vfont_ascii_lines_plus,
    &vfont_ascii_lines_comma,
    &vfont_ascii_lines_hyphen,
    &vfont_ascii_lines_full_stop,
    &vfont_ascii_lines_slash,
    &vfont_ascii_lines_0,
    &vfont_ascii_lines_1,
    &vfont_ascii_lines_2,
    &vfont_ascii_lines_3,
    &vfont_ascii_lines_4,
    &vfont_ascii_lines_5,
    &vfont_ascii_lines_6,
    &vfont_ascii_lines_7,
    &vfont_ascii_lines_8,
    &vfont_ascii_lines_9,
    &vfont_ascii_lines_colon,
    &vfont_ascii_lines_semicolon,
    &vfont_ascii_lines_less_than,
    &vfont_ascii_lines_equal,
    &vfont_ascii_lines_greater_than,
    &vfont_ascii_lines_question,
    &vfont_ascii_lines_at,
    &vfont_ascii_lines_A,
    &vfont_ascii_lines_B,
    &vfont_ascii_lines_C,
    &vfont_ascii_lines_D,
    &vfont_ascii_lines_E,
    &vfont_ascii_lines_F,
    &vfont_ascii_lines_G,
    &vfont_ascii_lines_H,
    &vfont_ascii_lines_I,
    &vfont_ascii_lines_J,
    &vfont_ascii_lines_K,
    &vfont_ascii_lines_L,
    &vfont_ascii_lines_M,
    &vfont_ascii_lines_O,
    &vfont_ascii_lines_P,
    &vfont_ascii_lines_Q,
    &vfont_ascii_lines_R,
    &vfont_ascii_lines_S,
    &vfont_ascii_lines_T,
    &vfont_ascii_lines_U,
    &vfont_ascii_lines_V,
    &vfont_ascii_lines_W,
    &vfont_ascii_lines_X,
    &vfont_ascii_lines_Y,
    &vfont_ascii_lines_Z,
    &vfont_ascii_lines_left_square,
    &vfont_ascii_lines_backslash,
    &vfont_ascii_lines_right_square,
    &vfont_ascii_lines_circumlex,
    &vfont_ascii_lines_underscore
};


VedgeLines* vfont_get_ascii_char(char ch)
{
    if ((ch < 0x020) || (ch > 0x5F))
    {
        return &vfont_ascii_lines_undefined;
    }
    return vfont_ascii_lines[ch-VFONT_ASCII_LINES_OFFSET];
}
/* ASCII VECTOR FONT 0x20 to 0x5F */


/*
0
1
2
3
4
5
6
7
8
9


A
B
C
+4,+4,-4,+4
-4,+4,-4,-4
-4,-4,+4,-4

D

E
+4,+4,-4,+4
-4,+4,-4,-4
-4,-4,+4,-4
-4,0,+4,0


F
+4,+4,-4,+4
-4,+4,-4,-4
-4,0,+4,0


G

H
-4,+4,-4,-4
-4,0,+4,0
+4,-4,+4,+4

I
-1,+4,1,+4
0,+4,0,-4
-1,-4,1,-4


J
K
L
M
N
-4,-4,-4,+4
-4,+4,+4,-4
+4,-4,+4,+4

O
+4,+4,-4,+4
-4,+4,-4,-4
-4,-4,+4,-4
+4,-4,+4,+4

P
+4,+4,-4,+4
-4,+4,-4,-4
-4,0,+4,0
+4,0,+4,+4


Q
R
S
T
U
V
W
X
Y
Z


space
!
?
arrow left
arrow R
arrow UP
arrow DOWN

HASH
+
-
=
/
<
>
.
,
"
$
%
^
&
*
(
)
[
        ]
        ~
        :
        ;

'
        )

*/