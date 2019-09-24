#ifdef _DEBUG
#include <stdio.h>
#endif

#include "_tiles_data_internal.h"
#include "c_hashmap.h"
#include "../Palette/palette_tree.h"

Tile_Var_Data* get_tile_var(Tiles_Data* td, Tile_Type type, Tile_Var var)
{
    Tile_Var_Data* result;

    if (hashmap_get(
        td->src[type]->vars, 
        (char*)tile_var_str_short[var], 
        (void**)(&result)) != MAP_OK
    ) {
        return NULL;
    } else {
        return result;
    }
}

Palette_Tree* TD_get_palette(Tiles_Data* td, Weather weather)
{
    const cJSON* base = cJSON_GetObjectItemCaseSensitive(td->JSON, "basePalette");
    const cJSON* tiles_palettes = cJSON_GetObjectItemCaseSensitive(td->JSON, "palettes");

    // Get cJSON item for the given palette
    const cJSON* tile_palette = cJSON_GetArrayItem(tiles_palettes, weather);

    if (cJSON_GetArraySize(tile_palette) < 1) {
        return NULL;
    }

    // Get the result
    return PT_create_from_JSON(base, tile_palette);
}

SS_Metadata* TD_get_ss_metadata(Tiles_Data* td)
{
    return td->ss_meta_data;
}

Animation* TD_get_next_tile_animation(Tiles_Data* td, Tile_Type tt)
{
    // Variation index
    static int index = 0;

    Tile_Data* tile = td->src[tt];

    // No tile variation at given index, reset it and return NULL
    if (index == tile->vars_amount) {
        index = 0;
        return NULL;
    }

    // Get tile variation data
    Tile_Var v = tile->vars_list[index];
    Tile_Var_Data* t_var_data;

    hashmap_get(tile->vars, (char*)tile_var_str_short[v], (void**)(&t_var_data));

    // Increment index for next time
    index++;

    return t_var_data->anim;
}

SDL_Rect* TD_gather_tile_data(
    Tiles_Data* td, 
    Tile_Type tt, 
    Tile_Var tv,
    Animation_Clock_Index* clock,
    Animation_Sub_Clock_Index* sub_clock
)
{
    Tile_Data* tile = td->src[tt];

    // Fill in clock index
    *clock = tile->clock;

    // Fill in sub-clock index & return animation frames pointer
    Tile_Var_Data* t_var_data;
    int count;
    hashmap_get(tile->vars, (char*)tile_var_str_short[tv], (void**)(&t_var_data));

    *sub_clock = t_var_data->sub_clock;

    return anim_get_frames(t_var_data->anim, &count);
}

void print_tile_type(Tiles_Data* td, Tile_Type type)
{
    Tile_Data* tile_data = td->src[type];

    printf("===============\n%s (%d)\n===============\n", tile_type_str[type], type);
    printf("Clock: %d\n", tile_data->clock);

    for (int i = 0; i < tile_data->vars_amount; i++) {
        Tile_Var var = tile_data->vars_list[i];
        Tile_Var_Data* tile_var = get_tile_var(td, type, var);

        printf("\n%s (%s)\n", tile_var_str[var], tile_var_str_short[var]);
        printf("SubClock: %d\n", tile_var->sub_clock);

        anim_print(tile_var->anim);
    }

}

void TD_print(Tiles_Data* td)
{
    for (Tile_Type type = TILE_TYPE_FIRST; type <= TILE_TYPE_LAST; type++) {
        print_tile_type(td, type);
    }
}
