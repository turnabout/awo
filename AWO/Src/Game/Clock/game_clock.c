#include <stdio.h>
#include <stdlib.h>

#include "conf.h"
#include "types.h"
#include "Game/Clock/game_clock.h"
#include "Game/Clock/Animation_Clock/_animation_clock.h"

struct Game_Clock {
    Uint8 current_tick;    // Current tick the game clock is on
    Uint32 accum_ms;       // Accumulated milliseconds
    Uint32 last_game_tick; // Result of SDL_GetTicks() last time the game clock was updated

    Animation_Clock* anim_clocks[ANIMATION_CLOCK_COUNT]; // Animation clocks attached to game clock
    int* static_tick; // Static tick counter, always pointing to 0. Given to static tiles.
};

Game_Clock* create_game_clock(const cJSON* json)
{
    // Create the game clock
    Game_Clock* gc = (Game_Clock*)malloc(sizeof(Game_Clock));

    gc->current_tick = 0;
    gc->accum_ms = 0;
    gc->last_game_tick = 0; // TODO: use GLFW time functions

    // Add static tick
    gc->static_tick = malloc(sizeof(int));
    *gc->static_tick = 0;

    // Create the game clock's animation clocks
    for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        gc->anim_clocks[i] = AC_create_from_JSON(
            cJSON_GetArrayItem(json, i)
        );
    }

    return gc;
}

void update_game_clock(Game_Clock* gc)
{
    // Get how many milliseconds passed since last update
    // Uint32 current_tick = SDL_GetTicks();
    Uint32 current_tick = 0; // TODO: Use GLFW time functions
    Uint32 delta = current_tick - gc->last_game_tick;

    gc->last_game_tick = current_tick;

    // Threshold reached, advance the current tick
    // Add to MS accumulation, advance current tick if threshold reached
    if ((gc->accum_ms += delta) > GAME_CLOCK_MAX_ACCUM_MS) {
        gc->accum_ms = 0;

        // Reset tick if exceeded max
        if (++gc->current_tick > GAME_CLOCK_TICK_MAX) {
            gc->current_tick = 0;
        }

        // Update the animation clocks
        for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
            AC_update(gc->anim_clocks[i], gc->current_tick);
        }
    }
}

int* get_game_clock_tick_ptr(Game_Clock* gc, Animation_Clock_Index ac_index, Animation_Sub_Clock_Index sc_index)
{
    if (ac_index == No_Clock) {
        return gc->static_tick;
    }

    return AC_get_ASC_tick_ptr(gc->anim_clocks[ac_index], sc_index);
}

void free_game_clock(Game_Clock* gc)
{
    free(gc->static_tick);

    // Free all attached animation clocks
    for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        AC_free(gc->anim_clocks[i]);
    }

    free(gc);
}
