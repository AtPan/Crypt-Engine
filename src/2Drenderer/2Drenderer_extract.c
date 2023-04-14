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

SDL_Window * Crypt_2D_renderer_extract_window(Crypt_2DWindow_t * restrict window) {
    if(window == NULL) return NULL;

    return window->window;
}

SDL_Renderer * Crypt_2D_renderer_extract_renderer(Crypt_2DWindow_t * restrict window) {
    if(window == NULL) return NULL;

    return window->renderer;
}
