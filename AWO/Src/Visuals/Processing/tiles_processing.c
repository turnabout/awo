#include "conf.h"
#include "../visuals_processing.h"
#include "_processing_internal.h"

void draw_tile_texture_anims(Game* game, Tile_Type t_type);

SDL_Texture* create_tiles_texture(Game* game, Weather weather)
{
    SDL_SetRenderDrawColor(game->rend, 0, 0, 0, 0);

    // Get palette & ss metadata
    Palette_Tree* palette = TD_get_palette(game->td, weather);
    SS_Metadata* metadata = TD_get_ss_metadata(game->td);

    // 1. Make a texture used to draw every individual tile sprite on
    SDL_Texture* temp = SDL_CreateTexture(
        game->rend,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        metadata->src_w, 
        metadata->src_h
    );

    SDL_SetRenderTarget(game->rend, temp);
    SDL_RenderClear(game->rend);

    // Draw every unit sprite on the texture
    draw_tile_texture_anims(game, Plain);
    draw_tile_texture_anims(game, Plain);

    for (Tile_Type t_type = TILE_TYPE_FIRST; t_type < TILE_TYPE_COUNT; t_type++) {
        draw_tile_texture_anims(game, t_type);
    }

    // 2. Generate new texture with palette applied to it
    SDL_Texture* res_texture = apply_palette(
        game->rend, 
        palette, 
        metadata->src_w, 
        metadata->src_h
    );

    // Reset to default render target & clean up temp texture/palette
    SDL_SetRenderTarget(game->rend, NULL);
    SDL_DestroyTexture(temp);
    PT_free(palette);

    SDL_SetTextureBlendMode(res_texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(game->rend, GAME_BG_R, GAME_BG_G, GAME_BG_B, GAME_BG_A);

    return res_texture;
}

void draw_tile_texture_anims(Game* game, Tile_Type t_type)
{
    Animation* anim;
        
    // Loop every variation of this tile type
    while ((anim = TD_get_next_tile_animation(game->td, t_type)) != NULL) {
        int frame_count;
        SDL_Rect* anim_frames = anim_get_frames(anim, &frame_count);

        for (int i = 0; i < frame_count; i++) {
            SDL_RenderCopy(
                game->rend,
                game->ss,
                &anim_frames[i],
                &anim_frames[i]
            );
        }
    }
}
