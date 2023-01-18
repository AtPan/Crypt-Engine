#ifndef __CRYPT_MEMORY_H
#error "Do not include <memory/structs.h> directly; use <Crypt_utils/memory.h> instead"
#endif

#ifndef __CRYPT_MEMORY_STRUCTS_H
#define __CRYPT_MEMORY_STRUCTS_H

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
 * Allocated: Number of bytes allocated to this block, not including the 'allocated' and 'next' fields.
 * Next: Pointer to the next block, or NULL if there is no next block.
 * Mem: The memory itself.
 */
struct __memory_block {
    size_t allocated;
    struct __memory_block * next;
};

#endif
