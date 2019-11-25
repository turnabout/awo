#include <stdlib.h>

#include "Game/Clock/_game_clock.h"

Game_Clock* create_game_clock(const cJSON* clock_data_JSON, Tiles_Data* tiles_data)
{
    Game_Clock* game_clock = (Game_Clock*)malloc(sizeof(Game_Clock));

    game_clock->pub_sub = create_pub_sub_service();

    game_clock->publisher = create_game_clock_publisher(
        clock_data_JSON,
        game_clock->pub_sub
    );

    game_clock->tile_subscriber = create_game_clock_tile_subscriber(tiles_data);

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
    free_pub_sub_service(clock->pub_sub);
    free_game_clock_tile_subscriber(clock->tile_subscriber);
}