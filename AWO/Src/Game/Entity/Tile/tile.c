#include <SDL.h>

#include "conf.h"
#include "tile.h"

struct Tile {
    SDL_Rect* anim_frames; // Frame arrays for this tile's animation
    int* anim_index;       // Pointer to sub-clock tick used to update this tile's animation
    Tile_Type type;
};

Tile* tile_create(Game_Clock* gc, Tiles_Data* td, Tile_Type tt, Tile_Var tv)
{
    Tile* tile = (Tile*)malloc(sizeof(Tile));

    tile->type = tt;

    // Get tile data for this tile
    Animation_Clock_Index clock;
    Animation_Sub_Clock_Index sub_clock;

    tile->anim_frames = TD_gather_tile_data(td, tt, tv, &clock, &sub_clock);

    // Get the animation index pointer
    tile->anim_index = GC_get_ASC_tick_ptr(gc, clock, sub_clock);

    return tile;
}

void tile_draw(Tile* tile, SDL_Renderer* rend, SDL_Texture* texture, int x, int y)
{
    SDL_Rect draw_rect = {
        x,
        y - tile->anim_frames[0].h + DEFAULT_TILE_DIMENSION,
        tile->anim_frames[0].w,
        tile->anim_frames[0].h,
    };

    SDL_RenderCopy(rend, texture, &tile->anim_frames[*tile->anim_index], &draw_rect);
}

void tile_free(Tile* tile)
{
    // TODO
}

Tile_Type tile_get_type(Tile* tile)
{
    return tile->type;
}