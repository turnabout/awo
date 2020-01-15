#include <stdio.h>

#include "AWO/Include/Game/game.h"

#include "Console/console.h"

int main(int argc, char** argv)
{
    Game* game = create_game(500, 500);

    /*
    Console* console = create_console();

    send_console_command(console, "dr");

    if (console != NULL) {
        run_console(console);
    }

    free_console(console);

    */
    return 0;
}