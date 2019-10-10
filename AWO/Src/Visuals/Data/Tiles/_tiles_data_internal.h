#pragma once

#include "c_hashmap.h"
#include "cJSON.h"
#include "Visuals/Data/Animation/animation.h"
#include "Visuals/Data/Sprite_Sheet_Metadata/ss_metadata.h"
#include "Game/Clock/Animation_Clock/animation_clock_enums.h"
#include "Game/Entities/Tile/enums.h"

#include "tiles_data.h"

typedef struct Auto_Var
{
    Tile_Var var;           // The variation selected by this auto var
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
    map_t vars;              // Map holding every variation (Tile_Var_Data)

    int vars_amount;         // Amount of variations this tile has
    Tile_Var* vars_list;     // List of every variation this tile has

    int auto_vars_amount;    // Amount of auto vars this tile has
    Auto_Var* auto_vars;     // List of auto vars used to autoselect this tile's variation when 
                             // placing it in editor mode.

    Animation_Clock_Index clock; // Clock used by this tile to update its animation
};

// A tile variation's visual data
typedef struct Tile_Var_Data
{
    Animation_Sub_Clock_Index sub_clock; // Sub clock used by this tile var to update its animation
    Animation* anim;                     // This tile variation's animation
} Tile_Var_Data;

// All tiles' visual data
struct Tiles_Data
{
    Tile_Data* src[TILE_TYPE_COUNT];
    SS_Metadata* ss_meta_data;
    const cJSON* JSON;
};
