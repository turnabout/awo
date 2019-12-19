#include <stdlib.h>

#include "Game/Player/player.h"

Player* create_player(Player_Index player_index, Army_Type player_army, CO_Type player_co)
{
    Player* player = (Player*)malloc(sizeof(Player));

    player->index = player_index;
    player->army = player_army;
    player->CO = create_CO(player_co);

    return player;
}

void free_player(Player* player)
{
    if (player == NULL) {
        return;
    }

    free_CO(player->CO);
    free(player);
}
