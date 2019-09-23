#pragma once
#include <SDL.h>

#include "Game/game.h"
#include "Visuals/visuals_data.h"

#define TILE_FOG_ON  1
#define TILE_FOG_OFF 0

// Creates and returns a texture for a group of units.
// \param type_var The unit variation representing the units' visuals type.
// \param color_var The unit variation representing the units' color.
SDL_Texture* create_units_texture(Game* game, unit_var type_var, unit_var color_var);

// Creates and returns a texture for a group of tiles.
// \param weather The weather palette used on this group of tiles.
// \param fog Whether to apply a fog effect to this group of tiles.
SDL_Texture* create_tiles_texture(Game* game, tile_weather weather, int fog);