#pragma once

#include "Utilities/macros.h"

// Every possible animation clock's index.
#define FOREACH_ANIMATION_CLOCK_INDEX(INDEX) \
    INDEX(Sea_Clock_0) \
    INDEX(Sea_Clock_1) \
    INDEX(Sea_Clock_2) \

/*
    INDEX(River_Clock) \
    INDEX(Base_Smoke_Clock) \
    INDEX(Property_Lights_Clock) \
    INDEX(Units_Clock) \
    */

#define No_Clock -1

typedef enum {FOREACH_ANIMATION_CLOCK_INDEX(GENERATE_ENUM)} Animation_Clock_Index;
static const char* animation_clock_str[] = {FOREACH_ANIMATION_CLOCK_INDEX(GENERATE_STRING)};

#define ANIMATION_CLOCK_FIRST Sea_Clock_0
#define ANIMATION_CLOCK_LAST  Sea_Clock_2
#define ANIMATION_CLOCK_COUNT ANIMATION_CLOCK_LAST + 1