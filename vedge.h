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


#include <SDL.h>

#include "vmath.h"
#include "vdraw.h"


//-----------------------------------------------------------------------------
// Constants.
//-----------------------------------------------------------------------------

// Error Codes
#define VEDGE_NO_ERROR (0)
#define VEDGE_ERR_NULL_CONTEXT (1)

// Error message maximum size (includes NUL terminator).
#define VDRAW_ERROR_MESSAGE_LENGTH_MAX (256)



//-----------------------------------------------------------------------------
// Vector Display Graphics Engine Types.
//-----------------------------------------------------------------------------

//// Display details.
//typedef struct VedgeDisplayDetail {
//    // Screen display's pixel width for current mode.
//    int width;
//    // Screen display pixel height for current mode.
//    int height;
//    // Screen display refresh frequency (Hz) for current mode.
//    int refresh_rate;
//};
//
//// Window details.
//typedef struct VedgeWindowDetail {
//    // Window client area width in pixels.
//    int width;
//    // Window client area height in pixels.
//    int height;
//};
//
//typedef struct VedgeConfig {
//    int video_width;
//    int video_height;
//    int refresh_rate;
//    int video_mode;
//} VedgeConfig;


//funct* video_configurator.


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
    _Bool closed;
    VedgePoints points[];
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


////
//typedef struct VedgeString {
//    enum { LEFT, CENTRE, RIGHT } justification;
//    char * characters;
//};

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
    int type;
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
    _Bool enable;
    // Optional application_data.
    void * application_data;
    // Optional game object items.
    VedgeGameObjectItems * items;
    // Optional children game objects.
    VedgeGameObjectChildren * children;
} VedgeGameObject;



//int length;
//VedgeGameItem items[];



















//
//// List of two dimensional points.
//typedef struct VedgeGlyph {
//    char character;
//    VmathNumber x1;
//    VmathNumber y1;
//    char character;
//    int length;
//    VedgePoint dots[];
//} VedgePath;
//




//
////
////groups of variant type+thing
//
//
//// List of two dimensional points.
//typedef struct VedgePoints {
//    int length;
//    VedgePoint dots[];
//} VedgePoints;
//
//
//// List of two dimensional lines.
//typedef struct VedgeLines {
//    int length;
//    VedgeLine lines[];
//} VedgeLines;
//





// Engine context (access via API functions only).
typedef struct VedgeContext {
    VdrawContext * vdraw_context;
    SDL_Renderer * sdl_renderer;
    VdrawContext private_vdraw_context;
    int vedge_error_code;
    char * vedge_error_message;
    char private_vdraw_error_message[VDRAW_ERROR_MESSAGE_LENGTH_MAX+1];
} VedgeContext;



//-----------------------------------------------------------------------------
// Lifecycle Management Functions.
//-----------------------------------------------------------------------------

// Initialise the engine context.
extern int vedge_init(VedgeContext * context, SDL_Renderer * sdl_renderer);

// Clean-up the engine context.
extern void vedge_done(VedgeContext * vedge);



//-----------------------------------------------------------------------------
// Error Handling Functions.
//-----------------------------------------------------------------------------

// Clear the last error code.
void vedge_clear_error_code(VedgeContext *vedge);

// Get the last error code.
int vedge_get_error_code(const VedgeContext *vedge);

// Get the last error message.
const char * vedge_get_error_message(const VedgeContext *vedge);



//-----------------------------------------------------------------------------
// Engine Functions.
//-----------------------------------------------------------------------------


void vedge_frame_start(VedgeContext * context);


void vedge_frame_finish(VedgeContext * context);


void vedge_frame_add_game_object(VedgeContext * context, const VedgeGameObject game_object);











//// Item types.
//enum ItemType {
//    // Single point.
//    Dot,
//    // A line
//    Line,
//    // A single characters.
//    Char,
//    // A collection of dots.
//    Dots,
//    // A collection of points joined together with lines that make up a continuous path.
//    LinePath,
//    // A collection of lines.
//    Lines,
//    // A string of text.
//    String,
//    // A collection of points joined together with lines that make up a continuous path.
//  //  LinePath,
//    //FXME: description and name.
//  //  VertsLines,
//    // Child game objects.
//    GameObjects
//};
//


//typedef struct VedgeGroupItem {
//} VedgeGroupItem;
//
//typedef struct  VedgeGroup {
//
//} VedgeGroup;
//
//
//typedef int VEDGE_GROUP;



//
//
//vedge_game_object_




// Type Drawing Functions

//void vedge_draw_point_type(VedgeContext *  context, VedgePoint point);
//{
    //FIXME: vedge_draw_point(context point.x, point.y);
//}



#endif /* __VEDGE__H__ */


