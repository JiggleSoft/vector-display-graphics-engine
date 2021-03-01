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



VedgeLines vfont_ascii_lines_space = { .length = 0, .lines = {}};
VedgeLines vfont_ascii_lines_exclamation = { .length = 2, .lines = { { .x1 = 0, .y1 = -4, .x2 = 0, .y2 = 2 }, { .x1 = 0, .y1 = 3, .x2 = 0, .y2 = 4 } } };
VedgeLines vfont_ascii_lines_quotation = {0};
VedgeLines vfont_ascii_lines_hash = {0};
VedgeLines vfont_ascii_lines_dollar = {0};
VedgeLines vfont_ascii_lines_percent = {0};
VedgeLines vfont_ascii_lines_ampersand = {0};
VedgeLines vfont_ascii_lines_apostrophe = {0};
VedgeLines vfont_ascii_lines_left_parenthesis = {0};
VedgeLines vfont_ascii_lines_right_parenthesis = {0};
VedgeLines vfont_ascii_lines_asterisk = {0};
VedgeLines vfont_ascii_lines_plus = {0};
VedgeLines vfont_ascii_lines_comma = {0};
VedgeLines vfont_ascii_lines_hyphen = {0};
VedgeLines vfont_ascii_lines_full_stop = {0};
VedgeLines vfont_ascii_lines_slash = {0};
VedgeLines vfont_ascii_lines_0 = { .length = 4, .lines = { { .x1 = -4, .y1 = -4, .x2 = 4, .y2 = -4 }, { .x1 = 4, .y1 = -4, .x2 = 4, .y2 = 4 }, { .x1 = 4, .y1 = 4, .x2 = -4, .y2 = 4 }, { .x1 = -4, .y1 = 4, .x2 = -4, .y2 = -4 } } };
VedgeLines vfont_ascii_lines_1 = { .length = 1, .lines = { { .x1 = 0, .y1 = -4, .x2 = 0, .y2 = 4 } } };
VedgeLines vfont_ascii_lines_2 = { .length = 5, .lines = { { .x1 = -4, .y1 = -4, .x2 = 4, .y2 = -4 }, { .x1 = 4, .y1 = -4, .x2 = 4, .y2 = 0 }, { .x1 = 4, .y1 = 0, .x2 = -4, .y2 = 0 }, { .x1 = -4, .y1 = 0, .x2 = -4, .y2 = 4 }, { .x1 = -4, .y1 = 4, .x2 = 4, .y2 = 4 } } };
VedgeLines vfont_ascii_lines_3 = { .length = 4, .lines = { { .x1 = -4, .y1 = -4, .x2 = 4, .y2 = -4 }, { .x1 = 4, .y1 = -4, .x2 = 4, .y2 = 4 }, { .x1 = 4, .y1 = 4, .x2 = -4, .y2 = 4 }, { .x1 = -4, .y1 = 0, .x2 = 4, .y2 = 0 } } };
VedgeLines vfont_ascii_lines_4 = { .length = 3, .lines = { { .x1 = -4, .y1 = -4, .x2 = -4, .y2 = 0 }, { .x1 = -4, .y1 = 0, .x2 = 4, .y2 = 0 }, { .x1 = 4, .y1 = -4, .x2 = 4, .y2 = 4 } } };
VedgeLines vfont_ascii_lines_5 = { .length = 5, .lines = { { .x1 = 4, .y1 = -4, .x2 = -4, .y2 = -4 }, { .x1 = -4, .y1 = -4, .x2 = -4, .y2 = 0 }, { .x1 = -4, .y1 = 0, .x2 = 4, .y2 = 0 }, { .x1 = 4, .y1 = 0, .x2 = 4, .y2 = 4 }, { .x1 = 4, .y1 = 4, .x2 = -4, .y2 = 4 } } };
VedgeLines vfont_ascii_lines_6 = { .length = 5, .lines = { { .x1 = 4, .y1 = -4, .x2 = -4, .y2 = -4 }, { .x1 = -4, .y1 = -4, .x2 = -4, .y2 = 4 }, { .x1 = -4, .y1 = 4, .x2 = 4, .y2 = 4 }, { .x1 = 4, .y1 = 4, .x2 = 4, .y2 = 0 }, { .x1 = 4, .y1 = 0, .x2 = -4, .y2 = 0 } } };
VedgeLines vfont_ascii_lines_7 = { .length = 2, .lines = { { .x1 = -4, .y1 = -4, .x2 = 4, .y2 = -4 }, { .x1 = 4, .y1 = -4, .x2 = 4, .y2 = 4 } } };
VedgeLines vfont_ascii_lines_8 = { .length = 5, .lines = { { .x1 = -4, .y1 = -4, .x2 = 4, .y2 = -4 }, { .x1 = 4, .y1 = -4, .x2 = 4, .y2 = 4 }, { .x1 = 4, .y1 = 4, .x2 = -4, .y2 = 4 }, { .x1 = -4, .y1 = 4, .x2 = -4, .y2 = -4 }, { .x1 = -4, .y1 = 0, .x2 = 4, .y2 = 0 } } };
VedgeLines vfont_ascii_lines_9 = { .length = 4, .lines = { { .x1 = 4, .y1 = 0, .x2 = -4, .y2 = 0 }, { .x1 = -4, .y1 = 0, .x2 = -4, .y2 = -4 }, { .x1 = -4, .y1 = -4, .x2 = 4, .y2 = -4 }, { .x1 = 4, .y1 = -4, .x2 = 4, .y2 = 4 } } };
VedgeLines vfont_ascii_lines_colon = {0};
VedgeLines vfont_ascii_lines_semicolon = {0};
VedgeLines vfont_ascii_lines_less_than = {0};
VedgeLines vfont_ascii_lines_equal = {0};
VedgeLines vfont_ascii_lines_greater_than = {0};
VedgeLines vfont_ascii_lines_question = {0};
VedgeLines vfont_ascii_lines_at = {0};
VedgeLines vfont_ascii_lines_A = {0};
VedgeLines vfont_ascii_lines_B = {0};
VedgeLines vfont_ascii_lines_C = {0};
VedgeLines vfont_ascii_lines_D = {0};
VedgeLines vfont_ascii_lines_E = {0};
VedgeLines vfont_ascii_lines_F = {0};
VedgeLines vfont_ascii_lines_G = {0};
VedgeLines vfont_ascii_lines_H = {0};
VedgeLines vfont_ascii_lines_I = {0};
VedgeLines vfont_ascii_lines_J = {0};
VedgeLines vfont_ascii_lines_K = {0};
VedgeLines vfont_ascii_lines_L = {0};
VedgeLines vfont_ascii_lines_M = {0};
VedgeLines vfont_ascii_lines_O = {0};
VedgeLines vfont_ascii_lines_P = {0};
VedgeLines vfont_ascii_lines_Q = {0};
VedgeLines vfont_ascii_lines_R = {0};
VedgeLines vfont_ascii_lines_S = {0};
VedgeLines vfont_ascii_lines_T = {0};
VedgeLines vfont_ascii_lines_U = {0};
VedgeLines vfont_ascii_lines_V = {0};
VedgeLines vfont_ascii_lines_W = {0};
VedgeLines vfont_ascii_lines_X = {0};
VedgeLines vfont_ascii_lines_Y = {0};
VedgeLines vfont_ascii_lines_Z = {0};
VedgeLines vfont_ascii_lines_left_square = {0};
VedgeLines vfont_ascii_lines_backslash = {0};
VedgeLines vfont_ascii_lines_right_square = {0};
VedgeLines vfont_ascii_lines_circumlex = {0};
VedgeLines vfont_ascii_lines_underscore = {0};
VedgeLines vfont_ascii_lines_undefined = {0};



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