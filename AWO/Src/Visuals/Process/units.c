#include <SDL.h>
#include "../../game.h"

SDL_Texture* create_units_texture(Game* game)
{
    int tex_width = 293;
    int tex_height = 275;
    int units_origin_x = 336;
    int units_origin_y = 0;

    SDL_Rect src, dst;

    SDL_Texture* temp = SDL_CreateTexture(
        game->rend,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        293,
        275
    );

    SDL_SetRenderTarget(game->rend, temp);

    // Clear the whole thing first
    SDL_SetRenderDrawColor(game->rend, 0, 0, 0, 0);
    SDL_RenderClear(game->rend);

    // Add every unit from source to destination
    src.x = 213 + units_origin_x;
    src.y = 64 + units_origin_y;
    src.w = 15;
    src.h = 16;

    dst.x = 202;
    dst.y = 0;
    dst.w = 15;
    dst.h = 16;

    SDL_RenderCopy(game->rend, game->ss, &src, &dst);

    // Make streaming texture to apply palette to greyscale sprites
    SDL_Texture* streaming_texture = SDL_CreateTexture(
        game->rend, 
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_STREAMING, 
        tex_width, 
        tex_height
    );

    void* m_pixels;
    int pitch;

    SDL_LockTexture(streaming_texture, NULL, &m_pixels, &pitch);
    SDL_RenderReadPixels(game->rend, NULL, SDL_PIXELFORMAT_RGBA8888, m_pixels, pitch);

    // Apply keymap
    SDL_PixelFormat* mapping_format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

    // Get pixel data
    Uint32* pixels = (Uint32*)m_pixels;
    int pixel_count = (pitch / mapping_format->BytesPerPixel) * tex_height;

    // Map colors
    // Test swapping black pixels with red pixels
    Uint32 color_key_from = SDL_MapRGBA(mapping_format, 0, 0, 0, 0xFF);
    Uint32 color_key_to = SDL_MapRGBA(mapping_format, 0xFF, 0, 0, 0xFF);

    // printf("%X\n", color_key_from >> 24);
    // printf("%X\n", color_key_to >> 24);

    /*
    for (int i = 0; i < pixel_count; i++) {

        Uint32 pixel = pixels[i];

        if (pixels[i] == color_key_from) {
            pixels[i] = color_key_to;
        }
    }*/

    SDL_UnlockTexture(streaming_texture);
    SDL_FreeFormat(mapping_format);

    // Reset to default render target & clean up temp texture
    SDL_SetRenderTarget(game->rend, NULL);
    SDL_DestroyTexture(temp);

    return streaming_texture;
}
