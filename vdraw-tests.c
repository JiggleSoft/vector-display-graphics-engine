//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) vDraw Unit Tests.
// Filename:     vdraw-tests.c
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-04-12 22:59
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
#include "vdraw.h"


// CTest configuration.
#define CTEST_MAIN
#define CTEST_SEGFAULT

// CTest vDraw include (implementation) file.
#include "vdraw-ctest.h"


// Sdl2Boot
#include "sdl2boot.h"



//-----------------------------------------------------------------------------
// Test Fixture Lifecycle.
//-----------------------------------------------------------------------------

CTEST_DATA(vdraw_integration)
{
    Sdl2BootConfig  sdl2boot_config;
    Sdl2BootContext sdl2boot;
    VdrawContext    vdraw;
};


CTEST_SETUP(vdraw_integration)
{
    sdl2boot_config_from_template(&data->sdl2boot_config, NULL);
    ASSERT_TRUE(sdl2boot_init(&data->sdl2boot, &data->sdl2boot_config));
    ASSERT_TRUE(vdraw_init(&data->vdraw, data->sdl2boot.state.renderer));
}


CTEST_TEARDOWN(vdraw_integration)
{
    vdraw_done(&data->vdraw);
    sdl2boot_done(&data->sdl2boot);
}



//-----------------------------------------------------------------------------
// Constant Test Data.
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// Test Utility Functions.
//-----------------------------------------------------------------------------

CTEST(vdraw, test_vdraw_order_Line_single_pixel) {
    const VmathNumber x1a = VMATHNUMBER_C(10.0);
    const VmathNumber y1a = VMATHNUMBER_C(20.0);
    const VmathNumber x2a = VMATHNUMBER_C(30.0);
    const VmathNumber y2a = VMATHNUMBER_C(40.0);
    VmathNumber x1b = VMATHNUMBER_C(-1.0);
    VmathNumber y1b = VMATHNUMBER_C(-1.0);
    VmathNumber x2b = VMATHNUMBER_C(-1.0);
    VmathNumber y2b = VMATHNUMBER_C(-1.0);
    const VmathNumber x1c = VMATHNUMBER_C(10.0);
    const VmathNumber y1c = VMATHNUMBER_C(20.0);
    const VmathNumber x2c = VMATHNUMBER_C(30.0);
    const VmathNumber y2c = VMATHNUMBER_C(40.0);
    vdraw_order_line(x1a, y1a, x2a, y2a,
                     &x1b, &y1b, &x2b, &y2b);
    ASSERT_LINE_ORDERED(x1b, y1b, x2b, y2b);
    ASSERT_DBL_EQUAL(x1b, x1c);
    ASSERT_DBL_EQUAL(y1b, y1c);
    ASSERT_DBL_EQUAL(x2b, x2c);
    ASSERT_DBL_EQUAL(y2b, y2c);
}


CTEST(vdraw, test_vdraw_order_Line_315_045) {
    const VmathNumber x1a = VMATHNUMBER_C(100.0);
    const VmathNumber y1a = VMATHNUMBER_C(100.0);
    VmathNumber x2a;
    const VmathNumber y2a = VMATHNUMBER_C(50.0);
    VmathNumber x1b = VMATHNUMBER_C(-1.0);
    VmathNumber y1b = VMATHNUMBER_C(-1.0);
    VmathNumber x2b = VMATHNUMBER_C(-1.0);
    VmathNumber y2b = VMATHNUMBER_C(-1.0);
    for (int x = 50;  x <= 150;  x++) {
        x2a = (VmathNumber)x;
        vdraw_order_line(x1a, y1a, x2a, y2a,
                         &x1b, &y1b, &x2b, &y2b);
        ASSERT_LINE_ORDERED(x1b, y1b, x2b, y2b);
    }
}


CTEST(vdraw, test_vdraw_order_Line_045_135) {
    const VmathNumber x1a = VMATHNUMBER_C(100.0);
    const VmathNumber y1a = VMATHNUMBER_C(100.0);
    const VmathNumber x2a = VMATHNUMBER_C(150.0);
    VmathNumber y2a;
    VmathNumber x1b = VMATHNUMBER_C(-1.0);
    VmathNumber y1b = VMATHNUMBER_C(-1.0);
    VmathNumber x2b = VMATHNUMBER_C(-1.0);
    VmathNumber y2b = VMATHNUMBER_C(-1.0);
    for (int y = 50;  y <= 150;  y++) {
        y2a = (VmathNumber)y;
        vdraw_order_line(x1a, y1a, x2a, y2a,
                         &x1b, &y1b, &x2b, &y2b);
        ASSERT_LINE_ORDERED(x1b, y1b, x2b, y2b);
    }
}


