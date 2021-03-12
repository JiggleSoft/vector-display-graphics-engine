//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) Mathematics Unit Tests.
// Filename:     vmath-tests.c
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-03-12 20:33
// Version:      0.9.1
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

// API under test.
#include "vmath.h"


// CTest configuration.
#define CTEST_MAIN
#define CTEST_SEGFAULT

// CTest include / implementation.
#include "ctest.h"



//-----------------------------------------------------------------------------
// Custom Vmath Test Utilities.
//-----------------------------------------------------------------------------

// .
#define countof(a) (sizeof(a) / sizeof(a[0]))


// .
int is_vmathnumber_equal(const VmathNumber number1, const VmathNumber number2)
{
    return (number1 == number2);
}


// .
int is_matrix3x1_equal(const VmathMatrix3x1 matrix1, const VmathMatrix3x1 matrix2)
{
    for (int x = 0;  x < 3;  x++) {
        if (matrix1[x] != matrix2[x]) {
            return 0;
        }
    }
    return 1;
}


// .
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



//-----------------------------------------------------------------------------
// Custom Vmath Test Assertions Macros.
//-----------------------------------------------------------------------------

// .
void assert_vmathnumber_equal(const VmathNumber exp, const VmathNumber real, const char* caller, int line);
#define ASSERT_VMATHNUMBER_EQUAL(exp, real) assert_vmathnumber_equal(exp, real, __FILE__, __LINE__)


// .
void assert_matrix3x1_equal(const VmathMatrix3x1 exp, const VmathMatrix3x1 real, const char* caller, int line);
#define ASSERT_MATRIX3X1_EQUAL(exp, real) assert_matrix3x1_equal(exp, real, __FILE__, __LINE__)


// .
void vmath_matrix3x3_equal(const VmathMatrix3x3 exp, const VmathMatrix3x3 real, const char* caller, int line);
#define ASSERT_MATRIX3X3_EQUAL(exp, real) assert_matrix3x3_equal(exp, real, __FILE__, __LINE__)



//-----------------------------------------------------------------------------
// Custom Vmath Test Assertions Functions.
//-----------------------------------------------------------------------------

// .
void assert_vmathnumber_equal(const VmathNumber exp, const VmathNumber real, const char* caller, int line)
{
    if (!is_vmathnumber_equal(exp, real)) {
        CTEST_ERR("%s:%d expected vmath number %f got %f", caller, line, exp, real);
    }
}


// .
void assert_matrix3x1_equal(const VmathMatrix3x1 exp, const VmathMatrix3x1 real, const char* caller, int line)
{
    if (!is_matrix3x1_equal(exp, real)) {
        CTEST_ERR("%s:%d expected matrix 3x1 [%f,%f,%f] got [%f,%f,%f]", caller, line,
            exp[0], exp[1], exp[2], real[0], real[1], real[2]);
    }
}


// .
void assert_matrix3x3_equal(const VmathMatrix3x3 exp, const VmathMatrix3x3 real, const char* caller, int line)
{
    if (!is_matrix3x3_equal(exp, real)) {
        CTEST_ERR("%s:%d matrix [[%f,%f,%f],[%f,%f,%f],[%f,%f,%f]] should be [[%f,%f,%f],[%f,%f,%f],[%f,%f,%f]]",
            caller, line,
            exp[0][0], exp[0][1], exp[0][2], exp[1][0], exp[1][1], exp[1][2], exp[2][0], exp[2][1], exp[2][2],
            real[0][0], real[0][1], real[0][2], real[1][0], real[1][1], real[1][2], real[2][0], real[2][1], real[2][2]);
    }
}



//-----------------------------------------------------------------------------
// Test Fixture Lifecycle.
//-----------------------------------------------------------------------------

CTEST_DATA(vmath) {
};


CTEST_SETUP(vmath)
{
    vmath_init();
}


CTEST_TEARDOWN(vmath)
{
    vmath_done();
}



//-----------------------------------------------------------------------------
// Test Trigonometry Functions.
//-----------------------------------------------------------------------------

