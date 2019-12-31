#include <stdio.h>
#include <AWO/Include/game.h>

#include "Console/_console.h"

void rundr(Console* console, void* payload[CMD_ARG_MAX_COUNT])
{
    // Ignore if game hasn't been set or isn't in the right state
    if (console->game == NULL) {
        // TODO: error
        return;
    }

    if (get_game_state(console->game) != Game_Prepared) {
        // TODO: error
        return;
    }

    // Activate Curses nodelay mode so update_console becomes nonblocking
    nodelay(stdscr, TRUE);

    // Start running the game, use console update function as passed-callback so we can keep 
    // processing user commands while the game runs.
    run_game(console->game, update_console, (void*)console);
}