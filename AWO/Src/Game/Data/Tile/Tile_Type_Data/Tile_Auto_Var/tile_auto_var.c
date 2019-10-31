#include <stdlib.h>

#include "Game/Data/Tile/Tile_Type_Data/Tile_Auto_Var/_tile_auto_var.h"

Auto_Var* create_tile_auto_var_data(
    cJSON* auto_var_JSON,
    map_t* variations_list_hashmap,
    int* auto_vars_amount
)
{
    if (auto_var_JSON->type == cJSON_NULL) {
        return NULL;
    }

    // Get amount of auto vars
    *auto_vars_amount = cJSON_GetArraySize(auto_var_JSON);

    // Record all auto vars_map' data
    Auto_Var* auto_var = malloc(sizeof(Auto_Var) * *auto_vars_amount);

    cJSON* auto_var_item_JSON;
    int auto_var_index = 0;

    cJSON_ArrayForEach(auto_var_item_JSON, auto_var_JSON)
    {
        // Get tile variation
        Tile_Variation* var;

        hashmap_get(
            *variations_list_hashmap, 
            cJSON_GetObjectItemCaseSensitive(auto_var_item_JSON, "tileVar")->valuestring, 
            (void**)(&var)
        );

        auto_var[auto_var_index].tile_var = *var;

        // Get adjacent tiles values
        const cJSON* auto_var_arr = cJSON_GetObjectItemCaseSensitive(auto_var_item_JSON, "adjTiles");

        auto_var[auto_var_index].adjacent_tiles[0] = cJSON_GetArrayItem(auto_var_arr, 0)->valueint;
        auto_var[auto_var_index].adjacent_tiles[1] = cJSON_GetArrayItem(auto_var_arr, 1)->valueint;
        auto_var[auto_var_index].adjacent_tiles[2] = cJSON_GetArrayItem(auto_var_arr, 2)->valueint;
        auto_var[auto_var_index].adjacent_tiles[3] = cJSON_GetArrayItem(auto_var_arr, 3)->valueint;

        auto_var_index++;
    }

    return auto_var;
}
