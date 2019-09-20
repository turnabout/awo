#pragma once

#include "cJSON.h"
#include "units_enums.h"

#include "../Sprite_Sheet_Metadata/ss_metadata.h"
#include "../Animation/animation_data.h"
#include "../Palette/palette_tree.h"

typedef struct Units_Data Units_Data;
typedef struct Src_Unit_Type Src_Unit_Type;

struct Src_Unit_Type
{
    int vars_count;         // Amount of variations used by this unit type
    Animation_Data*** vars; // Animation data for every variation of this unit type
};

struct Units_Data
{
    Src_Unit_Type* src[UNIT_TYPE_AMOUNT];
    Animation_Data* dst[UNIT_TYPE_AMOUNT][UNIT_ANIM_AMOUNT];
    SS_Metadata* ss_metadata;
    const cJSON* palettes_JSON;
};

void get_units_src_data(Units_Data* ud, const cJSON* src_json);
void get_units_dst_data(Units_Data* ud, const cJSON* dst_json);
Src_Unit_Type* get_unit_src_data(const cJSON* unit_type_json);

#ifdef _DEBUG
void print_src_unit_type(Src_Unit_Type* src_unit_type);
#endif
