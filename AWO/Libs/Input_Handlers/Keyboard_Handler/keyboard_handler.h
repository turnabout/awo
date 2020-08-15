#pragma once

#include "Game_Window/game_window.h"
#include "Input_State/Keyboard_State/keyboard_state.h"

typedef struct Keyboard_Handler Keyboard_Handler;

void create_keyboard_handler(Game_Window* game_window);

void update_keyboard_state(Keyboard_State* state);

void disable_default_keyboard_handler_callbacks();

void free_keyboard_handler();
