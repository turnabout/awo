#pragma once

#include "Game/Board/game_board.h"
#include "Game/Clock/game_clock.h"
#include "Game/Data/Tile/tiles_data.h"

// Used in game design mode. Changes the game board's entities according to user inputs.
typedef struct Game_Editor Game_Editor;

// Create the editor module.
Game_Editor* create_game_editor(
    Game_Board* game_board, 
    Tiles_Data* tiles_data, 
    Game_Clock* game_clock,
    int* window_width, 
    int* window_height
);

// Updates the editor module's selected tile type/variation.
void update_editor_selected_tile_type(Game_Editor* editor, Tile_Type type, int variation);

// Updates the editor module.
void update_game_editor(Game_Editor* editor);

// Draw the editor's visual components (gridlines, hover rectangle...).
// void render_editor(Editor* editor);

// Frees memory occupied by the game editor module.
void free_game_editor(Game_Editor* editor);
