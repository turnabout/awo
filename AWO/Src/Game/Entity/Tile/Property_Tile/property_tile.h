#pragma once

#include "types.h"
#include "Game/Clock/game_clock.h"
#include "Game/Data/Animation/Frame/frame.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Data/Unit/enums.h"
#include "Game/Entity/Tile/tile_render_grid_update.h"

typedef struct Property_Tile {

    // This property's frame.
    Frame* frame;

    // This property's type.
    Property_Type type;

    // This property's player owner index.
    // TODO

    // This property's army.
    Unit_Variation army;

} Property_Tile;

/*! @brief Creates a property tile.
 *
 *  @param[in] game_clock The game's clock struct.
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] property_type The type of this property.
 *  @param[in] army The army this property tile belongs to.
 *  @param[out] update_render_grid_cb Function used to update this property's render grid pixels.
 *  @return The created property tile.
 */
Property_Tile* create_property_tile(
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Property_Type property_type, 
    Unit_Variation army,
    tile_update_render_grid_cb* update_render_grid_cb
);