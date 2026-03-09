#ifndef PIT_H
#define PIT_H

#include <kernel/idt.h>
#include <klibc/stdint.h>

/* Initializes PIT to fire at the specified frequency (Hz) */
void pit_init(uint32_t freq);

/* The Interrupt Service Routine (ISR) for IRQ0; increments system ticks */
void pit_handler(registers_t* regs);

/* Returns total raw ticks since PIT was initialized */
uint32_t pit_get_ticks(void);

/* Returns the current operating frequency of the PIT */
uint32_t pit_get_frequency(void);

#endif