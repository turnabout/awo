#pragma once

#include "Game/Entity/Tile/Tile.h"
#include "Game/Entity/Tile/Neutral_Tile/neutral_tile.h"
#include "Game/Entity/Tile/Property_Tile/property_tile.h"

/*! @brief Generic representation of an entity (unit or tile).
 */
typedef struct Entity {

    // Coordinates of this entity within the game board.
    Uint8 x, y;

    // Function called to update this entity's corresponding render grid pixels.
    update_entity_render_grid_cb update_grid;

    // Function called to update this entity's palette.
    update_entity_palette_cb update_palette;

    // Function called to delete this entity.
    delete_entity_cb delete;

} Entity;