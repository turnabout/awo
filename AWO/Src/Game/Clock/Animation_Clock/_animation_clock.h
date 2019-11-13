#pragma once

#include <cJSON.h>

#include "Game/Clock/Animation_Clock/enums.h"
#include "Game/Clock/Animation_Clock/tick_event.h"
#include "Game/Clock/Animation_Clock/_animation_sub_clock.h"

typedef struct Animation_Clock {
    // Current tick of this animation clock.
    int current_tick;

    // Array of every game tick that updates this animation clock.
    int* changing_ticks;

    // Amount of changing ticks.
    int changing_ticks_count;

    // Pointers to sub-clocks subscribed to this animation clock.
    Animation_Sub_Clock** sub_clocks;

    // Amount of sub-clocks subscribed to this animation clock.
    int sub_clocks_count;

} Animation_Clock;

// Creates an animation clock using the given JSON data describing it.
Animation_Clock* create_animation_clock(
    const cJSON* JSON,
    Animation_Clock_Index clock_index
);

// Updates an animation clock
void update_animation_clock(
    Animation_Clock* animation_clock,
    int game_clock_tick,
    Tick_Events_List* event_list
);

// Frees an animation clock
void free_animation_clock(Animation_Clock* ac);
