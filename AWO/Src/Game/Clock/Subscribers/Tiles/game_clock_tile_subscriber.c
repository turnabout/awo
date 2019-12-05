#pragma warning( disable : 6308 28182 )

#include <stdlib.h>

#include "Game/Clock/game_clock.h"
#include "Game/Clock/Subscribers/Tiles/_game_clock_tile_subscriber.h"

Game_Clock_Tile_Subscriber* create_game_clock_tile_subscriber(Tiles_Data* tiles_data)
{
    Game_Clock_Tile_Subscriber* module = (Game_Clock_Tile_Subscriber*)malloc(sizeof(Game_Clock_Tile_Subscriber));

    module->tiles_data = tiles_data;

    // Allocate space for the tiles list.
    // Initialize the lists of tiles
    for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        for (int j = 0; j < MAX_ANIMATION_SUB_CLOCK_COUNT; j++) {

            module->tiles_lists[i][j] = create_linked_list(NULL, 0);

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

    // Add this tile to the tiles list it belongs to
    append_linked_list_item(module->tiles_lists[clock_index][sub_clock_index], tile);
}

void unregister_clock_subscriber_tile(
    Game_Clock_Tile_Subscriber* module, 
    Tile* tile,
    Animation_Clock_Index clock_index,
    Animation_Sub_Clock_Index sub_clock_index
)
{
    // No need to unregister the tile if no clock or sub clock
    if (clock_index == No_Clock || sub_clock_index == No_Sub_Clock) {
        return;
    }

    delete_linked_list_item(module->tiles_lists[clock_index][sub_clock_index], tile);
}

// Apply a tick event's value to a looped tile.
void apply_tick_event(void* tile, void* tick_event)
{
    ((Tile*)tile)->update_grid(
        tile,
        ((Tick_Event*)tick_event)->value
    );
}

void process_tile_subscriber_event(Tick_Event* tick_event, void* tile_subscriber_module)
{
    Game_Clock_Tile_Subscriber* module = ((Game_Clock_Tile_Subscriber*)tile_subscriber_module);

    // Get tiles list registered to tick events of this type
    loop_linked_list(
        module->tiles_lists[tick_event->clock_index][tick_event->sub_clock_index], 
        apply_tick_event,
        tick_event
    );

    // Get list of tiles registered to tick events of this type
    Tiles_List* tiles_list = ((Game_Clock_Tile_Subscriber*)tile_subscriber_module)
        ->tiles_list[tick_event->clock_index][tick_event->sub_clock_index];

    // Update the render grid pixels for every tile subscribed to this tick event
    for (int j = 0; j < tiles_list->tiles_count; j++) {
        tiles_list->tiles[j]->update_grid(tiles_list->tiles[j], tick_event->value);
    }
}

void free_game_clock_tile_subscriber(Game_Clock_Tile_Subscriber* module)
{
    if (module == NULL) {
        return;
    }

    for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        for (int j = 0; j < MAX_ANIMATION_SUB_CLOCK_COUNT; j++) {
            free_linked_list(module->tiles_lists[i][j]);
            free(module->tiles_list[i][j]);
        }
    }
}
