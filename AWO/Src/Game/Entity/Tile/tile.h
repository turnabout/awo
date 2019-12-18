#pragma once

#include "Game/Entity/entity_update_cb.h"
#include "Game/Entity/Tile/Neutral/neutral_tile.h"
#include "Game/Entity/Tile/Property/property_tile.h"

/*! @brief Generic representation of a tile, which can either be a neutral tile or a property tile.
 */
typedef struct Tile {

    // `Entity` members
    // Coordinates of this tile within the game board.
    Uint8 x, y;

    // Function called when this tile's animation updates.
    update_entity_render_grid_cb update_grid;

    // Function called when this tile's fog status updates.
    update_entity_palette_cb update_palette;

    // Function called to delete this tile.
    delete_entity_cb delete;


    // `Tile` members
    // This tile's type.
    Tile_Type type;

} Tile;
