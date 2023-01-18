#include <Crypt_utils/memory.h>
#include <Crypt_utils/memory/structs.h>
#include <stdlib.h>

struct __memory __memory_buf;

FLAG Crypt_init_memory(size_t n) {
    if(n == 0) {
        n = __CRYPT_DEFAULT_MEMORY_ALLOCATION;
    }
    n = __CRYPT_ROUND_TO_NEXT_BLOCK(n);

    __memory_buf.size = __memory_buf.allocated = 0;
    __memory_buf.buf = malloc(n);

    if(__memory_buf.buf == NULL) {
        /* TODO: Add error checking and handleing.
         * Keep it similar to C's errno for simplicity.
         */

        return FAIL;
    }

    __memory_buf.allocated = n;

    for(struct __memory_block * block = (struct __memory_block *) __memory_buf.buf;
            block != NULL && (size_t)block < (size_t)__memory_buf.buf + __memory_buf.allocated;
            block = block->next) {
        block->allocated = __CRYPT_DEFAULT_BLOCK_SIZE;
        block->next = (struct __memory_block *)((size_t)block + block->allocated + sizeof(struct __memory_block));
    }

    return SUCCESS;
}
