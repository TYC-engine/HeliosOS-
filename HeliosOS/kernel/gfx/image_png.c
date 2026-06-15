// подключаешь lodepng.c в kernel build

#include "image.h"
#include "lodepng.h"

image_t* load_png_from_memory(const void* data, size_t size)
{
    unsigned char* out;
    unsigned w, h;

    unsigned err = lodepng_decode32(&out, &w, &h, data, size);
    if (err) return 0;

    image_t* img = malloc(sizeof(image_t));
    img->width = w;
    img->height = h;
    img->pixels = (uint32_t*)out;

    return img;
}
