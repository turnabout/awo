#pragma once
#include <SDL.h>

#include "Game/game.h"
#include "Visuals/visuals_data.h"

// Creates and returns a texture for a group of units.
// \param type_var The unit variation representing the units' visuals type.
// \param color_var The unit variation representing the units' color.
SDL_Texture* create_units_texture(Game* game, unit_var type_var, unit_var color_var);