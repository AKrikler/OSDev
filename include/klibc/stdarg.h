#ifndef STDARG_H
#define STDARG_H

/**
 * @brief Type to hold information about variable arguments.
 * * On x86_32, this is simply a pointer to the current position in the 
 * argument list on the stack.
 */
typedef char* va_list;

/**
 * @brief Initialize a va_list to point to the first variadic argument.
 * * @param ap   The va_list object to initialize.
 * @param last The name of the last fixed parameter before the '...' list.
 */
#define va_start(ap, last) \
    (ap = (va_list)&last + sizeof(last))

/**
 * @brief Retrieve the next argument in the list.
 * * This macro performs two steps:
 * 1. Increments the ap pointer to the next argument (aligned to 4 bytes).
 * 2. Returns the value of the argument at the previous pointer location.
 * * @param ap   The initialized va_list object.
 * @param type The type of the argument to retrieve (e.g., int, char*).
 * @return     The value of the next argument cast to 'type'.
 */
#define va_arg(ap, type) \
    (*(type*)((ap += (sizeof(type) + 3) & ~3) - ((sizeof(type) + 3) & ~3)))

/**
 * @brief Clean up the va_list object after use.
 * * @param ap The va_list object to finalize.
 */
#define va_end(ap) \
    (ap = (va_list)0)

/**
 * @brief Copy the state of one va_list to another.
 * * Useful for passing the same set of variadic arguments to multiple 
 * helper functions.
 * * @param dest The destination va_list.
 * @param src  The source va_list to copy from.
 */
#define va_copy(dest, src) \
    ((dest) = (src))

#endif