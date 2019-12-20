#include "Game/Board/_game_board.h"
#include "Game/Entity/Unit/unit.h"

void add_game_board_unit(
    Game_Board* game_board,
    Game_Clock* game_clock,
    Units_Data* units_data,
    Unit_Type type,
    Player_Index owner_index,
    Uint8 x,
    Uint8 y
)
{
    Unit* unit;

    // Confirm this spot is empty
    if (game_board->units_grid[y][x] != NULL) {
        // TODO: log error
        return;
    }

    // Confirm the player is valid
    // TODO: check the player isn't eliminated
    if (owner_index < 0 || owner_index > game_board->stage->player_count) {
        return;
    }

    // Confirm units of this type are allowed on tile at coordinates
    // TODO

    // Confirm the player will not exceed the max amount of units per player
    if (get_linked_list_count(game_board->player_units[owner_index]) >= MAX_UNITS_PER_PLAYER) {
        // TODO: display message to player
        return;
    }

    // Add the unit
    unit = game_board->units_grid[y][x] = create_unit(
        game_clock,
        units_data,
        type,
        game_board->players[owner_index],
        x,
        y
    );

    // Register with the owner's list of units
    register_game_board_player_unit(game_board, (Unit*)unit);

    // Make initial call to the unit's render grid & palette update functions
    // unit->update_grid(game_board->game_renderer, (void*)unit, 0);
    // unit->update_palette(game_board->game_renderer, (void*)unit, 0);
}
