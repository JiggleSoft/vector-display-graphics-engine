//=============================================================================
// Title:        SDL2 Boot (Bootstrapping of SDL version 2) Unit Tests.
// Filename:     sdl2boot-tests.c
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-04-11 20:11
// Version:      1.0.0-alpha-1
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
#include "sdl2boot.h"


// CTest configuration.
#define CTEST_MAIN
#define CTEST_SEGFAULT

// CTest vDraw include (implementation) file.
#include "sdl2boot-ctest.h"



//-----------------------------------------------------------------------------
// Test Fixture Lifecycle.
//-----------------------------------------------------------------------------

CTEST_DATA(sdl2boot)
{
    Sdl2BootConfig  sdl2boot_config;
    Sdl2BootContext sdl2boot;
};


CTEST_SETUP(sdl2boot)
{
    sdl2boot_config_template(&data->sdl2boot_config, NULL);
    ASSERT_TRUE(sdl2boot_init(&data->sdl2boot, &data->sdl2boot_config));
}


CTEST_TEARDOWN(sdl2boot)
{
    sdl2boot_done(&data->sdl2boot);
}



//-----------------------------------------------------------------------------
// Constant Test Data.
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Test Configuration Functions..
//-----------------------------------------------------------------------------

CTEST(sdl2boot, test_sdl2boot_config_template) {
    ASSERT_FAIL();
}


CTEST(sdl2boot, test_sdl2boot_config_primary_desktop) {
    ASSERT_FAIL();
}



//-----------------------------------------------------------------------------
// Test Lifecycle Management Functions.
//-----------------------------------------------------------------------------

CTEST(sdl2boot, test_sdl2boot_init) {
    ASSERT_FAIL();
}


CTEST(sdl2boot, test_sdl2boot_done) {
    ASSERT_FAIL();
}



//-----------------------------------------------------------------------------
// Test Context State Access Functions and Macros.
//-----------------------------------------------------------------------------

CTEST2(sdl2boot, test_sdl2boot_is_initialised) {
    ASSERT_TRUE(sdl2boot_is_initialised(&data->sdl2boot));
    sdl2boot_done(&data->sdl2boot);
    ASSERT_FALSE(sdl2boot_is_initialised(&data->sdl2boot));
}


CTEST2(sdl2boot, test_sdl2boot_get_window) {
    ASSERT_FAIL();
}


CTEST2(sdl2boot, test_sdl2boot_get_renderer) {
    ASSERT_FAIL();
}


CTEST2(sdl2boot, test_sdl2boot_get_display_mode) {
    ASSERT_FAIL();
}


CTEST2(sdl2boot, test_sdl2boot_get_render_width) {
    ASSERT_FAIL();
}


CTEST2(sdl2boot, test_sdl2boot_get_render_height) {
    ASSERT_FAIL();
}



//-----------------------------------------------------------------------------
// Main Application Entry Point.
//-----------------------------------------------------------------------------

// Function main() implementation.
CTESTX_MAIN


