#include <stdio.h>
#include <AWO/Include/game.h>

#include "Console/_console.h"

int rundr(Console* console, void* payload[CMD_ARG_MAX_COUNT])
{
    // Ignore if game hasn't been set or isn't in the right state
    if (console->game == NULL) {
        add_console_message(
            console,
            COLOR_PAIR_ERROR,
            "Error: game must be created: run `init`"
        );
        return CMD_Ret_Error;
    }

    // Prepare the game for design room mode
    if (!prepare_design_room_game(console->game)) {
        return CMD_Ret_Error;
    }

    reset_console_user_command(console);

    // Activate Curses nodelay mode so update_console becomes nonblocking
    nodelay(stdscr, TRUE);

    // Start running the game, use console update function as passed-callback so we can keep 
    // processing user commands while the game runs.
    run_game(console->game, update_running_game_console, (void*)console);

    // Deactivate Curses nodelay mode so update_console goes back to blocking
    nodelay(stdscr, FALSE);

    return CMD_Ret_OK;
}