CTEST(vdraw, test_vdraw_order_Line_135_225) {
    const VmathNumber x1a = VMATHNUMBER_C(100.0);
    const VmathNumber y1a = VMATHNUMBER_C(100.0);
    VmathNumber x2a;
    const VmathNumber y2a = VMATHNUMBER_C(150.0);
    VmathNumber x1b = VMATHNUMBER_C(-1.0);
    VmathNumber y1b = VMATHNUMBER_C(-1.0);
    VmathNumber x2b = VMATHNUMBER_C(-1.0);
    VmathNumber y2b = VMATHNUMBER_C(-1.0);
    for (int x = 50;  x <= 150;  x++) {
        x2a = (VmathNumber)x;
        vdraw_order_line(x1a, y1a, x2a, y2a,
                         &x1b, &y1b, &x2b, &y2b);
        ASSERT_LINE_ORDERED(x1b, y1b, x2b, y2b);
    }
}


CTEST(vdraw, test_vdraw_order_Line_225_315) {
    const VmathNumber x1a = VMATHNUMBER_C(100.0);
    const VmathNumber y1a = VMATHNUMBER_C(100.0);
    const VmathNumber x2a = VMATHNUMBER_C(50.0);
    VmathNumber y2a;
    VmathNumber x1b = VMATHNUMBER_C(-1.0);
    VmathNumber y1b = VMATHNUMBER_C(-1.0);
    VmathNumber x2b = VMATHNUMBER_C(-1.0);
    VmathNumber y2b = VMATHNUMBER_C(-1.0);
    for (int y = 50;  y <= 150;  y++) {
        y2a = (VmathNumber)y;
        vdraw_order_line(x1a, y1a, x2a, y2a,
                         &x1b, &y1b, &x2b, &y2b);
        ASSERT_LINE_ORDERED(x1b, y1b, x2b, y2b);
    }
}



//-----------------------------------------------------------------------------
// Primitive Drawing Life-cycle Functions.
//-----------------------------------------------------------------------------

CTEST2(vdraw_integration, test_vdraw_init) {
    VdrawContext vdraw;
    ASSERT_TRUE(vdraw_init(&vdraw, data->sdl2boot.state.renderer));
    ASSERT_EQUAL(data->sdl2boot.state.renderer, vdraw.renderer);
    ASSERT_EQUAL(data->sdl2boot.state.renderer_width, vdraw.width);
    ASSERT_EQUAL(data->sdl2boot.state.renderer_height, vdraw.height);
    ASSERT_EQUAL(0, vdraw.background_colour.red);
    ASSERT_EQUAL(0, vdraw.background_colour.green);
    ASSERT_EQUAL(0, vdraw.background_colour.blue);
    ASSERT_EQUAL(255, vdraw.foreground_colour.red);
    ASSERT_EQUAL(255, vdraw.foreground_colour.green);
    ASSERT_EQUAL(255, vdraw.foreground_colour.blue);
    ASSERT_DBL_EQUAL(VMATHNUMBER_C(1.0), vdraw.pen_width);
    ASSERT_EQUAL(255, vdraw.foreground_colour_requested.red);
    ASSERT_EQUAL(255, vdraw.foreground_colour_requested.green);
    ASSERT_EQUAL(255, vdraw.foreground_colour_requested.blue);
    ASSERT_DBL_EQUAL(VMATHNUMBER_C(1.0), vdraw.foreground_colour_intensity);
    ASSERT_EQUAL(0, vdraw.foreground_colour_fade_min.red);
    ASSERT_EQUAL(0, vdraw.foreground_colour_fade_min.green);
    ASSERT_EQUAL(0, vdraw.foreground_colour_fade_min.blue);
    ASSERT_EQUAL(255, vdraw.foreground_colour_fade_max.red);
    ASSERT_EQUAL(255, vdraw.foreground_colour_fade_max.green);
    ASSERT_EQUAL(255, vdraw.foreground_colour_fade_max.blue);
    ASSERT_EQUAL(VMATHNUMBER_C(1.0), vdraw.foreground_colour_fade_val);
    ASSERT_EQUAL(VMATHNUMBER_C(0.2), vdraw.foreground_intensity_wave_size);
    ASSERT_EQUAL(VMATHNUMBER_C(0.0), vdraw.foreground_intensity_wave_mbr_angle);
    ASSERT_EQUAL(VMATHNUMBER_C(16.0), vdraw.foreground_intensity_wave_mbr_speed);
}


