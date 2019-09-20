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

void UD_print(Units_Data* ud)
{
}

void UD_free(Units_Data* ud)
{
}
