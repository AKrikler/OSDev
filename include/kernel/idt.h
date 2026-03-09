#ifndef IDT_H
#define IDT_H

#include <klibc/stdint.h>

typedef struct REGISTERS {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;     
} registers_t;

void idt_init(void);

#endif