#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Include/emx.h"
#include "GL_Helpers/gl_helpers.h"
#include "Game/game.h"
#include "Game_Data/game_data.h"
#include "Game_Message/game_message.h"

struct Game {

    // The game's current state.
    Game_State state;

    // The game's current mode.
    Game_Mode mode;

    // Collection of all game data modules.
    Game_Data* data;

    // Handle to the game's window.
    GLFWwindow* window;

    // Dimensions of the game's window.
    int window_width, window_height;

    // Current controller used to update & render the game.
    void* controller;

};

/*! @brief Initializes game rendering-related settings.
 *
 *  @param[in] game The game object.
 *  @param[in] window_width Initial width of the window.
 *  @param[in] window_height Initial height of the window.
 *  @return TRUE if successful, FALSE if an error occurred.
 */
Bool init_game_rendering(Game* game, int window_width, int window_height);