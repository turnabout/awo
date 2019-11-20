#include <stdlib.h>

#include "conf.h"
#include "Game/Entity/Tile/Neutral_Tile/neutral_tile.h"
#include "Game/Entity/Tile/Neutral_Tile/_neutral_tile_animation_update.h"

#include "Game/Data/Palette/game_palette.h"
#include "Game/Renderer/game_renderer.h"

Neutral_Tile* create_neutral_tile(
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Type type,
    Tile_Variation variation,
    Uint8 x,
    Uint8 y
)
{
    Neutral_Tile* tile = (Neutral_Tile*)malloc(sizeof(Neutral_Tile));


    tile->type = type;
    tile->variation = variation;
    tile->x = x;
    tile->y = y;

    // Get the tile's animation data & attempt to register it with the game clock module.
    Animation_Clock_Index clock_index;
    Animation_Sub_Clock_Index sub_clock_index;

    gather_tile_data(tiles_data, type, variation, &clock_index, &sub_clock_index, &tile->animation);
    register_game_clock_tile(game_clock, (Tile*)tile, clock_index, sub_clock_index);

    // Set the appropriate render grid update callback function
    // Use multi-layered cb if height of frame is that of two regular-sized frames
    if (tile->animation->frames->height == (DEFAULT_TILE_SIZE * 2)) {
        tile->update_render_grid_cb = update_multi_layered_tile_render_grid;
    } else {
        tile->update_render_grid_cb = update_regular_tile_render_grid;
    }

    update_tile_layer_pixel(
        TILE_LAYER_0,
        x,
        y,
        (vec4){
            tile->animation->frames[0].raw_top_left[0],
            tile->animation->frames[0].raw_top_left[1],
            get_active_tile_palette_index(0),
            0.0f
        }
    );

    tile->update_render_grid_cb(tile, 0);

    return tile;
}
