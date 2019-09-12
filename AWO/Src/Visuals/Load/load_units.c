#include <SDL.h>
#include <stdio.h>

#include "cJSON/cJSON.h"
#include "load_structure.h"
#include "../visuals_structure.h"
#include "../units.h"

#pragma warning( disable : 6011 )

// Process animation's source data
void process_src(Units_Data* units_data, const cJSON* src_json);

void load_units_visual_data_structure(const cJSON* units_visuals_JSON)
{
    Units_Data units_data;
    process_src(&units_data, cJSON_GetObjectItemCaseSensitive(units_visuals_JSON, "src"));

    print_anim_contents(units_data.src[Infantry][OS][Idle]);
}

void process_src(Units_Data* units_data, const cJSON* src_json)
{
    // Loop types
    const cJSON* unit_type_json = NULL;
    enum unit_type current_type = UNIT_TYPE_FIRST;

    cJSON_ArrayForEach(unit_type_json, src_json)
    {
        // Loop variations
        const cJSON* unit_var_json = NULL;
        enum unit_var current_var = UNIT_VAR_FIRST;

        cJSON_ArrayForEach(unit_var_json, unit_type_json)
        {
            // Loop animations
            const cJSON* unit_anim_json = NULL;
            enum unit_anim current_anim = UNIT_ANIM_FIRST;

            cJSON_ArrayForEach(unit_anim_json, unit_var_json)
            {
                // Store every animation
                units_data->src[current_type][current_var][current_anim++] = get_anim(unit_anim_json);
            }

            current_var++;
        }

        current_type++;
    }
}
