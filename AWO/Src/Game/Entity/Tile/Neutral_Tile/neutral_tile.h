#pragma once

#include "types.h"
#include "Game/Clock/game_clock.h"
#include "Game/Data/Animation/animation.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Entity/Tile/tile_update_cb.h"

typedef struct Neutral_Tile {

    // This tile's type.
    Tile_Type type;

    // Callback function used to update this tile's corresponding render grid pixels.
    update_tile_render_grid_cb update_animation;

    // Function called when this tile's fog status updates.
    update_fog_status_cb update_palette;

    // Function called to delete this tile.
    delete_tile_cb delete;

    // Coordinates of this tile within the game board.
    Uint8 x, y;


    // This tile's variation.
    Tile_Variation variation;

    // This tile's animation.
    Animation* animation;

} Neutral_Tile;

/*! @brief Creates a neutral tile (plain/river/etc).
 *
 *  @param[in] game_clock The game's clock module.
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] tile_type The type of the created tile.
 *  @param[in] tile_variation The variation of the created tile.
 *  @param[in] x The x coordinate of this tile within the game board.
 *  @param[in] y The y coordinate of this tile within the game board.
 *  @return The created neutral tile.
 */
Neutral_Tile* create_neutral_tile(
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Type type,
    Tile_Variation variation,
    Uint8 x,
    Uint8 y
);

/*! @brief Edits a neutral tile's variation.
 *
 *  @param[in] tile The tile to edit.
 *  @param[in] game_clock The game clock module.
 *  @param[in] tiles_data The tiles data module.
 *  @param[in] new_variation The new variation set to the tile.
 */
void edit_neutral_tile_variation(
    Neutral_Tile* tile,
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Variation new_variation
);