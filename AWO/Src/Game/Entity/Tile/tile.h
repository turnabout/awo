#pragma once

#include "Game/Entity/Tile/Neutral_Tile/neutral_tile.h"
#include "Game/Entity/Tile/Property_Tile/property_tile.h"
#include "Game/Entity/Tile/tile_update_cb.h"

/*! @brief Generic representation of a Tile, which can either be a Neutral tile or a Property tile.
 *
 * Used to typecast void pointers that point to either and access the type, variation and render 
 * grid update function regardless of whether the tile is a Neutral tile or a Property tile.
 */
typedef struct Tile {

    // The type of the tile.
    // For both Neutral and Property tiles: Tile_Type
    Tile_Type type;

    // Function called when this tile's animation updates.
    update_tile_animation_cb update_animation;

    // Function called when this tile's fog status updates.
    update_fog_status_cb update_fog;

    // Coordinates of this tile within the game board.
    Uint8 x, y;
} Tile;
