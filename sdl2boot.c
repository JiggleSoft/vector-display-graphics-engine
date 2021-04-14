//=============================================================================
// Title:        SDL2 Boot (Bootstrapping of SDL version 2).
// Filename:     sdl2boot.c
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-04-14 22:28
// Version:      1.0.0-beta-3
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

#include "sdl2boot.h"



//-----------------------------------------------------------------------------
// Configuration Functions.
//-----------------------------------------------------------------------------

// The default template initialisation config.
const Sdl2BootConfig sdl2boot_config_default = {
        .init_subsystems = SDL2BOOT_SDL_INIT,
        .window_title = SDL2BOOT_TITLE,
        .window_flags = SDL2BOOT_SDL_WINDOW_FLAGS,
        .renderer_flags = SDL2BOOT_SDL_RENDERER_FLAGS
};


// Configure of SDL 2 boot from the template, or if NULL the defaults.
void sdl2boot_config_from_template(Sdl2BootConfig * boot_config,
                                   const Sdl2BootConfig * template_boot_config)
{
    assert (boot_config != NULL);
    memcpy(boot_config,
           (template_boot_config == NULL) ? &sdl2boot_config_default : template_boot_config,
           sizeof(Sdl2BootConfig));
}


// Quick configure of SDL 2 boot for primary display and desktop resolution.
void sdl2boot_config_primary_desktop(Sdl2BootConfig * boot_config,
                                     const uint32_t init_subsystems,
                                     const char * window_title,
                                     const uint32_t window_flags,
                                     const uint32_t renderer_flags)
{
    assert (boot_config != NULL);
    boot_config->init_subsystems = init_subsystems;
    boot_config->window_title = window_title;
    boot_config->window_flags = window_flags;
    boot_config->renderer_flags = renderer_flags;
}



//-----------------------------------------------------------------------------
// Lifecycle Management Functions.
//-----------------------------------------------------------------------------

// Initialise SDL given the configuration, or if NULL use the defaults.
// If init fails sdl2boot_done(...) need not be called.
// Returns true upon success, or false upon failure.
bool sdl2boot_init(Sdl2BootContext * sdl2boot, const Sdl2BootConfig * boot_config)
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "sdl2boot_init: sdl2boot=%p, boot_config=%p\n", sdl2boot, boot_config);
    assert (sdl2boot != NULL);
    assert (sdl2boot->state.initialised == false);
    assert (sdl2boot->state.init_subsystems == 0);
    assert (sdl2boot->state.window == NULL);
    assert (sdl2boot->state.renderer == NULL);
    // Initialise the context.
    memset(sdl2boot, 0, sizeof(Sdl2BootContext));
    // Copy the configuration or use the default if passed NULL.
    const Sdl2BootConfig * config = (boot_config == NULL) ? &sdl2boot_config_default : boot_config;
    memcpy(&sdl2boot->config, config, sizeof(struct Sdl2BootConfig));
    // Initialise SDL and its required sub-systems.
    if (SDL_Init(sdl2boot->config.init_subsystems) != 0) {
        SDL_Log("sdl2boot_init: SDL_Init failed: %s", SDL_GetError());
        return false;
    }
    sdl2boot->state.init_subsystems = sdl2boot->config.init_subsystems;
    // Get the desktop dimensions.
    SDL_DisplayMode desktop_display_mode = { 0 };
    SDL_GetDesktopDisplayMode(0, &desktop_display_mode);
    // Create the window.
    sdl2boot->state.window = SDL_CreateWindow(
            sdl2boot->config.window_title,
            0,
            0,
            desktop_display_mode.w,
            desktop_display_mode.h,
            sdl2boot->config.window_flags);
    if (sdl2boot->state.window == NULL) {
        SDL_Log("sdl2boot_init: SDL_CreateWindow failed: %s", SDL_GetError());
        sdl2boot_done(sdl2boot);
        return false;
    }
    // Open the SDL renderer.
    sdl2boot->state.renderer = SDL_CreateRenderer(sdl2boot->state.window,
                                                  0,
                                                  sdl2boot->config.renderer_flags);
    if (sdl2boot->state.renderer == NULL) {
        SDL_Log("sdl2boot_init: SDL_CreateRenderer failed: %s", SDL_GetError());
        sdl2boot_done(sdl2boot);
        return false;
    }
    // Get SDL display mode.
    if (SDL_GetCurrentDisplayMode(0, &sdl2boot->state.display_mode) != 0) {
        SDL_Log("sdl2boot_init: SDL_GetCurrentDisplayMode failed: %s", SDL_GetError());
        sdl2boot_done(sdl2boot);
        return false;
    }
    // Get renderer pixel width and height.
    if (SDL_GetRendererOutputSize(sdl2boot->state.renderer,
                                  &sdl2boot->state.renderer_width,
                                  &sdl2boot->state.renderer_height) != 0) {
        SDL_Log("sdl2boot_init: SDL_GetRendererOutputSize failed: %s", SDL_GetError());
        sdl2boot_done(sdl2boot);
        return false;
    }
    // SDL 2 Boot is initialised successfully.
    sdl2boot->state.initialised = true;
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
                 "sdl2boot_init: successful."
                 " Display mode width=%d, height=%d, refresh=%d."
                 " Renderer width=%d, height=%d.\n",
                 sdl2boot->state.display_mode.w, sdl2boot->state.display_mode.h,
                 sdl2boot->state.display_mode.refresh_rate,
                 sdl2boot->state.renderer_width, sdl2boot->state.renderer_height);
    return true;
}


