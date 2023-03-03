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

/*
 * This module requires, at least, the logging module to function.
 * Without the logging module, debugging cannot occur.
 *
 * The other modules can be checked dynamically.
 */

#ifndef __CRYPT_DEBUG_H
#define __CRYPT_DEBUG_H

/* Needed for common types and internal function definitions */
#include <Crypt.h>
#include <Crypt_utils/debug/memory_func.h>

/* Location of Crypt's debugging log for the memory module */
#define CRYPT_DEBUG_MEMORY_LOG_LOCATION "Crypt_Memory_Log.txt"

/* Defines maximum amount of allocated pointers that can be tracked at once */
#define CRYPT_DEBUG_MEMORY_TABLE_POINTER_SIZE 256

/* Wrapper macros for memory module functions */
#define Crypt_memory_malloc(n) __Crypt_debug_memory_malloc(n, __FILE__, __LINE__)
#define Crypt_memory_realloc(p, n) __Crypt_debug_memory_realloc(p, n, __FILE__, __LINE__)
#define Crypt_memory_free(p) __Crypt_debug_memory_free(p, __FILE__, __LINE__)
#define Crypt_memory_init(n) __Crypt_debug_memory_init(n, __FILE__, __LINE__)
#define Crypt_memory_quit() __Crypt_debug_memory_quit(__FILE__, __LINE__)

#endif
