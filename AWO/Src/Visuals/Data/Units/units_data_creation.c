#include "_units_data_internal.h"

Units_Data* UD_create_from_JSON(const cJSON* ud_JSON)
{
    Units_Data* ud = malloc(sizeof(Units_Data));

    // Store metadata & JSON for palettes
    ud->ss_metadata = SS_Meta_create_from_JSON(ud_JSON);
    ud->JSON = ud_JSON;

    // Store source and destination data
    get_units_src_data(ud, cJSON_GetObjectItemCaseSensitive(ud_JSON, "src"));
    get_units_dst_data(ud, cJSON_GetObjectItemCaseSensitive(ud_JSON, "dst"));

    return ud;
}

void get_units_src_data(Units_Data* ud, const cJSON* src_json)
{
    const cJSON* unit_type_json;
    enum unit_type current_type = UNIT_TYPE_FIRST;

    cJSON_ArrayForEach(unit_type_json, src_json)
    {
        ud->src[current_type++] = get_unit_src_data(unit_type_json);
    }
}

void get_units_dst_data(Units_Data* ud, const cJSON* dst_json)
{
    const cJSON* unit_type_json;
    enum unit_type current_type = UNIT_TYPE_FIRST;

    cJSON_ArrayForEach(unit_type_json, dst_json)
    {
        const cJSON* unit_anim_json;
        enum unit_type current_anim = UNIT_ANIM_FIRST;

        cJSON_ArrayForEach(unit_anim_json, unit_type_json)
        {
            ud->dst[current_type][current_anim++] = anim_create_from_JSON(unit_anim_json);
        }

        current_type++;
    }
}

Src_Unit_Type* get_unit_src_data(const cJSON* unit_type_json)
{
    Src_Unit_Type* type;        // The unit type data struct returned
    Animation*** vars;     // Data for this unit type's variations
    const cJSON* unit_var_json; // cJSON data for current variation

    // Initialize unit type and its variation count
    type = malloc(sizeof(struct Src_Unit_Type));
    type->vars_count = cJSON_GetArraySize(unit_type_json);

    // Initialize Variations' memory
    vars = malloc(sizeof(Animation**) * type->vars_count);

    // Loop variations
    cJSON_ArrayForEach(unit_var_json, unit_type_json)
    {
        const cJSON* unit_anim_json; // cJSON data for current Animation
        Animation** anims;      // All Animations data for this Variation

        // Initialize Animations' memory
        anims = malloc(sizeof(Animation*) * UNIT_ANIM_COUNT); 

        // Loop animations
        cJSON_ArrayForEach(unit_anim_json, unit_var_json)
        {
            *(anims++) = anim_create_from_JSON(unit_anim_json);
        };

        // Reset anims pointer to the first variation, then save accumulated data
        anims -= UNIT_ANIM_COUNT;
        *(vars++) = anims;
    }

    vars -= type->vars_count;
    type->vars = vars;

    return type;
}
