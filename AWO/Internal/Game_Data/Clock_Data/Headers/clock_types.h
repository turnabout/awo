#pragma once

#include "Utilities/utilities.h"

// Every possible animation clock's index.
#define FOREACH_ANIMATION_CLOCK_INDEX(CLOCK) \
    CLOCK(Sea_Clock_0) \
    CLOCK(Sea_Clock_1) \
    CLOCK(Sea_Clock_2) \
    CLOCK(River_Clock) \
    CLOCK(Smoke_Clock) \
    CLOCK(Property_Lights_Clock) \

#define No_Clock -1

typedef enum {FOREACH_ANIMATION_CLOCK_INDEX(GENERATE_ENUM)} Clock_Index;
static const char* clock_str[] = {FOREACH_ANIMATION_CLOCK_INDEX(GENERATE_STRING)};

#define ANIMATION_CLOCK_FIRST Sea_Clock_0
#define ANIMATION_CLOCK_LAST  Property_Lights_Clock
#define ANIMATION_CLOCK_COUNT ANIMATION_CLOCK_LAST + 1