#include "conf.h"

#include "Visuals/visuals_processing.h"
#include "_processing_internal.h"

// Draws every animations of the given unit type
void draw_unit_texture_anims(Game* game, Unit_Type u_type, Unit_Var u_var, int flip);

SDL_Texture* create_units_texture(Game* game, Unit_Var type_var, Unit_Var color_var)
{
    SDL_SetRenderDrawColor(game->rend, 0, 0, 0, 0);

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
    for (Unit_Type u_type = UNIT_TYPE_FIRST; u_type < UNIT_TYPE_COUNT; u_type++) {
        draw_unit_texture_anims(game, u_type, type_var, palette_flip);
    }

    // 2. Generate new texture with palette applied to it
    SDL_Texture* res_texture = apply_palette(
        game->rend, 
        palette, 
        metadata->dst_w, 
        metadata->dst_h
    );

    // Reset to default render target & clean up temp texture/palette
    SDL_SetRenderTarget(game->rend, NULL);
    SDL_DestroyTexture(temp);
    PT_free(palette);

    SDL_SetTextureBlendMode(res_texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(game->rend, GAME_BG_R, GAME_BG_G, GAME_BG_B, GAME_BG_A);

    return res_texture;
}

void draw_unit_texture_anims(Game* game, Unit_Type u_type, Unit_Var u_var, int flip)
{
    Animation** src_anims = UD_get_src_anims(game->ud, u_type, u_var);
    Animation** dst_anims = UD_get_dst_anims(game->ud, u_type);

    // Draw every animation
    for (Unit_Anim u_anim = UNIT_ANIM_FIRST; u_anim <= UNIT_ANIM_LAST; u_anim++) {
        int frame_count;
        SDL_Rect* src_frames = anim_get_frames(src_anims[u_anim], &frame_count);
        SDL_Rect* dst_frames = anim_get_frames(dst_anims[u_anim], &frame_count);

        // Draw every frame of the animation
        for (int i = 0; i < frame_count; i++) {
            SDL_RenderCopyEx(
                game->rend, 
                game->ss, 
                &src_frames[i], 
                &dst_frames[i],
                0,
                NULL,
                (flip && u_anim == Idle) ? 1 : 0
            );
        }
    }
}
