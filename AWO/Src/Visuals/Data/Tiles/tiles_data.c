#include "../JSON/JSON_access.h"
#include "../data_init_internal.h"
#include "tiles_data_access.h"

#pragma warning( disable : 6011 )

static Tiles_Data* tiles_data;
static const cJSON* tiles_visuals_JSON;

// Initialize tiles' source visuals data
void init_tiles_src(const cJSON* src_json);

void init_tiles_visual_data_structure(cJSON* t_visuals_JSON)
{
    SS_Meta_Data* ss_meta_data = malloc(sizeof(SS_Meta_Data));
    tiles_data = malloc(sizeof(Tiles_Data));

    tiles_visuals_JSON = t_visuals_JSON;

    // Add tiles' src data
    init_tiles_src(cJSON_GetObjectItemCaseSensitive(t_visuals_JSON, "src"));

    // Add sprite sheet meta data
    ss_meta_data->src_x = cJSON_GetObjectItemCaseSensitive(t_visuals_JSON, "srcX")->valueint;
    ss_meta_data->src_y = cJSON_GetObjectItemCaseSensitive(t_visuals_JSON, "srcY")->valueint;
    ss_meta_data->src_width = cJSON_GetObjectItemCaseSensitive(t_visuals_JSON, "srcWidth")->valueint;
    ss_meta_data->src_height = cJSON_GetObjectItemCaseSensitive(t_visuals_JSON, "srcHeight")->valueint;
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
            tile_var_str_short[var],
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
        Tile_Data* tile_data;        // The tile data object representing this tile to be populated
        map_t vars_hashmap;          // Hashmap containing animations for this tile's variations
        int vars_amount;             // Amount of variations this tile has
        tile_var* vars_list;         // List of every variation this tile has

        tile_vars_json = cJSON_GetObjectItemCaseSensitive(tile_type_json, "vars");

        // Initialize tile data
        tile_data = malloc(sizeof(Tile_Data));
        vars_hashmap = hashmap_new();

        // Get amount of variations and initialize list of variations
        vars_amount = cJSON_GetArraySize(tile_vars_json);
        vars_list = malloc(sizeof(Tile_Data) * vars_amount);

        // Loop tile variations
        cJSON_ArrayForEach(tile_var_json, tile_vars_json)
        {
            // Add this variation to the tile's variations list
            tile_var* res;
            hashmap_get(all_vars_hashmap, tile_var_json->string, (void**)(&res));

            *vars_list = *res;
            vars_list++;

            // Add this variation's animation
            hashmap_put(
                vars_hashmap, 
                tile_var_json->string, 
                get_JSON_anim(tile_var_json)
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
            tile_var_str_short[var],
            (void**)(&res)
        );

        free(res);
    }

    hashmap_free(all_vars_hashmap);
}

Animation* access_tile_var_anim(tile_type type, tile_var var)
{
    Animation* result;

    if (hashmap_get(
        tiles_data->src[type]->vars, 
        tile_var_str_short[var], 
        (void**)(&result)) != MAP_OK
    ) {
        return NULL;
    } else {
        return result;
    }
}