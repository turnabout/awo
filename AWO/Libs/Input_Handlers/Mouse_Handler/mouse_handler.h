#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Input_State/Mouse_State/mouse_state.h"
#include "AWO/game_window.h"

typedef struct Mouse_Handler Mouse_Handler;

void create_mouse_handler(Game_Window* game_window);
void update_mouse_state(Mouse_State* state);

void disable_default_mouse_handler_callbacks();
void update_mouse_scroll(double x, double y);
void update_mouse_position(double x, double y);

void free_mouse_handler();