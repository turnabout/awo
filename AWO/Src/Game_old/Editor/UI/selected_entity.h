#pragma once

#include "Game/Input_State/input_state.h"

typedef struct Selected_Entity Selected_Entity;

// Create a selected entity UI box.
Selected_Entity* SE_create(int* screen_w, int* screen_h);

// Change the selected tile showcased.
void SE_change_tile(Selected_Entity* se, Tile_Type type, Tile_Var var);

// Update the positioning of the selected entity depending on mouse position.
void SE_update(Selected_Entity* se, Mouse_State* mouse);

// Draw the selected entity's box.
void SE_draw(Selected_Entity* se, SDL_Renderer* rend);
