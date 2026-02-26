#ifndef STDIO_H
#define STDIO_H

#include <klibc/types.h>
#include <klibc/stdarg.h>

/**
 * @brief Outputs a single character to the system console.
 * @param c The character to print.
 */
void kputc(int c);

/**
 * @brief Outputs a null-terminated string to the system console.
 * @param s The string to print.
 */
void kputs(const char* s);

/**
 * @brief Kernel formatted print to the system console.
 * @param fmt Format string (supports %c, %s, %d, %u, %x, %b, %p).
 */
void kprintf(const char* fmt, ...);

/**
 * @brief Variadic version of kprintf.
 */
void kvprintf(const char* fmt, va_list args);

/**
 * @brief Formats a string into a buffer with a size limit.
 * @param buf Destination buffer.
 * @param n   Maximum number of bytes to write (including null terminator).
 * @param fmt Format string.
 * @return    Number of characters that would have been written.
 */
int kvsnprintf(char* buf, size_t n, const char* fmt, va_list args);

/**
 * @brief Variadic version of ksprintf.
 */
int kvsprintf(char* buf, const char* fmt, va_list args);

/**
 * @brief Formats a string into a buffer with a size limit (Variadic).
 */
int ksnprintf(char* buf, size_t n, const char* fmt, ...);

/**
 * @brief Formats a string into a buffer.
 * @note Prefer ksnprintf to prevent buffer overflows.
 */
int ksprintf(char* buf, const char* fmt, ...);

#endif