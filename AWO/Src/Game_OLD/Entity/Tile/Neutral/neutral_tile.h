#pragma once

#include "types.h"
#include "Game/Clock/game_clock.h"
#include "Game/Data/Animation/animation.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Entity/entity_update_cb.h"

typedef struct Neutral_Tile {

    // `Entity` members
    // Coordinates of this tile within the game board.
    Uint8 x, y;

    // Function called to update this property's corresponding render grid pixels.
    update_entity_render_grid_cb update_grid;

    // Function called to update this property's palette.
    update_entity_palette_cb update_palette;

    // Function called to delete this property.
    delete_entity_cb delete;


    // `Tile` members
    // This tile's type.
    Tile_Type type;


    // `Neutral_Tile` members
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