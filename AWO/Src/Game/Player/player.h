#pragma once

#include "conf.h"
#include "types.h"
#include "Game/Player/player_index_enum.h"
#include "Game/Player/CO/CO.h"
#include "Game/Data/Unit/enums.h"

typedef struct Player {

    // The index of the player in this current game.
    Player_Index index;

    // The army occupied by the player in this current game.
    // Determines the color of the player's units and properties.
    Army_Type army;

    // The Commanding Officer used by the player.
    CO* CO;

} Player;

typedef struct Players_List {

    // Every player belonging to this list.
    Player* players[MAX_PLAYER_COUNT];

    // Amount of players belonging to this list.
    Uint8 player_count;

} Players_List;

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
free_player(Player* player);

/*! @brief Create an (empty) list of players.
 *
 *  @param[in] player_count Amount of players belonging to this list.
 */
Players_List* create_players_list(Uint8 player_count);
