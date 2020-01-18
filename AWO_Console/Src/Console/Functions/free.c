#include <stdio.h>

#include "Utilities/utilities.h"
#include "Console/_console.h"

int free_console_game(Console* console, void* payload[CMD_ARG_MAX_COUNT])
{
    /*
    if (console->game == NULL) {
        cprinte(console, "Error: game must be created: run `init`");
        return CMD_Ret_Error;
    }

    Game_State state = get_game_state(console->game);

    free_game(console->game);
    console->game = NULL;

    // If the game was running, return a ret value of 'Exit' so the game loop breaks
    if (state == Game_Running) {
        return CMD_Ret_Exit;
    } else {
        return CMD_Ret_OK;
    }
    */
}
