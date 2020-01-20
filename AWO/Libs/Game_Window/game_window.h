#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Include/Game_Window/game_window.h"

typedef void (*Window_Dimensions_Update_CB)(int width, int height);

void get_game_window_dimensions_ptrs(Game_Window* game_window, int** width, int** height);

void set_game_window_dimensions_update_callback(
    Game_Window* game_window,
    Window_Dimensions_Update_CB cb
);

GLFWwindow* get_game_window_GLFW_window_handle(Game_Window* game_window);
