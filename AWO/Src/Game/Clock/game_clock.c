#include <stdlib.h>

#include "Game/Clock/_game_clock.h"

Game_Clock* create_game_clock(const cJSON* clock_data_JSON, Tiles_Data* tiles_data)
{
    Game_Clock* game_clock = (Game_Clock*)malloc(sizeof(Game_Clock));

    game_clock->publisher = create_game_clock_publisher(clock_data_JSON);

    game_clock->tile_subscriber = create_game_clock_tile_subscriber(
        tiles_data, 
        game_clock->publisher->tick_events
    );

    return game_clock;
}

void update_game_clock(Game_Clock* game_clock, float delta_time)
{
    if (update_game_clock_publisher(game_clock->publisher, delta_time)) {
        update_game_clock_tile_subscriber(game_clock->tile_subscriber);
        
        game_clock->publisher->tick_events->ticks_count = 0;
    }
}

void register_game_clock_tile(Game_Clock* game_clock, Tile* tile)
{
    register_clock_subscriber_tile(game_clock->tile_subscriber, tile);
}

void free_game_clock(Game_Clock* clock)
{
    free_game_clock_publisher(clock->publisher);
    free_game_clock_tile_subscriber(clock->tile_subscriber);
}