#pragma once

#include "Game/Board/game_board.h"
#include "Game/Input_State/input_state.h"

// Used in game design mode. Changes the game board's entities according to user inputs.
typedef struct Editor Editor;

// Create the editor module.
Editor* create_editor(Game_Board* gb, Tiles_Data* td, int* screen_w, int* screen_h);

// Updates the editor module's selected tile type.
void update_editor_selected_tile_type(Editor* editor, Tile_Type type);

// Updates the editor module.
void update_editor(Editor* editor, Mouse_State* mouse);

// Draw the editor's visual components (gridlines, hover rectangle...).
void draw_editor(Editor* editor, SDL_Renderer* rend);
