#pragma once

#include "c_hashmap.h"
#include "cJSON.h"

#include "../Animation_Clock/animation_clock_enums.h"
#include "../Animation/animation.h"
#include "../Sprite_Sheet_Metadata/ss_metadata.h"
#include "tiles_enums.h"

typedef struct Tile_Data Tile_Data;
typedef struct Tile_Var_Data Tile_Var_Data;
typedef struct Tiles_Data Tiles_Data;

// A single tile's visual data.
struct Tile_Data
{
    map_t vars;            // Map holding every variation (Tile_Var_Data)
    int vars_amount;       // Amount of variations this tile has
    tile_var* vars_list;   // List of every variation this tile has

    Animation_Clock_Index clock; // Clock used by this tile to update its animation
};

// A tile variation's visual data
struct Tile_Var_Data
{
    Animation_Sub_Clock_Index sub_clock; // Sub clock used by this tile var to update its animation
    Animation* anim;                     // This tile variation's animation
};

// All tiles' visual data
struct Tiles_Data
{
    Tile_Data* src[TILE_TYPE_AMOUNT];
    SS_Metadata* ss_meta_data;
};
