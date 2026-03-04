#include <klibc/stdio.h>
#include <klibc/string.h>
#include <klibc/assert.h>
#include <klibc/stdint.h>
#include <arch/i386/gdt.h>
#include <drivers/vga.h>1
#include <kernel/idt.h>

void test_klibc() {
    kprintf("[TEST] Testing klibc string functions...\n");
    
    // Test strlen
    assert(strlen("Hello") == 5);
    
    // Test memcmp and memset
    uint8_t buf1[4] = {0xAA, 0xAA, 0xAA, 0xAA};
    uint8_t buf2[4];
    memset(buf2, 0xAA, 4);
    assert(memcmp(buf1, buf2, 4) == 0);
    
    kprintf("[PASS] klibc basic string/mem tests passed.\n");
}

void test_exceptions() {
    kprintf("[TEST] Triggering Software Interrupt (int 3)...\n");
    // This should trigger isr_handler and print "Received Interrupt: 3"
    __asm__ volatile("int $0x3"); 
    kprintf("[PASS] Software interrupt handled.\n");
}

void kmain(void) {
    vga_init();
    kprintf("--- KriklerOS Diagnostic Boot ---\n");

    // 1. Test GDT
    gdt_init();
    kprintf("[OK] GDT Initialized.\n");

    // 2. Test IDT & PIC
    idt_init(); // This includes pic_remap and sti
    kprintf("[OK] IDT Initialized & Hardware Interrupts Enabled.\n");

    // 3. Test klibc logic
    test_klibc();

    // 4. Test Exceptions
    test_exceptions();

    kprintf("\n[SYSTEM] Testing Hardware IRQs. Press any key...\n");

    // Final Loop: Just wait for IRQs (Timer and Keyboard)
    for(;;) {
        __asm__ volatile("hlt"); 
    }
}