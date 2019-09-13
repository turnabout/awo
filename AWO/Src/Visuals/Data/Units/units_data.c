#include <SDL.h>
#include <stdio.h>

#include "units_enums.h"
#include "../JSON/JSON_access.h"
#include "../data_init_internal.h"
#include "../../data_access.h"

#pragma warning( disable : 6011 )

static Units_Data* units_data;

// Get all units' visual destination data
void init_units_dst(const cJSON* dst_json);

// Get all units' visual source data
void init_units_src(const cJSON* src_json);

// Get a Unit type's visual source data
Src_Unit_Type* init_unit_src(const cJSON* unit_type_json);

void init_units_visual_data_structure(const cJSON* units_visuals_JSON)
{
    units_data = malloc(sizeof(Units_Data));

    // Add src/dst data
    init_units_src(cJSON_GetObjectItemCaseSensitive(units_visuals_JSON, "src"));
    init_units_dst(cJSON_GetObjectItemCaseSensitive(units_visuals_JSON, "dst"));

    // Add sprite sheet metadata
    units_data->src_x      = cJSON_GetObjectItemCaseSensitive(units_visuals_JSON, "srcX")->valueint;
    units_data->src_y      = cJSON_GetObjectItemCaseSensitive(units_visuals_JSON, "srcY")->valueint;
    units_data->src_width  = cJSON_GetObjectItemCaseSensitive(units_visuals_JSON, "srcWidth")->valueint;
    units_data->src_height = cJSON_GetObjectItemCaseSensitive(units_visuals_JSON, "srcHeight")->valueint;
    units_data->dst_width  = cJSON_GetObjectItemCaseSensitive(units_visuals_JSON, "dstWidth")->valueint;
    units_data->dst_height = cJSON_GetObjectItemCaseSensitive(units_visuals_JSON, "dstHeight")->valueint;

    // Add other data (TODO)
}

void init_units_src(const cJSON* src_json)
{
    const cJSON* unit_type_json;
    enum unit_type current_type = UNIT_TYPE_FIRST;

    cJSON_ArrayForEach(unit_type_json, src_json)
    {
        units_data->src[current_type++] = init_unit_src(unit_type_json);
    }
}

Src_Unit_Type* init_unit_src(const cJSON* unit_type_json)
{
    Src_Unit_Type* type;        // The Unit Type struct returned
    Animation*** vars;          // All Variations' data
    const cJSON* unit_var_json; // cJSON data for current Variation

    // Initialize Unit Type memory and count
    type = malloc(sizeof(Src_Unit_Type));
    type->count = cJSON_GetArraySize(unit_type_json);

    // Initialize Variations' memory
    vars = malloc(sizeof(Animation**) * type->count);

    // Loop Variations cJSON
    cJSON_ArrayForEach(unit_var_json, unit_type_json)
    {
        const cJSON* unit_anim_json; // cJSON data for current Animation
        Animation** anims;           // All Animations data for this Variation

        // Initialize Animations' memory
        anims = malloc(sizeof(Animation*) * UNIT_ANIM_AMOUNT); 

        // Loop Animations cJSON
        cJSON_ArrayForEach(unit_anim_json, unit_var_json)
        {
            *(anims++) = get_JSON_anim(unit_anim_json); // Set next animation
        };

        // Reset anims pointer to the first variation, then record
        anims -= UNIT_ANIM_AMOUNT;

        *(vars++) = anims;
    }

    vars -= type->count;
    type->vars = vars;

    return type;
}

void init_units_dst(const cJSON* dst_json)
{
    const cJSON* unit_type_json;
    enum unit_type current_type = UNIT_TYPE_FIRST;

    cJSON_ArrayForEach(unit_type_json, dst_json)
    {
        const cJSON* unit_anim_json;
        enum unit_type current_anim = UNIT_ANIM_FULL_FIRST;

        cJSON_ArrayForEach(unit_anim_json, unit_type_json)
        {
            // printf("%s %s\n", unit_type_str[current_type], unit_anim_str[current_anim]);
            units_data->dst[current_type][current_anim++] = get_JSON_anim(unit_anim_json);
        }

        current_type++;
    }
}

Animation* access_unit_src_animation(enum unit_type type, enum unit_var var, enum unit_anim anim)
{
    return units_data->src[type]->vars[var][anim];
}

Animation* access_unit_dst_animation(enum unit_type type, enum unit_anim anim)
{
    return units_data->dst[type][anim];
}

Units_Data* access_units_data()
{
    return units_data;
}
