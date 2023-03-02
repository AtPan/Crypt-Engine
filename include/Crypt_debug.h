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

#include <Crypt.h>
#include <Crypt_utils/debug/memory_func.h>

#define CRYPT_DEBUG_MEMORY_LOG_LOCATION "Crypt_Memory_Log.txt"

#define CRYPT_DEBUG_MEMORY_TABLE_POINTER_SIZE 256

#define Crypt_memory_malloc(n) __Crypt_debug_memory_malloc(n, __FILE__, __LINE__)
#define Crypt_memory_realloc(p, n) __Crypt_debug_memory_realloc(p, n, __FILE__, __LINE__)
#define Crypt_memory_free(p) __Crypt_debug_memory_free(p, __FILE__, __LINE__)

/* Initializes debugging for the memory module.
 * If this function is not called, there will be no debugging information or support
 * available for the memory module.
 *
 * Crypt_memory_init must be called and return successfully before this function is called.
 *
 * Returns:
 * A flag marking whether debugging was successfully initialized for the memory module or not.
 * FAIL if Crypt_memory_init was not called, or returned an error. SUCCESS otherwise.
 */
extern flag_t Crypt_debug_memory(void);

#endif
