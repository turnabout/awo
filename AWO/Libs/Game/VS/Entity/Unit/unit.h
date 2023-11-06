#pragma once

#include "Game/Clock/game_clock.h"
#include "Game/Data/Animation/animation.h"
#include "Game/Data/Unit/units_data.h"
#include "Game/Entity/entity_update_cb.h"
#include "Game/Player/player.h"

/*! @brief A player-owned and player-controlled unit.
 */
typedef struct Unit {

    // `Entity` members
    // Coordinates of this tile within the game board.
    Uint8 x, y;

    // Function called when this tile's animation updates.
    update_entity_render_grid_cb update_grid;

    // Function called when this tile's fog status updates.
    update_entity_palette_cb update_palette;

    // Function called to delete this unit.
    delete_entity_cb delete;


    // `Unit` members
    // This unit's type.
    Unit_Type type;

    // This unit's player owner.
    Player* player;

    // This unit's idle animation.
    Animation* idle_animation;

} Unit;

/*! @brief Creates a unit.
 *
 *  @param[in] game_clock The game's clock module.
 *  @param[in] units_data The units data object.
 *  @param[in] type The type of the created unit.
 *  @param[in] player The player who owns and controls this unit.
 *  @param[in] x The x coordinate of this unit within the game board.
 *  @param[in] y The y coordinate of this unit within the game board.
 *  @return The created unit.
 */
Unit* create_unit(
    Clock* game_clock,
    Units_Data* units_data,
    Unit_Type type,
    Player* player,
    Uint8 x,
    Uint8 y
);
