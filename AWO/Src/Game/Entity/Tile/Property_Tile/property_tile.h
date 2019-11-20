#pragma once

#include "types.h"
#include "Game/Player/player.h"
#include "Game/Clock/game_clock.h"
#include "Game/Data/Animation/Frame/frame.h"
#include "Game/Data/Animation/animation.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Entity/Tile/tile_animation_update_cb.h"
#include "Game/Entity/Tile/tile_fog_update_cb.h"

typedef struct Property_Tile {

    // This tile's type.
    Tile_Type type;

    // Index of the player who owns this property.
    Unit_Variation player;

    // Callback function used to update this tile's corresponding render grid pixels.
    tile_animation_update_cb update_render_grid;

    // Function called when this tile's fog status updates.
    fog_update_cb update_fog;

    // Coordinates of this tile within the game board.
    Uint8 x, y;


    // This property's frame data.
    Frame* frame;

    // This property's additional animation, if it exists.
    Animation* additional_animation;

} Property_Tile;

/*! @brief Creates a property tile.
 *
 *  @param[in] parent_tile Reference to the parent tile entity holding this property tile.
 *  @param[in] game_clock The game's clock struct.
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] tile_type The type of this property tile.
 *  @param[in] player Index of the player this tile belongs to.
 *  @param[in] x The x coordinate of this tile within the game board.
 *  @param[in] y The y coordinate of this tile within the game board.
 *  @return The created property tile.
 */
Property_Tile* create_property_tile(
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Type tile_type,
    Player_Index player,
    Uint8 x,
    Uint8 y
);