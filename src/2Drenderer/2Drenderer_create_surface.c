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

#include <Crypt_log.h>
#include <SDL_surface.h>
#include <Crypt_renderer.h>

flag_t Crypt_2D_renderer_create_surface(Crypt_2DSurface_t * restrict surface, unsigned int width, unsigned int height) {
    if(surface == NULL) return FAIL;

    SDL_Surface * sdl_s = SDL_CreateRGBSurface(0, width, height, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
    if(sdl_s == NULL) {
        Crypt_log_write(__Crypt_2D_renderer_log,
                "ERROR: Could not create 2D surface\nError Message: %s\n",
                SDL_GetError());
        return FAIL;
    }
    surface->surface = sdl_s;

    return SUCCESS;
}
