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

/* Needed for common enum types */
#include <stddef.h>
#include <Crypt_types.h>

// -------------------------------------------------------------------------
// Macros

/* The default size of the memory pool */
#define CRYPT_MEMORY_DEFAULT_ALLOCATION 1 << 16

/* The default size of a memory block; must always be larger than sizeof(struct __memory_block) */
#define CRYPT_MEMORY_DEFAULT_BLOCK_SIZE 128

// End of Macros
// -------------------------------------------------------------------------



// -------------------------------------------------------------------------
// Initializers and Destructors

/* Initializes the memory module.
 * This must be called before any other memory function is called.
 *
 * Parameters:
 * @n - The starting size of the memory pool. If 0, the default amount is used.
 *
 * Returns:
 * FAIL if an error occured, SUCCESS otherwise.
 *
 * Errors:
 * The initial memory size must be at least one block size, and the block size must be at least sizeof(struct __memory_block).
 * It is not recommended to change the size of the block size, because making it too small could result in unexpected errors.
 */
extern flag_t Crypt_memory_init(size_t n);

/*  Frees all allocated memory from the pool and
 *  resets the master memory struct.
 *
 *  DO NOT use any pointers allocated from Crypt_alloc or Crypt_realloc,
 *  call Crypt_alloc, Crypt_realloc, Crypt_free, Crypt_defrag_memory, or any other
 *  Crypt memory function other than Crypt_init_memory after calling this function.
 */
extern void Crypt_memory_quit(void);

// End of Initializers and Destructors
// --------------------------------------------------------------------------



// --------------------------------------------------------------------------
// Allocators

/* Allocates space from the pool of at least the size requested.
 *
 * Parameters:
 * @n - The requested size of the block.
 *
 * Returns:
 * NULL if there is not enough consecutive memory available or if @n is 0; a pointer to the block otherwise.
 */
extern void * Crypt_memory_malloc(size_t n);

/* Attempts to resize a pointer to a given size.
 * The passed pointer must be a pointer returned by Crypt_alloc or from a previous
 * call to Crypt_realloc.
 *
 * If NULL is passed, a new buffer of size n is allocated.
 * If the requested size is 0, NULL is returned.
 *
 * The returned pointer is not guaranteed to be the same as old_ptr.
 * Realloc will attempt to resize in place, but if it cannot then memory will be
 * copied to a new location and that will be returned. For safety, always use the pointer
 * returned instead of the passed pointer to avoid using a dead pointer by accident.
 *
 * Parameters:
 * @p - The pointer to resize. This pointer must be either NULL, or returned from Crypt_memory_malloc.
 * @n - The requested size to resize the pointer to.
 *
 * Returns:
 * The resized pointer. This will usually be the same as @p, but is not guaranteed to be, and the return value should be used instead.
 */
extern void * Crypt_memory_realloc(void * restrict p, size_t n);

/* Crypt's implementation of free.
 * Attempts to free a block of memory previously allocated to a user.
 *
 * WARNING: Only pointers that have been returned by Crypt_alloc or Crypt_realloc should be
 * used here! This function will check if the pointer passed lies within the pool before doing
 * anything with it.
 *
 * Parameters:
 * @p - The pointer to free. This pointer should not be used after being freed.
 *
 * Returns:
 * This function should always return SUCCESS. If ERROR is returned, report it as a bug.
 */
extern flag_t Crypt_memory_free(void * restrict p);

// End of Allocators
// --------------------------------------------------------------------------


// --------------------------------------------------------------------------
// Memory Support Functions

/* This function attempts to defrag the pool by coalescing all adjacent, unallocated blocks together.
 *
 * When Crypt_memory_malloc fails to find enough consecutive memory to fulfill a request, this function is
 * automatically called in hopes that enough can be squeezed together to fulfill the request.
 *
 * This can be an expensive operation, so its use should be sparse. To help ease the burden carried by this function,
 * Crypt's free tries to condense the next block.
 */
extern void Crypt_memory_defrag(void);

// End of Memory Support Functions
// --------------------------------------------------------------------------

#endif
