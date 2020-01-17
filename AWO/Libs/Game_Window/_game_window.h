#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Include/types.h"
#include "Game_Window/game_window.h"
#include "Game_Message/game_message.h"

/*! @brief Game window instance. Holds the game window's dimensions.
 *
 *  Initializing it will also initialize rendering support for the game (GLFW & GL).
 */
struct Game_Window {

    // Handle to the GLFW window.
    GLFWwindow* glfw_window;

    // The window's dimensions.
    int width, height;

};