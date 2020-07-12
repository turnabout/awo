#include <stdlib.h>
#include <cjson/cJSON.h>
#include <c_hashmap.h>

#include "Game_Data/Tile_Data/tile_data.h"

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

Tile_Data* create_tile_data(cJSON* tiles_data_JSON, int ss_width, int ss_height)
{
    Tile_Data* tiles_data = malloc(sizeof(Tile_Data));
    map_t variations_list_hashmap = create_variations_list_hashmap();

    // Gather all data from JSON
    Tile_Type tile_type = NEUTRAL_TILE_TYPE_FIRST;

    // Loop tile types
    cJSON* tile_type_JSON;
    cJSON_ArrayForEach(tile_type_JSON, tiles_data_JSON)
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

void free_tile_data(Tile_Data* tiles_data)
{
    if (tiles_data != NULL) {
        for (Tile_Type type = NEUTRAL_TILE_TYPE_FIRST; type < NEUTRAL_TILE_TYPE_COUNT; type++) {
            free_tile_type_data(tiles_data->src[type]);
        }

        free(tiles_data);
    }
}
