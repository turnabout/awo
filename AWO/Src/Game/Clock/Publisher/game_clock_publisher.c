#include <stdio.h>
#include <stdlib.h>

#include "conf.h"
#include "Game/Clock/Publisher/_game_clock_publisher.h"

// How much time (in seconds) must be accumulated before the game clock ticks
static const float GAME_CLOCK_MAX_ACCUM = FRAME_TIME * GAME_CLOCK_FRAMES_TO_TICK;

Game_Clock_Publisher* create_game_clock_publisher(const cJSON* clock_data_JSON)
{
    // Create the game clock
    Game_Clock_Publisher* publisher = (Game_Clock_Publisher*)malloc(
        sizeof(Game_Clock_Publisher)
    );

    publisher->current_tick = 0;
    publisher->accum_time = 0.0f;

    // Add static tick
    publisher->static_tick = malloc(sizeof(int));
    *publisher->static_tick = 0;

    // Create the game clock's animation clocks
    for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        publisher->animation_clocks[i] = create_animation_clock(
            cJSON_GetArrayItem(clock_data_JSON, i),
            (Animation_Clock_Index)i
        );
    }

    publisher->tick_events = (Tick_Events_List*)malloc(sizeof(Tick_Events_List));
    publisher->tick_events->ticks_count = 0;

    return publisher;
}

Bool update_game_clock_publisher(Game_Clock_Publisher* publisher, float delta_time)
{
    // Add to MS accumulation, advance current tick if threshold reached
    if ((publisher->accum_time += delta_time) > GAME_CLOCK_MAX_ACCUM) {
        publisher->accum_time = 0;

        // Reset tick if exceeded max
        if (++publisher->current_tick > GAME_CLOCK_TICK_MAX) {
            publisher->current_tick = 0;
        }

        // Update the animation clocks
        for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
            update_animation_clock(
                publisher->animation_clocks[i],
                publisher->current_tick,
                publisher->tick_events
            );
        }

        // Return true if the tick events were updated
        if (publisher->tick_events->ticks_count) {
            return TRUE;
        }
    }

    return FALSE;
}

void free_game_clock_publisher(Game_Clock_Publisher* publisher)
{
    if (publisher != NULL) {
        free(publisher->static_tick);

        // Free all attached animation clocks
        for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
            free_animation_clock(publisher->animation_clocks[i]);
        }

        free(publisher);
    }
}
