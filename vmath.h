//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) Mathematics.
// Filename:     vmath.h
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

#ifndef __VMATH__H__
#define __VMATH__H__


#include <float.h>
#include <math.h>


//-----------------------------------------------------------------------------
// Constant Definition.
//-----------------------------------------------------------------------------

// Constant

#define VMATHNUMBER_C(v) (v ## f)


//-----------------------------------------------------------------------------
// Common Constants.
//-----------------------------------------------------------------------------

// The transcendental number PI.
#define VMATHNUMBER_PI (M_PI)

// The transcendental number PI multiplied by 2 (360 degrees).
#define VMATHNUMBER_2PI (VMATHNUMBER_C( 2.0 ) * (M_PI))


//-----------------------------------------------------------------------------
// Number and Matrix Data Types and Limits.
//-----------------------------------------------------------------------------

// Number type minimum value.
#define VMATHNUMBER_MIN FLT_MIN;

// Number type maximum value.
#define VMATHNUMBER_MAX FLT_MAX;

// Number type.
typedef float VmathNumber;

// Matrix 3X1 type; Generally used for homogeneous co-ordinates [0] = X, [1] = Y, [2] = T.
typedef VmathNumber VmathMatrix3x1[3];

// Matrix 3X3 type. Generally used for transformations.
typedef VmathNumber VmathMatrix3x3[3][3];


//-----------------------------------------------------------------------------
// Library life-cycle methods.
//-----------------------------------------------------------------------------

// Initialise math library.
extern void vmath_init(void);

// Clean-up the math library.
extern void vmath_done(void);


//-----------------------------------------------------------------------------
// Trigonometry Functions.
// Angles are specified in millibit-revolutions.
// Note: 360 degrees = 1024 millibit-revolutions.
//-----------------------------------------------------------------------------

// Get the sine value for an angle specified in millibit-revolutions.
extern VmathNumber vmath_mbr_sin(const VmathNumber mbr);

// Get the cosine value for an angle specified in millibit-revolutions.
extern VmathNumber vmath_mbr_cos(const VmathNumber mbr);


//-----------------------------------------------------------------------------
// Angle Conversion Functions.
// Millibit-revolutions (mbr), Radians (rad), and Degrees (deg).
// Note: 360 degrees = 1024 millibit-revolutions.
//-----------------------------------------------------------------------------

// Convert radians to millibit-revolutions.
extern VmathNumber vmath_rad_to_mbr(const VmathNumber rad);

// Convert degrees to millibit-revolutions.
extern VmathNumber vmath_deg_to_mbr(const VmathNumber deg);

// Convert millibit-revolutions to radians.
extern VmathNumber vmath_mbr_to_rad(const VmathNumber mbr);

// Convert degrees to radians.
extern VmathNumber vmath_deg_to_rad(const VmathNumber deg);

// Convert millibit-revolutions to degrees.
extern VmathNumber vmath_mbr_to_deg(const VmathNumber mbr);

// Convert radians to degrees.
extern VmathNumber vmath_rad_to_deg(const VmathNumber deg);


//-----------------------------------------------------------------------------
// Co-ordinate Conversion Functions.
//-----------------------------------------------------------------------------

// Normalise a 3x1 matrix to unit length..
extern void vmath_matrix3x1_normalise(VmathMatrix3x1 matrix);

// Convert a 3x1 matrix od homogeneous co-ordinates to cartesian co-ordinates.
extern void vmath_matrix3x1_homogeneous_to_cartesian(VmathMatrix3x1 matrix);


//-----------------------------------------------------------------------------
// Set a 3x3 Matrix With a Chosen Transformation.
//-----------------------------------------------------------------------------

// Set a 3x3 matrix with its identity.
extern void vmath_matrix3x3_set_identity(VmathMatrix3x3 matrix);

// Set a 3x3 matrix with a translation value for both the  X and Y directions.
extern void vmath_matrix3x3_set_translation(VmathMatrix3x3 matrix, const VmathNumber tx, const VmathNumber ty);

// Set a 3x3 matrix with a scale value for both the X and Y directions.
extern void vmath_matrix3x3_set_scaling(VmathMatrix3x3 matrix, const VmathNumber sx, const VmathNumber sy);

// Set a 3x3 matrix with a clockwise rotation in millibit-revolutions.
extern void vmath_matrix3x3_set_rotation_clockwise(VmathMatrix3x3 matrix, const VmathNumber mbr);

// Set a 3x3 matrix with an anti-clockwise rotation in millibit-revolutions.
extern void vmath_matrix3x3_set_rotation_anticlockwise(VmathMatrix3x3 matrix, const VmathNumber mbr);

