#pragma warning( disable : 6308 28182 )

#include <stdlib.h>

#include "Game/Clock/game_clock.h"
#include "Game/Clock/Tile_Subscriber/_game_clock_tile_subscriber.h"

Game_Clock_Tile_Subscriber* create_game_clock_tile_subscriber(Tiles_Data* tiles_data)
{
    Game_Clock_Tile_Subscriber* module = (Game_Clock_Tile_Subscriber*)malloc(sizeof(Game_Clock_Tile_Subscriber));

    module->tiles_data = tiles_data;

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

void register_clock_subscriber_tile(
    Game_Clock_Tile_Subscriber* module, 
    Tile* tile,
    Animation_Clock_Index clock_index,
    Animation_Sub_Clock_Index sub_clock_index
)
{
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

void process_tile_subscriber_event(Tick_Event* tick_event, void* tile_subscriber_module)
{
    // Get list of tiles registered to tick events of this type
    Tiles_List* tiles_list = ((Game_Clock_Tile_Subscriber*)tile_subscriber_module)
        ->tiles_list[tick_event->clock_index][tick_event->sub_clock_index];

    // Update the render grid pixels for every tile subscribed to this tick event
    for (int j = 0; j < tiles_list->tiles_count; j++) {
        tiles_list->tiles[j]->update_grid(tiles_list->tiles[j], tick_event->frame_index);
    }
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
