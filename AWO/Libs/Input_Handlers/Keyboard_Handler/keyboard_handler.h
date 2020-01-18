#pragma once

#include "Game_Window/game_window.h"

typedef struct Keyboard_Handler Keyboard_Handler;

Keyboard_Handler* create_keyboard_handler(Game_Window* game_window);

void free_keyboard_handler(Keyboard_Handler* handler);
