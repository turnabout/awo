#ifdef _DEBUG
#include <stdio.h>
#endif

#include "units_data.h"
#include "_units_data_internal.h"

// TODO: Instead, return a Palette_Tree* and store the 'flip' value in an additional pointer arg
Palette_Tree* UD_get_palette(Units_Data* ud, unit_var u_var, int* flip)
{
    // TODO: Can't rely on static JSON anymore, use given Units_Data* instead
    const cJSON* base = cJSON_GetObjectItemCaseSensitive(ud->JSON, "basePalette");
    const cJSON* unit_palettes = cJSON_GetObjectItemCaseSensitive(ud->JSON, "palettes");

    // Get cJSON item for the given palette
    const cJSON* unit_palette = cJSON_GetArrayItem(unit_palettes, u_var);

    if (cJSON_GetArraySize(unit_palette) < 1) {
        return NULL;
    }

    // Get the result
    *flip = cJSON_GetObjectItemCaseSensitive(unit_palette, "flip")->valueint;

    return PT_create_from_JSON(
        base, 
        cJSON_GetObjectItemCaseSensitive(unit_palette, "palette")
    );
}

Animation** UD_get_src_anims(Units_Data* ud, unit_type u_type, unit_var u_var)
{
    // If variation doesn't exist on unit type, return data for default variation instead
    unit_var returned_var = (u_var < ud->src[u_type]->vars_count)
        ? u_var
        : UNIT_VAR_FIRST;

    return ud->src[u_type]->vars[returned_var];
}

Animation** UD_get_dst_anims(Units_Data* ud, unit_type u_type)
{
    return ud->dst[u_type];
}

SS_Metadata* UD_get_ss_metadata(Units_Data* ud)
{
    return ud->ss_metadata;
}

#ifdef _DEBUG
void print_src_unit_type(Src_Unit_Type* src_u_type)
{
    printf("Vars amount: %d\n", src_u_type->vars_count);

    // Loop variations
    for (unit_var u_var = UNIT_VAR_FIRST; u_var < src_u_type->vars_count; u_var++) {
        printf("\n==========\n%s\n==========\n", unit_var_str[u_var]);

        // Loop every animation
        for (unit_anim anim = UNIT_ANIM_FIRST; anim <= UNIT_ANIM_LAST; anim++) {
            printf("\n%s\n----------", unit_anim_str[anim]);
            AD_print(src_u_type->vars[u_var][anim]);
        }
    }
}

void UD_print(Units_Data* ud, UD_print_arg which)
{
    switch (which) {

    // Print source data
    case UD_SRC:
        printf("Units source data\n");
        for (unit_type type = UNIT_TYPE_FIRST; type <= UNIT_TYPE_LAST; type++) {
            printf("\n\n====================\n%s\n====================\n", unit_type_str[type]);
            print_src_unit_type(ud->src[type]);
        }
        break;

    // Print destination data
    case UD_DST:
        printf("Units destination data\n");
        for (unit_type type = UNIT_TYPE_FIRST; type <= UNIT_TYPE_LAST; type++) {
            printf("\n==========\n%s\n==========\n", unit_type_str[type]);

            for (unit_anim anim = UNIT_ANIM_FIRST; anim <= UNIT_ANIM_LAST; anim++) {
                printf("\n%s\n----------", unit_anim_str[anim]);
                AD_print(ud->dst[type][anim]);
            }
        }
        break;
    }
}
#endif

void UD_free(Units_Data* ud)
{
    // TODO
}
