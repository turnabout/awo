#include <stdlib.h>

#include "Game/Data/Tile/Neutral_Tile/Type/Variation/_tile_variation_data.h"

Tile_Variation_Data* create_tile_variation_data(
    cJSON* tile_var_JSON,
    int ss_width,
    int ss_height
)
{
    Tile_Variation_Data* tile_variation_data = malloc(sizeof(Tile_Variation_Data));

    // Set clock
    cJSON* clock_JSON = cJSON_GetObjectItemCaseSensitive(tile_var_JSON, "clock");
    tile_variation_data->clock = (clock_JSON != NULL) ? clock_JSON->valueint : No_Clock;

    // Set frames
    tile_variation_data->animation = create_animation(
        cJSON_GetObjectItemCaseSensitive(tile_var_JSON, "frames"),
        ss_width,
        ss_height
    );

    return tile_variation_data;
}

void free_tile_variation_data(Tile_Variation_Data* tile_variation_data)
{
    free_animation(tile_variation_data->animation);
    free(tile_variation_data);
}