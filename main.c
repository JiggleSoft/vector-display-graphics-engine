//=============================================================================
// Title:        Vector Display Graphics Engine (vEDGE) - Test Application.
// Filename:     main.c
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


#include <stdio.h>
#include "main.h"
#include "vdraw.h"

#include <math.h>



VedgeContext vedge;

SDL_Window *window;




void game_init(void)
{
    SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO|SDL_INIT_JOYSTICK);

    window = SDL_CreateWindow(
            GAME_WINDOW_TITLE,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            GAME_WINDOW_WIDTH,
            GAME_WINDOW_HEIGHT,
            GAME_WINDOW_FLAGS
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    vmath_init();

    vedge_init(&vedge, renderer);
}

void game_done(void)
{
    vedge_done(&vedge);
    //vmath_done(ved);
    SDL_DestroyWindow(window);
    SDL_Quit();
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


void dump_matrix3x3(char string[8], VmathMatrix3x3 pDouble);

void dump_matrix3x1(char string[8], VmathMatrix3x1 pDouble);

//void draw_number(VdrawContext * vdraw, char ich, VmathNumber rot);
void draw_char(VdrawContext * vdraw, const Vfont * font, char ich, VmathNumber x, VmathNumber y, VmathNumber scale_x, VmathNumber scale_y, VmathNumber rot);

void draw_char2(VdrawContext * vdraw, const Vfont * font, char ich,
                VmathNumber cam_x, VmathNumber cam_y, VmathNumber cam_scale_x, VmathNumber cam_scale_y, VmathNumber cam_rot,
                VmathNumber obj_x, VmathNumber obj_y, VmathNumber obj_scale_x, VmathNumber obj_scale_y, VmathNumber obj_rot);

void collitz();



void dump_matrix3x1(char * msg, VmathMatrix3x1 m) {
    printf("%s\n""%02.2f  %02.2f  %02.2f\n",
           msg, m[0], m[1], m[2]);
}

void dump_matrix3x3(char * msg, VmathMatrix3x3 m) {
    printf("%s\n""%02.2f  %02.2f  %02.2f\n""%02.2f  %02.2f  %02.2f\n""%02.2f  %02.2f  %02.2f\n",
           msg, m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2]);
}



static VmathNumber cam_tx  = VMATHNUMBER_C( 0.0 );
static VmathNumber cam_ty  = VMATHNUMBER_C(  0.0 );
static VmathNumber cam_rot = VMATHNUMBER_C( 0.0 );
static VmathNumber cam_sx  = VMATHNUMBER_C( 1.0 );
static VmathNumber cam_sy  = VMATHNUMBER_C( 1.0 );





