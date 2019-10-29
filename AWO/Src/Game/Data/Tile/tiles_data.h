#pragma once

#include <cJSON.h>

#include "types.h"
#include "Game/Data/Animation/animation.h"
#include "Game/Clock/game_clock.h"
#include "Game/Data/Tile/enums.h"

// Holds all of the game's visuals data for tiles.
typedef struct Tiles_Data Tiles_Data;

// Create tiles data object from JSON.
Tiles_Data* create_tiles_data_from_JSON(cJSON* tiles_visuals_JSON, mat4 ss_projection);

// Gets the tile variation the given middle tile should have, according to the given adjacent 
// tiles.
Tile_Variation get_tile_auto_var(
    Tiles_Data* td,
    Tile_Type middle_tile,
    Tile_Type top_tile,
    Tile_Type right_tile,
    Tile_Type bottom_tile,
    Tile_Type left_tile
);

// Gather data on tile of given type & variation
// \param td Tiles' data object.
// \param tt The tile type.
// \param tv The tile variation.
// \param clock Pointer filled in with the tile's animation clock index.
// \param clock Pointer filled in with the tile's sub-clock index.
// \returns The tile's Animation object.
Animation* gather_tile_data(
    Tiles_Data* tiles_data,
    Tile_Type type,
    Tile_Variation variation,
    Animation_Clock_Index* clock_index,
    Animation_Sub_Clock_Index* sub_clock_index
);

// Gets the next animation for tile type. Must be called continuously until it returns NULL.
// Goes through all tile variations of the tile type until all have been returned.
Animation* get_next_tile_animation(Tiles_Data* td, Tile_Type tt);

// Gets the first (default) tile variation for a tile type.
Tile_Variation get_tile_default_var(Tiles_Data* td, Tile_Type type);

// Gets the next tile variation data belonging to the given tile type.
// Returns string corresponding to variation and stores variation value in given pointer.
const char* get_next_tile_var_data(Tiles_Data* td, Tile_Type tt, Uint8* var_val);

#ifdef _DEBUG
// Print contents from tiles data.
void print_tiles_data(Tiles_Data* td);
#endif
