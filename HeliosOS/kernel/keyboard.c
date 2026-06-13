#include "ports.h"
#include "screen.h"

static char last_key = 0;

static const char map[128] =
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
    unsigned char sc = inb(0x60);

    if(sc < 128)
    {
        last_key = map[sc];
    }

    outb(0x20, 0x20);
}

char keyboard_read()
{
    char c = last_key;
    last_key = 0;
    return c;
}
