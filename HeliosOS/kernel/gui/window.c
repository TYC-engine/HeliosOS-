#include "window.h"
#include "../gfx/surface.h"
#include "../gfx/gdi.h"
#include <string.h>
#include <stdlib.h>

Window* window_create(int x, int y, int w, int h, const char* title)
{
    Window* win = (Window*)malloc(sizeof(Window));

    win->x = x;
    win->y = y;
    win->w = w;
    win->h = h;

    win->buffer = (uint32_t*)malloc(w * h * 4);

    win->visible = 1;

    for(int i = 0; i < 31 && title[i]; i++)
        win->title[i] = title[i];

    win->title[31] = 0;

    return win;
}

void window_draw(Window* win)
{
    if(!win->visible)
        return;

    // фон окна
    for(int y = 0; y < win->h; y++)
    {
        for(int x = 0; x < win->w; x++)
        {
            win->buffer[y * win->w + x] = 0x2B2B2B;
        }
    }

    // заголовок
    for(int x = 0; x < win->w; x++)
    {
        win->buffer[x] = 0x1E90FF;
    }
}
