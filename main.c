//=============================================================================
// Title:        Vector Display Graphics Engine (vEDGE) - Test Application.
// Filename:     main.c
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


#include <stdio.h>
#include "main.h"
#include "vdraw.h"

#include <math.h>


#define SINUS_SIZE 256

int sinus[SINUS_SIZE];

void game_done();

void init_sinus(void)
{
    for (int i = 0; i < SINUS_SIZE; i++)
    {
        sinus[i] = sin(((double)i) / 57.4d);
    }
}

void game_init(void)
{
    init_sinus();
    vmath_init();
}

void game_done(void) {

}


int lander[] = {};
void renderLander(SDL_Renderer* renderer, int x, int y, int scale, int rotation)
{

}


void renderClosedVector(SDL_Renderer* renderer, int red, int green, int blue, int *lines, int num_lines, int scale, int rotation)
{
    SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
    for (int i = 0;  i < num_lines;  i++)
    {

    }

}


extern void run_all_tests(void);

void dump_matrix3x3(char string[8], VmathMatrix3x3 pDouble);

void dump_matrix3x1(char string[8], VmathMatrix3x1 pDouble);

void draw_number(VdrawContext * vdraw, char ich, VmathNumber rot);

#include "test-vmath.c"


void dump_matrix3x1(char * msg, VmathMatrix3x1 m) {
    printf("%s\n""%02.2f  %02.2f  %02.2f\n",
           msg, m[0], m[1], m[2]);
}

void dump_matrix3x3(char * msg, VmathMatrix3x3 m) {
    printf("%s\n""%02.2f  %02.2f  %02.2f\n""%02.2f  %02.2f  %02.2f\n""%02.2f  %02.2f  %02.2f\n",
           msg, m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2]);
}





int main() {
VedgeLines * chara = vfont_get_ascii_char('A');


    game_init();

    run_all_tests();


//    return 0;
    SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_JOYSTICK);

    SDL_Window *window = SDL_CreateWindow(
            GAME_WINDOW_TITLE,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            GAME_WINDOW_WIDTH,
            GAME_WINDOW_HEIGHT,
            GAME_WINDOW_FLAGS
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    VdrawContext vdraw;
    vdraw_init(&vdraw, renderer);

    vdraw_set_foreground_colour(&vdraw, 255, 255, 255 );
    vdraw_set_background_colour(&vdraw, 0, 0, 0);
    vdraw_set_foreground_colour_min_max_enable(&vdraw, 0);
    vdraw_clear_screen(&vdraw);
    vdraw_flip(&vdraw);


    int x1 = 22;
    int y1 = 321;
    int x2 = 84;
    int y2 = 11;
    int x1d = 5;
    int y1d = -3;
    int x2d = 2;
    int y2d = -3;

    VmathNumber xxx = 0.0f;
    VmathNumber yyy = 0.0f;


int z = 0; int x = 0; int c = 0;
    //Main loop flag
    _Bool quit = 0;

    //Event handler
    SDL_Event e;

    VmathNumber rot = 0.0f;


    char ich = '0';0x20;

    int zch = 255;

    //While application is running
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = 1;
            }
        }


rot += 0.2;


