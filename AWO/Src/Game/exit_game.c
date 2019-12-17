#include <stdlib.h>

#include "Game/_game.h"

void exit_game(Game* game)
{
    glfwTerminate();

    if (game == NULL) {
        return;
    }

    // Free main game modules
    free_game_renderer();
    free_game_camera(game->camera);
    free_game_board(game->board);

    // Free input modules
    free_keyboard_module();
    free_mouse_module();

    // Free game data modules
    free_game_clock(game->clock);
    free_tiles_data(game->tiles_data);
    free_units_data(game->units_data);
    free_UI_data(game->UI_data);

    for (int i = 0; i < MAX_LOADED_STAGE_COUNT; i++) {
        free_stage(game->stages[i]);
    }

    // Free additional modules
    free_game_editor(game->editor);

    free(game);
}
