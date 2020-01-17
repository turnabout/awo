#include <stdlib.h>

#include "Game_Renderer/_game_renderer.h"
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

Game_Renderer* create_game_renderer(int window_width, int window_height)
{
    Game_Renderer* game_renderer = malloc(sizeof(Game_Renderer));

    if (game_renderer == NULL) {
        return NULL;
    }

    // Init GLFW
    if (!init_glfw()) {
        free_game_renderer(game_renderer);
        return NULL;
    }

    // Create window
    game_renderer->window = create_glfw_window(window_width, window_height, DEFAULT_WINDOW_TITLE);

    if (game_renderer->window == NULL) {
        printe("Failed to create game window.");

        free_game_renderer(game_renderer);
        return NULL;
    }

    update_game_renderer_window_dimensions(game_renderer, window_width, window_height);

    return game_renderer;
}

void update_game_renderer_window_dimensions(Game_Renderer* game_renderer, int width, int height)
{
    game_renderer->width = width;
    game_renderer->height = height;
    glViewport(0, 0, game_renderer->width, game_renderer->height);
}

void get_game_renderer_dimensions_ptrs(Game_Renderer* game_renderer, int** width, int** height)
{
    if (game_renderer == NULL) {
        *width = NULL;
        *height = NULL;
    }

    *width = &game_renderer->width;
    *height = &game_renderer->height;
}

void free_game_renderer(Game_Renderer* game_window)
{
    glfwTerminate();

    if (game_window == NULL) {
        return;
    }

    free(game_window);
}