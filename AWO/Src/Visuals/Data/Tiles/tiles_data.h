#pragma once

#include "cJSON.h"

#include "Visuals/Data/Palette/palette_tree.h"
#include "Visuals/Data/Sprite_Sheet_Metadata/ss_metadata.h"
#include "Visuals/Data/Animation/animation.h"
#include "Game/Clock/game_clock.h"

#include "tiles_enums.h"

// Holds all of the game's visuals data for tiles.
typedef struct Tiles_Data Tiles_Data;
typedef struct Tile_Data Tile_Data;

// Create tiles data object from JSON.
Tiles_Data* TD_create_from_JSON(cJSON* tiles_visuals_JSON);

// Gets the palette for the given tile weather variation.
// \param td The tiles data object.
// \param weather The weather variation of the palette.
Palette_Tree* TD_get_palette(Tiles_Data* td, Weather weather);

// Gets the tiles sprite sheet metadata.
SS_Metadata* TD_get_ss_metadata(Tiles_Data* td);

// Gather data on tile of given type & variation
// \param td Tiles' data object.
// \param tt The tile type.
// \param tv The tile variation.
// \param clock Pointer filled in with the tile's animation clock index.
// \param clock Pointer filled in with the tile's sub-clock index.
// \returns Gets pointer to the tile's animation frames.
SDL_Rect* TD_gather_tile_data(
    Tiles_Data* td,
    Tile_Type tt,
    Tile_Var tv,
    Animation_Clock_Index* clock_index,
    Animation_Sub_Clock_Index* sub_clock_index
);

// Gets the next animation for tile type. Must be called continuously until it returns NULL.
// Goes through all tile variations of the tile type until all have been returned.
Animation* TD_get_next_tile_animation(Tiles_Data* td, Tile_Type tt);

#ifdef _DEBUG
// Print contents from tiles data.
void TD_print(Tiles_Data* td);
#endif
