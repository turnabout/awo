#pragma once

#include "cJSON.h"
#include "Visuals/Data/Sprite_Sheet_Metadata/ss_metadata.h"
#include "Visuals/Data/Animation/animation.h"
#include "Visuals/Data/Palette/palette_tree.h"

#include "units_data.h"

typedef struct Src_Unit_Type
{
    int vars_count;    // Amount of variations used by this unit type
    Animation*** vars; // Animation data for every variation of this unit type
} Src_Unit_Type;

struct Units_Data
{
    Src_Unit_Type* src[UNIT_TYPE_COUNT];
    Animation* dst[UNIT_TYPE_COUNT][UNIT_ANIM_COUNT];
    SS_Metadata* ss_metadata;
    const cJSON* JSON;
};

void get_units_src_data(Units_Data* ud, const cJSON* src_json);
void get_units_dst_data(Units_Data* ud, const cJSON* dst_json);
Src_Unit_Type* get_unit_src_data(const cJSON* unit_type_json);

#ifdef _DEBUG
void print_src_unit_type(Src_Unit_Type* src_unit_type);
#endif
