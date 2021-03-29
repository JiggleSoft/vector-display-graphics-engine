//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) Mathematics.
// Filename:     vmath.c
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-03-28 13:52
// Version:      1.0.0-beta-2
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



//-----------------------------------------------------------------------------
// Trigonometry Sine and Cosine Configuration.
//-----------------------------------------------------------------------------

// Trigonometry sin / cos look-up table precision (4 = 1/4 milli-bit revs).
#ifndef VMATH_SINCOS_PRECISION
#define VMATH_SINCOS_PRECISION 4
#endif


//-----------------------------------------------------------------------------
// Trigonometry Sine and Cosine Look-up Table.
//-----------------------------------------------------------------------------

// Millibit-revolution look up table.
static VmathNumber vmath_millirev_lut[1024 * VMATH_SINCOS_PRECISION];


//-----------------------------------------------------------------------------
// Library life-cycle methods.
//-----------------------------------------------------------------------------

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


//-----------------------------------------------------------------------------
// Clipping Functions.
//-----------------------------------------------------------------------------

// Clip to a floor clipping value. Returns value but no less than clip.
VmathNumber vmath_clip_floor(const VmathNumber value, const VmathNumber clip)
{
    return (value < clip) ? clip : value;
}

// Clip to a ceiling clipping value. Returns value but no greater than clip.
VmathNumber vmath_clip_ceil(const VmathNumber value, const VmathNumber clip)
{
    return (value > clip) ? clip : value;
}

// Clip to a floor and ceiling clipping values.
// Returns value but no less than clip_floor and no greater than clip_ceil.
VmathNumber vmath_clip_floor_ceil(const VmathNumber value,
                                  const VmathNumber clip_floor,
                                  const VmathNumber clip_ceil)
{
    return (value < clip_floor) ? clip_floor : (value > clip_ceil) ? clip_ceil : value;
}


//-----------------------------------------------------------------------------
// Trigonometry Functions.
//-----------------------------------------------------------------------------

// Get the sine value for an angle specified in millibit-revolutions.
VmathNumber vmath_mbr_sin(VmathNumber mbr)
{
    return vmath_millirev_lut[(int)(vmath_normalise_mbr(mbr) * VMATH_SINCOS_PRECISION)];
}


// Get the cosine value for an angle specified in millibit-revolutions.
VmathNumber vmath_mbr_cos(VmathNumber mbr)
{
    return vmath_millirev_lut[(int)(vmath_normalise_mbr(mbr + VMATHNUMBER_C(256.0)) * VMATH_SINCOS_PRECISION)];
}


//-----------------------------------------------------------------------------
// Full Rotation and Angle Measurement Type Ratio Constants.
//-----------------------------------------------------------------------------

// Milli-bit revolutions per full revolution.
#define VMATH_MBR_PER_REV VMATHNUMBER_C(1024.0)
// Radians per full revolution.
#define VMATH_RAD_PER_REV VMATHNUMBER_2PI
// Radians per full revolution.
#define VMATH_DEG_PER_REV VMATHNUMBER_C(360.0)

// Milli-bit revolutions per radian.
#define VMATH_MBR_PER_RAD (VMATH_MBR_PER_REV / VMATH_RAD_PER_REV)
// Milli-bit revolutions per degree.
#define VMATH_MBR_PER_DEG (VMATH_MBR_PER_REV / VMATH_DEG_PER_REV)
// Radians per Milli-bit revolution.
#define VMATH_RAD_PER_MBR (VMATH_RAD_PER_REV / VMATH_MBR_PER_REV)
// Radians per degree.
#define VMATH_RAD_PER_DEG (VMATH_RAD_PER_REV / VMATH_DEG_PER_REV)
// Degrees per Milli-bit revolution.
#define VMATH_DEG_PER_MBR (VMATH_DEG_PER_REV / VMATH_MBR_PER_REV)
// Degrees per radian.
#define VMATH_DEG_PER_RAD (VMATH_DEG_PER_REV / VMATH_RAD_PER_REV)


//-----------------------------------------------------------------------------
// Angle Conversion Functions.
//-----------------------------------------------------------------------------

// Convert radians to millibit-revolutions.
VmathNumber vmath_rad_to_mbr(VmathNumber rad)
{
    return rad * VMATH_MBR_PER_RAD;
}


// Convert degrees to millibit-revolutions.
VmathNumber vmath_deg_to_mbr(VmathNumber deg)
{
    return deg * VMATH_MBR_PER_DEG;
}


