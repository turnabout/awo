#include <stdlib.h>

#include "conf.h"
#include "Game/Entity/Tile/tile.h"
#include "Game/Data/Palette/palette.h"

struct Tile {

    // This tile's type.
    Tile_Type type;

    // This tile's animation.
    Animation* animation;

    // Index of the palette applied to this tile.
    GLfloat palette_index;

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
    tile->palette_index = get_active_tile_palette_index(0);

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

void render_tile(Tile* tile, Game_Renderer* renderer, int x, int y)
{
    update_renderer_tiles_layer_pixel(
        renderer,
        TILE_LAYER_0,
        x,
        y,
        (vec4) {
            tile->animation->frames[*(tile->animation_index_ptr)].raw_top_left[0],
            tile->animation->frames[*(tile->animation_index_ptr)].raw_top_left[1],
            tile->palette_index,
            0.0f
        }
    );
}

void free_tile(Tile* tile)
{
    if (tile != NULL) {
        free(tile);
    }
}

Tile_Type get_tile_type(Tile* tile)
{
    return tile->type;
}