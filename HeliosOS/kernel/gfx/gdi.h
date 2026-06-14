#ifndef GDI_H
#define GDI_H

#include "surface.h"

void gdi_clear(Surface* s, uint32_t color);
void gdi_rect(Surface* s, int x, int y, int w, int h, uint32_t color);

#endif
