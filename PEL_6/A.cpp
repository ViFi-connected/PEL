#include "A.h"
#include <malloc.h>
#include <stdio.h>

unsigned int* alloc_bytes(unsigned int byteCount)
{
	return (unsigned int*)malloc(byteCount);
}

int* alloc_ints(unsigned int intCount)
{
	return (int*)malloc(4 * intCount);
}

void dealloc(void* address)
{
	free(address);
}

void dump(void *address, unsigned int size)
{
    printf("Vypis pameti:\n\n");

    unsigned char* p = (unsigned char*)address;
    for (unsigned int i = 0; i < size; i++) {
        printf("%02hhX ", p[i]);
    }
    printf("\n\n");
}