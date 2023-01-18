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
