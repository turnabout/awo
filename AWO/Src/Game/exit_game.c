#include <stdlib.h>

#include "Game/_game.h"

void exit_game(Game* game)
{
    glfwTerminate();

    if (game == NULL) {
        return;
    }

    // Free main game modules
    free_game_renderer(game->renderer);
    free_game_camera(game->camera);
    free_game_board(game->board);
    free_game_cursor(game->pointer);

    // Free input modules
    free_keyboard_module();
    free_mouse_module();

    // Free game data modules
    free_game_clock(game->clock);

    // Free optional modules
    free_game_editor(game->editor);

    free(game);
}
