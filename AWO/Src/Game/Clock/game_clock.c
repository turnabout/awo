#include <stdlib.h>

#include "Game/Clock/_game_clock.h"

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

    game_clock->tile_subscriber = NULL;
    game_clock->property_lights_subscriber = NULL;

    return game_clock;
}

void activate_game_clock_subscribers(
    Game_Clock* game_clock, 
    Game_Renderer* game_renderer, 
    GLuint* game_palette
)
{
    // Create the subscriber modules which subscribe to the pub-sub service and receive tick events

    // Tiles clock subscriber module
    game_clock->tile_subscriber = create_game_clock_tile_subscriber(game_renderer);

    register_clocks_pub_sub_subscriber(
        game_clock->pub_sub,
        (void*)game_clock->tile_subscriber,
        process_tile_subscriber_event,
        (Clock_Index[ANIMATION_CLOCK_COUNT]) {
            Sea_Clock_0,
            Sea_Clock_1,
            Sea_Clock_2
        },
        1
    );

    /*
    // Property lights clock subscriber module
    game_clock->property_lights_subscriber = create_game_clock_property_lights_subscriber(
        game_palette
    );

    register_clock_pub_sub_subscriber(
        game_clock->pub_sub,
        (void*)game_clock->property_lights_subscriber,
        process_property_light_tick_event,
        Property_Lights_Clock
    );
*/
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

void register_game_clock_tile(
    Game_Clock* game_clock, 
    Tile* tile,
    Clock_Index clock_index
)
{
    // TODO
    // register_clock_subscriber_tile(game_clock->tile_subscriber, tile, clock_index, sub_clock_index);
}

void unregister_game_clock_tile(
    Game_Clock* game_clock, 
    Tile* tile,
    Clock_Index clock_index
)
{
    // TODO
    // unregister_clock_subscriber_tile(game_clock->tile_subscriber, tile, clock_index, sub_clock_index);
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
    // free_game_clock_tile_subscriber(game_clock->tile_subscriber);
    // free_game_clock_property_lights_subscriber(game_clock->property_lights_subscriber);
}