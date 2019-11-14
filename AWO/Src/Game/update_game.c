#include "Game/_game.h"

void update_game(Game* game, float delta_time)
{
    update_keys_state();
    update_mouse_buttons_state();

    // Clock / animations updating
    update_game_clock(game->clock, delta_time);

    Tick_Events_List* tick_events = get_game_clock_tick_event_list(game->clock);

    process_tick_events(game->tiles_clock_sub, tick_events);

    update_game_board(game->board);
}