#pragma once
#include "Animation_Clock/animation_clock_enums.h"

// Main game clock used for updating and keeping animations synchronized.
typedef struct Game_Clock Game_Clock;

// Create the game clock, along with its animation clocks using the given data JSON
Game_Clock* GC_create(const cJSON* json);

// Update the game clock's current tick value
void GC_update(Game_Clock* gc);

// Gets pointer to the tick counter belonging to the given animation clock & animation sub-clock
// \param gc       Pointer to the game clock.
// \param ac_index Index of the animation clock, to which the sought sub-clock belongs.
// \param sc_index Index of the sought sub-clock, from which the tick pointer will be returned.
int* GC_get_ASC_tick_ptr(Game_Clock* gc, Animation_Clock_Index ac_index, Animation_Sub_Clock_Index sc_index);

// Free the game clock's allocated memory
void GC_free(Game_Clock* clock);