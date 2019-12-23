#include "Game/_game.h"

void run_game(Game* game)
{
    // Use vSync
    glfwSwapInterval(1);

    // Reset the GLFW timer before starting the game loop
    glfwSetTime(0);

    while (!glfwWindowShouldClose(game->window)) {
        game_loop(game);
    }
}
