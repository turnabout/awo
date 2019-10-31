#include <stdlib.h>

#include "Game/Data/Tile/Type/_tile_type_data.h"
#include "Game/Data/Tile/Type/Variation/_tile_variation_data.h"

Tile_Type_Data* create_tile_type_data(
    cJSON* tile_type_JSON, 
    map_t variations_list_hashmap,
    mat4 projection
)
{
    // Initialize tile data
    Tile_Type_Data* tile_type_data = malloc(sizeof(Tile_Type_Data));

    tile_type_data->vars_map = hashmap_new();

    // Get amount of variations and initialize list of variations
    cJSON* tile_vars_JSON = cJSON_GetObjectItemCaseSensitive(tile_type_JSON, "vars");

    tile_type_data->vars_count = cJSON_GetArraySize(tile_vars_JSON);
    Tile_Variation* vars_list = malloc(sizeof(Tile_Type_Data) * tile_type_data->vars_count);

    // Get the animation clock index belonging to this tile type
    cJSON* tile_type_clock_data_JSON = cJSON_GetObjectItemCaseSensitive(
        tile_type_JSON, 
        "clockData"
    );

    tile_type_data->clock = (cJSON_HasObjectItem(tile_type_JSON, "clockData"))

        ? tile_type_data->clock = cJSON_GetObjectItemCaseSensitive(
            tile_type_clock_data_JSON,
            "clock"
        )->valueint

        : No_Clock;

    // Loop tile variations
    cJSON* tile_variation_JSON;
    cJSON_ArrayForEach(tile_variation_JSON, tile_vars_JSON)
    {
        // Get which tile variation this JSON object represents
        Tile_Variation* tile_variation;
        hashmap_get(variations_list_hashmap, tile_variation_JSON->string, (void**)(&tile_variation));

        // Store on this tile data's vars list
        *vars_list = *tile_variation;
        vars_list++;

        // Get short string representing this tile variation
        char* tile_variation_string = tile_var_str_short[*tile_variation];

        // Add populated tile variation to hashmap
        hashmap_put(
            tile_type_data->vars_map, 
            tile_variation_string, 

            create_tile_variation_data(
                tile_variation_string,
                tile_type_JSON,
                projection
            )
        );
    }

    // Reset variations list pointer to its start
    vars_list -= tile_type_data->vars_count;

    tile_type_data->vars_list = vars_list;
    
    // Get this tile's auto tile data
    tile_type_data->auto_vars = create_tile_auto_var_data(
        cJSON_GetObjectItemCaseSensitive(tile_type_JSON, "autoVars"),
        &variations_list_hashmap,
        &tile_type_data->auto_vars_count
    );

    return tile_type_data;
}

void free_tile_type_data(Tile_Type_Data* tile_type_data)
{
    // Free every tile variation data object attached to this tile type
    for (int i = 0; i < tile_type_data->vars_count; i++) {
        Tile_Variation tile_variation = tile_type_data->vars_list[i];
        Tile_Variation_Data* tile_variation_data;

        hashmap_get(
            tile_type_data->vars_map,
            (char*)tile_var_str_short[tile_variation],
            (void**)(&tile_variation_data)
        );

        free_tile_variation_data(tile_variation_data);
    }

    // Free the map itself
    free(tile_type_data->vars_map);

    free(tile_type_data->auto_vars);
    free(tile_type_data);
}