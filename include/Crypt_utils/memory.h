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


#ifndef __CRYPT_MEMORY_H
#define __CRYPT_MEMORY_H

/* Needed for common types like size_t and intptr_t */
#include <stddef.h>
#include <stdint.h>

/* Needed for common enum types */
#include "definitions.h"

/* The default size of a block. Should always be greater than sizeof(struct __memory_block) */
#define __CRYPT_DEFAULT_BLOCK_SIZE 128

/* The default size of the memory pool */
#define __CRYPT_DEFAULT_MEMORY_ALLOCATION 1 << 16

/* Rounds a passed number to the next block-aligned integer */
#define __CRYPT_ROUND_TO_NEXT_BLOCK(x) ((x) + __CRYPT_DEFAULT_BLOCK_SIZE - \
        ((intptr_t)(x) % __CRYPT_DEFAULT_BLOCK_SIZE) % __CRYPT_DEFAULT_BLOCK_SIZE)

FLAG Crypt_init_memory(size_t);
void * Crypt_alloc(size_t);
FLAG Crypt_free(void *);
void Crypt_defrag_memory(void);
void * Crypt_realloc(void *, size_t);

#endif