CTEST2(vdraw_integration, test_vdraw_done) {
    VdrawContext vdraw;
    ASSERT_TRUE(vdraw_init(&vdraw, data->sdl2boot.state.renderer));
    ASSERT_EQUAL(data->sdl2boot.state.renderer, vdraw.renderer);
    vdraw_done(&vdraw);
    ASSERT_NULL(vdraw.renderer);
}



//-----------------------------------------------------------------------------
// Primitive Drawing State Functions.
//-----------------------------------------------------------------------------

CTEST(vdraw, test_vdraw_set_bg_colour) {
    VdrawContext vdraw = { 0 };
    vdraw_set_bg_colour(&vdraw, 92, 33, 187);
    ASSERT_DBL_EQUAL(92, vdraw.background_colour.red);
    ASSERT_DBL_EQUAL(33, vdraw.background_colour.green);
    ASSERT_DBL_EQUAL(187, vdraw.background_colour.blue);
}


CTEST(vdraw, test_vdraw_set_fg_colour) {
    VdrawContext vdraw = { 0 };
    vdraw_set_fg_colour(&vdraw, 27, 213, 132);
    ASSERT_DBL_EQUAL(27, vdraw.foreground_colour.red);
    ASSERT_DBL_EQUAL(213, vdraw.foreground_colour.green);
    ASSERT_DBL_EQUAL(132, vdraw.foreground_colour.blue);
}


CTEST(vdraw, test_vdraw_set_pen_width) {
    VdrawContext vdraw = { 0 };
    vdraw_set_pen_width(&vdraw, VMATHNUMBER_C(6.78));
    ASSERT_DBL_EQUAL(VMATHNUMBER_C(6.78), vdraw.pen_width);
}


CTEST(vdraw, test_vdraw_set_fg_colour_requested) {
    VdrawContext vdraw = { 0 };
    vdraw_set_fg_colour_requested(&vdraw, 127, 203, 193);
    ASSERT_DBL_EQUAL(127, vdraw.foreground_colour_requested.red);
    ASSERT_DBL_EQUAL(203, vdraw.foreground_colour_requested.green);
    ASSERT_DBL_EQUAL(193, vdraw.foreground_colour_requested.blue);
}


CTEST(vdraw, test_vdraw_set_fg_colour_intensity) {
    VdrawContext vdraw = { 0 };
    vdraw_set_fg_colour_intensity(&vdraw, VMATHNUMBER_C(0.65));//FIXME: Should this be clipped rage 0 - 1
    ASSERT_DBL_EQUAL(VMATHNUMBER_C(0.65), vdraw.foreground_colour_intensity);
}


CTEST(vdraw, test_vdraw_upd_fg_colour_from_requested_and_intensity) {
    VdrawContext vdraw = { 0 };
    vdraw_set_fg_colour_requested(&vdraw, 127, 203, 193);
    vdraw_set_fg_colour_intensity(&vdraw, VMATHNUMBER_C(0.66));
    vdraw_upd_fg_colour_from_requested_and_intensity(&vdraw);
    ASSERT_DBL_EQUAL(83, vdraw.foreground_colour.red);//FIXME: not rounding okay for speed? probably.
    ASSERT_DBL_EQUAL(133, vdraw.foreground_colour.green);
    ASSERT_DBL_EQUAL(127, vdraw.foreground_colour.blue);
}


CTEST(vdraw, test_vdraw_set_fg_colour_fade_min) {
    VdrawContext vdraw = { 0 };
    vdraw_set_fg_colour_fade_min(&vdraw, 239, 73, 22);
    ASSERT_DBL_EQUAL(239, vdraw.foreground_colour_fade_min.red);
    ASSERT_DBL_EQUAL(73, vdraw.foreground_colour_fade_min.green);
    ASSERT_DBL_EQUAL(22, vdraw.foreground_colour_fade_min.blue);
}


CTEST(vdraw, test_vdraw_set_fg_colour_fade_max) {
    VdrawContext vdraw = { 0 };
    vdraw_set_fg_colour_fade_max(&vdraw, 134, 47, 222);
    ASSERT_DBL_EQUAL(134, vdraw.foreground_colour_fade_max.red);
    ASSERT_DBL_EQUAL(47, vdraw.foreground_colour_fade_max.green);
    ASSERT_DBL_EQUAL(222, vdraw.foreground_colour_fade_max.blue);
}