CTEST(vmath, test_vmath_mbr_sin) {
    const VmathNumber values[] = {
            VMATHNUMBER_C( 0.0 ), // 0 degrees
            VMATHNUMBER_C( 128.0 ), // 45 degrees
            VMATHNUMBER_C( 256.0 ), // 90 degrees
            VMATHNUMBER_C( 512.0 ), // 180 degrees
            VMATHNUMBER_C( 768.0 ), // 270 degrees
            VMATHNUMBER_C( 1024.0 ), // 360 degrees
            VMATHNUMBER_C( 1152.0 )}; // 405 degrees
    const VmathNumber expects[] = {
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.7071067812 ),
            VMATHNUMBER_C( 1.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( -1.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.7071067812                                                                                                                  )};
    for (int i = 0;  i < countof(values);  i++) {
        const VmathNumber output = vmath_mbr_sin(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_NEAR(expect, output);
    }
}


CTEST(vmath, test_vmath_mbr_cos) {
    const VmathNumber values[] = {
            VMATHNUMBER_C( 0.0 ), // 0 degrees
            VMATHNUMBER_C( 128.0 ), // 45 degrees
            VMATHNUMBER_C( 256.0 ), // 90 degrees
            VMATHNUMBER_C( 512.0 ), // 180 degrees
            VMATHNUMBER_C( 768.0 ), // 270 degrees
            VMATHNUMBER_C( 1024.0 ), // 360 degrees
            VMATHNUMBER_C( 1152.0 )}; // 405 degrees
    const VmathNumber expects[] = {
            VMATHNUMBER_C( 1.0 ),
            VMATHNUMBER_C( 0.7071067812 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( -1.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 1.0 ),
            VMATHNUMBER_C( 0.7071067812 )};
    for (int i = 0;  i < countof(values);  i++) {
        const VmathNumber output = vmath_mbr_cos(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_NEAR(expect, output);
    }
}



//-----------------------------------------------------------------------------
// Test Angle Conversion Functions.
//-----------------------------------------------------------------------------

CTEST(vmath, test_vmath_rad_to_mbr) {
    const VmathNumber values[] = {
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.785398 ), // 45 degrees
            VMATHNUMBER_C( 1.5708 ), // 90 degrees
            VMATHNUMBER_C( 3.14159 ), // 180 degrees
            VMATHNUMBER_C( 4.71239 ), // 270 degrees
            VMATHNUMBER_C( 0.0 ), // 360 degrees
            VMATHNUMBER_C( 0.785398 )}; // 405 degrees
    const VmathNumber expects[] = {
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 128.0 ),
            VMATHNUMBER_C( 256.0 ),
            VMATHNUMBER_C( 512.0 ),
            VMATHNUMBER_C( 768.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 128.0 )};
    for (int i = 0;  i < countof(values);  i++) {
        const VmathNumber output = vmath_rad_to_mbr(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_NEAR(expect, output);
    }
}


CTEST(vmath, test_vmath_deg_to_mbr) {
    const VmathNumber values[] = {
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 45.0 ),
            VMATHNUMBER_C( 90.0 ),
            VMATHNUMBER_C( 180.0 ),
            VMATHNUMBER_C( 270.0 ),
            VMATHNUMBER_C( 360.0 ),
            VMATHNUMBER_C( 405.0 )};
    const VmathNumber expects[] = {
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 128.0 ),
            VMATHNUMBER_C( 256.0 ),
            VMATHNUMBER_C( 512.0 ),
            VMATHNUMBER_C( 768.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 128.0 )};
    for (int i = 0;  i < countof(values);  i++) {
        const VmathNumber output = vmath_deg_to_mbr(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_NEAR(expect, output);
    }
}


CTEST(vmath, test_vmath_mbr_to_rad) {
    const VmathNumber values[] = {
            VMATHNUMBER_C( 0.0 ), // 0 degrees
            VMATHNUMBER_C( 128.0 ), // 45 degrees
            VMATHNUMBER_C( 256.0 ), // 90 degrees
            VMATHNUMBER_C( 512.0 ), // 180 degrees
            VMATHNUMBER_C( 760.0 ), // 270 degrees
            VMATHNUMBER_C( 0.0 ), // 360 degrees
            VMATHNUMBER_C( 128.0 )}; // 405 degrees
    const VmathNumber expects[] = {
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.785398 ),
            VMATHNUMBER_C( 1.5708 ),
            VMATHNUMBER_C( 3.14159 ),
            VMATHNUMBER_C( 4.71239 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.785398 )};
    for (int i = 0;  i < countof(values);  i++) {
        const VmathNumber output = vmath_mbr_to_rad(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_NEAR(expect, output);
    }
}


CTEST(vmath, test_vmath_deg_to_rad) {
    const VmathNumber values[] = {
            VMATHNUMBER_C( -540.0 ),
            VMATHNUMBER_C( -180.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 45.0 ),
            VMATHNUMBER_C( 90.0 ),
            VMATHNUMBER_C( 180.0 ),
            VMATHNUMBER_C( 270.0 ),
            VMATHNUMBER_C( 360.0 ),
            VMATHNUMBER_C( 405.0 )};
    const VmathNumber expects[] = {
            VMATHNUMBER_C( -9.42477795 ),
            VMATHNUMBER_C( -3.14159265 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.785398163 ),
            VMATHNUMBER_C( 1.570796325 ),
            VMATHNUMBER_C( 3.14159265 ),
            VMATHNUMBER_C( 4.712388975 ),
            VMATHNUMBER_C( 6.2831853 ),
            VMATHNUMBER_C( 7.068583463 )};
    for (int i = 0;  i < countof(values);  i++) {
        const VmathNumber output = vmath_deg_to_rad(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_NEAR(expect, output);
    }
}


CTEST(vmath, test_vmath_mbr_to_deg) {
    const VmathNumber values[] = {
            VMATHNUMBER_C( 0.0 ), // 0 degrees
            VMATHNUMBER_C( 128.0 ), // 45 degrees
            VMATHNUMBER_C( 256.0 ), // 90 degrees
            VMATHNUMBER_C( 512.0 ), // 180 degrees
            VMATHNUMBER_C( 760.0 ), // 270 degrees
            VMATHNUMBER_C( 0.0 ), // 360 degrees
            VMATHNUMBER_C( 128.0 )}; // 405 degrees
    const VmathNumber expects[] = {
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 45.0 ),
            VMATHNUMBER_C( 90.0 ),
            VMATHNUMBER_C( 180.0 ),
            VMATHNUMBER_C( 270.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 45.0 )};
    for (int i = 0;  i < countof(values);  i++) {
        const VmathNumber output = vmath_mbr_to_deg(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_NEAR(expect, output);
    }
}


CTEST(vmath, test_vmath_rad_to_deg) {
    const VmathNumber values[] = {
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.785398 ), // 45 degrees
            VMATHNUMBER_C( 1.5708 ), // 90 degrees
            VMATHNUMBER_C( 3.14159 ), // 180 degrees
            VMATHNUMBER_C( 4.71239 ), // 270 degrees
            VMATHNUMBER_C( 0.0 ), // 360 degrees
            VMATHNUMBER_C( 0.785398 )}; // 405 degrees
    const VmathNumber expects[] = {
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 45.0 ),
            VMATHNUMBER_C( 90.0 ),
            VMATHNUMBER_C( 180.0 ),
            VMATHNUMBER_C( 270.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 45.0 )};
    for (int i = 0;  i < countof(values);  i++) {
        const VmathNumber output = vmath_rad_to_deg(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_NEAR(expect, output);
    }
}



//-----------------------------------------------------------------------------
// Angle Normalisation Functions.
//-----------------------------------------------------------------------------

CTEST(vmath, test_vmath_normalise_mbr) {
    const VmathNumber values[] = {
            VMATHNUMBER_C( -2048.7 ),
            VMATHNUMBER_C( -2048.0 ),
            VMATHNUMBER_C( -1792.0 ),
            VMATHNUMBER_C( -1280.0 ),
            VMATHNUMBER_C( -1024.0 ),
            VMATHNUMBER_C( -768.0 ),
            VMATHNUMBER_C( -512.0 ),
            VMATHNUMBER_C( -256.0 ),
            VMATHNUMBER_C( -0.7 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.7 ),
            VMATHNUMBER_C( 256.0 ),
            VMATHNUMBER_C( 512.0 ),
            VMATHNUMBER_C( 768.0 ),
            VMATHNUMBER_C( 1024.0 ),
            VMATHNUMBER_C( 1280.0 ),
            VMATHNUMBER_C( 1792.0 ),
            VMATHNUMBER_C( 2048.0 ),
            VMATHNUMBER_C( 2048.7 ),
            };
    const VmathNumber expects[] = {
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 )};
    for (int i = 0;  i < countof(values);  i++) {
        const VmathNumber output = vmath_normalise_mbr(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_VMATHNUMBER_EQUAL(expect, output);
    }
}

CTEST(vmath, test_vmath_normalise_rad) {
    const VmathNumber values[] = {
            VMATHNUMBER_C( -2048.7 ),
            VMATHNUMBER_C( -2048.0 ),
            VMATHNUMBER_C( -1792.0 ),
            VMATHNUMBER_C( -1280.0 ),
            VMATHNUMBER_C( -1024.0 ),
            VMATHNUMBER_C( -768.0 ),
            VMATHNUMBER_C( -512.0 ),
            VMATHNUMBER_C( -256.0 ),
            VMATHNUMBER_C( -0.7 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.7 ),
            VMATHNUMBER_C( 256.0 ),
            VMATHNUMBER_C( 512.0 ),
            VMATHNUMBER_C( 768.0 ),
            VMATHNUMBER_C( 1024.0 ),
            VMATHNUMBER_C( 1280.0 ),
            VMATHNUMBER_C( 1792.0 ),
            VMATHNUMBER_C( 2048.0 ),
            VMATHNUMBER_C( 2048.7 ),
            };
    const VmathNumber expects[] = {
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 )};
    for (int i = 0;  i < countof(values);  i++) {
        const VmathNumber output = vmath_normalise_rad(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_VMATHNUMBER_EQUAL(expect, output);
    }
}

CTEST(vmath, test_vmath_normalise_deg) {
    const VmathNumber values[] = {
            VMATHNUMBER_C( -2048.7 ),
            VMATHNUMBER_C( -2048.0 ),
            VMATHNUMBER_C( -1792.0 ),
            VMATHNUMBER_C( -1280.0 ),
            VMATHNUMBER_C( -1024.0 ),
            VMATHNUMBER_C( -768.0 ),
            VMATHNUMBER_C( -512.0 ),
            VMATHNUMBER_C( -256.0 ),
            VMATHNUMBER_C( -0.7 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.7 ),
            VMATHNUMBER_C( 256.0 ),
            VMATHNUMBER_C( 512.0 ),
            VMATHNUMBER_C( 768.0 ),
            VMATHNUMBER_C( 1024.0 ),
            VMATHNUMBER_C( 1280.0 ),
            VMATHNUMBER_C( 1792.0 ),
            VMATHNUMBER_C( 2048.0 ),
            VMATHNUMBER_C( 2048.7 ),
            };
    const VmathNumber expects[] = {
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.0 )};
    for (int i = 0;  i < countof(values);  i++) {
        const VmathNumber output = vmath_normalise_deg(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_VMATHNUMBER_EQUAL(expect, output);
    }
}


//-----------------------------------------------------------------------------
// Co-ordinate Conversion Functions.
//-----------------------------------------------------------------------------

CTEST(vmath, test_vmath_matrix3x1_normalise) {
    VmathMatrix3x1 matrix = { VMATHNUMBER_C( 10.0 ), VMATHNUMBER_C( -20.0 ), VMATHNUMBER_C( 5.0 ) };
    const VmathMatrix3x1 expect = { VMATHNUMBER_C( 0.5 ), VMATHNUMBER_C( -1.0 ), VMATHNUMBER_C( 1.0 ) };
    vmath_matrix3x1_normalise(matrix);
    ASSERT_MATRIX3X1_EQUAL(expect, matrix);
}


CTEST(vmath, test_vmath_matrix3x1_homogeneous_to_cartesian) {
    VmathMatrix3x1 matrix = { VMATHNUMBER_C( 10.0 ), VMATHNUMBER_C( -20.0 ), VMATHNUMBER_C( 5.0 ) };
    const VmathMatrix3x1 expect = { VMATHNUMBER_C( 2.0 ), VMATHNUMBER_C( -4.0 ), VMATHNUMBER_C( 1.0 ) };
    vmath_matrix3x1_homogeneous_to_cartesian(matrix);
    ASSERT_MATRIX3X1_EQUAL(expect, matrix);
}


//-----------------------------------------------------------------------------
// Set a 3x3 Matrix With a Chosen Transformation.
//-----------------------------------------------------------------------------

CTEST(vmath, test_vmath_matrix3x3_set_identity) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_identity(matrix);
    ASSERT_MATRIX3X3_EQUAL(expect, matrix);
}


