//=============================================================================
// Title:        SDL2 Boot (Bootstrapping of SDL version 2).
// Filename:     sdl2boot.h
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-04-12 22:55
// Version:      1.0.0-beta-2
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

// Event handlers function pointer types.
typedef struct VedgeContext VedgeContext;
typedef void (*sdl2boot_common_handler)(VedgeContext * vedge, SDL_CommonEvent * common);
typedef void (*sdl2boot_window_handler)(VedgeContext * vedge, SDL_WindowEvent * window);
typedef void (*sdl2boot_keyboard_handler)(VedgeContext * vedge, SDL_KeyboardEvent * key);
typedef void (*sdl2boot_textediting_handler)(VedgeContext * vedge, SDL_TextEditingEvent * edit);
typedef void (*sdl2boot_textinput_handler)(VedgeContext * vedge, SDL_TextInputEvent * text);
typedef void (*sdl2boot_mousemotion_handler)(VedgeContext * vedge, SDL_MouseMotionEvent * motion);
typedef void (*sdl2boot_mousebutton_handler)(VedgeContext * vedge, SDL_MouseButtonEvent * button);
typedef void (*sdl2boot_mousewheeel_handler)(VedgeContext * vedge, SDL_MouseWheelEvent * wheel);
typedef void (*sdl2boot_joyaxis_handler)(VedgeContext * vedge, SDL_JoyAxisEvent * jaxis);
typedef void (*sdl2boot_joyball_handler)(VedgeContext * vedge, SDL_JoyBallEvent * jball);
typedef void (*sdl2boot_joyhat_handler)(VedgeContext * vedge, SDL_JoyHatEvent * jhat);
typedef void (*sdl2boot_joybutton_handler)(VedgeContext * vedge, SDL_JoyButtonEvent * jbutton);
typedef void (*sdl2boot_joydevice_handler)(VedgeContext * vedge, SDL_JoyDeviceEvent * jdevice);
typedef void (*sdl2boot_controlleraxis_handler)(VedgeContext * vedge, SDL_ControllerAxisEvent * caxis);
typedef void (*sdl2boot_controllerbutton_handler)(VedgeContext * vedge, SDL_ControllerButtonEvent * cbutton);
typedef void (*sdl2boot_controllerdevice_handler)(VedgeContext * vedge, SDL_ControllerDeviceEvent * cdevice);
typedef void (*sdl2boot_audiodevice_handler)(VedgeContext * vedge, SDL_AudioDeviceEvent * adevice);
typedef void (*sdl2boot_quit_handler)(VedgeContext * vedge, SDL_QuitEvent * quit);
typedef void (*sdl2boot_user_handler)(VedgeContext * vedge, SDL_UserEvent * user);
typedef void (*sdl2boot_syswm_handler)(VedgeContext * vedge, SDL_SysWMEvent * syswm);
typedef void (*sdl2boot_touchfinger_handler)(VedgeContext * vedge, SDL_TouchFingerEvent * tfinger);
typedef void (*sdl2boot_multigesture_handler)(VedgeContext * vedge, SDL_MultiGestureEvent * mgesture);
typedef void (*sdl2boot_dollargesture_handler)(VedgeContext * vedge, SDL_DollarGestureEvent * dgesture);
typedef void (*sdl2boot_drop_handler)(VedgeContext * vedge, SDL_DropEvent * drop);


typedef struct Sdl2BootEventHandlers
{
    void * context_param;
    sdl2boot_common_handler common_handler;
    sdl2boot_window_handler window_handler;
    sdl2boot_keyboard_handler key_handler;
    sdl2boot_textediting_handler edit_handler;
    sdl2boot_textinput_handler text_handler;
    sdl2boot_mousemotion_handler motion_handler;
    sdl2boot_mousebutton_handler button_handler;
    sdl2boot_mousewheeel_handler wheel_handler;
    sdl2boot_joyaxis_handler jaxis_handler;
    sdl2boot_joyball_handler jball_handler;
    sdl2boot_joyhat_handler jhat_handler;
    sdl2boot_joybutton_handler jbutton_handler;
    sdl2boot_joydevice_handler jdevice_handler;
    sdl2boot_controlleraxis_handler caxis_handler;
    sdl2boot_controllerbutton_handler cbutton_handler;
    sdl2boot_controllerdevice_handler cdevice_handler;
    sdl2boot_audiodevice_handler adevice_handler;
    sdl2boot_quit_handler quit_handler;
    sdl2boot_user_handler user_handler;
    sdl2boot_syswm_handler syswm_handler;
    sdl2boot_touchfinger_handler tfinger_handler;
    sdl2boot_multigesture_handler mgesture_handler;
    sdl2boot_dollargesture_handler dgesture_handler;
    sdl2boot_drop_handler drop_handler;
} Sdl2BootEventHandlers;


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
    // Event handlers.
    Sdl2BootEventHandlers event_handlers;
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
    // Is the context running.
    bool running;
    // Is the context to stop running.
    bool quit;
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
void sdl2boot_config_from_template(Sdl2BootConfig * boot_config,
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
const bool sdl2boot_is_initialised(const Sdl2BootContext * sdl2boot);

// Get the SDL windows for an SDL Boot context.
SDL_Window * sdl2boot_get_window(const Sdl2BootContext * sdl2boot);

// Get the SDL Boot renderer for an SDL Boot context.
SDL_Renderer * sdl2boot_get_renderer(const Sdl2BootContext * sdl2boot);

// Get the display mode for an SDL Boot context.
const SDL_DisplayMode * sdl2boot_get_display_mode(const Sdl2BootContext * sdl2boot);

// Get the renderer width for an SDL Boot context.
const int sdl2boot_get_render_width(const Sdl2BootContext * sdl2boot);

// Get the renderer height for an SDL Boot context.
const int sdl2boot_get_render_height(const Sdl2BootContext * sdl2boot);


#endif /* __SDL2BOOT__H__ */


