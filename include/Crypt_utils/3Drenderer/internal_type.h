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

#ifndef __CRYPT_3D_RENDERER_H
#error "Do not include this header directly; include <Crypt_3D.h> instead"
#endif

#ifndef __CRYPT_3D_RENDERER_INTERNAL_TYPE_H
#define __CRYPT_3D_RENDERER_INTERNAL_TYPE_H

#include <Crypt_types.h>
#include <SDL_video.h>
#include <SDL.h>

struct __Crypt_3D_window_t {
    unsigned int width;
    unsigned int height;
    SDL_Window * sdl_window;
    SDL_Renderer * sdl_renderer;
    struct __Crypt_3D_camera_t * camera;
};
struct __Crypt_3D_camera_t {
    float focal_length;
    float camera_angle_width;
    float camera_angle;
    vector3_t camera_position;
    float camera_aspect_ratio;
};

#endif
