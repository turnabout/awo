#include "Game_Data/Tile_Data/_tile_data.h"

static Tile_Variation_Data* get_tile_variation_data(
    Tile_Data* tile_data, 
    Tile_Type type, 
    Tile_Variation var
)
{
    Tile_Variation_Data* tile_var_data;

    char* key = (char*)tile_var_str_short[var];

    if (hashmap_get(
        tile_data->src[type]->vars_map, key, (void**)(&tile_var_data)) != MAP_OK
    ) {
        return NULL;
    } else {
        return tile_var_data;
    }
}

void gather_tile_data(
    Tile_Data* tile_data, 
    Tile_Type type, 
    Tile_Variation var,
    Clock_Index* clock,
    Animation** animation
)
{
    Tile_Variation_Data* tile_var_data = get_tile_variation_data(tile_data, type, var);

    if (tile_var_data == NULL) {
        return;
    }

    if (clock != NULL) {
        *clock = tile_var_data->clock;
    }

    if (animation != NULL) {
        *animation = tile_var_data->animation;
    }
}

Tile_Variation get_next_tile_variation(Tile_Data* tile_data, Tile_Type type)
{
    static int index = 0;

    // No tile_type_data variation at given tile_var_index, reset it and return NULL
    if (index == tile_data->src[type]->var_count) {
        index = 0;
        return TILE_VAR_NONE;
    }

    return tile_data->src[type]->vars_list[index++];
}

Tile_Variation get_default_tile_variation(Tile_Data* tile_data, Tile_Type type)
{
    return tile_data->src[type]->vars_list[0];
}

Bool tile_type_variation_exists(Tile_Data* tile_data, Tile_Type type, Tile_Variation var)
{
    return get_tile_variation_data(tile_data, type, var) != NULL;
}
