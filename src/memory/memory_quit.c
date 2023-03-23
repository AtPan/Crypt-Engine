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

#include <Crypt.h>
#include <Crypt_utils/internal_memory.h>
#include <Crypt_utils/internal_resources.h>
#include <stdlib.h>

extern struct __memory __Crypt_memory_buf;

void Crypt_memory_quit() {
    if(__Crypt_memory_buf.buf == NULL) return;

    free(__Crypt_memory_buf.buf);
    __Crypt_memory_buf.buf = NULL;
    __Crypt_memory_buf.allocated = __Crypt_memory_buf.size = 0;

    __Crypt_resources_remove_resource(__Crypt_resource_type_memory);
}
