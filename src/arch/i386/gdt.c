#include <arch/i386/gdt.h>
#include <klibc/stdbool.h>
#include <klibc/stdint.h>

extern void gdt_flush(uint32_t);

typedef struct GDT_ENTRY
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_mid;
    uint8_t  access;
    uint8_t  flags;
    uint8_t  base_high;
} __attribute__((packed)) gdt_entry_t;

static gdt_entry_t create_entry(uint32_t limit, uint32_t base, uint8_t present, uint8_t DPL, uint8_t descriptor_type, bool executable, uint8_t DC, bool RW, bool accessed, bool gran, bool DB, bool long_mode)
{
    return (gdt_entry_t)
	{
        (uint16_t)(limit & 0xFFFF),
        (uint16_t)(base & 0xFFFF),
        (uint8_t)((base >> 16) & 0xFF),
        (uint8_t)((present << 7) | (DPL << 5) | (descriptor_type << 4) | (executable << 3) | (DC << 2) | (RW << 1) | accessed),
        (uint8_t)((gran << 7) | (DB << 6) | (long_mode << 5) | ((limit >> 16) & 0x0F)),
		(uint8_t)((base >> 24) & 0xFF),
    };
}

void gdt_init(void)
{
	static gdt_entry_t gdt[5];

	gdt[0] = create_entry(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);								// Null
	gdt[1] = create_entry(0xFFFFF, 0, 1, 0, 1, true,  0, true, false, true, true, false);	// K-Code
	gdt[2] = create_entry(0xFFFFF, 0, 1, 0, 1, false, 0, true, false, true, true, false);	// K-Data
	gdt[3] = create_entry(0xFFFFF, 0, 1, 3, 1, true,  0, true, false, true, true, false);	// U-Code
	gdt[4] = create_entry(0xFFFFF, 0, 1, 3, 1, false, 0, true, false, true, true, false);	// U-Data

	gdt_flush((uint32_t)&(struct { uint16_t limit; uint32_t base; } __attribute__((packed)))
	{
    	(uint16_t)(sizeof(gdt) - 1), 
        (uint32_t)&gdt
    });
}