// Convert millibit-revolutions to radians.
VmathNumber vmath_mbr_to_rad(VmathNumber mbr)
{
    return mbr * VMATH_RAD_PER_MBR;
}


// Convert degrees to radians.
VmathNumber vmath_deg_to_rad(VmathNumber deg)
{
    return deg * VMATH_RAD_PER_DEG;
}


// Convert millibit-revolutions to degrees.
VmathNumber vmath_mbr_to_deg(VmathNumber mbr)
{
    return mbr * VMATH_DEG_PER_MBR;
}


// Convert radians to degrees.
VmathNumber vmath_rad_to_deg(VmathNumber deg)
{
    return deg * VMATH_DEG_PER_RAD;
}


//-----------------------------------------------------------------------------
// Angle Normalisation Functions.
//-----------------------------------------------------------------------------

// Normalise millibit-revolutions.
VmathNumber vmath_normalise_mbr(const VmathNumber mbr)
{
    VmathNumber norm = fmodf(mbr, VMATH_MBR_PER_REV);
    if (norm < VMATHNUMBER_C(0.0)) {
        return VMATH_MBR_PER_REV + norm;
    }
    return norm;
}


// Normalise radians.
VmathNumber vmath_normalise_rad(const VmathNumber rad)
{
    VmathNumber norm = fmodf(rad, VMATH_RAD_PER_REV);
    if (norm < VMATHNUMBER_C(0.0)) {
        return VMATH_RAD_PER_REV + norm;
    }
    return norm;
}


// Normalise degrees.
VmathNumber vmath_normalise_deg(const VmathNumber deg)
{
    VmathNumber norm = fmodf(deg, VMATH_DEG_PER_REV);
    if (norm < VMATHNUMBER_C(0.0)) {
        return VMATH_DEG_PER_REV + norm;
    }
    return norm;
}


//-----------------------------------------------------------------------------
// Co-ordinate Conversion Functions.
//-----------------------------------------------------------------------------

// Normalise a 3x1 matrix to unit length and convert to cartesian co-ordinates.
void vmath_matrix3x1_normalise_to_cartesian(VmathMatrix3x1 matrix)
{
    vmath_matrix3x1_normalise(matrix);
    vmath_matrix3x1_homogeneous_to_cartesian(matrix);
}


// Normalise a 3x1 matrix to unit length.
void vmath_matrix3x1_normalise(VmathMatrix3x1 matrix)
{
    VmathNumber length = sqrt( (matrix[0] * matrix[0]) + (matrix[1] * matrix[1]));
    matrix[0] = matrix[0] / length;
    matrix[1] = matrix[1] / length;
}


// Convert a 3x1 matrix of homogeneous co-ordinates to cartesian co-ordinates.
void vmath_matrix3x1_homogeneous_to_cartesian(VmathMatrix3x1 matrix)
{
    matrix[0] = matrix[0] / matrix[2];
    matrix[1] = matrix[1] / matrix[2];
    matrix[2] = VMATHNUMBER_C( 1.0 );
}


//-----------------------------------------------------------------------------
// Set a 3x3 Matrix With a Chosen Transformation.
//-----------------------------------------------------------------------------

// Set a 3x3 matrix with its identity.
void vmath_matrix3x3_set_identity(VmathMatrix3x3 matrix)
{
    matrix[0][0] = 1;  matrix[0][1] = 0;  matrix[0][2] = 0;
    matrix[1][0] = 0;  matrix[1][1] = 1;  matrix[1][2] = 0;
    matrix[2][0] = 0;  matrix[2][1] = 0;  matrix[2][2] = 1;
}


// Set a 3x3 matrix with a translation value for both the  X and Y directions.
void vmath_matrix3x3_set_translation(VmathMatrix3x3 matrix, const VmathNumber tx, const VmathNumber ty)
{
    matrix[0][0] = 1;  matrix[0][1] = 0;  matrix[0][2] = tx;
    matrix[1][0] = 0;  matrix[1][1] = 1;  matrix[1][2] = ty;
    matrix[2][0] = 0;  matrix[2][1] = 0;  matrix[2][2] = 1;
}


