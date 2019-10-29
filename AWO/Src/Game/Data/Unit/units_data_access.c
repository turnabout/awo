#include <stdio.h>

#include "Game/Data/Unit/_units_data.h"

Animation** get_unit_animations(Units_Data* units_data, Unit_Type type, Unit_Variation variation)
{
    // If variation doesn't exist on unit type, return data for default variation instead
    Unit_Variation returned_var = (variation < units_data->src[type]->variations_count)
        ? variation
        : UNIT_VAR_FIRST;

    return units_data->src[type]->variations[returned_var];
}

void free_units_data(Units_Data* units_data)
{
    // TODO
}

#ifdef _DEBUG
void print_unit_type_data(Unit_Type_Data* unit_type_data)
{
    printf("Vars amount: %d\n", unit_type_data->variations_count);

    // Loop variations
    for (Unit_Variation var = UNIT_VAR_FIRST; var < unit_type_data->variations_count; var++) {
        printf("\n==========\n%s\n==========\n", unit_var_str[var]);

        // Loop every animation
        for (Unit_Anim anim = UNIT_ANIM_FIRST; anim <= UNIT_ANIM_LAST; anim++) {
            printf("\n%s\n----------", unit_anim_str[anim]);
            print_animation(unit_type_data->variations[var][anim]);
        }
    }
}

void print_units_data(Units_Data* units_data)
{
    for (Unit_Type type = UNIT_TYPE_FIRST; type <= UNIT_TYPE_LAST; type++) {
        printf("\n\n====================\n%s\n====================\n", unit_type_str[type]);
        print_unit_type_data(units_data->src[type]);
    }
}
#endif
