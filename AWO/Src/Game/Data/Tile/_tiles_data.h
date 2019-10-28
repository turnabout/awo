#pragma once

#include <c_hashmap.h>
#include <cJSON.h>

#include "Game/Data/Animation/animation.h"
#include "Game/Data/Tile/enums.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Clock/Animation_Clock/enums.h"

typedef struct Auto_Var
{
    Tile_Variation var;           // The variation selected by this auto var
    int adjacent_tiles[4];  // Array pointing out which adjacent tiles are acceptable for this auto
                            // var to be selected
} Auto_Var;

typedef enum {
    Auto_Var_Up    = 0,
    Auto_Var_Right = 1,
    Auto_Var_Down  = 2,
    Auto_Var_Left  = 3,
} Auto_Var_Adjacent_Tile;

// A single tile's visual data.
struct Tile_Data
{
    map_t vars_map;            // Map holding every variation (Tile_Var_Data)

    int vars_count;            // How many variations this tile has
    Tile_Variation* vars_list; // List of every variation this tile has

    int auto_vars_count;       // Amount of auto vars_map this tile has
    Auto_Var* auto_vars;       // List of auto vars_map used to autoselect this tile's variation 
                               // when placing it in editor mode.

    Animation_Clock_Index clock; // Clock used by this tile to update its animation
};

// A tile variation's visual data
typedef struct Tile_Var_Data
{
    Animation_Sub_Clock_Index sub_clock; // Sub clock used by this tile var to update its animation
    Animation* animation;                // This tile variation's animation
} Tile_Var_Data;

// All tiles' visual data
struct Tiles_Data
{
    Tile_Data* src[TILE_TYPE_COUNT];

    // TODO: hold palette data
};
