#pragma warning( disable : 6308 28182 )

#include <stdlib.h>

#include "conf.h"
#include "Game/Entity/Tile/tile.h"

typedef struct Tile_Position {
    Uint8 x, y;
} Tile_Position;

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

    // How many of this tile type/variation exist.
    Uint16 count;

    // The x/y position of every tile of this type/variation.
    Tile_Position* positions;

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
    // Bind the tile texture of the tile layer bound to this tile
    bind_tile_layer_texture(TILE_LAYER_0);

    for (int i = 0; i < tile->count; i++) {

        update_renderer_tiles_layer_pixel_low(
            TILE_LAYER_0,
            tile->positions[i].x,
            tile->positions[i].y,
            (vec2) {
                tile->animation->frames[tile->animation_index].raw_top_left[0],
                tile->animation->frames[tile->animation_index].raw_top_left[1]
            }
        );
    }
}

void register_tile_position(Tile* tile, Uint8 x, Uint8 y)
{
    int new_position_index = tile->count++;

    tile->positions = realloc(tile->positions, sizeof(Tile_Position) * tile->count);

    tile->positions[new_position_index].x = x;
    tile->positions[new_position_index].y = y;
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
    }
}