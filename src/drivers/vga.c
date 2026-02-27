#include <drivers/vga.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDRESS 0xB8000

static uint16_t* const vga_buffer = (uint16_t*)VGA_ADDRESS;
static uint32_t vga_row = 0, vga_col = 0;
static uint8_t  vga_color = 0x07;

static inline uint16_t vga_entry(unsigned char c, uint8_t color) { return (uint16_t)c | (uint16_t)color << 8; }

void vga_init(void)
{
    vga_clear();
}

void vga_clear(void)
{
    uint16_t blank = vga_entry(' ', vga_color);
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
    {
        vga_buffer[i] = blank;
    }
    vga_row = 0;
    vga_col = 0;
}

void vga_scroll(void)
{
    for (int i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH; i++)
    {
        vga_buffer[i] = vga_buffer[i + VGA_WIDTH];
    }
    uint16_t blank = vga_entry(' ', vga_color);
    for (int i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < VGA_HEIGHT * VGA_WIDTH; i++)
    {
        vga_buffer[i] = blank;
    }
    vga_row =  VGA_HEIGHT - 2;
    vga_col = 0;
}

void vga_putc(unsigned char c)
{
    switch(c)
    {
        case '\a':
            break;
        case '\b':
            if (vga_col > 0)
            {
                vga_col--;
            }
            else if (vga_row > 0)
            {
                vga_row--;
                vga_col = VGA_WIDTH - 1;
            }
            vga_buffer[vga_row * VGA_WIDTH + vga_col] = vga_entry(' ', vga_color);
            break;
        case '\n':
            vga_col = 0;
            if (++vga_row == VGA_HEIGHT)
            {
                vga_scroll();
            }
            break;
        case '\r':
            vga_col = 0;
            break;
        case '\t':
            vga_col = (vga_col + 8) & ~7; 
            if (vga_col >= VGA_WIDTH)
            {
                vga_col = 0;
                if (++vga_row == VGA_HEIGHT) vga_scroll();
            }
            break;
        default:
            vga_buffer[vga_row * VGA_WIDTH + vga_col] = vga_entry(c, vga_color); 
            if (++vga_col == VGA_WIDTH)
            {
                vga_col = 0;
                if (++vga_row == VGA_HEIGHT)
                {
                    vga_scroll();
                }
            }
            break;
    }
}

void vga_puts(const char* s)
{
    while (*s)
    {
        vga_putc(*s++);
    }
}

static int itoa(int value, char* buf, int base)
{
    char tmp[32];
    int i = 0, len = 0;
    int negative = 0;

    if (value == 0) { buf[len++] = '0'; buf[len] = 0; return len; }
    if (value < 0 && base == 10) {negative = 1; value = -value; }

    unsigned int uval = (unsigned int)value;
    while (uval > 0) {tmp[i++] = "0123456789abcdef"[uval % base]; uval /= base; }
    if (negative) tmp[i++] = '-';

    for (int j = i - 1; j >= 0; j--) buf[len++] = tmp[j];
    buf[len] = 0;
    return len;
}

void vga_printf(const char* fmt, ...)
{
    __builtin_va_list args;
    __builtin_va_start(args, fmt);

    while (*(fmt))
    {
        if (*fmt != '%')
        {
            vga_putc(*(fmt++));
            continue;
        }
        
        switch (*++fmt)
        {   
            case 'd':
            {
                int i = __builtin_va_arg(args, int);
                char buf[32];
                itoa(i, buf, 10);
                vga_puts(buf);
                break;
            }
            case 'x':
            {
                int x = __builtin_va_arg(args, int);
                char buf[32];
                itoa(x, buf, 16);
                vga_puts(buf);
                break;
            }
            case 's':
            {
                const char* s = __builtin_va_arg(args, char*);
                vga_puts(s);
                break;
            }
            case 'c':
            {
                vga_putc((char)__builtin_va_arg(args, int));
                break;
            }
            case '%':
            {
                vga_putc('%');
                break;
            }
            default:
            {
                vga_putc('%');
                vga_putc(*fmt);
                break;
            }
        }
        fmt++;
    }
    __builtin_va_end(args);
}

void vga_set_color(vga_color_t fg, vga_color_t bg) { vga_color = (uint8_t)fg | (uint8_t)bg << 4; }
void vga_set_pos(uint32_t row, uint32_t col) { vga_row = row; vga_col = col; }

uint32_t vga_get_row(void) { return vga_row; }
uint32_t vga_get_col(void) { return vga_col; }