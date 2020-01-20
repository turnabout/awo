#include <stdio.h>

#include "Console/_console.h"

int dr(Console* console, void* payload[CMD_ARG_MAX_COUNT])
{
    // Ignore if game has already been initialized
    if (console->game != NULL) {
        cprinte(console, "Error: a game has already been initialized");
        return CMD_Ret_Error;
    }

    // Create the editor game
    console->game = create_editor_game(console->game_data, console->game_window);

    if (console->game == NULL) {
        cprinte(console, "Error creating editor game");
        return CMD_Ret_Error;
    }

    // Tile the console and game windows
    tile_console(console);
    curs_set(0);
    reset_console_user_command(console);

    // Activate Curses nodelay mode so update_console becomes nonblocking
    nodelay(stdscr, TRUE);
    show_game_window(console->game_window);
    focus_console_window();

    // Start running the game, pass console update function callback to keep processing user
    // commands while the game runs.
    run_game(console->game, console->game_window, update_console, (void*)console);

    // Clean up
    hide_game_window(console->game_window);
    free_editor_game(console->game);
    console->game = NULL;

    // Deactivate Curses nodelay mode so update_console goes back to blocking
    nodelay(stdscr, FALSE);

    return CMD_Ret_OK;
}
