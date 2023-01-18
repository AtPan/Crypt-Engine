#include <Crypt_utils/memory.h>
#include <Crypt_utils/memory/structs.h>

extern struct __memory __memory_buf;

void * Crypt_alloc(size_t n) {
    if(n == 0) return NULL;
    n = __CRYPT_ROUND_TO_NEXT_BLOCK(n);

    if(n < __memory_buf.allocated) {
        /* TODO: Expand allocated buffer
         */

        return NULL;
    }

    struct __memory_block * block = (struct __memory_block *)__memory_buf.buf;
    while(block != NULL && block->allocated < n) block = block->next;

    if(block == NULL) return NULL;
}
