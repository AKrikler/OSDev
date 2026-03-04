section .text
extern isr_handler
extern irq_handler

%macro IRQ 2
  global irq%1
  irq%1:
    push 0
    push %2
    jmp irq_common
%endmacro

%macro ISR_NOERRCODE 1
global isr%1
isr%1:
    push 0
    push %1
    jmp isr_common
%endmacro

%macro ISR_ERRCODE 1
global isr%1
isr%1:
    push %1
    jmp isr_common
%endmacro

global isr_stub_table

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8 ; Double Fault
ISR_NOERRCODE 9 ; Coprocessor Segment Overrun
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15 ; Reserved
ISR_NOERRCODE 16 ; x87 FPU Error
ISR_ERRCODE   17 ; Alignment Check
ISR_NOERRCODE 18 ; Machine Check
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

global irq_stub_table

; Master PIC (IRQ 0-7)
IRQ 0, 32	; Programmable Interrupt Timer
IRQ 1, 33	; Keyboard
IRQ 2, 34	; Cascade (Used internally by the PIC)
IRQ 3, 35	; COM2 (if enabled)
IRQ 4, 36	; COM1 (if enabled)
IRQ 5, 37	; LPT2 (if enabled)
IRQ 6, 38	; Floppy Disk Controller
IRQ 7, 39	; LPT1 / Spurious Interrupts

; Slave PIC (IRQ 8-15)
IRQ 8, 40	; CMOS Real Time Clock
IRQ 9, 41	; Free for peripherals / legacy SCSI / NIC
IRQ 10, 42	; Free for peripherals / NIC
IRQ 11, 43	; Free for peripherals / NIC
IRQ 12, 44	; PS2 Mouse
IRQ 13, 45	; FPU / Coprocessor / Inter-processor
IRQ 14, 46	; Primary ATA Channel (Hard Disk)
IRQ 15, 47	; Secondary ATA Channel

irq_common:
    pushad
    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    push esp
    call irq_handler

    add esp, 4
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popad
    add esp, 8
    iret

isr_common:
    pushad
	mov ax, ds
	push eax

	mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

	push esp
    call isr_handler

	add esp, 4
	pop eax
	mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
	popad
	add esp, 8
    iret

section .data
    isr_stub_table dd isr0, isr1, isr2, isr3, isr4, isr5, isr6, isr7, isr8, isr9, isr10, isr11, isr12, isr13, isr14, isr15, isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23, isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31 
	irq_stub_table dd irq0, irq1, irq2, irq3, irq4, irq5, irq6, irq7, irq8, irq9, irq10, irq11, irq12, irq13, irq14, irq15