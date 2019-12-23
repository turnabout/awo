#include "Game/_game.h"

void update_game_window_dimensions(Game* game, int width, int height)
{

    glfwSetWindowSize(game->window, width, height);
    glViewport(0, 0, width, height);

    game->window_width = width;
    game->window_height = height;
}
