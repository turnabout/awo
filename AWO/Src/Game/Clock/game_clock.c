#include <stdio.h>
#include <stdlib.h>

#include "conf.h"
#include "types.h"
#include "Game/Clock/_game_clock.h"
#include "Game/Clock/Animation_Clock/_animation_clock.h"

// How much time (in seconds) must be accumulated before the game clock ticks
static const float GAME_CLOCK_MAX_ACCUM = FRAME_TIME * GAME_CLOCK_FRAMES_TO_TICK;

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
            cJSON_GetArrayItem(clock_data_JSON, i),
            (Animation_Clock_Index)i
        );
    }

    game_clock->tick_events = (Tick_Event_List*)malloc(sizeof(Tick_Event_List));
    game_clock->tick_events->ticks_count = 0;

    return game_clock;
}

void update_game_clock(Game_Clock* game_clock, float delta_time)
{
    // Reset tick events list from previous frame, if non-empty
    if (game_clock->tick_events->ticks_count) {
        print_game_clock_tick_events(game_clock);
        game_clock->tick_events->ticks_count = 0;
    }

    // Add to MS accumulation, advance current tick if threshold reached
    if ((game_clock->accum_time += delta_time) > GAME_CLOCK_MAX_ACCUM) {
        game_clock->accum_time = 0;

        // Reset tick if exceeded max
        if (++game_clock->current_tick > GAME_CLOCK_TICK_MAX) {
            game_clock->current_tick = 0;
        }

        // Update the animation clocks
        for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
            update_animation_clock(
                game_clock->animation_clocks[i],
                game_clock->current_tick,
                game_clock->tick_events
            );
        }
    }
}

int* get_game_clock_tick_ptr(
    Game_Clock* game_clock, 
    Animation_Clock_Index anim_clock_index, 
    Animation_Sub_Clock_Index anim_sub_clock_index
)
{
    if (anim_clock_index == No_Clock) {
        return game_clock->static_tick;
    }

    return get_animation_clock_child_tick_ptr(game_clock->animation_clocks[anim_clock_index], anim_sub_clock_index);
}

void free_game_clock(Game_Clock* game_clock)
{
    if (game_clock != NULL) {
        free(game_clock->static_tick);

        // Free all attached animation clocks
        for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
            free_animation_clock(game_clock->animation_clocks[i]);
        }

        free(game_clock);
    }
}
