#include <stdlib.h>
#include <cglm/cglm.h>

#include "Game/Data/Tile/_tiles_data.h"

void get_tiles_src_data(Tiles_Data* td, const cJSON* src_json, mat4 ss_projection);

Tiles_Data* create_tiles_data(cJSON* tiles_data_JSON, mat4 ss_projection)
{
    Tiles_Data* tiles_data = malloc(sizeof(Tiles_Data));

    // Add tiles' src data
    get_tiles_src_data(
        tiles_data,
        cJSON_GetObjectItemCaseSensitive(tiles_data_JSON, "src"),
        ss_projection
    );

    return tiles_data;
}

// Get a tile's auto tile_variation_data data struct
Auto_Var* get_tile_auto_var_data(
    const cJSON* auto_var_json, 
    int* auto_vars_amount, 
    map_t* all_vars_hashmap
)
{
    // Record amount
    *auto_vars_amount = cJSON_GetArraySize(auto_var_json);

    // Record all auto vars_map' data
    Auto_Var* auto_var = malloc(sizeof(Auto_Var) * *auto_vars_amount);

    const cJSON* auto_var_item_json;
    int auto_var_index = 0;

    cJSON_ArrayForEach(auto_var_item_json, auto_var_json)
    {
        // Get tile variation
        Tile_Variation* var;

        hashmap_get(
            *all_vars_hashmap, 
            cJSON_GetObjectItemCaseSensitive(auto_var_item_json, "tileVar")->valuestring, 
            (void**)(&var)
        );

        auto_var[auto_var_index].tile_var = *var;

        // Get adjacent tiles values
        const cJSON* auto_var_arr = cJSON_GetObjectItemCaseSensitive(auto_var_item_json, "adjTiles");

        auto_var[auto_var_index].adjacent_tiles[0] = cJSON_GetArrayItem(auto_var_arr, 0)->valueint;
        auto_var[auto_var_index].adjacent_tiles[1] = cJSON_GetArrayItem(auto_var_arr, 1)->valueint;
        auto_var[auto_var_index].adjacent_tiles[2] = cJSON_GetArrayItem(auto_var_arr, 2)->valueint;
        auto_var[auto_var_index].adjacent_tiles[3] = cJSON_GetArrayItem(auto_var_arr, 3)->valueint;

        auto_var_index++;
    }

    return auto_var;
}

// TODO: refactor/clean up
void get_tiles_src_data(Tiles_Data* tiles_data, const cJSON* src_json, mat4 ss_projection)
{
    // Initialize temporary hashmap containing all variations, using short strings as keys.
    // This is done so we can access the corresponding tile variation for each tile, as we loop 
    // the JSON data
    map_t all_vars_hashmap = hashmap_new();

    for (Tile_Variation var = TILE_VAR_FIRST; var <= TILE_VAR_LAST; var++) {

        // Have to malloc the tile variation, because hashmap_put requires a value to be a pointer
        Tile_Variation* tile_variation = malloc(sizeof(Tile_Variation));
        *tile_variation = var;

        hashmap_put(
            all_vars_hashmap,
            (char*)tile_var_str_short[var],
            tile_variation
        );
    }

    // Gather all data from JSON
    Tile_Type tile_type = TILE_TYPE_FIRST;

    // Loop tile types
    cJSON* tile_type_JSON;
    cJSON_ArrayForEach(tile_type_JSON, src_json)
    {
        cJSON* tile_vars_json; // JSON holding all variations of this tile
        cJSON* tile_variation_JSON;  // JSON holding currently looped variation of this tile
        cJSON* var_sub_clocks; // JSON holding this tile's variations' sub clocks
        cJSON* auto_var_json;  // JSON holding this tile type's auto-tile_variation_data data

        Tile_Type_Data* tile_data; // The tile data object representing this tile to be populated
        map_t vars_hashmap;        // Hashmap every tile variation data for this tile type
        int vars_amount;           // Amount of variations this tile has
        Tile_Variation* vars_list; // List of every variation this tile has
        Animation_Sub_Clock_Index default_sub_clock; // Default sub clock used by this tile's vars_map

        tile_vars_json = cJSON_GetObjectItemCaseSensitive(tile_type_JSON, "vars");
        auto_var_json = cJSON_GetObjectItemCaseSensitive(tile_type_JSON, "autoVars");

        // Initialize tile data
        tile_data = malloc(sizeof(Tile_Type_Data));
        vars_hashmap = hashmap_new();

        // Get amount of variations and initialize list of variations
        vars_amount = cJSON_GetArraySize(tile_vars_json);
        vars_list = malloc(sizeof(Tile_Type_Data) * vars_amount);

        // TODO: Only do this when game mode is design room
        // Get this tile's auto tile_variation_data data
        if (auto_var_json->type != cJSON_NULL) {

            tile_data->auto_vars = get_tile_auto_var_data(
                auto_var_json, 
                &tile_data->auto_vars_count,
                &all_vars_hashmap
             );
        }

        // Gather clock data for this tile type
        cJSON* tile_type_clock_data_JSON = cJSON_GetObjectItemCaseSensitive(
            tile_type_JSON, 
            "clockData"
        );

        // Get this tile's clock data and prepare to get tile variations' clock data
        tile_data->clock = (cJSON_HasObjectItem(tile_type_JSON, "clockData"))

            ? tile_data->clock = cJSON_GetObjectItemCaseSensitive(
                tile_type_clock_data_JSON,
                "clock"
            )->valueint

            : No_Clock;

        // Loop tile variations
        cJSON_ArrayForEach(tile_variation_JSON, tile_vars_json)
        {
            // Get which tile variation this JSON object represents
            Tile_Variation* tile_variation;
            hashmap_get(all_vars_hashmap, tile_variation_JSON->string, (void**)(&tile_variation));

            // Store on this tile data's vars list
            *vars_list = *tile_variation;
            vars_list++;

            // Get short string representing this tile variation
            char* tile_variation_string = tile_var_str_short[*tile_variation];

            // Add populated tile variation to hashmap
            hashmap_put(
                vars_hashmap, 
                tile_variation_string, 

                create_tile_variation_data(
                    tile_variation_string,
                    tile_type_JSON,
                    ss_projection
                )
            );
        }

        // Reset variations list pointer to its start
        vars_list -= vars_amount;

        // Populate tile data
        tile_data->vars_map = vars_hashmap;
        tile_data->vars_count = vars_amount;
        tile_data->vars_list = vars_list;
        
        // Store populated tile data
        tiles_data->src[tile_type++] = tile_data;
    }

    // Free the temporary variations hashmap
    for (Tile_Variation var = TILE_VAR_FIRST; var <= TILE_VAR_LAST; var++) {
        Tile_Variation* res;

        hashmap_get(
            all_vars_hashmap,
            (char*)tile_var_str_short[var],
            (void**)(&res)
        );

        free(res);
    }

    hashmap_free(all_vars_hashmap);
}
