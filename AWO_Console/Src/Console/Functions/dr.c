#include <stdio.h>
#include <AWO/Include/game.h>

#include "Console/_console.h"

int dr(Console* console, void* payload[CMD_ARG_MAX_COUNT])
{
    // Ignore if game has already been initialized
    if (console->game != NULL) {
        add_console_message(
            console,
            COLOR_PAIR_ERROR,
            "Error: Game has already been initialized"
        );
        return CMD_Ret_Error;
    }

    // Create the game & print any messages sent during creation
    console->game = create_game(500, 500);
    process_console_game_messages(console);

    // Check if an error happened during creation
    if (get_game_state(console->game) == Game_Unusable) {
        free_game(console->game);
        console->game = NULL;
        return CMD_Ret_Error;
    }

    // Tile the console and game windows


    // Prepare the game for design room mode
    if (!prepare_design_room_game(console->game)) {
        process_console_game_messages(console);
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
