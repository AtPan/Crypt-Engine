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
#include <string.h>

extern struct __memory __Crypt_memory_buf;

/* Attempts to resize a pointer to a given size.
 * The passed pointer must be a pointer returned by Crypt_alloc or from a previous
 * call to Crypt_realloc.
 *
 * If NULL is passed, a new buffer of size n is allocated.
 * If the requested size is 0, NULL is returned.
 *
 * The returned pointer is not guaranteed to be the same as old_ptr.
 * Realloc will attempt to resize in place, but if it cannot then memory will be
 * copied to a new location and that will be returned. For safety, always use the pointer
 * returned instead of old_ptr to avoid using a dead pointer by accident.
 *
 * -old_ptr: The pointer to the buffer to resize.
 * -n: The size to resize to.
 *
 *  Returns: NULL on error, else a pointer to the resized buffer.
 */
void * Crypt_memory_realloc(void * restrict old_ptr, size_t n) {
    /* If old_ptr is null, allocate a new pointer */
    if(old_ptr == NULL) return Crypt_memory_malloc(n);
    /* If old_ptr lies outside of the pool's range, it's not our pointer so return null */
    if((intptr_t)old_ptr < (intptr_t)__Crypt_memory_buf.buf || (intptr_t)old_ptr > (intptr_t)__Crypt_memory_buf.buf + __Crypt_memory_buf.size) return NULL;

    /* Round n to next block size */
    n = __CRYPT_MEMORY_ROUND_TO_NEXT_BLOCK(n + sizeof(struct __memory_block));

    /* Find the block old_ptr belongs to */
    struct __memory_block * block = (struct __memory_block *)__Crypt_memory_buf.buf;
    struct __memory_block * old_block = block;
    while(block != NULL && (intptr_t)old_ptr > (intptr_t)block) {
        old_block = block;
        block = block->next;
    }

    /* If no bytes are to be allocated or block is not allocated, return null */
    if(n == 0 || old_block->is_allocated == FALSE) {
        old_block->is_allocated = FALSE;
        return NULL;
    }

    /* If there is not enough room for reallocation, set error and return null */
    if(__Crypt_memory_buf.allocated - __Crypt_memory_buf.size + old_block->block_size < n) {
        /* TODO: Set error */

        return NULL;
    }

    /* Update master memory structure accordingly */
    __Crypt_memory_buf.size += n - old_block->block_size;

    /* If the same size should be allocated, do nothing */
    if(old_block->block_size == n) return old_ptr;

    /* If a smaller size is requested, shrink the block */
    if(old_block->block_size > n) {
        block = (struct __memory_block *)((intptr_t)old_block + n);
        block->next = old_block->next;
        block->block_size = old_block->block_size - n;
        block->is_allocated = FALSE;

        old_block->block_size = n;
        old_block->next = block;

        return old_ptr;
    }

    /* Otherwise, we must enlargen the allocated space */
    /* Find how much free consecutive space is available after this block */
    size_t count = old_block->block_size;
    while(block != NULL && block->is_allocated == FALSE && count < n) {
        count += block->block_size;
        block = block->next;
    }

    /* If there is a perfect amount of space, assign those blocks to this one */
    if (count == n) {
        old_block->next = (struct __memory_block *)((intptr_t)old_block + count);
        old_block->block_size = n;
    }

    /* If there is too little space, copy memory elsewhere */
    else if(count < n) {
        if((old_ptr = Crypt_memory_malloc(n)) == NULL) return NULL;
        memcpy(old_ptr, (void *)((intptr_t)old_block + sizeof(struct __memory_block)), old_block->block_size - sizeof(struct __memory_block));
        old_block->is_allocated = FALSE;
    }

    /* If there is too much space, slice up the last block */
    else if(count != n) {
        block = (struct __memory_block *)((intptr_t)old_block + n);
        block->is_allocated = FALSE;
        block->next = old_block->next;
        block->block_size = old_block->block_size - n;

        old_block->block_size = n;
        old_block->next = block;
    }

    return old_ptr;
}
