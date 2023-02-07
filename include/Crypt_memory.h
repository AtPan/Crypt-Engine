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
#define __CRYPT_MEMORY_H

/* Needed for common types like size_t and intptr_t */
#include <stddef.h>
#include <stdint.h>

/* Needed for common enum types */
#include "Crypt.h"

flag_t Crypt_memory_init(size_t);
void * Crypt_memory_malloc(size_t);
flag_t Crypt_memory_free(void *);
void Crypt_memory_defrag(void);
void * Crypt_memory_realloc(void *, size_t);

#endif
