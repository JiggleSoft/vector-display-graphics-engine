//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) Primitive Draw Funcs.
// Filename:     vdraw.c
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-03-27 14:56
// Version:      1.0.0-alpha-4
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

#include "vdraw.h"



//-----------------------------------------------------------------------------
// Primitive Drawing Utility Functions.
//-----------------------------------------------------------------------------

// Order line to always draw to the right and then down.
void vdraw_order_line(const VmathNumber x1a, const VmathNumber y1a,
                      const VmathNumber x2a, const VmathNumber y2a,
                      VmathNumber * x1b, VmathNumber * y1b,
                      VmathNumber * x2b, VmathNumber * y2b)
{
    if (x1a < x2a) {
        *x1b = x1a;
        *y1b = y1a;
        *x2b = x2a;
        *y2b = y2a;
    } else if (x1a > x2a) {
        *x1b = x2a;
        *y1b = y2a;
        *x2b = x1a;
        *y2b = y1a;
    } else {
        *x1b = x1a;
        *x2b = x2a;
        if (y1a < y2a) {
            *y1b = y1a;
            *y2b = y2a;
        } else {
            *y1b = y2a;
            *y2b = y1a;
        }
    }
}



//-----------------------------------------------------------------------------
// Primitive Drawing Life-cycle Functions.
//-----------------------------------------------------------------------------

// Initialise the drawing context with the SDL renderer.
bool vdraw_init(VdrawContext * vdraw, SDL_Renderer * sdl_renderer)
{
    assert (vdraw != NULL);
    assert (sdl_renderer != NULL);
    // Clear the context.
    memset(vdraw, 0, sizeof(struct VdrawContext));
    // Store the renderer.
    vdraw->renderer = sdl_renderer;
    // Get renderer pixel width and height.
    if (SDL_GetRendererOutputSize(vdraw->renderer,
                                  &vdraw->width,
                                  &vdraw->height) != 0) {
        SDL_Log("vdraw_init: SDL_GetRendererOutputSize failed: %s", SDL_GetError());
        vdraw_done(vdraw);
        return false;
    }
    // Initialise state with defaults.
    vdraw->background_colour.red = 0;
    vdraw->background_colour.green = 0;
    vdraw->background_colour.blue = 0;
    vdraw->foreground_colour.red = 255;
    vdraw->foreground_colour.green = 255;
    vdraw->foreground_colour.blue = 255;
    vdraw->pen_width = VMATHNUMBER_C( 1.0 );
    vdraw->foreground_colour_requested.red = 255;
    vdraw->foreground_colour_requested.green = 255;
    vdraw->foreground_colour_requested.blue = 255;
    vdraw->foreground_colour_intensity = VMATHNUMBER_C(1.0);
    vdraw->foreground_colour_fade_val = VMATHNUMBER_C(1.0);
    vdraw->foreground_colour_fade_min.red = 0;
    vdraw->foreground_colour_fade_min.green = 0;
    vdraw->foreground_colour_fade_min.blue = 0;
    vdraw->foreground_colour_fade_max.red = 255;
    vdraw->foreground_colour_fade_max.green = 255;
    vdraw->foreground_colour_fade_max.blue = 255;
    vdraw->foreground_intensity_wave_size = VMATHNUMBER_C(0.2);
    vdraw->foreground_intensity_wave_mbr_angle = VMATHNUMBER_C( 0.0);
    vdraw->foreground_intensity_wave_mbr_speed = VMATHNUMBER_C(16.0);
    return true;
}


// Clean-up the drawing context.
void vdraw_done(VdrawContext * vdraw)
{
    assert (vdraw != NULL);
    vdraw->renderer = NULL;
}



//-----------------------------------------------------------------------------
// Primitive Drawing State Functions.
//-----------------------------------------------------------------------------

// Set the single background colour used when clearing and drawing to the screen.
void vdraw_set_bg_colour(VdrawContext * vdraw,
                         const uint8_t red,
                         const uint8_t green,
                         const uint8_t blue)
{
    assert (vdraw != NULL);
    vdraw->background_colour.red = red;
    vdraw->background_colour.green = green;
    vdraw->background_colour.blue = blue;
}


// Set the single foreground colour used when drawing to the screen.
void vdraw_set_fg_colour(VdrawContext * vdraw,
                         const uint8_t red,
                         const uint8_t green,
                         const uint8_t blue)
{
    assert (vdraw != NULL);
    vdraw->foreground_colour.red = red;
    vdraw->foreground_colour.green = green;
    vdraw->foreground_colour.blue = blue;
}


