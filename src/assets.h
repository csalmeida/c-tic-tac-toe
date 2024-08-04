#ifndef ASSETS_H_
#define ASSETS_H_

// Include the generated header files, includes binary data and length:
#include "assets/X.h"
#include "assets/O.h"

// Defines the required data for an embedded image:
typedef struct {
    const char *filename;
    const unsigned char *data;
    int data_len;
} EmbeddedImage;

// An array with all the embedded assets the game requires:
EmbeddedImage embedded_images[] = {
    { "X.bmp", src_assets_X_bmp, src_assets_X_bmp_len },
    { "O.bmp", src_assets_O_bmp, src_assets_O_bmp_len },
};

// Loads image from binary data: 
SDL_Surface *load_surface_from_memory(const unsigned char *data, int data_len)
{
    SDL_RWops *rw = SDL_RWFromConstMem(data, data_len);
    if (!rw) {
        fprintf(stderr, "Could not create RWops from memory\n");
        return NULL;
    }

    SDL_Surface *image_surface = IMG_Load_RW(rw, 1);
    if (!image_surface) {
        fprintf(stderr, "Could not load image from memory: %s\n", IMG_GetError());
        return NULL;
    }

    return image_surface;
}

// Loads a image asset or throws an error;
SDL_Surface *load_surface(char const *path)
{
    SDL_Surface *image_surface = IMG_Load(path);

    if(!image_surface) {
      fprintf(stderr, "Could not load BMP image for path: %s\n", path);
      return 0;
    }

    return image_surface;
}

#endif // ASSETS_H_