#pragma warning( disable : 6308 28182 )

#include <stdlib.h>

#include "conf.h"
#include "Game/Entity/Tile/tile.h"

struct Tile {

    // This tile's type.
    Tile_Type type;

    // This tile's variation.
    Tile_Variation variation;

    // This tile's animation.
    Animation* animation;

    // Index of the clock this tile subscribes to, to update its animation.
    Animation_Clock_Index clock_index;

    // Index of the sub-clock this tile subscribes to.
    Animation_Sub_Clock_Index sub_clock_index;

    // The coordinates of every instances of this tile present in the game.
    Point* positions;

    // How many instances of this tile exist in the game.
    Uint16 count;

    // Current animation index of tiles of this type/variation.
    Uint8 animation_index;
};

Tile* create_tile(
    Game_Clock* game_clock, 
    Tiles_Data* tiles_data, 
    Tile_Type type, 
    Tile_Variation variation
)
{
    Tile* tile = (Tile*)malloc(sizeof(Tile));

    tile->type = type;
    tile->variation = variation;
    tile->count = 0;
    tile->positions = NULL;
    tile->animation_index = 0;

    // Gather clock index, sub clock index and the tile animation.
    gather_tile_data(
        tiles_data,
        type,
        variation,
        &tile->clock_index,
        &tile->sub_clock_index,
        &tile->animation
    );

    return tile;
}

// Update every render grid cell occupied by this tile.
void update_tile_render_grid(Tile* tile)
{
    update_tile_layer_pixels_low(
        TILE_LAYER_0,
        tile->positions,
        tile->count,
        (vec2) {
            tile->animation->frames[tile->animation_index].raw_top_left[0],
            tile->animation->frames[tile->animation_index].raw_top_left[1]
        }
    );
}

void register_tile_position(Tile* tile, Uint8 x, Uint8 y)
{
    tile->positions = realloc(tile->positions, sizeof(Point) * (tile->count + 1));

    tile->positions[tile->count].x = x;
    tile->positions[tile->count++].y = y;
}

void update_tile_animation_index(Tile* tile, Uint8 index)
{
    tile->animation_index = index;
    update_tile_render_grid(tile);
}

void get_tile_clock_data(
    Tile* tile,
    Animation_Clock_Index* clock_index, 
    Animation_Sub_Clock_Index* sub_clock_index
)
{
    *clock_index = tile->clock_index;
    *sub_clock_index = tile->sub_clock_index;
}

Tile_Type get_tile_type(Tile* tile)
{
    return tile->type;
}

void free_tile(Tile* tile)
{
    if (tile != NULL) {
        free(tile);
        // TODO
    }
}