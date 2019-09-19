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
    const cJSON* tile_type_json;
    int tile_count = 0;

    // Loop tile types
    cJSON_ArrayForEach(tile_type_json, src_json)
    {
        const cJSON* tile_vars_json = cJSON_GetObjectItemCaseSensitive(tile_type_json, "vars");
        const cJSON* tile_var_json;

        Tile_Data* tile_data = malloc(sizeof(Tile_Data));
        map_t vars_hashmap = hashmap_new();

        // Loop tile variations
        cJSON_ArrayForEach(tile_var_json, tile_vars_json)
        {
            hashmap_put(
                vars_hashmap, 
                tile_var_json->string, 
                get_JSON_anim(tile_var_json)
            );
        }

        tile_data->vars = vars_hashmap;
        tiles_data->src[tile_count++] = tile_data;
    }

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