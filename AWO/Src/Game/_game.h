#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game/game.h"

struct Game {
    GLFWwindow* window;
    GLuint shader_program;
    GLuint sprite_sheet;
};