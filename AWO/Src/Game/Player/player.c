#include <stdlib.h>

#include "Game/Player/player.h"

Player* create_player(Player_Index player_index, Army_Type player_army, CO_Type player_co)
{
    Player* player = (Player*)malloc(sizeof(Player));

    player->index = player_index;
    player->army = player_army;
    player->CO = create_CO(player_co);
    player->properties = create_linked_list(NULL, 0);

    return player;
}

free_player(Player* player)
{
    free_CO(player->CO);
    free(player);
}

void register_player_property(Player* player, Property_Tile* property)
{
    append_linked_list_item(player->properties, (void*)property);
    update_property_army(property, player->army, player->CO->army);
}
