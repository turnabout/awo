#pragma once

#include "types.h"
#include "Game/Clock/game_clock.h"
#include "Game/Data/Animation/Frame/frame.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Data/Unit/enums.h"
#include "Game/Entity/Tile/tile_render_grid_update.h"
#include "Game/player_index_enum.h"

typedef struct Property_Tile {

    // This property's frame.
    Frame* frame;

    // This property's type.
    Property_Type type;

    // Index of the player who owns this property.
    Unit_Variation player;

} Property_Tile;

/*! @brief Creates a property tile.
 *
 *  @param[in] parent_tile Reference to the parent tile entity holding this property tile.
 *  @param[in] game_clock The game's clock struct.
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] property_type The type of this property.
 *  @param[in] player Index of the player this tile belongs to.
 *  @param[out] update_render_grid_cb Function used to update this property's render grid pixels.
 *  @return The created property tile.
 */
Property_Tile* create_property_tile(
    Tile* parent_tile,
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Property_Type property_type,
    Player_Index player,
    tile_update_render_grid_cb* update_render_grid_cb
);