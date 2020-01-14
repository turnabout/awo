#include <c_hashmap.h>

#include "Game_Data/Tile_Data/_tile_data.h"
#include "Game_Data/Tile_Data/Tile_Type_Data/Tile_Variation_Data/tile_variation_data.h"

Tile_Variation get_next_tile_variation(Tiles_Data* tiles_data, Tile_Type type)
{
    static int index = 0;

    Tile_Type_Data* tile = tiles_data->neutral_tiles->src[type];

    // No tile_type_data variation at given tile_var_index, reset it and return NULL
    if (index == tile->var_count) {
        index = 0;
        return TILE_VAR_NONE;
    }

    return tile->vars_list[index++];
}

Animation* get_next_tile_variation_animation(Tiles_Data* tiles_data, Tile_Type type)
{
    Tile_Variation variation = get_next_tile_variation( tiles_data, type);

    if (variation == TILE_VAR_NONE) {
        return NULL;
    }

    return get_tile_variation_data(tiles_data, type, variation)->animation;
}

Tile_Variation_Data* get_tile_variation_data(
    Tiles_Data* tiles_data, 
    Tile_Type type, 
    Tile_Variation variation
)
{
    Tile_Variation_Data* tile_var_data;

    char* key = (char*)tile_var_str_short[variation];

    if (hashmap_get(
        tiles_data->neutral_tiles->src[type]->vars_map, key, (void**)(&tile_var_data)) != MAP_OK
    ) {
        return NULL;
    } else {
        return tile_var_data;
    }
}

Tile_Variation get_default_tile_variation(Tiles_Data* tiles_data, Tile_Type type)
{
    return tiles_data->neutral_tiles->src[type]->vars_list[0];
}

Bool tile_type_variation_exists(Tiles_Data* tiles_data, Tile_Type type, Tile_Variation var)
{
    return get_tile_variation_data(tiles_data, type, var) != NULL;
}
