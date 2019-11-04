#include <stdlib.h>

#include "conf.h"
#include "Game/Entity/Tile/tile.h"

struct Tile {

    // This tile's type.
    Tile_Type type;

    // This tile's animation.
    Animation* animation;

    // Pointer to sub-clock tick used to update this tile's animation.
    int* animation_index_ptr;
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

    // Get tile data for this tile
    Animation_Clock_Index clock_index;
    Animation_Sub_Clock_Index sub_clock_index;

    // Gather clock index, sub clock index and the tile animation.
    gather_tile_data(
        tiles_data,
        type,
        variation,
        &clock_index,
        &sub_clock_index,
        &tile->animation
    );

    // Get the animation index pointer
    tile->animation_index_ptr = get_game_clock_tick_ptr(game_clock, clock_index, sub_clock_index);

    return tile;
}

void draw_tile(Tile* tile, Sprite_Batch* sprite_batch, GLfloat palette_index, vec2 destination)
{
    add_to_sprite_batch(
        sprite_batch, 
        destination,
        &(tile->animation->frames[*tile->animation_index_ptr]),
        palette_index
    );
}

void free_tile(Tile* tile)
{
    // TODO
}

Tile_Type get_tile_type(Tile* tile)
{
    return tile->type;
}