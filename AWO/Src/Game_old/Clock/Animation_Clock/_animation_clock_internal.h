#pragma once
#include "cJSON.h"
#include "animation_clock_enums.h"

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
Animation_Sub_Clock* ASC_create_from_JSON(const cJSON* json);

// Updates the current tick of a sub clock depending on its animation clock's current tick
void ASC_update(Animation_Sub_Clock* asc, int ac_current_tick);

// Gets pointer to the animation sub-clock's current tick
int* ASC_get_tick_ptr(Animation_Sub_Clock* asc);

// Frees an animation sub clock
void ASC_free(Animation_Sub_Clock* asc);
