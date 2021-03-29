//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge).
// Filename:     vedge.c
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-01-24 19:27
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


#include <assert.h>
#include "vedge.h"



//-----------------------------------------------------------------------------
// Temporary Debugging.
//-----------------------------------------------------------------------------

void debug_display_mode(char * title, SDL_DisplayMode * display_mode) {
    printf("%s: format=%d, w=%d, h=%d, refresh_rate=%d, driver_data=%p\n", title, display_mode->format, display_mode->w, display_mode->h, display_mode->refresh_rate, display_mode->driverdata);
}


//-----------------------------------------------------------------------------
// Utilities.
//-----------------------------------------------------------------------------

#define countof(n) (sizeof(n)/sizeof(n[0]))


//-----------------------------------------------------------------------------
// Error Message Strings.
//-----------------------------------------------------------------------------

// Error message strings.
const char * vedge_error_messages[] = {
        "No error",
        "Context is NULL",
        "Context is not initialised",
        "General failure"
};


//-----------------------------------------------------------------------------
// Configuration Functions.
//-----------------------------------------------------------------------------

// The default template initialisation config..
const VedgeConfig vedge_config_default = {
        0
};


// Initialise an init config from defaults (template_init_config == NULL) or
// by a supplied template_init_config.
void vedge_config_template(VedgeConfig * vedge_config,
                           const VedgeConfig * template_vedge_config)
{
    assert (vedge_config != NULL);
    memcpy(vedge_config,
           (template_vedge_config == NULL) ? &vedge_config_default : template_vedge_config,
           sizeof(VedgeConfig));
}


// .
static void vedge_init_config_sdl(VedgeConfig * vedge_config,
                           SDL_Window * sdl_window,
                           SDL_Renderer * sdl_renderer)
{
    assert (vedge_config != NULL);
    assert (sdl_window != NULL);
    assert (sdl_renderer != NULL);
    vedge_config_template(vedge_config, NULL);
    vedge_config->sdl_window = sdl_window = sdl_window;
    vedge_config->sdl_renderer = sdl_renderer;
}


// .
void vedge_config_sdl2boot(VedgeConfig * vedge_config,
                           const Sdl2BootContext * sdl2boot)
{
    assert (vedge_config != NULL);
    assert (sdl2boot != NULL);
    vedge_init_config_sdl(vedge_config, sdl2boot->state.window, sdl2boot->state.renderer);
}


//-----------------------------------------------------------------------------
// Lifecycle Management Functions.
//-----------------------------------------------------------------------------

// Initialise the engine and the initial sub-systems.
bool vedge_init(VedgeContext * vedge, const VedgeConfig * vedge_config)
{
    assert (vedge != NULL);
    assert (vedge_config != NULL);
    // Initialise the context.
    memset(vedge, 0, sizeof(VedgeContext));
    // Copy the configuration.
    memcpy(&vedge->config, vedge_config, sizeof(VedgeConfig));
    // Initialise vmath.
    vmath_init();
    vedge->state.vmath_initialised = 1;
    // Set up initial open config.
    vdraw_init(&vedge->state.private_vdraw_context, vedge->config.sdl_renderer);//FIXME: bring in line with other code.
    vedge->state.vdraw_context = &vedge->state.private_vdraw_context;
//FIXME: move to vdraw...
    // Get width and heigt
//    SDL_GetRendererOutputSize(vedge->state.vdraw_context->sdl_renderer, &vedge->state.width, &vedge->state.height);
    //FIXME: above.
    // vEdge is initialised successfully.
    vedge->state.initialised = true;
    return true;
}


// .
void vedge_done(VedgeContext * vedge)
{
    assert (vedge != NULL);
    // Close the vmath.
    if (vedge->state.vmath_initialised) {
        vmath_done();
        vedge->state.vmath_initialised = 0;
    }
//    // Shutdown SDL and its sub-systems.
//    if (vedge->init_state.init_subsystems) {
//        SDL_Quit();
//        vedge->init_state.init_subsystems = 0;
//    }
//    // vEdge is no longer initialised.
//    vedge->init_state.vedge_initialised = 0;
}


