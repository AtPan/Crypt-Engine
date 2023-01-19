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
 */


#include <Crypt_utils/memory.h>
#include <Crypt_utils/memory/structs.h>

extern struct __memory __memory_buf;

void * Crypt_alloc(size_t n) {
    if(n == 0) return NULL;
    n = __CRYPT_ROUND_TO_NEXT_BLOCK(n);

    if(n < __memory_buf.allocated) {
        /* TODO: Expand allocated buffer
         */

        return NULL;
    }

    struct __memory_block * block = (struct __memory_block *)__memory_buf.buf;
    while(block != NULL && block->allocated < n) block = block->next;

    if(block == NULL) return NULL;
}