int main() {
VedgeGlyph * chara = vfont_get_char(vfont_arcade, 'A');


    game_init();

    VdrawContext * vdraw = &vedge.private_vdraw_context;

    vdraw_set_foreground_colour(vdraw, 255, 255, 255 );
    vdraw_set_background_colour(vdraw, 0, 0, 0);
    vdraw_set_foreground_colour_min_max_enable(vdraw, 0);
    vdraw_clear_screen(vdraw);
    vdraw_flip(vdraw);


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


    char ich = 0x20;

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


        vedge_frame_start(&vedge);

rot += 0.2;


for (int aaa = 0;  aaa < 1;  aaa++) {

z++;
        x += 3;
        c += 8;
        //Clear screen
        vdraw_clear_screen(vdraw);


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

    vdraw_line_intensity(vdraw, A[0], A[1], B[0], B[1], rot / 1000);
    vdraw_line_intensity(vdraw, B[0], B[1], C[0], C[1], rot / 1000);
    vdraw_line_intensity(vdraw, C[0], C[1], A[0], A[1], rot / 1000);


    for (int yyy = 0;  yyy < 8;  yyy++)
    {
        for (int xxx = 0;  xxx < 8;  xxx++)
        {
            draw_char2(vdraw, vfont_arcade, 0x20+yyy*8+xxx,
            cam_tx, cam_ty, cam_sx, cam_sy, cam_rot,
            xxx*130+70, yyy*70+40, 4.0, 8.0, rot);
        }
    }

    cam_rot += 0.5;
    if (cam_rot > 1024.0) { cam_rot = 0.0; }

//    cam_sx += 0.01;
//    if (cam_sx > 20) cam_sx = -5.0;
//    cam_sy += 0.005;
//    if (cam_sy > 20) cam_sy = -51.0;

//    cam_tx += 0.1;
//    if (cam_tx < -400.0) cam_tx = 400;

    //cam_ty -= 0.5;
    //if (cam_ty < -400.0) cam_ty = 400;

    draw_char(vdraw, vfont_arcade, ich, GAME_WINDOW_WIDTH/2, GAME_WINDOW_HEIGHT/2+150, 10.0, 20.0, rot);

    draw_char(vdraw, vfont_arcade, 'L', 100, 690, 3.0, 6.0, rot);
    draw_char(vdraw, vfont_arcade, 'U', 160, 690, 3.0, 6.0, rot);
    draw_char(vdraw, vfont_arcade, 'N', 210, 690, 3.0, 6.0, rot);
    draw_char(vdraw, vfont_arcade, 'A', 270, 690, 3.0, 6.0, rot);
    draw_char(vdraw, vfont_arcade, 'R', 330, 690, 3.0, 6.0, rot);
    draw_char(vdraw, vfont_arcade, ' ', 390, 690, 3.0, 6.0, rot);
    draw_char(vdraw, vfont_arcade, 'L', 450, 690, 3.0, 6.0, rot);
    draw_char(vdraw, vfont_arcade, 'A', 510, 690, 3.0, 6.0, rot);
    draw_char(vdraw, vfont_arcade, 'N', 570, 690, 3.0, 6.0, rot);
    draw_char(vdraw, vfont_arcade, 'D', 630, 690, 3.0, 6.0, rot);
    draw_char(vdraw, vfont_arcade, 'E', 690, 690, 3.0, 6.0, rot);
    draw_char(vdraw, vfont_arcade, 'R', 750, 690, 3.0, 6.0, rot);

    draw_char(vdraw, vfont_arcade, 'J', 100, 610, 3.0, 6.0, rot/2.0);
    draw_char(vdraw, vfont_arcade, 'U', 160, 610, 3.0, 6.0, rot/2.0);
    draw_char(vdraw, vfont_arcade, 'S', 210, 610, 3.0, 6.0, rot/2.0);
    draw_char(vdraw, vfont_arcade, 'T', 270, 610, 3.0, 6.0, rot/2.0);
    draw_char(vdraw, vfont_arcade, 'I', 330, 610, 3.0, 6.0, rot/2.0);
    draw_char(vdraw, vfont_arcade, 'N', 390, 610, 3.0, 6.0, rot/2.0);
    draw_char(vdraw, vfont_arcade, ' ', 450, 610, 3.0, 6.0, rot/2.0);
    draw_char(vdraw, vfont_arcade, 'L', 510, 610, 3.0, 6.0, rot/2.0);
    draw_char(vdraw, vfont_arcade, 'A', 570, 610, 3.0, 6.0, rot/2.0);
    draw_char(vdraw, vfont_arcade, 'N', 630, 610, 3.0, 6.0, rot/2.0);
    draw_char(vdraw, vfont_arcade, 'E', 690, 610, 3.0, 6.0, rot/2.0);
    draw_char(vdraw, vfont_arcade, '!', 750, 610, 3.0, 6.0, rot/2.0);


    //dump_matrix3x3("matrix1", matrix1);
    //dump_matrix3x3("matrix2", matrix2);
    //dump_matrix3x3("matrix3", matrix3);

    //dump_matrix3x1("matrixa", ma);
    //dump_matrix3x1("matrixb", mb);
    //dump_matrix3x1("matrixc", mc);

    //dump_matrix3x1("matrixA", A);
    //dump_matrix3x1("matrixB", B);
    //dump_matrix3x1("matrixC", C);



//    const VedgeGlyph * const linesch = vfont_get_char(vfont_7seg, ich);
//    const VedgeGlyph * const linesch = vfont_get_char(vfont_16seg, ich);
    const VedgeGlyph * const linesch = vfont_get_char(vfont_arcade, ich);

    if (--zch == 0) {
        zch = 256;
    if (++ich > 0x7F || ich < 0) {
        ich = 0x20;
    }
    }
//    ich = 0x21;

    for (int jch = 0; jch < linesch->length; jch++) {
        //printf("linesch=%d\n", linesch);
        //printf("lines length = %d, jch = %d\n", linesch->length, jch);
        //fflush(stdout);
        vdraw_line(vdraw, linesch->lines[jch].x1*30+150, linesch->lines[jch].y1*30+150, linesch->lines[jch].x2*30+150, linesch->lines[jch].y2*30+150);
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
        vdraw_line_intensity(vdraw, xxxxxx+GAME_WINDOW_WIDTH/2, yyyyyy+GAME_WINDOW_HEIGHT/2, xxxxx+GAME_WINDOW_WIDTH/2, yyyyy+GAME_WINDOW_HEIGHT/2, xxxxx/1000);

        VmathNumber xxxx = vmath_mbr_sin(xxx) * GAME_WINDOW_WIDTH / 3;
        VmathNumber yyyy = vmath_mbr_cos(yyy) * GAME_WINDOW_HEIGHT / 3;

        //SDL_SetRenderDrawColor(renderer, z, x, c, SDL_ALPHA_OPAQUE);

        vdraw_line_intensity(vdraw, GAME_WINDOW_WIDTH/2, GAME_WINDOW_HEIGHT/2, xxxx+GAME_WINDOW_WIDTH/2, yyyy+GAME_WINDOW_HEIGHT/2, xxxx/500);

        //SDL_RenderDrawLine(renderer, xxxx + x1, yyyy + y1, xxxx+GAME_WINDOW_WIDTH/2, yyyy+GAME_WINDOW_HEIGHT/2);

        xxx += 2.0f;
        yyy += 1.4f;

        //Render texture to screen
        //SDL_RenderCopy( renderer, gTexture, NULL, NULL );
}
        //Update screen
//        vdraw_flip(vdraw);
        vedge_frame_finish(&vedge);
 //break;
    }




    vdraw_clear_screen(vdraw);
    vdraw_flip(vdraw);

    game_done();
//    SDL_Delay(3000);

    game_done();

    return 0;
}

