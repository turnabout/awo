#pragma once

#include "Utilities/macros.h"

// UI element enum
#define FOREACH_UI_ELEMENT(ELEMENT) \
    ELEMENT(TileCursor) \
    ELEMENT(TileCursorX) \
    ELEMENT(StarSm) \
    ELEMENT(StarLg) \

typedef enum {FOREACH_UI_ELEMENT(GENERATE_ENUM)} UI_Element_Type;
static const char* UI_element_str[] = {FOREACH_UI_ELEMENT(GENERATE_STRING)};

#define UI_ELEMENT_FIRST TileCursor
#define UI_ELEMENT_LAST  StarLg
#define UI_ELEMENT_COUNT UI_ELEMENT_LAST + 1
