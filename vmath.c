//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) Mathematics.
// Filename:     vmath.c
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-01-24 19:27
// Version:      0.0.1
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
#include <memory.h>
#include "vmath.h"



// Millibit-revolution look up table
static VmathNumber vmath_millirev_lut[1024];



// Initialise math library.
void vmath_init(void)
{
    for (int i = 0;  i < 1024;  i++)
    {
        vmath_millirev_lut[i] = sin(vmath_mbr_to_rad(i));
    }
}



// Millibit-revolution functions.
VmathNumber vmath_mbr_sin(VmathNumber mbr)
{
    return vmath_millirev_lut[((int)(mbr + (0.5f))) % 1024];
}


VmathNumber vmath_mbr_cos(VmathNumber mbr)
{
    return vmath_millirev_lut[((int)(mbr + (256.5f))) % 1024];
}



// Angle conversion functions; Millibit-revolutions (mbr) (1024 * mbr = 360 degrees), Radians (rad), Degrees (deg).
VmathNumber vmath_rad_to_mbr(VmathNumber rad)
{
    return rad * VMATHNUMBER_2PI / VMATHNUMBER_C(1024.0);
}


VmathNumber vmath_deg_to_mbr(VmathNumber deg)
{
    return deg * (VMATHNUMBER_C( 1024.0 ) / VMATHNUMBER_C( 360.0 ));
}


VmathNumber vmath_mbr_to_rad(VmathNumber mbr)
{
    return mbr * VMATHNUMBER_2PI / VMATHNUMBER_C( 1024.0 );
}


VmathNumber vmath_deg_to_rad(VmathNumber deg)
{
    return deg * (VMATHNUMBER_C( 360.0 ) / VMATHNUMBER_C( 1024.0 ));;
}


VmathNumber vmath_mbr_to_deg(VmathNumber mbr)
{
    return mbr * (VMATHNUMBER_C( 360.0 ) / VMATHNUMBER_C( 1024.0 ));
}


VmathNumber vmath_rad_to_deg(VmathNumber deg)
{
    return deg * (VMATHNUMBER_C( 360.0 ) / VMATHNUMBER_C( 1024.0 ));;
}


// Normalise a matrix 3.
void vmath_matrix3x1_normalise(VmathMatrix3x1 matrix)
{
    vmath_matrix3x1_homogeneous_to_cartesian(matrix);
    VmathNumber length = sqrt( (matrix[0] * matrix[0]) + (matrix[1] * matrix[1]));
    matrix[0] = matrix[0] / length;
    matrix[1] = matrix[1] / length;
    // Already set by vmath_matrix3x1_homogeneous_to_cartesian - matrix[2] = VMATHNUMBER_C( 1.0 );
}


void vmath_matrix3x1_homogeneous_to_cartesian(VmathMatrix3x1 matrix)
{
    matrix[0] = matrix[0] / matrix[2];
    matrix[1] = matrix[1] / matrix[2];
    matrix[3] = VMATHNUMBER_C( 1.0 );
}


// Set a 3 x 3 matrix with a transformation.
void vmath_matrix3x3_set_identity(VmathMatrix3x3 matrix)
{
    matrix[0][0] = 1;  matrix[0][1] = 0;  matrix[0][2] = 0;
    matrix[1][0] = 0;  matrix[1][1] = 1;  matrix[1][2] = 0;
    matrix[2][0] = 0;  matrix[2][1] = 0;  matrix[2][2] = 1;
}


void vmath_matrix3x3_set_translation(VmathMatrix3x3 matrix, const VmathNumber tx, const VmathNumber ty)
{
    matrix[0][0] = 1;  matrix[0][1] = 0;  matrix[0][2] = tx;
    matrix[1][0] = 0;  matrix[1][1] = 1;  matrix[1][2] = ty;
    matrix[2][0] = 0;  matrix[2][1] = 0;  matrix[2][2] = 1;
}


void vmath_matrix3x3_set_scaling(VmathMatrix3x3 matrix, const VmathNumber sx, const VmathNumber sy)
{
    matrix[0][0] = sx;  matrix[0][1] = 0;   matrix[0][2] = 0;
    matrix[1][0] = 0;   matrix[1][1] = sy;  matrix[1][2] = 0;
    matrix[2][0] = 0;   matrix[2][1] = 0;   matrix[2][2] = 1;
}


