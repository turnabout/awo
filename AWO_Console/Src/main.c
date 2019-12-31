#include <stdio.h>

#include "Console/console.h"

int main(int argc, char** argv)
{
    Console* console = create_console();

    if (console != NULL) {
        run_console(console);
    }

    free_console(console);

    /*
    // Initialize game & run
    Game* game;

    if ((game = create_game(0, 0)) == NULL) {
        printf("Failed to initialize game\n");
        free_game(game);
        return 1;
    }

    if (prepare_design_room_game(game)) {
        run_game(game, game_run_callback);
    }

    free_game(game);
    */

    return 0;
}