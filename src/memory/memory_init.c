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

struct __memory __Crypt_memory_buf;

flag_t Crypt_memory_init(size_t n) {
    if(n == 0) {
        n = CRYPT_MEMORY_DEFAULT_ALLOCATION;
    }
    n = __CRYPT_MEMORY_ROUND_TO_NEXT_BLOCK(n);

    __Crypt_memory_buf.size = __Crypt_memory_buf.allocated = 0;
    __Crypt_memory_buf.buf = malloc(n);

    if(__Crypt_memory_buf.buf == NULL) {
        /* TODO: Add error checking and handeling.
         * Keep it similar to C's errno for simplicity.
         */

        return FAIL;
    }

    if(CRYPT_MEMORY_DEFAULT_BLOCK_SIZE <= sizeof(struct __memory_block)
            || CRYPT_MEMORY_DEFAULT_BLOCK_SIZE >= n)
    {
        /* TODO: Add error checking and handleing.
         * Keep it similar to C's errno for simplicity.
         */

        free(__Crypt_memory_buf.buf);
        __Crypt_memory_buf.buf = NULL;
        return FAIL;
    }

    __Crypt_memory_buf.allocated = n;
    struct __memory_block * head = (struct __memory_block *)__Crypt_memory_buf.buf;
    head->block_size = n;
    head->is_allocated = FALSE;
    head->next = NULL;

    __Crypt_resources_add_resource(__Crypt_resource_type_memory, (void *)__Crypt_memory_buf.buf);

    return SUCCESS;
}
