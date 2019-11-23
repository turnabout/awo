#include "Game/Board/_game_board.h"

void register_game_board_player_property(
    Game_Board* game_board,
    Player_Index player_index,
    Property_Tile* property
)
{
    append_linked_list_item(game_board->player_properties[player_index], (void*)property);

    // TODO: update the new player owner on the property
}

void unregister_game_board_player_property(
    Game_Board* game_board,
    Player_Index player_index,
    Property_Tile* property
)
{
    delete_linked_list_item(game_board->player_properties[player_index], (void*)property);
}