CTEST(vdraw, test_vdraw_set_fg_colour_fade_val) {
    VdrawContext vdraw = { 0 };
    vdraw_set_fg_colour_fade_val(&vdraw, VMATHNUMBER_C(0.0));
    ASSERT_DBL_EQUAL(VMATHNUMBER_C(0.0), vdraw.foreground_colour_fade_val);
    vdraw_set_fg_colour_fade_val(&vdraw, VMATHNUMBER_C(0.0001));
    ASSERT_DBL_EQUAL(VMATHNUMBER_C(0.0001), vdraw.foreground_colour_fade_val);
    vdraw_set_fg_colour_fade_val(&vdraw, VMATHNUMBER_C(0.23));
    ASSERT_DBL_EQUAL(VMATHNUMBER_C(0.23), vdraw.foreground_colour_fade_val);
    vdraw_set_fg_colour_fade_val(&vdraw, VMATHNUMBER_C(0.9999));
    ASSERT_DBL_EQUAL(VMATHNUMBER_C(0.9999), vdraw.foreground_colour_fade_val);
    vdraw_set_fg_colour_fade_val(&vdraw, VMATHNUMBER_C(1.0));
    ASSERT_DBL_EQUAL(VMATHNUMBER_C(1.0), vdraw.foreground_colour_fade_val);
    vdraw_set_fg_colour_fade_val(&vdraw, VMATHNUMBER_C(-0.0001));
    ASSERT_DBL_EQUAL(VMATHNUMBER_C(0.0), vdraw.foreground_colour_fade_val);
    vdraw_set_fg_colour_fade_val(&vdraw, VMATHNUMBER_C(-2.222));
    ASSERT_DBL_EQUAL(VMATHNUMBER_C(0.0), vdraw.foreground_colour_fade_val);
    vdraw_set_fg_colour_fade_val(&vdraw, VMATHNUMBER_C(2.222));
    ASSERT_DBL_EQUAL(VMATHNUMBER_C(1.0), vdraw.foreground_colour_fade_val);
}


CTEST(vdraw, test_vdraw_upd_fg_colour_requested_from_fade) {
    VdrawContext vdraw = { 0 };
    vdraw_set_fg_colour_fade_min(&vdraw, 239, 73, 22);
    vdraw_set_fg_colour_fade_max(&vdraw, 134, 47, 222);
    vdraw_set_fg_colour_fade_val(&vdraw, VMATHNUMBER_C(0.0001));
    vdraw_upd_fg_colour_requested_from_fade(&vdraw);
    ASSERT_DBL_EQUAL(134, vdraw.foreground_colour_requested.red);
    ASSERT_DBL_EQUAL(47, vdraw.foreground_colour_requested.green);
    ASSERT_DBL_EQUAL(222, vdraw.foreground_colour_requested.blue);
}


CTEST(vdraw, test_vdraw_set_fg_intensity_wave_size) {
    VdrawContext vdraw = { 0 };
    vdraw_set_fg_intensity_wave_size(&vdraw, VMATHNUMBER_C(2.43)); //FIXME: bounds 0 - 1?
    ASSERT_DBL_EQUAL(VMATHNUMBER_C(2.43), vdraw.foreground_intensity_wave_size);
}


CTEST(vdraw, test_vdraw_set_fg_intensity_wave_mbr_angle) {
    VdrawContext vdraw = { 0 };
    vdraw_set_fg_intensity_wave_mbr_angle(&vdraw, VMATHNUMBER_C(539.44)); //FIXME: bounds 0 - 1023.9999?
    ASSERT_DBL_EQUAL(VMATHNUMBER_C(539.44), vdraw.foreground_intensity_wave_mbr_angle);
}


CTEST(vdraw, test_vdraw_set_fg_intensity_wave_mbr_speed) {
    VdrawContext vdraw = { 0 };
    vdraw_set_fg_intensity_wave_mbr_speed(&vdraw, VMATHNUMBER_C(16.132)); //FIXME: bounds 0 - 1023.9999?
    ASSERT_DBL_EQUAL(VMATHNUMBER_C(16.132), vdraw.foreground_intensity_wave_mbr_speed);
}


