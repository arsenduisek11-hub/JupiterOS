#ifndef MEMORY_H
#define MEMORY_H

#include "../include/types.h"

void* malloc(uint32_t size);
void free(void* ptr);

#endif