// Set a 3x3 matrix with a scale value for both the X and Y directions.
void vmath_matrix3x3_set_scaling(VmathMatrix3x3 matrix, const VmathNumber sx, const VmathNumber sy)
{
    matrix[0][0] = sx;  matrix[0][1] = 0;   matrix[0][2] = 0;
    matrix[1][0] = 0;   matrix[1][1] = sy;  matrix[1][2] = 0;
    matrix[2][0] = 0;   matrix[2][1] = 0;   matrix[2][2] = 1;
}


// Set a 3x3 matrix with a clockwise rotation in millibit-revolutions.
void vmath_matrix3x3_set_rotation_clockwise(VmathMatrix3x3 matrix, const VmathNumber mbr)
{
    VmathNumber cos = vmath_mbr_cos(mbr);
    VmathNumber sin = vmath_mbr_sin(mbr);
    matrix[0][0] = cos;  matrix[0][1] = -sin;  matrix[0][2] = 0;
    matrix[1][0] = sin;  matrix[1][1] = cos;   matrix[1][2] = 0;
    matrix[2][0] = 0;    matrix[2][1] = 0;     matrix[2][2] = 1;
}


// Set a 3x3 matrix with an anti-clockwise rotation in millibit-revolutions.
void vmath_matrix3x3_set_rotation_anticlockwise(VmathMatrix3x3 matrix, const VmathNumber mbr)
{
    VmathNumber cos = vmath_mbr_cos(mbr);
    VmathNumber sin = vmath_mbr_sin(mbr);
    matrix[0][0] = cos;   matrix[0][1] = sin;  matrix[0][2] = 0;
    matrix[1][0] = -sin;  matrix[1][1] = cos;  matrix[1][2] = 0;
    matrix[2][0] = 0;     matrix[2][1] = 0;    matrix[2][2] = 1;
}


// Set a 3x3 matrix with a reflection transform against the X axis.
void vmath_matrix3x3_set_reflect_x(VmathMatrix3x3 matrix)
{
    matrix[0][0] = 1;  matrix[0][1] = 0;   matrix[0][2] = 0;
    matrix[1][0] = 0;  matrix[1][1] = -1;  matrix[1][2] = 0;
    matrix[2][0] = 0;  matrix[2][1] = 0;   matrix[2][2] = 1;
}


// Set a 3x3 matrix with a reflection transform against the Y axis.
void vmath_matrix3x3_set_reflect_y(VmathMatrix3x3 matrix)
{
    matrix[0][0] = -1;  matrix[0][1] = 0;  matrix[0][2] = 0;
    matrix[1][0] = 0;   matrix[1][1] = 1;  matrix[1][2] = 0;
    matrix[2][0] = 0;   matrix[2][1] = 0;  matrix[2][2] = 1;
}


// Set a 3x3 matrix with a reflection transform about the origin (against both the X and Y axis).
void vmath_matrix3x3_set_reflect_origin(VmathMatrix3x3 matrix)
{
    matrix[0][0] = -1;  matrix[0][1] = 0;   matrix[0][2] = 0;
    matrix[1][0] = 0;   matrix[1][1] = -1;  matrix[1][2] = 0;
    matrix[2][0] = 0;   matrix[2][1] = 0;   matrix[2][2] = 1;
}


// Set a 3x3 matrix with a reflection transform about Y = X line.
void vmath_matrix3x3_set_reflect_y_equals_x(VmathMatrix3x3 matrix)
{
    matrix[0][0] = 0;  matrix[0][1] = 1;  matrix[0][2] = 0;
    matrix[1][0] = 1;  matrix[1][1] = 0;  matrix[1][2] = 0;
    matrix[2][0] = 0;  matrix[2][1] = 0;  matrix[2][2] = 1;
}


// Set a 3x3 matrix with a reflection transform about Y = -X line.
void vmath_matrix3x3_set_reflect_y_equals_neg_x(VmathMatrix3x3 matrix)
{
    matrix[0][0] = 0;   matrix[0][1] = -1;  matrix[0][2] = 0;
    matrix[1][0] = -1;  matrix[1][1] = 0;   matrix[1][2] = 0;
    matrix[2][0] = 0;   matrix[2][1] = 0;   matrix[2][2] = 1;
}


// Set a 3x3 matrix with a shear transform in the X direction.
void vmath_matrix3x3_set_shear_x_direction(VmathMatrix3x3 matrix, const VmathNumber shx)
{
    matrix[0][0] = 1;    matrix[0][1] = 0;  matrix[0][2] = 0;
    matrix[1][0] = shx;  matrix[1][1] = 1;  matrix[1][2] = 0;
    matrix[2][0] = 0;    matrix[2][1] = 0;  matrix[2][2] = 1;
}