static Sdl2BootEventResult sdl2boot_handle_events(Sdl2BootContext * sdl2boot);


void sdl2boot_run(Sdl2BootContext * sdl2boot)
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "sdl2boot_run: sdl2boot=%p\n", sdl2boot);
    assert (sdl2boot != NULL);
    Sdl2BootEventResult result = SDL2BOOT_OKAY;
    while (result == SDL2BOOT_OKAY)
    {
        result = sdl2boot_handle_events(sdl2boot);
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "sdl2boot_run: completed.\n");
}







static Sdl2BootEventResult sdl2boot_handle_event(Sdl2BootContext * sdl2boot, const SDL_Event * event)
{
    assert (sdl2boot != NULL);
    assert (event != NULL);
    Sdl2BootEventHandlers * handlers = &sdl2boot->config.event_handlers;
    switch (event->type)
    {
        case SDL_FIRSTEVENT:
            break;
        case SDL_QUIT:
            if (handlers->quit_handler != NULL) {
                return handlers->quit_handler(sdl2boot, (SDL_QuitEvent *)event);
            } else {
                return SDL2BOOT_QUIT;
            }
            break;
        SDL_APP_TERMINATING:
            break;
        case SDL_APP_LOWMEMORY:
//            if (handlers->handler != NULL) {
//                handlers->quit_handler(vedge, (SDL_QuitEvent *)event);
//            }
            break;
        case SDL_APP_WILLENTERBACKGROUND:
            break;
        case SDL_APP_DIDENTERBACKGROUND:
            break;
        case SDL_APP_WILLENTERFOREGROUND:
            break;
        case  SDL_APP_DIDENTERFOREGROUND:
            break;
        case   SDL_WINDOWEVENT:
            if (handlers->window_handler != NULL) {
                handlers->window_handler(sdl2boot, (SDL_WindowEvent *)event);
            }
            break;
        case SDL_SYSWMEVENT:
            break;
        case SDL_KEYDOWN:
            if (handlers->key_handler != NULL) {
                handlers->key_handler(sdl2boot, (SDL_KeyboardEvent *)event);
            }
            break;
        case SDL_KEYUP:
            if (handlers->key_handler != NULL) {
                handlers->key_handler(sdl2boot, (SDL_KeyboardEvent *)event);
            }
            break;
        case SDL_TEXTEDITING:
            break;
        case SDL_TEXTINPUT:
            break;
        case SDL_KEYMAPCHANGED:
            break;
        case SDL_MOUSEMOTION:
            break;
        case SDL_MOUSEBUTTONDOWN:
            break;
        case SDL_MOUSEBUTTONUP:
            break;
        case SDL_MOUSEWHEEL:
            break;
        case SDL_JOYAXISMOTION:
            break;
        case SDL_JOYBALLMOTION:
            if (handlers->jball_handler != NULL) {
                handlers->jball_handler(sdl2boot, (SDL_JoyBallEvent *)event);
            }
            break;
        case SDL_JOYHATMOTION:
            if (handlers->jhat_handler != NULL) {
                handlers->jhat_handler(sdl2boot, (SDL_JoyHatEvent *)event);
            }
            break;
        case SDL_JOYBUTTONDOWN:
            break;
        case SDL_JOYBUTTONUP:
            break;
        case SDL_JOYDEVICEADDED:
            break;
        case SDL_JOYDEVICEREMOVED:
            break;
        case SDL_CONTROLLERAXISMOTION:
            break;
        case SDL_CONTROLLERBUTTONDOWN:
            break;
        case SDL_CONTROLLERBUTTONUP:
            break;
        case SDL_CONTROLLERDEVICEADDED:
            break;
        case SDL_CONTROLLERDEVICEREMOVED:
            break;
        case SDL_CONTROLLERDEVICEREMAPPED:
            break;
        case SDL_FINGERDOWN:
            break;
        case SDL_DOLLARGESTURE:
            break;
        case  SDL_CLIPBOARDUPDATE:
            break;
        case
            SDL_DROPFILE:
            break;
        case SDL_DROPTEXT:
            break;
        case SDL_DROPBEGIN:
            break;
        case SDL_DROPCOMPLETE:
            break;
        case SDL_AUDIODEVICEADDED :
            break;
        case SDL_AUDIODEVICEREMOVED:
            break;
        case SDL_RENDER_TARGETS_RESET:
            break;
        case SDL_RENDER_DEVICE_RESET:
            break;
        default:
            if (event->type >= SDL_USEREVENT) {
                //handlers->u
            } else {
                // unknown
            }
    }
}


