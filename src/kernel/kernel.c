#include <drivers/pit.h>
#include <drivers/cmos.h>
#include <drivers/vga.h>
#include <drivers/keyboard.h>
#include <arch/i386/gdt.h>
#include <arch/i386/io.h>
#include <kernel/idt.h>
#include <kernel/multiboot.h>
#include <klibc/time.h>
#include <klibc/unistd.h>
#include <klibc/stdio.h>
#include <klibc/string.h>

static void shell_cpu(void)
{
    uint32_t ebx, ecx, edx;
    __asm__ volatile("cpuid" : "=b"(ebx), "=c"(ecx), "=d"(edx) : "a"(0));
    char vendor[13];
    *((uint32_t*)&vendor[0]) = ebx;
    *((uint32_t*)&vendor[4]) = edx;
    *((uint32_t*)&vendor[8]) = ecx;
    vendor[12] = '\0';
    kprintf("CPU Vendor: %s\n", vendor);
}

static void shell_reboot(void) {
    kprintf("Rebooting...\n");
    uint8_t good = 0x02;
    while (good & 0x02) good = inb(0x64);
    outb(0x64, 0xFE);
}

static void print_banner(void) {
    kprintf("     _____                                                            _____ \n");
	kprintf("    ( ___ )                                                          ( ___ )\n");
	kprintf("     |   |------------------------------------------------------------|   | \n");
	kprintf("     |   |  __    __            __  __        __                      |   | \n");
	kprintf("     |   | |  \\  /  \\          |  \\|  \\      |  \\                     |   | \n");
	kprintf("     |   | | $$ /  $$  ______   \\$$| $$   __ | $$  ______    ______   |   | \n");
	kprintf("     |   | | $$/  $$  /      \\ |  \\| $$  /  \\| $$ /      \\  /      \\  |   | \n");
	kprintf("     |   | | $$  $$  |  $$$$$$\\| $$| $$_/  $$| $$|  $$$$$$\\|  $$$$$$\\ |   | \n");
	kprintf("     |   | | $$$$$\\  | $$   \\$$| $$| $$   $$ | $$| $$    $$| $$   \\$$ |   | \n");
	kprintf("     |   | | $$ \\$$\\ | $$      | $$| $$$$$$\\ | $$| $$$$$$$$| $$       |   | \n");
	kprintf("     |   | | $$  \\$$\\| $$      | $$| $$  \\$$\\| $$ \\$$     \\| $$       |   | \n");
	kprintf("     |   |  \\$$   \\$$ \\$$       \\$$ \\$$   \\$$ \\$$  \\$$$$$$$ \\$$       |   | \n");
	kprintf("     |   |   ______    ______                                         |   | \n");
	kprintf("     |   |  /      \\  /      \\                                        |   | \n");
	kprintf("     |   | |  $$$$$$\\|  $$$$$$\\                                       |   | \n");
	kprintf("     |   | | $$  | $$| $$___\\$$                                       |   | \n");
	kprintf("     |   | | $$  | $$ \\$$    \\                                        |   | \n");
	kprintf("     |   | | $$  | $$ _\\$$$$$$\\                                       |   | \n");
	kprintf("     |   | | $$__/ $$|  \\__| $$                                       |   | \n");
	kprintf("     |   |  \\$$    $$ \\$$    $$                                       |   | \n");
	kprintf("     |   |   \\$$$$$$   \\$$$$$$                                        |   | \n");
	kprintf("     |___|------------------------------------------------------------|___| \n");
	kprintf("    (_____) v0.2.0-alpha                          (c) 2026 KriklerOS (_____)\n");
}

void kmain(unsigned int magic, multiboot_info_t* mbi)
{
	vga_init();
    gdt_init();
    idt_init();
    pit_init(CLOCKS_PER_SEC);

	print_banner();
	kprintf("\n                    --- Press any key to start KriklerOS ---                   ");
	kgetc();
	vga_clear();

	kprintf("Welcome to KriklerOS!\n");
	kprintf("Type \"help\" to see available commands.\n\n");

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC) kprintf("Invalid Multiboot Magic: %x\n", magic);
    
    char input[64];
    while(1) {
        kprintf("root@krikleros:~$ ");
        kgets(input, 64);
		if (strlen(input) == 0) continue;
        
        if (strcmp(input, "hello") == 0)
		{
            kprintf("Hello to you too!\n");
        }
		else if (strcmp(input, "uptime") == 0)
		{
            kprintf("Uptime: %d seconds\n", get_uptime_s());
        }
		else if (strcmp(input, "date") == 0)
		{
			print_date();
		}
		else if (strcmp(input, "clear") == 0)
		{
			vga_clear();
		}
		else if (strcmp(input, "help") == 0)
		{
			kprintf("Commands:\nhello\nuptime\ndate\nclear\ninfo\nmem\nmmap\nreboot\n");
		}
		else if (strcmp(input, "info") == 0)
		{
			shell_cpu();
		}
		else if (strcmp(input, "reboot") == 0)
		{
			shell_reboot();
		}
		else if (strcmp(input, "mem") == 0)
		{
            if (mbi->flags & 0x01)
			{
                uint32_t total_kb = mbi->mem_lower + mbi->mem_upper;
                kprintf("Lower Memory: %u KB\n", mbi->mem_lower);
                kprintf("Upper Memory: %u KB\n", mbi->mem_upper);
                kprintf("Total RAM:    %u MB\n", total_kb / 1024);
            }
			else
			{
                kprintf("Memory information not provided by bootloader.\n");
            }
        }
        else if (strcmp(input, "mmap") == 0)
		{
            kprintf("MMap Addr: %p, Length: %d bytes\n", mbi->mmap_addr, mbi->mmap_length);
        }
		else
		{
            kprintf("Unknown command: %s\n", input);
        }
    }

	for(;;) __asm__ volatile("hlt");
}