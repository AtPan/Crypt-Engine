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

#include <Crypt_utils/memory.h>
#include <Crypt_utils/memory/structs.h>
#include <stdlib.h>

struct __memory __memory_buf;

/* Crypt_init_memory
 * -----------------------------------
 * Initializes Crypt's memory management and pool.
 *
 * Must be called before any other Crypt memory function is,
 * otherwise expect undefined behavior.
 *
 * -n: The size of the pool. If 0, the default amount will be chosen instead.
 *
 *  Returns: FAIL on an error, SUCCESS otherwise.
 */
FLAG Crypt_init_memory(size_t n) {
    if(n == 0) {
        n = __CRYPT_DEFAULT_MEMORY_ALLOCATION;
    }
    n = __CRYPT_ROUND_TO_NEXT_BLOCK(n);

    __memory_buf.size = __memory_buf.allocated = 0;
    __memory_buf.buf = malloc(n);

    if(__memory_buf.buf == NULL) {
        /* TODO: Add error checking and handeling.
         * Keep it similar to C's errno for simplicity.
         */

        return FAIL;
    }

    if(__CRYPT_DEFAULT_BLOCK_SIZE <= sizeof(struct __memory_block)
            || __CRYPT_DEFAULT_BLOCK_SIZE >= n)
    {
        /* TODO: Add error checking and handleing.
         * Keep it similar to C's errno for simplicity.
         */

        free(__memory_buf.buf);
        __memory_buf.buf = NULL;
        return FAIL;
    }

    __memory_buf.allocated = n;
    struct __memory_block * head = (struct __memory_block *)__memory_buf.buf;
    head->block_size = n;
    head->is_allocated = FALSE;
    head->next = NULL;

    return SUCCESS;
}
