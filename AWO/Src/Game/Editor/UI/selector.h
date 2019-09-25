#pragma once
#include <SDL.h>
#include "Visuals/visuals_data.h"

// Used to select the current entity to add to the map (tile/unit/etc).
typedef struct Tile_Selector Selector;

// Create the entity selector.
Selector* tile_selector_create(Tiles_Data* td);

// Update the selector.
void tile_selector_update(Selector* sel);

// Draw the selector UI.
void tile_selector_draw(Selector* sel, SDL_Renderer* rend, SDL_Texture* tile_tex);