void vmath_matrix3x3_set_rotation_clockwise(VmathMatrix3x3 matrix, const VmathNumber mbr)
{
    VmathNumber cos = vmath_mbr_cos(mbr);
    VmathNumber sin = vmath_mbr_sin(mbr);
    matrix[0][0] = cos;  matrix[0][1] = -sin;  matrix[0][2] = 0;
    matrix[1][0] = sin;  matrix[1][1] = cos;   matrix[1][2] = 0;
    matrix[2][0] = 0;    matrix[2][1] = 0;     matrix[2][2] = 1;
}


void vmath_matrix3x3_set_rotation_anticlockwise(VmathMatrix3x3 matrix, const VmathNumber mbr)
{
    VmathNumber cos = vmath_mbr_cos(mbr);
    VmathNumber sin = vmath_mbr_sin(mbr);
    matrix[0][0] = cos;   matrix[0][1] = sin;  matrix[0][2] = 0;
    matrix[1][0] = -sin;  matrix[1][1] = cos;  matrix[1][2] = 0;
    matrix[2][0] = 0;     matrix[2][1] = 0;    matrix[2][2] = 1;
}


void vmath_matrix3x3_set_reflect_x(VmathMatrix3x3 matrix)
{
    matrix[0][0] = 1;  matrix[0][1] = 0;   matrix[0][2] = 0;
    matrix[1][0] = 0;  matrix[1][1] = -1;  matrix[1][2] = 0;
    matrix[2][0] = 0;  matrix[2][1] = 0;   matrix[2][2] = 1;
}


void vmath_matrix3x3_set_reflect_y(VmathMatrix3x3 matrix)
{
    matrix[0][0] = -1;  matrix[0][1] = 0;  matrix[0][2] = 0;
    matrix[1][0] = 0;   matrix[1][1] = 1;  matrix[1][2] = 0;
    matrix[2][0] = 0;   matrix[2][1] = 0;  matrix[2][2] = 1;
}


void vmath_matrix3x3_set_reflect_origin(VmathMatrix3x3 matrix)
{
    matrix[0][0] = -1;  matrix[0][1] = 0;   matrix[0][2] = 0;
    matrix[1][0] = 0;   matrix[1][1] = -1;  matrix[1][2] = 0;
    matrix[2][0] = 0;   matrix[2][1] = 0;   matrix[2][2] = 1;
}


void vmath_matrix3x3_set_reflect_y_equals_x(VmathMatrix3x3 matrix)
{
    matrix[0][0] = 0;  matrix[0][1] = 1;  matrix[0][2] = 0;
    matrix[1][0] = 1;  matrix[1][1] = 0;  matrix[1][2] = 0;
    matrix[2][0] = 0;  matrix[2][1] = 0;  matrix[2][2] = 1;
}


void vmath_matrix3x3_set_reflect_y_equals_neg_x(VmathMatrix3x3 matrix)
{
    matrix[0][0] = 0;   matrix[0][1] = -1;  matrix[0][2] = 0;
    matrix[1][0] = -1;  matrix[1][1] = 0;   matrix[1][2] = 0;
    matrix[2][0] = 0;   matrix[2][1] = 0;   matrix[2][2] = 1;
}


void vmath_matrix3x3_set_shear_x_direction(VmathMatrix3x3 matrix, const VmathNumber shx)
{
    matrix[0][0] = 1;    matrix[0][1] = 0;  matrix[0][2] = 0;
    matrix[1][0] = shx;  matrix[1][1] = 1;  matrix[1][2] = 0;
    matrix[2][0] = 0;    matrix[2][1] = 0;  matrix[2][2] = 1;
}


void vmath_matrix3x3_set_shear_y_direction(VmathMatrix3x3 matrix, const VmathNumber shy)
{
    matrix[0][0] = 1;  matrix[0][1] = shy;  matrix[0][2] = 0;
    matrix[1][0] = 0;  matrix[1][1] = 1;    matrix[1][2] = 0;
    matrix[2][0] = 0;  matrix[2][1] = 0;    matrix[2][2] = 1;
}


