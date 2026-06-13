#include "ports.h"
#include "screen.h"

void keyboard_irq()
{
    unsigned char scancode;

    scancode = inb(0x60);

    print("K");

    outb(0x20,0x20);
}
