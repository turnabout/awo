#pragma once

#include "types.h"
#include "Game/Clock/game_clock.h"
#include "Game/Data/Animation/Frame/frame.h"
#include "Game/Data/Animation/animation.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Data/Enums/army_type.h"
#include "Game/Entity/Tile/tile_update_cb.h"
#include "Game/Player/player.h"

typedef struct Property_Tile {

    // This tile's type.
    Tile_Type type;

    // Callback function used to update this tile's corresponding render grid pixels.
    update_tile_render_grid_cb update_render_grid;

    // Function called when this tile's fog status updates.
    update_fog_status_cb update_fog;

    // Function called to delete this tile.
    delete_tile_cb delete;

    // Coordinates of this tile within the game board.
    Uint8 x, y;

    
    // The player who owns this property.
    Player* player;

    // This property's frame data.
    Frame* frame;

    // Base smoke animation, for bases only.
    Animation* base_smoke;

} Property_Tile;

/*! @brief Creates a property tile.
 *
 *  @param[in] parent_tile Reference to the parent tile entity holding this property tile.
 *  @param[in] game_clock The game's clock struct.
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] tile_type The type of this property tile.
 *  @param[in] player Player who owns the newly-created property.
 *  @param[in] x The x coordinate of this tile within the game board.
 *  @param[in] y The y coordinate of this tile within the game board.
 *  @return The created property tile.
 */
Property_Tile* create_property_tile(
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Type tile_type,
    Player* player,
    Uint8 x,
    Uint8 y
);

/*! @brief Updates the owner of the property tile.
 *
 *  @param[in] tiles_data The tiles data module.
 *  @param[in] property The property to update.
 *  @param[in] player The new player owner.
 */
void update_property_owner(Tiles_Data* tiles_data, Property_Tile* property, Player* player);