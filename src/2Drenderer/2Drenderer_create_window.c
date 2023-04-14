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

#include <SDL_render.h>
#include <Crypt_renderer.h>

flag_t Crypt_2D_renderer_create_window(Crypt_2DWindow_t * restrict window, Crypt_2DWindow_opts_t window_opts) {
    if(window == NULL) return FAIL;

    window->background_color = window_opts.default_color;

    SDL_Window * sdl_w = SDL_CreateWindow(window_opts.name,
            window_opts.x, window_opts.y, window_opts.w, window_opts.h, window_opts.sdl_window_flags);
    if(sdl_w == NULL) {
        Crypt_log_write(__Crypt_2D_renderer_log,
                "ERROR: Could not open 2D rendering window\nError Message: %s\n",
                SDL_GetError());
        return FAIL;
    }
    window->window = sdl_w;

    SDL_Renderer * sdl_r = SDL_CreateRenderer(sdl_w, -1, SDL_RENDERER_ACCELERATED);
    if((window->renderer = sdl_r) == NULL) {
        Crypt_log_write(__Crypt_2D_renderer_log,
                "ERROR: Could not open 2D rendering renderer\nError Message: %s\n",
                SDL_GetError());
        goto renderer_create_fail;
    }

    if((window->surface = SDL_GetWindowSurface(sdl_w)) == NULL) {
        Crypt_log_write(__Crypt_2D_renderer_log,
                "ERROR: Could not get 2D surface of window\nError Message: %s\n",
                SDL_GetError());
        goto surface_create_fail;
    }

    SDL_SetRenderDrawColor(sdl_r,
            window_opts.default_color.rgba_t.r, window_opts.default_color.rgba_t.g,
            window_opts.default_color.rgba_t.b, window_opts.default_color.rgba_t.a);

    if(SDL_SetRenderDrawBlendMode(sdl_r, SDL_BLENDMODE_BLEND) < 0) {
        Crypt_log_write(__Crypt_2D_renderer_log,
                "WARNING: Error on setting alpha blend mode for renderer\nError Message: %s\n",
                SDL_GetError());
    }

    return SUCCESS;

surface_create_fail:
    SDL_DestroyRenderer(sdl_r);

renderer_create_fail:
    SDL_DestroyWindow(sdl_w);

    return FAIL;
}
