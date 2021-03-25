//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) Primitive Draw Funcs.
// Filename:     vdraw.h
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-03-25 21:04
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
    // Current background and foreground colours and foreground intensity.
    VdrawRGB background_colour;
    VdrawRGB foreground_colour;
    VmathNumber foreground_intensity;
    // Enablement, min and max colour bounds for the foreground intensity.
    bool foreground_colour_min_max_enable; // Enable specific min and max intensity range else 0 - 255.
    VdrawRGB foreground_colour_min;
    VdrawRGB foreground_colour_max;
    // Vector display intensity shimmer wave enablement, size, mbr angle and speed;
    bool foreground_intensity_wave_enable; // Automatically update intensity on each frame.
    VmathNumber foreground_intensity_wave_size;
    VmathNumber foreground_intensity_wave_mbr_angle;
    VmathNumber foreground_intensity_wave_mbr_speed;
    // The width of the pen used to draw on the foreground.
    VmathNumber pen_width;
} VdrawContext;



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

// Set the background colour to use when clearing or drawing to the screen.
void vdraw_set_bg_colour(VdrawContext * vdraw,
                         const uint8_t red,
                         const uint8_t green,
                         const uint8_t blue);

// Set the foreground colour to use when drawing to the screen.
void vdraw_set_fg_colour(VdrawContext * vdraw,
                         const uint8_t red,
                         const uint8_t green,
                         const uint8_t blue);

// Update the foreground colour with the current intensity and min/max range.
void vdraw_upd_fg_colour(struct VdrawContext * vdraw);

// Set the foreground intensity to use when drawing to the screen.
void vdraw_set_fg_intensity(VdrawContext * vdraw,
                            const VmathNumber intensity);

// Update the foreground intensity wave setting the foreground intensity.
void vdraw_upd_fg_intensity_wave(struct VdrawContext * vdraw);

// Set the foreground colour min and max enablement.
void vdraw_set_fg_colour_min_max_enable(VdrawContext * vdraw,
                                        const bool enable);

// Set the max foreground colour and the foreground and min foreground colors given the intensity range.
void vdraw_set_fg_colour_min_max_range(VdrawContext * vdraw,
                                       const uint8_t red,
                                       const uint8_t green,
                                       const uint8_t blue,
                                       const VmathNumber intensity_size);

// Set the minimum foreground colour.
void vdraw_set_fg_colour_min(VdrawContext * vdraw,
                             const uint8_t red,
                             const uint8_t green,
                             const uint8_t blue);

// Set the max foreground colour.
void vdraw_set_fg_colour_max(VdrawContext * vdraw,
                             const uint8_t red,
                             const uint8_t green,
                             const uint8_t blue);

// Set the foreground intensity wave efeect enablement.
void vdraw_set_fg_intensity_wave_enable(VdrawContext * vdraw,
                                        const bool enable);

// Set the foreground intensity wave effect configuration values.
void vdraw_set_fg_intensity_wave_values(VdrawContext * vdraw,
                                        const VmathNumber size,
                                        const VmathNumber mbr_angle,
                                        const VmathNumber mbr_speed);

// Set the pen width.
void vdraw_set_pen_width(VdrawContext * vdraw,
                         const VmathNumber pen_width);



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
void vdraw_flip(const VdrawContext * vdraw); // Calls vdraw_upd_fg_intensity_wave() if enabled. Note does not set current colour.



#endif /* __VDRAW__H__ */


