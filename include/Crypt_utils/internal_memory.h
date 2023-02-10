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

#ifndef __CRYPT_MEMORY_H
#error "Do not include <Crypt_utils/internal_memory.h> directly; use <Crypt_memory.h> instead"
#endif

#ifndef __CRYPT_MEMORY_INTERNAL_H
#define __CRYPT_MEMORY_INTERNAL_H


/* Rounds a passed number to the next block-aligned integer */
#define __CRYPT_MEMORY_ROUND_TO_NEXT_BLOCK(x) ((x) + CRYPT_MEMORY_DEFAULT_BLOCK_SIZE - \
        ((intptr_t)(x) % CRYPT_MEMORY_DEFAULT_BLOCK_SIZE) % CRYPT_MEMORY_DEFAULT_BLOCK_SIZE)

/* Structure used to represent allocated memory for the engine.
 *
 * Size: Number of bytes currently in use.
 * Allocated: Number of bytes allocated -- Size of the buffer.
 * Buf: The memory itself.
 */
struct __memory {
    size_t size;
    size_t allocated;
    void * buf;
};

/* Structure used to represent a block of allocated memory.
 * Returned by Crypt_alloc.
 *
 * Block Size: Number of bytes allocated to this block, including the space reserved for this structure.
 * Is Allocated: If this block is reserved or free.
 * Next: Pointer to the next block, or NULL if there is no next block.
 */
struct __memory_block {
    size_t block_size;
    bool_t is_allocated;
    struct __memory_block * next;
};


#endif
