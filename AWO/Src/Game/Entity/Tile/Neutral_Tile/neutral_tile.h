#pragma once

#include "types.h"
#include "Game/Clock/game_clock.h"
#include "Game/Data/Animation/animation.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Entity/Tile/tile_render_grid_update.h"

typedef struct Neutral_Tile {

    // This tile's animation.
    Animation* animation;

    // The coordinates of every instances of this tile present in the game.
    Point* positions;

    // This tile's type.
    Tile_Type type;

    // This tile's variation.
    Tile_Variation variation;

    // How many instances of this tile exist in the game.
    Uint16 count;

} Neutral_Tile;

/*! @brief Creates a neutral tile (plain/river/etc).
 *
 *  @param[in] game_clock The game's clock struct.
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] tile_type The type of the created tile.
 *  @param[in] tile_variation The variation of the created tile.
 *  @return The created neutral tile.
 */
Neutral_Tile* create_neutral_tile(
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Type type, 
    Tile_Variation variation,
    tile_update_render_grid_cb* update_render_grid_cb
);