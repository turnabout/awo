#include <stdlib.h>

#include "Game/Data/Tile/Neutral_Tile/Type/Variation/_tile_variation_data.h"

Animation_Clock_Index get_tile_variation_clock_index(
    char* tile_variation_string, 
    cJSON* tile_type_JSON
)
{
    // TODO: arrange
    /*
    // Get clock data for this tile type
    cJSON* tile_type_clock_data_JSON = cJSON_GetObjectItemCaseSensitive(
        tile_type_JSON, 
        "clockData"
    );

    if (tile_type_clock_data_JSON != NULL) {
        // Try to get sub clock data specific to this tile variation
        cJSON* tile_variation_sub_clocks_JSON = cJSON_GetObjectItemCaseSensitive(
            tile_type_clock_data_JSON,
            "varSubClocks"
        );

        if (cJSON_HasObjectItem(tile_variation_sub_clocks_JSON, tile_variation_string)) {
            return cJSON_GetObjectItemCaseSensitive(
                tile_variation_sub_clocks_JSON,
                tile_variation_string
            )->valueint;
        }

        // Settle for default sub clock data for all variations of this type
        return cJSON_GetObjectItemCaseSensitive(
            tile_type_clock_data_JSON,
            "varSubClocks"
        )->valueint;
    }
    */

    return 0;
}

Tile_Variation_Data* create_tile_variation_data(
    char* tile_variation_string,
    cJSON* tile_type_JSON, 
    int ss_width,
    int ss_height
)
{
    Tile_Variation_Data* tile_variation_data = malloc(sizeof(Tile_Variation_Data));

    // TODO: arrange
    tile_variation_data->clock = get_tile_variation_clock_index(
        tile_variation_string,
        tile_type_JSON
    );

    cJSON* tile_variations_JSON = cJSON_GetObjectItemCaseSensitive(tile_type_JSON, "vars");

    tile_variation_data->animation = create_animation(
        cJSON_GetObjectItemCaseSensitive(tile_variations_JSON, tile_variation_string),
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