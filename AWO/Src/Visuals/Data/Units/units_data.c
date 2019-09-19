#include "../JSON/JSON_access.h"
#include "../data_init_internal.h"
#include "units_data_access.h"

#pragma warning( disable : 6011 )

static Units_Data* units_data;
static const cJSON* units_visuals_JSON;

// Initialize units' destination visuals data
void init_units_dst(const cJSON* dst_json);

// Initialize units' source visuals data
void init_units_src(const cJSON* src_json);

// Initialize source visuals data for one unit type
Src_Unit_Type* init_unit_src(const cJSON* unit_type_json);

void init_units_visual_data_structure(const cJSON* u_visuals_JSON)
{
    SS_Meta_Data* ss_meta_data = malloc(sizeof(SS_Meta_Data));
    units_data = malloc(sizeof(Units_Data));

    units_visuals_JSON = u_visuals_JSON;

    // Add src/dst data
    init_units_src(cJSON_GetObjectItemCaseSensitive(u_visuals_JSON, "src"));
    init_units_dst(cJSON_GetObjectItemCaseSensitive(u_visuals_JSON, "dst"));

    // Add sprite sheet metadata
    ss_meta_data->src_x = cJSON_GetObjectItemCaseSensitive(u_visuals_JSON, "srcX")->valueint;
    ss_meta_data->src_y = cJSON_GetObjectItemCaseSensitive(u_visuals_JSON, "srcY")->valueint;
    ss_meta_data->src_width = cJSON_GetObjectItemCaseSensitive(u_visuals_JSON, "srcWidth")->valueint;
    ss_meta_data->src_height = cJSON_GetObjectItemCaseSensitive(u_visuals_JSON, "srcHeight")->valueint;
    ss_meta_data->dst_width = cJSON_GetObjectItemCaseSensitive(u_visuals_JSON, "dstWidth")->valueint;
    ss_meta_data->dst_height = cJSON_GetObjectItemCaseSensitive(u_visuals_JSON, "dstHeight")->valueint;

    units_data->ss_meta_data = ss_meta_data;
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

    // Initialize Unit Type memory and vars_count
    type = malloc(sizeof(Src_Unit_Type));
    type->vars_count = cJSON_GetArraySize(unit_type_json);

    // Initialize Variations' memory
    vars = malloc(sizeof(Animation**) * type->vars_count);

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

    vars -= type->vars_count;
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
        enum unit_type current_anim = UNIT_ANIM_FIRST;

        cJSON_ArrayForEach(unit_anim_json, unit_type_json)
        {
            units_data->dst[current_type][current_anim++] = get_JSON_anim(unit_anim_json);
        }

        current_type++;
    }
}

Unit_Palette* get_unit_palette(unit_var u_var)
{
    const cJSON* base = cJSON_GetObjectItemCaseSensitive(units_visuals_JSON, "basePalette");
    const cJSON* unit_palettes = cJSON_GetObjectItemCaseSensitive(units_visuals_JSON, "palettes");

    // Get cJSON item for the given palette
    const cJSON* unit_palette = cJSON_GetArrayItem(unit_palettes, u_var);

    if (cJSON_GetArraySize(unit_palette) < 1) {
        return NULL;
    }

    // Build up the result
    Unit_Palette* result = malloc(sizeof(Unit_Palette));

    result->flip = cJSON_GetObjectItemCaseSensitive(unit_palette, "flip")->valueint;
    result->palette = generate_palette_tree(
        base, 
        cJSON_GetObjectItemCaseSensitive(unit_palette, "palette")
    );

    return result;
}

void free_unit_palette(Unit_Palette* u_palette)
{
    free_palette_tree(u_palette->palette);
    free(u_palette);
}

Animation** access_unit_src_anims(unit_type type, unit_var var)
{
    // If variation doesn't exist on unit type, return default instead
    unit_var returned_var = (var < units_data->src[type]->vars_count)
        ? var
        : UNIT_VAR_FIRST;

    return units_data->src[type]->vars[returned_var];
}

Animation** access_unit_dst_anims(unit_type type)
{
    return units_data->dst[type];
}

SS_Meta_Data* access_units_ss_meta_data()
{
    return units_data->ss_meta_data;
}