void vmath_matrix3x3_set_shear_x_and_y_direction(VmathMatrix3x3 matrix, const VmathNumber shx, const VmathNumber shy)

{
    matrix[0][0] = 1;    matrix[0][1] = shy;  matrix[0][2] = 0;
    matrix[1][0] = shx;  matrix[1][1] = 1;    matrix[1][2] = 0;
    matrix[2][0] = 0;    matrix[2][1] = 0;    matrix[2][2] = 1;
}


// Update a 3 x 3 matrix with a transformation.
void vmath_matrix3x3_upd_translation(VmathMatrix3x3 matrix, const VmathNumber tx, const VmathNumber ty)
{
    matrix[0][2] = tx;
    matrix[1][2] = ty;
}


void vmath_matrix3x3_upd_scaling(VmathMatrix3x3 matrix, VmathNumber sx, const VmathNumber sy)
{
    matrix[0][0] = sx;
    matrix[1][1] = sy;
}


void vmath_matrix3x3_upd_rotation_clockwise(VmathMatrix3x3 matrix, const VmathNumber mbr)
{
    VmathNumber cos = vmath_mbr_cos(mbr);
    VmathNumber sin = vmath_mbr_sin(mbr);
    matrix[0][0] = cos;  matrix[0][1] = -sin;
    matrix[1][0] = sin;  matrix[1][1] = cos;
}


void vmath_matrix3x3_upd_rotation_anticlockwise(VmathMatrix3x3 matrix, const VmathNumber mbr)
{
    VmathNumber cos = vmath_mbr_cos(mbr);
    VmathNumber sin = vmath_mbr_sin(mbr);
    matrix[0][0] = cos;   matrix[0][1] = sin;
    matrix[1][0] = -sin;  matrix[1][1] = cos;
}


void vmath_matrix3x3_upd_shear_x_direction(VmathMatrix3x3 matrix, const VmathNumber shx)
{
    matrix[1][0] = shx;
}


void vmath_matrix3x3_upd_shear_y_direction(VmathMatrix3x3 matrix, const VmathNumber shy)
{
    matrix[0][1] = shy;
}


void vmath_matrix3x3_upd_shear_x_and_y_direction(VmathMatrix3x3 matrix, const VmathNumber shx, const VmathNumber shy)

{
    matrix[0][1] = shy;
    matrix[1][0] = shx;
}



// Multiply matrices.
void vmath_matrix3x3_multiply_matrix3x3(const VmathMatrix3x3 matrix1, const VmathMatrix3x3 matrix2, VmathMatrix3x3 result)
{
    assert(result != matrix1 && result != matrix2);
    result[0][0] = (matrix1[0][0] * matrix2[0][0]) + (matrix1[0][1] * matrix2[1][0]) + (matrix1[0][2] * matrix2[2][0]);
    result[0][1] = (matrix1[0][0] * matrix2[0][1]) + (matrix1[0][1] * matrix2[1][1]) + (matrix1[0][2] * matrix2[2][1]);
    result[0][2] = (matrix1[0][0] * matrix2[0][2]) + (matrix1[0][1] * matrix2[1][2]) + (matrix1[0][2] * matrix2[2][2]);
    result[1][0] = (matrix1[1][0] * matrix2[0][0]) + (matrix1[1][1] * matrix2[1][0]) + (matrix1[1][2] * matrix2[2][0]);
    result[1][1] = (matrix1[1][0] * matrix2[0][1]) + (matrix1[1][1] * matrix2[1][1]) + (matrix1[1][2] * matrix2[2][1]);
    result[1][2] = (matrix1[1][0] * matrix2[0][2]) + (matrix1[1][1] * matrix2[1][2]) + (matrix1[1][2] * matrix2[2][2]);
    result[2][0] = (matrix1[2][0] * matrix2[0][0]) + (matrix1[2][1] * matrix2[1][0]) + (matrix1[2][2] * matrix2[2][0]);
    result[2][1] = (matrix1[2][0] * matrix2[0][1]) + (matrix1[2][1] * matrix2[1][1]) + (matrix1[2][2] * matrix2[2][1]);
    result[2][2] = (matrix1[2][0] * matrix2[0][2]) + (matrix1[2][1] * matrix2[1][2]) + (matrix1[2][2] * matrix2[2][2]);
}

