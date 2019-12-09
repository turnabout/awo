#include <stdio.h>

#include "conf.h"
#include "Game/_game.h"

void glfw_error_cb(int err_int, const char* err_str)
{
    printf("GLFW Error: %s\n", err_str);
}

int init_glfw(Game* game, int initial_window_width, int initial_window_height)
{
    // Initialize GLFW
    glfwSetErrorCallback(glfw_error_cb);
    glfwInit();

    // Get GLFW window
    GLFWwindow* window = glfwCreateWindow(
        initial_window_width, 
        initial_window_height, 
        DEFAULT_WINDOW_TITLE, 
        NULL, 
        NULL
    );

    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        return 0;
    }

    glfwMakeContextCurrent(window);
    game->window = window;

    return 1;
}

int set_GL_options(Game* game)
{
    #ifndef __EMSCRIPTEN__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    #endif

    // Set viewport
    glfwGetWindowSize(game->window, &game->window_width, &game->window_height);
    glViewport(0, 0, game->window_width, game->window_height);

    #ifndef __EMSCRIPTEN__
    // Set initial window position
    GLFWmonitor* primary = glfwGetPrimaryMonitor();

    int monitor_x, monitor_y, monitor_w, monitor_h;
    glfwGetMonitorWorkarea(primary, &monitor_x, &monitor_y, &monitor_w, &monitor_h);

    glfwSetWindowPos(
        game->window,
        monitor_x + ((monitor_w / 2) - (game->window_width / 2)),
        monitor_y + ((monitor_h / 2) - (game->window_height / 2))
    );
    #endif

    // Set other options
    glClearColor(
        (float)GAME_CLEAR_COLOR_R / 255.0f, 
        (float)GAME_CLEAR_COLOR_G / 255.0f, 
        (float)GAME_CLEAR_COLOR_B / 255.0f, 
        (float)GAME_CLEAR_COLOR_A / 255.0f
    );

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 1;
}

Bool init_GL(Game* game, int initial_window_width, int initial_window_height)
{
    if (
        init_glfw(game, initial_window_width, initial_window_height) && 
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) && 
        set_GL_options(game)
    ) {
        return TRUE;
    }

    return FALSE;
}
