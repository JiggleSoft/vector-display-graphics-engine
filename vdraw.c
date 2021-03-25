//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) Primitive Draw Funcs.
// Filename:     vdraw.c
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


#include <assert.h>
#include "vdraw.h"



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
    vdraw->foreground_intensity = VMATHNUMBER_C(1.0);
    vdraw->foreground_colour_min_max_enable = false;
    vdraw->foreground_colour_min.red = 0;
    vdraw->foreground_colour_min.green = 0;
    vdraw->foreground_colour_min.blue = 0;
    vdraw->foreground_colour_max.red = 255;
    vdraw->foreground_colour_max.green = 255;
    vdraw->foreground_colour_max.blue = 255;
    vdraw->foreground_intensity_wave_enable = false;
    vdraw->foreground_intensity_wave_size = VMATHNUMBER_C( 20.0 );
    vdraw->foreground_intensity_wave_mbr_angle = VMATHNUMBER_C( 00.0 );
    vdraw->foreground_intensity_wave_mbr_speed = VMATHNUMBER_C( 0.2 );
    vdraw->pen_width = VMATHNUMBER_C( 1.0 );
    return true;
}


// Clean-up the drawing context.
void vdraw_done(VdrawContext * vdraw)
{
    assert (vdraw != NULL);
    vdraw->renderer = NULL;
}



//-----------------------------------------------------------------------------
// Primitive Drawing Functions.
//-----------------------------------------------------------------------------

// Set the single background colour used when clearing and drawing to the screen.
void vdraw_set_background_colour(VdrawContext * context,
                                 const uint8_t red, const uint8_t green, const uint8_t blue)
{
    context->background_colour.red = red;
    context->background_colour.green = green;
    context->background_colour.blue = blue;
}


// Set the single foreground colour used when drawing to the screen.
void vdraw_set_foreground_colour(VdrawContext * context,
                                 const uint8_t red, const uint8_t green, const uint8_t blue)
{
    context->foreground_colour.red = red;
    context->foreground_colour.green = green;
    context->foreground_colour.blue = blue;
}


// Set the foreground colour min and max enablement.
void vdraw_set_foreground_colour_min_max_enable(VdrawContext * context, const bool enable)
{
    context->foreground_colour_min_max_enable = enable;
}


// Set the max foreground colour and the foreground and min foreground colors given the intensity range.
void vdraw_set_foreground_colour_min_max_range(VdrawContext * context,
                                               const uint8_t red, const uint8_t green, const uint8_t blue,
                                               const VmathNumber intensity)
{
    context->foreground_colour_max.red = red;
    context->foreground_colour_max.green = green;
    context->foreground_colour_max.blue = blue;
    context->foreground_colour_max.red = red - (red * intensity);
    context->foreground_colour_max.green = green - (green * intensity);
    context->foreground_colour_max.blue = blue - (blue * intensity);
    context->foreground_colour.red = red - (red * intensity / 2.0f);
    context->foreground_colour.green = green - (green * intensity / 2.0f);
    context->foreground_colour.blue = blue - (blue * intensity / 2.0f);
}


// Set the minimum foreground colour.
void vdraw_set_foreground_colour_min(VdrawContext * context,
                                     const uint8_t red, const uint8_t green, const uint8_t blue)
{
    context->foreground_colour_min.red = red;
    context->foreground_colour_min.green = green;
    context->foreground_colour_min.blue = blue;
}


// Set the max foreground colour.
void vdraw_set_foreground_colour_max(VdrawContext * context,
                                     const uint8_t red, const uint8_t green, const uint8_t blue)
{
    context->foreground_colour_max.red = red;
    context->foreground_colour_max.green = green;
    context->foreground_colour_max.blue = blue;
}


// Set the foreground intensity wave efeect enablement.
void vdraw_set_foreground_intensity_wave_enable(VdrawContext * context, const bool enable)
{
    context->foreground_intensity_wave_enable = enable;
}


// Set the foreground intensity wave effect configuration values.
void vdraw_set_fg_intensity_wave_values(VdrawContext * context,
                                        const VmathNumber size,
                                        const VmathNumber angle,
                                        const VmathNumber speed)
{
    context->foreground_intensity_wave_size = size;
    context->foreground_intensity_wave_mbr_angle = angle;
    context->foreground_intensity_wave_mbr_speed = speed;
}



// Set the pen width.
void vdraw_set_pen_width(VdrawContext * context, VmathNumber pen_width)
{
    context->pen_width = pen_width;
}


