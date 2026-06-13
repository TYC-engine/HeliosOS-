#include "screen.h"
#include "keyboard.h"
#include "pit.h"

void irq_handler(int irq)
{
    if(irq == 0)
        pit_irq();

    if(irq == 1)
        keyboard_irq();

    outb(0x20, 0x20);
}
