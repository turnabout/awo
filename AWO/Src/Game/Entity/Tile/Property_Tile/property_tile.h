#pragma once

#include "types.h"
#include "Game/Clock/game_clock.h"
#include "Game/Data/Animation/animation.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Entity/entity_update_cb.h"
#include "Game/Player/player.h"

typedef struct Property_Tile {

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
    

    // `Property_Tile` members
    // The player who owns this property.
    Player* player;

    // This property's frame data.
    Frame** frame;

    // Base smoke animation, for bases only.
    Animation* base_smoke;

} Property_Tile;

/*! @brief Creates a property tile.
 *
 *  @param[in] game_clock The game's clock struct.
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] tile_type The type of this property tile.
 *  @param[in] player Player who owns the newly-created property.
 *  @param[in] x The x coordinate of this tile within its game board.
 *  @param[in] y The y coordinate of this tile within its game board.
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
 *  @param[in] property The property to update.
 *  @param[in] tiles_data The tiles data module.
 *  @param[in] player The new player owner.
 */
void update_property_owner(Property_Tile* property, Tiles_Data* tiles_data, Player* player);