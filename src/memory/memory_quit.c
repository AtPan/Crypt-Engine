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

#include <Crypt_memory.h>
#include <Crypt_utils/internal_memory.h>
#include <stdlib.h>

extern struct __memory __memory_buf;

/*  Frees all allocated memory from the pool and
 *  resets the master memory struct.
 *
 *  DO NOT use any pointers allocated from Crypt_alloc or Crypt_realloc,
 *  call Crypt_alloc, Crypt_realloc, Crypt_free, Crypt_defrag_memory, or any other
 *  Crypt memory function other than Crypt_init_memory after calling this function.
 */
void Crypt_memory_quit() {
    if(__memory_buf.buf == NULL) return;

    free(__memory_buf.buf);
    __memory_buf.buf = NULL;
    __memory_buf.allocated = __memory_buf.size = 0;
}
