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
#define __CRYPT_3D_RENDERER_H

#include <Crypt.h>
#include <Crypt_log.h>
#include <Crypt_utils/3Drenderer/internal_type.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_video.h>
#include <SDL2/SDL_image.h>

#define CRYPT_3D_RENDERER_LOG_PATH "log/3D_rendering.txt"

/* How long the screen is, in world units. This is done to keep scaling correct across different resolutions.
 * Screen height can be computed using the aspect ratio of the camera rendering the scene.
 */
#define SCREEN_LENGTH_IN_WORLD_UNITS 20.0

typedef struct __Crypt_3D_camera_t Crypt_3D_camera_t;
typedef struct __Crypt_3D_window_t Crypt_3D_window_t;
typedef struct __Crypt_3D_object_t Crypt_3D_object_t;

typedef struct {
    const char * restrict window_title;
    vector2_t window_position;
    int window_width;
    int window_height;
    int sdl_flags;
} Crypt_3D_window_flags_t;

extern cryptlog_t * restrict __Crypt_3D_renderer_log;

extern flag_t Crypt_3D_init(void);
extern Crypt_3D_camera_t * Crypt_3D_init_camera(Crypt_3D_camera_t * restrict, float focal_length, float camera_angle_width, float camera_render_distance);
extern Crypt_3D_window_t * Crypt_3D_create_window(Crypt_3D_window_t * restrict, Crypt_3D_camera_t * restrict, Crypt_3D_window_flags_t);
extern void Crypt_3D_destroy_window(Crypt_3D_window_t * restrict);
extern void Crypt_3D_quit(void);

#endif
