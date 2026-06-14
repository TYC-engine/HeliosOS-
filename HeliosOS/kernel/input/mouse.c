#include "mouse.h"
#include "../gfx/framebuffer.h"

static MouseState mouse;

MouseState* mouse_get()
{
    return &mouse;
}

void mouse_irq_handler(uint8_t data)
{
    mouse.packet[mouse.packet_phase] = data;
    mouse.packet_phase++;

    if(mouse.packet_phase < 3)
        return;

    mouse.packet_phase = 0;

    uint8_t flags = mouse.packet[0];

    int dx = mouse.packet[1];
    int dy = mouse.packet[2];

    if(flags & 0x10) dx |= 0xFFFFFF00;
    if(flags & 0x20) dy |= 0xFFFFFF00;

    mouse.x += dx;
    mouse.y -= dy;

    if(mouse.x < 0) mouse.x = 0;
    if(mouse.y < 0) mouse.y = 0;
}
