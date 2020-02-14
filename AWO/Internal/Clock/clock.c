#include <stdlib.h>

#include "Clock/_clock.h"
#include "Config/config.h"

Game_Clock* create_game_clock(Clock_Data* clock_data)
{
    Game_Clock* game_clock = malloc(sizeof(Game_Clock));

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

void update_game_clock(Game_Clock* game_clock, float delta_time)
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

void free_game_clock(Game_Clock* game_clock)
{
    if (game_clock == NULL) {
        return;
    }

    for (Clock_Index i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        free_clock_timer(game_clock->timers[i]);
    }

    free_clock_pub_sub(game_clock->pub_sub);
}