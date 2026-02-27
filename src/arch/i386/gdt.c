#include <arch/i386/gdt.h>

#include <klibc/types.h>

extern void gdt_flush(uint32_t);

static uint64_t create_entry(uint32_t base, uint32_t limit, uint8_t selector_type, uint8_t is_system_type, uint8_t DPL, uint8_t present, uint8_t available, uint8_t long_mode, uint8_t misc, uint8_t gran)
{
    uint64_t entry = 0;

    entry |= (uint64_t)(limit & 0xFFFF);                // 0-15: Limit Low
    entry |= (uint64_t)((limit >> 16) & 0x0F) << 48;    // 48-51: Limit High

    entry |= (uint64_t)(base & 0xFFFF) << 16;           // 16-31: Base Low
    entry |= (uint64_t)((base >> 16) & 0xFF) << 32;     // 32-39: Base Middle
    entry |= (uint64_t)((base >> 24) & 0xFF) << 56;     // 56-63: Base High

    uint8_t access = (present & 0x01) << 7;
    access |= (DPL & 0x03) << 5;
    access |= (is_system_type & 0x01) << 4;
    access |= (selector_type & 0x0F);
    entry |= (uint64_t)access << 40;                    // 40-47: Access Byte [Present(1) | DPL(2) | S(1) | Type(4)]

    uint8_t flags = (gran & 0x01) << 7;
    flags |= (misc & 0x01) << 6;
    flags |= (long_mode & 0x01) << 5;
    flags |= (available & 0x01) << 4;
    entry |= (uint64_t)flags << 48;                     // 52-55: Flags/Gran [Gran(1) | Size/Misc(1) | Long(1) | Avl(1)]

    return entry;
}

void gdt_init(void)
{
    static uint64_t gdt[5];

    gdt[0] = create_entry(0, 0, 0, 0, 0, 0, 0,0, 0, 0);             // Null
    gdt[1] = create_entry(0, 0xFFFFF, 0x0A, 1, 0, 1, 0, 0, 1, 1);   // K-Code
    gdt[2] = create_entry(0, 0xFFFFF, 0x02, 1, 0, 1, 0, 0, 1, 1);   // K-Data
    gdt[3] = create_entry(0, 0xFFFFF, 0x0A, 1, 3, 1, 0, 0, 1, 1);   // U-Code
    gdt[4] = create_entry(0, 0xFFFFF, 0x02, 1, 3, 1, 0, 0, 1, 1);   // U-Data

    gdt_flush((uint32_t)&(struct { uint16_t limit; uint32_t base; } __attribute__((packed))){
        (uint16_t)(sizeof(gdt) - 1), 
        (uint32_t)&gdt
    });
}