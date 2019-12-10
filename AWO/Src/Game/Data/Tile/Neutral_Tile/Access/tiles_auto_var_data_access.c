#include <stdio.h>

#include "Game/Data/Tile/_tiles_data.h"

Tile_Variation get_tile_auto_var(
    Tiles_Data* tiles_data,
    Tile_Type middle_tile,
    Tile_Type top_tile,
    Tile_Type right_tile,
    Tile_Type bottom_tile,
    Tile_Type left_tile
)
{
    Tile_Type_Data* middle_tile_data = tiles_data->neutral_tiles->src[middle_tile];

    // Go through all of the middle tile_type_data's autovars
    for (int i = 0; i < middle_tile_data->auto_vars_count; i++) {

        // Get this autovar and look for match with adjacent tiles
        Auto_Var_Data auto_var = middle_tile_data->auto_vars[i];

        if (
            (auto_var.adjacent_tiles[Auto_Var_Up]    & (1 << top_tile))    &&
            (auto_var.adjacent_tiles[Auto_Var_Right] & (1 << right_tile))  &&
            (auto_var.adjacent_tiles[Auto_Var_Down]  & (1 << bottom_tile)) &&
            (auto_var.adjacent_tiles[Auto_Var_Left]  & (1 << left_tile))
        ) {
            return auto_var.tile_var;
        }
    }

    #ifdef _DEBUG
    printf("default...\n");
    #endif

    return get_default_tile_variation(tiles_data, middle_tile);
}
