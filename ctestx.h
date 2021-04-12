//=============================================================================
// Title:        CTest Extras.
// Filename:     ctestx.h
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-04-12 22:54
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


// CTest include (implementation) file.
#include "ctest.h"


// Standard string functions.
#include <string.h>


// Standard memory functions.
#include <memory.h>



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

int is_cstr_equal(const char * cstr1, const char * cstr2)
{
    if (cstr1 == cstr2) {
        return 1;
    }
    if ((cstr1 == NULL) || (cstr2 == NULL)) {
        return 0;
    }
    return !strcmp(cstr1, cstr2);
}


int is_mem_equal(const void * mem_ptr1, const int mem_size1, const void * mem_ptr2, const int mem_size2)
{
    if ((mem_ptr1 == mem_ptr2) && (mem_size1 == mem_size2)) {
        return 1;
    }
    if (mem_size1 != mem_size2) {
        return 0;
    }
    if ((mem_ptr1 == NULL) || (mem_ptr2 == NULL)) {
        return 0;
    }
    return !memcmp(mem_ptr1, mem_ptr2, mem_size1);
}



//-----------------------------------------------------------------------------
// Common Test Assertions Macros And Test Assertion Functions Prototypes.
//-----------------------------------------------------------------------------

// Assert equality.
#define ASSERT_DBL_EQUAL(exp, real) ASSERT_DBL_NEAR_TOL(exp, real, 0e-0)


// Assert inequality.
#define ASSERT_DBL_NOT_EQUAL(exp, real) ASSERT_DBL_FAR_TOL(exp, real, 0e-0)


// Assertion function declaration and its client used macro.
void assert_cstr_equal(const char * exp, const char * real, const char * caller, int line);
#define ASSERT_CSTR_EQUAL(exp, real) assert_cstr_equal(exp, real, __FILE__, __LINE__)


// Assertion function declaration and its client used macro.
void assert_cstr_not_equal(const char * exp, const char * real, const char * caller, int line);
#define ASSERT_CSTR_NOT_EQUAL(exp, real) assert_cstr_not_equal(exp, real, __FILE__, __LINE__)


// Assertion function declaration and its client used macro.
void assert_mem_equal(const void * exp_ptr, const int exp_size, const void * real_ptr, const int real_size, const char * caller, int line);
#define ASSERT_MEM_EQUAL(exp_ptr, exp_size, real_ptr, real_size) assert_vmathnumber_equal(xp_ptr, exp_size, real_ptr, real_size, __FILE__, __LINE__)


// Assertion function declaration and its client used macro.
void assert_mem_not_equal(const void * exp_ptr, const int exp_size, const void * real_ptr, const int real_size, const char * caller, int line);
#define ASSERT_MEM_NOT)EQUAL(exp_ptr, exp_size, real_ptr, real_size) assert_vmathnumber_equal(xp_ptr, exp_size, real_ptr, real_size, __FILE__, __LINE__)



//-----------------------------------------------------------------------------
// Common Test Assertions Functions Implementation.
//-----------------------------------------------------------------------------

// Assertion function definition.
void assert_cstr_equal(const char * exp, const char * real, const char * caller, int line)
{
    if (!is_cstr_equal(exp, real)) {
        CTEST_ERR("%s:%d expected string %s got %s", caller, line, exp, real);
    }
}


// Assertion function definition.
void assert_cstr_not_equal(const char * exp, const char * real, const char * caller, int line)
{
    if (is_cstr_equal(exp, real)) {
        CTEST_ERR("%s:%d should not be %s", caller, line, real);
    }
}


// Assertion function definition.
void assert_mem_equal(const void * exp_ptr, const int exp_size, const void * real_ptr, const int real_size, const char * caller, int line)
{
    if (!is_mem_equal(exp_ptr, exp_size, real_ptr, real_size)) {
        CTEST_ERR("%s:%d expected memory contents %p with size %d got %p with size %d", caller, line, exp_ptr, exp_size, real_ptr, real_size);
    }
}


// Assertion function definition.
void assert_mem_not_equal(const void * exp_ptr, const int exp_size, const void * real_ptr, const int real_size, const char * caller, int line)
{
    if (is_mem_equal(exp_ptr, exp_size, real_ptr, real_size)) {
        CTEST_ERR("%s:%d should not be %p with size of ", caller, line, real_ptr, real_size);
    }
}



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


