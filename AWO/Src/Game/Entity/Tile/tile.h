#pragma once

#include "Game/Entity/Tile/Neutral_Tile/neutral_tile.h"
#include "Game/Entity/Tile/Property_Tile/property_tile.h"
#include "Game/Entity/Tile/tile_animation_update_cb.h"
#include "Game/Entity/Tile/tile_fog_update_cb.h"

/*! @brief Generic representation of a Tile, which can either be a Neutral tile or a Property tile.
 *
 * Used to typecast void pointers that point to either and access the type, variation and render 
 * grid update function regardless of whether the tile is a Neutral tile or a Property tile.
 */
typedef struct Tile {

    // The type of the tile.
    // For both Neutral and Property tiles: Tile_Type
    Tile_Type type;

    // The variation of the tile.
    // For Neutral tiles: Tile_Variation
    // For Property tiles: Player_Index (index of the player who owns this tile)
    int variation;

    // Function called when this tile's animation updates.
    tile_animation_update_cb update_animation;

    // Function called when this tile's fog status updates.
    fog_update_cb update_fog;

    // Coordinates of this tile within the game board.
    Uint8 x, y;
} Tile;
