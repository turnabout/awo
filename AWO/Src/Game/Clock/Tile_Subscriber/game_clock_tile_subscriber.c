#pragma warning( disable : 6308 28182 )

#include <stdlib.h>

#include "Game/Clock/game_clock.h"
#include "Game/Clock/Tile_Subscriber/_game_clock_tile_subscriber.h"

Game_Clock_Tile_Subscriber* create_game_clock_tile_subscriber(
    Tiles_Data* tiles_data, 
    Tick_Events_List* tick_events
)
{
    Game_Clock_Tile_Subscriber* module = (Game_Clock_Tile_Subscriber*)malloc(sizeof(Game_Clock_Tile_Subscriber));

    module->tiles_data = tiles_data;
    module->tick_events = tick_events;

    // Allocate space for the tiles list.
    for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        for (int j = 0; j < MINIMAL_ANIMATION_SUB_CLOCK_COUNT; j++) {
            module->tiles_list[i][j] = malloc(sizeof(Tiles_List));
            module->tiles_list[i][j]->tiles_count = 0;
            module->tiles_list[i][j]->tiles = NULL;
        }
    }

    return module;
}

void register_clock_subscriber_tile(Game_Clock_Tile_Subscriber* module, Tile* tile)
{
    // Get the tile's clock/sub-clock index.
    Animation_Clock_Index clock_index;
    Animation_Sub_Clock_Index sub_clock_index;

    gather_tile_data(
        module->tiles_data,
        tile->type,
        tile->variation,
        &clock_index,
        &sub_clock_index,
        NULL
    );

    // No need to register the tile if no clock or sub clock
    if (clock_index == No_Clock || sub_clock_index == No_Sub_Clock) {
        return;
    }

    // Add this tile to the tiles list it belongs to.
    int index = module->tiles_list[clock_index][sub_clock_index]->tiles_count++;

    module->tiles_list[clock_index][sub_clock_index]->tiles = realloc(
        module->tiles_list[clock_index][sub_clock_index]->tiles,
        sizeof(Tile**) * module->tiles_list[clock_index][sub_clock_index]->tiles_count
    );

    module->tiles_list[clock_index][sub_clock_index]->tiles[index] = tile;
}

void update_game_clock_tile_subscriber(Game_Clock_Tile_Subscriber* clock_subscriber)
{
    print_tick_events_list(clock_subscriber->tick_events);


    // Loop the current tick events
    for (int i = 0; i < clock_subscriber->tick_events->ticks_count; i++) {
        Tick_Event event = clock_subscriber->tick_events->ticks[i];
        Tiles_List* tiles_list = clock_subscriber->tiles_list[event.clock_index][event.sub_clock_index];

        // Update the render grid pixels for every tile subscribed to this tick event
        for (int j = 0; j < tiles_list->tiles_count; j++) {
            tiles_list->tiles[j]->update_render_grid(tiles_list->tiles[j], event.frame_index);
        }
    }

    // Reset the count of the now-processed tick events list
    // events_list->ticks_count = 0;
}

void free_game_clock_tile_subscriber(Game_Clock_Tile_Subscriber* module)
{
    if (module == NULL) {
        return;
    }

    for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        for (int j = 0; j < MINIMAL_ANIMATION_SUB_CLOCK_COUNT; j++) {
            free(module->tiles_list[i][j]);
        }
    }
}
