#pragma once

typedef struct Game Game;

Game* init_game(int game_board_width, int game_board_height, int window_width, int window_height);
void run_game(Game* game);
void exit_game(Game* game);