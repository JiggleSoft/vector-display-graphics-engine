//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge).
// Filename:     vedge.h
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

#ifndef __VEDGE__H__
#define __VEDGE__H__


#include <stdbool.h>

#include <SDL.h>

#include "sdl2boot.h"

#include "vmath.h"
#include "vdraw.h"



//-----------------------------------------------------------------------------
// Engine Version and Title Constants.
//-----------------------------------------------------------------------------

#define VEDGE_VERSION "0.0.0.0-beta-0"

#define VEDGE_TITLE "Powered by vEDGE version " VEDGE_VERSION \
                    " by Justin Lane (https://github.com/JiggleSoft/vector-display-graphics-engine/)."                        \
                    " Using SDL 2 library (https://www.libsdl.org/)."


//-----------------------------------------------------------------------------
// Engine Constants.
//-----------------------------------------------------------------------------

// .
#define VEDGE_SDL_INIT (SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)

// .
#define VEDGE_SDL_WINDOW_FLAGS (SDL_WINDOW_FULLSCREEN_DESKTOP)

// .
#define VEDGE_SDL_RENDERER_FLAGS (SDL_RENDERER_SOFTWARE)


//-----------------------------------------------------------------------------
// Configuration, State, and Context Data Types.
//-----------------------------------------------------------------------------

// Initialisation configuration.
typedef struct VedgeConfig {
    SDL_Window * sdl_window;
    SDL_Renderer * sdl_renderer;
} VedgeConfig;


// Initial state.
typedef struct VedgeState {
    // Has vmath_init been called successfully?
    bool vmath_initialised;
    // The private vdraw context.
    VdrawContext private_vdraw_context;
    // Pointer to the vdraw context or NULL (not successfully initialised).
    VdrawContext * vdraw_context;
    // vEdge iniitialised successfully.
    bool initialised;
} VedgeState;


// Event handlers function pointer types.
typedef struct VedgeContext VedgeContext;
typedef void (*vedge_sdl2_common_handler)(VedgeContext * vedge, SDL_CommonEvent * common);
typedef void (*vedge_sdl2_window_handler)(VedgeContext * vedge, SDL_WindowEvent * window);
typedef void (*vedge_sdl2_keyboard_handler)(VedgeContext * vedge, SDL_KeyboardEvent * key);
typedef void (*vedge_sdl2_textediting_handler)(VedgeContext * vedge, SDL_TextEditingEvent * edit);
typedef void (*vedge_sdl2_textinput_handler)(VedgeContext * vedge, SDL_TextInputEvent * text);
typedef void (*vedge_sdl2_mousemotion_handler)(VedgeContext * vedge, SDL_MouseMotionEvent * motion);
typedef void (*vedge_sdl2_mousebutton_handler)(VedgeContext * vedge, SDL_MouseButtonEvent * button);
typedef void (*vedge_sdl2_mousewheeel_handler)(VedgeContext * vedge, SDL_MouseWheelEvent * wheel);
typedef void (*vedge_sdl2_joyaxis_handler)(VedgeContext * vedge, SDL_JoyAxisEvent * jaxis);
typedef void (*vedge_sdl2_joyball_handler)(VedgeContext * vedge, SDL_JoyBallEvent * jball);
typedef void (*vedge_sdl2_joyhat_handler)(VedgeContext * vedge, SDL_JoyHatEvent * jhat);
typedef void (*vedge_sdl2_joybutton_handler)(VedgeContext * vedge, SDL_JoyButtonEvent * jbutton);
typedef void (*vedge_sdl2_joydevice_handler)(VedgeContext * vedge, SDL_JoyDeviceEvent * jdevice);
typedef void (*vedge_sdl2_controlleraxis_handler)(VedgeContext * vedge, SDL_ControllerAxisEvent * caxis);
typedef void (*vedge_sdl2_controllerbutton_handler)(VedgeContext * vedge, SDL_ControllerButtonEvent * cbutton);
typedef void (*vedge_sdl2_controllerdevice_handler)(VedgeContext * vedge, SDL_ControllerDeviceEvent * cdevice);
typedef void (*vedge_sdl2_audiodevice_handler)(VedgeContext * vedge, SDL_AudioDeviceEvent * adevice);
typedef void (*vedge_sdl2_quit_handler)(VedgeContext * vedge, SDL_QuitEvent * quit);
typedef void (*vedge_sdl2_user_handler)(VedgeContext * vedge, SDL_UserEvent * user);
typedef void (*vedge_sdl2_syswm_handler)(VedgeContext * vedge, SDL_SysWMEvent * syswm);
typedef void (*vedge_sdl2_touchfinger_handler)(VedgeContext * vedge, SDL_TouchFingerEvent * tfinger);
typedef void (*vedge_sdl2_multigesture_handler)(VedgeContext * vedge, SDL_MultiGestureEvent * mgesture);
typedef void (*vedge_sdl2_dollargesture_handler)(VedgeContext * vedge, SDL_DollarGestureEvent * dgesture);
typedef void (*vedge_sdl2_drop_handler)(VedgeContext * vedge, SDL_DropEvent * drop);


