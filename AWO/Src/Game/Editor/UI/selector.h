#pragma once
#include <SDL.h>
#include "Visuals/visuals_data.h"

// Used to select the current entity to add to the map (tile/unit/etc).
typedef struct Selector Selector;

// Create the entity selector.
Selector* selector_create(Tiles_Data* td);

// Update the selector.
void selector_update(Selector* sel);

// Draw the selector UI.
void selector_draw(Selector* sel, SDL_Renderer* rend);