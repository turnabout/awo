#include <stdlib.h>
#include <cJSON.h>
#include <c_hashmap.h>
#include <cglm/cglm.h>

#include "Game/Data/Tile/_tiles_data.h"

// Creates hashmap containing all variations, using short strings as keys.
// This is so we can get tile variations corresponding to short strings fetched from the JSON data.
map_t create_variations_list_hashmap()
{
    map_t variations_list_hashmap = hashmap_new();

    for (Tile_Variation var = TILE_VAR_FIRST; var <= TILE_VAR_LAST; var++) {

        // Have to malloc the tile variation, because hashmap_put requires a value to be a pointer
        Tile_Variation* tile_variation = malloc(sizeof(Tile_Variation));
        *tile_variation = var;

        hashmap_put(variations_list_hashmap, (char*)tile_var_str_short[var], tile_variation);
    }

    return variations_list_hashmap;
}

// Frees the given variations list hashmap and all of its contents.
void free_variations_list_hashmap(map_t variations_list_hashmap)
{
    for (Tile_Variation var = TILE_VAR_FIRST; var <= TILE_VAR_LAST; var++) {
        Tile_Variation* res;

        hashmap_get(
            variations_list_hashmap,
            (char*)tile_var_str_short[var],
            (void**)(&res)
        );

        free(res);
    }

    hashmap_free(variations_list_hashmap);
}

Neutral_Tiles_Data* create_neutral_tiles_data(cJSON* tiles_data_JSON, int ss_width, int ss_height)
{
    Neutral_Tiles_Data* tiles_data = malloc(sizeof(Neutral_Tiles_Data));
    map_t variations_list_hashmap = create_variations_list_hashmap();

    // Gather all data from JSON
    Tile_Type tile_type = NEUTRAL_TILE_TYPE_FIRST;

    // Loop tile types
    cJSON* src_JSON = cJSON_GetObjectItemCaseSensitive(tiles_data_JSON, "src");
    cJSON* tile_type_JSON;
    cJSON_ArrayForEach(tile_type_JSON, src_JSON)
    {
         tiles_data->src[tile_type++] = create_tile_type_data(
            tile_type_JSON, 
            variations_list_hashmap,
             ss_width,
             ss_height
        );
    }

    // Free the temporary variations hashmap
    free_variations_list_hashmap(variations_list_hashmap);

    return tiles_data;
}
