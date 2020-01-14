#include <stdio.h>
#include <stdlib.h>

#include "Game_Data/Unit/_units_data.h"

Animation* get_unit_animation(
    Units_Data* units_data,
    Unit_Type type,
    Army_Type variation,
    Unit_Anim animation
)
{
    // If variation doesn't exist on unit type, return data for default variation instead
    Army_Type returned_var = (variation < units_data->src[type]->variations_count)
        ? variation
        : ARMY_TYPE_FIRST;

    return units_data->src[type]->variations[returned_var]->animations[animation];
}

void free_unit_type_data(Unit_Type_Data* type_data)
{
    if (type_data== NULL) {
        return;
    }

    if (type_data->variations == NULL) {
        free(type_data);
        return;
    }

    // Free all variations' data
    for (int i = 0; i < type_data->variations_count; i++) {
        if (type_data->variations[i] == NULL) {
            continue;
        }

        for (Unit_Anim anim = UNIT_ANIM_FIRST; anim < UNIT_ANIM_COUNT; anim++) {
            free_animation(type_data->variations[i]->animations[anim]);
        }

        free(type_data->variations[i]);
    }

    free(type_data->variations);
    free(type_data);
}

void free_units_data(Units_Data* units_data)
{
    if (units_data == NULL) {
        return;
    }

    // Free all types' data
    for (int i = 0; i < UNIT_TYPE_COUNT; i++) {
        free_unit_type_data(units_data->src[i]);
    }

    free(units_data);
}

#ifdef _DEBUG
void print_unit_type_data(Unit_Type_Data* unit_type_data)
{
    /*
    printf("Vars amount: %d\n", unit_type_data->variations_count);

    // Loop variations
    for (Army_Type var = ARMY_TYPE_FIRST; var < unit_type_data->variations_count; var++) {
        printf("\n==========\n%s\n==========\n", army_type_str[var]);

        // Loop every animation
        for (Unit_Anim anim = UNIT_ANIM_FIRST; anim <= UNIT_ANIM_LAST; anim++) {
            printf("\n%s\n----------", unit_anim_str[anim]);
            print_animation(unit_type_data->variations[var][anim]);
        }
    }
    */
}

void print_units_data(Units_Data* units_data)
{
    /*
    for (Unit_Type type = UNIT_TYPE_FIRST; type <= UNIT_TYPE_LAST; type++) {
        printf("\n\n====================\n%s\n====================\n", unit_type_str[type]);
        print_unit_type_data(units_data->src[type]);
    }
    */
}
#endif
