//
// Created by Vinicius de Freitas Pereira on 19/04/26.
//

#include "malloc.h"

void *malloc(size_t size)
{
    if (size == 0)
        return NULL;
    return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
}
