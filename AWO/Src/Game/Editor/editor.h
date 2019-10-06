#pragma once

#include "Game/Board/game_board.h"
#include "Game/Input_State/input_state.h"

// Used in game design mode. Changes the game board's entities according to user inputs.
typedef struct Editor Editor;

// Create the editor module.
Editor* create_editor(Game_Board* gb);

// Update the editor module.
void update_editor(Editor* editor, Mouse_State* mouse);

// Draw the editor's visual components (gridlines, hover rectangle...).
void draw_editor(Editor* editor, SDL_Renderer* rend);
