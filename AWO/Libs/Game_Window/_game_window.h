#pragma once

#include "AWO/types.h"
#include "AWO/emx.h"
#include "Game_Message/game_message.h"
#include "Game_Window/game_window.h"

/*! @brief Game window instance. Holds the game window's dimensions.
 *
 *  Initializing it will also initialize rendering support for the game (GLFW & GL).
 */
struct Game_Window {

    // Handle to the GLFW window.
    GLFWwindow* glfw_window;

    // The window's dimensions.
    int width, height;

    // Function called when the window's dimensions are updated.
    Window_Dimensions_Update_CB dimensions_update_callback;

};