CTEST(vmath, test_vmath_matrix3x3_set_translation) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(123.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(-345.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_translation(matrix, VMATHNUMBER_C( 123.0 ), VMATHNUMBER_C( -345.0 ));
    ASSERT_MATRIX3X3_EQUAL(expect, matrix);
}


CTEST(vmath, test_vmath_matrix3x3_set_scaling) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.1 ),
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.1 ),
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.1 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C( 123.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(-345.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_scaling(matrix, VMATHNUMBER_C( 123.0 ), VMATHNUMBER_C( -345.0 ));
    ASSERT_MATRIX3X3_EQUAL(expect, matrix);
}


CTEST(vmath, test_vmath_matrix3x3_set_rotation_clockwise) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_rotation_clockwise(matrix, VMATHNUMBER_C( 123.0 ));
    ASSERT_MATRIX3X3_EQUAL(expect, matrix);
}


CTEST(vmath, test_vmath_matrix3x3_set_rotation_anticlockwise) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_rotation_anticlockwise(matrix, VMATHNUMBER_C( 123.0 ));
    ASSERT_MATRIX3X3_EQUAL(expect, matrix);
}


CTEST(vmath, test_vmath_matrix3x3_set_reflect_x) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(-1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_reflect_x(matrix);
    ASSERT_MATRIX3X3_EQUAL(expect, matrix);
}


