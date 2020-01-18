#include <stdlib.h>

#include "Game_Window/_game_window.h"
#include "Config/config.h"

void glfw_error_cb(int err_int, const char* err_str)
{
    printe("GLFW Error: %s", err_str);
}

Bool init_glfw()
{
    if (glfwInit() == GLFW_FALSE) {
        printe("Failed to initialize GLFW.");
        return FALSE;
    }

    glfwSetErrorCallback(glfw_error_cb);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printe("Failed to initialize GL.");
        return FALSE;
    }

    // Set GL options
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

GLFWwindow* create_glfw_window(int width, int height, char* title)
{
    #ifndef __EMSCRIPTEN__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    #endif

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (window == NULL) {
        return NULL;
    }

    glfwMakeContextCurrent(window);

    return window;
}

Game_Window* create_game_window(int window_width, int window_height)
{
    Game_Window* game_window = malloc(sizeof(Game_Window));

    if (game_window == NULL) {
        return NULL;
    }

    // Init GLFW
    if (!init_glfw()) {
        free_game_window(game_window);
        return NULL;
    }

    // Create GLFW window
    game_window->glfw_window = create_glfw_window(window_width, window_height, DEFAULT_WINDOW_TITLE);

    if (game_window->glfw_window == NULL) {
        printe("Failed to create game window.");

        free_game_window(game_window);
        return NULL;
    }

    update_game_window_dimensions(game_window, window_width, window_height);

    return game_window;
}

void update_game_window_dimensions(Game_Window* game_window, int width, int height)
{
    glfwSetWindowSize(game_window->glfw_window, width, height);
    game_window->width = width;
    game_window->height = height;
    glViewport(0, 0, game_window->width, game_window->height);
}

void get_game_window_dimensions_ptrs(Game_Window* game_window, int** width, int** height)
{
    if (game_window == NULL) {
        *width = NULL;
        *height = NULL;
    }

    *width = &game_window->width;
    *height = &game_window->height;
}

void free_game_window(Game_Window* game_window)
{
    glfwTerminate();

    if (game_window == NULL) {
        return;
    }

    free(game_window);
}