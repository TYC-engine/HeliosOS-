#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include <stddef.h>

typedef struct {
    uint32_t width;
    uint32_t height;
    uint32_t* pixels; // RGBA
} image_t;

image_t* load_bmp(const void* data);
void draw_image(image_t* img, int x, int y);
void free_image(image_t* img);

#endif
