//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) Font.
// Filename:     vfont.h
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

#ifndef __VFONT__H__
#define __VFONT__H__


#include "vedge.h"


//-----------------------------------------------------------------------------
// Font Data Types.
//-----------------------------------------------------------------------------

// Fixed size font with origin [0.0,0.0] at approx. half the width and height.
typedef struct Vfont {
    // The lowest ASCII character value supported.
    const int char_min;
    // The maximum ASCII character value supported.
    const int char_max;
    // The width of the characters.
    const VmathNumber char_width;
    // The height of the characters.
    const VmathNumber char_height;
    // The graphical lines to be returned for characters that are undefined.
    const VedgeLines * undefined_lines;
    // The graphical lines that make up this font.
    const VedgeLines * char_lines[];
} Vfont;



//-----------------------------------------------------------------------------
// Fonts Data.
//-----------------------------------------------------------------------------

// 7-segment font (disabled by default; enable if required).
#ifdef VFONT_7SEG_ENABLE
extern Vfont * vfont_7seg;
#endif


// 16-segment font (disabled by default; enable if required).
#ifdef VFONT_16SEG_ENABLE
extern Vfont * vfont_16seg;
#endif


// Arcade font (enabled by default; disable if not required).
#ifndef VFONT_ARCADE_DISABLE
extern Vfont * vfont_arcade;
#endif



//-----------------------------------------------------------------------------
// Font Functions.
//-----------------------------------------------------------------------------

// Get a font character as vEDGE lines.
extern const VedgeLines * vfont_get_char(const Vfont * font, const char ch);



#endif /* __VFONT__H__ */


