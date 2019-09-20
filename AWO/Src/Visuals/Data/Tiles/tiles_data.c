#include <stdio.h>

#include "cJSON.h"
#include "tiles_data.h"

#pragma warning( disable : 6011 )

static Tiles_Data* tiles_data;

// Initialize tiles' source visuals data
void init_tiles_src(const cJSON* src_json);

void init_tiles_visual_data_structure(cJSON* t_visuals_JSON)
{
    tiles_data = malloc(sizeof(Tiles_Data));
    tiles_data->ss_meta_data = SS_Meta_create_from_JSON(t_visuals_JSON);

    // Add tiles' src data
    init_tiles_src(cJSON_GetObjectItemCaseSensitive(t_visuals_JSON, "src"));
}

void init_tiles_src(const cJSON* src_json)
{
    // Initialize temporary hashmap containing all variations, using short strings as keys.
    // This is done so we can access the corresponding tile variation for each tile, as we loop 
    // the JSON data
    map_t all_vars_hashmap = hashmap_new();

    for (tile_var var = TILE_VAR_FIRST; var <= TILE_VAR_LAST; var++) {
        tile_var* v = malloc(sizeof(tile_var));
        *v = var;

        hashmap_put(
            all_vars_hashmap,
            (char*)tile_var_str_short[var],
            v
        );
    }

    // Gather all data from JSON
    const cJSON* tile_type_json;
    int tile_count = 0;

    // Loop tile types
    cJSON_ArrayForEach(tile_type_json, src_json)
    {
        const cJSON* tile_vars_json; // JSON holding all variations of this tile
        const cJSON* tile_var_json;  // JSON holding currently looped variation of this tile
        const cJSON* var_sub_clocks; // JSON holding this tile's variations' sub clocks
        Tile_Data* tile_data;        // The tile data object representing this tile to be populated
        map_t vars_hashmap;          // Hashmap containing animations for this tile's variations
        int vars_amount;             // Amount of variations this tile has
        tile_var* vars_list;         // List of every variation this tile has
        Animation_Sub_Clock_Index default_sub_clock; // Default sub clock used by this tile's vars

        tile_vars_json = cJSON_GetObjectItemCaseSensitive(tile_type_json, "vars");

        // Initialize tile data
        tile_data = malloc(sizeof(Tile_Data));
        vars_hashmap = hashmap_new();

        // Get amount of variations and initialize list of variations
        vars_amount = cJSON_GetArraySize(tile_vars_json);
        vars_list = malloc(sizeof(Tile_Data) * vars_amount);

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
            tile_var* res;
            hashmap_get(all_vars_hashmap, tile_var_json->string, (void**)(&res));

            *vars_list = *res;
            vars_list++;

            // Create this tile variation & get its animation
            Tile_Var_Data* tile_var = malloc(sizeof(Tile_Var_Data));
            tile_var->anim = AD_create_from_JSON(tile_var_json);

            int bla = cJSON_HasObjectItem(var_sub_clocks, tile_var_json->string);

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
        tile_data->vars = vars_hashmap;
        tile_data->vars_amount = vars_amount;
        tile_data->vars_list = vars_list;
        
        // Store populated tile data
        tiles_data->src[tile_count++] = tile_data;
    }

    // Free the temporary variations hashmap
    for (tile_var var = TILE_VAR_FIRST; var <= TILE_VAR_LAST; var++) {
        tile_var* res;

        hashmap_get(
            all_vars_hashmap,
            (char*)tile_var_str_short[var],
            (void**)(&res)
        );

        free(res);
    }

    hashmap_free(all_vars_hashmap);
}

Tile_Data* access_tile(tile_type type)
{
    return tiles_data->src[type];
}

Tile_Var_Data* access_tile_var(tile_type type, tile_var var)
{
    Tile_Var_Data* result;

    if (hashmap_get(
        tiles_data->src[type]->vars, 
        (char*)tile_var_str_short[var], 
        (void**)(&result)) != MAP_OK
    ) {
        return NULL;
    } else {
        return result;
    }
}

void debug_print_tile_data(tile_type type)
{
    Tile_Data* tile_data = access_tile(type);

    printf("=====\n%s (%d)\n=====\n", tile_type_str[type], type);

    printf("Clock: %d\n", tile_data->clock);

    for (int i = 0; i < tile_data->vars_amount; i++) {
        tile_var var = tile_data->vars_list[i];
        Tile_Var_Data* tile_var = access_tile_var(type, var);

        printf("\n%s (%s)\n", tile_var_str[var], tile_var_str_short[var]);
        printf("SubClock: %d\n", tile_var->sub_clock);

        AD_print(tile_var->anim);
    }
}