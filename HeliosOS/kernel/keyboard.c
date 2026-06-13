#include "ports.h"

static char last_key = 0;

static const char keymap[128] =
{
    0,27,'1','2','3','4','5','6',
    '7','8','9','0','-','=',
    '\b','\t',
    'q','w','e','r','t','y','u','i',
    'o','p','[',']','\n',0,
    'a','s','d','f','g','h','j','k',
    'l',';','\'','`',0,'\\',
    'z','x','c','v','b','n','m',',',
    '.','/',0,'*',0,' '
};

void keyboard_irq()
{
    unsigned char scancode = inb(0x60);

    if(scancode < 128)
        last_key = keymap[scancode];
}

char keyboard_get_last()
{
    char c = last_key;
    last_key = 0;
    return c;
}
