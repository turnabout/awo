#pragma once

#include "Game/Clock/Animation_Clock/enums.h"
#include "Game/Clock/game_clock.h"
#include "Game/Clock/Animation_Clock/_animation_clock.h"

struct Game_Clock {

    // Current tick the game clock is on.
    Uint8 current_tick;

    // Accumulated game delta time.
    float accum_time;

    // Animation clocks attached to game clock.
    Animation_Clock* animation_clocks[ANIMATION_CLOCK_COUNT];

    // Static tick counter, always pointing to 0. Given to static tiles.
    int* static_tick;

    // List of current tick events.
    Tick_Event_List* tick_events;
};

#ifdef _DEBUG
/*! @brief Prints the contents of the game clock's current clock tick events.
 *
 *  @param[in] game_clock The game clock.
 */
void print_game_clock_tick_events(Game_Clock* game_clock);
#endif
