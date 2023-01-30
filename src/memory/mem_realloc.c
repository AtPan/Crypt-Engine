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
#include <string.h>
#include <stdio.h>

extern struct __memory __memory_buf;

void * Crypt_realloc(void * old_ptr, size_t n) {
    if(old_ptr == NULL) return Crypt_alloc(n);
    if((intptr_t)old_ptr < (intptr_t)__memory_buf.buf || (intptr_t)old_ptr > (intptr_t)__memory_buf.buf + __memory_buf.size) return NULL;

    /* Round n to next block size */
    n = __CRYPT_ROUND_TO_NEXT_BLOCK(n + sizeof(struct __memory_block));

    /* Find the block old_ptr belongs to */
    struct __memory_block * block = (struct __memory_block *)__memory_buf.buf;
    struct __memory_block * old_block = block;

    /* Find block allocated to old_ptr */
    while(block != NULL && (intptr_t)old_ptr > (intptr_t)block) {
        old_block = block;
        block = block->next;
    }

    /* If the block is not allocated, return null */
    if(old_block->is_allocated == FALSE) return NULL;

    /* If the requested size of this block is 0, mark it as available */
    if(n == 0) {
        old_block->is_allocated = FALSE;
        return NULL;
    }

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
        if((old_ptr = Crypt_alloc(n)) == NULL) return NULL;
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
