#include <SDL.h>

#include "game.h"
#include "../processing.h"
#include "../data_access.h"

SDL_Texture* create_units_texture(Game* game, unit_var type_var, unit_var color_var)
{
    SS_Meta_Data* ss_meta_data = access_units_ss_meta_data();
    SDL_Rect src, dst;

    // 1. Make a texture used to draw every individual unit sprite on
    SDL_Texture* temp = SDL_CreateTexture(
        game->rend,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        ss_meta_data->dst_width, 
        ss_meta_data->dst_height
    );

    SDL_SetRenderTarget(game->rend, temp);
    SDL_RenderClear(game->rend);

    // Draw every unit sprite on the texture
    for (unit_type u_type = UNIT_TYPE_FIRST; u_type <= UNIT_TYPE_LAST; u_type++) {
        Animation** u_var_anims = access_unit_src_var(u_type, type_var);

        printf("\n\n%s\n", unit_type_str[u_type]);
        print_anim_contents(u_var_anims[Idle]);
    }

    // access_unit_src_var(unit_type type, unit_var var)

    src.x = ss_meta_data->src_x + 213;
    src.y = ss_meta_data->src_y + 64;
    src.w = 15;
    src.h = 16;

    dst.x = 0;
    dst.y = 0;
    dst.w = 15;
    dst.h = 16;

    SDL_RenderCopy(game->rend, game->ss, &src, &dst);

    // 2. Make a texture used to colorize and flip the sprites
    SDL_Texture* streaming_texture = SDL_CreateTexture(
        game->rend, 
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_STREAMING, 
        ss_meta_data->dst_width, 
        ss_meta_data->dst_height
    );

    void* m_pixels;
    int pitch;

    // Transfer contents of first texture over to this one
    SDL_LockTexture(streaming_texture, NULL, &m_pixels, &pitch);
    SDL_RenderReadPixels(game->rend, NULL, SDL_PIXELFORMAT_RGBA8888, m_pixels, pitch);

    // Apply keymap
    SDL_PixelFormat* mapping_format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

    // Get pixel data
    Uint32* pixels = (Uint32*)m_pixels;
    int pixel_count = (pitch / mapping_format->BytesPerPixel) * ss_meta_data->dst_height;

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

    SDL_SetTextureBlendMode(streaming_texture, SDL_BLENDMODE_BLEND);
    return streaming_texture;
}
