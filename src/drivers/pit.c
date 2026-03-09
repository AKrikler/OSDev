#include <drivers/pit.h>
#include <arch/i386/io.h>
#include <kernel/idt.h>

#define PIT_FREQUENCY 1193182

#define PIT_CHANNEL0_DATA 	0x40
#define PIT_CHANNEL1_DATA 	0x41
#define PIT_CHANNEL2_DATA 	0x42
#define PIT_COMMAND			0x43

#define PIT_SET_COMMAND   0x36

static uint32_t ticks = 0;
static uint32_t frequency = 0;

void pit_init(uint32_t freq)
{
    frequency = freq == 0 ? 100 : freq;
    uint32_t divisor = PIT_FREQUENCY / frequency;

    outb(PIT_COMMAND, PIT_SET_COMMAND);
    outb(PIT_CHANNEL0_DATA, (uint8_t)(divisor & 0xFF));
    outb(PIT_CHANNEL0_DATA, (uint8_t)((divisor >> 8) & 0xFF));
}

void pit_handler(registers_t* regs)
{
	(void)regs;
    ticks++;
}

uint32_t pit_get_ticks()
{
    return ticks;
}

uint32_t pit_get_frequency(void)
{
	return frequency;
}