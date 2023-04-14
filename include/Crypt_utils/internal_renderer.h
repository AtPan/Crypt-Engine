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
#error "Do not include this file directly; include <Crypt_renderer.h>"
#endif

#ifndef __CRYPT_INTERNAL_RENDERER_H
#define __CRYPT_INTERNAL_RENDERER_H

#include <SDL_video.h>
#include <SDL_render.h>
#include <SDL_surface.h>

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
struct __Crypt_rgba_color_t {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};
#elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
struct __Crypt_rgba_color_t {
    unsigned char a;
    unsigned char b;
    unsigned char g;
    unsigned char r;
};
#else
#error "Machines other than big or little endian are not supported"
#endif

typedef union {
    struct __Crypt_rgba_color_t rgba_t;
    unsigned int rgba;
} Crypt_rgba_color_t;

typedef struct __Crypt_2DWindow_t {
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Surface * surface;
    Crypt_rgba_color_t background_color;
} Crypt_2DWindow_t;

typedef struct __Crypt_2DSurface_t {
    SDL_Surface * surface;
} Crypt_2DSurface_t;

#endif
