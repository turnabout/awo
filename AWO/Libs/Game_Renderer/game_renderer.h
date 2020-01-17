#pragma once

typedef struct Game_Renderer Game_Renderer;

Game_Renderer* create_game_renderer(int width, int height);

void update_game_renderer_window_dimensions(Game_Renderer* game_renderer, int width, int height);
void get_game_renderer_dimensions_ptrs(Game_Renderer* game_window, int** width, int** height);

void free_game_renderer(Game_Renderer* game_renderer);