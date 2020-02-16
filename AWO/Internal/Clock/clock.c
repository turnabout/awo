#include <stdlib.h>

#include "Clock/_clock.h"
#include "Config/config.h"

Clock* create_clock(Clock_Data* clock_data)
{
    Clock* game_clock = malloc(sizeof(Clock));

    game_clock->frame_count = 0;
    game_clock->accum_time = 0;

    // Create the pub-sub module responsible for linking the game clock publisher with subscribers
    game_clock->pub_sub = create_clock_pub_sub();

    // Create the timers array (publishers)
    for (Clock_Index i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        game_clock->timers[i] = create_clock_timer(clock_data, i, game_clock->pub_sub);
    }

    return game_clock;
}

void update_clock(Clock* game_clock, float delta_time)
{

    // Reached time for a frame
    if ((game_clock->accum_time += delta_time) >= FRAME_TIME) {

        // Get frame count
        float frame_count = game_clock->accum_time / FRAME_TIME;

        for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
            update_timer(game_clock->timers[i], (int)frame_count);
        }

        game_clock->accum_time -= (int)frame_count * FRAME_TIME;
    }
}

void register_clock_subscriber(
    Clock* clock,
    void* subscriber_module,
    clock_subscriber_event_cb subscriber_callback,
    Clock_Index timers[ANIMATION_CLOCK_COUNT],
    int timer_count
)
{
    register_clocks_pub_sub_subscriber(
        clock->pub_sub,
        subscriber_module,
        subscriber_callback,
        timers,
        timer_count
    );
}

void free_clock(Clock* game_clock)
{
    if (game_clock == NULL) {
        return;
    }

    for (Clock_Index i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        free_clock_timer(game_clock->timers[i]);
    }

    free_clock_pub_sub(game_clock->pub_sub);
}