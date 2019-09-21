#pragma once

#include "cJSON.h"
#include "tiles_enums.h"

// Holds all of the game's visuals data for tiles.
typedef struct Tiles_Data Tiles_Data;

// Create tiles data object from JSON.
Tiles_Data* TD_create_from_JSON(cJSON* tiles_visuals_JSON);

#ifdef _DEBUG
// Print contents from tiles data.
void TD_print(Tiles_Data* td);
#endif

// TODO: still need?
// Gets a tile's data.
// Tile_Data* access_tile(tile_type type);

// TODO: still need?
// Gets a tile's variation's data.
// Returns the tile variation data associated with the given tile type and tile variation, or NULL
// if given variation was not found on the tile type.
// Tile_Var_Data* access_tile_var(tile_type type, tile_var var);
