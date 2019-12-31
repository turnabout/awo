#include <stdio.h>
#include <AWO/Include/game.h>

#include "Utilities/utilities.h"
#include "Console/_console.h"

int free_console_game(Console* console, void* payload[CMD_ARG_MAX_COUNT])
{
    if (console->game == NULL) {
        add_console_message(
            console,
            COLOR_PAIR_ERROR,
            "Error: game must be created: run `init`"
        );
        return CMD_Ret_Error;
    }

    free_game(console->game);
    console->game = NULL;

    return CMD_Ret_OK;
}