// Set a 3x3 matrix with a shear transform in the Y direction.
void vmath_matrix3x3_set_shear_y_direction(VmathMatrix3x3 matrix, const VmathNumber shy)
{
    matrix[0][0] = 1;  matrix[0][1] = shy;  matrix[0][2] = 0;
    matrix[1][0] = 0;  matrix[1][1] = 1;    matrix[1][2] = 0;
    matrix[2][0] = 0;  matrix[2][1] = 0;    matrix[2][2] = 1;
}


// Set a 3x3 matrix with a shear transform in both the X and Y directions.
void vmath_matrix3x3_set_shear_x_and_y_direction(VmathMatrix3x3 matrix, const VmathNumber shx, const VmathNumber shy)

{
    matrix[0][0] = 1;    matrix[0][1] = shy;  matrix[0][2] = 0;
    matrix[1][0] = shx;  matrix[1][1] = 1;    matrix[1][2] = 0;
    matrix[2][0] = 0;    matrix[2][1] = 0;    matrix[2][2] = 1;
}


//-----------------------------------------------------------------------------
// Update a Previously Set 3x3 Matrix Transformation With New Values.
//-----------------------------------------------------------------------------

// Update a previously set 3x3 matrix with a translation value for both the  X and Y directions.
void vmath_matrix3x3_upd_translation(VmathMatrix3x3 matrix, const VmathNumber tx, const VmathNumber ty)
{
    matrix[0][2] = tx;
    matrix[1][2] = ty;
}


// Update a previously set 3x3 matrix with a scale value for both the X and Y directions.
void vmath_matrix3x3_upd_scaling(VmathMatrix3x3 matrix, VmathNumber sx, const VmathNumber sy)
{
    matrix[0][0] = sx;
    matrix[1][1] = sy;
}


// Update a previously set 3x3 matrix with a clockwise rotation in millibit-revolutions.
void vmath_matrix3x3_upd_rotation_clockwise(VmathMatrix3x3 matrix, const VmathNumber mbr)
{
    VmathNumber cos = vmath_mbr_cos(mbr);
    VmathNumber sin = vmath_mbr_sin(mbr);
    matrix[0][0] = cos;  matrix[0][1] = -sin;
    matrix[1][0] = sin;  matrix[1][1] = cos;
}


// Update a previously set 3x3 matrix with a anti-clockwise rotation in millibit-revolutions.
void vmath_matrix3x3_upd_rotation_anticlockwise(VmathMatrix3x3 matrix, const VmathNumber mbr)
{
    VmathNumber cos = vmath_mbr_cos(mbr);
    VmathNumber sin = vmath_mbr_sin(mbr);
    matrix[0][0] = cos;   matrix[0][1] = sin;
    matrix[1][0] = -sin;  matrix[1][1] = cos;
}


// Update a previously set 3x3 matrix with a shear transform in the X direction.
void vmath_matrix3x3_upd_shear_x_direction(VmathMatrix3x3 matrix, const VmathNumber shx)
{
    matrix[1][0] = shx;
}


// Update a previously set 3x3 matrix with a shear transform in the Y direction.
void vmath_matrix3x3_upd_shear_y_direction(VmathMatrix3x3 matrix, const VmathNumber shy)
{
    matrix[0][1] = shy;
}


// Update a previously set 3x3 matrix with a shear transform in both the X and Y directions.
void vmath_matrix3x3_upd_shear_x_and_y_direction(VmathMatrix3x3 matrix, const VmathNumber shx, const VmathNumber shy)

{
    matrix[0][1] = shy;
    matrix[1][0] = shx;
}



//-----------------------------------------------------------------------------
// Matrix Multiplication.
//-----------------------------------------------------------------------------

