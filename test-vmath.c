//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) Mathematics.
// Filename:     vmath.c
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

#include "vmath.h"


/*void startup(void)
{
    vmath_init();
}

void teardown(void)
{
    ; // Do nowt.
}


void test_vmath_rad_to_mbr(void)
{
    assert(vmath_rad_to_mbr(VMATHNUMBER_C(0.0) == 0);
    assert(vmath_rad_to_mbr(VMATHNUMBER_C(3.14159265 / 2) == 256);
    assert(vmath_rad_to_mbr(VMATHNUMBER_C((2 * 3.14159265))) == 0);
    assert(vmath_rad_to_mbr(VMATHNUMBER_C((2 * 3.14159265))) == 0);
}


int main(int args, char ** argv)
{
    startup();
    test_vmath_rad_to_mbr();
    teardown();
}
*/



// ******************** TESTS *********************

int test_failed = 0;

int vmath_matrix3x1_equal(const VmathMatrix3x1 matrix1, const VmathMatrix3x1 matrix2)
{
    for (int x = 0;  x < 3;  x++) {
        if (matrix1[x] != matrix2[x]) {
            return 0;
        }
    }
    return 1;
}


int vmath_matrix3x3_equal(const VmathMatrix3x3 matrix1, const VmathMatrix3x3 matrix2)
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


void assert_equals_vmathnumber(const VmathNumber expect, const VmathNumber value)
{
    if (expect != value) {
        printf("FAIL: Expected %f but found %f\n", expect, value);
        test_failed++;
    }
}


void assert_equals_matrix3x1(const VmathMatrix3x1 expect, const VmathMatrix3x1 matrix)
{
    if (!vmath_matrix3x1_equal(expect, matrix)) {
        printf("FAIL: Expected %f, %f, %f but found %f, %f, %f\n",
               expect[0], expect[1], expect[2],
               matrix[0], matrix[1], matrix[2]);
        test_failed++;
    }
}


void assert_equals_matrix3x3(const VmathMatrix3x3 expect, const VmathMatrix3x3 matrix) {
    if (!vmath_matrix3x3_equal(expect, matrix)) {
        printf("FAIL: Expected %f, %f, %f, %f, %f, %f, %f, %f, %f but found %f, %f, %f, %f, %f, %f, %f, %f, %f \n",
               expect[0][0], expect[0][1], expect[0][2],
               expect[1][0], expect[1][1], expect[1][2],
               expect[2][0], expect[2][1], expect[2][2],
               matrix[0][0], matrix[0][1], matrix[0][2],
               matrix[1][0], matrix[1][1], matrix[1][2],
               matrix[2][0], matrix[2][1], matrix[2][2]);
        test_failed++;
    }
}

void assert_success()
{
    if (test_failed) {
        printf("FAILED %d TESTS!!!", test_failed);
    } else {
        puts("SUCCESS: ALL TESTS PASS.");
    }
}


#define countof(a) (sizeof(a) / sizeof(a[0]))


void test_vmath_mbr_sin(void)
{
    puts("test_vmath_mbr_sin");
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
        assert_equals_vmathnumber(expect, output);
    }
}

void test_vmath_mbr_cos(void)
{
    puts("test_vmath_mbr_cos");
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
        assert_equals_vmathnumber(expect, output);
    }
}

void test_vmath_rad_to_mbr(void)
{
    puts("test_vmath_rad_to_mbr");
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
        assert_equals_vmathnumber(expect, output);
    }
}

void test_vmath_deg_to_mbr(void)
{
    puts("test_vmath_deg_to_mbr");
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
        assert_equals_vmathnumber(expect, output);
    }
}

void test_vmath_mbr_to_rad(void)
{
    puts("test_vmath_mbr_to_rad");
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
        assert_equals_vmathnumber(expect, output);
    }
}

void test_vmath_deg_to_rad(void)
{
    puts("test_vmath_deg_to_rad");
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
            VMATHNUMBER_C( 0.785398 ),
            VMATHNUMBER_C( 1.5708 ),
            VMATHNUMBER_C( 3.14159 ),
            VMATHNUMBER_C( 4.71239 ),
            VMATHNUMBER_C( 0.0 ),
            VMATHNUMBER_C( 0.785398 )};
    for (int i = 0;  i < countof(values);  i++) {
        const VmathNumber output = vmath_deg_to_rad(values[i]);
        const VmathNumber expect = expects[i];
        assert_equals_vmathnumber(expect, output);
    }
}

void test_vmath_mbr_to_deg(void)
{
    puts("test_vmath_mbr_to_deg");
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
        assert_equals_vmathnumber(expect, output);
    }
}

void test_vmath_rad_to_deg(void)
{
    puts("test_vmath_rad_to_deg");
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
        assert_equals_vmathnumber(expect, output);
    }
}

void test_vmath_matrix3x1_normalise(void)
{
    puts("test_vmath_matrix3x1_normalise");
    VmathMatrix3x1 matrix = { VMATHNUMBER_C( 10.0 ), VMATHNUMBER_C( -20.0 ), VMATHNUMBER_C( 5.0 ) };
    const VmathMatrix3x1 expect = { VMATHNUMBER_C( 0.5 ), VMATHNUMBER_C( -1.0 ), VMATHNUMBER_C( 1.0 ) };
    vmath_matrix3x1_normalise(matrix);
    assert_equals_matrix3x1(expect, matrix);
}

