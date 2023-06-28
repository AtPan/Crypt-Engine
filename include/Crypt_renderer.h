/*  This file is part of Crypt Engine.
 *
 *  Crypt Engine is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the Free Software Foundation,
 *  either version 3 of the License, or (at your option) any later version.
 *
 *  Crypt Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with Crypt Engine.
 *  If not, see <https://www.gnu.org/licenses/>.
 *
 *  Copyright 2023 Anthony Panarello
 */

#ifndef __CRYPT_RENDERER_H
#define __CRYPT_RENDERER_H

#include <Crypt_types.h>
#include <Crypt_log.h>
#include <Crypt_utils/internal_renderer.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_error.h>

extern cryptlog_t * restrict __Crypt_2D_renderer_log;

typedef struct __Crypt_2DWindow_opts_t {
    const char * name;
    unsigned int x;
    unsigned int y;
    unsigned int w;
    unsigned int h;
    uint32_t sdl_window_flags;
    Crypt_rgba_color_t default_color;
} Crypt_2DWindow_opts_t;

flag_t Crypt_2D_renderer_init(cryptlog_t * restrict);
void Crypt_2D_renderer_quit(void);
flag_t Crypt_2D_renderer_create_window(Crypt_2DWindow_t * restrict, Crypt_2DWindow_opts_t);
void Crypt_2D_renderer_destroy_window(Crypt_2DWindow_t * restrict);

flag_t Crypt_2D_renderer_draw_surface(Crypt_2DWindow_t * restrict, Crypt_2DSurface_t * restrict, unsigned int, unsigned int);
flag_t Crypt_2D_renderer_create_surface(Crypt_2DSurface_t * restrict, unsigned int, unsigned int);

SDL_Window * Crypt_2D_renderer_extract_window(Crypt_2DWindow_t * restrict);
SDL_Renderer * Crypt_2D_renderer_extract_renderer(Crypt_2DWindow_t * restrict);

#endif
