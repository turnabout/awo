#pragma once

typedef struct Game Game;

Game* init_game();
void run_game(Game* game);
void exit_game(Game* game);