#pragma once
#include "cJSON.h"

typedef struct Animation_Clock {
    int current_tick; // Current tick of this animation clock

    int* changing_ticks;      // Array of every game tick that updates this animation clock
    int changing_ticks_count; // Amount of changing ticks
} Animation_Clock;

// Creates an animation clock using the given JSON data describing it.
Animation_Clock* AC_create_from_JSON(const cJSON* json);

// Update this animation clock
void AC_update(Animation_Clock* animation_clock, int game_clock_tick);
