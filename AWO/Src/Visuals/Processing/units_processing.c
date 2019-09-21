#include <stdio.h>

#include "Visuals/visuals_processing.h"

// Draws every animations of the given unit type
void draw_unit_texture_anims(Game* game, unit_type u_type, unit_var u_var);

SDL_Texture* create_units_texture(Game* game, unit_var type_var, unit_var color_var)
{
    // Get sprite sheet metadata
    SS_Metadata* metadata = UD_get_ss_metadata(game->ud);

    // Get palette data
    int palette_flip;
    Palette_Tree* palette = UD_get_palette(game->ud, color_var, &palette_flip);

    // 1. Make a texture used to draw every individual unit sprite on
    SDL_Texture* temp = SDL_CreateTexture(
        game->rend,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        metadata->dst_w, 
        metadata->dst_h
    );

    SDL_SetRenderTarget(game->rend, temp);
    SDL_RenderClear(game->rend);

    // Draw every unit sprite on the texture
    for (unit_type u_type = UNIT_TYPE_FIRST; u_type <= UNIT_TYPE_LAST; u_type++) {
        draw_unit_texture_anims(game, u_type, type_var);
    }

    // 2. Make a texture used to colorize and flip the sprites
    SDL_Texture* streaming_texture = SDL_CreateTexture(
        game->rend, 
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_STREAMING, 
        metadata->dst_w, 
        metadata->dst_h
    );

    // Transfer contents of temp texture over to the streaming texture
    Uint32* s_pixels; // Pointer filled with pixel data
    int s_pitch;      // Length of a row of s_pixels in bytes

    SDL_LockTexture(streaming_texture, NULL, &s_pixels, &s_pitch);
    SDL_RenderReadPixels(game->rend, NULL, SDL_PIXELFORMAT_RGBA8888, s_pixels, s_pitch);

    // Get pixel count
    SDL_PixelFormat* mapping_format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    int pixel_count = (s_pitch / mapping_format->BytesPerPixel) * metadata->dst_h;
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
            printf(
                "Color '%d' not found in palette for color variation '%s'\n", 
                s_pixels[i] >> 24, 
                unit_type_str[color_var]
            );
        }
    }

    SDL_UnlockTexture(streaming_texture);

    // Reset to default render target & clean up temp texture/palette
    SDL_SetRenderTarget(game->rend, NULL);
    SDL_DestroyTexture(temp);
    PT_free(palette);

    SDL_SetTextureBlendMode(streaming_texture, SDL_BLENDMODE_BLEND);
    return streaming_texture;
}

void draw_unit_texture_anims(Game* game, unit_type u_type, unit_var u_var)
{
    Animation** src_anims = UD_get_src_anims(game->ud, u_type, u_var);
    Animation** dst_anims = UD_get_dst_anims(game->ud, u_type);

    // Draw every animation
    for (unit_anim u_anim = UNIT_ANIM_FIRST; u_anim <= UNIT_ANIM_LAST; u_anim++) {

        // TODO: use functionality hidden in animation to loop every frame instead
        // Draw every frame of the animation
        for (int i = 0; i < src_anims[u_anim]->count; i++) {
            SDL_RenderCopy(
                game->rend, 
                game->ss, 
                &src_anims[u_anim]->frames[i], 
                &dst_anims[u_anim]->frames[i]
            );
        }
    }
}