typedef struct VedgeEventHandlers
{
vedge_sdl2_common_handler common_handler;
vedge_sdl2_window_handler window_handler;
vedge_sdl2_keyboard_handler key_handler;
vedge_sdl2_textediting_handler edit_handler;
vedge_sdl2_textinput_handler text_handler;
vedge_sdl2_mousemotion_handler motion_handler;
vedge_sdl2_mousebutton_handler button_handler;
vedge_sdl2_mousewheeel_handler wheel_handler;
vedge_sdl2_joyaxis_handler jaxis_handler;
vedge_sdl2_joyball_handler jball_handler;
vedge_sdl2_joyhat_handler jhat_handler;
vedge_sdl2_joybutton_handler jbutton_handler;
vedge_sdl2_joydevice_handler jdevice_handler;
vedge_sdl2_controlleraxis_handler caxis_handler;
vedge_sdl2_controllerbutton_handler cbutton_handler;
vedge_sdl2_controllerdevice_handler cdevice_handler;
vedge_sdl2_audiodevice_handler adevice_handler;
vedge_sdl2_quit_handler quit_handler;
vedge_sdl2_user_handler user_handler;
vedge_sdl2_syswm_handler syswm_handler;
vedge_sdl2_touchfinger_handler tfinger_handler;
vedge_sdl2_multigesture_handler mgesture_handler;
vedge_sdl2_dollargesture_handler dgesture_handler;
vedge_sdl2_drop_handler drop_handler;
} VedgeEventHandlers;


// Engine context (access via API functions only or macros only).
typedef struct VedgeContext {
    VedgeConfig config;
    VedgeState  state;
    VedgeEventHandlers event_handlers;
} VedgeContext;


//-----------------------------------------------------------------------------
// Configuration Functions.
//-----------------------------------------------------------------------------

// Initialise an init config from defaults (template_config == NULL) or
// by a supplied template_config.
void vedge_config_template(VedgeConfig * vedge_config,
                           const VedgeConfig * template_vedge_config);


// .
void vedge_config_sdl2boot(VedgeConfig * vedge_config,
                           const Sdl2BootContext * sdl2boot);


//-----------------------------------------------------------------------------
// Lifecycle Management Functions.
//-----------------------------------------------------------------------------

// Initialise the engine context.
bool vedge_init(VedgeContext * vedge, const VedgeConfig * vedge_config);

// Clean-up the engine context.
void vedge_done(VedgeContext * vedge);


//-----------------------------------------------------------------------------
// Vector Display Graphics Engine Main Loop and Event Processing.
//-----------------------------------------------------------------------------

// .
typedef int * (dd)();


// .
int vedge_run(VedgeContext * vedge);


//-----------------------------------------------------------------------------
// Vector Display Graphics Engine State Update Types.
//-----------------------------------------------------------------------------

typedef struct VpenWidth {
    VmathNumber width;
} VpenWdith;


typedef struct VfgColour {
    VdrawRGB colour;
} VfgColour;


