#pragma once

#include <SDL.h>
#include "Game/Clock/game_clock.h"
#include "Visuals/visuals_data.h"

typedef struct Tile Tile;

// Create a tile entity.
Tile* tile_create(Game_Clock* gc, Tiles_Data* td, tile_type tt, tile_var tv);

// Draw a tile.
void tile_draw(Tile* t, SDL_Renderer* rend, SDL_Texture* texture, int x, int y);
