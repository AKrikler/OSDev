#ifndef STDLIB_H
#define STDLIB_H

#include <klibc/types.h>

/**
 * @brief Converts an integer to a string based on the provided base.
 * Supported bases: 2 (binary), 10 (decimal), 16 (hex).
 * @param value The number to convert.
 * @param str   The buffer to store the result.
 * @param base  The numerical base.
 * @return      A pointer to the resulting string.
 */
char* itoa(int value, char* str, int base);

/**
 * @brief Converts an unsigned integer to a string based on the provided base.
 * Supported bases: 2 (binary), 10 (decimal), 16 (hex).
 * @param value The number to convert.
 * @param str   The buffer to store the result.
 * @param base  The numerical base.
 * @return      A pointer to the resulting string.
 */
char* utoa(unsigned int value, char* str, int base);

#endif