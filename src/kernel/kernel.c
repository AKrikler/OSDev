#include <drivers/pit.h>
#include <drivers/cmos.h>
#include <drivers/vga.h>
#include <arch/i386/gdt.h>
#include <kernel/idt.h>
#include <klibc/time.h>
#include <klibc/unistd.h>
#include <klibc/stdio.h>

void kmain() 
{
	vga_init();
    gdt_init();
    idt_init();
    pit_init(CLOCKS_PER_SEC);

    kprintf("Timekeeping Tests\n");
    kprintf("---------------------------------------\n");

    kprintf("\nTEST 1: Absolute Time (CMOS)\n");
    struct tm now;
    cmos_read_rtc(&now);
    kprintf("Current UTC Time: %d:%d:%d, %d/%d/%d\n", now.hour, now.min, now.sec, now.mon, now.mday, now.year);

    kprintf("\nTEST 2: Sleep & Uptime (PIT)\n");
    kprintf("Testing msleep(2500)... (Should take 2.5s)\n");
    time_t start_ms = get_uptime_ms();
    msleep(2500);
    time_t end_ms = get_uptime_ms();
    kprintf("Actual time elapsed: %d ms\n", (time_t)difftime(end_ms, start_ms));

    kprintf("\nTEST 3: time.h wrapper\n");
    time_t t = time(NULL);
    kprintf("Epoch Seconds (since 2000): %u\n", (uint32_t)t);

    kprintf("\nTEST 4: Live Counter");
    kprintf("\nStarting live uptime counter\n");
    while(1) {
        kprintf("\rUptime: %d seconds", get_uptime_s());
        sleep(1);
    }

	for(;;)
	{
		__asm__ volatile("hlt");
	}
}