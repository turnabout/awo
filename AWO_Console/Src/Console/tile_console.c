#include <curses.h>

#include "Utilities/utilities.h"
#include "Console/_console.h"

void tile_console(Console* console)
{
    if (console->game == NULL) {
        return;
    }

    tile_console_window();
    curs_set(0);
}