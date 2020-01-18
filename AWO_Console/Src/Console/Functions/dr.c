#include <curses.h>
#include <stdio.h>
#include <AWO/Include/Game/editor_game.h>

#include "Utilities/utilities.h"
#include "Console/_console.h"

int dr(Console* console, void* payload[CMD_ARG_MAX_COUNT])
{
    // Ignore if game has already been initialized
    if (console->game != NULL) {
        cprinte(console, "Error: a Game has already been initialized");
        return CMD_Ret_Error;
    }

    // Create the game window & game
    console->game_window = create_game_window(0, 0);

    if (console->game_window == NULL) {
        cprinte(console, "Error during game window creation");
        return CMD_Ret_Error;
    }

    console->game = create_editor_game(console->game_data, console->game_window);

    if (console->game == NULL) {
        cprinte(console, "Error during game creation");
        return CMD_Ret_Error;
    }

    // Tile the console and game windows
    tile_console(console);
    curs_set(0);

    reset_console_user_command(console);

    // Activate Curses nodelay mode so update_console becomes nonblocking
    nodelay(stdscr, TRUE);
    focus_console_window();

    // Start running the game, use console update function as passed-callback to keep processing 
    // user commands while the game runs.
    run_game(console->game, console->game_window, update_console, (void*)console);

    free_game_window(console->game_window);
    free_editor_game(console->game);

    // Deactivate Curses nodelay mode so update_console goes back to blocking
    nodelay(stdscr, FALSE);

    return CMD_Ret_OK;
}
