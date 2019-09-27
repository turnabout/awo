#include <stdlib.h>

#include "unit.h"
#include "Visuals/Data/Animation/animation.h"

struct Unit {
    SDL_Rect draw_rect;       // Unit's draw rectangle (where to draw on screen)
    SDL_Texture* src_texture; // Pointer to texture used to draw this unit

    int* anim_index; // Pointer to sub-clock tick which dictates this unit's idle anim index

    SDL_Rect* anims_frames[UNIT_ANIM_COUNT];  // Frame arrays for every animation
    int anims_frames_counts[UNIT_ANIM_COUNT]; // Frame count for every frame array
    Unit_Anim current_anim;                   // Currently active animation
};

Unit* unit_create(Game_Clock* gc, Units_Data* ud, SDL_Texture* src_texture, Unit_Type ut)
{
    Unit* u = (Unit*)malloc(sizeof(Unit));

    // Get pointer to animation frame index (sub-clock tick)
    u->anim_index = GC_get_ASC_tick_ptr(gc, Units_Clock, Pyramid_3_Frames);

    // Store starting animation data
    Animation** anims = UD_get_dst_anims(ud, ut);

    for (Unit_Anim ua = UNIT_ANIM_FIRST; ua < UNIT_ANIM_COUNT; ua++) {
        u->anims_frames[ua] = anim_get_frames(anims[ua], &u->anims_frames_counts[ua]);
    }

    u->current_anim = UNIT_ANIM_FIRST;
    u->src_texture = src_texture;

    // Set start draw rectangle
    SDL_Rect start_draw_rect = { 
        100, 
        100, 
        u->anims_frames[u->current_anim][0].w, 
        u->anims_frames[u->current_anim][0].h
    };

    u->draw_rect = start_draw_rect;

    return u;
}

void unit_update(Unit* u)
{
    // printf("n_columns %d n_lines %d\n", u->anims_frames[u->current_anim][0].n_columns, u->anims_frames[u->current_anim][0].n_lines);
}

void unit_draw(Unit* u, SDL_Renderer* rend)
{
    SDL_RenderCopy(
        rend, 
        u->src_texture, 
        &u->anims_frames[u->current_anim][*u->anim_index], 
        &u->draw_rect
    );
}

void unit_free(Unit* u)
{
    free(u);
}