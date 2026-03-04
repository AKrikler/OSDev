#ifndef ASSERT_H
#define ASSERT_H

/**
 * @brief Halts execution if a condition is false.
 * @param condition The expression to evaluate.
 * @details If condition is false, prints the expression, filename, and line number
 * to the console.
 */
#define assert(condition) 																			\
	do 																								\
	{ 																								\
		if (!(condition)) 																			\
		{ 																							\
			kprintf("ASSERTION FAILED: %s\nFile: %s, Line: %d\n", #condition, __FILE__, __LINE__); 	\
		} 																							\
	}																								\
	while(0) 																						\

#endif