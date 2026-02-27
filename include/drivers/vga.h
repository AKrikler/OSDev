#ifndef VGA_H
#define VGA_H

#include <klibc/types.h>

/**
 * @brief VGA Color Palette.
 * * A VGA attribute byte consists of:
 * - Bits 0-3: Foreground color
 * - Bits 4-6: Background color
 * - Bit 7:    Blink bit (or bright background depending on setup)
 */
typedef enum VGA_COLOR {
    VGA_COLOR_BLACK         = 0x0,
    VGA_COLOR_BLUE          = 0x1,
    VGA_COLOR_GREEN         = 0x2,
    VGA_COLOR_CYAN          = 0x3,
    VGA_COLOR_RED           = 0x4,
    VGA_COLOR_MAGENTA       = 0x5,
    VGA_COLOR_BROWN         = 0x6,
    VGA_COLOR_LIGHT_GREY    = 0x7,
    VGA_COLOR_DARK_GREY     = 0x8,
    VGA_COLOR_LIGHT_BLUE    = 0x9,
    VGA_COLOR_LIGHT_GREEN   = 0xA,
    VGA_COLOR_LIGHT_CYAN    = 0xB,
    VGA_COLOR_LIGHT_RED     = 0xC,
    VGA_COLOR_LIGHT_MAGENTA = 0xD,
    VGA_COLOR_LIGHT_BROWN   = 0xE,
    VGA_COLOR_WHITE         = 0xF,
} vga_color_t;

/**
 * @brief Initializes the VGA driver, setting default colors and clearing the screen.
 */
void vga_init(void);

/**
 * @brief Clears the entire VGA buffer with the current background color.
 */
void vga_clear(void);

/**
 * @brief Scrolls the screen up by one line if the cursor exceeds VGA_HEIGHT.
 */
void vga_scroll(void);

/**
 * @brief Prints a single character to the screen at the current cursor position.
 * @note Correctly handles newline '\n' and carriage return '\r'.
 * @param c The unsigned character to display.
 */
void vga_putc(unsigned char c);

/**
 * @brief Prints a null-terminated string to the screen.
 * @param s Pointer to the string.
 */
void vga_puts(const char* s);

/**
 * @brief Driver-level formatted print. 
 * @note Usually kprintf is preferred over this in kernel code.
 */
void vga_printf(const char* fmt, ...);

/**
 * @brief Sets the foreground and background colors for subsequent output.
 * @param fg Foreground color.
 * @param bg Background color.
 */
void vga_set_color(vga_color_t fg, vga_color_t bg);

/**
 * @brief Manually moves the hardware cursor and internal tracking to a specific coordinate.
 * @param row The vertical coordinate (0 to VGA_HEIGHT-1).
 * @param col The horizontal coordinate (0 to VGA_WIDTH-1).
 */
void vga_set_pos(uint32_t row, uint32_t col);

/** @return Current cursor row. */
uint32_t vga_get_row(void);
/** @return Current cursor column. */
uint32_t vga_get_col(void);

#endif