// Set a 3x3 matrix with a reflection transform against the X axis.
extern void vmath_matrix3x3_set_reflect_x(VmathMatrix3x3 matrix);

// Set a 3x3 matrix with a reflection transform against the Y axis.
extern void vmath_matrix3x3_set_reflect_y(VmathMatrix3x3 matrix);

// Set a 3x3 matrix with a reflection transform about the origin (against both the X and Y axis).
extern void vmath_matrix3x3_set_reflect_origin(VmathMatrix3x3 matrix);

// Set a 3x3 matrix with a reflection transform about Y = X line.
extern void vmath_matrix3x3_set_reflect_y_equals_x(VmathMatrix3x3 matrix);

// Set a 3x3 matrix with a reflection transform about Y = -X line.
extern void vmath_matrix3x3_set_reflect_y_equals_neg_x(VmathMatrix3x3 matrix);

// Set a 3x3 matrix with a shear transform in the X direction.
extern void vmath_matrix3x3_set_shear_x_direction(VmathMatrix3x3 matrix, const VmathNumber shx);

// Set a 3x3 matrix with a shear transform in the Y direction.
extern void vmath_matrix3x3_set_shear_y_direction(VmathMatrix3x3 matrix, const VmathNumber shy);

// Set a 3x3 matrix with a shear transform in both the X and Y directions.
extern void vmath_matrix3x3_set_shear_x_and_y_direction(VmathMatrix3x3 matrix, const VmathNumber shx, const VmathNumber shy);


//-----------------------------------------------------------------------------
// Update a Previously Set 3x3 Matrix Transformation With New Values.
//-----------------------------------------------------------------------------

// Update a previously set 3x3 matrix with a translation value for both the  X and Y directions.
extern void vmath_matrix3x3_upd_translation(VmathMatrix3x3 matrix, const VmathNumber tx, const VmathNumber ty);

// Update a previously set 3x3 matrix with a scale value for both the X and Y directions.
extern void vmath_matrix3x3_upd_scaling(VmathMatrix3x3 matrix, const VmathNumber sx, const VmathNumber sy);

// Update a previously set 3x3 matrix with a clockwise rotation in millibit-revolutions.
extern void vmath_matrix3x3_upd_rotation_clockwise(VmathMatrix3x3 matrix, const VmathNumber mbr);

// Update a previously set 3x3 matrix with a anti-clockwise rotation in millibit-revolutions.
extern void vmath_matrix3x3_upd_rotation_anticlockwise(VmathMatrix3x3 matrix, const VmathNumber mbr);

// Update a previously set 3x3 matrix with a shear transform in the X direction.
extern void vmath_matrix3x3_upd_shear_x_direction(VmathMatrix3x3 matrix, const VmathNumber shx);

// Update a previously set 3x3 matrix with a shear transform in the Y direction.
extern void vmath_matrix3x3_upd_shear_y_direction(VmathMatrix3x3 matrix, const VmathNumber shy);

// Update a previously set 3x3 matrix with a shear transform in both the X and Y directions.
extern void vmath_matrix3x3_upd_shear_x_and_y_direction(VmathMatrix3x3 matrix, const VmathNumber shx, const VmathNumber shy);


//-----------------------------------------------------------------------------
// Matrix Multiplication.
//-----------------------------------------------------------------------------

// Multiply a 3x3 matrix by another 3x3 matrix storing the result into another 3x3 matrix.
extern void vmath_matrix3x3_multiply_matrix3x3(const VmathMatrix3x3 matrix1, const VmathMatrix3x3 matrix2, VmathMatrix3x3 result);

// Multiply a 3x3 matrix by another 3x3 matrix storing the result into either matrix1 or matrix2..
extern void vmath_matrix3x3_multiply_matrix3x3_safe(const VmathMatrix3x3 matrix1, const VmathMatrix3x3 matrix2, const _Bool result_matrix2);

// Multiply a 3x3 matrix by a 3x1 matrix storing the result into a 3x1 matrix.
extern void vmath_matrix3x3_multiply_matrix3x1(const VmathMatrix3x3 matrix1, const VmathMatrix3x1 matrix2, VmathMatrix3x1 result);

// Multiply a 3x3 matrix by a 3x1 matrix storing the result into the 3x1 matrix.
extern void vmath_matrix3x3_multiply_matrix3x1_safe(const VmathMatrix3x3 matrix1, const VmathMatrix3x1 matrix2);



#endif /* __VMATH__H__ */


