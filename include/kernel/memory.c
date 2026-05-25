// менеджер памяти - простейший кусок
// выделяем из статического буфера, без освобождения пока

#include "../include/types.h"
#include "memory.h"

#define HEAP_SIZE (1024 * 1024) // 1 MB, хватит на первое время
static char heap[HEAP_SIZE];
static uint32_t heap_ptr = 0;

void* malloc(uint32_t size) {
    if(heap_ptr + size > HEAP_SIZE) return NULL;
    void* ptr = heap + heap_ptr;
    heap_ptr += size;
    return ptr;
}

void free(void* ptr) {
    // похуй, не освобождаем
}
