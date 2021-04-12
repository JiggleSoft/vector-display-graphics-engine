//=============================================================================
// Title:        SDL2 Boot (Bootstrapping of SDL version 2) Unit Tests.
// Filename:     sdl2boot-tests.c
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-04-12 22:55
// Version:      1.0.0-alpha-2
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
    sdl2boot_config_from_template(&data->sdl2boot_config, NULL);
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

CTEST(sdl2boot, test_sdl2boot_config_from_template_null) {
    Sdl2BootConfig  sdl2boot_config;
    sdl2boot_config_from_template(&sdl2boot_config, NULL);
    ASSERT_EQUAL_U((SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK), sdl2boot_config.init_subsystems);
    ASSERT_CSTR_EQUAL("SDL 2 Boot version 1.0.0-beta-0 by Justin Lane.", sdl2boot_config.window_title);
    ASSERT_EQUAL_U((SDL_WINDOW_FULLSCREEN_DESKTOP), sdl2boot_config.window_flags);
    ASSERT_EQUAL_U((SDL_RENDERER_SOFTWARE), sdl2boot_config.renderer_flags);
}


CTEST(sdl2boot, test_sdl2boot_config_from_template_copy) {
    Sdl2BootConfig  sdl2boot_config_template;
    memset(&sdl2boot_config_template, 88, sizeof(sdl2boot_config_template));
    sdl2boot_config_template.init_subsystems = 62373723U;
    sdl2boot_config_template.window_title = "TEMPLATE_TITLE";
    sdl2boot_config_template.window_flags = 98318724U;
    sdl2boot_config_template.renderer_flags = 74312113U;
    Sdl2BootConfig  sdl2boot_config;
    memset(&sdl2boot_config, 99, sizeof(sdl2boot_config));
    sdl2boot_config_from_template(&sdl2boot_config, &sdl2boot_config_template);
    ASSERT_EQUAL_U(62373723U, sdl2boot_config.init_subsystems);
    ASSERT_CSTR_EQUAL("TEMPLATE_TITLE", sdl2boot_config.window_title);
    ASSERT_EQUAL_U(98318724U, sdl2boot_config.window_flags);
    ASSERT_EQUAL_U(74312113U, sdl2boot_config.renderer_flags);
}


CTEST(sdl2boot, test_sdl2boot_config_primary_desktop) {
    Sdl2BootConfig  sdl2boot_config;
    memset(&sdl2boot_config, 99, sizeof(sdl2boot_config));
    sdl2boot_config_primary_desktop(&sdl2boot_config, 262373723U, "TEMPLATE_TITLE", 398318724U, 474312113U);
    ASSERT_EQUAL_U(262373723U, sdl2boot_config.init_subsystems);
    ASSERT_CSTR_EQUAL("TEMPLATE_TITLE", sdl2boot_config.window_title);
    ASSERT_EQUAL_U(398318724U, sdl2boot_config.window_flags);
    ASSERT_EQUAL_U(474312113U, sdl2boot_config.renderer_flags);
}



//-----------------------------------------------------------------------------
// Test Lifecycle Management Functions.
//-----------------------------------------------------------------------------

CTEST2(sdl2boot, test_sdl2boot_init) {
}


CTEST2(sdl2boot, test_sdl2boot_done) {
    sdl2boot_done(&data->sdl2boot);
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
    ASSERT_NOT_NULL(sdl2boot_get_window(&data->sdl2boot));
}


CTEST2(sdl2boot, test_sdl2boot_get_renderer) {
    ASSERT_NOT_NULL(sdl2boot_get_renderer(&data->sdl2boot));
}


CTEST2(sdl2boot, test_sdl2boot_get_display_mode) {
    const SDL_DisplayMode * display_mode = sdl2boot_get_display_mode(&data->sdl2boot);
    ASSERT_NOT_NULL(display_mode);
    ASSERT_NOT_EQUAL(0, display_mode->format);
    ASSERT_TRUE(display_mode->w > 127);
    ASSERT_TRUE(display_mode->h > 127);
}


CTEST2(sdl2boot, test_sdl2boot_get_render_width) {
    ASSERT_TRUE(sdl2boot_get_render_width(&data->sdl2boot) > 127);
}


CTEST2(sdl2boot, test_sdl2boot_get_render_height) {
    ASSERT_TRUE(sdl2boot_get_render_height(&data->sdl2boot) > 127);
}



//-----------------------------------------------------------------------------
// Main Application Entry Point.
//-----------------------------------------------------------------------------

// Function main() implementation.
CTESTX_MAIN


