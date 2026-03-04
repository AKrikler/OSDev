#ifndef CSTDDEF
#define CSTDDEF

/**
 * @brief Unsigned integer type used for sizes of objects.
 * @details Defined using compiler intrinsics to ensure it matches the 
 * architecture's natural word size for memory addressing and pointer math.
 */
typedef typeof(sizeof(0)) size_t;

#endif