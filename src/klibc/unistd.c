#include <klibc/unistd.h>

void msleep(uint32_t msec)
{
    uint32_t start = pit_get_ticks();
	uint32_t freq = pit_get_frequency();
    uint32_t ticks_to_wait = (msec * freq) / 1000; 
    while (pit_get_ticks() < start + ticks_to_wait) {
        __asm__ volatile("hlt");
    }
}

unsigned int sleep(unsigned int seconds)
{
    msleep(seconds * 1000);
	return 0;
}

uint32_t get_uptime_s(void)
{
	return pit_get_ticks() / pit_get_frequency();
}

uint32_t get_uptime_ms(void)
{
    return (pit_get_ticks() * 1000) / pit_get_frequency();
}