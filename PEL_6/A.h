#pragma once

unsigned int* alloc_bytes(unsigned int byteCount);
int* alloc_ints(unsigned int intCount);
void dealloc(void* address);
void dump(void* address, unsigned int size);
