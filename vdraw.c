//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge) Primitive Draw Functions.
// Filename:     vdraw.c
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-02-27 11:06
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


#include "vdraw.h"


//-----------------------------------------------------------------------------
// Primitive Drawing Life-cycle Functions.
//-----------------------------------------------------------------------------

// Initialise the drawing context with the SDL renderer.
void vdraw_init(VdrawContext * context, SDL_Renderer * sdl_renderer)
{
    memset(context, 0, sizeof(struct VdrawContext));
    context->sdl_renderer = sdl_renderer;
    context->foreground_colour_min_max_enable = 0;
    context->foreground_colour.red = 255;
    context->foreground_colour.green = 255;
    context->foreground_colour.blue = 255;
    context->foreground_colour_max.red = 255;
    context->foreground_colour_max.green = 255;
    context->foreground_colour_max.blue = 255;
    context->foreground_intensity_wave_mbr_size = VMATHNUMBER_C( 20.0 );
    context->foreground_intensity_wave_mbr_speed = VMATHNUMBER_C( 0.2 );
    context->pen_width = VMATHNUMBER_C( 1.0 );
}


// Clean-up the drawing context.
void vdraw_done(VdrawContext * context)
{}



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
void vdraw_set_foreground_colour_min_max_enable(VdrawContext * context, const _Bool enable)
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
void vdraw_set_foreground_intensity_wave_enable(VdrawContext * context, const _Bool enable)
{
    context->foreground_intensity_wave_enable = enable;
}


// Set the foreground intensity wave effect configuration values.
void vdraw_set_foreground_intensity_wave_size_pos_speed(VdrawContext * context,
                                                        const VmathNumber size,
                                                        const VmathNumber pos,
                                                        const VmathNumber speed)
{
    context->foreground_intensity_wave_mbr_size = size;
    context->foreground_intensity_wave_mbr_pos = pos;
    context->foreground_intensity_wave_mbr_speed = speed;
}



// Set the pen width.
void vdraw_set_pen_width(VdrawContext * context, VmathNumber pen_width)
{
    context->pen_width = pen_width;
}


// Clear the screen with the current background colour.
void vdraw_clear_screen(const VdrawContext * context)
{
    SDL_SetRenderDrawColor(context->sdl_renderer,
                           context->background_colour.red,
                           context->background_colour.green,
                           context->background_colour.blue,
                           SDL_ALPHA_OPAQUE);
    SDL_RenderClear(context->sdl_renderer);
}


static void cdraw_set_render_draw_colour_by_intensity(const struct VdrawContext * context, VmathNumber intensity) {
    if (intensity == VMATHNUMBER_C(1.0)) {
        SDL_SetRenderDrawColor(context->sdl_renderer,
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

        SDL_SetRenderDrawColor(context->sdl_renderer, red, green, blue, SDL_ALPHA_OPAQUE);
    }
}


// Draw a point with the foreground colour.
void vdraw_point(const VdrawContext * context,
                 const VmathNumber x, const VmathNumber y)
{
    SDL_SetRenderDrawColor(context->sdl_renderer,
                           context->foreground_colour.red,
                           context->foreground_colour.green,
                           context->foreground_colour.blue,
                           SDL_ALPHA_OPAQUE);
    //FIXME: context->pen_width, context->pen_width);
    SDL_RenderDrawPoint(context->sdl_renderer, x, y);
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
    SDL_SetRenderDrawColor(context->sdl_renderer,
                           context->foreground_colour.red,
                           context->foreground_colour.green,
                           context->foreground_colour.blue,
                           SDL_ALPHA_OPAQUE);
    //FIXME: context->pen_width, context->pen_width);
    SDL_RenderDrawLine(context->sdl_renderer, x1, y1, x2, y2);
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
    SDL_RenderDrawLine(context->sdl_renderer, x1, y1, x2, y2);
}


// Render all screen drawing since the last call to vdraw_flip().
void vdraw_flip(const VdrawContext * context)
{
    SDL_RenderPresent(context->sdl_renderer);
}


