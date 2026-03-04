#include <klibc/string.h>
#include <klibc/stddef.h>

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

size_t strlen(const char* str)
{
	size_t count = 0;
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return count;
}

int strncmp(const char* s1, const char* s2, size_t num) {
	int i = 0;
    while (*s1 && (*s1 == *s2) && i < num) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

int strcmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}