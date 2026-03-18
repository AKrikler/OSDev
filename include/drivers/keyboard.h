#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <kernel/idt.h>
#include <klibc/stdint.h>

void keyboard_handler(registers_t* regs);
char keyboard_pop_char(void);

#endif