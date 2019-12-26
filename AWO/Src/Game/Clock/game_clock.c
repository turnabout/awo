#include <stdlib.h>

#include "Game/Clock/_game_clock.h"

Game_Clock* create_game_clock(cJSON* clock_data_JSON)
{
    Game_Clock* game_clock = malloc(sizeof(Game_Clock));

    // Create the sub-clocks array (publishers)



    // Create the pub-sub module responsible for linking the game clock publisher with subscribers
    game_clock->pub_sub = create_clock_pub_sub();

    // Create the game clock publisher which emits tick events to the pub-sub service
    game_clock->publisher = create_game_clock_publisher(
        clock_data_JSON,
        game_clock->pub_sub
    );

    return game_clock;
}

void activate_game_clock_subscribers(
    Game_Clock* game_clock, 
    Game_Renderer* game_renderer, 
    GLuint* game_palette
)
{
    // Create the subscriber modules, which all subscribe to the pub-sub service and receive tick 
    // events to be processed

    // Tiles clock subscriber module
    game_clock->tile_subscriber = create_game_clock_tile_subscriber(game_renderer);

    /*
    register_clock_pub_sub_subscriber(
        game_clock->pub_sub,
        (void*)game_clock->tile_subscriber,
        process_tile_subscriber_event,
        Sea_Clock
    );

    register_clock_pub_sub_subscriber(
        game_clock->pub_sub,
        (void*)game_clock->tile_subscriber,
        process_tile_subscriber_event,
        River_Clock
    );

    register_clock_pub_sub_subscriber(
        game_clock->pub_sub,
        (void*)game_clock->tile_subscriber,
        process_tile_subscriber_event,
        Base_Smoke_Clock
    );

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
    // update_game_clock_publisher(game_clock->publisher, delta_time);
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

void free_game_clock(Game_Clock* clock)
{
    if (clock == NULL) {
        return;
    }

    free_game_clock_publisher(clock->publisher);
    free_clock_pub_sub(clock->pub_sub);
    free_game_clock_tile_subscriber(clock->tile_subscriber);
    free_game_clock_property_lights_subscriber(clock->property_lights_subscriber);
}