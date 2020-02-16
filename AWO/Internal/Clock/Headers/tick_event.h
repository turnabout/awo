#pragma once

#include "Include/types.h"
#include "Game_Data/Clock_Data/Headers/clock_types.h"

// Event generated whenever an animation sub-clock ticks.
typedef struct Tick_Event {

    // Index of the clock that ticked.
    Clock_Index clock_index;

    // Value held by this tick event.
    Uint8 value;

} Tick_Event;

// List of tick events.
typedef struct Tick_Events_List {

    // List of ticks.
    Tick_Event ticks[ANIMATION_CLOCK_COUNT];

    // Amount of ticks.
    Uint8 ticks_count;

} Tick_Events_List;