CTEST(vmath, test_vmath_matrix3x3_set_reflect_y) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(-1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_reflect_y(matrix);
    ASSERT_MATRIX3X3_EQUAL(expect, matrix);
}


CTEST(vmath, test_vmath_matrix3x3_set_reflect_origin) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(-1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(-1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_reflect_origin(matrix);
    ASSERT_MATRIX3X3_EQUAL(expect, matrix);
}


CTEST(vmath, test_vmath_matrix3x3_set_reflect_y_equals_x) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_reflect_y_equals_x(matrix);
    ASSERT_MATRIX3X3_EQUAL(expect, matrix);
}


CTEST(vmath, test_vmath_matrix3x3_set_reflect_y_equals_neg_x) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(-1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(-1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_reflect_y_equals_neg_x(matrix);
    ASSERT_MATRIX3X3_EQUAL(expect, matrix);
}


CTEST(vmath, test_vmath_matrix3x3_set_shear_x_direction) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(123.0 ), VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_shear_x_direction(matrix, VMATHNUMBER_C( 123.0 ));
    ASSERT_MATRIX3X3_EQUAL(expect, matrix);
}


CTEST(vmath, test_vmath_matrix3x3_set_shear_y_direction) {
    puts("test_vmath_matrix3x3_set_shear_y_direction");
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(123.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_shear_y_direction(matrix, VMATHNUMBER_C( 123.0 ));
    ASSERT_MATRIX3X3_EQUAL(expect, matrix);
}


CTEST(vmath, test_vmath_matrix3x3_set_shear_x_and_y_direction) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(234.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(123.0 ), VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_shear_x_and_y_direction(matrix, VMATHNUMBER_C( 123.0 ), VMATHNUMBER_C( 234.0 ));
    ASSERT_MATRIX3X3_EQUAL(expect, matrix);
}




//-----------------------------------------------------------------------------
// Update a Previously Set 3x3 Matrix Transformation With New Values.
//-----------------------------------------------------------------------------

CTEST(vmath, test_vmath_matrix3x3_upd_translation) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(123.0 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(234.0 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    vmath_matrix3x3_upd_translation(matrix, VMATHNUMBER_C( 123.0 ), VMATHNUMBER_C( 234.0 ));
    ASSERT_MATRIX3X3_EQUAL(expect, matrix);
}


CTEST(vmath, test_vmath_matrix3x3_upd_scaling) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(123.0 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-345.0 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    vmath_matrix3x3_upd_scaling(matrix, VMATHNUMBER_C( 123.0 ), VMATHNUMBER_C( -345.0 ));
    ASSERT_MATRIX3X3_EQUAL(expect, matrix);
}


CTEST(vmath, test_vmath_matrix3x3_upd_rotation_clockwise) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_upd_rotation_clockwise(matrix, VMATHNUMBER_C( 123.0 ));
    ASSERT_MATRIX3X3_EQUAL(expect, matrix);
}


CTEST(vmath, test_vmath_matrix3x3_upd_rotation_anticlockwise) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_upd_rotation_anticlockwise(matrix, VMATHNUMBER_C( 123.0 ));
    ASSERT_MATRIX3X3_EQUAL(expect, matrix);
}


