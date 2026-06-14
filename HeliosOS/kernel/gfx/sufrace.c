#include "surface.h"
#include <stdlib.h>

Surface surface_create(int w, int h)
{
    Surface s;
    s.width = w;
    s.height = h;
    s.buffer = (uint32_t*)malloc(w * h * 4);
    return s;
}

void surface_setpixel(Surface* s, int x, int y, uint32_t color)
{
    if(x < 0 || y < 0 || x >= s->width || y >= s->height)
        return;

    s->buffer[y * s->width + x] = color;
}
