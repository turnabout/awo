#pragma once

#include "types.h"
#include "Game/Clock/Animation_Clock/enums.h"

// Event generated whenever an animation sub-clock ticks.
typedef struct Tick_Event {

    // Index of the animation clock that ticked.
    Animation_Clock_Index clock_index;

    // Index of the animation sub-clock that ticked.
    Animation_Sub_Clock_Index sub_clock_index;

    // New animation index of entities that process this tick event.
    Uint8 frame_index;

} Tick_Event;

// List of tick events.
typedef struct Tick_Event_List {

    // List of ticks.
    Tick_Event ticks[ANIMATION_SUB_CLOCK_COUNT];

    // Amount of ticks.
    Uint8 ticks_count;

} Tick_Event_List;