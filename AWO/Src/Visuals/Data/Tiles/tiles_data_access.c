#ifdef _DEBUG
#include <stdio.h>
#endif

#include "_tiles_data_internal.h"
#include "c_hashmap.h"


Tile_Data* access_tile(tile_type type)
{
    // return tiles_data->src[type];
    return NULL;
}

Tile_Var_Data* access_tile_var(Tiles_Data* td, tile_type type, tile_var var)
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

void print_tile_type(Tiles_Data* td, tile_type type)
{
    Tile_Data* tile_data = access_tile(type);

    printf("=====\n%s (%d)\n=====\n", tile_type_str[type], type);

    printf("Clock: %d\n", tile_data->clock);

    for (int i = 0; i < tile_data->vars_amount; i++) {
        tile_var var = tile_data->vars_list[i];
        Tile_Var_Data* tile_var = access_tile_var(td, type, var);

        printf("\n%s (%s)\n", tile_var_str[var], tile_var_str_short[var]);
        printf("SubClock: %d\n", tile_var->sub_clock);

        AD_print(tile_var->anim);
    }

}

void TD_print(Tiles_Data* td)
{
}
