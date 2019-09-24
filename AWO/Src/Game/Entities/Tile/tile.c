#include <SDL.h>

#include "conf.h"
#include "tile.h"
#include "Game/Clock/game_clock.h"
#include "Visuals/visuals_data.h"

#pragma warning( disable: 6011 6386 )

struct Tile {
    SDL_Texture* src_texture; // Pointer to texture used to draw this tile
    SDL_Rect draw_rect;       // The tile's draw rectangle
    SDL_Rect* anim_frames;    // Frame arrays for this tile's animation
    int* anim_index;          // Pointer to sub-clock tick used to update this tile's animation
};

Tile* tile_create(
    Game_Clock* gc, 
    Tiles_Data* td, 
    SDL_Texture* src_texture, 
    tile_type tt,
    tile_var tv,
    int x,
    int y
)
{
    Tile* t = (Tile*)malloc(sizeof(Tile));

    // Get tile data for this tile
    Animation_Clock_Index clock;
    Animation_Sub_Clock_Index sub_clock;

    t->anim_frames = TD_gather_tile_data(td, tt, tv, &clock, &sub_clock);

    // Get the animation index pointer
    t->anim_index = GC_get_ASC_tick_ptr(gc, clock, sub_clock);

    // Set the starting draw rectangle
    SDL_Rect draw_rect = {
        x,
        y,
        t->anim_frames[0].w,
        t->anim_frames[0].h,
    };

    t->src_texture = src_texture;
    t->draw_rect = draw_rect;
    return t;
}

void tile_draw(Tile* t, SDL_Renderer* rend)
{
    SDL_RenderCopy(
        rend, 
        t->src_texture, 
        &t->anim_frames[*t->anim_index], 
        &t->draw_rect
    );
}