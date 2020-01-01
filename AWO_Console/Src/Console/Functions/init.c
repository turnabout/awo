#include <stdio.h>
#include <AWO/Include/game.h>

#include "Utilities/utilities.h"
#include "Console/_console.h"

#define DEFAULT_WINDOW_W 500
#define DEFAULT_WINDOW_H 500

int init(Console* console, void* payload[CMD_ARG_MAX_COUNT])
{
    // Ignore if game was already set
    if (console->game != NULL) {
        add_console_message(
            console,
            COLOR_PAIR_ERROR,
            "Error: game window already set"
        );

        return CMD_Ret_Error;
    }

    // Unpack the payload's values
    int window_w = (payload[0] != NULL) ? *((int*)payload[0]) : DEFAULT_WINDOW_W;
    int window_h = (payload[1] != NULL) ? *((int*)payload[1]) : DEFAULT_WINDOW_H;

    add_console_message(
        console,
        COLOR_PAIR_INFO,
        "Creating game window with dimensions %d,%d",
        window_w,
        window_h
    );

    console->game = create_game(window_w, window_h);

    // Ensure the game was created successfully
    if (get_game_state(console->game) == Game_Unusable) {
        free_game(console->game);
        return CMD_Ret_Error;
    }

    focus_console_window();

    return CMD_Ret_OK;
}