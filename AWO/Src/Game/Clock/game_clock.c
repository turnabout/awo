#include <stdlib.h>

#include "Game/Clock/_game_clock.h"

Game_Clock* create_game_clock(
    const cJSON* clock_data_JSON, 
    Tiles_Data* tiles_data,
    GLuint* game_palette
)
{
    Game_Clock* game_clock = (Game_Clock*)malloc(sizeof(Game_Clock));

    // Create the pub-sub module responsible for linking the game clock publisher with subscribers
    game_clock->pub_sub = create_clock_pub_sub();

    // Create the game clock publisher which emits tick events to the pub-sub service
    game_clock->publisher = create_game_clock_publisher(
        clock_data_JSON,
        game_clock->pub_sub
    );

    // Create the subscriber modules, which all subscribe to the pub-sub service and receive tick 
    // events to be processed

    // Tiles clock subscriber module
    game_clock->tile_subscriber = create_game_clock_tile_subscriber(tiles_data);

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

    return game_clock;
}

void update_game_clock(Game_Clock* game_clock, float delta_time)
{
    update_game_clock_publisher(game_clock->publisher, delta_time);

    /*
    if (update_game_clock_publisher(game_clock->publisher, delta_time)) {
        update_game_clock_tile_subscriber(game_clock->tile_subscriber);
        
        game_clock->publisher->tick_events->ticks_count = 0;
    }
    */
}

void register_game_clock_tile(
    Game_Clock* game_clock, 
    Tile* tile,
    Animation_Clock_Index clock_index,
    Animation_Sub_Clock_Index sub_clock_index
)
{
    register_clock_subscriber_tile(game_clock->tile_subscriber, tile, clock_index, sub_clock_index);
}

void free_game_clock(Game_Clock* clock)
{
    free_game_clock_publisher(clock->publisher);
    free_clock_pub_sub(clock->pub_sub);
    free_game_clock_tile_subscriber(clock->tile_subscriber);
}