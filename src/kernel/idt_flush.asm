global idt_flush

idt_flush:
    mov eax, [esp + 4]
    lidt [eax]
.flush_done:
    ret