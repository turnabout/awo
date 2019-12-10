#include "Game/_game.h"

static float delta_time = 0.0f;      // Time between current frame and last frame.
static float last_frame_time = 0.0f; // Time of last frame.

void game_loop(void* game)
{
    // Update delta time
    float current_frame_time = (float)glfwGetTime();
    delta_time = current_frame_time - last_frame_time;
    last_frame_time = current_frame_time;

    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT);
    update_game((Game*)game, delta_time);
    render_game((Game*)game);

    glfwSwapBuffers(((Game*)game)->window);
}

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
