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

#include <Crypt_3D.h>
#include <Crypt_utils/3Drenderer/internal_type.h>

Crypt_3D_window_t * Crypt_3D_create_window(Crypt_3D_window_t * restrict window,
        Crypt_3D_camera_t * restrict camera,
        Crypt_3D_window_flags_t flags) {
    if(window == NULL || camera == NULL) return NULL;

    SDL_Window * sdl_window = SDL_CreateWindow(flags.window_title,
            flags.window_position.x,
            flags.window_position.y,
            flags.window_width,
            flags.window_height,
            flags.sdl_flags);
    SDL_Renderer * sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_SOFTWARE);
    if(sdl_window == NULL) {
        return NULL;
    }

    window->sdl_window = sdl_window;
    window->width = flags.window_width;
    window->height = flags.window_height;
    window->sdl_renderer = sdl_renderer;

    window->camera = camera;
    window->camera->camera_angle = 0.0;
    window->camera->camera_position = (vector3_t){.x = 0.0, .y = 0.0, .z = 0.0};
    window->camera->camera_aspect_ratio = (float)flags.window_width / flags.window_height;

    return window;
}
