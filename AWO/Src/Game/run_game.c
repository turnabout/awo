#include "Game/_game.h"

void run_game(Game* game)
{
    static float delta_time = 0.0f;      // Time between current frame and last frame.
    static float last_frame_time = 0.0f; // Time of last frame.

    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(game->window)) {

        // Update delta time
        float current_frame_time = (float)glfwGetTime();
        delta_time = current_frame_time - last_frame_time;
        last_frame_time = current_frame_time;

        glfwPollEvents();

        // TODO: Handle input
        // TODO: Update
        // TODO: Render

        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(game->window);
    }
}