// Set the pen width.
void vdraw_set_pen_width(VdrawContext * vdraw,
                         const VmathNumber pen_width)
{
    assert (vdraw != NULL);
    vdraw->pen_width = pen_width;
}


// Set the requested foreground colour.
void vdraw_set_fg_colour_requested(VdrawContext * vdraw,
                                   const uint8_t red,
                                   const uint8_t green,
                                   const uint8_t blue)
{
    assert (vdraw != NULL);
    vdraw->foreground_colour_requested.red = red;
    vdraw->foreground_colour_requested.green = green;
    vdraw->foreground_colour_requested.blue = blue;
}


// Set the foreground colour intensity.
void vdraw_set_fg_colour_intensity(VdrawContext * vdraw,
                                   const VmathNumber intensity)
{
    assert (vdraw != NULL);
    vdraw->foreground_colour_intensity = intensity;
}


// Update the foreground colour with the requested colour and intensity.
void vdraw_upd_fg_colour_from_requested_and_intensity(VdrawContext * vdraw)
{
    assert (vdraw != NULL);
    vdraw->foreground_colour.red = vdraw->foreground_colour_requested.red * vdraw->foreground_colour_intensity;
    vdraw->foreground_colour.green = vdraw->foreground_colour_requested.green * vdraw->foreground_colour_intensity;
    vdraw->foreground_colour.blue = vdraw->foreground_colour_requested.blue * vdraw->foreground_colour_intensity;
}


// Set foreground colour fade minimum RGB values.
void vdraw_set_fg_colour_fade_min(VdrawContext * vdraw,
                                  const uint8_t red,
                                  const uint8_t green,
                                  const uint8_t blue)
{
    assert (vdraw != NULL);
    vdraw->foreground_colour_fade_min.red = red;
    vdraw->foreground_colour_fade_min.green = green;
    vdraw->foreground_colour_fade_min.blue = blue;
}


// Set foreground colour fade maximum RGB values.
void vdraw_set_fg_colour_fade_max(VdrawContext * vdraw,
                                  const uint8_t red,
                                  const uint8_t green,
                                  const uint8_t blue)
{
    assert (vdraw != NULL);
    vdraw->foreground_colour_fade_max.red = red;
    vdraw->foreground_colour_fade_max.green = green;
    vdraw->foreground_colour_fade_max.blue = blue;
}


// Set foreground colour fade value (0.0 = fade_min, 1.0 = fade_max).
void vdraw_set_fg_colour_fade_val(VdrawContext * vdraw,
                                  const VmathNumber fade_value)
{
    assert (vdraw != NULL);
    if (fade_value < VMATHNUMBER_C(0.0)) {
        vdraw->foreground_colour_fade_val = VMATHNUMBER_C(0.0);
    } else if (fade_value > VMATHNUMBER_C(1.0)) {
        vdraw->foreground_colour_fade_val = VMATHNUMBER_C(1.0);
    } else {
        vdraw->foreground_colour_fade_val = fade_value;
    }
}


// Update the requested foreground colour from the fade values.
void vdraw_upd_fg_colour_requested_from_fade(VdrawContext * vdraw)
{
    assert (vdraw != NULL);
    vdraw->foreground_colour_requested.red =
            ((vdraw->foreground_colour_fade_max.red - vdraw->foreground_colour_fade_max.red)
            * vdraw->foreground_colour_fade_val) + vdraw->foreground_colour_fade_max.red;
    vdraw->foreground_colour_requested.green =
            ((vdraw->foreground_colour_fade_max.green - vdraw->foreground_colour_fade_max.green)
            * vdraw->foreground_colour_fade_val) + vdraw->foreground_colour_fade_max.green;
    vdraw->foreground_colour_requested.blue =
            ((vdraw->foreground_colour_fade_max.blue - vdraw->foreground_colour_fade_max.blue)
            * vdraw->foreground_colour_fade_val) + vdraw->foreground_colour_fade_max.blue;
}


// Set the foreground intensities wave size (0.0 to 1.0).
void vdraw_set_fg_intensity_wave_size(VdrawContext * vdraw,
                                      const VmathNumber wave_size)
{
    assert (vdraw != NULL);
    if (wave_size < VMATHNUMBER_C(0.0)) {
        vdraw->foreground_intensity_wave_size = VMATHNUMBER_C(0.0);
    } else if (wave_size > VMATHNUMBER_C(1.0)) {
        vdraw->foreground_intensity_wave_size = VMATHNUMBER_C(1.0);
    } else {
        vdraw->foreground_intensity_wave_size = wave_size;
    }
}


