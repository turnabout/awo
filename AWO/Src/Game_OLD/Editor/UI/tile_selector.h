/*
#pragma once
#include <SDL.h>
#include "Visuals/visuals_data.h"
#include "Game/Input_State/input_state.h"

// Used to select the current entity to add to the map (tile/unit/etc).
typedef struct Tile_Selector Tile_Selector;

// Create the entity selector.
Tile_Selector* tile_selector_create(Tiles_Data* td);

// Update the selector.
void tile_selector_update(Tile_Selector* selector, Mouse_State* mouse_state);

// Draw the selector UI.
void tile_selector_draw(Tile_Selector* selector, SDL_Renderer* rend, SDL_Texture* tile_tex);
*/