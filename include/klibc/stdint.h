#ifndef STDINT_H
#define STDINT_H

/** @brief Unsigned 8-bit integer (1 byte). Range: 0 to 255. */
typedef unsigned char       uint8_t;
/** @brief Unsigned 16-bit integer (2 bytes). Range: 0 to 65,535. */
typedef unsigned short      uint16_t;
/** @brief Unsigned 32-bit integer (4 bytes). Range: 0 to 4,294,967,295. */
typedef unsigned int        uint32_t;
/** @brief Unsigned 64-bit integer (8 bytes). Range: 0 to ~1.84e19. */
typedef unsigned long long  uint64_t;

/** @brief Signed 8-bit integer. Range: -128 to 127. */
typedef signed char         int8_t;
/** @brief Signed 16-bit integer. Range: -32,768 to 32,767. */
typedef signed short        int16_t;
/** @brief Signed 32-bit integer. Range: -2,147,483,648 to 2,147,483,647. */
typedef signed int          int32_t;
/** @brief Signed 64-bit integer. Range: ~-9.22e18 to ~9.22e18. */
typedef signed long long    int64_t;

#endif