//-----------------------------------------------------------------------------
// Vector Display Graphics Engine Main Loop and Event Processing.
//-----------------------------------------------------------------------------

#define VEDGE_VDRAW(vedge) vedge->state.vdraw_context

// .
int vedge_run(VedgeContext * vedge)
{
    int x1 = 44;
    int y1 = 393;
    int x2 = 123;
    int y2 = 13;
    int x1d = 5;
    int y1d = 6;
    int x2d = -4;
    int y2d = 8;

    int x = 0;
    SDL_Event event;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            //call general event handler vedge_event(&event);
            //call specific event handlers
            //User requests quit
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }


printf("%d %d %d   %d %d %d   %f   %f %f %f\n",
       VEDGE_VDRAW(vedge)->foreground_colour.red,
       VEDGE_VDRAW(vedge)->foreground_colour.green,
       VEDGE_VDRAW(vedge)->foreground_colour.blue,

       VEDGE_VDRAW(vedge)->foreground_colour_requested.red,
       VEDGE_VDRAW(vedge)->foreground_colour_requested.green,
       VEDGE_VDRAW(vedge)->foreground_colour_requested.blue,

       VEDGE_VDRAW(vedge)->foreground_colour_intensity,

       VEDGE_VDRAW(vedge)->foreground_intensity_wave_size,
       VEDGE_VDRAW(vedge)->foreground_intensity_wave_mbr_angle,
       VEDGE_VDRAW(vedge)->foreground_intensity_wave_mbr_speed


);

vedge->state.vdraw_context->foreground_intensity_wave_mbr_speed = 128;
       /// vdraw_clear_screen(VEDGE_VDRAW(vedge));
vdraw_set_pen_width(VEDGE_VDRAW(vedge), 2.0);

        vdraw_set_fg_colour(VEDGE_VDRAW(vedge), 255, 255, 255);


//        vdraw_set_fg_colour_requested(VEDGE_VDRAW(vedge), 255, 0, 255);
//        vdraw_set_fg_colour_intensity(VEDGE_VDRAW(vedge), x/64.0);
//        vdraw_upd_fg_colour_from_requested_and_intensity(VEDGE_VDRAW(vedge));

vdraw_update_fg_colour_intensity_from_wave(VEDGE_VDRAW(vedge));
VEDGE_VDRAW(vedge)->foreground_intensity_wave_mbr_angle += VEDGE_VDRAW(vedge)->foreground_intensity_wave_mbr_speed;

vdraw_upd_fg_colour_from_requested_and_intensity(VEDGE_VDRAW(vedge));

        vdraw_line(VEDGE_VDRAW(vedge), x1, y1, x2 , y2);
        x1 = x1 + x1d;
        y1 = y1 + y1d;
        x2 = x2 + x2d;
        y2 = y2 + y2d;
        if (x1 < 5 || x1 > (VEDGE_VDRAW(vedge)->width-5)) x1d = -x1d;
        if (y1 < 5 || y1 > (VEDGE_VDRAW(vedge)->height-5)) y1d = -y1d;
        if (x2 < 5 || x2 > (VEDGE_VDRAW(vedge)->width-5)) x2d = -x2d;
        if (y2 < 5 || y2 > (VEDGE_VDRAW(vedge)->height-5)) y2d = -y2d;



//        for (int a = 0; a < 25; a++) {
//            vdraw_set_fg_colour(VEDGE_VDRAW(vedge), 255, 255, 255);
//            vdraw_line(VEDGE_VDRAW(vedge), x % 2048, 200, 300, 800);
//
//            vdraw_set_fg_colour(VEDGE_VDRAW(vedge), 255, 0, 0);
//            vdraw_line(VEDGE_VDRAW(vedge), x % 20458, 200, x % 1024, 800);
//
//            vdraw_set_fg_colour(VEDGE_VDRAW(vedge), 0, 255, 0);
//            vdraw_line(VEDGE_VDRAW(vedge), x / 2 % 4096, 200, 300, 800);
//
            x++;
//        }
SDL_Delay(10);
if (x > 2048) {
    x = 0;
    vdraw_clear_screen(VEDGE_VDRAW(vedge));
}
//        vdraw_char(VEDGE_VDRAW(vedge), 'J', 300, 800);
//        vdraw_text(VEDGE_VDRAW(vedge), 300, 800, 10, 200);

