void kmain(void)
{
    *((unsigned short*)0xB8000) = 0x0F58;


    while(1) { __asm__ volatile("hlt"); }
}