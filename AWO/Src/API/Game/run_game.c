#include "conf.h"
#include "emx.h"
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

void EMX run_game(Game* game, void (*callback)(Game*))
{
    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(game_loop, (void*)game, FPS, 1);
    #else
    // Use vSync
    glfwSwapInterval(1);

    // Reset the GLFW timer before starting the game loop
    glfwSetTime(0);

    while (!glfwWindowShouldClose(game->window)) {
        callback(game);
        game_loop(game);
    }
    #endif
}
