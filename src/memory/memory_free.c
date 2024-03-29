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
#include <Crypt_memory.h>
#include <Crypt_utils/internal_memory.h>

extern struct __memory __Crypt_memory_buf;

flag_t Crypt_memory_free(void * restrict ptr) {
    intptr_t addr = (intptr_t)ptr;
    struct __memory_block * block = (struct __memory_block *)__Crypt_memory_buf.buf;
    struct __memory_block * parent = block;

    if(ptr == NULL || addr < (intptr_t)__Crypt_memory_buf.buf || addr > (intptr_t)__Crypt_memory_buf.buf + __Crypt_memory_buf.allocated) {
        return FAIL;
    }

    while(block != NULL && addr > (intptr_t)block) {
        parent = block;
        block = block->next;
    }

    if(parent->is_allocated == FALSE) { /* wtf ??? */ return FAIL; }

    parent->is_allocated = FALSE;

    __Crypt_memory_buf.size -= parent->block_size;

    if(block != NULL && block->is_allocated == FALSE) {
        parent->block_size += block->block_size;
        parent->next = block->next;
    }

    return SUCCESS;
}
