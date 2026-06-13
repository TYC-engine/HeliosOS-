#include "screen.h"
#include "keyboard.h"
#include "pit.h"
#include "idt.h"

extern void pic_remap();

void kernel_main()
{
    clear_screen();

    print("HeliosOS Kernel Booted\n");

    pic_remap();
    idt_init();
    pit_init();

    __asm__ volatile("sti");

    print("System ready\n");
    print("helios> ");

    while(1)
    {
        char c = keyboard_read();

        if(c)
            putchar(c);

        __asm__ volatile("hlt");
    }
}