// Clear the screen with the current background colour.
bool vdraw_clear_screen(const VdrawContext * context)
{
//    SDL_SetRenderDrawColor(context->renderer,
//                           context->background_colour.red,
//                           context->background_colour.green,
//                           context->background_colour.blue,
//                           SDL_ALPHA_OPAQUE);
    return !SDL_RenderClear(context->renderer);
}


static void cdraw_set_render_draw_colour_by_intensity(const struct VdrawContext * context, VmathNumber intensity) {
    if (intensity == VMATHNUMBER_C(1.0)) {
        SDL_SetRenderDrawColor(context->renderer,
                               context->foreground_colour.red,
                               context->foreground_colour.green,
                               context->foreground_colour.blue,
                               SDL_ALPHA_OPAQUE);
    } else {
        int red, green, blue;
        if (context->foreground_colour_min_max_enable) {
            if (intensity > VMATHNUMBER_C(1.0)) {
                red = (context->foreground_colour_max.red - context->foreground_colour_max.red) *
                      (intensity - VMATHNUMBER_C(1.0) + context->foreground_colour_max.red);
                green = (context->foreground_colour_max.green - context->foreground_colour_max.green) *
                        (intensity - VMATHNUMBER_C(1.0) + context->foreground_colour_max.green);
                blue = (context->foreground_colour_max.blue - context->foreground_colour_max.blue) *
                       (intensity - VMATHNUMBER_C(1.0) + context->foreground_colour_max.blue);
            } else {
                red = (context->foreground_colour_max.red - context->foreground_colour_max.red) *
                      (intensity - VMATHNUMBER_C(1.0) + context->foreground_colour_max.red);
                green = (context->foreground_colour_max.green - context->foreground_colour_max.green) *
                        (intensity - VMATHNUMBER_C(1.0) + context->foreground_colour_max.green);
                blue = (context->foreground_colour_max.blue - context->foreground_colour_max.blue) *
                       (intensity - VMATHNUMBER_C(1.0) + context->foreground_colour_max.blue);
            }
        } else {
            red = (context->foreground_colour.red * intensity);
            green = (context->foreground_colour.green * intensity);
            blue = (context->foreground_colour.blue * intensity);
        }

        SDL_SetRenderDrawColor(context->renderer, red, green, blue, SDL_ALPHA_OPAQUE);
    }
}


// Draw a point with the foreground colour.
void vdraw_point(const VdrawContext * context,
                 const VmathNumber x, const VmathNumber y)
{
    SDL_SetRenderDrawColor(context->renderer,
                           context->foreground_colour.red,
                           context->foreground_colour.green,
                           context->foreground_colour.blue,
                           SDL_ALPHA_OPAQUE);
    //FIXME: context->pen_width, context->pen_width);
    SDL_RenderDrawPoint(context->renderer, x, y);
}


// Draw a point with the given intensity.
// Intensity enabled: 0.0 = foreground_min, 1.0 = foreground_nom, 2.0 foreground_max.
// Intensity disabled: 0.0 = background_colour, 0.5 = half way between background and foreground colour, 1.0 = foreground_colour.
void vdraw_point_intensity(const VdrawContext * context,
                           const VmathNumber x, const VmathNumber y, const VmathNumber intensity)
{
    cdraw_set_render_draw_colour_by_intensity(context, intensity);
    //FIXME: !!!
    vdraw_point(context, x, y);
}


// Draw a line with the foreground colour.
void vdraw_line(const VdrawContext * context,
                const VmathNumber x1, const VmathNumber y1,
                const VmathNumber x2, const VmathNumber y2)
{
    SDL_SetRenderDrawColor(context->renderer,
                           context->foreground_colour.red,
                           context->foreground_colour.green,
                           context->foreground_colour.blue,
                           SDL_ALPHA_OPAQUE);
    //FIXME: context->pen_width, context->pen_width);
    SDL_RenderDrawLine(context->renderer, x1, y1, x2, y2);
}


// Draw a line with the given intensity.
// Intensity enabled: 0.0 = foreground_min, 1.0 = foreground_nom, 2.0 foreground_max.
// Intensity disabled: 0.0 = background_colour, 0.5 = half way between background and foreground colour, 1.0 = foreground_colour.
void vdraw_line_intensity(const VdrawContext * context,
                          const VmathNumber x1, const VmathNumber y1,
                          const VmathNumber x2, const VmathNumber y2,
                          const VmathNumber intensity)
{
    cdraw_set_render_draw_colour_by_intensity(context, intensity);
//FIXME: !!!
    //FIXME: context->pen_width, context->pen_width);
    SDL_RenderDrawLine(context->renderer, x1, y1, x2, y2);
}


// Render all screen drawing since the last call to vdraw_flip().
void vdraw_flip(const VdrawContext * context)
{
    SDL_RenderPresent(context->renderer);
}


