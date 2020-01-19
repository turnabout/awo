#include <stdio.h>

#include <AWO/Include/Game/editor_game.h>

#include "Console/console.h"

int main(int argc, char** argv)
{
    Game_Window* window = create_game_window(0, 0);
    Game_Data* data = create_game_data();

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