#pragma once

#include "Include/macros.h"

#define FOREACH_UNIT_ANIM(UNITANIM) \
    UNITANIM(Unit_Idle) \
    UNITANIM(Unit_Right) \
    UNITANIM(Unit_Up) \
    UNITANIM(Unit_Down) \

typedef enum {FOREACH_UNIT_ANIM(GENERATE_ENUM)} Unit_Anim;
static const char* unit_anim_str[] = {FOREACH_UNIT_ANIM(GENERATE_STRING)};

#define UNIT_ANIM_FIRST Unit_Idle
#define UNIT_ANIM_LAST Unit_Down
#define UNIT_ANIM_COUNT UNIT_ANIM_LAST + 1
