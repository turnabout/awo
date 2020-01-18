#include <stdio.h>
// #include <AWO/Include/Game_Controller/game_editor_controller.h>

#include "Utilities/utilities.h"
#include "Console/_console.h"

int update_editor_tile(Console* console, void* payload[CMD_ARG_MAX_COUNT])
{
    if (console->game == NULL) {
        cprinte(console, "Error: game not created");
        return CMD_Ret_Error;
    }

    // Unpack payload values
    int tile_type = (payload[0] != NULL) ? *((int*)payload[0]) : -1;

    /*
    update_game_editor_selected_entity(
        console->game,
        Editor_Entity_Type_Tile,
        tile_type,
        -1
    );
    */

    return CMD_Ret_OK;
}
