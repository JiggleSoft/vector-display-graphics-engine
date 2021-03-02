//=============================================================================
// Title:        VEctor Display Graphics Engine (vEdge).
// Filename:     vedge.c
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (atari@jigglesoft.co.uk)
// Date:         2021-01-24 19:27
// Version:      0.0.1
//-----------------------------------------------------------------------------
// Copyright (c) 2020 Justin Lane
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





//-----------------------------------------------------------------------------
// Error Messages.
//-----------------------------------------------------------------------------
const char * vedge_error_messages[] = {
        "No error",
        "Context is NULL"
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

}


// .
void vedge_done(VedgeContext * vedge)
{

}



//-----------------------------------------------------------------------------
// Error Handling Functions.
//-----------------------------------------------------------------------------

int vedge_clear_error_code(VedgeContext *vedge)
{

}

int vedge_get_error_code(const VedgeContext *vedge)
{

}


const char * vedge_get_error_message(const VedgeContext *vedge)
{
    if (vedge == NULL) {
  //FIXME      return vedge_get_error_code_message(ERR_NULL_CONTEXT_GET_ERROR_MESSAGE);
    }
    //FIXME return vedge_get_error_code_message(vedge);
    return 0L;
}


//-----------------------------------------------------------------------------
// .....
//-----------------------------------------------------------------------------