static Sdl2BootEventResult sdl2boot_handle_events(Sdl2BootContext * sdl2boot)
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        Sdl2BootEventResult result = sdl2boot_handle_event(sdl2boot, &event);
        if (result != SDL2BOOT_OKAY) {
            return result;
        }
    }
    return SDL2BOOT_OKAY;
}


// Clean-up and shutdown SDL2 including any resources that have been allocated.
// Can be called more than once on any configured context.
void sdl2boot_done(Sdl2BootContext * sdl2boot)
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "sdl2boot_done: sdl2boot=%p\n", sdl2boot);
    assert (sdl2boot != NULL);
    // Clean up renderer width and height.
    sdl2boot->state.renderer_height = 0;
    sdl2boot->state.renderer_width = 0;
    // Clean up display mode.
    memset(&sdl2boot->state.display_mode, 0, sizeof(sdl2boot->state.display_mode));
    // Close the SDL renderer.
    if (sdl2boot->state.renderer != NULL) {
        SDL_DestroyRenderer(sdl2boot->state.renderer);
        sdl2boot->state.renderer = NULL;
    }
    // Close the SDL window.
    if (sdl2boot->state.window) {
        SDL_DestroyWindow(sdl2boot->state.window);
        sdl2boot->state.window = NULL;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "sdl2boot_done: shutting down SDL.\n");
    // Shutdown SDL and its sub-systems.
    if (sdl2boot->state.init_subsystems) {
        SDL_Quit();
        sdl2boot->state.init_subsystems = 0;
    }
    // SDL 2 Boot is no longer initialised.
    sdl2boot->state.initialised = 0;
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "sdl2boot_done: completed.\n");
}



//-----------------------------------------------------------------------------
// Context State Access Functions and Macros.
//-----------------------------------------------------------------------------

// Has SDL Boot been fully initialised successfully.
const bool sdl2boot_is_initialised(const Sdl2BootContext * sdl2boot)
{
    return sdl2boot->state.initialised;
}

// Get the SDL windows for an SDL Boot context.
SDL_Window * sdl2boot_get_window(const Sdl2BootContext * sdl2boot)
{
    return sdl2boot->state.window;
}

// Get the SDL Boot renderer for an SDL Boot context.
SDL_Renderer * sdl2boot_get_renderer(const Sdl2BootContext * sdl2boot)
{
    return sdl2boot->state.renderer;
}


// Get the display mode for an SDL Boot context.
const SDL_DisplayMode * sdl2boot_get_display_mode(const Sdl2BootContext * sdl2boot)
{
    return &sdl2boot->state.display_mode;
}


// Get the renderer width for an SDL Boot context.
const int sdl2boot_get_render_width(const Sdl2BootContext * sdl2boot)
{
    return sdl2boot->state.renderer_width;
}


// Get the renderer height for an SDL Boot context.
const int sdl2boot_get_render_height(const Sdl2BootContext * sdl2boot)
{
    return sdl2boot->state.renderer_height;
}