// Multiply a 3x3 matrix by a 3x3 matrix storing the result into a 3x3 matrix (matrix1 and matrix2 must not equal result).
void vmath_matrix3x3_multiply_matrix3x3_fast(const VmathMatrix3x3 matrix1, const VmathMatrix3x3 matrix2, VmathMatrix3x3 result)
{
    assert((result != matrix1) && (result != matrix2));
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


// Multiply a 3x3 matrix by a 3x3 matrix storing the result into a 3x3 matrix (matrix1 or matrix2 may equal result).
void vmath_matrix3x3_multiply_matrix3x3(VmathMatrix3x3 matrix1, VmathMatrix3x3 matrix2, VmathMatrix3x3 result)
{
    if ((matrix2 == result) || (matrix1 == result)) {
        VmathMatrix3x3 temp_result;
        temp_result[0][0] = (matrix1[0][0] * matrix2[0][0]) + (matrix1[0][1] * matrix2[1][0]) + (matrix1[0][2] * matrix2[2][0]);
        temp_result[0][1] = (matrix1[0][0] * matrix2[0][1]) + (matrix1[0][1] * matrix2[1][1]) + (matrix1[0][2] * matrix2[2][1]);
        temp_result[0][2] = (matrix1[0][0] * matrix2[0][2]) + (matrix1[0][1] * matrix2[1][2]) + (matrix1[0][2] * matrix2[2][2]);
        temp_result[1][0] = (matrix1[1][0] * matrix2[0][0]) + (matrix1[1][1] * matrix2[1][0]) + (matrix1[1][2] * matrix2[2][0]);
        temp_result[1][1] = (matrix1[1][0] * matrix2[0][1]) + (matrix1[1][1] * matrix2[1][1]) + (matrix1[1][2] * matrix2[2][1]);
        temp_result[1][2] = (matrix1[1][0] * matrix2[0][2]) + (matrix1[1][1] * matrix2[1][2]) + (matrix1[1][2] * matrix2[2][2]);
        temp_result[2][0] = (matrix1[2][0] * matrix2[0][0]) + (matrix1[2][1] * matrix2[1][0]) + (matrix1[2][2] * matrix2[2][0]);
        temp_result[2][1] = (matrix1[2][0] * matrix2[0][1]) + (matrix1[2][1] * matrix2[1][1]) + (matrix1[2][2] * matrix2[2][1]);
        temp_result[2][2] = (matrix1[2][0] * matrix2[0][2]) + (matrix1[2][1] * matrix2[1][2]) + (matrix1[2][2] * matrix2[2][2]);
        memcpy(matrix2 == result ? matrix2 : matrix1, temp_result, sizeof(temp_result));
    } else {
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
}


// Multiply a 3x3 matrix by a 3x1 matrix storing the result into a 3x1 matrix (matrix2 must not equal result).
void vmath_matrix3x3_multiply_matrix3x1_fast(const VmathMatrix3x3 matrix1, const VmathMatrix3x1 matrix2, VmathMatrix3x1 result)
{
    assert(result != matrix2);
    result[0] = (matrix1[0][0] * matrix2[0]) + (matrix1[0][1] * matrix2[1]) + (matrix1[0][2] * matrix2[2]);
    result[1] = (matrix1[1][0] * matrix2[0]) + (matrix1[1][1] * matrix2[1]) + (matrix1[1][2] * matrix2[2]);
    result[2] = (matrix1[2][0] * matrix2[0]) + (matrix1[2][1] * matrix2[1]) + (matrix1[2][2] * matrix2[2]);
}


// Multiply a 3x3 matrix by a 3x1 matrix storing the result into a 3x1 matrix (matrix2 may equal result).
void vmath_matrix3x3_multiply_matrix3x1(const VmathMatrix3x3 matrix1, VmathMatrix3x1 matrix2, VmathMatrix3x1 result)
{
    if (matrix2 == result) {
        VmathMatrix3x1 temp_result;
        temp_result[0] = (matrix1[0][0] * matrix2[0]) + (matrix1[0][1] * matrix2[1]) + (matrix1[0][2] * matrix2[2]);
        temp_result[1] = (matrix1[1][0] * matrix2[0]) + (matrix1[1][1] * matrix2[1]) + (matrix1[1][2] * matrix2[2]);
        temp_result[2] = (matrix1[2][0] * matrix2[0]) + (matrix1[2][1] * matrix2[1]) + (matrix1[2][2] * matrix2[2]);
        memcpy(matrix2, temp_result, sizeof(temp_result));
    } else {
        result[0] = (matrix1[0][0] * matrix2[0]) + (matrix1[0][1] * matrix2[1]) + (matrix1[0][2] * matrix2[2]);
        result[1] = (matrix1[1][0] * matrix2[0]) + (matrix1[1][1] * matrix2[1]) + (matrix1[1][2] * matrix2[2]);
        result[2] = (matrix1[2][0] * matrix2[0]) + (matrix1[2][1] * matrix2[1]) + (matrix1[2][2] * matrix2[2]);
    }
}


