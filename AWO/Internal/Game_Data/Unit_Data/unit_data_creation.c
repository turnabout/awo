#include <stdlib.h>

#include "Game_Data/Unit_Data/_unit_data.h"

Unit_Type_Data* create_unit_type_data(cJSON* unit_type_JSON, int ss_width, int ss_height)
{
    Unit_Type_Data* type_data = malloc(sizeof(Unit_Type_Data));

    if (type_data == NULL) {
        return NULL;
    }

    // Add this unit type's variations' data
    // Get/confirm JSON valid
    cJSON* vars_JSON = cJSON_GetObjectItem(unit_type_JSON, "vars");

    if (cJSON_IsInvalid(vars_JSON)) {
        free_unit_type_data(type_data);
        return NULL;
    }

    // Get/confirm variations count
    type_data->variations_count = cJSON_GetArraySize(vars_JSON);

    if (type_data->variations_count < 1 || type_data->variations_count > ARMY_TYPE_COUNT) {
        free_unit_type_data(type_data);
        return NULL;
    }

    // Allocate space for this unit's variations
    type_data->variations = malloc(sizeof(Unit_Animation_Data*) * type_data->variations_count);

    // Loop each variation
    for (int i = 0; i < type_data->variations_count; i++) {
        cJSON* var_JSON = cJSON_GetArrayItem(vars_JSON, i);

        if (cJSON_IsInvalid(var_JSON)) {
            free_unit_type_data(type_data);
            return NULL;
        }

        // Add the animation data for this variation
        type_data->variations[i] = malloc(sizeof(Unit_Animation_Data));

        for (Unit_Anim anim = UNIT_ANIM_FIRST; anim < UNIT_ANIM_COUNT; anim++) {
            cJSON* anim_JSON = cJSON_GetArrayItem(var_JSON, anim);

            if (cJSON_IsInvalid(anim_JSON)) {
                free_unit_type_data(type_data);
                return NULL;
            }

            type_data->variations[i]->animations[anim] = create_animation(
                anim_JSON,
                ss_width,
                ss_height
            );
        }
    }

    return type_data;
}

Units_Data* create_units_data(cJSON* units_data_JSON, int ss_width, int ss_height)
{
    Units_Data* units_data = malloc(sizeof(Units_Data));

    if (units_data == NULL) {
        return NULL;
    }

    // Confirm JSON count of unit types' data
    if (cJSON_GetArraySize(units_data_JSON) != UNIT_TYPE_COUNT) {
        /*
        printe(
            "create_units_data: JSON unit types count incorrect: expected '%d', got '%d'",
            UNIT_TYPE_COUNT,
            cJSON_GetArraySize(units_data_JSON)
        );
        */
        return NULL;
    }

    // Create all unit types' data
    for (Unit_Type type = UNIT_TYPE_FIRST; type < UNIT_TYPE_COUNT; type++) {
        units_data->src[type] = create_unit_type_data(
            cJSON_GetArrayItem(units_data_JSON, type),
            ss_width, 
            ss_height
        );

        if (units_data->src[type] == NULL) {
            free_units_data(units_data);
            return NULL;
        }
    }

    return units_data;
}
