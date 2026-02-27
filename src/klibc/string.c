#include <string.h>

void* memset(void* ptr, int value, size_t num)
{
    unsigned char* p = ptr;
    while (num-- > 0) *p++ = (unsigned char) value;
    return ptr;
}

void* memcpy(void* destination, const void* source, size_t num)
{
    unsigned char* dptr = destination;
    const unsigned char* sptr = source;
    while (num-- > 0) *dptr++ = *sptr++;
    return destination; 
}

int memcmp(const void* ptr1, const void* ptr2, size_t num)
{
    const unsigned char* p1 = ptr1;
    const unsigned char* p2 = ptr2;
    for (size_t i = 0; i < num; i++)
    {
        if (p1[i] < p2[i]) return -1;
        if (p1[i] > p2[i]) return 1;
    }
    return 0;
}