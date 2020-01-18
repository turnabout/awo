#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Include/Game_Window/game_window.h"

void get_game_window_dimensions_ptrs(Game_Window* game_window, int** width, int** height);

GLFWwindow* get_game_window_GLFW_window_handle(Game_Window* game_window);
