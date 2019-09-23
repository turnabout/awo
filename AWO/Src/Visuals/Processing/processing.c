#include <stdio.h>
#include "_processing_internal.h"

SDL_Texture* apply_palette(SDL_Renderer* rend, Palette_Tree* palette, int w, int h)
{
    SDL_Texture* streaming_texture = SDL_CreateTexture(
        rend, 
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_STREAMING, 
        w, 
        h
    );

    // Transfer contents of temp texture over to the streaming texture
    Uint32* s_pixels; // Pointer filled with pixel data
    int s_pitch;      // Length of a row of s_pixels in bytes

    SDL_LockTexture(streaming_texture, NULL, &s_pixels, &s_pitch);
    SDL_RenderReadPixels(rend, NULL, SDL_PIXELFORMAT_RGBA8888, s_pixels, s_pitch);

    // Get pixel count
    SDL_PixelFormat* mapping_format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    int pixel_count = (s_pitch / mapping_format->BytesPerPixel) * h;
    SDL_FreeFormat(mapping_format);

    // Apply color palette to every pixel
    for (int i = 0; i < pixel_count; i++) {

        // Ignore transparent pixels
        if (s_pixels[i] == 0) {
            continue;
        }

        // Swap pixel according to palette
        Uint32 color_to;
        if ((color_to = PT_get_value(palette, s_pixels[i] >> 24)) != -1) {
            s_pixels[i] = color_to;
        } else {
            printf("Color '%d' not found in palette\n", s_pixels[i] >> 24);
        }
    }

    SDL_UnlockTexture(streaming_texture);
    return streaming_texture;
}
