#pragma once

#include "cJSON.h"
#include "tiles_enums.h"
#include "../Palette/palette_tree.h"
#include "../Sprite_Sheet_Metadata/ss_metadata.h"
#include "../Animation/animation.h"

// Holds all of the game's visuals data for tiles.
typedef struct Tiles_Data Tiles_Data;
typedef struct Tile_Data Tile_Data;

// Create tiles data object from JSON.
Tiles_Data* TD_create_from_JSON(cJSON* tiles_visuals_JSON);

// Gets the palette for the given tile weather variation.
// \param td The tiles data object.
// \param weather The weather variation of the palette.
Palette_Tree* TD_get_palette(Tiles_Data* td, tile_weather weather);

// Gets the tiles sprite sheet metadata.
SS_Metadata* TD_get_ss_metadata(Tiles_Data* td);

// Gets the tile data for the given tile type
// Tile_Data* TD_get_tile(Tiles_Data* td, tile_type tt);

// Gets the next animation for tile type. Must be called continuously until it returns NULL.
// Goes through all tile variations of the tile type until all have been returned.
Animation* TD_get_next_tile_animation(Tiles_Data* td, tile_type tt);

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
