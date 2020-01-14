#include "Game_Data/Tile_Data/Tile_Type_Data/_tile_type_data.h"

Tile_Variation get_next_tile_variation(Tile_Type_Data* tile_type_data)
{
    static int index = 0;

    // No tile_type_data variation at given tile_var_index, reset it and return NULL
    if (index == tile_type_data->var_count) {
        index = 0;
        return TILE_VAR_NONE;
    }

    return tile_type_data->vars_list[index++];
}

Tile_Variation_Data* get_next_tile_variation_data(Tile_Type_Data* tile_type_data)
{
    Tile_Variation variation = get_next_tile_variation(tile_type_data);

    if (variation == TILE_VAR_NONE) {
        return NULL;
    }

    return get_tile_variation_data(tile_type_data, variation);
}

Tile_Variation_Data* get_tile_variation_data(Tile_Type_Data* tile_type_data, Tile_Variation var)
{
    Tile_Variation_Data* tile_var_data;

    char* key = (char*)tile_var_str_short[var];

    if (hashmap_get(
        tile_type_data->vars_map, key, (void**)(&tile_var_data)) != MAP_OK
    ) {
        return NULL;
    } else {
        return tile_var_data;
    }
}

Tile_Variation get_default_tile_variation(Tile_Type_Data* tile_type_data)
{
    return tile_type_data->vars_list[0];
}

Bool tile_type_variation_exists(Tile_Type_Data* tile_type_data, Tile_Variation var)
{
    return get_tile_variation_data(tile_type_data, var) != NULL;
}