void draw_char(VdrawContext * vdraw, const Vfont * font, char ich, VmathNumber x, VmathNumber y, VmathNumber scale_x, VmathNumber scale_y, VmathNumber rot) {

    VmathMatrix3x3 matrix1, matrix2, matrix3, matrix4, matrix5;
    vmath_matrix3x3_set_rotation_clockwise(matrix1, rot);
    vmath_matrix3x3_set_translation(matrix2, x, y);
    vmath_matrix3x3_set_scaling(matrix3, scale_x, scale_y);
    vmath_matrix3x3_multiply_matrix3x3(matrix2, matrix1, matrix4);
    vmath_matrix3x3_multiply_matrix3x3(matrix4, matrix3, matrix5);
    VmathMatrix3x1 ma, mb;
    VedgeGlyph *glyph = vfont_get_char(font, ich);
    for (int i = 0; i < glyph->length; i++) {
        ma[0] = glyph->lines[i].x1; ma[1] = glyph->lines[i].y1; ma[2] = 1;
        mb[0] = glyph->lines[i].x2; mb[1] = glyph->lines[i].y2; mb[2] = 1;
        VmathMatrix3x1 A, B;
        vmath_matrix3x3_multiply_matrix3x1(matrix5, ma, A);
        vmath_matrix3x3_multiply_matrix3x1(matrix5, mb, B);
        vdraw_line(vdraw, A[0], A[1], B[0], B[1]);
    }
    SDL_SetRenderDrawColor(vdraw->sdl_renderer, 255, 0, 0, 0);
    SDL_RenderDrawLine(vdraw->sdl_renderer, x-2, y-2, x+2, y+2);
    SDL_RenderDrawLine(vdraw->sdl_renderer, x-2, y+2, x+2, y-2);
}



