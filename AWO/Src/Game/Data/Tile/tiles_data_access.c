#include <stdio.h>
#include <stdlib.h>
#include <c_hashmap.h>

#include "Game/Data/Tile/_tiles_data.h"

Tile_Var_Data* get_tile_var_data(Tiles_Data* tiles_data, Tile_Type type, Tile_Variation var)
{
    Tile_Var_Data* result;

    if (hashmap_get(
        tiles_data->src[type]->vars_map, 
        (char*)tile_var_str_short[var], 
        (void**)(&result)) != MAP_OK
    ) {
        return NULL;
    } else {
        return result;
    }
}

Animation* get_next_tile_animation(Tiles_Data* tiles_data, Tile_Type type)
{
    // Variation var_index
    static int var_index = 0;

    Tile_Type_Data* tile = tiles_data->src[type];

    // No tile variation at given var_index, reset it and return NULL
    if (var_index == tile->vars_count) {
        var_index = 0;
        return NULL;
    }

    // Get tile variation data
    Tile_Variation v = tile->vars_list[var_index];
    Tile_Var_Data* tile_var_data = get_tile_var_data(tiles_data, type, v);

    // Increment var_index for next time
    var_index++;

    return tile_var_data->animation;
}

const char* get_next_tile_var_data(Tiles_Data* td, Tile_Type tt, Uint8* var_val)
{
    // Variation var_index
    static int index = 0;

    Tile_Type_Data* tile = td->src[tt];

    // No tile variation at given var_index, reset it and return NULL
    if (index == tile->vars_count) {
        index = 0;
        return NULL;
    }

    // Get tile variation data
    *var_val = tile->vars_list[index++];

    return tile_var_str[*var_val];
}

Tile_Variation get_tile_default_var(Tiles_Data* td, Tile_Type type)
{
    return td->src[type]->vars_list[0];
}

Tile_Variation get_tile_auto_var(
    Tiles_Data* td,
    Tile_Type middle_tile,
    Tile_Type top_tile,
    Tile_Type right_tile,
    Tile_Type bottom_tile,
    Tile_Type left_tile
)
{
    Tile_Type_Data* middle_tile_data = td->src[middle_tile];

    // Go through all of the middle tile's autovars
    for (int i = 0; i < middle_tile_data->auto_vars_count; i++) {

        // Get this autovar and look for match with adjacent tiles
        Auto_Var auto_var = middle_tile_data->auto_vars[i];

        if (
            (auto_var.adjacent_tiles[Auto_Var_Up]    & (1 << top_tile))    &&
            (auto_var.adjacent_tiles[Auto_Var_Right] & (1 << right_tile))  &&
            (auto_var.adjacent_tiles[Auto_Var_Down]  & (1 << bottom_tile)) &&
            (auto_var.adjacent_tiles[Auto_Var_Left]  & (1 << left_tile))
        ) {
            return auto_var.var;
        }
    }

    printf("default...\n");
    return get_tile_default_var(td, middle_tile);
}

Animation* gather_tile_data(
    Tiles_Data* tiles_data, 
    Tile_Type type, 
    Tile_Variation var,
    Animation_Clock_Index* clock,
    Animation_Sub_Clock_Index* sub_clock
)
{
    Tile_Type_Data* tile = tiles_data->src[type];

    // Fill in clock var_index
    if (clock != NULL) {
        *clock = tile->clock;
    }

    // Fill in sub-clock var_index & return animation pointer
    Tile_Var_Data* tile_var_data = get_tile_var_data(tiles_data, type, var);

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
        Tile_Var_Data* tile_var = get_tile_var_data(td, type, var);

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
