#pragma once

#include "Include/Game_Window/game_window.h"

Game_Window* create_game_window(int width, int height);

void update_game_window_dimensions(Game_Window* game_window, int width, int height);
void get_game_window_dimensions_ptrs(Game_Window* game_window, int** width, int** height);

void free_game_window(Game_Window* game_window);