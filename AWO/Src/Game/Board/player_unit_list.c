#include "Game/Board/_game_board.h"

void register_game_board_player_unit(Game_Board* game_board, Unit* unit)
{
    append_linked_list_item(
        game_board->player_units[unit->player->index], 
        (void*)unit
    );

    // TODO: update the new player owner on the unit
}

void unregister_game_board_player_unit(Game_Board* game_board, Unit* unit)
{
    delete_linked_list_item(
        game_board->player_units[unit->player->index], 
        (void*)unit
    );
}
