//=============================================================================
// Title:        CTest Extras.
// Filename:     ctestx.h
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-03-29 17:47
// Version:      1.0.0-beta-1
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


// CTest include (implementation) file.
#include "ctest.h"



//-----------------------------------------------------------------------------
// Common Test Utility Macros.
//-----------------------------------------------------------------------------

// Count of elements in a single dimension array.
#ifndef _countof
#define _countof(a) (sizeof(a) / sizeof(a[0]))
#endif



//-----------------------------------------------------------------------------
// Common Test Utility Functions.
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Common Test Assertions Macros And Test Assertion Functions Prototypes.
//-----------------------------------------------------------------------------

// Assert equality.
#define ASSERT_DBL_EQUAL(exp, real) ASSERT_DBL_NEAR_TOL(exp, real, 0e-0)

// Assert equality.
#define ASSERT_DBL_NOT_EQUAL(exp, real) ASSERT_DBL_FAR_TOL(exp, real, 0e-0)



//-----------------------------------------------------------------------------
// Common Test Assertions Functions Implementation.
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Main Implementation.
//-----------------------------------------------------------------------------

#ifdef CTEST_MAIN
#define CTESTX_MAIN \
int main(int argc, const char *argv[]) \
{\
    return ctest_main(argc, argv);\
}
#endif


