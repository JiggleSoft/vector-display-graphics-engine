//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge).
// Filename:     vedge-debug.h
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-03-20 18:21
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

#ifndef __VEDGE_DEBUG__H__
#define __VEDGE_DEBUG__H__



#include <SDL.h>

#include "vmath.h"
#include "vdraw.h"
#include "vedge.h"


//-----------------------------------------------------------------------------
// Engine Version and Title Constants.
//-----------------------------------------------------------------------------


static char * indent_strings[] = { "", " ", "  ", "   ", "    ", "     ", "      ",
                                   "       ", "        ", "         ", "          " };


char * indent_string(const int indent)
{
    return indent_strings[indent];
}


void vedge_debug_print_init_config(const char * prefix, const VedgeInitConfig * config, const int indent)
{
    printf("%s%s: {\n", indent_string(indent), prefix);
    printf("%sinit_subsystems = %d\n", indent_string(indent+2), config->init_subsystems);
    printf("%sopen_subsystems = %d\n", indent_string(indent+2), config->open_subsystems);
    printf("%sdisplay_index = %d\n", indent_string(indent+2), config->display_index);
    printf("%sdisplay_format = %d\n", indent_string(indent+2), config->display_format);
    printf("%sdisplay_width = %d\n", indent_string(indent+2), config->display_width);
    printf("%sdisplay_height = %d\n", indent_string(indent+2), config->display_height);
    printf("%sdisplay_refresh_rate = %d\n", indent_string(indent+2), config->display_refresh_rate);
    printf("%swindows_title = %s\n", indent_string(indent+2), config->windows_title);
    printf("%swindow_x_pos = %d\n", indent_string(indent+2), config->window_x_pos);
    printf("%swindow_y_pos = %d\n", indent_string(indent+2), config->window_y_pos);
    printf("%swindow_width = %d\n", indent_string(indent+2), config->window_width);
    printf("%swindow_height = %d\n", indent_string(indent+2), config->window_height);
    printf("%swindow_flags = %d\n", indent_string(indent+2), config->window_flags);
    printf("%s}\n", indent_string(indent));
}


void vedge_debug_print_init_state(const char * prefix, const VedgeInitState * state, const int indent)
{
    printf("%s%s: {\n", indent_string(indent), prefix);
    printf("%sinit_subsystems = %d\n", indent_string(indent+2), state->init_subsystems);
    printf("%svmath_initialised = %d\n", indent_string(indent+2), state->vmath_initialised);
    printf("%svedge_initialised = %d\n", indent_string(indent+2), state->vedge_initialised);
    printf("%s}\n", indent_string(indent));
}


void vedge_debug_print_sdl_display_mode(const char * prefix, const SDL_DisplayMode * mode, const int indent)
{
    printf("%s%s: {\n", indent_string(indent), prefix);
    printf("%sformat = %d\n", indent_string(indent+2), mode->format);
    printf("%sw = %d\n", indent_string(indent+2), mode->w);
    printf("%sh = %d\n", indent_string(indent+2), mode->h);
    printf("%srefresh_rate = %d\n", indent_string(indent+2), mode->refresh_rate);
    printf("%sdriverdata = %p\n", indent_string(indent+2), mode->driverdata);
    printf("%s}\n", indent_string(indent));
}


void vedge_debug_print_open_config(const char * prefix, const VedgeOpenConfig * config, const int indent)
{
    printf("%s%s: {\n", indent_string(indent), prefix);
    printf("%sdisplay_index = %d\n", indent_string(indent+2), config->display_index);
    vedge_debug_print_sdl_display_mode("initial_display_mode", &config->initial_display_mode, indent+2);
    printf("%sdisplay_modes_supported = %d\n", indent_string(indent+2), config->query_display_modes_count);
    printf("%squery_display_mode_index = %d\n", indent_string(indent+2), config->query_display_mode_index);
    vedge_debug_print_sdl_display_mode("query_display_mode_selected", &config->query_display_mode_selected, indent+2);
    vedge_debug_print_sdl_display_mode("request_display_mode", &config->request_display_mode, indent+2);
    vedge_debug_print_sdl_display_mode("nearest_display_mode", &config->nearest_display_mode, indent+2);
    printf("%s}\n", indent_string(indent));
}


void vedge_debug_print_open_state(const char * prefix, const VedgeOpenState * state, const int indent)
{
    printf("%s%s: {\n", indent_string(indent), prefix);
    printf("%ssdl_window = %p\n", indent_string(indent+2), state->sdl_window);
    printf("%ssdl_renderer = %p\n", indent_string(indent+2), state->sdl_renderer);
    vedge_debug_print_sdl_display_mode("opened_display_mode", &state->opened_display_mode, indent+2);
    printf("%sprivate_vdraw_context = %d\n", indent_string(indent+2), state->private_vdraw_context);//fixme print struct
    printf("%svdraw_context = %p\n", indent_string(indent+2), state->vdraw_context);
    printf("%svedge_opened = %d\n", indent_string(indent+2), state->vedge_opened);
    printf("%s}\n", indent_string(indent));
}


void vedge_debug_print_error_state(const char * prefix, const VedgeErrorState * state, const int indent)
{
    printf("%s%s: {\n", indent_string(indent), prefix);
    printf("%sedge_error_code = %u\n", indent_string(indent+2), state->vedge_error_code);
    printf("%svedge_error_message = %p\n", indent_string(indent+2), state->vedge_error_message);
    printf("%sprivate_vdraw_error_message = %s\n", indent_string(indent+2), state->private_vdraw_error_message);
    printf("%s}\n", indent_string(indent));
}


void vedge_debug_print_vedge(const char * prefix, const VedgeContext * vedge, const int indent)
{
    printf("%s%s: {\n", indent_string(indent), prefix);
    vedge_debug_print_init_config("init_config", &vedge->init_config, 2);
    vedge_debug_print_init_state("init_state", &vedge->init_state, 2);
    vedge_debug_print_open_config("open_config", &vedge->open_config, 2);
    vedge_debug_print_open_state("open_state", &vedge->open_state, 2);
    vedge_debug_print_error_state("error_state", &vedge->error_state, 2);
    printf("%s}\n", indent_string(indent));
}


#endif /* __VEDGE_DEBUG__H__ */