// Set the foreground intensities wave MBR angle value.
void vdraw_set_fg_intensity_wave_mbr_angle(VdrawContext * vdraw,
                                           const VmathNumber wave_mbr_angle)
{
    assert (vdraw != NULL);
    vdraw->foreground_intensity_wave_mbr_angle = wave_mbr_angle;
}


// Set the foreground intensities wave MBR speed of rotation value.
void vdraw_set_fg_intensity_wave_mbr_speed(VdrawContext * vdraw,
                                           const VmathNumber wave_mbr_speed)
{
    assert (vdraw != NULL);
    vdraw->foreground_intensity_wave_mbr_speed = wave_mbr_speed;
}


// Update wave rotation value by the current speed of rotation.
void vdraw_upd_fg_intensity_wave_mbr_angle(VdrawContext * vdraw)
{
    assert (vdraw != NULL);
    vdraw->foreground_intensity_wave_mbr_angle +=
            vdraw->foreground_intensity_wave_mbr_speed;
}


// Update the foreground colour intensity from the wave values.
void vdraw_update_fg_colour_intensity_from_wave(VdrawContext * vdraw)
{
    assert (vdraw != NULL);
    vdraw->foreground_colour_intensity = -1+(1.0 - (vdraw->foreground_intensity_wave_size/2)) + (vmath_mbr_cos(vdraw->foreground_intensity_wave_mbr_angle) * vdraw->foreground_intensity_wave_size) + (1.0 - (vdraw->foreground_intensity_wave_size*2));
    //FIXME: !!!!!!!!!!!
}



//-----------------------------------------------------------------------------
// Primitive Drawing Rendering Functions.
//-----------------------------------------------------------------------------

// Clear the screen with the current background colour.
bool vdraw_clear_screen(const VdrawContext * context)
{
    SDL_SetRenderDrawColor(context->renderer,
                           context->background_colour.red,
                           context->background_colour.green,
                           context->background_colour.blue,
                           SDL_ALPHA_OPAQUE);
    return !SDL_RenderClear(context->renderer);
}


// Draw a point with the foreground colour.
void vdraw_point(const VdrawContext * vdraw,
                 const VmathNumber x,
                 const VmathNumber y)
{
    SDL_SetRenderDrawColor(vdraw->renderer,
                           vdraw->foreground_colour.red,
                           vdraw->foreground_colour.green,
                           vdraw->foreground_colour.blue,
                           SDL_ALPHA_OPAQUE);
    const VmathNumber pen_width = vdraw->pen_width;
    if (pen_width != VMATHNUMBER_C(1.0)) {
        SDL_Rect rect = { .x = x - (pen_width/2), .y = y - (pen_width/2), pen_width, pen_width};
        SDL_RenderFillRect(vdraw->renderer, &rect);
    } else {
        SDL_RenderDrawPoint(vdraw->renderer, x, y);
    }
}


// Draw a line with the current foreground colour.
void vdraw_line(const VdrawContext * vdraw,
                const VmathNumber x1, const VmathNumber y1,
                const VmathNumber x2, const VmathNumber y2) {
    // Order line to always draw to the right and then down.
    VmathNumber x1b, y1b, x2b, y2b;
    vdraw_order_line(x1, y1, x2, y2, &x1b, &y1b, &x2b, &y2b);
    x1b = x1;
    y1b = y1;
    x2b = x2;
    y2b = y2;
    SDL_SetRenderDrawColor(vdraw->renderer,
                           vdraw->foreground_colour.red,
                           vdraw->foreground_colour.green,
                           vdraw->foreground_colour.blue,
                           SDL_ALPHA_OPAQUE);
    const VmathNumber pen_width = vdraw->pen_width;
    if (pen_width == VMATHNUMBER_C(1.0)) {
        SDL_RenderDrawLine(vdraw->renderer, x1b, y1b, x2b, y2b);
    } else {
    //FIXME: !!!! pen_width
        SDL_RenderDrawLine(vdraw->renderer, x1b-1, y1b-1, x2b-1, y2b-1);
        SDL_RenderDrawLine(vdraw->renderer, x1b, y1b, x2b, y2b);
        SDL_RenderDrawLine(vdraw->renderer, x1b+1, y1b+1, x2b+1, y2b+1);
    }
}


// Render all screen drawing since the last call to vdraw_flip().
void vdraw_flip_screen(VdrawContext * vdraw)
{
    SDL_RenderPresent(vdraw->renderer);
}


