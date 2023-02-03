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

/* Crypt_free
 * ----------------------------------
 * Crypt's implementation of free.
 * Attempts to free a block of memory previously allocated to a user.
 *
 * WARNING: Only pointers that have been returned by Crypt_alloc or Crypt_realloc should be
 * used here! This function will check if the pointer passed lies within the pool before doing
 * anything with it.
 *
 * -ptr: The pointer to free. Must be one returned by Crypt_alloc or Crypt_realloc.
 */
FLAG Crypt_free(void *ptr) {
    intptr_t addr = (intptr_t)ptr;
    struct __memory_block * block = (struct __memory_block *)__memory_buf.buf;
    struct __memory_block * parent = block;

    if(ptr == NULL || addr < (intptr_t)__memory_buf.buf || addr > (intptr_t)__memory_buf.buf + __memory_buf.allocated) {
        return FAIL;
    }

    while(block != NULL && addr > (intptr_t)block) {
        parent = block;
        block = block->next;
    }

    if(parent->is_allocated == FALSE) { /* wtf ??? */ return FAIL; }

    parent->is_allocated = FALSE;

    __memory_buf.size -= parent->block_size;

    if(block != NULL && block->is_allocated == FALSE) {
        parent->block_size += block->block_size;
        parent->next = block->next;
    }

    return SUCCESS;
}
