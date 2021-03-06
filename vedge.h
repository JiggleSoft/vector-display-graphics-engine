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
// Vector Display Engine Types.
//-----------------------------------------------------------------------------



//Error Codes
#define VEDGE_NO_ERROR (0)
#define VEDGE_ERR_NULL_CONTEXT (1)


#define VDRAW_ERROR_MESSAGE_LENGTH_MAX (256)


// Engine context (access via API functions only).
typedef struct VedgeContext {
    VdrawContext * vdraw_context;
    SDL_Renderer * sdl_renderer;
    VdrawContext private_vdraw_context;
    int vedge_error_code;
    char * vedge_error_message;
    char private_vdraw_error_message[VDRAW_ERROR_MESSAGE_LENGTH_MAX+1];
} VedgeContext;





typedef struct VedgePoint {
    VmathNumber x;
    VmathNumber y;
    VmathNumber t;
} VedgePoint;


typedef struct VedgeLine {
    VmathNumber x1;
    VmathNumber y1;
    VmathNumber x2;
    VmathNumber y2;
} VedgeLine;


typedef struct VedgeLinePath {
    int length;
    VedgePoint   origin;
    VedgePoint path[];
} VedgeLinePath;

typedef struct VedgeLines {
    int length;
    VedgeLine lines[];
} VedgeLines;

enum ItemType { Point, Line, LinePath, Lines, Group };


typedef struct VedgeGroupItem {
} VedgeGroupItem;

typedef struct  VedgeGroup {

} VedgeGroup;


typedef int VEDGE_GROUP;







// Type Drawing Functions

void vedge_draw_point_type(VedgeContext *  context, VedgePoint point);
//{
    //FIXME: vedge_draw_point(context point.x, point.y);
//}



#endif /* __VEDGE__H__ */


