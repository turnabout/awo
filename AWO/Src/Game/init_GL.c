#include <stdio.h>

#include "conf.h"
#include "Game/_game.h"

void glfw_error_cb(int err_int, const char* err_str)
{
    printe("GLFW Error: %s", err_str);
}

Bool init_glfw(Game* game)
{
    // Initialize GLFW
    if (glfwInit() == GLFW_FALSE) {
        printe("Failed to create GLFW window");
        return FALSE;
    }

    // Set GLFW error callback
    glfwSetErrorCallback(glfw_error_cb);

    //Set GLFW window
    #ifndef __EMSCRIPTEN__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    #endif

    game->window = glfwCreateWindow(
        game->window_width, 
        game->window_height, 
        DEFAULT_WINDOW_TITLE, 
        NULL, 
        NULL
    );

    if (game->window == NULL) {
        printe("Failed to create GLFW window");
        return FALSE;
    }

    glfwMakeContextCurrent(game->window);

    return TRUE;
}

Bool set_GL_options(Game* game)
{
    // Set viewport
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

    return TRUE;
}

Bool init_GL(Game* game)
{
    if (
        init_glfw(game) && 
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) && 
        set_GL_options(game)
    ) {
        return TRUE;
    }

    return FALSE;
}
