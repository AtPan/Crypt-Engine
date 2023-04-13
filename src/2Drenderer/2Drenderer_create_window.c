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

#include <Crypt_renderer.h>

flag_t Crypt_2D_renderer_create_window(Crypt_2DWindow_t ** restrict window, Crypt_2DWindow_opts_t window_opts) {
    if(window == NULL) return FAIL;

    Crypt_2DWindow_t * l_window = SDL_CreateWindow(window_opts.name,
            window_opts.x, window_opts.y, window_opts.w, window_opts.h, window_opts.flags);

    if((*window = l_window) == NULL) {
        Crypt_log_write(__Crypt_2D_renderer_log,
                "ERROR: Could not open 2D rendering window\nError Message: %s\n",
                SDL_GetError());
        return FAIL;
    }

    return SUCCESS;
}