void draw_char2(VdrawContext * vdraw, const Vfont * font, char ich,
               VmathNumber cam_x, VmathNumber cam_y, VmathNumber cam_scale_x, VmathNumber cam_scale_y, VmathNumber cam_rot,
               VmathNumber obj_x, VmathNumber obj_y, VmathNumber obj_scale_x, VmathNumber obj_scale_y, VmathNumber obj_rot)
{
    VmathMatrix3x3 matrix_cam_translation, matrix_cam_rotation, matrix_cam_scaling, matrix_cam_temp, matrix_cam_combined;
    vmath_matrix3x3_set_translation(matrix_cam_translation, -cam_x, -cam_y); //2
    vmath_matrix3x3_set_rotation_anticlockwise(matrix_cam_rotation, cam_rot); //1
    vmath_matrix3x3_set_scaling(matrix_cam_scaling, cam_scale_x, cam_scale_y);//3
    vmath_matrix3x3_multiply_matrix3x3(matrix_cam_translation, matrix_cam_rotation, matrix_cam_temp);
    vmath_matrix3x3_multiply_matrix3x3(matrix_cam_temp, matrix_cam_scaling, matrix_cam_combined);

    VmathMatrix3x3 matrix_obj_translation, matrix_obj_rotation, matrix_obj_scaling, matrix_obj_temp, matrix_obj_combined;
    vmath_matrix3x3_set_translation(matrix_obj_translation, obj_x, obj_y); //2
    vmath_matrix3x3_set_rotation_clockwise(matrix_obj_rotation, obj_rot); //1
    vmath_matrix3x3_set_scaling(matrix_obj_scaling, obj_scale_x, obj_scale_y);//3
    vmath_matrix3x3_multiply_matrix3x3(matrix_obj_translation, matrix_obj_rotation, matrix_obj_temp);
    vmath_matrix3x3_multiply_matrix3x3(matrix_obj_temp, matrix_obj_scaling, matrix_obj_combined);

    VmathMatrix3x3 matrix_combined;
    vmath_matrix3x3_multiply_matrix3x3(matrix_cam_combined, matrix_obj_combined, matrix_combined);

    dump_matrix3x3("matrix_combined", matrix_combined);

    VmathMatrix3x1 ma, mb;
    VedgeGlyph *glyph = vfont_get_char(font, ich);
    for (int i = 0; i < glyph->length; i++) {
        ma[0] = glyph->lines[i].x1; ma[1] = glyph->lines[i].y1; ma[2] = 1;
        mb[0] = glyph->lines[i].x2; mb[1] = glyph->lines[i].y2; mb[2] = 1;
        VmathMatrix3x1 A, B;
        vmath_matrix3x3_multiply_matrix3x1(matrix_combined, ma, A);
        vmath_matrix3x3_multiply_matrix3x1(matrix_combined, mb, B);
        vdraw_line(vdraw, A[0], A[1], B[0], B[1]);
    }
    SDL_SetRenderDrawColor(vdraw->sdl_renderer, 0, 255, 0, 0);
    SDL_RenderDrawLine(vdraw->sdl_renderer, cam_x-2, cam_y-2, cam_x+2, cam_y+2);
    SDL_RenderDrawLine(vdraw->sdl_renderer, cam_x-2, cam_y+2, cam_x+2, cam_y-2);

    SDL_SetRenderDrawColor(vdraw->sdl_renderer, 0, 0, 255, 0);
    SDL_RenderDrawLine(vdraw->sdl_renderer, cam_x, cam_y, (cos((cam_rot-90.0)/1024.0*6.28)*50)+cam_x, (sin((cam_rot-90.0)/1024.0*6.28)*50)+cam_y);

    SDL_SetRenderDrawColor(vdraw->sdl_renderer, 255, 0, 0, 0);
    SDL_RenderDrawLine(vdraw->sdl_renderer, obj_x-2, obj_y-2, obj_x+2, obj_y+2);
    SDL_RenderDrawLine(vdraw->sdl_renderer, obj_x-2, obj_y+2, obj_x+2, obj_y-2);
}
