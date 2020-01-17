#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Include/types.h"
#include "Game_Renderer/game_renderer.h"
#include "Game_Message/game_message.h"

struct Game_Renderer {

    // Handle to the GLFW window.
    GLFWwindow* window;

    // The window's dimensions.
    int width, height;

};