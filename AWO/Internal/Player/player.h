#pragma once

// Internal
#include "../Config/config.h"
#include "../Utilities/utilities.h"
#include "../Player/player_index_enum.h"
#include "../Player/CO/CO.h"

// Libs
#include "../../Libs/Game_Data/Unit_Data/unit_data.h"

typedef struct Player {

    // The index of the player in this current game.
    Player_Index index;

    // The army occupied by the player in this current game.
    // Determines the color of the player's units and properties.
    Army_Type army;

    // The Commanding Officer used by the player.
    CO* CO;

} Player;

/*! @brief Creates a player entity, representing a player during gameplay.
 *
 *  @param[in] player_index This player's index.
 *  @param[in] player_army This player's army (color).
 *  @param[in] player_co This player's selected commanding officer.
 *  @return The created Player.
 */
Player* create_player(Player_Index player_index, Army_Type player_army, CO_Type player_co);

/*! @brief Frees the memory allocated by the given player.
 *
 *  @param[in] player The player to free.
 */
void free_player(Player* player);
