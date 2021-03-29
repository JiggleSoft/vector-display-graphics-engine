//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) Primitive Draw Funcs.
// Filename:     vdraw.h
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

#ifndef __VDRAW__H__
#define __VDRAW__H__


#include <SDL.h>

#include <stdint.h>
#include <stdbool.h>

#include "vmath.h"



//-----------------------------------------------------------------------------
// Primitive Drawing Types.
//-----------------------------------------------------------------------------

// Primitive red, green, and blue type.
typedef struct VdrawRGB {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} VdrawRGB;


// Primitive drawing context (access via API functions only).
typedef struct VdrawContext {
    // The SDL renderer;
    SDL_Renderer * renderer;
    // Renderer pixel width.
    int width;
    // Renderer pixel height.
    int height;
    // Current background and foreground colours used for drawing.
    VdrawRGB background_colour;
    VdrawRGB foreground_colour;
    // The width of the pen used to draw on the foreground.
    VmathNumber pen_width;
    // The foreground colour requested and its intensity value.
    // Used to populate foreground_colour.
    VdrawRGB    foreground_colour_requested;
    VmathNumber foreground_colour_intensity;
    // Colour graduation fading.
    // Used to populate foreground_colour_requested or foreground_colour.
    VdrawRGB    foreground_colour_fade_min;
    VdrawRGB    foreground_colour_fade_max;
    VmathNumber foreground_colour_fade_val;
    // Vector display intensity shimmer wave enablement, size, mbr angle and speed;
    // Used to populate foreground_intensity.
    VmathNumber foreground_intensity_wave_size;
    VmathNumber foreground_intensity_wave_mbr_angle;
    VmathNumber foreground_intensity_wave_mbr_speed;
} VdrawContext;



//-----------------------------------------------------------------------------
// Primitive Drawing Utility Functions.
//-----------------------------------------------------------------------------

// Order line to always draw to the right and then down.
void vdraw_order_line(const VmathNumber x1a, const VmathNumber y1a,
                      const VmathNumber x2a, const VmathNumber y2a,
                      VmathNumber * x1b, VmathNumber * y1b,
                      VmathNumber * x2b, VmathNumber * y2b);



//-----------------------------------------------------------------------------
// Primitive Drawing Life-cycle Functions.
//-----------------------------------------------------------------------------

// Initialise the drawing context with the SDL renderer.
bool vdraw_init(VdrawContext * vdraw, SDL_Renderer * sdl_renderer);


// Clean-up the drawing context.
void vdraw_done(VdrawContext * vdraw);



//-----------------------------------------------------------------------------
// Primitive Drawing State Functions.
//-----------------------------------------------------------------------------

// Set the background colour to use when clearing the screen.
void vdraw_set_bg_colour(VdrawContext * vdraw,
                         const uint8_t red,
                         const uint8_t green,
                         const uint8_t blue);

// Set the foreground colour to use when drawing to the screen.
void vdraw_set_fg_colour(VdrawContext * vdraw,
                         const uint8_t red,
                         const uint8_t green,
                         const uint8_t blue);


// Set the pen width.
void vdraw_set_pen_width(VdrawContext * vdraw,
                         const VmathNumber pen_width);


// Set the requested foreground colour.
void vdraw_set_fg_colour_requested(VdrawContext * vdraw,
                                   const uint8_t red,
                                   const uint8_t green,
                                   const uint8_t blue);

// Set the foreground colour intensity.
void vdraw_set_fg_colour_intensity(VdrawContext * vdraw,
                                   const VmathNumber intensity);

// Update the foreground colour with the requested colour and intensity.
void vdraw_upd_fg_colour_from_requested_and_intensity(VdrawContext * vdraw);


// Set foreground colour fade value (0.0 = fade_min, 1.0 = fade_max).
void vdraw_set_fg_colour_fade_val(VdrawContext * vdraw,
                                  const VmathNumber fade_value);

// Set foreground colour fade minimum RGB values.
void vdraw_set_fg_colour_fade_min(VdrawContext * vdraw,
                                  const uint8_t red,
                                  const uint8_t green,
                                  const uint8_t blue);

// Set foreground colour fade maximum RGB values.
void vdraw_set_fg_colour_fade_max(VdrawContext * vdraw,
                                  const uint8_t red,
                                  const uint8_t green,
                                  const uint8_t blue);

// Update the requested foreground colour from the fade values.
void vdraw_upd_fg_colour_requested_from_fade(VdrawContext * vdraw);


// Set the foreground intensities wave size (0.0 to 1.0).
void vdraw_set_fg_intensity_wave_size(VdrawContext * vdraw,
                                      const VmathNumber wave_size);

// Set the foreground intensities wave MBR angle value.
void vdraw_set_fg_intensity_wave_mbr_angle(VdrawContext * vdraw,
                                           const VmathNumber wave_mbr_angle);

// Set the foreground intensities wave MBR speed of rotation value.
void vdraw_set_fg_intensity_wave_mbr_speed(VdrawContext * vdraw,
                                           const VmathNumber wave_mbr_speed);

// Update wave rotation value by the current speed of rotation.
void vdraw_upd_fg_intensity_wave_mbr_angle(VdrawContext * vdraw);

// Update the foreground colour intensity from the wave values.
void vdraw_update_fg_colour_intensity_from_wave(VdrawContext * vdraw);



//-----------------------------------------------------------------------------
// Primitive Drawing Rendering Functions.
//-----------------------------------------------------------------------------

// Clear the screen with the current background colour.
bool vdraw_clear_screen(const VdrawContext * vdraw);

// Draw a point with the foreground colour.
void vdraw_point(const VdrawContext * vdraw,
                 const VmathNumber x,
                 const VmathNumber y);

// Draw a line with the current foreground colour.
void vdraw_line(const VdrawContext * vdraw,
                const VmathNumber x1, const VmathNumber y1,
                const VmathNumber x2, const VmathNumber y2);

// Render all screen drawing since the last call to vdraw_flip().
void vdraw_flip_screen(VdrawContext * vdraw);



#endif /* __VDRAW__H__ */


