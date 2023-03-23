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

#include <Crypt.h>
#include <Crypt_types.h>
#include <Crypt_debug.h>
#include <Crypt_utils/debug/memory_func.h>
#include <Crypt_utils/internal_resources.h>
#include <Crypt_utils/internal_log.h>

#undef Crypt_memory_malloc
#undef Crypt_memory_realloc
#undef Crypt_memory_free
#undef Crypt_memory_init
#undef Crypt_memory_quit

struct __Crypt_pointer_table_entry {
    intptr_t ptr;
    size_t n;
    const char * f;
    unsigned int l;
};

static struct __Crypt_pointer_table_entry __Crypt_pointer_table[CRYPT_DEBUG_MEMORY_TABLE_POINTER_SIZE];
static size_t __Crypt_pointer_table_size = 0;
static cryptlog_t __Crypt_memory_log;

flag_t __Crypt_debug_memory_init(size_t n, const char * f, unsigned int l) {
    if(Crypt_memory_init(n) == FALSE) return FAIL;
    if(Crypt_log_init(&__Crypt_memory_log, CRYPT_DEBUG_MEMORY_LOG_LOCATION) == FAIL) return FAIL;
    Crypt_log_write(&__Crypt_memory_log, "Memory log opened at %s:%u\n", f, l);
    return SUCCESS;
}

void * __Crypt_debug_memory_malloc(size_t n, const char * f, unsigned int l) {
    Crypt_log_write(&__Crypt_memory_log,
            "Called Crypt_memory_malloc(%ld) at %s:%u\n",
            n, f, l);

    void * ptr = Crypt_memory_malloc(n);

    Crypt_log_write(&__Crypt_memory_log,
            "Crypt_memory_malloc(%ld) -- Returned 0x%x\n",
            n, (intptr_t)ptr);

    __Crypt_debug_memory_add_ptr_to_table(ptr, n, f, l);

    return ptr;
}

void * __Crypt_debug_memory_realloc(void * restrict p, size_t n, const char * f, unsigned int l) {
    Crypt_log_write(&__Crypt_memory_log,
            "Called Crypt_memory_realloc(0x%x, %ld) at %s:%u\n",
            (size_t)p, n, f, l);

    void * ptr = Crypt_memory_realloc(p, n);

    Crypt_log_write(&__Crypt_memory_log,
            "Crypt_memory_realloc(0x%x, %ld) -- Returned 0x%x\n",
            (intptr_t)p, n, (intptr_t)ptr);

    if((intptr_t)ptr == (intptr_t)p) return ptr;

    __Crypt_debug_memory_remove_ptr_from_table(p);

    if(ptr != NULL) __Crypt_debug_memory_add_ptr_to_table(ptr, n, f, l);

    return ptr;
}

flag_t __Crypt_debug_memory_free(void * restrict p, const char * f, unsigned int l) {
    Crypt_log_write(&__Crypt_memory_log,
            "Called Crypt_memory_free(0x%x) at %s:%u\n",
            (intptr_t)p, f, l);

    flag_t free_ret = Crypt_memory_free(p);

    Crypt_log_write(&__Crypt_memory_log,
            "Crypt_memory_free(0x%x) -- Returned %s\n",
            (intptr_t)p, free_ret == SUCCESS ? "SUCCESS" : "FAIL");

    __Crypt_debug_memory_remove_ptr_from_table(p);

    return free_ret;
}


void __Crypt_debug_memory_quit(const char * f, unsigned int l) {
    Crypt_log_write(&__Crypt_memory_log,
            "Stopping memory module at %s:%u\n",
            f, l);

    for(size_t i = 0; i < __Crypt_pointer_table_size; i++) {
        struct __Crypt_pointer_table_entry entry = __Crypt_pointer_table[i];
        Crypt_log_write(&__Crypt_memory_log,
                "Memory leak detected:\n"
                "\tFrom %s:%u: Buffer at 0x%x with requested size %lu was not freed\n",
                entry.f, entry.l, entry.ptr, entry.n);
    }

    Crypt_memory_quit();
    Crypt_log_quit(&__Crypt_memory_log);
}

void __Crypt_debug_memory_add_ptr_to_table(void * restrict p, size_t n, const char * f, unsigned int l) {
    if(__Crypt_pointer_table_size == CRYPT_DEBUG_MEMORY_TABLE_POINTER_SIZE) return;

    struct __Crypt_pointer_table_entry entry = {.ptr = (intptr_t)p, .f = f, .l = l, .n = n};
    size_t low = 0, high = __Crypt_pointer_table_size - 1, mid = 0;

    if(__Crypt_pointer_table_size == 0) {
        __Crypt_pointer_table[__Crypt_pointer_table_size++] = entry;
        return;
    }

    while(low < high) {
        mid = (low + high) >> 1;
        if(__Crypt_pointer_table[mid].ptr < entry.ptr) low = mid + 1;
        else high = mid;
    }

    for(size_t i = __Crypt_pointer_table_size; i > mid; i--) {
        __Crypt_pointer_table[i] = __Crypt_pointer_table[i - 1];
    }

    __Crypt_pointer_table[mid] = entry;
    __Crypt_pointer_table_size++;
}

void __Crypt_debug_memory_remove_ptr_from_table(void * restrict p) {
    if(__Crypt_pointer_table_size == 0) return;

    size_t low = 0, high = __Crypt_pointer_table_size - 1, mid = 0;

    while(low < high) {
        mid = (low + high) >> 1;
        if(__Crypt_pointer_table[mid].ptr < (intptr_t)p) low = mid + 1;
        else high = mid;
    }

    for(size_t i = mid; i < __Crypt_pointer_table_size; i--) {
        __Crypt_pointer_table[i - 1] = __Crypt_pointer_table[i];
    }

    __Crypt_pointer_table_size--;
}
