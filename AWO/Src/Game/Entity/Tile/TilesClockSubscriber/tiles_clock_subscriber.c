#pragma warning( disable : 6308 28182 )

#include <stdlib.h>

#include "Game/Clock/game_clock.h"
#include "Game/Entity/Tile/TilesClockSubscriber/tiles_clock_subscriber.h"

typedef struct Tiles_List {

    // How many tiles belong to the list.
    int tiles_count;

    // Tiles belonging to the list.
    Tile** tiles;

} Tiles_List;

struct Tiles_Clock_Subscriber {

    // List of every tile, sorted by which animation clock/sub-clocks they belong to.
    Tiles_List* tiles_list[ANIMATION_CLOCK_COUNT][MINIMAL_ANIMATION_SUB_CLOCK_COUNT];
};

Tiles_Clock_Subscriber* create_tiles_clock_subscriber()
{
    Tiles_Clock_Subscriber* sub_module = malloc(sizeof(Tiles_Clock_Subscriber));

    // Allocate space for the tiles list.
    for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        for (int j = 0; j < MINIMAL_ANIMATION_SUB_CLOCK_COUNT; j++) {
            sub_module->tiles_list[i][j] = malloc(sizeof(Tiles_List));
            sub_module->tiles_list[i][j]->tiles_count = 0;
        }
    }

    return sub_module;
}

void register_tiles_clock_subscriber_tile(Tiles_Clock_Subscriber* sub_module, Tile* tile)
{
    // Get the tile's clock/sub-clock index.
    Animation_Clock_Index clock_index;
    Animation_Sub_Clock_Index sub_clock_index;

    get_tile_clock_data(tile, &clock_index, &sub_clock_index);

    // Add this tile to the tiles list it belongs to.
    int index = sub_module->tiles_list[clock_index][sub_clock_index]->tiles_count++;

    sub_module->tiles_list[clock_index][sub_clock_index]->tiles = realloc(
        sub_module->tiles_list[clock_index][sub_clock_index]->tiles,
        sizeof(Tile**) * sub_module->tiles_list[clock_index][sub_clock_index]->tiles_count
    );

    sub_module->tiles_list[clock_index][sub_clock_index]->tiles[index] = tile;
}

void process_tiles_tick_events(Tiles_Clock_Subscriber* sub_module, Tick_Events_List* events_list)
{
    // Loop the received tick events
    for (int i = 0; i < events_list->ticks_count; i++) {
        Tick_Event event = events_list->ticks[i];
        Tiles_List* tiles_list = sub_module->tiles_list[event.clock_index][event.sub_clock_index];

        // Update the animation index of every tile subscribed to this tick event
        for (int j = 0; j < tiles_list->tiles_count; j++) {
            update_tile_animation_index(tiles_list->tiles[j], event.frame_index);
        }
    }

    // Reset the count of the now-processed tick events list
    events_list->ticks_count = 0;
}

void free_tiles_clock_subscriber(Tiles_Clock_Subscriber* sub_module)
{
    if (sub_module == NULL) {
        return;
    }

    for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        for (int j = 0; j < MINIMAL_ANIMATION_SUB_CLOCK_COUNT; j++) {
            free(sub_module->tiles_list[i][j]);
        }
    }
}
