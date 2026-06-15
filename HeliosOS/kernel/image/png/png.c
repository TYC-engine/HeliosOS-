#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "png.h"
#include "../fs/file.h"
#include <stdlib.h>

Image* png_load(const char* path) {
    int w, h, c;

    unsigned char* data = stbi_load(path, &w, &h, &c, 4);
    if (!data) return 0;

    Image* img = malloc(sizeof(Image));
    img->width = w;
    img->height = h;
    img->data = data;

    return img;
}