CTEST(vdraw, test_vdraw_upd_fg_intensity_wave_mbr_angle) {
    VdrawContext vdraw = { 0 };
    vdraw_set_fg_intensity_wave_mbr_speed(&vdraw, VMATHNUMBER_C(16.0));
    vdraw_set_fg_intensity_wave_mbr_angle(&vdraw, VMATHNUMBER_C(128.0));
    vdraw_upd_fg_intensity_wave_mbr_angle(&vdraw);
    ASSERT_DBL_EQUAL(VMATHNUMBER_C(144.0), vdraw.foreground_intensity_wave_mbr_angle);
}


CTEST(vdraw, test_vdraw_update_fg_colour_intensity_from_wave) {
    VdrawContext vdraw = { 0 };
    vdraw_set_fg_intensity_wave_size(&vdraw, VMATHNUMBER_C(0.2));
    vdraw_set_fg_intensity_wave_mbr_angle(&vdraw, VMATHNUMBER_C(128.0));
    vdraw_update_fg_colour_intensity_from_wave(&vdraw);
    ASSERT_DBL_EQUAL(VMATHNUMBER_C(0.141421356), vdraw.foreground_colour_intensity);
}



//-----------------------------------------------------------------------------
// Primitive Drawing Rendering Functions.
//-----------------------------------------------------------------------------

CTEST2(vdraw_integration, test_vdraw_clear_screen) {
    vdraw_set_bg_colour(&data->vdraw, 168, 63, 232);
    vdraw_clear_screen(&data->vdraw);
    vdraw_flip_screen(&data->vdraw);
    const SDL_Rect pixelRect = { .x = 100, .y = 100, .w = 1, .h = 1 };
    uint8_t pixels[3];
    ASSERT_EQUAL(0, SDL_RenderReadPixels(data->vdraw.renderer, &pixelRect, SDL_PIXELFORMAT_BGR888, pixels, 1));
    ASSERT_EQUAL(168, pixels[0]);
    ASSERT_EQUAL(63, pixels[1]);
    ASSERT_EQUAL(232, pixels[2]);
}


CTEST2(vdraw_integration, test_vdraw_point) {
    vdraw_set_bg_colour(&data->vdraw, 161, 15, 188);
    vdraw_set_fg_colour(&data->vdraw, 82, 36, 186);
    vdraw_clear_screen(&data->vdraw);
    vdraw_flip_screen(&data->vdraw);
    vdraw_point(&data->vdraw, 100, 100);
    const SDL_Rect pixelRect = { .x = 100, .y = 100, .w = 1, .h = 1 };
    uint8_t pixels[3];
    ASSERT_EQUAL(0, SDL_RenderReadPixels(data->vdraw.renderer, &pixelRect, SDL_PIXELFORMAT_BGR888, pixels, 1));
    ASSERT_EQUAL(82, pixels[0]);
    ASSERT_EQUAL(36, pixels[1]);
    ASSERT_EQUAL(186, pixels[2]);
}


CTEST2(vdraw_integration, test_vdraw_line) {
    vdraw_set_bg_colour(&data->vdraw, 159, 11, 173);
    vdraw_set_fg_colour(&data->vdraw, 85, 47, 216);
    vdraw_clear_screen(&data->vdraw);
    vdraw_flip_screen(&data->vdraw);
    vdraw_line(&data->vdraw, 0, 100, 200, 100);
    const SDL_Rect pixelRect = { .x = 100, .y = 100, .w = 1, .h = 1 };
    uint8_t pixels[3];
    ASSERT_EQUAL(0, SDL_RenderReadPixels(data->vdraw.renderer, &pixelRect, SDL_PIXELFORMAT_BGR888, pixels, 1));
    ASSERT_EQUAL(85, pixels[0]);
    ASSERT_EQUAL(47, pixels[1]);
    ASSERT_EQUAL(216, pixels[2]);
}


CTEST2(vdraw_integration, test_vdraw_flip_screen) {
    vdraw_set_bg_colour(&data->vdraw, 59, 112, 243);
    vdraw_clear_screen(&data->vdraw);
    vdraw_flip_screen(&data->vdraw);
    const SDL_Rect pixelRect = { .x = 100, .y = 100, .w = 1, .h = 1 };
    uint8_t pixels[3];
    ASSERT_EQUAL(0, SDL_RenderReadPixels(data->vdraw.renderer, &pixelRect, SDL_PIXELFORMAT_BGR888, pixels, 1));
    ASSERT_EQUAL(59, pixels[0]);
    ASSERT_EQUAL(112, pixels[1]);
    ASSERT_EQUAL(243, pixels[2]);
}



//-----------------------------------------------------------------------------
// Main Application Entry Point.
//-----------------------------------------------------------------------------

// Function main() implementation.
CTESTX_MAIN


