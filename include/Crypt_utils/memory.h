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

#include <stddef.h>
#include "definitions.h"

#define __CRYPT_DEFAULT_BLOCK_SIZE 128
#define __CRYPT_DEFAULT_MEMORY_ALLOCATION 1 << 16
#define __CRYPT_ROUND_TO_NEXT_BLOCK(x) ((x) + (sizeof(struct __memory_block) - ((size_t)(x) % sizeof(struct __memory_block))) % sizeof(struct __memory_block))
#define __CRYPT_POINTER_AS_INT(x) (size_t)(x)
#define __CRYPT_INT_AS_POINTER(x, type) (type *)(x)

FLAG Crypt_init_memory(size_t n);

#endif