for (int aaa = 0;  aaa < 1;  aaa++) {

z++;
        x += 3;
        c += 8;
        //Clear screen
        vdraw_clear_screen(&vdraw);


    VmathMatrix3x3 matrix1, matrix2, matrix3;
    vmath_matrix3x3_set_rotation_clockwise(matrix1, rot);
    //vmath_matrix3x3_set_identity(matrix1);
    vmath_matrix3x3_set_translation(matrix2, GAME_WINDOW_WIDTH/2+sin(rot/200) * 300, GAME_WINDOW_HEIGHT/2);
    vmath_matrix3x3_multiply_matrix3x3(matrix2, matrix1, matrix3);
    VmathMatrix3x1 ma, mb, mc;
    ma[0] = 100; ma[1] = 100; ma[2] = 1;
    mb[0] = -100; mb[1] = 100; mb[2] = 1;
    mc[0] = 0; mc[1] = -100; mc[2] = 1;
    VmathMatrix3x1 A, B, C;
    vmath_matrix3x3_multiply_matrix3x1(matrix3, ma, A);
    vmath_matrix3x3_multiply_matrix3x1(matrix3, mb, B);
    vmath_matrix3x3_multiply_matrix3x1(matrix3, mc, C);

    vdraw_line_intensity(&vdraw, A[0], A[1], B[0], B[1], rot / 1000);
    vdraw_line_intensity(&vdraw, B[0], B[1], C[0], C[1], rot / 1000);
    vdraw_line_intensity(&vdraw, C[0], C[1], A[0], A[1], rot / 1000);


    draw_number(&vdraw, ich, rot);



    dump_matrix3x3("matrix1", matrix1);
    dump_matrix3x3("matrix2", matrix2);
    dump_matrix3x3("matrix3", matrix3);

    dump_matrix3x1("matrixa", ma);
    dump_matrix3x1("matrixb", mb);
    dump_matrix3x1("matrixc", mc);

    dump_matrix3x1("matrixA", A);
    dump_matrix3x1("matrixB", B);
    dump_matrix3x1("matrixC", C);



    VedgeLines * linesch = vfont_get_ascii_char(ich);

    if (--zch == 0) {
        zch = 256;
    if (++ich > '9') {//0x5F) {
        ich = '0';//0x20;
    }
    }
//    ich = 0x21;

    for (int jch = 0; jch < linesch->length; jch++) {
        //printf("linesch=%d\n", linesch);
        printf("lines length = %d, jch = %d\n", linesch->length, jch);
        fflush(stdout);
        vdraw_line(&vdraw, linesch->lines[jch].x1*30+150, linesch->lines[jch].y1*30+150, linesch->lines[jch].x2*30+150, linesch->lines[jch].y2*30+150);
    }


    x1 = x1 + x1d;
        y1 = y1 + y1d;
        x2 = x2 + x2d;
        y2 = y2 + y2d;
        if (x1< 5) x1d = -x1d;
        if (x1> (GAME_WINDOW_WIDTH-5)) x1d = -x1d;
        if (y1< 5) y1d = -y1d;
        if (y1> (GAME_WINDOW_HEIGHT-5)) y1d = -y1d;
        if (x2< 5) x2d = -x2d;
        if (x2> (GAME_WINDOW_WIDTH-5)) x2d = -x2d;
        if (y2< 5) y2d = -y2d;
        if (y2> (GAME_WINDOW_HEIGHT-5)) y2d = -y2d;
        //SDL_SetRenderDrawColor(renderer, z, x, c, SDL_ALPHA_OPAQUE);

        //SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        //SDL_SetRenderDrawColor(renderer, z, 0, 0, SDL_ALPHA_OPAQUE);
        //SDL_RenderDrawLine(renderer, GAME_WINDOW_WIDTH-x1, GAME_WINDOW_HEIGHT-y1, x2+1, y2+1);
        //SDL_SetRenderDrawColor(renderer, 0, x, 0, SDL_ALPHA_OPAQUE);
        //SDL_RenderDrawLine(renderer, x1, GAME_WINDOW_HEIGHT-y1, GAME_WINDOW_WIDTH-x2+1, y2+1);
        //SDL_SetRenderDrawColor(renderer, 0, 0, c, SDL_ALPHA_OPAQUE);
        //SDL_RenderDrawLine(renderer, x1, y1, GAME_WINDOW_WIDTH-x2+1, GAME_WINDOW_HEIGHT-y2+1);

        //SDL_SetRenderDrawColor(renderer, z+128, x+128, c+128, SDL_ALPHA_OPAQUE);

        VmathNumber xxxxx = vmath_mbr_sin(yyy) * GAME_WINDOW_WIDTH / 3;
        VmathNumber yyyyy = vmath_mbr_cos(xxx) * GAME_WINDOW_HEIGHT / 3;
        VmathNumber xxxxxx = vmath_mbr_sin(xxx) * GAME_WINDOW_WIDTH / 8;
        VmathNumber yyyyyy = vmath_mbr_cos(xxx) * GAME_WINDOW_HEIGHT / 8;
        vdraw_line_intensity(&vdraw, xxxxxx+GAME_WINDOW_WIDTH/2, yyyyyy+GAME_WINDOW_HEIGHT/2, xxxxx+GAME_WINDOW_WIDTH/2, yyyyy+GAME_WINDOW_HEIGHT/2, xxxxx/1000);

        VmathNumber xxxx = vmath_mbr_sin(xxx) * GAME_WINDOW_WIDTH / 3;
        VmathNumber yyyy = vmath_mbr_cos(yyy) * GAME_WINDOW_HEIGHT / 3;

        //SDL_SetRenderDrawColor(renderer, z, x, c, SDL_ALPHA_OPAQUE);

        vdraw_line_intensity(&vdraw, GAME_WINDOW_WIDTH/2, GAME_WINDOW_HEIGHT/2, xxxx+GAME_WINDOW_WIDTH/2, yyyy+GAME_WINDOW_HEIGHT/2, xxxx/500);

        //SDL_RenderDrawLine(renderer, xxxx + x1, yyyy + y1, xxxx+GAME_WINDOW_WIDTH/2, yyyy+GAME_WINDOW_HEIGHT/2);

        xxx += 2.0f;
        yyy += 1.4f;

        //Render texture to screen
        //SDL_RenderCopy( renderer, gTexture, NULL, NULL );
}
        //Update screen
        vdraw_flip(&vdraw);
 //break;
    }




    vdraw_clear_screen(&vdraw);
    vdraw_flip(&vdraw);

    game_done();
//    SDL_Delay(3000);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void draw_number(VdrawContext * vdraw, char ich, VmathNumber rot) {

    VmathMatrix3x3 matrix1, matrix2, matrix3, matrix4, matrix5;
    vmath_matrix3x3_set_rotation_clockwise(matrix1, rot);
    vmath_matrix3x3_set_translation(matrix2, GAME_WINDOW_WIDTH/2, GAME_WINDOW_HEIGHT/2 + 150);
    vmath_matrix3x3_set_scaling(matrix3, 10.0, 20.0);
    vmath_matrix3x3_multiply_matrix3x3(matrix2, matrix1, matrix4);
    vmath_matrix3x3_multiply_matrix3x3(matrix4, matrix3, matrix5);
    VmathMatrix3x1 ma, mb;
    VedgeLines *glyph = vfont_get_ascii_char(ich);
    for (int i = 0; i < glyph->length; i++) {
        ma[0] = glyph->lines[i].x1; ma[1] = glyph->lines[i].y1; ma[2] = 1;
        mb[0] = glyph->lines[i].x2; mb[1] = glyph->lines[i].y2; mb[2] = 1;
        VmathMatrix3x1 A, B;
        vmath_matrix3x3_multiply_matrix3x1(matrix5, ma, A);
        vmath_matrix3x3_multiply_matrix3x1(matrix5, mb, B);
        vdraw_line(vdraw, A[0], A[1], B[0], B[1]);
    }
}



