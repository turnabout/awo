#include <stdlib.h>

#include "Game/Data/Unit/_units_data.h"

Unit_Type_Data* create_unit_src_data(const cJSON* unit_type_JSON, int ss_width, int ss_height)
{
    Unit_Type_Data* type;        // The unit type data struct returned
    Animation*** variations;    // Data for this unit type's variations
    const cJSON* unit_var_JSON; // cJSON data for current variation

    // Initialize unit type and its variation count
    type = malloc(sizeof(struct Unit_Type_Data));
    type->variations_count = cJSON_GetArraySize(unit_type_JSON);

    // Initialize Variations' memory
    variations = malloc(sizeof(Animation**) * type->variations_count);

    // Loop variations
    cJSON_ArrayForEach(unit_var_JSON, unit_type_JSON)
    {
        Animation** animations;

        // Initialize Animations' memory
        animations = malloc(sizeof(Animation*) * UNIT_ANIM_COUNT); 

        // Loop animations
        const cJSON* unit_anim_JSON;
        cJSON_ArrayForEach(unit_anim_JSON, unit_var_JSON)
        {
            *(animations++) = create_animation(unit_anim_JSON, ss_width, ss_height);
        };

        // Reset animations pointer to the first variation, then save accumulated data
        animations -= UNIT_ANIM_COUNT;
        *(variations++) = animations;
    }

    variations -= type->variations_count;
    type->variations = variations;

    return type;
}

Units_Data* create_units_data(cJSON* units_data_JSON, int ss_width, int ss_height)
{
    Units_Data* units_data = malloc(sizeof(Units_Data));

    const cJSON* unit_type_JSON;
    Unit_Type current_type = UNIT_TYPE_FIRST;

    cJSON_ArrayForEach(unit_type_JSON, units_data_JSON)
    {
        units_data->src[current_type++] = create_unit_src_data(
            unit_type_JSON, 
            ss_width, 
            ss_height
        );
    }

    return units_data;
}
