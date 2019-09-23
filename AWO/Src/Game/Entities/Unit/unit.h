#pragma once
#include <SDL.h>
#include "Game/Clock/game_clock.h"
#include "Visuals/Data/Units/units_data.h"

// An in-game unit.
typedef struct Unit Unit;

// Create a unit entity.
Unit* unit_create(Game_Clock* gc, Units_Data* ud, SDL_Texture* src_texture, unit_type ut);

// Update a unit.
void unit_update(Unit* u);

// Draw a unit.
void unit_draw(Unit* u, SDL_Renderer* rend);

// Free a unit's allocated memory.
void unit_free(Unit* u);
