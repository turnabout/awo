#include <stdio.h>
#include <stdlib.h>

#include "Game/Data/Tile/_tiles_data.h"

void gather_tile_data(
    Tiles_Data* tiles_data, 
    Tile_Type type, 
    Tile_Variation var,
    Animation** animation
)
{
    Tile_Type_Data* tile_type_data = tiles_data->neutral_tiles->src[type];

    // Fill in sub-clock tile_var_index & return animation pointer
    Tile_Variation_Data* tile_var_data = get_tile_variation_data(tiles_data, type, var);

    if (animation != NULL) {
        *animation = tile_var_data->animation;
    }
}

void free_tiles_data(Tiles_Data* tiles_data)
{
    if (tiles_data != NULL) {
        for (Tile_Type type = NEUTRAL_TILE_TYPE_FIRST; type < NEUTRAL_TILE_TYPE_COUNT; type++) {
            free_tile_type_data(tiles_data->neutral_tiles->src[type]);
        }

        free(tiles_data);
    }
}

#ifdef _DEBUG
void print_tile_type(Tiles_Data* td, Tile_Type type)
{
    // TODO cleanup
    /*
    Tile_Type_Data* tile_data = td->neutral_tiles->src[type];

    printf("===============\n%s (%d)\n===============\n", tile_type_str[type], type);
    printf("Clock: %d\n", tile_data->clock);

    for (int i = 0; i < tile_data->vars_count; i++) {
        Tile_Variation var = tile_data->vars_list[i];
        Tile_Variation_Data* tile_var = get_tile_variation_data(td, type, var);

        printf("\n%s (%s)\n", tile_var_str[var], tile_var_str_short[var]);
        printf("SubClock: %d\n", tile_var->sub_clock);

        print_animation(tile_var->animation);
    }
    */
}

void print_tiles_data(Tiles_Data* td)
{
    for (Tile_Type type = NEUTRAL_TILE_TYPE_FIRST; type <= NEUTRAL_TILE_TYPE_LAST; type++) {
        print_tile_type(td, type);
    }
}
#endif
