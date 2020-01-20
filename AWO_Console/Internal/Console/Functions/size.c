#include "Console/_console.h"

#define DEFAULT_WIDTH 700
#define DEFAULT_HEIGHT 500

int size(Console* console, void* payload[CMD_ARG_MAX_COUNT])
{
    // Unpack payload values & update
    int width = (payload[0] != NULL) ? *((int*)payload[0]) : DEFAULT_WIDTH;
    int height = (payload[1] != NULL) ? *((int*)payload[1]) : DEFAULT_HEIGHT;

    update_game_window_dimensions(console->game_window, width, height);
    cprinti(console, "Updated game window dimensions to %d, %d", width, height);

    return CMD_Ret_OK;
}