//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) vDraw CTest Util.
// Filename:     vdraw-ctest.c
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-03-29 19:17
// Version:      1.0.0-alpha-1
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


// CTest Extra include (implementation) file.
#include "ctestx.h"



//-----------------------------------------------------------------------------
// Custom vDraw Test Utility Macros.
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Custom vDraw Test Utility Functions.
//-----------------------------------------------------------------------------

// Is a line ordered left to right, otherwise top to bottom..
bool is_line_ordered(const VmathNumber x1, const VmathNumber y1,
                     const VmathNumber x2, const VmathNumber y2)
{
    return ((x1 < x2) || ((x1 == x2) && (y1 <= y2)));
}


// Is a line equal having equal start and end points.
bool is_line_equal(const VmathNumber exp_x1, const VmathNumber exp_y1,
                   const VmathNumber exp_x2, const VmathNumber exp_y2,
                   const VmathNumber real_x1, const VmathNumber real_y1,
                   const VmathNumber real_x2, const VmathNumber real_y2)
{
    return ((exp_x1 == real_x1) && (exp_y1 == real_y1) &&
            (exp_x2 == real_x2) && (exp_y2 == real_y2));
}



//-----------------------------------------------------------------------------
// Custom vDraw Test Assertions Macros And Test Assertion Functions Prototypes.
//-----------------------------------------------------------------------------

// Assertion function declaration and its client used macro.
void assert_line_ordered(const VmathNumber x1, const VmathNumber y1,
                         const VmathNumber x2, const VmathNumber y2,
                         const char* caller, int line);
#define ASSERT_LINE_ORDERED(x1, y1, x2, y2) assert_line_ordered(x1, y1, x2, y2, __FILE__, __LINE__)


// Assertion function declaration and its client used macro.
void assert_line_equal(const VmathNumber exp_x1, const VmathNumber exp_y1,
                       const VmathNumber exp_x2, const VmathNumber exp_y2,
                       const VmathNumber real_x1, const VmathNumber real_y1,
                       const VmathNumber real_x2, const VmathNumber real_y2,
                       const char* caller, int line);
#define ASSERT_LINE_EQUAL(exp_x1, exp_y1, exp_x2, exp_y2, real_x1, real_y1, real_x2, real_y2) assert_line_equal(exp_x1, exp_y1, exp_x2, exp_y2, real_x1, real_y1, real_x2, real_y2, __FILE__, __LINE__)



//-----------------------------------------------------------------------------
// Custom vDraw Test Assertions Functions Implementation.
//-----------------------------------------------------------------------------

// Assertion function definition.
void assert_line_ordered(const VmathNumber x1, const VmathNumber y1,
                         const VmathNumber x2, const VmathNumber y2,
                         const char* caller, int line)
{
    if (!is_line_ordered(x1, y2, x2, y2)) {
        CTEST_ERR("%s:%d line is not ordered for (%f,%f)-(%f,%f)\n", caller, line, x1, y1, x2, y2);
    }
}


// Assertion function definition.
void assert_line_equal(const VmathNumber exp_x1, const VmathNumber exp_y1,
                       const VmathNumber exp_x2, const VmathNumber exp_y2,
                       const VmathNumber real_x1, const VmathNumber real_y1,
                       const VmathNumber real_x2, const VmathNumber real_y2,
                       const char* caller, int line)
{
    if (!is_line_equal(exp_x1, exp_y1, exp_x2, exp_y2, real_x1, real_y1, real_x2, real_y2)) {
        CTEST_ERR("%s:%d expected line (%f,%f)-(%f,%f) got (%f,%f)-(%f,%f)\n", caller, line, exp_x1, exp_y1, exp_x2, exp_y2, real_x1, real_y1, real_x2, real_y2);
    }
}


