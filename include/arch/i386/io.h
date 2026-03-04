#include <klibc/stdint.h>

/**
 * @brief Sends a byte of data to a specified hardware port.
 * @param port The 16-bit I/O port address (e.g., 0x20 for PIC1, 0x60 for Keyboard).
 * @param val  The 8-bit data value to send.
 * @note The "memory" clobber ensures the compiler doesn't reorder this around 
 * other memory operations.
 */
static inline void outb(uint16_t port, uint8_t val)
{
    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

/**
 * @brief Reads a byte of data from a specified hardware port.
 * @param port The 16-bit I/O port address to read from.
 * @return The 8-bit data value received from the hardware.
 */
static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ volatile ( "inb %w1, %0" : "=a"(ret) : "Nd"(port) : "memory");
    return ret;
}

/**
 * @brief Provides a tiny delay for I/O operations.
 * @details Forces the CPU to wait for an I/O cycle to complete by writing to
 * port 0x80, which is normally unused (often used for POST codes).
 */
static inline void io_wait(void)
{
    outb(0x80, 0);
}