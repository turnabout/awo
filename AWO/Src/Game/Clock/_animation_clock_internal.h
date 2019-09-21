#pragma once
#include "cJSON.h"

typedef struct Animation_Clock {
    int current_tick;

    int* changing_ticks;
    int changing_ticks_count;
} Animation_Clock;

// Creates an animation clock using the given JSON data describing it.
Animation_Clock* AC_create_from_JSON(const cJSON* json);

void AC_update(Animation_Clock* animation_clock, int game_clock_tick);
