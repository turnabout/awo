#pragma once

#include "Game/Entity/Tile/Neutral_Tile/neutral_tile.h"
#include "Game/Entity/Tile/tile_render_grid_update.h"

/*! @brief Generic representation of a Tile, which can either be a Neutral tile or a Property tile.
 *
 * Used to typecast void pointers that point to either and access the type, variation and render 
 * grid update function regardless of whether the tile is a Neutral tile or a Property tile.
 */
typedef struct Tile {

    // The type of the tile.
    // For both Neutral and Property tiles: Tile_Type
    Tile_Type tile_type;

    // The variation of the tile.
    // For Neutral tiles: Tile_Variation
    // For Property tiles: Player_Index (index of the player who owns this tile)
    int tile_variation;

    // Callback function used to update this tile's corresponding render grid pixels.
    tile_update_render_grid_cb update_render_grid;
} Tile;
