#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Input_State/Mouse_State/mouse_state.h"
#include "Game_Window/game_window.h"

typedef struct Mouse_Handler Mouse_Handler;

Mouse_Handler* create_mouse_handler(Game_Window* game_window);

void disable_default_mouse_handler_callbacks();
void update_mouse_scroll(double x, double y);
void update_mouse_position(double x, double y);

void free_mouse_handler(Mouse_Handler* handler);