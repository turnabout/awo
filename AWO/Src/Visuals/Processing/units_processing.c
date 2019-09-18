#include <stdio.h>
#include <SDL.h>

#include "game.h"
#include "../processing.h"
#include "../data_access.h"

void draw_anim(Game* game, Animation** src_anims, Animation** dst_anims, unit_anim dst_anim, int flip);

SDL_Texture* create_units_texture(Game* game, unit_var type_var, unit_var color_var)
{
    SS_Meta_Data* ss_meta_data = access_units_ss_meta_data();
    SDL_Rect* src = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    SDL_Rect* dst = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    Unit_Palette* u_palette = get_unit_palette(color_var);

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
        Animation** src_anims = access_unit_src_anims(u_type, type_var);
        Animation** dst_anims = access_unit_dst_anims(u_type);

        for (unit_anim u_anim = UNIT_ANIM_FULL_FIRST; u_anim <= UNIT_ANIM_FULL_LAST; u_anim++) {
            draw_anim(game, src_anims, dst_anims, u_anim, u_palette->flip);
        }
    }

    // 2. Make a texture used to colorize and flip the sprites
    SDL_Texture* streaming_texture = SDL_CreateTexture(
        game->rend, 
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_STREAMING, 
        ss_meta_data->dst_width, 
        ss_meta_data->dst_height
    );

    // Transfer contents of temp texture over to the streaming texture
    Uint32* s_pixels; // Pointer filled with pixel data
    int s_pitch;      // Length of a row of s_pixels in bytes

    SDL_LockTexture(streaming_texture, NULL, &s_pixels, &s_pitch);
    SDL_RenderReadPixels(game->rend, NULL, SDL_PIXELFORMAT_RGBA8888, s_pixels, s_pitch);

    // Get pixel count
    SDL_PixelFormat* mapping_format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    int pixel_count = (s_pitch / mapping_format->BytesPerPixel) * ss_meta_data->dst_height;
    SDL_FreeFormat(mapping_format);

    // Apply color palette to every pixel
    for (int i = 0; i < pixel_count; i++) {

        // Ignore transparent pixels
        if (s_pixels[i] == 0) {
            continue;
        }

        // Swap pixel according to palette
        Uint32 color_to;
        if ((color_to = get_p_node_val(u_palette->palette, s_pixels[i] >> 24)) != -1) {
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
    free_unit_palette(u_palette);

    SDL_SetTextureBlendMode(streaming_texture, SDL_BLENDMODE_BLEND);
    return streaming_texture;
}

void draw_anim(Game* game, Animation** src_anims, Animation** dst_anims, unit_anim dst_anim, int flip)
{
    unit_anim src_anim = dst_anim;

    switch (dst_anim) {
    case Done:
        src_anim = Idle;
        break;
    case Left:
        src_anim = Right;
        break;
    }

    // Flip the sprite if:
    // 1. The destination animation is Idle/Done AND "flip" is true
    // 2. The destination animation is Left
    SDL_RendererFlip flip_arg = 
        (flip == 1 && (dst_anim == Idle || dst_anim == Done)) || dst_anim == Left
            ? SDL_FLIP_HORIZONTAL
            : SDL_FLIP_NONE;

    // Draw every individual frame
    for (int i = 0; i < src_anims[src_anim]->count; i++) {
        SDL_RenderCopyEx(
            game->rend, 
            game->ss, 
            &src_anims[src_anim]->frames[i], 
            &dst_anims[dst_anim]->frames[i],
            0,
            NULL,
            flip_arg
        );
    }
}
