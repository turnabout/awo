#pragma once

#include "Game/Entities/Tile/tile.h"

// Used by game board. Holds a map containing every unique tile contained within the game board.
typedef struct Tiles_Map Tiles_Map;

// Creates a tiles map.
Tiles_Map* TM_create();

// Gets tile corresponding to given type/variation from the tiles map, if it exists.
// Else, returns NULL.
Tile* TM_get_map_tile(Tiles_Map* tm, Tile_Type type, Tile_Var var);

// Adds a tile to the map.
void TM_add_map_tile(Tiles_Map* tm, Tile* tile, Tile_Type type, Tile_Var var);

// Frees a tile map along with its stored tiles.
void TM_free(Tiles_Map* tm);