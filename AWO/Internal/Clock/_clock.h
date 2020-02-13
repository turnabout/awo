#pragma once

#include "Clock/clock.h"
#include "Clock/Timer/clock_timer.h"
#include "Clock/Tick_Event/tick_event.h"

struct Game_Clock {

    // Array of all publisher timer clocks belonging to the game clock module.
    Clock_Timer* timers[ANIMATION_CLOCK_COUNT];

    // Count of passed frames since the game clock started updating
    int frame_count;

    // Amount of time accumulated in milliseconds
    float accum_time;

};
