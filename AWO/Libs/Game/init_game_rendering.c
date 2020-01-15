#include "Game/_game.h"

void glfw_error_cb(int err_int, const char* err_str)
{
    printe("GLFW Error: %s", err_str);
}

Bool init_game_rendering(Game* game, int window_width, int window_height)
{
    if (glfwInit() == GLFW_FALSE) {
        printe("Failed to initialize GLFW.");
        return FALSE;
    }

    glfwSetErrorCallback(glfw_error_cb);

    if ((game->window = create_glfw_window(
        window_width,
        window_height,
        DEFAULT_WINDOW_TITLE
    )) == NULL) {
        printe("Failed to create game window.");
        return FALSE;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printe("Failed to initialize GL.");
        return FALSE;
    }

    // Set GL options
    glViewport(0, 0, game->window_width, game->window_height);

    glClearColor(
        (float)GAME_CLEAR_COLOR_R / 255.0f, 
        (float)GAME_CLEAR_COLOR_G / 255.0f, 
        (float)GAME_CLEAR_COLOR_B / 255.0f, 
        (float)GAME_CLEAR_COLOR_A / 255.0f
    );

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return TRUE;
}