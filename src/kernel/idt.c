#include <kernel/idt.h>
#include <klibc/stdio.h>
#include <klibc/string.h>
#include <drivers/pit.h>
#include <arch/i386/io.h>

#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1

#define PIC1_OFFSET  0x20
#define PIC2_OFFSET  0x28

#define PIC_ICW1_IC4       0x01
#define PIC_ICW1_INIT      0x10
#define PIC_INIT_COMMAND   (PIC_ICW1_INIT | PIC_ICW1_IC4)

#define PIC_MASTER_SLAVE_BIT  0x04
#define PIC_SLAVE_ID          0x02

#define PIC_ICW4_8086      0x01

#define PIC_EOI 0x20

#define PIC_MASK_ALL_ENABLED  0x00

#define KBD_DATA_PORT 0x60

extern void idt_flush(uint32_t);

extern void* isr_stub_table[];
extern void* irq_stub_table[];

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

void isr_handler(registers_t* regs)
{
    kprintf("Received Interrupt: %d, Error Code: %x\n", regs->int_no, regs->err_code);
}

void irq_handler(registers_t* regs)
{
    if (regs->int_no >= 40)
	{
        outb(PIC2_COMMAND, PIC_EOI);
    }
    outb(PIC1_COMMAND, PIC_EOI);
    if (regs->int_no == 33)
	{
        kprintf("Keyboard press detected\n");
        inb(KBD_DATA_PORT); 
    }
	if (regs->int_no == 32)
	{
		pit_handler(regs);
    }
}

void pic_remap(void)
{
    outb(PIC1_COMMAND, PIC_INIT_COMMAND);
	io_wait();
    outb(PIC2_COMMAND, PIC_INIT_COMMAND);
	io_wait();
    outb(PIC1_DATA, PIC1_OFFSET);
	io_wait();
    outb(PIC2_DATA, PIC2_OFFSET);
	io_wait();
    outb(PIC1_DATA, PIC_MASTER_SLAVE_BIT);
    io_wait();
	outb(PIC2_DATA, PIC_SLAVE_ID);
	io_wait();
    outb(PIC1_DATA, PIC_ICW1_IC4);
	io_wait();
    outb(PIC2_DATA, PIC_ICW1_IC4);
	io_wait();
    outb(PIC1_DATA, PIC_MASK_ALL_ENABLED);
	io_wait();
    outb(PIC2_DATA, PIC_MASK_ALL_ENABLED);
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