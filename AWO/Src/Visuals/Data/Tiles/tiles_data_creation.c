#include <stdlib.h>

#include "tiles_data.h"
#include "_tiles_data_internal.h"

void get_tiles_src_data(Tiles_Data* td, const cJSON* src_json);

Tiles_Data* TD_create_from_JSON(cJSON* tiles_visuals_JSON)
{
    Tiles_Data* td = malloc(sizeof(Tiles_Data));

    // Store metadata & JSON for palettes
    td->ss_meta_data = SS_Meta_create_from_JSON(tiles_visuals_JSON);
    td->JSON = tiles_visuals_JSON;

    // Add tiles' src data
    get_tiles_src_data(
        td,
        cJSON_GetObjectItemCaseSensitive(tiles_visuals_JSON, "src")
    );

    return td;
}

// Get a tile's auto var data struct
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
        Tile_Var* var;

        hashmap_get(
            *all_vars_hashmap, 
            cJSON_GetObjectItemCaseSensitive(auto_var_item_json, "tileVar")->valuestring, 
            (void**)(&var)
        );

        auto_var[auto_var_index].var = *var;

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

void get_tiles_src_data(Tiles_Data* td, const cJSON* src_json)
{
    // Initialize temporary hashmap containing all variations, using short strings as keys.
    // This is done so we can access the corresponding tile variation for each tile, as we loop 
    // the JSON data
    map_t all_vars_hashmap = hashmap_new();

    for (Tile_Var var = TILE_VAR_FIRST; var <= TILE_VAR_LAST; var++) {
        Tile_Var* v = malloc(sizeof(Tile_Var));
        *v = var;

        hashmap_put(
            all_vars_hashmap,
            (char*)tile_var_str_short[var],
            v
        );
    }

    // Gather all data from JSON
    const cJSON* tile_type_json;
    int tile_type = 0;

    // Loop tile types
    cJSON_ArrayForEach(tile_type_json, src_json)
    {
        const cJSON* tile_vars_json; // JSON holding all variations of this tile
        const cJSON* tile_var_json;  // JSON holding currently looped variation of this tile
        const cJSON* var_sub_clocks; // JSON holding this tile's variations' sub clocks
        const cJSON* auto_var_json;  // JSON holding this tile type's auto-var data

        Tile_Data* tile_data;        // The tile data object representing this tile to be populated
        map_t vars_hashmap;          // Hashmap containing animations for this tile's variations
        int vars_amount;             // Amount of variations this tile has
        Tile_Var* vars_list;         // List of every variation this tile has
        Animation_Sub_Clock_Index default_sub_clock; // Default sub clock used by this tile's vars_map

        tile_vars_json = cJSON_GetObjectItemCaseSensitive(tile_type_json, "vars");
        auto_var_json = cJSON_GetObjectItemCaseSensitive(tile_type_json, "autoVars");

        // Initialize tile data
        tile_data = malloc(sizeof(Tile_Data));
        vars_hashmap = hashmap_new();

        // Get amount of variations and initialize list of variations
        vars_amount = cJSON_GetArraySize(tile_vars_json);
        vars_list = malloc(sizeof(Tile_Data) * vars_amount);

        // TODO: Only do this when game mode is design room
        // Get this tile's auto var data
        if (auto_var_json->type != cJSON_NULL) {

            tile_data->auto_vars = get_tile_auto_var_data(
                auto_var_json, 
                &tile_data->auto_vars_amount,
                &all_vars_hashmap
             );
        }

        // Get this tile's clock data and prepare to get tile variations' clock data
        if (cJSON_HasObjectItem(tile_type_json, "clockData")) {
            const cJSON* c_data = cJSON_GetObjectItemCaseSensitive(tile_type_json, "clockData");

            tile_data->clock = cJSON_GetObjectItemCaseSensitive(c_data, "clock")->valueint;
            default_sub_clock = cJSON_GetObjectItemCaseSensitive(c_data, "defaultSubClock")->valueint;

            var_sub_clocks = cJSON_GetObjectItemCaseSensitive(c_data, "varSubClocks");
        } else {
            tile_data->clock = No_Clock;
            default_sub_clock = No_Sub_Clock;

            var_sub_clocks = NULL;
        }

        // Loop tile variations
        cJSON_ArrayForEach(tile_var_json, tile_vars_json)
        {
            // Add this variation to the tile's variations list
            Tile_Var* res;
            hashmap_get(all_vars_hashmap, tile_var_json->string, (void**)(&res));

            *vars_list = *res;
            vars_list++;

            // Create this tile variation & get its animation
            Tile_Var_Data* tile_var = malloc(sizeof(Tile_Var_Data));
            tile_var->anim = anim_create_from_JSON(tile_var_json);

            // Get this tile variation's correct sub clock value
            if (
                var_sub_clocks != NULL && 
                cJSON_HasObjectItem(var_sub_clocks, tile_var_json->string)
            ) {
                tile_var->sub_clock = cJSON_GetObjectItemCaseSensitive(var_sub_clocks, tile_var_json->string)->valueint;
            } else {
                tile_var->sub_clock = default_sub_clock;
            }

            // Add populated tile variation to hashmap
            hashmap_put(
                vars_hashmap, 
                tile_var_json->string, 
                tile_var
            );
        }

        // Reset variations list pointer to its start
        vars_list -= vars_amount;

        // Populate tile data
        tile_data->vars_map = vars_hashmap;
        tile_data->vars_amount = vars_amount;
        tile_data->vars_list = vars_list;
        
        // Store populated tile data
        td->src[tile_type++] = tile_data;
    }

    // Free the temporary variations hashmap
    for (Tile_Var var = TILE_VAR_FIRST; var <= TILE_VAR_LAST; var++) {
        Tile_Var* res;

        hashmap_get(
            all_vars_hashmap,
            (char*)tile_var_str_short[var],
            (void**)(&res)
        );

        free(res);
    }

    hashmap_free(all_vars_hashmap);
}
