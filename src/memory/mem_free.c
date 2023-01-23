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

void Crypt_free(void *ptr) {
    intptr_t addr = (intptr_t)ptr;
    struct __memory_block * block = (struct __memory_block *)__memory_buf.buf;
    struct __memory_block * parent = block;

    if(addr < (intptr_t)__memory_buf.buf || addr > (intptr_t)__memory_buf.buf + __memory_buf.allocated) return;

    while(block != NULL && addr > (intptr_t)block) {
        parent = block;
        block = block->next;
    }

    if(parent->is_allocated == FALSE) { /* wtf ??? */ return; }

    parent->is_allocated = FALSE;

    __memory_buf.size -= parent->block_size;

    if(block != NULL && block->is_allocated == FALSE) {
        parent->block_size += block->block_size;
        parent->next = block->next;
    }
}
