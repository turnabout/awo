#include <stdio.h>
#include <stdlib.h>

#include "conf.h"
#include "types.h"
#include "Game/Clock/game_clock.h"
#include "Game/Clock/Animation_Clock/_animation_clock.h"

// How much time (in seconds) must be accumulated before the game clock ticks
static const float GAME_CLOCK_MAX_ACCUM = FRAME_TIME * GAME_CLOCK_FRAMES_TO_TICK;

struct Game_Clock {
    Uint8 current_tick; // Current tick the game clock is on
    float accum_time;   // Accumulated game delta time
    Animation_Clock* animation_clocks[ANIMATION_CLOCK_COUNT]; // Animation clocks attached to game clock
    int* static_tick; // Static tick counter, always pointing to 0. Given to static tiles.
};

Game_Clock* create_game_clock(const cJSON* clock_data_JSON)
{
    // Create the game clock
    Game_Clock* game_clock = (Game_Clock*)malloc(sizeof(Game_Clock));

    game_clock->current_tick = 0;
    game_clock->accum_time = 0.0f;

    // Add static tick
    game_clock->static_tick = malloc(sizeof(int));
    *game_clock->static_tick = 0;

    // Create the game clock's animation clocks
    for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        game_clock->animation_clocks[i] = create_animation_clock(
            cJSON_GetArrayItem(clock_data_JSON, i)
        );
    }

    return game_clock;
}

void update_game_clock(Game_Clock* game_clock, float delta_time)
{
    // Add to MS accumulation, advance current tick if threshold reached
    if ((game_clock->accum_time += delta_time) > GAME_CLOCK_MAX_ACCUM) {
        game_clock->accum_time = 0;

        // Reset tick if exceeded max
        if (++game_clock->current_tick > GAME_CLOCK_TICK_MAX) {
            game_clock->current_tick = 0;
        }

        // Update the animation clocks
        for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
            update_animation_clock(game_clock->animation_clocks[i], game_clock->current_tick);
        }
    }
}

int* get_game_clock_tick_ptr(Game_Clock* gc, Animation_Clock_Index ac_index, Animation_Sub_Clock_Index sc_index)
{
    if (ac_index == No_Clock) {
        return gc->static_tick;
    }

    return get_animation_clock_child_tick_ptr(gc->animation_clocks[ac_index], sc_index);
}

void free_game_clock(Game_Clock* gc)
{
    free(gc->static_tick);

    // Free all attached animation clocks
    for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        free_animation_clock(gc->animation_clocks[i]);
    }

    free(gc);
}
