#include <stdlib.h>

#include "conf.h"
#include "Game/Entity/Tile/tile.h"
#include "Game/Data/Palette/palette.h"

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
};

Tile* create_tile(
    Game_Clock* game_clock, 
    Tiles_Data* tiles_data, 
    Tile_Type type, 
    Tile_Variation variation
)
{
    Tile* tile = (Tile*)malloc(sizeof(Tile));

    printf("%d, %d\n", sizeof(tiles_data), sizeof(type));

    tile->type = type;
    tile->variation = variation;

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

void render_tile(Tile* tile, Game_Renderer* renderer, int x, int y, GLfloat palette_index)
{
    /*
    update_renderer_tiles_layer_pixel(
        renderer,
        TILE_LAYER_0,
        x,
        y,
        (vec4) {
            tile->animation->frames[*(tile->animation_index_ptr)].raw_top_left[0],
            tile->animation->frames[*(tile->animation_index_ptr)].raw_top_left[1],
            palette_index,
            0.0f
        }
    );
*/
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