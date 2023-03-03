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

#ifndef __CRYPT_DEBUG_H
#error "Do not include this file directly; use <Crypt_debug.h> instead"
#endif

#ifndef __CRYPT_DEBUG_MEMORY_INTERNAL_H
#define __CRYPT_DEBUG_MEMORY_INTERNAL_H

/* Needed for common types */
#include <Crypt.h>

// ------------------------------------------------------------------------------------------------
// Initializers and Destructors

/* A debug wrapper for Crypt_memory_init(n). This function will call and return Crypt_memory_init(n).
 * This function initializes debugging of the memory module.
 * The memory module must be included for this function to work.
 *
 * Parameters:
 * @n - The initial size of the pool to allocate. Passed to Crypt_memory_init.
 * @f - The name of the file calling this funciton.
 * @l - The line number this function is called on.
 *
 * Returns:
 * FAIL if an error occured, SUCCESS otherwise.
 */
extern flag_t __Crypt_debug_memory_init(size_t n, const char * f, unsigned int l);

/* A debug wrapper for Crypt_memory_quit(). This function will call Crypt_memory_quit().
 *
 * Parameters:
 * @f - The name of the file calling this funciton.
 * @l - The line number this function is called on.
 */
extern void __Crypt_debug_memory_quit(const char * f, unsigned int l);

// End of Initializers and Destructors
// ------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// Allocators

/* A debug wrapper for Crypt_memory_malloc(n). This function will call and return Crypt_memory_malloc(n),
 * while logging the file, line, calling parameters, and return values.
 *
 * Parameters:
 * @n - The size of the buffer to allocate. Passed to Crypt_memory_malloc.
 * @f - The name of the calling file.
 * @l - The line number this function is called on.
 *
 * Returns:
 * A pointer to the allocated buffer, or NULL on error.
 *
 * See Crypt_memory_malloc for more information.
 */
extern void * __Crypt_debug_memory_malloc(size_t n, const char * f, unsigned int l);

/* A debug wrapper for Crypt_memory_realloc(p, n). This function will call and return Crypt_memory_realloc(p, n),
 * while logging the file, line, calling parameters, and return values.
 *
 * Parameters:
 * @p - A pointer to the buffer to resize. Passed to Crypt_memory_realloc.
 * @n - The size of the buffer to allocate. Passed to Crypt_memory_realloc.
 * @f - The name of the calling file.
 * @l - The line number this function is called on.
 *
 * Returns:
 * A pointer to the resized buffer.
 */
extern void * __Crypt_debug_memory_realloc(void * restrict p, size_t n, const char * f, unsigned int l);

/* A debug wrapper for Crypt_memory_free(p). This function will call and return Crypt_memory_free(p).
 * while logging the file, line, calling parameters, and return values.
 *
 * Parameters:
 * @p - A pointer to the buffer to free. Passed to Crypt_memory_free.
 * @f - The name of the calling file.
 * @l - The line number this function is called on.
 *
 * Returns:
 * Should always return SUCCESS.
 * See Crypt_memory_free for more information.
 */
extern flag_t __Crypt_debug_memory_free(void * restrict p, const char * f, unsigned int l);

// End of Allocators
// ------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------
// Memory Debug Support Functions

/* Adds a pointer to the internal pointer table.
 * The internal pointer table is checked upon termination of the memory module.
 * If the table is not empty, the details are logged.
 */
extern void __Crypt_debug_memory_add_ptr_to_table(void * restrict p, size_t n, const char * f, unsigned int l);

/* Removes a pointer to the internal pointer table.
 * The internal pointer table is checked upon termination of the memory module.
 * If the table is not empty, the details are logged.
 */
extern void __Crypt_debug_memory_remove_ptr_from_table(void * restrict p);

// End of Memory Debug Support Functions
// ------------------------------------------------------------------------------------------------

#endif
