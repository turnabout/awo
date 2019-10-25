#pragma once

#include "Visuals/Data/Tiles/tiles_data.h"
#include "Game/Clock/game_clock.h"
#include "Game/Entities/Tile/tile.h"

// Used to create tiles.
// Can be used as a high-level interface to simply get the pointer to a tile of the requested 
// type and variation, without worrying about how it was created or its internal details.
typedef struct Tile_Factory Tile_Factory;

// Creates a tile factory.
Tile_Factory* TF_create(Tiles_Data* td, Game_Clock* gc);

// Gets a tile.
Tile* TF_get_tile(Tile_Factory* factory, Tile_Type type, Tile_Var var);