//for (int z = 0;  z < 1024;  z+= 16) {
//    vdraw_set_pen_width(VEDGE_VDRAW(vedge), z / 64);
//    vdraw_point(VEDGE_VDRAW(vedge), z+ ((x %1024) * 10), z);
//}
        vdraw_set_pen_width(VEDGE_VDRAW(vedge), 1.0);


        vdraw_flip_screen(VEDGE_VDRAW(vedge));

        //call render loop function
    }
    return 0;
}









//-----------------------------------------------------------------------------
// Engine Management Functions.
//-----------------------------------------------------------------------------

// Open the engine with current configuration..
int vedge_open(VedgeContext * context)
{
    assert (context != NULL);
    //TODO check flag for initialised.
    // Initialise SDL's optional sub-systems.
    // TODO: !!!!!!!!!!!!!!!!!
    // Open the SDL window.
    SDL_DisplayMode current_display_mode;
    SDL_DisplayMode request_display_mode = { .format = 0, .w = 0, .h = 0, .refresh_rate = 0, .driverdata = NULL };
    SDL_DisplayMode nearest_display_mode;
//    SDL_GetCurrentDisplayMode(context->init_config.display_index, &current_display_mode);
//    SDL_GetClosestDisplayMode(context->init_config.display_index, &request_display_mode, &nearest_display_mode);
//    debug_display_mode("current_display_mode", &current_display_mode);
//    debug_display_mode("request_display_mode", &request_display_mode);
//    debug_display_mode("nearest_display_mode", &nearest_display_mode);
//    context->init_state.sdl_window = SDL_CreateWindow(
//            context->init_config.windows_title,
//            context->init_config.window_x_pos,
//            context->init_config.window_y_pos,
//            context->init_config.window_width == 0 ? current_display_mode.w : context->init_config.window_width,
//            context->init_config.window_height == 0 ? current_display_mode.h : context->init_config.window_height,
//            context->init_config.window_flags);
    // Open the SDL renderer.
//    context->init_state.sdl_renderer = SDL_CreateRenderer(context->init_state.sdl_window,
//                                                          context->init_config.display_index,
//                                                          SDL_RENDERER_SOFTWARE);
//    // Initialise vdraw.
//    vdraw_init(&context->init_state.private_vdraw_context, context->init_state.sdl_renderer);
//    context->init_state.vdraw_context = &context->init_state.private_vdraw_context;
    return 0;
}



// Close the engine.
int vedge_close(VedgeContext * context)
{
    assert (context != NULL);
    // Close the vdraw context.
//    if (context->init_state.vdraw_context != NULL) {
//        vdraw_done(context->init_state.vdraw_context);
//        context->init_state.vdraw_context = NULL;
//    }
//    // Close the SDL renderer.
//    if (context->init_state.sdl_renderer) {
//        SDL_DestroyRenderer(context->init_state.sdl_renderer);
//        context->init_state.sdl_renderer = NULL;
//    }
//    // Close the SDL window.
//    if (context->init_state.sdl_window) {
//        SDL_DestroyWindow(context->init_state.sdl_window);
//        context->init_state.sdl_window = NULL;
//    }
    // Close the SDL optional sub-systems.
    // TODO: !!!
    return 0;
}


//-----------------------------------------------------------------------------
// .....
//-----------------------------------------------------------------------------


void vedge_frame_start(VedgeContext * context)
{
    assert (context != NULL);
//    vdraw_clear_screen(context->init_state.vdraw_context);
}


void vedge_frame_finish(VedgeContext * context)
{
    assert (context != NULL);
 //   vdraw_flip(context->init_state.vdraw_context);
}


void vedge_frame_add_game_object(VedgeContext * context, const VedgeGameObject * game_object)
{
    assert (context != NULL);
    assert (game_object != NULL);
    if (game_object->enable) {
        for (int i = 0;  i < game_object->items->length;  i++) {
            switch (game_object->items->game_items[i].type) {
                case POINT:
//FIXME:                     VedgePoint * point = game_object->items->game_items[i].game_item.point;
break;

            }
        }
    }
}



