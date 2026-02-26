#include <klibc/stdio.h>

#include <drivers/vga.h>

void kputc(int c) {
    vga_putc((unsigned char)c);
}

void kputs(const char* s) {
    vga_puts(s);
}

void kvprintf(const char* fmt, va_list args) {
    while (*fmt) {
        if (*fmt != '%') {
            kputc(*fmt++);
            continue;
        }
        fmt++;
        switch (*fmt) {
            case 'c': {
                char c = (char)va_arg(args, int);
                kputc(c);
                break;
            }
            case 's': {
                const char* s = va_arg(args, const char*);
                if (!s) s = "(null)";
                kputs(s);
                break;
            }
            case 'd': {
                int i = va_arg(args, int);
                char buf[32];
                itoa(i, buf, 10);
                kputs(buf);
                break;
            }
            case 'u': {
                unsigned int u = va_arg(args, unsigned int);
                char buf[32];
                utoa(u, buf, 10);
                kputs(buf);
                break;
            }
            case 'b': {
                unsigned int b = va_arg(args, unsigned int);
                char buf[33];
                itoa(b, buf, 2); 
                kputs("0b");
                kputs(buf);
                break;
            }
            case 'x': {
                unsigned int x = va_arg(args, unsigned int);
                char buf[32];
                utoa(x, buf, 16);
                kputs("0x");
                kputs(buf);
                break;
            }
            case 'p': {
                unsigned int p = (unsigned int)va_arg(args, void*);
                char buf[32];
                kputc('0'); kputc('x');
                utoa(p, buf, 16);
                kputs(buf);
                break;
            }
            case '%': {
                kputc('%');
                break;
            }
            default: {
                kputc('%');
                kputc(*fmt);
                break;
            }
        }
        fmt++;
    }
}

void kprintf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    kvprintf(fmt, args); 
    va_end(args);
}

int kvsnprintf(char* buf, size_t n, const char* fmt, va_list args) {
    size_t i = 0;
    if (n == 0) return 0;
    while (*fmt && i < n - 1) {
        if (*fmt != '%') {
            buf[i++] = *fmt++;
            continue;
        }

        fmt++;
        switch (*fmt) {
            case 'c': {
                buf[i++] = (char)va_arg(args, int);
                break;
            }
            case 's': {
                const char* s = va_arg(args, const char*);
                if (!s) s = "(null)";
                while (*s && i < n - 1) {
                    buf[i++] = *s++;
                }
                break;
            }
            case 'd': {
                int val = va_arg(args, int);
                char tmp[32];
                itoa(val, tmp, 10);
                for (int j = 0; tmp[j] && i < n - 1; j++) {
                    buf[i++] = tmp[j];
                }
                break;
            }
            case 'u': {
                unsigned int val = va_arg(args, unsigned int);
                char tmp[32];
                utoa(val, tmp, 10);
                for (int j = 0; tmp[j] && i < n - 1; j++) {
                    buf[i++] = tmp[j];
                }
                break;
            }
            case 'b': {
                unsigned int val = va_arg(args, unsigned int);
                char tmp[33];
                itoa(val, tmp, 2);
                buf[i++] = '0';
                buf[i++] = 'b';
                for (int j = 0; tmp[j] && i < n - 1; j++) {
                    buf[i++] = tmp[j];
                }
                break;
            }
            case 'x': {
                unsigned int val = va_arg(args, unsigned int);
                char tmp[32];
                utoa(val, tmp, 16);
                buf[i++] = '0';
                buf[i++] = 'x';
                for (int j = 0; tmp[j] && i < n - 1; j++) {
                    buf[i++] = tmp[j];
                }
                break;
            }
            case 'p': {
                unsigned int val = (unsigned int)va_arg(args, void*);
                char tmp[32];
                if (i < n - 3) {
                    buf[i++] = '0';
                    buf[i++] = 'x';
                    utoa(val, tmp, 16);
                    for (int j = 0; tmp[j] && i < n - 1; j++) {
                        buf[i++] = tmp[j];
                    }
                }
                break;
            }
            case '%': {
                buf[i++] = '%';
                break;
            }
            default: {
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

int ksnprintf(char* buf, size_t n, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int result = kvsnprintf(buf, n, fmt, args);
    va_end(args);
    return result;
}

int kvsprintf(char* buf, const char* fmt, va_list args) {
    return kvsnprintf(buf, (size_t)-1, fmt, args);
}

int ksprintf(char* buf, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int result = kvsprintf(buf, fmt, args);
    va_end(args);
    return result;
}