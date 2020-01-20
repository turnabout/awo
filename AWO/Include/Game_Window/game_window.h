#pragma once

/*! @brief Game window instance. Holds the game window's dimensions.
 */
typedef struct Game_Window Game_Window;

Game_Window* create_game_window(int width, int height);

void update_game_window_dimensions(Game_Window* game_window, int width, int height);
void show_game_window(Game_Window* game_window);
void hide_game_window(Game_Window* game_window);

void free_game_window(Game_Window* game_window);