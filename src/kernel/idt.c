#include <klibc/stdint.h>
#include <klibc/stdio.h>
#include <klibc/string.h>
#include <arch/i386/io.h>

extern void idt_flush(uint32_t);

extern void* isr_stub_table[];
extern void* irq_stub_table[];

static uint32_t timer_ticks;

typedef struct IDT_ENTRY
{
    uint16_t offset_low;
    uint16_t selector;
    uint8_t  reserved;
    uint8_t  access;
    uint16_t offset_high;
} __attribute__((packed)) idt_entry_t;

static idt_entry_t create_idt_entry(uint32_t handler, uint16_t selector, uint8_t type, uint8_t DPL, uint8_t present)
{
    return (idt_entry_t)
	{
        (uint16_t)handler,
        selector,
        0b00000000,
        (uint8_t)(present << 7 | DPL << 5 | type),
        (uint16_t)(handler >> 16),
    };
}

typedef struct REGISTERS {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;     
} registers_t;

void isr_handler(registers_t *regs)
{
    kprintf("Received Interrupt: %d, Error Code: %x\n", regs->int_no, regs->err_code);
}

void irq_handler(registers_t *regs)
{
    if (regs->int_no >= 40)
	{
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);
    if (regs->int_no == 33)
	{
        kprintf("Keyboard press detected\n");
        inb(0x60); 
    }
		if (regs->int_no == 32) {
        timer_ticks++;
        if (timer_ticks % 18 == 0) {
            kprintf("System uptime: %d seconds\n", timer_ticks / 18);
        }
    }
}

void pic_remap(void)
{
    outb(0x20, 0x11);
	io_wait();
    outb(0xA0, 0x11);
	io_wait();
    outb(0x21, 0x20);
	io_wait();
    outb(0xA1, 0x28);
	io_wait();
    outb(0x21, 0x04);
    io_wait();
	outb(0xA1, 0x02);
	io_wait();
    outb(0x21, 0x01);
	io_wait();
    outb(0xA1, 0x01);
	io_wait();
    outb(0x21, 0x0);
	io_wait();
    outb(0xA1, 0x0);
	io_wait();
}

void idt_init(void)
{
    static idt_entry_t __attribute__((aligned(16))) idt[256];

    memset(idt, 0, sizeof(idt));

    for (int i = 0; i < 32; i++)
	{
        idt[i] = create_idt_entry((uint32_t)isr_stub_table[i], 0x08, 0xE, 0, 1);
    }

	for (int i = 0; i < 16; i++)
	{
		idt[32 + i] = create_idt_entry((uint32_t)irq_stub_table[i], 0x08, 0xE, 0, 1);
	}

	pic_remap();

    idt_flush((uint32_t)&(struct { uint16_t limit; uint32_t base; } __attribute__((packed)))
	{
        (uint16_t)(sizeof(idt) - 1),
        (uint32_t)&idt
    });

	__asm__ volatile("sti");
}