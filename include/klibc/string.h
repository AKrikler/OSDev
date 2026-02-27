#ifndef STRING_H
#define STRING_H

#include <klibc/types.h>

void* memset(void* ptr, int value, size_t num);
void* memcpy(void* destination, const void* source, size_t num);
int memcmp(const void* ptr1, const void* ptr2, size_t num);

#endif