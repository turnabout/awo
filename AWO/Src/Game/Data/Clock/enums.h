#pragma once

#include "Utilities/macros.h"

// Every possible animation clock's index.
#define FOREACH_ANIMATION_CLOCK_INDEX(INDEX) \
    INDEX(Sea_Clock) \
    INDEX(River_Clock) \
    INDEX(Base_Smoke_Clock) \
    INDEX(Property_Lights_Clock) \
    INDEX(Units_Clock) \

#define No_Clock -1

typedef enum {FOREACH_ANIMATION_CLOCK_INDEX(GENERATE_ENUM)} Animation_Clock_Index;
static const char* animation_clock_str[] = {FOREACH_ANIMATION_CLOCK_INDEX(GENERATE_STRING)};

#define ANIMATION_CLOCK_FIRST Sea_Clock
#define ANIMATION_CLOCK_LAST  Units_Clock
#define ANIMATION_CLOCK_COUNT ANIMATION_CLOCK_LAST + 1

// Every possible animation sub clock's index.
typedef enum Animation_Sub_Clock_Index {
    // Sea Clock
    Pyramid1 = 0,
    Pyramid2 = 1,
    Ten      = 2,

    // River Clock
    Eight    = 0,

    // Base Smoke Clock
    Base_Smoke_Sub_Clock = 0,

    // Property lights clock
    Property_Lights_Sub_Clock = 0,

    // Units Clock
    Pyramid_3_Frames = 0,

    // None
    No_Sub_Clock = -1,
} Animation_Sub_Clock_Index;

#define MAX_ANIMATION_SUB_CLOCK_COUNT 3
#define ANIMATION_SUB_CLOCK_COUNT 15