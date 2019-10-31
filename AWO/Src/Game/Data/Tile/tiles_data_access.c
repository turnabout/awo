#include <stdio.h>
#include <stdlib.h>
#include <c_hashmap.h>

#include "Game/Data/Tile/_tiles_data.h"

Tile_Variation_Data* get_tile_var_data(Tiles_Data* tiles_data, Tile_Type type, Tile_Variation var)
{
    Tile_Variation_Data* tile_var_data;

    char* key = (char*)tile_var_str_short[var];

    if (hashmap_get(tiles_data->src[type]->vars_map, key, (void**)(&tile_var_data)) != MAP_OK) {
        return NULL;
    } else {
        return tile_var_data;
    }
}

Tile_Variation get_next_tile_type_var(Tiles_Data* tiles_data, Tile_Type type)
{
    // Variation tile_var_index
    static int index = 0;

    Tile_Type_Data* tile = tiles_data->src[type];

    // No tile_type_data variation at given tile_var_index, reset it and return NULL
    if (index == tile->vars_count) {
        index = 0;
        return TILE_VAR_NONE;
    }

    return tile->vars_list[index++];
}

Animation* get_next_tile_type_var_animation(Tiles_Data* tiles_data, Tile_Type type)
{
    // Variation tile_var_index
    static int tile_var_index = 0;

    Tile_Type_Data* tile = tiles_data->src[type];

    // No tile_type_data variation at given tile_var_index, reset it and return NULL
    if (tile_var_index == tile->vars_count) {
        tile_var_index = 0;
        return NULL;
    }

    // Get tile_type_data variation data
    Tile_Variation tile_var = tile->vars_list[tile_var_index];
    Tile_Variation_Data* tile_var_data = get_tile_var_data(tiles_data, type, tile_var);

    // Increment tile_var_index for next time
    tile_var_index++;

    return tile_var_data->animation;
}

Tile_Variation get_tile_type_default_var(Tiles_Data* tiles_data, Tile_Type type)
{
    return tiles_data->src[type]->vars_list[0];
}

Tile_Variation get_tile_auto_var(
    Tiles_Data* tiles_data,
    Tile_Type middle_tile,
    Tile_Type top_tile,
    Tile_Type right_tile,
    Tile_Type bottom_tile,
    Tile_Type left_tile
)
{
    Tile_Type_Data* middle_tile_data = tiles_data->src[middle_tile];

    // Go through all of the middle tile_type_data's autovars
    for (int i = 0; i < middle_tile_data->auto_vars_count; i++) {

        // Get this autovar and look for match with adjacent tiles
        Auto_Var auto_var = middle_tile_data->auto_vars[i];

        if (
            (auto_var.adjacent_tiles[Auto_Var_Up]    & (1 << top_tile))    &&
            (auto_var.adjacent_tiles[Auto_Var_Right] & (1 << right_tile))  &&
            (auto_var.adjacent_tiles[Auto_Var_Down]  & (1 << bottom_tile)) &&
            (auto_var.adjacent_tiles[Auto_Var_Left]  & (1 << left_tile))
        ) {
            return auto_var.tile_var;
        }
    }

    printf("default...\n");
    return get_tile_type_default_var(tiles_data, middle_tile);
}

Animation* gather_tile_data(
    Tiles_Data* tiles_data, 
    Tile_Type type, 
    Tile_Variation var,
    Animation_Clock_Index* clock,
    Animation_Sub_Clock_Index* sub_clock
)
{
    Tile_Type_Data* tile_type_data = tiles_data->src[type];

    // Fill in clock tile_var_index
    if (clock != NULL) {
        *clock = tile_type_data->clock;
    }

    // Fill in sub-clock tile_var_index & return animation pointer
    Tile_Variation_Data* tile_var_data = get_tile_var_data(tiles_data, type, var);

    if (sub_clock != NULL) {
        *sub_clock = tile_var_data->sub_clock;
    }

    return tile_var_data->animation;
}

void free_tiles_data(Tiles_Data* tiles_data)
{
    // TODO
    free(tiles_data);
}

#ifdef _DEBUG
void print_tile_type(Tiles_Data* td, Tile_Type type)
{
    Tile_Type_Data* tile_data = td->src[type];

    printf("===============\n%s (%d)\n===============\n", tile_type_str[type], type);
    printf("Clock: %d\n", tile_data->clock);

    for (int i = 0; i < tile_data->vars_count; i++) {
        Tile_Variation var = tile_data->vars_list[i];
        Tile_Variation_Data* tile_var = get_tile_var_data(td, type, var);

        printf("\n%s (%s)\n", tile_var_str[var], tile_var_str_short[var]);
        printf("SubClock: %d\n", tile_var->sub_clock);

        print_animation(tile_var->animation);
    }

}

void print_tiles_data(Tiles_Data* td)
{
    for (Tile_Type type = TILE_TYPE_FIRST; type <= TILE_TYPE_LAST; type++) {
        print_tile_type(td, type);
    }
}
#endif
