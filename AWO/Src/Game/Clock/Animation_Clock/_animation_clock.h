#pragma once

#include <cJSON.h>

#include "Game/Clock/Animation_Clock/enums.h"

typedef struct Animation_Sub_Clock {
    int current_tick; // Current tick of this animation sub clock
    int* ticks_array;  // Array of every possible game tick
} Animation_Sub_Clock;

typedef struct Animation_Clock {
    int current_tick; // Current tick of this animation clock

    int* changing_ticks;      // Array of every game tick that updates this animation clock
    int changing_ticks_count; // Amount of changing ticks

    Animation_Sub_Clock** sub_clocks; // Pointers to sub-clocks subscribed to this animation clock
    int sub_clocks_count;             // Amount of sub-clocks subscribed to this animation clock
} Animation_Clock;

// Creates an animation clock using the given JSON data describing it.
Animation_Clock* AC_create_from_JSON(const cJSON* json);

// Updates an animation clock
void AC_update(Animation_Clock* animation_clock, int game_clock_tick);

// Gets pointer to the animation sub-clock's current tick, belonging to the given animation clock
int* AC_get_ASC_tick_ptr(Animation_Clock* ac, Animation_Sub_Clock_Index sub_clock_index);

// Frees an animation clock
void AC_free(Animation_Clock* ac);

// Creates an animation sub clock using the given JSON data describing it.
Animation_Sub_Clock* create_animation_sub_clock_from_JSON(const cJSON* json);

// Updates the current tick of a sub clock depending on its animation clock's current tick
void update_animation_sub_clock(Animation_Sub_Clock* asc, int ac_current_tick);

// Gets pointer to the animation sub-clock's current tick
int* get_animation_sub_clock_tick_ptr(Animation_Sub_Clock* asc);

// Frees an animation sub clock
void free_animation_sub_clock(Animation_Sub_Clock* asc);
