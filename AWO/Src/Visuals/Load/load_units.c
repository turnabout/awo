#include <SDL.h>
#include <stdio.h>

#include "cJSON/cJSON.h"
#include "load_structure.h"
#include "../visuals_structure.h"
#include "../units.h"

#pragma warning( disable : 6011 )

// Get all units' visual source data
void get_units_src(Units_Data* units_data, const cJSON* src_json);

// Get a Unit type's visual source data
Src_Unit_Type* get_unit_type_src(const cJSON* unit_type_json);

void load_units_visual_data_structure(const cJSON* units_visuals_JSON)
{
    Units_Data units_data;
    get_units_src(&units_data, cJSON_GetObjectItemCaseSensitive(units_visuals_JSON, "src"));

    print_anim_contents(units_data.src[Infantry]->vars[BM][Idle]);
}

void get_units_src(Units_Data* units_data, const cJSON* src_json)
{
    // Loop types
    const cJSON* unit_type_json = NULL;
    enum unit_type current_type = UNIT_TYPE_FIRST;

    cJSON_ArrayForEach(unit_type_json, src_json)
    {
        units_data->src[current_type++] = get_unit_type_src(unit_type_json);
    }
}

Src_Unit_Type* get_unit_type_src(const cJSON* unit_type_json)
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
            *(anims++) = get_anim(unit_anim_json); // Set next animation
        };

        // Reset anims pointer to the first variation, then record
        anims -= UNIT_ANIM_AMOUNT;

        *(vars++) = anims;
    }

    vars -= type->count;
    type->vars = vars;

    return type;
}