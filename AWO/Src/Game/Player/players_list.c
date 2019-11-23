#include <stdlib.h>

#include "Game/Player/player.h"

Players_List* create_players_list(
    Uint8 player_count, 
    Army_Type player_armies[MAX_PLAYER_COUNT],
    CO_Type player_COs[MAX_PLAYER_COUNT]
)
{
    Players_List* players_list = (Players_List*)malloc(sizeof(Players_List));
    players_list->player_count = player_count;

    for (int i = 0; i < player_count; i++) {
        players_list->players[i] = create_player(i, player_armies[i], player_COs[i]);
    }

    return players_list;
}

void free_players_list(Players_List* players_list)
{
    for (int i = 0; i < players_list->player_count; i++) {
        free_player(players_list->players[i]);
    }
}
