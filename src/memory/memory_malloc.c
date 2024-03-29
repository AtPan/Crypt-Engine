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

extern struct __memory __Crypt_memory_buf;

void * Crypt_memory_malloc(size_t n) {
    void * __Crypt_memory_malloc(size_t);
    if(n == 0) return NULL;

    n = __CRYPT_MEMORY_ROUND_TO_NEXT_BLOCK(n + sizeof(struct __memory_block));

    if(n > __Crypt_memory_buf.allocated - __Crypt_memory_buf.size) {
        /* TODO: Expand allocated buffer
         */

        return NULL;
    }

    void * mem;

    if((mem = __Crypt_memory_malloc(n)) == NULL) {
        Crypt_memory_defrag();
        mem = __Crypt_memory_malloc(n);
    }

    return mem;
}

/* This function is what actually tries and allocates memory from the pool.
 *
 * This function should not be used by itself, as there are no failsafes or alignment occuring
 * to avoid repeated operations on failure. If this function is called directly, expect the memory
 * pool to break.
 *
 * @n: The amount of memory to allocate.
 *
 * Returns: NULL on error, otherwise a pointer to allocated memory.
 */
void * __Crypt_memory_malloc(size_t n) {
    struct __memory_block * block = (struct __memory_block *)__Crypt_memory_buf.buf;

    while(block != NULL && (block->is_allocated == TRUE || block->block_size < n)) {
        block = block->next;
    }

    if(block == NULL || block->block_size < n || block->is_allocated == TRUE) return NULL;

    block->is_allocated = TRUE;

    if(block->block_size != n) {
        struct __memory_block * new_block = (struct __memory_block *)((intptr_t)block + n);
        new_block->is_allocated = FALSE;
        new_block->block_size = block->block_size - n;
        new_block->next = block->next;

        block->block_size = n;
        block->next = new_block;
    }

    __Crypt_memory_buf.size += n;

    return (void *)((intptr_t)block + sizeof(struct __memory_block));
}
