#ifdef _DEBUG
#include <stdio.h>
#endif

#include "units_data.h"
#include "_units_data_internal.h"

// TODO: Instead, return a Palette_Tree* and store the 'flip' value in an additional pointer arg
struct Palette_Tree* get_unit_palette(unit_var u_var, int* flip)
{
    // TODO: Can't rely on static JSON anymore, use given Units_Data* instead
    /*
    const cJSON* base = cJSON_GetObjectItemCaseSensitive(units_visuals_JSON, "basePalette");
    const cJSON* unit_palettes = cJSON_GetObjectItemCaseSensitive(units_visuals_JSON, "palettes");

    // Get cJSON item for the given palette
    const cJSON* unit_palette = cJSON_GetArrayItem(unit_palettes, u_var);

    if (cJSON_GetArraySize(unit_palette) < 1) {
        return NULL;
    }

    // Build up the result
    struct Unit_Palette* result = malloc(sizeof(struct Unit_Palette));

    result->flip = cJSON_GetObjectItemCaseSensitive(unit_palette, "flip")->valueint;
    result->palette = PT_create_from_JSON(
        base, 
        cJSON_GetObjectItemCaseSensitive(unit_palette, "palette")
    );

    return result;
    */
    return NULL;
}

Animation_Data** access_unit_src_anims(unit_type type, unit_var var)
{
    // If variation doesn't exist on unit type, return default instead
    /*
    unit_var returned_var; = (var < units_data->src[type]->vars_count)
        ? var
        : UNIT_VAR_FIRST;

    return units_data->src[type]->vars[returned_var];
*/
    return NULL;
}

Animation_Data** access_unit_dst_anims(unit_type type)
{
    // return units_data->dst[type];
    return NULL;
}

SS_Metadata* access_units_ss_meta_data()
{
    // return units_data->ss_meta_data;
    return NULL;
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
