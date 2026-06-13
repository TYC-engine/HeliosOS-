#include "screen.h"

static uint16_t* const VGA = (uint16_t*)0xB8000;

static int row = 0;
static int col = 0;

static uint8_t color = 0x0F;

void clear_screen()
{
    for(int i = 0; i < 80 * 25; i++)
        VGA[i] = (color << 8) | ' ';

    row = 0;
    col = 0;
}

void putchar(char c)
{
    if(c == '\n')
    {
        col = 0;
        row++;
        return;
    }

    VGA[row * 80 + col] = (color << 8) | c;

    col++;

    if(col >= 80)
    {
        col = 0;
        row++;
    }

    if(row >= 25)
        row = 0;
}

void print(const char* str)
{
    while(*str)
        putchar(*str++);
}
