//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) Mathematics CTest Util.
// Filename:     vmath-ctest.h
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-03-29 17:47
// Version:      1.0.0-beta-3
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
// Custom vMath Test Utility Macros.
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Custom vMath Test Utility Functions.
//-----------------------------------------------------------------------------

// Test two vmath numbers for equality.
int is_vmathnumber_equal(const VmathNumber number1, const VmathNumber number2)
{
    return (number1 == number2);
}


// Test two 3x1 matrices for equality.
int is_matrix3x1_equal(const VmathMatrix3x1 matrix1, const VmathMatrix3x1 matrix2)
{
    for (int x = 0;  x < 3;  x++) {
        if (matrix1[x] != matrix2[x]) {
            return 0;
        }
    }
    return 1;
}


// Test two 3x1 matrices for equality with given tolerance.
int is_matrix3x1_equal_tol(const VmathMatrix3x1 matrix1, const VmathMatrix3x1 matrix2, const double tol)
{
    for (int x = 0;  x < 3;  x++) {
        double diff = matrix1[x] - matrix2[x];
        double absdiff = diff;
        /* avoid using fabs and linking with a math lib */
        if(diff < 0) {
            absdiff *= -1;
        }
        if (absdiff > tol) {
            return 0;
        }
    }
    return 1;
}


// Test two 3x3 matrices for equality.
int is_matrix3x3_equal(const VmathMatrix3x3 matrix1, const VmathMatrix3x3 matrix2)
{
    for (int y = 0;  y < 3;  y++) {
        for (int x = 0;  x < 3;  x++) {
            if (matrix1[y][x] != matrix2[y][x]) {
                return 0;
            }
        }
    }
    return 1;
}


// Test two 3x3 matrices for equality with given tolerance.
int is_matrix3x3_equal_tol(const VmathMatrix3x3 matrix1, const VmathMatrix3x3 matrix2, const double tol)
{
    for (int y = 0;  y < 3;  y++) {
        for (int x = 0;  x < 3;  x++) {
            double diff = matrix1[y][x] - matrix2[y][x];
            double absdiff = diff;
            /* avoid using fabs and linking with a math lib */
            if(diff < 0) {
                absdiff *= -1;
            }
            if (absdiff > tol) {
                return 0;
            }
        }
    }
    return 1;
}



//-----------------------------------------------------------------------------
// Custom vMath Test Assertions Macros And Test Assertion Functions Prototypes.
//-----------------------------------------------------------------------------

// Assertion function declaration and its client used macro.
void assert_vmathnumber_equal(const VmathNumber exp, const VmathNumber real, const char* caller, int line);
#define ASSERT_VMATHNUMBER_EQUAL(exp, real) assert_vmathnumber_equal(exp, real, __FILE__, __LINE__)


// Assertion function declaration and its client used macro.
void assert_matrix3x1_equal(const VmathMatrix3x1 exp, const VmathMatrix3x1 real, const char* caller, int line);
#define ASSERT_MATRIX3X1_EQUAL(exp, real) assert_matrix3x1_equal(exp, real, __FILE__, __LINE__)


// Assertion function declaration and its client used macro.
void assert_matrix3x1_equal_tol(const VmathMatrix3x1 exp, const VmathMatrix3x1 real, const double tol, const char* caller, int line);
#define ASSERT_MATRIX3X1_EQUAL_TOL(exp, real, tol) assert_matrix3x1_equal_tol(exp, real, tol, __FILE__, __LINE__)


// Assertion function declaration and its client used macro.
void assert_matrix3x3_equal(const VmathMatrix3x3 exp, const VmathMatrix3x3 real, const char* caller, int line);
#define ASSERT_MATRIX3X3_EQUAL(exp, real) assert_matrix3x3_equal(exp, real, __FILE__, __LINE__)


// Assertion function declaration and its client used macro.
void assert_matrix3x3_equal_tol(const VmathMatrix3x3 exp, const VmathMatrix3x3 real, const double tol, const char* caller, int line);
#define ASSERT_MATRIX3X3_EQUAL_TOL(exp, real, tol) assert_matrix3x3_equal_tol(exp, real, tol, __FILE__, __LINE__)



//-----------------------------------------------------------------------------
// Custom vMath Test Assertions Functions Implementation.
//-----------------------------------------------------------------------------

// Assertion function definition.
void assert_vmathnumber_equal(const VmathNumber exp, const VmathNumber real, const char* caller, int line)
{
    if (!is_vmathnumber_equal(exp, real)) {
        CTEST_ERR("%s:%d expected vmath number %f got %f", caller, line, exp, real);
    }
}


// Assertion function definition.
void assert_matrix3x1_equal(const VmathMatrix3x1 exp, const VmathMatrix3x1 real, const char* caller, int line)
{
    if (!is_matrix3x1_equal(exp, real)) {
        CTEST_ERR("%s:%d expected matrix 3x1 [%f,%f,%f] got [%f,%f,%f]", caller, line,
            exp[0], exp[1], exp[2], real[0], real[1], real[2]);
    }
}


// Assertion function definition.
void assert_matrix3x1_equal_tol(const VmathMatrix3x1 exp, const VmathMatrix3x1 real, double tol, const char* caller, int line)
{
    if (!is_matrix3x1_equal_tol(exp, real, tol)) {
        CTEST_ERR("%s:%d expected matrix 3x1 [%f,%f,%f] got [%f,%f,%f] tolerance %f", caller, line,
            exp[0], exp[1], exp[2], real[0], real[1], real[2], tol);
    }
}


// Assertion function definition.
void assert_matrix3x3_equal(const VmathMatrix3x3 exp, const VmathMatrix3x3 real, const char* caller, int line)
{
    if (!is_matrix3x3_equal(exp, real)) {
        CTEST_ERR("%s:%d expected matrix 3x3 [[%f,%f,%f],[%f,%f,%f],[%f,%f,%f]] got [[%f,%f,%f],[%f,%f,%f],[%f,%f,%f]]",
            caller, line,
            exp[0][0], exp[0][1], exp[0][2], exp[1][0], exp[1][1], exp[1][2], exp[2][0], exp[2][1], exp[2][2],
            real[0][0], real[0][1], real[0][2], real[1][0], real[1][1], real[1][2], real[2][0], real[2][1], real[2][2]);
    }
}


// Assertion function definition.
void assert_matrix3x3_equal_tol(const VmathMatrix3x3 exp, const VmathMatrix3x3 real, const double tol, const char* caller, int line)
{
    if (!is_matrix3x3_equal_tol(exp, real, tol)) {
        CTEST_ERR("%s:%d expected matrix 3x3 [[%f,%f,%f],[%f,%f,%f],[%f,%f,%f]] got [[%f,%f,%f],[%f,%f,%f],[%f,%f,%f]] tolerance %f",
                  caller, line,
                  exp[0][0], exp[0][1], exp[0][2], exp[1][0], exp[1][1], exp[1][2], exp[2][0], exp[2][1], exp[2][2],
                  real[0][0], real[0][1], real[0][2], real[1][0], real[1][1], real[1][2], real[2][0], real[2][1], real[2][2],
                  tol);
    }
}


