#include <stdio.h>
#include <AWO/Include/game.h>
#include <AWO/Include/game_editor.h>

#include "Utilities/utilities.h"
#include "Console/_console.h"

int update_editor_tile(Console* console, void* payload[CMD_ARG_MAX_COUNT])
{
    if (console->game == NULL) {
        add_console_message(
            console,
            COLOR_PAIR_ERROR,
            "Error: game not created"
        );
        return CMD_Ret_Error;
    }

    // Confirm game state
    if (get_game_state(console->game) != Game_Running) {
        add_console_message(
            console,
            COLOR_PAIR_ERROR,
            "Error: game must be running in design room mode"
        );
        return CMD_Ret_Error;
    }

    // Unpack payload values
    int tile_type = (payload[0] != NULL) ? *((int*)payload[0]) : -1;

    update_game_editor_selected_entity(
        console->game,
        Editor_Entity_Type_Tile,
        tile_type,
        -1
    );

    return CMD_Ret_OK;
}
