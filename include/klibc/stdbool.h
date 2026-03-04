#ifndef STDBOOL_H
#define STDBOOL_H

/**
 * @brief Boolean type definition for the kernel.
 * Since we are operating in a freestanding environment without a 
 * standard library, we define our own boolean logic.
 */
typedef unsigned char bool;

/** @brief Logical true constant. */
#define true 1
/** @brief Logical false constant. */
#define false 0

/** @brief Macro to signal that bool, true, and false are defined. */
#define bool_true_false_defined 1

#endif