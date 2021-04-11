//=============================================================================
// Title:        Vector Display Graphics Engine (vEDGE) - Test Application.
// Filename:     main.c
// Platform:     Any supported by SDL version 2.
// Language:     ANSI C99
// Author:       Justin Lane (vedge@jigglesoft.co.uk)
// Date:         2021-03-25 21:38
// Version:      1.0.0-alpha-1
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


#include <SDL.h>

#include "sdl2boot.h"
#include "vedge.h"



static Sdl2BootConfig sdl2boot_config;

static Sdl2BootContext sdl2boot;


static VedgeConfig vedge_config;

static VedgeContext vedge;



int main(int argc, char * argv[])
{
#ifndef NDEBUG
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
#endif
    sdl2boot_config_primary_desktop(&sdl2boot_config,
                                    VEDGE_SDL_INIT,
                                    VEDGE_TITLE,
                                    VEDGE_SDL_WINDOW_FLAGS,
                                    VEDGE_SDL_RENDERER_FLAGS);
    if (sdl2boot_init(&sdl2boot, &sdl2boot_config))
    {
        vedge_config_sdl2boot(&vedge_config, &sdl2boot);
        //FIXME: !!!vedge_add_handler(&vedge, )
        if (vedge_init(&vedge, &vedge_config))
        {
            vedge_run(&vedge);
            vedge_done(&vedge);
        }
        sdl2boot_done(&sdl2boot);
    }
    return 0;
}


int game_init(VedgeContext vedge)
{

}