// Multiply a 3x3 matrix by another 3x3 matrix storing the result into either matrix1 or matrix2..
void vmath_matrix3x3_multiply_matrix3x3_safe (const VmathMatrix3x3 matrix1, const VmathMatrix3x3 matrix2, const _Bool result_matrix2)
{
    VmathMatrix3x3 result;
    result[0][0] = (matrix1[0][0] * matrix2[0][0]) + (matrix1[0][1] * matrix2[1][0]) + (matrix1[0][2] * matrix2[2][0]);
    result[0][1] = (matrix1[0][0] * matrix2[0][1]) + (matrix1[0][1] * matrix2[1][1]) + (matrix1[0][2] * matrix2[2][1]);
    result[0][2] = (matrix1[0][0] * matrix2[0][2]) + (matrix1[0][1] * matrix2[1][2]) + (matrix1[0][2] * matrix2[2][2]);
    result[1][0] = (matrix1[1][0] * matrix2[0][0]) + (matrix1[1][1] * matrix2[1][0]) + (matrix1[1][2] * matrix2[2][0]);
    result[1][1] = (matrix1[1][0] * matrix2[0][1]) + (matrix1[1][1] * matrix2[1][1]) + (matrix1[1][2] * matrix2[2][1]);
    result[1][2] = (matrix1[1][0] * matrix2[0][2]) + (matrix1[1][1] * matrix2[1][2]) + (matrix1[1][2] * matrix2[2][2]);
    result[2][0] = (matrix1[2][0] * matrix2[0][0]) + (matrix1[2][1] * matrix2[1][0]) + (matrix1[2][2] * matrix2[2][0]);
    result[2][1] = (matrix1[2][0] * matrix2[0][1]) + (matrix1[2][1] * matrix2[1][1]) + (matrix1[2][2] * matrix2[2][1]);
    result[2][2] = (matrix1[2][0] * matrix2[0][2]) + (matrix1[2][1] * matrix2[1][2]) + (matrix1[2][2] * matrix2[2][2]);
    memcpy(result_matrix2 ? matrix2 : matrix1, result, sizeof(result));
}


// Multiply a 3x3 matrix by a 3x1 matrix storing the result into a 3x1 matrix.
void vmath_matrix3x3_multiply_matrix3x1(const VmathMatrix3x3 matrix1, const VmathMatrix3x1 matrix2, VmathMatrix3x1 result)
{
    assert(result != matrix1 && result != matrix2);
    result[0] = (matrix1[0][0] * matrix2[0]) + (matrix1[0][1] * matrix2[1]) + (matrix1[0][2] * matrix2[2]);
    result[1] = (matrix1[1][0] * matrix2[0]) + (matrix1[1][1] * matrix2[1]) + (matrix1[1][2] * matrix2[2]);
    result[2] = (matrix1[2][0] * matrix2[0]) + (matrix1[2][1] * matrix2[1]) + (matrix1[2][2] * matrix2[2]);
}

// Multiply a 3x3 matrix by a 3x1 matrix storing the result into the 3x1 matrix.
void vmath_matrix3x3_multiply_matrix3x1_safe(const VmathMatrix3x3 matrix1, const VmathMatrix3x1 matrix2)
{
    VmathMatrix3x1 result;
    result[0] = (matrix1[0][0] * matrix2[0]) + (matrix1[0][1] * matrix2[1]) + (matrix1[0][2] * matrix2[2]);
    result[1] = (matrix1[1][0] * matrix2[0]) + (matrix1[1][1] * matrix2[1]) + (matrix1[1][2] * matrix2[2]);
    result[2] = (matrix1[2][0] * matrix2[0]) + (matrix1[2][1] * matrix2[1]) + (matrix1[2][2] * matrix2[2]);
    memcpy(matrix2, result, sizeof(result));
}