CTEST(vmath, test_vmath_matrix3x3_upd_shear_x_direction) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(123.0 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    vmath_matrix3x3_upd_shear_x_direction(matrix, VMATHNUMBER_C( 123.0 ));
    ASSERT_MATRIX3X3_EQUAL(expect, matrix);
}


CTEST(vmath, test_vmath_matrix3x3_upd_shear_y_direction) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(123.0 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    vmath_matrix3x3_upd_shear_y_direction(matrix, VMATHNUMBER_C( 123.0 ));
    ASSERT_MATRIX3X3_EQUAL(expect, matrix);
}


CTEST(vmath, test_vmath_matrix3x3_upd_shear_x_and_y_direction) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(234.0 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(123.0 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    vmath_matrix3x3_upd_shear_x_and_y_direction(matrix, VMATHNUMBER_C( 123.0 ), VMATHNUMBER_C( 234.0 ));
    ASSERT_MATRIX3X3_EQUAL(expect, matrix);
}


CTEST(vmath, test_vmath_matrix3x3_multiply_matrix3x3) {
    const VmathMatrix3x3 matrix1 = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 matrix2 = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.1 ),
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.1 ),
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.1 ), };
    VmathMatrix3x3 result = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_multiply_matrix3x3(matrix1, matrix2, result);
    ASSERT_MATRIX3X3_EQUAL(expect, result);
}


CTEST(vmath, test_vmath_matrix3x3_multiply_matrix3x1) {
    const VmathMatrix3x3 matrix1 = {
            VMATHNUMBER_C(1.1 ), VMATHNUMBER_C(1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(2.1 ), VMATHNUMBER_C(2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(3.1 ), VMATHNUMBER_C(3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x1 matrix2 = {
            VMATHNUMBER_C(11.11 ), VMATHNUMBER_C(11.12 ), VMATHNUMBER_C(-11.13 ) };
    VmathMatrix3x1 result = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.1 ) };
    const VmathMatrix3x1 expect = {
            VMATHNUMBER_C(40.034 ), VMATHNUMBER_C(73.394 ), VMATHNUMBER_C(106.754 ) };
    vmath_matrix3x3_multiply_matrix3x1(matrix1, matrix2, result);
    ASSERT_MATRIX3X1_EQUAL(expect, result);
}



//-----------------------------------------------------------------------------
// Update a Previously Set 3x3 Matrix Transformation With New Values.
//-----------------------------------------------------------------------------

int main(int argc, const char *argv[])
{
    return ctest_main(argc, argv);
}


