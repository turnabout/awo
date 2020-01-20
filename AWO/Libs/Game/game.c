#include "Game/_game.h"
#include "Game_Window/game_window.h"

/*! @brief Used to internally signify the game window was updated, and that the game's dimensions 
 *  should be updated at the start of the next frame.
 */
void _update_game_dimensions(int new_width, int new_height);

// Time between current frame and last frame.
static float delta_time = 0.0f;

// Time of last frame.
static float last_frame_time = 0.0f;

// GLFW window instance
static GLFWwindow* glfw_window = NULL;

// Whether the game window dimensions were changed before last frame, along with the new dimensions
static Bool window_dimensions_changed = FALSE;
static int new_window_width, new_window_height;

void game_loop(void* game)
{
    // Update delta time
    float current_frame_time = (float)glfwGetTime();
    delta_time = current_frame_time - last_frame_time;
    last_frame_time = current_frame_time;

    glfwPollEvents();

    if (window_dimensions_changed) {
        ((Game*)game)->update_dimensions(game, new_window_width, new_window_height);
        window_dimensions_changed = FALSE;
    }

    ((Game*)game)->update(game, delta_time);
    glClear(GL_COLOR_BUFFER_BIT);
    ((Game*)game)->render(game);

    glfwSwapBuffers(glfw_window);
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
    glfw_window = get_game_window_GLFW_window_handle(game_window);
    window_dimensions_changed = FALSE;

    set_game_window_dimensions_update_callback(game_window, _update_game_dimensions);

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
    glfw_window = NULL;

    set_game_window_dimensions_update_callback(game_window, NULL);
}

void EMX update_game_dimensions(Game* game, int new_width, int new_height)
{
    game->update_dimensions(game, new_width, new_height);
}

void _update_game_dimensions(int new_width, int new_height)
{
    window_dimensions_changed = TRUE;
    new_window_width = new_width;
    new_window_height = new_height;
}
