#include "Game/_game.h"

// Time between current frame and last frame.
static float delta_time = 0.0f;

// Time of last frame.
static float last_frame_time = 0.0f;

// GLFW window instance
static GLFWwindow* window = NULL;

void game_loop(void* game)
{
    // Update delta time
    float current_frame_time = (float)glfwGetTime();
    delta_time = current_frame_time - last_frame_time;
    last_frame_time = current_frame_time;

    glfwPollEvents();

    glClear(GL_COLOR_BUFFER_BIT);
    ((Game*)game)->update(game, delta_time);
    ((Game*)game)->render(game);

    glfwSwapBuffers(window);
}

void EMX run_game(
    Game* game, 
    Game_Window* game_window,
    int (*callback)(void*), 
    void* cb_value
)
{
    // Set starting static values
    delta_time = 0.0f;
    last_frame_time = 0.0f;
    window = get_game_window_GLFW_window_handle(game_window);

    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(game_loop, (void*)game, FPS, 1);
    #else

    // Use vSync & reset the GLFW timer before starting the game loop
    glfwSwapInterval(1);
    glfwSetTime(0);

    while (1) {
        if (callback(cb_value) == -1) {
            break;
        }

        game_loop(game);
    }
    #endif

    // Reset static values
    delta_time = 0.0f;
    last_frame_time = 0.0f;
    window = NULL;
}