//-----------------------------------------------------------------------------
// Vector Display Graphics Engine Renderable Types.
//-----------------------------------------------------------------------------

// Two dimensional point (x1,y1)
typedef struct VedgePoint {
    VmathNumber x1;
    VmathNumber y1;
} VedgePoint;


// Two dimensional line (x1,y1)-(x2,y2).
typedef struct VedgeLine {
    VmathNumber x1;
    VmathNumber y1;
    VmathNumber x2;
    VmathNumber y2;
} VedgeLine;


// Array of two dimensional points.
typedef struct VedgePoints {
    int length;
    VedgePoint points[];
} VedgePoints;


// Array of two dimensional points.
typedef struct VedgePath {
    bool closed;
    VedgePoints points;
} VedgePath;


// Array of two dimensional lines.
typedef struct VedgeLines {
    int length;
    VedgeLine lines[];
} VedgeLines;


// Font glyph.
typedef struct VedgeGlyph {
    int length;
    struct VedgeLine lines[];
} VedgeGlyph;


//// Text string.
////extern  Vfont;
//typedef struct VedgeString {
//    enum { LEFT, CENTRE, RIGHT } justification;
//    struct Vfont * font;
//    int length;
//    char * characters;
//};


//typedef struct VedgeVerticesEdges {
//    VedgePoints points;
//    int length;
//     edges[];
//} VedgeVerticesEdges;
//
//
//typedef struct VedgeVerticesEdges {
//VmathNumber frame;
//enum interplation { LINEAR };
//    frames[] VedgePoints points;
//
//int length;
//edges[];
//} VedgeVerticesEdges;



// Item types.
typedef enum ItemType {
    // Single point.
    POINT,
    // A line
    LINE,
    // A single characters.
    CHAR,
    // A collection of dots.
    POINTS,
    // A collection of points joined together with lines that make up a continuous path.
    LINEPATH,
    // A collection of lines.
    LINES,
    // A string of text.
    STRING,
    // A collection of points joined together with lines that make up a continuous path.
    //  LinePath,
    //FXME: description and name.
    //  VertsLines,
    // Child game objects.
    GameObjects
} ItemType;

//
typedef union VedgeGameItemVariant {
    VedgePoint       * point;
    VedgeLine        * line;
    VedgePoints      * points;
    VedgePath        * path;
    VedgeLines       * lines;
} VedgeGameItemVariant;

//
typedef struct VedgeGameItem {
    ItemType type;
    VedgeGameItemVariant game_item;
} VedgeGameItem;

//
////VedgeItem
//struct VedgeItems {
//    int count;
//    union {;
////    CedgeItem
//
//};
//

typedef struct VedgeGameObject VedgeGameObject;


typedef struct VedgeGameObjectItems {
    int length;
    VedgeGameItem game_items[];

} VedgeGameObjectItems;


typedef struct VedgeGameObjectChildren {
    int length;
    VedgeGameObject * game_objects[];
} VedgeGameObjectChildren;


// Represents an object within the game.
typedef struct VedgeGameObject {
    // The position of this object within the world.
    VmathMatrix3x3 position;
    // The orientation of this object within the world.
    VmathMatrix3x3 rotation;
    // The size of this object within the world.
    VmathMatrix3x3 scaling;
    // Enablement.
    bool enable;
    // Optional application_data.
    void * application_data;
    // Optional game object items.
    VedgeGameObjectItems * items;
    // Optional children game objects.
    VedgeGameObjectChildren * children;
} VedgeGameObject;





//-----------------------------------------------------------------------------
// Engine Functions.
//-----------------------------------------------------------------------------

//void vedge_set_viewport);

//void vedge_

void vedge_frame_start(VedgeContext * context);


void vedge_frame_finish(VedgeContext * context);


void vedge_frame_add_game_object(VedgeContext * context, const VedgeGameObject * game_object);

void vedge_frame_add_game_objects(VedgeContext * context, const int length, const VedgeGameObject * game_objects);



#endif /* __VEDGE__H__ */


