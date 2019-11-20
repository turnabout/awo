#pragma once

#include "Game/Player/player_index_enum.h"
#include "Game/Player/CO/CO.h"
#include "Game/Data/Unit/enums.h"

typedef struct Player {

    // The index of the player in this current game.
    Player_Index index;

    // The army occupied by the player in this current game.
    Unit_Variation army;

    // The Commanding Officer used by the player.
    CO* co;

} Player;