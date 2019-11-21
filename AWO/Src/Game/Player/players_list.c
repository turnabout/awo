#include <stdlib.h>

#include "Game/Player/player.h"

Players_List* create_players_list(Uint8 player_count)
{

    Players_List* players_list = (Players_List*)malloc(sizeof(Players_List));

    return players_list;
}

void free_players_list(Players_List* players_list)
{
    for (int i = 0; i < players_list->player_count; i++) {
        free_player(players_list->players[i]);
    }
}
