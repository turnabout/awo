#pragma once

#include "Utilities/utilities.h"

#define FOREACH_UNIT_VAR(ARMY) \
    ARMY(OS) \
    ARMY(BM) \
    ARMY(GE) \
    ARMY(YC) \
    ARMY(BH) \

typedef enum {FOREACH_UNIT_VAR(GENERATE_ENUM)} Army_Type;
static const char* army_type_str[] = {FOREACH_UNIT_VAR(GENERATE_STRING)};

#define ARMY_TYPE_FIRST OS
#define ARMY_TYPE_LAST  BH
#define ARMY_TYPE_COUNT ARMY_TYPE_LAST + 1
#define ARMY_TYPE_NONE  -1

// Additional neutral army for neutral properties
#define ARMY_TYPE_NEUTRAL     ARMY_TYPE_LAST + 1