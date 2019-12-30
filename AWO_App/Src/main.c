#include <stdio.h>

#include "AWO/Include/game.h"
#include "Console/console.h"

static Console* console;

void game_run_callback(Game* game)
{
    update_console(console, game);
}

int main(int argc, char** argv)
{
    console = create_console();

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
    free_console(console);

    return 0;
}