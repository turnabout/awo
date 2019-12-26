#include <stdlib.h>

#include "Game/Clock/_game_clock.h"

Game_Clock* create_game_clock(Clock_Data* clock_data)
{
    Game_Clock* game_clock = malloc(sizeof(Game_Clock));

    // Create the pub-sub module responsible for linking the game clock publisher with subscribers
    game_clock->pub_sub = create_clock_pub_sub();

    // Create the sub-clocks array (publishers)
    for (Animation_Clock_Index i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        game_clock->sub_clocks[i] = create_sub_clock(clock_data, i, game_clock->pub_sub);
    }

    /*
    update_sub_clock(game_clock->sub_clocks[2], 1);
    update_sub_clock(game_clock->sub_clocks[2], 1);
    update_sub_clock(game_clock->sub_clocks[2], 7);
    update_sub_clock(game_clock->sub_clocks[2], 9);
    update_sub_clock(game_clock->sub_clocks[2], 9);
    update_sub_clock(game_clock->sub_clocks[2], 9);
    update_sub_clock(game_clock->sub_clocks[2], 9);
    update_sub_clock(game_clock->sub_clocks[2], 9);
    update_sub_clock(game_clock->sub_clocks[2], 9);
    update_sub_clock(game_clock->sub_clocks[2], 9);
    update_sub_clock(game_clock->sub_clocks[2], 18);
    update_sub_clock(game_clock->sub_clocks[2], 9);
    update_sub_clock(game_clock->sub_clocks[2], 10);
    */
    // update_sub_clock(game_clock->sub_clocks[2], 109);

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
        (Animation_Clock_Index[ANIMATION_CLOCK_COUNT]) {
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
    // TODO
}

void register_game_clock_tile(
    Game_Clock* game_clock, 
    Tile* tile,
    Animation_Clock_Index clock_index
)
{
    // TODO
    // register_clock_subscriber_tile(game_clock->tile_subscriber, tile, clock_index, sub_clock_index);
}

void unregister_game_clock_tile(
    Game_Clock* game_clock, 
    Tile* tile,
    Animation_Clock_Index clock_index
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

    for (Animation_Clock_Index i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        free_sub_clock(game_clock->sub_clocks[i]);
    }

    // free_clock_pub_sub(game_clock->pub_sub);
    // free_game_clock_tile_subscriber(game_clock->tile_subscriber);
    // free_game_clock_property_lights_subscriber(game_clock->property_lights_subscriber);
}