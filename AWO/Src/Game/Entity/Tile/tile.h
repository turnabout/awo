#pragma once

#include <cglm/types.h>

#include "Game/Clock/game_clock.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Renderer/game_renderer.h"
#include "Game/Entity/Tile/Neutral_Tile/neutral_tile.h"
#include "Game/Entity/Tile/Property_Tile/property_tile.h"
#include "Game/Entity/Tile/tile_render_grid_update.h"

/*! @brief Represents the different types of tile contents.
 */
typedef enum Tile_Contents_Type {
    Tile_Contents_Neutral,
    Tile_Contents_Property
} Tile_Contents_Type;

/*! @brief Represents a tile used in the game's tile map system.
 */
typedef struct Tile {

    // Callback function used to update this tile's corresponding render grid pixels.
    tile_update_render_grid_cb update_render_grid;

    // The contents of this tile.
    // Can either be a Neutral_Tile or Property_Tile.
    void* contents;

    // The type of this tile's contents.
    Tile_Contents_Type contents_type;
} Tile;

/*! @brief Creates a tile.
 *
 *  @param[in] game_clock The game clock.
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] tile_type The type of the created tile.
 *  @param[in] tile_variation The variation of the created tile.
 *  For neutral tiles, this is a Tile_Variation. For property tiles, Player_Index.
 *  @return The created tile.
 */
Tile* create_tile(
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Type type,
    Uint8 variation
);

/*! @brief Frees memory occupied by a tile.
 *
 *  @param[in] The tile to free.
 */
void free_tile(Tile* tile);
