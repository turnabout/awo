#include "Game_Data/Tile_Data/_tile_data.h"

Tile_Variation get_tile_auto_var(
    Tile_Data* tile_data,
    Tile_Type middle_tile,
    Tile_Type top_tile,
    Tile_Type right_tile,
    Tile_Type bottom_tile,
    Tile_Type left_tile
)
{
    // Go through all of the middle tile's autovars
    for (int i = 0; i < tile_data->src[middle_tile]->auto_vars_count; i++) {

        // Get this autovar and look for match with adjacent tiles
        Auto_Var_Data auto_var = tile_data->src[middle_tile]->auto_vars[i];

        if (
            (auto_var.adjacent_tiles[Auto_Var_Up]    & (1 << top_tile))    &&
            (auto_var.adjacent_tiles[Auto_Var_Right] & (1 << right_tile))  &&
            (auto_var.adjacent_tiles[Auto_Var_Down]  & (1 << bottom_tile)) &&
            (auto_var.adjacent_tiles[Auto_Var_Left]  & (1 << left_tile))
        ) {
            return auto_var.tile_var;
        }
    }

    // No match found
    return TILE_VAR_NONE;
}
