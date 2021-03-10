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


#include "vedge.h"


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
// Lifecycle Management Functions.
//-----------------------------------------------------------------------------

// .
int vedge_init(VedgeContext * context, SDL_Renderer * sdl_renderer)
{
    memset(context, 0, sizeof(VedgeContext));
    context->sdl_renderer = sdl_renderer;
    context->vdraw_context = &context->private_vdraw_context;
    vedge_clear_error_code(context);
    vdraw_init(context->vdraw_context, sdl_renderer);


//    vedge_frame_start(context);
//    vedge_frame_finish(context);
//    vdraw_set_foreground_colour(vdraw, 255, 255, 255 );
//    vdraw_set_background_colour(vdraw, 0, 0, 0);
//    vdraw_set_foreground_colour_min_max_enable(vdraw, 0);
//    vdraw_clear_screen(vdraw);
//    vdraw_flip(vdraw);

}


// .
void vedge_done(VedgeContext * vedge)
{
    vdraw_done(vedge->vdraw_context);
}



//-----------------------------------------------------------------------------
// Error Handling Functions.
//-----------------------------------------------------------------------------

// Clear the last error code.
void vedge_clear_error_code(VedgeContext *vedge)
{
    vedge->vedge_error_code = VEDGE_NO_ERROR;
    vedge->vedge_error_message = vedge_error_messages[VEDGE_NO_ERROR];
}


// Get the last error code.
int vedge_get_error_code(const VedgeContext *vedge)
{
    return vedge->vedge_error_code;
}


// Get the last error message.
const char * vedge_get_error_message(const VedgeContext *vedge)
{
    return vedge->vedge_error_message;
}


void vedge_set_error_code(VedgeContext * vedge, const int error_code)
{
    vedge->vedge_error_code = error_code;
    if (error_code >= 0 || error_code < countof(vedge_error_messages)) {
        vedge->vedge_error_message = vedge_error_messages[error_code];
    } else {
        sprintf(vedge->private_vdraw_error_message, "Unknown error %d", error_code);
        vedge->vedge_error_message = vedge->private_vdraw_error_message;
    }
}


void vedge_set_error(VedgeContext * vedge, const int error_code, const char * error_message)
{
    vedge->vedge_error_code = error_code;
    strncpy(vedge->private_vdraw_error_message, error_message, VDRAW_ERROR_MESSAGE_LENGTH_MAX);
    vedge->private_vdraw_error_message[VDRAW_ERROR_MESSAGE_LENGTH_MAX-1] = '\0';
    vedge->vedge_error_message = vedge->private_vdraw_error_message;
}



//-----------------------------------------------------------------------------
// .....
//-----------------------------------------------------------------------------


void vedge_frame_start(VedgeContext * context)
{
    vdraw_clear_screen(context->vdraw_context);
}


void vedge_frame_finish(VedgeContext * context)
{
    vdraw_flip(context->vdraw_context);
}


void vedge_frame_add_game_object(VedgeContext * context, const VedgeGameObject game_object)
{

}



