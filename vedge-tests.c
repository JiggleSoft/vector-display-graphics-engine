//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) Unit Tests.
// Filename:     vedge-tests.c
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-03-17 20:12
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

// API under test.
#include "vedge.h"


// CTest configuration.
#define CTEST_MAIN
#define CTEST_SEGFAULT

// CTest include / implementation.
#include "ctest.h"



//-----------------------------------------------------------------------------
// .
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Test Fixture Lifecycle.
//-----------------------------------------------------------------------------

CTEST_DATA(vedge) {
};


CTEST_SETUP(vedge)
{
//FIXME:    vedge_init();
}


CTEST_TEARDOWN(vedge)
{
//FIXME:    vedge_done();
}



//-----------------------------------------------------------------------------
// Constant Test Data.
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Test Stuff.
//-----------------------------------------------------------------------------

CTEST(vedge, test_vedge_stuff) {
    ASSERT_FAIL();
}



//-----------------------------------------------------------------------------
// Main Application Entry Point./.
//-----------------------------------------------------------------------------

int main(int argc, const char *argv[])
{
    return ctest_main(argc, argv);
}


