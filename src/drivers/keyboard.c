#include <drivers/keyboard.h>
#include <arch/i386/io.h>
#include <klibc/stdio.h>

#define KBD_DATA_PORT 0x60
#define KBD_SCAN_SET_GET 0xF0

#define KBD_BUFFER_SIZE 128

static char char_set[128] = { 0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 
	0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ' };

static char kbd_buffer[KBD_BUFFER_SIZE];
static int head = 0, tail = 0;

void keyboard_handler(registers_t* regs)
{
	(void)regs;
	uint8_t scancode = inb(KBD_DATA_PORT);
	
	if (scancode & 0x80)
	{
        // TODO: Release modifiers
    }
	else
	{
        char c = char_set[scancode];
        if (c > 0)
		{
			int next = (head + 1) % KBD_BUFFER_SIZE;
			if (next != tail)
			{
				kbd_buffer[head] = c;
				head = next;
			}
		}
    }
}

char keyboard_pop_char(void)
{
	if (head == tail) return 0;
	char c = kbd_buffer[tail];
	tail = (tail + 1) % KBD_BUFFER_SIZE;
	return c;
}