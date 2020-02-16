#pragma once

#include "Clock/clock.h"
#include "Clock/Timer/clock_timer.h"

struct Clock {

    // Array of all publisher timer clocks belonging to the game clock module.
    Clock_Timer* timers[ANIMATION_CLOCK_COUNT];

    // Links the game clock publishers and subscribers.
    Clock_Pub_Sub* pub_sub;

    // Count of passed frames since the game clock started updating
    int frame_count;

    // Amount of time accumulated in milliseconds
    float accum_time;

};