void test_vmath_matrix3x1_homogeneous_to_cartesian(void)
{
    puts("test_vmath_matrix3x1_homogeneous_to_cartesian");
    VmathMatrix3x1 matrix = { VMATHNUMBER_C( 10.0 ), VMATHNUMBER_C( -20.0 ), VMATHNUMBER_C( 5.0 ) };
    const VmathMatrix3x1 expect = { VMATHNUMBER_C( 2.0 ), VMATHNUMBER_C( -4.0 ), VMATHNUMBER_C( 1.0 ) };
    vmath_matrix3x1_homogeneous_to_cartesian(matrix);
    assert_equals_matrix3x1(expect, matrix);
}

void test_vmath_matrix3x3_set_identity(void)
{
    puts("test_vmath_matrix3x3_set_identity");
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_identity(matrix);
    assert_equals_matrix3x3(expect, matrix);
}

void test_vmath_matrix3x3_set_translation(void)
{
    puts("test_vmath_matrix3x3_set_translation");
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(123.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(-345.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_translation(matrix, VMATHNUMBER_C( 123.0 ), VMATHNUMBER_C( -345.0 ));
    assert_equals_matrix3x3(expect, matrix);
}

void test_vmath_matrix3x3_set_scaling(void)
{
    puts("test_vmath_matrix3x3_set_scaling");
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.1 ),
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.1 ),
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.1 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C( 123.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(-345.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_scaling(matrix, VMATHNUMBER_C( 123.0 ), VMATHNUMBER_C( -345.0 ));
    assert_equals_matrix3x3(expect, matrix);
}

void test_vmath_matrix3x3_set_rotation_clockwise(void)
{
    puts("test_vmath_matrix3x3_set_rotation_clockwise");
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_rotation_clockwise(matrix, VMATHNUMBER_C( 123.0 ));
    assert_equals_matrix3x3(expect, matrix);
}

void test_vmath_matrix3x3_set_rotation_anticlockwise(void)
{
    puts("test_vmath_matrix3x3_set_rotation_anticlockwise");
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_rotation_anticlockwise(matrix, VMATHNUMBER_C( 123.0 ));
    assert_equals_matrix3x3(expect, matrix);
}

void test_vmath_matrix3x3_set_reflect_x(void)
{
    puts("test_vmath_matrix3x3_set_reflect_x");
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(-1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_reflect_x(matrix);
    assert_equals_matrix3x3(expect, matrix);
}

void test_vmath_matrix3x3_set_reflect_y(void)
{
    puts("test_vmath_matrix3x3_set_reflect_y");
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(-1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_reflect_y(matrix);
    assert_equals_matrix3x3(expect, matrix);
}

void test_vmath_matrix3x3_set_reflect_origin(void)
{
    puts("test_vmath_matrix3x3_set_reflect_origin");
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(-1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(-1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_reflect_origin(matrix);
    assert_equals_matrix3x3(expect, matrix);
}

void test_vmath_matrix3x3_set_reflect_y_equals_x(void)
{
    puts("test_vmath_matrix3x3_set_reflect_y_equals_x");
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_reflect_y_equals_x(matrix);
    assert_equals_matrix3x3(expect, matrix);
}

void test_vmath_matrix3x3_set_reflect_y_equals_neg_x(void)
{
    puts("test_vmath_matrix3x3_set_reflect_y_equals_neg_x");
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(-1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(-1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_reflect_y_equals_neg_x(matrix);
    assert_equals_matrix3x3(expect, matrix);
}

void test_vmath_matrix3x3_set_shear_x_direction(void)
{
    puts("test_vmath_matrix3x3_set_shear_x_direction");
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(123.0 ), VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_shear_x_direction(matrix, VMATHNUMBER_C( 123.0 ));
    assert_equals_matrix3x3(expect, matrix);
}

void test_vmath_matrix3x3_set_shear_y_direction(void)
{
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
    assert_equals_matrix3x3(expect, matrix);
}

void test_vmath_matrix3x3_set_shear_x_and_y_direction(void)
{
    puts("test_vmath_matrix3x3_set_shear_x_and_y_direction");
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(234.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(123.0 ), VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_set_shear_x_and_y_direction(matrix, VMATHNUMBER_C( 123.0 ), VMATHNUMBER_C( 234.0 ));
    assert_equals_matrix3x3(expect, matrix);
}

void test_vmath_matrix3x3_upd_translation(void)
{
    puts("test_vmath_matrix3x3_upd_translation");
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(123.0 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(234.0 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    vmath_matrix3x3_upd_translation(matrix, VMATHNUMBER_C( 123.0 ), VMATHNUMBER_C( 234.0 ));
    assert_equals_matrix3x3(expect, matrix);
}

void test_vmath_matrix3x3_upd_scaling(void)
{
    puts("test_vmath_matrix3x3_upd_scaling");
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(123.0 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-345.0 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    vmath_matrix3x3_upd_scaling(matrix, VMATHNUMBER_C( 123.0 ), VMATHNUMBER_C( -345.0 ));
    assert_equals_matrix3x3(expect, matrix);
}

void test_vmath_matrix3x3_upd_rotation_clockwise(void)
{
    puts("test_vmath_matrix3x3_upd_rotation_clockwise");
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_upd_rotation_clockwise(matrix, VMATHNUMBER_C( 123.0 ));
    assert_equals_matrix3x3(expect, matrix);
}

void test_vmath_matrix3x3_upd_rotation_anticlockwise(void)
{
    puts("test_vmath_matrix3x3_upd_rotation_anticlockwise");
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), VMATHNUMBER_C(0.0 ),
            VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(0.0 ), VMATHNUMBER_C(1.0 ), };
    vmath_matrix3x3_upd_rotation_anticlockwise(matrix, VMATHNUMBER_C( 123.0 ));
    assert_equals_matrix3x3(expect, matrix);
}

void test_vmath_matrix3x3_upd_shear_x_direction(void)
{
    puts("test_vmath_matrix3x3_upd_shear_x_direction");
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(123.0 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    vmath_matrix3x3_upd_shear_x_direction(matrix, VMATHNUMBER_C( 123.0 ));
    assert_equals_matrix3x3(expect, matrix);
}

void test_vmath_matrix3x3_upd_shear_y_direction(void)
{
    puts("test_vmath_matrix3x3_upd_shear_y_direction");
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(123.0 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    vmath_matrix3x3_upd_shear_y_direction(matrix, VMATHNUMBER_C( 123.0 ));
    assert_equals_matrix3x3(expect, matrix);
}

void test_vmath_matrix3x3_upd_shear_x_and_y_direction(void)
{
    puts("test_vmath_matrix3x3_upd_shear_x_and_y_direction");
    VmathMatrix3x3 matrix = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(-1.2 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(-2.1 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    const VmathMatrix3x3 expect = {
            VMATHNUMBER_C(-1.1 ), VMATHNUMBER_C(234.0 ), VMATHNUMBER_C(-1.3 ),
            VMATHNUMBER_C(123.0 ), VMATHNUMBER_C(-2.2 ), VMATHNUMBER_C(-2.3 ),
            VMATHNUMBER_C(-3.1 ), VMATHNUMBER_C(-3.2 ), VMATHNUMBER_C(-3.3 ), };
    vmath_matrix3x3_upd_shear_x_and_y_direction(matrix, VMATHNUMBER_C( 123.0 ), VMATHNUMBER_C( 234.0 ));
    assert_equals_matrix3x3(expect, matrix);
}

void test_vmath_matrix3x3_multiply_matrix3x3(void)
{
    puts("test_vmath_matrix3x3_multiply_matrix3x3");
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
    assert_equals_matrix3x3(expect, result);
}

void test_vmath_matrix3x3_multiply_matrix3x1(void)
{
    puts("test_vmath_matrix3x3_multiply_matrix3x1");
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
    assert_equals_matrix3x1(expect, result);
}



void run_all_tests(void)
{
    test_failed = 0;

    test_vmath_mbr_sin();
    test_vmath_mbr_cos();
    test_vmath_rad_to_mbr();
    test_vmath_deg_to_mbr();
    test_vmath_mbr_to_rad();
    test_vmath_deg_to_rad();
    test_vmath_mbr_to_deg();
    test_vmath_rad_to_deg();
    test_vmath_matrix3x1_normalise();
    test_vmath_matrix3x1_homogeneous_to_cartesian();
    test_vmath_matrix3x3_set_identity();
    test_vmath_matrix3x3_set_translation();
    test_vmath_matrix3x3_set_scaling();
    test_vmath_matrix3x3_set_rotation_clockwise();
    test_vmath_matrix3x3_set_rotation_anticlockwise();
    test_vmath_matrix3x3_set_reflect_x();
    test_vmath_matrix3x3_set_reflect_y();
    test_vmath_matrix3x3_set_reflect_origin();
    test_vmath_matrix3x3_set_reflect_y_equals_x();
    test_vmath_matrix3x3_set_reflect_y_equals_neg_x();
    test_vmath_matrix3x3_set_shear_x_direction();
    test_vmath_matrix3x3_set_shear_y_direction();
    test_vmath_matrix3x3_set_shear_x_and_y_direction();
    test_vmath_matrix3x3_upd_translation();
    test_vmath_matrix3x3_upd_scaling();
    test_vmath_matrix3x3_upd_rotation_clockwise();
    test_vmath_matrix3x3_upd_rotation_anticlockwise();
    test_vmath_matrix3x3_upd_shear_x_direction();
    test_vmath_matrix3x3_upd_shear_y_direction();
    test_vmath_matrix3x3_upd_shear_x_and_y_direction();
    test_vmath_matrix3x3_multiply_matrix3x3();
    test_vmath_matrix3x3_multiply_matrix3x1();

    assert_success();
}


// ******************** TESTS *********************

