#pragma once

typedef enum Player_Index {
    Player_Index_0,
    Player_Index_1,
    Player_Index_2,
    Player_Index_3,
    Player_Index_Neutral,
} Player_Index;

#define PLAYER_INDEX_FIRST Player_Index_0
#define PLAYER_INDEX_LAST  Player_Index_Neutral
#define PLAYER_INDEX_COUNT PLAYER_INDEX_LAST + 1

#define REAL_PLAYER_INDEX_FIRST Player_Index_0
#define REAL_PLAYER_INDEX_LAST  Player_Index_3
#define REAL_PLAYER_INDEX_COUNT REAL_PLAYER_INDEX_LAST + 1