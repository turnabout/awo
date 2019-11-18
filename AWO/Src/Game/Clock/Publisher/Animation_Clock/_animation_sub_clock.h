#pragma once

#include <cJSON.h>

#include "Game/Clock/Tick_Event/tick_event.h"

typedef struct Animation_Sub_Clock {

    // Animation clock index this sub-clock belongs to.
    Animation_Clock_Index clock_index;

    // Index of this sub-clock.
    Animation_Sub_Clock_Index sub_clock_index;

    // Frame value that was stored the last time this sub clock ticked.
    Uint8 previous_tick_value;

    // Array of every possible game tick.
    Uint8* ticks_array;

} Animation_Sub_Clock;

// Creates an animation sub clock using the given JSON data describing it.
Animation_Sub_Clock* create_animation_sub_clock(
    const cJSON* JSON,
    Animation_Clock_Index animation_clock_index,
    Animation_Sub_Clock_Index sub_clock_index
);

// Updates the current tick of a sub clock depending on its animation clock's current tick
void tick_animation_sub_clock(
    Animation_Sub_Clock* asc, 
    int ac_current_tick,
    Tick_Events_List* event_list
);

// Frees an animation sub clock
void free_animation_sub_clock(Animation_Sub_Clock* asc);