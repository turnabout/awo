#include <stdlib.h>

#include "Utilities/macros.h"
#include "Game/Data/Tile/Neutral_Tile/Type/_tile_type_data.h"
#include "Game/Data/Tile/Neutral_Tile/Type/Variation/_tile_variation_data.h"

PRAGMA(warning (disable: 4090))

Tile_Type_Data* create_tile_type_data(
    cJSON* tile_type_JSON, 
    map_t variations_list_hashmap,
    int ss_width,
    int ss_height
)
{
    // Initialize tile data
    Tile_Type_Data* data = malloc(sizeof(Tile_Type_Data));

    data->vars_map = hashmap_new();

    // Get amount of variations and initialize list of variations
    cJSON* tile_vars_JSON = cJSON_GetObjectItemCaseSensitive(tile_type_JSON, "vars");

    data->vars_count = cJSON_GetArraySize(tile_vars_JSON);
    Tile_Variation* vars_list = malloc(sizeof(Tile_Type_Data) * data->vars_count);

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
        char* tile_var_short_str = tile_var_str_short[*tile_variation];

        // Add populated tile variation to hashmap
        hashmap_put(
            data->vars_map, 
            tile_var_short_str, 

            create_tile_variation_data(
                cJSON_GetObjectItemCaseSensitive(tile_vars_JSON, tile_var_short_str),
                ss_width,
                ss_height
            )
        );
    }

    // Reset variations list pointer to its start
    vars_list -= data->vars_count;

    data->vars_list = vars_list;
    
    // Get auto-var data
    data->auto_vars = create_tile_auto_var_data(
        cJSON_GetObjectItemCaseSensitive(tile_type_JSON, "autoVars"),
        &variations_list_hashmap,
        &data->auto_vars_count
    );

    // Get tile placement rules
    cJSON* placement_rules_JSON = cJSON_GetObjectItem(tile_type_JSON, "placementRules");
    data->placement_rule_count = cJSON_GetArraySize(placement_rules_JSON);

    if (data->placement_rule_count < 1) {
        data->placement_rules = NULL;
    } else {
        data->placement_rules = malloc(sizeof(Tile_Placement_Rule*) * data->placement_rule_count);
    }

    for (int i = 0; i < data->placement_rule_count; i++) {
        data->placement_rules[i] = create_tile_placement_rule(
            cJSON_GetArrayItem(placement_rules_JSON, i)
        );
    }

    return data;
}

void free_tile_type_data(Tile_Type_Data* data)
{
    if (data == NULL) {
        return;
    }

    // Free every tile variation data object attached to this tile type
    for (int i = 0; i < data->vars_count; i++) {
        Tile_Variation tile_variation = data->vars_list[i];
        Tile_Variation_Data* tile_variation_data;

        hashmap_get(
            data->vars_map,
            (char*)tile_var_str_short[tile_variation],
            (void**)(&tile_variation_data)
        );

        free_tile_variation_data(tile_variation_data);
    }

    // Free the hashmap itself
    free(data->vars_map);

    // Free auto-var data
    free(data->auto_vars);

    // Free placement rules
    for (int i = 0; i < data->placement_rule_count; i++) {
        free_tile_placement_rule(data->placement_rules[i]);
    }

    free(data->placement_rules);

    free(data);
}
