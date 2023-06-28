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

#include <SDL_surface.h>
#include <Crypt_renderer.h>

/* TODO: Check for locked surface before blitting
 */
flag_t Crypt_2D_renderer_draw_surface(Crypt_2DWindow_t * restrict window, Crypt_2DSurface_t * restrict surface, unsigned int x, unsigned int y) {
    int e_code = SDL_BlitSurface(surface->surface, surface->rect, window->surface,
            &((SDL_Rect) {.x = x, .y = y, .w = 0, .h = 0}));

    if(e_code != 0) {
        Crypt_log_write(__Crypt_2D_renderer_log,
                "Crypt_2D_renderer_draw_surface: Error on SDL_BlitSurface with error code %d\nError message: %s\n",
                e_code, SDL_GetError());

        return FAIL;
    }

    return SUCCESS;
}
