#include "gui.h"
#include "../gfx/compositor.h"
#include <stdlib.h>

#define MAX_WINDOWS 32

static Window* windows[MAX_WINDOWS];
static int window_count = 0;

void gui_init()
{
    window_count = 0;
}

void gui_add_window(Window* win)
{
    if(window_count < MAX_WINDOWS)
        windows[window_count++] = win;
}
