#include <stdlib.h>

#include "Game_Data/Tile_Data/Tile_Type_Data/tile_type_data.h"

Tile_Type_Data* create_tile_type_data(
    cJSON* tile_type_JSON, 
    map_t variations_list_hashmap,
    int ss_width,
    int ss_height
)
{
    // Initialize tile data
    Tile_Type_Data* data = malloc(sizeof(Tile_Type_Data));

    if (data == NULL) {
        return NULL;
    }

    // Get tile variations data
    data->vars_map = hashmap_new();

    // Get amount of variations
    cJSON* tile_vars_JSON = cJSON_GetObjectItem(tile_type_JSON, "vars");

    data->var_count = cJSON_GetArraySize(tile_vars_JSON);

    if (data->var_count < 1) {
        free_tile_type_data(data);
        return NULL;
    }

    //  Initialize list of variations
    data->vars_list = malloc(sizeof(Tile_Variation) * data->var_count);

    // Loop tile variations
    for (int i = 0; i < data->var_count; i++) {
        cJSON* tile_variation_JSON = cJSON_GetArrayItem(tile_vars_JSON, i);

        // Get which tile variation this JSON object represents
        Tile_Variation* tile_variation;

        hashmap_get(
            variations_list_hashmap, 
            tile_variation_JSON->string, 
            (void**)(&tile_variation)
        );

        data->vars_list[i] = *tile_variation;

        // Add populated tile variation to hashmap
        hashmap_put(
            data->vars_map, 
            tile_var_str_short[*tile_variation], 

            create_tile_variation_data(
                cJSON_GetObjectItemCaseSensitive(
                    tile_vars_JSON, 
                    tile_var_str_short[*tile_variation]
                ),
                ss_width,
                ss_height
            )
        );
    }
    
    // Get auto-var data
    data->auto_vars = create_tile_auto_var_data(
        cJSON_GetObjectItem(tile_type_JSON, "autoVars"),
        &variations_list_hashmap,
        &data->auto_vars_count
    );

    data->placement_rules = create_tile_placement_rule_set(
        cJSON_GetObjectItem(tile_type_JSON, "placementRules")
    );

    return data;
}

void free_tile_type_data(Tile_Type_Data* data)
{
    if (data == NULL) {
        return;
    }

    // Free tile variations data
    for (int i = 0; i < data->var_count; i++) {
        Tile_Variation tile_variation = data->vars_list[i];
        Tile_Variation_Data* tile_variation_data;

        hashmap_get(
            data->vars_map,
            (char*)tile_var_str_short[tile_variation],
            (void**)(&tile_variation_data)
        );

        free_tile_variation_data(tile_variation_data);
    }

    hashmap_free(data->vars_map);

    free_tile_placement_rule_set(data->placement_rules);
    free(data->auto_vars);
    free(data);
}
