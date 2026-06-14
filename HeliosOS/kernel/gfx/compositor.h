#ifndef COMPOSITOR_H
#define COMPOSITOR_H

#include "surface.h"

void compositor_init();
void compositor_present(Surface* desktop);

#endif
