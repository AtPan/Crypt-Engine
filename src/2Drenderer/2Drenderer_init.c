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

#include <SDL_error.h>
#include <SDL.h>
#include <Crypt_renderer.h>

Crypt_2DWindow_t * Crypt_main_window = NULL;
cryptlog_t * __Crypt_2D_renderer_log = NULL;

flag_t Crypt_2D_renderer_init() {
    if(Crypt_log_init(__Crypt_2D_renderer_log, "Crypt_renderer.txt") == FAIL) {
        return FAIL;
    }

    int e_code;
    if((e_code = SDL_Init(SDL_INIT_VIDEO)) < 0) {
        Crypt_log_write(__Crypt_2D_renderer_log,
                "FATAL: Error initializing SDL_VIDEO subsystem.\nError Code: %d\nError Message: %s\n",
                e_code, SDL_GetError());

        Crypt_log_quit(__Crypt_2D_renderer_log);
        return FAIL;
    }

    Crypt_log_write(__Crypt_2D_renderer_log, "Successfully initialized SDL_VIDEO subsystem.\n");

    return SUCCESS;
}
