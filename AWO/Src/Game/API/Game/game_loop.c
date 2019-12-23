#include "Game/_game.h"

// Time between current frame and last frame.
static float delta_time = 0.0f;

// Time of last frame.
static float last_frame_time = 0.0f;

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
