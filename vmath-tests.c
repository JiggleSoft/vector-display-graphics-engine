//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) Mathematics Unit Tests.
// Filename:     vmath-tests.c
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-04-10 23:03
// Version:      1.0.0-beta-4
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

// CTest vMath include (implementation) file.
#include "vmath-ctest.h"



//-----------------------------------------------------------------------------
// Test Fixture Lifecycle.
//-----------------------------------------------------------------------------

CTEST_DATA(vmath)
{
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
// Constant Test Data.
//-----------------------------------------------------------------------------

// Millibit-revolutions test angles.
static const VmathNumber test_vmath_mbr_values[] = {
        VMATHNUMBER_C( -2049.137777778 ), // -720.4 degrees.
        VMATHNUMBER_C( -2048.0 ), // -720 degrees.
        VMATHNUMBER_C( -1792.0 ), // -630.0 degrees.
        VMATHNUMBER_C( -1536.0 ), // -540.0 degrees.
        VMATHNUMBER_C( -1280.0 ), // -450.0 degrees.
        VMATHNUMBER_C( -1024.0 ), // -360.0 degrees.
        VMATHNUMBER_C( -768.0 ), // -270.0 degrees.
        VMATHNUMBER_C( -512.0 ), // -180.0 degrees.
        VMATHNUMBER_C( -256.0 ), // -90.0 degrees.
        VMATHNUMBER_C( -128.0 ), // -45.0 degrees.
        VMATHNUMBER_C( -1.137777778 ), // -0.4 degrees.
        VMATHNUMBER_C( 0.0 ), // 0.0 degrees.
        VMATHNUMBER_C( 1.137777778 ), // 0.4 degrees.
        VMATHNUMBER_C( 128.0 ), // 45.0 degrees.
        VMATHNUMBER_C( 256.0 ), // 90.0 degrees.
        VMATHNUMBER_C( 512.0 ), // 180.0 degrees.
        VMATHNUMBER_C( 768.0 ), // 270.0 degrees.
        VMATHNUMBER_C( 1024.0 ), // 360.0 degrees.
        VMATHNUMBER_C( 1280.0 ), // 450.0 degrees.
        VMATHNUMBER_C( 1536.0 ), // 540.0 degrees.
        VMATHNUMBER_C( 1792.0 ), // 630.0 degrees.
        VMATHNUMBER_C( 2048.0 ), // 720.0 degrees.
        VMATHNUMBER_C( 2049.137777778 ) // 720.4 degrees.
    };


// Radians test angles.
static const VmathNumber test_vmath_rad_values[] = {
        VMATHNUMBER_C( -12.573351917 ), // -720.4 degrees.
        VMATHNUMBER_C( -12.5663706 ), // -720 degrees.
        VMATHNUMBER_C( -10.995574275 ), // -630.0 degrees.
        VMATHNUMBER_C( -9.42477795 ), // -540.0 degrees.
        VMATHNUMBER_C( -7.853981625 ), // -450.0 degrees.
        VMATHNUMBER_C( -6.2831853 ), // -360.0 degrees.
        VMATHNUMBER_C( -4.712388975 ), // -270.0 degrees.
        VMATHNUMBER_C( -3.14159265 ), // -180.0 degrees.
        VMATHNUMBER_C( -1.570796325 ), // -90.0 degrees.
        VMATHNUMBER_C( -0.785398163 ), // -45.0 degrees.
        VMATHNUMBER_C( -0.006981317 ), // -0.4 degrees.
        VMATHNUMBER_C( 0.0 ), // 0.0 degrees.
        VMATHNUMBER_C( 0.006981317 ), // 0.4 degrees.
        VMATHNUMBER_C( 0.785398163 ), // 45.0 degrees.
        VMATHNUMBER_C( 1.570796325 ), // 90.0 degrees.
        VMATHNUMBER_C( 3.14159265 ), // 180.0 degrees.
        VMATHNUMBER_C( 4.712388975 ), // 270.0 degrees.
        VMATHNUMBER_C( 6.2831853 ), // 360.0 degrees.
        VMATHNUMBER_C( 7.853981625 ), // 450.0 degrees.
        VMATHNUMBER_C( 9.42477795 ), // 540.0 degrees.
        VMATHNUMBER_C( 10.995574275 ), // 630.0 degrees.
        VMATHNUMBER_C( 12.5663706 ), // 720.0 degrees.
        VMATHNUMBER_C( 12.573351917 ) // 720.4 degrees.
    };


// Degrees test angles.
static const VmathNumber test_vmath_deg_values[] = {
        VMATHNUMBER_C( -720.4 ),
        VMATHNUMBER_C( -720.0 ),
        VMATHNUMBER_C( -630.0 ),
        VMATHNUMBER_C( -540.0 ),
        VMATHNUMBER_C( -450.0 ),
        VMATHNUMBER_C( -360.0 ),
        VMATHNUMBER_C( -270.0 ),
        VMATHNUMBER_C( -180.0 ),
        VMATHNUMBER_C( -90.0 ),
        VMATHNUMBER_C( -45.0 ),
        VMATHNUMBER_C( -0.4 ),
        VMATHNUMBER_C( 0.0 ),
        VMATHNUMBER_C( 0.4 ),
        VMATHNUMBER_C( 45.0 ),
        VMATHNUMBER_C( 90.0 ),
        VMATHNUMBER_C( 180.0 ),
        VMATHNUMBER_C( 270.0 ),
        VMATHNUMBER_C( 360.0 ),
        VMATHNUMBER_C( 450.0 ),
        VMATHNUMBER_C( 540.0 ),
        VMATHNUMBER_C( 630.0 ),
        VMATHNUMBER_C( 720.0 ),
        VMATHNUMBER_C( 720.4 )
    };


CTEST(vmath, test_vmath_mbr_rad_deg_values) {
    ASSERT_EQUAL(_countof(test_vmath_mbr_values), _countof(test_vmath_rad_values));
    ASSERT_EQUAL(_countof(test_vmath_rad_values), _countof(test_vmath_deg_values));
    ASSERT_EQUAL(_countof(test_vmath_deg_values), _countof(test_vmath_mbr_values));
}



//-----------------------------------------------------------------------------
// Test Clipping Functions.
//-----------------------------------------------------------------------------

CTEST(vmath, test_vmath_clip_floor) {
    const VmathNumber values[] = {
            VMATHNUMBER_C(-256.0),
            VMATHNUMBER_C(-64.001),
            VMATHNUMBER_C(-64.0),
            VMATHNUMBER_C(-63.999),
            VMATHNUMBER_C(-0.001),
            VMATHNUMBER_C(-0.0),
            VMATHNUMBER_C(0.0),
            VMATHNUMBER_C(0.001),
            VMATHNUMBER_C(63.999),
            VMATHNUMBER_C(64.0),
            VMATHNUMBER_C(64.001),
            VMATHNUMBER_C(256.0)};
    const VmathNumber expects[] = {
            VMATHNUMBER_C(-64.0),
            VMATHNUMBER_C(-64.0),
            VMATHNUMBER_C(-64.0),
            VMATHNUMBER_C(-63.999),
            VMATHNUMBER_C(-0.001),
            VMATHNUMBER_C(-0.0),
            VMATHNUMBER_C(0.0),
            VMATHNUMBER_C(0.001),
            VMATHNUMBER_C(63.999),
            VMATHNUMBER_C(64.0),
            VMATHNUMBER_C(64.001),
            VMATHNUMBER_C(256.0)};
    for (int i = 0; i < _countof(values); i++) {
        const VmathNumber output = vmath_clip_floor(values[i], -64.0);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_EQUAL(expect, output);
    }
}


CTEST(vmath, test_vmath_clip_ceil) {
    const VmathNumber values[] = {
            VMATHNUMBER_C(-256.0),
            VMATHNUMBER_C(-64.001),
            VMATHNUMBER_C(-64.0),
            VMATHNUMBER_C(-63.999),
            VMATHNUMBER_C(-0.001),
            VMATHNUMBER_C(-0.0),
            VMATHNUMBER_C(0.0),
            VMATHNUMBER_C(0.001),
            VMATHNUMBER_C(63.999),
            VMATHNUMBER_C(64.0),
            VMATHNUMBER_C(64.001),
            VMATHNUMBER_C(256.0)};
    const VmathNumber expects[] = {
            VMATHNUMBER_C(-256.0),
            VMATHNUMBER_C(-64.001),
            VMATHNUMBER_C(-64.0),
            VMATHNUMBER_C(-63.999),
            VMATHNUMBER_C(-0.001),
            VMATHNUMBER_C(-0.0),
            VMATHNUMBER_C(0.0),
            VMATHNUMBER_C(0.001),
            VMATHNUMBER_C(63.999),
            VMATHNUMBER_C(64.0),
            VMATHNUMBER_C(64.0),
            VMATHNUMBER_C(64.0)};
    for (int i = 0; i < _countof(values); i++) {
        const VmathNumber output = vmath_clip_ceil(values[i], 64.0);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_EQUAL(expect, output);
    }
}


CTEST(vmath, test_vmath_clip_floor_ceil) {
    const VmathNumber values[] = {
            VMATHNUMBER_C( -256.0 ),
            VMATHNUMBER_C( -64.001 ),
            VMATHNUMBER_C( -64.0 ),
            VMATHNUMBER_C( -63.999 ),
            VMATHNUMBER_C( -0.001 ),
            VMATHNUMBER_C( -0.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.001 ),
            VMATHNUMBER_C( 63.999 ),
            VMATHNUMBER_C(  64.0),
            VMATHNUMBER_C(  64.001),
            VMATHNUMBER_C( 256.0 )};
    const VmathNumber expects[] = {
            VMATHNUMBER_C(-64.0),
            VMATHNUMBER_C(-64.0),
            VMATHNUMBER_C(-64.0),
            VMATHNUMBER_C(-63.999),
            VMATHNUMBER_C(-0.001),
            VMATHNUMBER_C(-0.0),
            VMATHNUMBER_C(0.0),
            VMATHNUMBER_C(0.001),
            VMATHNUMBER_C(63.999),
            VMATHNUMBER_C(64.0),
            VMATHNUMBER_C(64.0),
            VMATHNUMBER_C(64.0)};
    for (int i = 0;  i < _countof(values);  i++) {
        const VmathNumber output = vmath_clip_floor_ceil(values[i], -64.0, 64.0);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_EQUAL(expect, output);
    }
}



//-----------------------------------------------------------------------------
// Test Trigonometry Functions.
//-----------------------------------------------------------------------------

CTEST2(vmath, test_vmath_mbr_sin) {
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
            VMATHNUMBER_C( 0.7071067812 )};
    for (int i = 0;  i < _countof(values);  i++) {
        const VmathNumber output = vmath_mbr_sin(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_NEAR(expect, output);
    }
}


CTEST2(vmath, test_vmath_mbr_cos) {
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
    for (int i = 0;  i < _countof(values);  i++) {
        const VmathNumber output = vmath_mbr_cos(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_NEAR(expect, output);
    }
}



//-----------------------------------------------------------------------------
// Test Angle Conversion Functions.
//-----------------------------------------------------------------------------

CTEST(vmath, test_vmath_rad_to_mbr) {
    const VmathNumber * values = test_vmath_rad_values;
    const VmathNumber * expects = test_vmath_mbr_values;
    for (int i = 0;  i < _countof(test_vmath_rad_values);  i++) {
        const VmathNumber output = vmath_rad_to_mbr(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_NEAR_TOL(expect, output, 0.000333f);
    }
}


CTEST(vmath, test_vmath_deg_to_mbr) {
    const VmathNumber * values = test_vmath_deg_values;
    const VmathNumber * expects = test_vmath_mbr_values;
    ASSERT_EQUAL(_countof(values), _countof(expects));
    for (int i = 0;  i < _countof(test_vmath_deg_values);  i++) {
        const VmathNumber output = vmath_deg_to_mbr(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_NEAR_TOL(expect, output, 0.000333f);
    }
}


CTEST(vmath, test_vmath_mbr_to_rad) {
    const VmathNumber * values = test_vmath_mbr_values;
    const VmathNumber * expects = test_vmath_rad_values;
    for (int i = 0;  i < _countof(test_vmath_mbr_values);  i++) {
        const VmathNumber output = vmath_mbr_to_rad(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_NEAR_TOL(expect, output, 0.000333f);
    }
}


CTEST(vmath, test_vmath_deg_to_rad) {
    const VmathNumber * values = test_vmath_deg_values;
    const VmathNumber * expects = test_vmath_rad_values;
    for (int i = 0;  i < _countof(test_vmath_deg_values);  i++) {
        const VmathNumber output = vmath_deg_to_rad(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_NEAR_TOL(expect, output, 0.000333f);
    }
}


CTEST(vmath, test_vmath_mbr_to_deg) {
    const VmathNumber * values = test_vmath_mbr_values;
    const VmathNumber * expects = test_vmath_deg_values;
    for (int i = 0;  i < _countof(test_vmath_mbr_values);  i++) {
        const VmathNumber output = vmath_mbr_to_deg(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_NEAR_TOL(expect, output, 0.000333f);
    }
}


CTEST(vmath, test_vmath_rad_to_deg) {
    const VmathNumber * values = test_vmath_rad_values;
    const VmathNumber * expects = test_vmath_deg_values;
    for (int i = 0;  i < _countof(test_vmath_rad_values);  i++) {
        const VmathNumber output = vmath_rad_to_deg(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_NEAR_TOL(expect, output, 0.000333f);
    }
}



//-----------------------------------------------------------------------------
// Angle Normalisation Functions.
//-----------------------------------------------------------------------------

CTEST(vmath, test_vmath_normalise_mbr) {
    const VmathNumber * values = test_vmath_mbr_values;
    const VmathNumber expects[] = {
            VMATHNUMBER_C( 1022.862222222 ), // -720.4 degrees.
            VMATHNUMBER_C( 0.0 ), // -720 degrees.
            VMATHNUMBER_C( 256.0 ), // -630.0 degrees.
            VMATHNUMBER_C( 512.0 ), // -540.0 degrees.
            VMATHNUMBER_C( 768.0 ), // -450.0 degrees.
            VMATHNUMBER_C( 0.0 ), // -360.0 degrees.
            VMATHNUMBER_C( 256.0 ), // -270.0 degrees.
            VMATHNUMBER_C( 512.0 ), // -180.0 degrees.
            VMATHNUMBER_C( 768.0 ), // -90.0 degrees.
            VMATHNUMBER_C( 896.0 ), // -45.0 degrees.
            VMATHNUMBER_C( 1022.862222222 ), // -0.4 degrees.
            VMATHNUMBER_C( 0.0 ), // 0.0 degrees.
            VMATHNUMBER_C( 1.137777778 ), // 0.4 degrees.
            VMATHNUMBER_C( 128.0 ), // 45.0 degrees.
            VMATHNUMBER_C( 256.0 ), // 90.0 degrees.
            VMATHNUMBER_C( 512.0 ), // 180.0 degrees.
            VMATHNUMBER_C( 768.0 ), // 270.0 degrees.
            VMATHNUMBER_C( 0.0 ), // 360.0 degrees.
            VMATHNUMBER_C( 256.0 ), // 450.0 degrees.
            VMATHNUMBER_C( 512.0 ), // 540.0 degrees.
            VMATHNUMBER_C( 768.0 ), // 630.0 degrees.
            VMATHNUMBER_C( 0.0 ), // 720.0 degrees.
            VMATHNUMBER_C( 1.137777778 ) // 720.4 degrees.
        };
    ASSERT_EQUAL(_countof(test_vmath_mbr_values), _countof(expects));
    for (int i = 0;  i < _countof(test_vmath_mbr_values);  i++) {
        const VmathNumber output = vmath_normalise_mbr(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_NEAR(expect, output);
    }
}


CTEST(vmath, test_vmath_normalise_rad) {
    const VmathNumber * values = test_vmath_rad_values;
    const VmathNumber expects[] = {
            VMATHNUMBER_C( 6.276203983 ), // -720.4 degrees.
            VMATHNUMBER_C( 0.0 ), // -720 degrees.
            VMATHNUMBER_C( 1.570796325 ), // -630.0 degrees.
            VMATHNUMBER_C( 3.14159265 ), // -540.0 degrees.
            VMATHNUMBER_C( 4.712388975 ), // -450.0 degrees.
            VMATHNUMBER_C( 0.0 ), // -360.0 degrees.
            VMATHNUMBER_C( 1.570796325 ), // -270.0 degrees.
            VMATHNUMBER_C( 3.14159265 ), // -180.0 degrees.
            VMATHNUMBER_C( 4.712388975 ), // -90.0 degrees.
            VMATHNUMBER_C( 5.497787138 ), // -45.0 degrees.
            VMATHNUMBER_C( 6.276203983 ), // -0.4 degrees.
            VMATHNUMBER_C( 0.0 ), // 0.0 degrees.
            VMATHNUMBER_C( 0.006981317 ), // 0.4 degrees.
            VMATHNUMBER_C( 0.785398163 ), // 45.0 degrees.
            VMATHNUMBER_C( 1.570796325 ), // 90.0 degrees.
            VMATHNUMBER_C( 3.14159265 ), // 180.0 degrees.
            VMATHNUMBER_C( 4.712388975 ), // 270.0 degrees.
            VMATHNUMBER_C( 0.0 ), // 360.0 degrees.
            VMATHNUMBER_C( 1.570796325 ), // 450.0 degrees.
            VMATHNUMBER_C( 3.14159265 ), // 540.0 degrees.
            VMATHNUMBER_C( 4.712388975 ), // 630.0 degrees.
            VMATHNUMBER_C( 0.0 ), // 720.0 degrees.
            VMATHNUMBER_C( 0.006981317 ) // 720.4 degrees.
        };
    ASSERT_EQUAL(_countof(test_vmath_rad_values), _countof(expects));
    for (int i = 0;  i < _countof(test_vmath_rad_values);  i++) {
        const VmathNumber output = vmath_normalise_rad(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_NEAR_TOL(expect, output, 0.000333f);
    }
}


CTEST(vmath, test_vmath_normalise_deg) {
    const VmathNumber * values = test_vmath_deg_values;
    const VmathNumber expects[] = {
            VMATHNUMBER_C( 359.6 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 90.0 ),
            VMATHNUMBER_C( 180.0 ),
            VMATHNUMBER_C( 270.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 90.0 ),
            VMATHNUMBER_C( 180.0 ),
            VMATHNUMBER_C( 270.0 ),
            VMATHNUMBER_C( 315.0 ),
            VMATHNUMBER_C( 359.6 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.4 ),
            VMATHNUMBER_C( 45.0 ),
            VMATHNUMBER_C( 90.0 ),
            VMATHNUMBER_C( 180.0 ),
            VMATHNUMBER_C( 270.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 90.0 ),
            VMATHNUMBER_C( 180.0 ),
            VMATHNUMBER_C( 270.0 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.4 )
        };
    ASSERT_EQUAL(_countof(test_vmath_deg_values), _countof(expects));
    for (int i = 0;  i < _countof(test_vmath_deg_values);  i++) {
        const VmathNumber output = vmath_normalise_deg(values[i]);
        const VmathNumber expect = expects[i];
        ASSERT_DBL_NEAR_TOL(expect, output, 0.000333f);
    }
}



//-----------------------------------------------------------------------------
// Co-ordinate Conversion Functions.
//-----------------------------------------------------------------------------

CTEST(vmath, vmath_matrix3x1_normalise_to_cartesian) {
    VmathMatrix3x1 matrix = { VMATHNUMBER_C( 10.0 ), VMATHNUMBER_C( -20.0 ), VMATHNUMBER_C( 5.0 ) };
    const VmathMatrix3x1 expect = { VMATHNUMBER_C( 0.089442719 ), VMATHNUMBER_C( -0.178885438 ), VMATHNUMBER_C( 1.0 ) };
    vmath_matrix3x1_normalise_to_cartesian(matrix);
    ASSERT_MATRIX3X1_EQUAL_TOL(expect, matrix, 0.000333f);
}


CTEST(vmath, test_vmath_matrix3x1_normalise) {
    VmathMatrix3x1 matrix = { VMATHNUMBER_C( 10.0 ), VMATHNUMBER_C( -20.0 ), VMATHNUMBER_C( 5.0 ) };
    const VmathMatrix3x1 expect = { VMATHNUMBER_C( 0.447213595 ), VMATHNUMBER_C( -0.894427191 ), VMATHNUMBER_C( 5.0 ) };
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


CTEST2(vmath, test_vmath_matrix3x3_set_rotation_clockwise) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(0.72846439 ), VMATHNUMBER_C(-0.685083668 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.685083668 ), VMATHNUMBER_C(0.72846439 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_rotation_clockwise(matrix, VMATHNUMBER_C( 123.0 ));
    ASSERT_MATRIX3X3_EQUAL_TOL(expect, matrix, 0.000333f);
}


CTEST2(vmath, test_vmath_matrix3x3_set_rotation_anticlockwise) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(0.72846439 ), VMATHNUMBER_C(0.685083668 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(-0.685083668 ), VMATHNUMBER_C(0.72846439 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_rotation_anticlockwise(matrix, VMATHNUMBER_C( 123.0 ));
    ASSERT_MATRIX3X3_EQUAL_TOL(expect, matrix, 0.000333f);
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


CTEST2(vmath, test_vmath_matrix3x3_upd_rotation_clockwise) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(0.72846439 ), VMATHNUMBER_C(-0.685083668 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(0.685083668 ), VMATHNUMBER_C(0.72846439 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    vmath_matrix3x3_upd_rotation_clockwise(matrix, VMATHNUMBER_C( 123.0 ));
    ASSERT_MATRIX3X3_EQUAL_TOL(expect, matrix, 0.000333f);
}


CTEST2(vmath, test_vmath_matrix3x3_upd_rotation_anticlockwise) {
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(0.72846439 ), VMATHNUMBER_C(0.685083668 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-0.685083668 ), VMATHNUMBER_C(0.72846439 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    vmath_matrix3x3_upd_rotation_anticlockwise(matrix, VMATHNUMBER_C( 123.0 ));
    ASSERT_MATRIX3X3_EQUAL_TOL(expect, matrix, 0.000333f);
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


CTEST(vmath, test_vmath_matrix3x3_multiply_matrix3x3_fast) {
    const VmathMatrix3x3 matrix1 = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 matrix2 = {
            VMATHNUMBER_C(-11.11 ), VMATHNUMBER_C(11.22 ), VMATHNUMBER_C(-11.33 ),
            VMATHNUMBER_C(22.11 ), VMATHNUMBER_C(-22.22 ), VMATHNUMBER_C(-22.33 ),
            VMATHNUMBER_C(-33.11 ), VMATHNUMBER_C(-33.22 ), VMATHNUMBER_C(-33.33 ), };
    VmathMatrix3x3 result = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(28.732 ), VMATHNUMBER_C(57.508 ), VMATHNUMBER_C(82.588 ),
            VMATHNUMBER_C(50.842 ), VMATHNUMBER_C(101.728 ), VMATHNUMBER_C(149.578 ),
            VMATHNUMBER_C(72.952 ), VMATHNUMBER_C(145.948 ), VMATHNUMBER_C(216.568 ), };
    vmath_matrix3x3_multiply_matrix3x3_fast(matrix1, matrix2, result);
    ASSERT_MATRIX3X3_EQUAL_TOL(expect, result, 0.000333f);
}


CTEST(vmath, test_vmath_matrix3x3_multiply_matrix3x3_matrix1) {
    const VmathMatrix3x3 matrix1 = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 matrix2 = {
            VMATHNUMBER_C(-11.11 ), VMATHNUMBER_C(11.22 ), VMATHNUMBER_C(-11.33 ),
            VMATHNUMBER_C(22.11 ), VMATHNUMBER_C(-22.22 ), VMATHNUMBER_C(-22.33 ),
            VMATHNUMBER_C(-33.11 ), VMATHNUMBER_C(-33.22 ), VMATHNUMBER_C(-33.33 ), };
    VmathMatrix3x3 * result = (VmathMatrix3x3 *)matrix1;
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(28.732 ), VMATHNUMBER_C(57.508 ), VMATHNUMBER_C(82.588 ),
            VMATHNUMBER_C(50.842 ), VMATHNUMBER_C(101.728 ), VMATHNUMBER_C(149.578 ),
            VMATHNUMBER_C(72.952 ), VMATHNUMBER_C(145.948 ), VMATHNUMBER_C(216.568 ), };
    vmath_matrix3x3_multiply_matrix3x3(matrix1, matrix2, result);
    ASSERT_MATRIX3X3_EQUAL_TOL(expect, result, 0.000333f);
}


CTEST(vmath, test_vmath_matrix3x3_multiply_matrix3x3_matrix2) {
    const VmathMatrix3x3 matrix1 = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 matrix2 = {
            VMATHNUMBER_C(-11.11 ), VMATHNUMBER_C(11.22 ), VMATHNUMBER_C(-11.33 ),
            VMATHNUMBER_C(22.11 ), VMATHNUMBER_C(-22.22 ), VMATHNUMBER_C(-22.33 ),
            VMATHNUMBER_C(-33.11 ), VMATHNUMBER_C(-33.22 ), VMATHNUMBER_C(-33.33 ), };
    VmathMatrix3x3 * result = matrix2;
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(28.732 ), VMATHNUMBER_C(57.508 ), VMATHNUMBER_C(82.588 ),
            VMATHNUMBER_C(50.842 ), VMATHNUMBER_C(101.728 ), VMATHNUMBER_C(149.578 ),
            VMATHNUMBER_C(72.952 ), VMATHNUMBER_C(145.948 ), VMATHNUMBER_C(216.568 ), };
    vmath_matrix3x3_multiply_matrix3x3(matrix1, matrix2, result);
    ASSERT_MATRIX3X3_EQUAL_TOL(expect, result, 0.000333f);
}


CTEST(vmath, test_vmath_matrix3x3_multiply_matrix3x3_result) {
    const VmathMatrix3x3 matrix1 = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 matrix2 = {
            VMATHNUMBER_C(-11.11 ), VMATHNUMBER_C(11.22 ), VMATHNUMBER_C(-11.33 ),
            VMATHNUMBER_C(22.11 ), VMATHNUMBER_C(-22.22 ), VMATHNUMBER_C(-22.33 ),
            VMATHNUMBER_C(-33.11 ), VMATHNUMBER_C(-33.22 ), VMATHNUMBER_C(-33.33 ), };
    VmathMatrix3x3 result = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(28.732 ), VMATHNUMBER_C(57.508 ), VMATHNUMBER_C(82.588 ),
            VMATHNUMBER_C(50.842 ), VMATHNUMBER_C(101.728 ), VMATHNUMBER_C(149.578 ),
            VMATHNUMBER_C(72.952 ), VMATHNUMBER_C(145.948 ), VMATHNUMBER_C(216.568 ), };
    vmath_matrix3x3_multiply_matrix3x3(matrix1, matrix2, result);
    ASSERT_MATRIX3X3_EQUAL_TOL(expect, result, 0.000333f);
}


CTEST(vmath, test_vmath_matrix3x3_multiply_matrix3x1_fast) {
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
    vmath_matrix3x3_multiply_matrix3x1_fast(matrix1, matrix2, result);
    ASSERT_MATRIX3X1_EQUAL(expect, result);
}


CTEST(vmath, test_vmath_matrix3x3_multiply_matrix3x1_matrix2) {
    const VmathMatrix3x3 matrix1 = {
            VMATHNUMBER_C(1.1 ), VMATHNUMBER_C(1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(2.1 ), VMATHNUMBER_C(2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(3.1 ), VMATHNUMBER_C(3.2 ), VMATHNUMBER_C(-3.3 ), };
    VmathMatrix3x1 matrix2 = {
            VMATHNUMBER_C(11.11 ), VMATHNUMBER_C(11.12 ), VMATHNUMBER_C(-11.13 ) };
    VmathMatrix3x1 * result = matrix2;
    const VmathMatrix3x1 expect = {
            VMATHNUMBER_C(40.034 ), VMATHNUMBER_C(73.394 ), VMATHNUMBER_C(106.754 ) };
    vmath_matrix3x3_multiply_matrix3x1(matrix1, matrix2, result);
    ASSERT_MATRIX3X1_EQUAL(expect, result);
}


CTEST(vmath, test_vmath_matrix3x3_multiply_matrix3x1_result) {
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
// Main Application Entry Point.
//-----------------------------------------------------------------------------

// Function main() implementation.
CTESTX_MAIN


