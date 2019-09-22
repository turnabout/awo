#include <stdlib.h>
#include <SDL.h>

#include "unit.h"
#include "Visuals/Data/Animation/animation.h"

#pragma warning( disable: 6011 6386 )

struct Unit {
    // SDL_Rect* src_rect; // Destination rectangle (where to get unit from in its texture)
    SDL_Rect draw_rect; // Destination rectangle (where to draw on screen)
    SDL_Texture* src_texture; // Pointer to texture used to draw this unit

    int* anim_index;    // Pointer to sub-clock tick which dictates this unit's animation index

    SDL_Rect* current_anim_frames;
    Animation** anims; // All animations
};

Unit* unit_create(Game* game, SDL_Texture* src_texture, unit_type ut)
{
    Unit* u = (Unit*)malloc(sizeof(Unit));

    u->src_texture = src_texture;

    // Get pointer to animation frame index (sub-clock tick)
    u->anim_index = GC_get_ASC_tick_ptr(game->clock, Units_Clock, Pyramid_3_Frames);

    // Store starting animation data
    u->anims = UD_get_dst_anims(game->ud, ut);
    u->current_anim_frames = anim_get_frames(u->anims[UNIT_ANIM_FIRST], NULL);

    // Set start draw rectangle
    SDL_Rect start_draw_rect = { 
        100, 
        100, 
        u->current_anim_frames[0].w, 
        u->current_anim_frames[0].h 
    };

    u->draw_rect = start_draw_rect;

    /*
    printf("%s\n", unit_type_str[ut]);

    for (unit_anim ua = 0; ua < UNIT_ANIM_AMOUNT; ua++) {
        printf("%s\n", unit_anim_str[ua]);
        anim_print(src_anims[ua]);
    }
    */

    // SDL_Rect* test = anim_get_frames(Animation* anim, int* count);
    // SDL_Rect* anim_get_frames(Animation* anim, int* count);

    return u;
}

void unit_update(Unit* u)
{
    printf("w %d h %d\n", u->current_anim_frames[0].w, u->current_anim_frames[0].h);
}

void unit_draw(Unit* u)
{
}