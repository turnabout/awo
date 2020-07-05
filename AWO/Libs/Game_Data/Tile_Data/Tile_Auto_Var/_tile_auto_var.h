#pragma once

#include "AWO/game_data.h"
#include "Game_Data/Tile_Data/Tile_Auto_Var/tile_auto_var.h"

struct Auto_Var_Data {

    // The variation selected by this auto-var.
    Tile_Variation tile_var;

    // Array listing the acceptable adjacent tiles for this auto-var to be selected.
    int adjacent_tiles[4];

};

typedef enum Auto_Var_Adjacent_Tile {
    Auto_Var_Up    = 0,
    Auto_Var_Right = 1,
    Auto_Var_Down  = 2,
    Auto_Var_Left  = 3,
} Auto_Var_Adjacent_Tile;