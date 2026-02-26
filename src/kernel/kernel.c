#include <drivers/vga.h>
#include <klibc/stdio.h>
#include <klibc/stdlib.h>

void kmain(void) {
    vga_init();

    kprintf("KriklerOS Kernel Booting...\n");
    kprintf("--------------------------\n\n");

    kprintf("Testing Strings: [%s]\n", "Success");
    kprintf("Testing Chars:   [%c%c%c]\n", 'O', 'K', '!');

    int negative = -12345;
    unsigned int positive = 54321;
    kprintf("Negative Int:    %d\n", negative);
    kprintf("Positive Int:    %u\n", positive);
    kprintf("Binary Check:    %b\n", 0xAF);
    kprintf("Hex Check:       %x\n", 0xDEADBEEF);

    void* test_ptr = (void*)0x1000;
    kprintf("Pointer Check:   %p\n", test_ptr);

    char buffer[20];
    ksnprintf(buffer, sizeof(buffer), "Buffer Overflow Test"); // Truncate 't'
    kprintf("Snprintf Test:   %s\n", buffer);

    kprintf("\nFilling screen to test scrolling...\n");
    for(int i = 0; i < 15; i++) {
        kprintf("Line count: %d\n", i);
    }

    for(;;) {
        __asm__ volatile("hlt");
    }
}