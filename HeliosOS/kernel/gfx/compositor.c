#include "compositor.h"
#include "../framebuffer.h"

void compositor_init()
{
}

void compositor_present(Surface* desktop)
{
    for(int y = 0; y < desktop->height; y++)
    {
        for(int x = 0; x < desktop->width; x++)
        {
            fb_putpixel(x, y, desktop->buffer[y * desktop->width + x]);
        }
    }
}
