#pragma once

#include "types.h"
#include "Game/Clock/game_clock.h"
#include "Game/Data/Animation/Frame/frame.h"
#include "Game/Data/Animation/animation.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Data/Enums/army_type.h"
#include "Game/Entity/Tile/tile_update_cb.h"

typedef struct Property_Tile {

    // This tile's type.
    Tile_Type type;

    // The army type which determines the color of this property.
    Army_Type color_army;

    // Callback function used to update this tile's corresponding render grid pixels.
    update_tile_animation_cb update_render_grid;

    // Function called when this tile's fog status updates.
    update_fog_status_cb update_fog;

    // Coordinates of this tile within the game board.
    Uint8 x, y;

    // The army type which determines the visual style of this property.
    Army_Type visual_army;

    // Data for this property.
    Property_Type_Data* data;

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
 *  @param[in] color_army The color of this property tile.
 *  @param[in] x The x coordinate of this tile within the game board.
 *  @param[in] y The y coordinate of this tile within the game board.
 *  @return The created property tile.
 */
Property_Tile* create_property_tile(
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Type tile_type,
    Army_Type color_army,
    Uint8 x,
    Uint8 y
);

/*! @brief Updates a property tile's army.
 *
 *  @param[in] property The property to update.
 *  @param[in] color_army The new color army for the property.
 *  @param[in] visual_army The new visual army for the property.
 */
void update_property_army(Property_Tile* property, Army_Type color_army, Army_Type visual_army);