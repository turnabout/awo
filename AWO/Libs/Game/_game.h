#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Include/emx.h"
#include "GL_Helpers/gl_helpers.h"
#include "Game/game.h"
#include "Game_Data/game_data.h"
#include "Game_Message/game_message.h"
#include "Game_Window/game_window.h"

struct Game {

    // The game's current state.
    Game_State state;

    // The game's current mode.
    Game_Mode mode;

    // Collection of all game data modules.
    Game_Data* data;

    // The game's window.
    Game_Window* window;

    // Current game controller. Used to update & render the game.
    void* controller;

};