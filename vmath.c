//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) Mathematics.
// Filename:     vmath.c
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-03-14 22:51
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


#include <assert.h>
#include <memory.h>
#include <stdint.h>

#include "vmath.h"



#ifndef VMATH_SINCOS_PRECISION
#define VMATH_SINCOS_PRECISION 4
#endif


// Millibit-revolution look up table
static VmathNumber vmath_millirev_lut[1024 * VMATH_SINCOS_PRECISION];



// Initialise math library.
void vmath_init(void)
{
    for (int i = 0;  i < 1024 * VMATH_SINCOS_PRECISION;  i++)
    {
        vmath_millirev_lut[i] = sin(vmath_mbr_to_rad(i / VMATH_SINCOS_PRECISION));
    }
}


// Clean-up math library.
void vmath_done(void)
{
    // EMPTY.
}



// Millibit-revolution functions.
VmathNumber vmath_mbr_sin(VmathNumber mbr)
{
    return vmath_millirev_lut[(int)(vmath_normalise_mbr(mbr) * VMATH_SINCOS_PRECISION)];
}


VmathNumber vmath_mbr_cos(VmathNumber mbr)
{
    return vmath_millirev_lut[(int)(vmath_normalise_mbr(mbr + VMATHNUMBER_C(256.0)) * VMATH_SINCOS_PRECISION)];
}


// .
#define VMATH_MBR_PER_REV VMATHNUMBER_C(1024.0)
// .
#define VMATH_RAD_PER_REV VMATHNUMBER_2PI
// .
#define VMATH_DEG_PER_REV VMATHNUMBER_C(360.0)


#define VMATH_MBR_PER_RAD (VMATH_MBR_PER_REV / VMATH_RAD_PER_REV)
#define VMATH_MBR_PER_DEG (VMATH_MBR_PER_REV / VMATH_DEG_PER_REV)
#define VMATH_RAD_PER_MBR (VMATH_RAD_PER_REV / VMATH_MBR_PER_REV)
#define VMATH_RAD_PER_DEG (VMATH_RAD_PER_REV / VMATH_DEG_PER_REV)
#define VMATH_DEG_PER_MBR (VMATH_DEG_PER_REV / VMATH_MBR_PER_REV)
#define VMATH_DEG_PER_RAD (VMATH_DEG_PER_REV / VMATH_RAD_PER_REV)


// Angle conversion functions; Millibit-revolutions (mbr) (1024 * mbr = 360 degrees), Radians (rad), Degrees (deg).
VmathNumber vmath_rad_to_mbr(VmathNumber rad)
{
    return rad * VMATH_MBR_PER_RAD;
}


VmathNumber vmath_deg_to_mbr(VmathNumber deg)
{
    return deg * VMATH_MBR_PER_DEG;
}


VmathNumber vmath_mbr_to_rad(VmathNumber mbr)
{
    return mbr * VMATH_RAD_PER_MBR;
}


VmathNumber vmath_deg_to_rad(VmathNumber deg)
{
    return deg * VMATH_RAD_PER_DEG;
}


VmathNumber vmath_mbr_to_deg(VmathNumber mbr)
{
    return mbr * VMATH_DEG_PER_MBR;
}


VmathNumber vmath_rad_to_deg(VmathNumber deg)
{
    return deg * VMATH_DEG_PER_RAD;
}

#include <stdio.h>
//-----------------------------------------------------------------------------
// Angle Normalisation Functions.
//-----------------------------------------------------------------------------

// Normalise millibit-revolutions.
VmathNumber vmath_normalise_mbr(const VmathNumber mbr)
{
    VmathNumber norm;
    if (mbr < VMATHNUMBER_C(0.0)) {
        norm = VMATH_MBR_PER_REV + fmodf(mbr, VMATH_MBR_PER_REV);
    } else {
        return fmodf(mbr, VMATH_MBR_PER_REV);
    }
    if (norm >= VMATH_MBR_PER_REV) { // Covers where fmodf(,) becomes negative 0.0 that would have yielded 360.0.
        norm = VMATHNUMBER_C(0.0);
    }
    return norm;
}

// Normalise radians.
VmathNumber vmath_normalise_rad(const VmathNumber rad)
{
    VmathNumber norm;
    if (rad < VMATHNUMBER_C(0.0)) {
        norm = VMATH_RAD_PER_REV + fmodf(rad, VMATH_RAD_PER_REV);
    } else {
        return fmodf(rad, VMATH_RAD_PER_REV);
    }
    if (norm >= VMATH_RAD_PER_REV) { // Covers where fmodf(,) becomes negative 0.0 that would have yielded 360.0.
        norm = VMATHNUMBER_C(0.0);
    }
    return norm;
}


// Normalise degrees.
VmathNumber vmath_normalise_deg(const VmathNumber deg)
{
    VmathNumber norm;
    if (deg < VMATHNUMBER_C(0.0)) {
        norm = VMATH_DEG_PER_REV + fmodf(deg, VMATH_DEG_PER_REV);
    } else {
        return fmodf(deg, VMATH_DEG_PER_REV);
    }
    if (norm >= VMATH_DEG_PER_REV) { // Covers where fmodf(,) becomes negative 0.0 that would have yielded 360.0.
        norm = VMATHNUMBER_C(0.0);
    }
    return norm;
}



// Normalise a 3x1 matrix to unit length and convert to cartesian co-ordinates.
void vmath_matrix3x1_normalise_to_cartesian(VmathMatrix3x1 matrix)
{
    vmath_matrix3x1_normalise(matrix);
    vmath_matrix3x1_homogeneous_to_cartesian(matrix);
}


// Normalise a 3x1 matrix.
void vmath_matrix3x1_normalise(VmathMatrix3x1 matrix)
{
    VmathNumber length = sqrt( (matrix[0] * matrix[0]) + (matrix[1] * matrix[1]));
    matrix[0] = matrix[0] / length;
    matrix[1] = matrix[1] / length;
}


void vmath_matrix3x1_homogeneous_to_cartesian(VmathMatrix3x1 matrix)
{
    matrix[0] = matrix[0] / matrix[2];
    matrix[1] = matrix[1] / matrix[2];
    matrix[2] = VMATHNUMBER_C( 1.0 );
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


