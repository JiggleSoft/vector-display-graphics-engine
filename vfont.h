//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) Font.
// Filename:     vfont.h
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

#ifndef __VFONT__H__
#define __VFONT__H__


#include "vedge.h"


#define VFONT_ASCII_LINES_OFFSET (0x20)


extern VedgeLines vfont_ascii_lines_undefined;

extern VedgeLines vfont_ascii_lines_space;
extern VedgeLines vfont_ascii_lines_exclamation;
extern VedgeLines vfont_ascii_lines_quotation;
extern VedgeLines vfont_ascii_lines_hash;
extern VedgeLines vfont_ascii_lines_dollar;
extern VedgeLines vfont_ascii_lines_percent;
extern VedgeLines vfont_ascii_lines_ampersand;
extern VedgeLines vfont_ascii_lines_apostrophe;
extern VedgeLines vfont_ascii_lines_left_parenthesis;
extern VedgeLines vfont_ascii_lines_right_parenthesis;
extern VedgeLines vfont_ascii_lines_asterisk;
extern VedgeLines vfont_ascii_lines_plus;
extern VedgeLines vfont_ascii_lines_comma;
extern VedgeLines vfont_ascii_lines_hyphen;
extern VedgeLines vfont_ascii_lines_full_stop;
extern VedgeLines vfont_ascii_lines_slash;
extern VedgeLines vfont_ascii_lines_0;
extern VedgeLines vfont_ascii_lines_1;
extern VedgeLines vfont_ascii_lines_2;
extern VedgeLines vfont_ascii_lines_3;
extern VedgeLines vfont_ascii_lines_4;
extern VedgeLines vfont_ascii_lines_5;
extern VedgeLines vfont_ascii_lines_6;
extern VedgeLines vfont_ascii_lines_7;
extern VedgeLines vfont_ascii_lines_8;
extern VedgeLines vfont_ascii_lines_9;
extern VedgeLines vfont_ascii_lines_colon;
extern VedgeLines vfont_ascii_lines_semicolon;
extern VedgeLines vfont_ascii_lines_less_than;
extern VedgeLines vfont_ascii_lines_equal;
extern VedgeLines vfont_ascii_lines_greater_than;
extern VedgeLines vfont_ascii_lines_question;
extern VedgeLines vfont_ascii_lines_at;
extern VedgeLines vfont_ascii_lines_A;
extern VedgeLines vfont_ascii_lines_B;
extern VedgeLines vfont_ascii_lines_C;
extern VedgeLines vfont_ascii_lines_D;
extern VedgeLines vfont_ascii_lines_E;
extern VedgeLines vfont_ascii_lines_F;
extern VedgeLines vfont_ascii_lines_G;
extern VedgeLines vfont_ascii_lines_H;
extern VedgeLines vfont_ascii_lines_I;
extern VedgeLines vfont_ascii_lines_J;
extern VedgeLines vfont_ascii_lines_K;
extern VedgeLines vfont_ascii_lines_L;
extern VedgeLines vfont_ascii_lines_M;
extern VedgeLines vfont_ascii_lines_O;
extern VedgeLines vfont_ascii_lines_P;
extern VedgeLines vfont_ascii_lines_Q;
extern VedgeLines vfont_ascii_lines_R;
extern VedgeLines vfont_ascii_lines_S;
extern VedgeLines vfont_ascii_lines_T;
extern VedgeLines vfont_ascii_lines_U;
extern VedgeLines vfont_ascii_lines_V;
extern VedgeLines vfont_ascii_lines_W;
extern VedgeLines vfont_ascii_lines_X;
extern VedgeLines vfont_ascii_lines_Y;
extern VedgeLines vfont_ascii_lines_Z;
extern VedgeLines vfont_ascii_lines_left_square;
extern VedgeLines vfont_ascii_lines_backslash;
extern VedgeLines vfont_ascii_lines_right_square;
extern VedgeLines vfont_ascii_lines_circumlex;
extern VedgeLines vfont_ascii_lines_backslash;




extern VedgeLines* vfont_ascii_lines[64];



extern VedgeLines* vfont_get_ascii_char(char ch);



#endif /* __VFONT__H__ */


