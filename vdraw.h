//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) Primitive Draw Functions.
// Filename:     vdraw.h
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-02-28 16:20
// Version:      0.0.2
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
    SDL_Renderer * sdl_renderer;
    // Current background and foreground colours.
    VdrawRGB background_colour;
    VdrawRGB foreground_colour;
    // Enablement, min and max colour bounds for the foreground intensity.
    _Bool foreground_colour_min_max_enable;
    VdrawRGB foreground_colour_min;
    VdrawRGB foreground_colour_max;
    // Vector display intensity shimmer wave enablement, size, position, and speed;
    _Bool foreground_intensity_wave_enable;
    VmathNumber foreground_intensity_wave_mbr_size;
    VmathNumber foreground_intensity_wave_mbr_pos;
    VmathNumber foreground_intensity_wave_mbr_speed;
    // The width of the pen used to draw on the foreground.
    VmathNumber pen_width;
} VdrawContext;



//-----------------------------------------------------------------------------
// Primitive Drawing Life-cycle Functions.
//-----------------------------------------------------------------------------

// Initialise the drawing context with the SDL renderer.
extern void vdraw_init(VdrawContext * context, SDL_Renderer * sdl_renderer);


// Clean-up the drawing context.
extern void vdraw_done(VdrawContext * context);



//-----------------------------------------------------------------------------
// Primitive Drawing State Functions.
//-----------------------------------------------------------------------------

// Set the single background colour used when clearing and drawing to the screen.
extern void vdraw_set_background_colour(VdrawContext * context,
                                        const uint8_t red, const uint8_t green, const uint8_t blue);

// Set the single foreground colour used when drawing to the screen.
extern void vdraw_set_foreground_colour(VdrawContext * context,
                                        const uint8_t red, const uint8_t green, const uint8_t blue);

// Set the foreground colour min and max enablement.
extern void vdraw_set_foreground_colour_min_max_enable(VdrawContext * context, const _Bool enable);

// Set the max foreground colour and the foreground and min foreground colors given the intensity range.
extern void vdraw_set_foreground_colour_min_max_range(VdrawContext * context,
                                                      const uint8_t red, const uint8_t green, const uint8_t blue,
                                                      const VmathNumber intensity);

// Set the minimum foreground colour.
extern void vdraw_set_foreground_colour_min(VdrawContext * context,
                                            const uint8_t red, const uint8_t green, const uint8_t blue);

// Set the max foreground colour.
extern void vdraw_set_foreground_colour_max(VdrawContext * context,
                                            const uint8_t red, const uint8_t green, const uint8_t blue);

// Set the foreground intensity wave efeect enablement.
extern void vdraw_set_foreground_intensity_wave_enable(VdrawContext * context, const _Bool enable);

// Set the foreground intensity wave effect configuration values.
extern void vdraw_set_foreground_intensity_wave_size_pos_speed(VdrawContext * context,
                                                               const VmathNumber foreground_intensity_wave_mbr_size,
                                                               const VmathNumber foreground_intensity_wave_mbr_pos,
                                                               const VmathNumber foreground_intensity_wave_mbr_speed);

// Set the pen width.
extern void vdraw_set_pen_width(VdrawContext * context, VmathNumber pen_width);



//-----------------------------------------------------------------------------
// Primitive Drawing Rendering Functions.
//-----------------------------------------------------------------------------

// Clear the screen with the current background colour.
extern void vdraw_clear_screen(const VdrawContext * context);

// Draw a point with the foreground colour.
extern void vdraw_point(const VdrawContext * context,
                        const VmathNumber x, const VmathNumber y);

// Draw a point with the given intensity.
// Intensity enabled: 0.0 = foreground_min, 1.0 = foreground_nom, 2.0 foreground_max.
// Intensity disabled: 0.0 = background_colour, 0.5 = half way between background and foreground colour, 1.0 = foreground_colour.
extern void vdraw_point_intensity(const VdrawContext * context,
                                  const VmathNumber x, const VmathNumber y, const VmathNumber intensity);

// Draw a line with the foreground colour.
extern void vdraw_line(const VdrawContext * context,
                       const VmathNumber x1, const VmathNumber y1,
                       const VmathNumber x2, const VmathNumber y2);

// Draw a line with the given intensity.
// Intensity enabled: 0.0 = foreground_min, 1.0 = foreground_nom, 2.0 foreground_max.
// Intensity disabled: 0.0 = background_colour, 0.5 = half way between background and foreground colour, 1.0 = foreground_colour.
extern void vdraw_line_intensity(const VdrawContext * context,
                                 const VmathNumber x1, const VmathNumber y1,
                                 const VmathNumber x2, const VmathNumber y2,
                                 const VmathNumber intensity);

// Render all screen drawing since the last call to vdraw_flip().
extern void vdraw_flip(const VdrawContext * context);



#endif /* __VDRAW__H__ */


