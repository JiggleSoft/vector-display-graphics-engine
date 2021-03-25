//=============================================================================
// Title:        SDL2 Boot (Bootstrapping of SDL version 2).
// Filename:     sdl2boot.h
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

#ifndef __SDL2BOOT__H__
#define __SDL2BOOT__H__


#include <SDL.h>

#include <stdint.h>
#include <stdbool.h>


//-----------------------------------------------------------------------------
// SDL 2 Boot Version and Title Constants.
//-----------------------------------------------------------------------------

// SDL 2 Boot version string.
#define SDL2BOOT_VERSION "1.0.0-beta-0"

// SDL 2 Boot title string.
#define SDL2BOOT_TITLE "SDL 2 Boot version " SDL2BOOT_VERSION " by Justin Lane."


//-----------------------------------------------------------------------------
// SDL 2 Boot Constants.
//-----------------------------------------------------------------------------

// Default sub-systems to initialise.
#define SDL2BOOT_SDL_INIT (SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)

// Default window flags.
#define SDL2BOOT_SDL_WINDOW_FLAGS (SDL_WINDOW_FULLSCREEN_DESKTOP)

// Default renderer flags.
#define SDL2BOOT_SDL_RENDERER_FLAGS (SDL_RENDERER_SOFTWARE)


//-----------------------------------------------------------------------------
// Configuration, State, and Context Data Types.
//-----------------------------------------------------------------------------

// Initialisation configuration.
typedef struct Sdl2BootConfig {
    // Initial sub-systems to initialise (passed to SDL_Init(...)).
    uint32_t init_subsystems;
    // Window title.
    const char * window_title;
    // Window creation flags.
    uint32_t window_flags;
    // Renderer creation flags.
    uint32_t renderer_flags;
} Sdl2BootConfig;


// Initial state.
typedef struct Sdl2BootState {
    // Initial sub-systems that have been successfully initialised.
    uint32_t init_subsystems;
    // Pointer to the window or NULL (not successfully initialised).
    SDL_Window * window;
    // SDL rendering context or NULL (not successfully initialised).
    SDL_Renderer * renderer;
    // Display mode as opened.
    SDL_DisplayMode display_mode;
    // Renderer width.
    int renderer_width;
    // Renderer height.
    int renderer_height;
    // Is the context initialised fully.
    bool initialised;
} Sdl2BootState;


// Engine context (access via API functions only).
typedef struct Sdl2BootContext {
    Sdl2BootConfig config;
    Sdl2BootState  state;
} Sdl2BootContext;


//-----------------------------------------------------------------------------
// Configuration Functions.
//-----------------------------------------------------------------------------

// Configure of SDL 2 boot from the template, or if NULL the defaults.
void sdl2boot_config_template(Sdl2BootConfig * boot_config,
                              const Sdl2BootConfig * template_boot_config);

// Quick configure of SDL 2 boot for primary display and desktop resolution.
void sdl2boot_config_primary_desktop(Sdl2BootConfig * boot_config,
                                     const uint32_t init_subsystems,
                                     const char * windows_title,
                                     const uint32_t window_flags,
                                     const uint32_t renderer_flags);


//-----------------------------------------------------------------------------
// Lifecycle Management Functions.
//-----------------------------------------------------------------------------

// Initialise SDL given the configuration, or if NULL use the defaults.
// If init fails sdl2boot_done(...) need not be called.
// Returns true upon success, or false upon failure.
bool sdl2boot_init(Sdl2BootContext * sdl2boot, const Sdl2BootConfig * boot_config);

// Clean-up and shutdown SDL2 including any resources that have been allocated.
// Can be called more than once on any configured context.
void sdl2boot_done(Sdl2BootContext * sdl2boot);


//-----------------------------------------------------------------------------
// Context State Access Functions and Macros.
//-----------------------------------------------------------------------------

// Has SDL Boot been fully initialised successfully.
inline const bool sdl2boot_is_initialised(const Sdl2BootContext * sdl2boot)
{
    return sdl2boot->state.initialised;
}

// Get the SDL windows for an SDL Boot context.
inline SDL_Window * sdl2boot_get_window(const Sdl2BootContext * sdl2boot)
{
    return sdl2boot->state.window;
}

// Get the SDL Boot renderer for an SDL Boot context.
inline SDL_Renderer * sdl2boot_get_renderer(const Sdl2BootContext * sdl2boot)
{
    return sdl2boot->state.renderer;
}


// Get the display mode for an SDL Boot context.
inline const SDL_DisplayMode * sdl2boot_get_display_mode(const Sdl2BootContext * sdl2boot)
{
    return &sdl2boot->state.display_mode;
}


// Get the renderer width for an SDL Boot context.
inline const int sdl2boot_get_render_width(const Sdl2BootContext * sdl2boot)
{
    return sdl2boot->state.renderer_width;
}


// Get the renderer height for an SDL Boot context.
inline const int sdl2boot_get_render_height(const Sdl2BootContext * sdl2boot)
{
    return sdl2boot->state.renderer_height;
}



#endif /* __SDL2BOOT__H__ */


