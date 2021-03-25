//=============================================================================
// Title:        SDL2 Boot (Bootstrapping of SDL version 2).
// Filename:     sdl2boot.c
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-03-24 21:55
// Version:      1.0.0-beta-1
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
void sdl2boot_config_template(Sdl2BootConfig * boot_config,
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


