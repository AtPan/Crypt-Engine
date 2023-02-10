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

extern struct __memory __memory_buf;

void Crypt_memory_defrag() {
    struct __memory_block * block = (struct __memory_block *)__memory_buf.buf;

    while(block->next != NULL) {
        while(block->next != NULL && block->is_allocated == TRUE) block = block->next;

        while(block->next != NULL && block->next->is_allocated == FALSE) {
            block->block_size += block->next->block_size;
            block->next = block->next->next;
        }
    }
}
