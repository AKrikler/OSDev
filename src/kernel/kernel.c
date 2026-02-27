#include <drivers/vga.h>
#include <arch/i386/gdt.h>
#include <klibc/stdio.h>
#include <klibc/stdlib.h>

void kmain(void) {
    vga_init();
    gdt_init();

    uint16_t cs;
    __asm__ volatile("mov %%cs, %0" : "=r"(cs));
    kprintf("CS Register: %x\n", cs);
    uint16_t ds;
    __asm__ volatile("mov %%ds, %0" : "=r"(ds));
    kprintf("CS Register: %x\n", ds);

    for(;;) {
        __asm__ volatile("hlt");
    }
}