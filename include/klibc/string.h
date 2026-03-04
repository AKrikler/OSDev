#ifndef STRING_H
#define STRING_H

#include <klibc/stddef.h>

/** * @brief Symbol representing a null pointer.
 * Used to indicate that a pointer does not point to a valid memory location.
 */
#define NULL (void*)0

/**
 * @brief Fills a block of memory with a specific value.
 * @param ptr Pointer to the block of memory to fill.
 * @param value The value to be set (passed as int, converted to unsigned char).
 * @param num Number of bytes to be set to the value.
 * @return A pointer to the memory area ptr.
 */
void* memset(void* ptr, int value, size_t num);

/**
 * @brief Copies a block of memory from one location to another.
 * @param destination Pointer to the destination array where the content is to be copied.
 * @param source Pointer to the source of data to be copied.
 * @param num Number of bytes to copy.
 * @return A pointer to destination.
 * @note If the destination and source overlap, behavior is undefined (use memmove for overlaps).
 */
void* memcpy(void* destination, const void* source, size_t num);

/**
 * @brief Compares two blocks of memory.
 * @param ptr1 Pointer to the first block of memory.
 * @param ptr2 Pointer to the second block of memory.
 * @param num Number of bytes to compare.
 * @return 0 if the blocks are equal, or a non-zero value representing the difference 
 * between the first pair of bytes that differ.
 */
int memcmp(const void* ptr1, const void* ptr2, size_t num);

/**
 * @brief Calculates the length of a null-terminated string.
 * @param str The string to measure.
 * @return The number of characters in the string, excluding the null terminator.
 * @note This function will traverse memory until a '\0' is found. Ensure the 
 * buffer is properly terminated to avoid kernel memory leaks or crashes.
 */
size_t strlen(const char* str);

/**
 * @brief Compares up to 'num' characters of two strings.
 * @param str1 The first string to compare.
 * @param str2 The second string to compare.
 * @param num  The maximum number of characters to examine.
 * @return An integer less than, equal to, or greater than zero if str1 is found,
 * respectively, to be less than, to match, or be greater than str2.
 * @note This is the "safe" version of strcmp, preventing the kernel from 
 * reading past the end of a buffer if the null terminator is missing.
 */
int strncmp(const char* str1, const char* str2, size_t num);

/**
 * @brief Compares two null-terminated strings.
 * @param str1 The first string to compare.
 * @param str2 The second string to compare.
 * @return An integer reflecting the lexicographical difference:
 * 0  : Strings are identical.
 * <0 : The first differing character has a lower value in str1.
 * >0 : The first differing character has a higher value in str1.
 */
int strcmp(const char* str1, const char* str2);

#endif