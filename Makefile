CC = gcc
AS = nasm
LD = ld

CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra -fno-stack-protector -nostdlib -nostdinc -I$(shell pwd)/include -MMD
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T src/arch/i386/linker.ld -z noexecstack

SRCS_C = $(shell find src -name "*.c")
SRCS_ASM = $(shell find src -name "*.asm")

OBJS = $(SRCS_C:src/%.c=build/%.o)
OBJS += $(SRCS_ASM:src/%.asm=build/%.o)

DEPS = $(OBJS:.o=.d)

all: build/os.bin

build/os.bin: $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: src/%.asm
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

-include $(DEPS)

clean:
	rm -rf build

.PHONY: all clean