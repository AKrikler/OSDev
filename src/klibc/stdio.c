#include <klibc/stdio.h>

#include <drivers/vga.h>
#include <drivers/keyboard.h>
#include <klibc/stdlib.h>
#include <klibc/string.h>

void kputc(int c)
{
    vga_putc((unsigned char)c);
}

void kputs(const char* s)
{
    vga_puts(s);
}

void kvprintf(const char* fmt, va_list args)
{
    while (*fmt)
	{
        if (*fmt != '%') {
            vga_putc(*fmt++);
            continue;
        }
        fmt++;

		int pad_zero = 0;
        int width = 0;

        if (*fmt == '0') {
            pad_zero = 1;
            fmt++;
        }

        if (*fmt >= '1' && *fmt <= '9') {
            width = *fmt - '0';
            fmt++;
        }
		
        switch (*fmt)
		{
            case 'c':
			{
                char c = (char)va_arg(args, int);
                vga_putc(c);
                break;
            }
            case 's':
			{
                const char* s = va_arg(args, const char*);
                if (!s) s = "(null)";
                vga_puts(s);
                break;
            }
            case 'd':
			{
                int i = va_arg(args, int);
                char buf[32];
                itoa(i, buf, 10);
				if (pad_zero && width > 0) {
                    int len = strlen(buf);
                    while (len < width) {
                        vga_putc('0');
                        len++;
                    }
                }
                vga_puts(buf);
                break;
            }
            case 'u':
			{
                unsigned int u = va_arg(args, unsigned int);
                char buf[32];
                utoa(u, buf, 10);
				if (pad_zero && width > 0) {
                    int len = strlen(buf);
                    while (len < width) {
                        vga_putc('0');
                        len++;
                    }
                }
                vga_puts(buf);
                break;
            }
            case 'b':
			{
                unsigned int b = va_arg(args, unsigned int);
                char buf[33];
                itoa(b, buf, 2); 
                vga_puts("0b");
				if (pad_zero && width > 0) {
                    int len = strlen(buf);
                    while (len < width) {
                        vga_putc('0');
                        len++;
                    }
                }
                vga_puts(buf);
                break;
            }
            case 'x':
			{
                unsigned int x = va_arg(args, unsigned int);
                char buf[32];
                utoa(x, buf, 16);
                vga_puts("0x");
				if (pad_zero && width > 0) {
                    int len = strlen(buf);
                    while (len < width) {
                        vga_putc('0');
                        len++;
                    }
                }
                vga_puts(buf);
                break;
            }
            case 'p':
			{
                unsigned int p = (unsigned int)va_arg(args, void*);
                char buf[32];
                vga_puts("0x");
                utoa(p, buf, 16);
				if (pad_zero && width > 0) {
                    int len = strlen(buf);
                    while (len < width) {
                        vga_putc('0');
                        len++;
                    }
                }
                vga_puts(buf);
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
}

void kprintf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    kvprintf(fmt, args); 
    va_end(args);
}

int kvsnprintf(char* buf, size_t n, const char* fmt, va_list args)
{
    size_t i = 0;
    if (n == 0) return 0;
    while (*fmt && i < n - 1)
	{
        if (*fmt != '%')
		{
            buf[i++] = *fmt++;
            continue;
        }

        fmt++;
        switch (*fmt)
		{
            case 'c':
			{
                buf[i++] = (char)va_arg(args, int);
                break;
            }
            case 's':
			{
                const char* s = va_arg(args, const char*);
                if (!s) s = "(null)";
                while (*s && i < n - 1)
				{
                    buf[i++] = *s++;
                }
                break;
            }
            case 'd': 
			{
                int val = va_arg(args, int);
                char tmp[32];
                itoa(val, tmp, 10);
                for (int j = 0; tmp[j] && i < n - 1; j++)
				{
                    buf[i++] = tmp[j];
                }
                break;
            }
            case 'u':
			{
                unsigned int val = va_arg(args, unsigned int);
                char tmp[32];
                utoa(val, tmp, 10);
                for (int j = 0; tmp[j] && i < n - 1; j++)
				{
                    buf[i++] = tmp[j];
                }
                break;
            }
            case 'b':
			{
                unsigned int val = va_arg(args, unsigned int);
                char tmp[33];
                itoa(val, tmp, 2);
                buf[i++] = '0';
                buf[i++] = 'b';
                for (int j = 0; tmp[j] && i < n - 1; j++)
				{
                    buf[i++] = tmp[j];
                }
                break;
            }
            case 'x':
			{
                unsigned int val = va_arg(args, unsigned int);
                char tmp[32];
                utoa(val, tmp, 16);
                buf[i++] = '0';
                buf[i++] = 'x';
                for (int j = 0; tmp[j] && i < n - 1; j++)
				{
                    buf[i++] = tmp[j];
                }
                break;
            }
            case 'p':
			{
                unsigned int val = (unsigned int)va_arg(args, void*);
                char tmp[32];
                if (i < n - 3) {
                    buf[i++] = '0';
                    buf[i++] = 'x';
                    utoa(val, tmp, 16);
                    for (int j = 0; tmp[j] && i < n - 1; j++)
					{
                        buf[i++] = tmp[j];
                    }
                }
                break;
            }
            case '%':
			{
                buf[i++] = '%';
                break;
            }
			case '0':
			{
				int pad_width = 0;
				fmt++; 
				if (*fmt >= '1' && *fmt <= '9') {
					pad_width = *fmt - '0';
					fmt++;
				}
				
				if (*fmt == 'd') {
					int val = va_arg(args, int);
					char tmp[32];
					itoa(val, tmp, 10);
					int len = strlen(tmp);
					
					while (len < pad_width && i < n - 1) {
						buf[i++] = '0';
						len++;
					}
					
					for (int j = 0; tmp[j] && i < n - 1; j++) {
						buf[i++] = tmp[j];
					}
				}
				break;
			}
            default:
			{
                buf[i++] = '%';
                if (i < n - 1) buf[i++] = *fmt;
                break;
            }
        }
        fmt++;
    }

    buf[i] = '\0';
    return (int)i;
}

int ksnprintf(char* buf, size_t n, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int result = kvsnprintf(buf, n, fmt, args);
    va_end(args);
    return result;
}

int kvsprintf(char* buf, const char* fmt, va_list args)
{
    return kvsnprintf(buf, (size_t)-1, fmt, args);
}

int ksprintf(char* buf, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int result = kvsprintf(buf, fmt, args);
    va_end(args);
    return result;
}

char kgetc(void)
{
	char c = 0;
	while ((c = keyboard_pop_char()) == 0) __asm__ volatile("hlt");
	return c;
}

void kgets(char* buf, size_t size)
{
	size_t i = 0;
	while (i < size - 1)
	{
		char c = kgetc();
		if (c == '\n')
		{
			kprintf("\n");
			break;
		}
		else if (c == '\b')
		{
			if (i > 0)
			{
				i--;
				kprintf("\b \b");
			}
			continue;
		}
		else
		{
			kprintf("%c", c);
			buf[i++] = c;
		}
	}
	buf[i] = '\0';
}