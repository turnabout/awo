#include <stdlib.h>

#include "Utilities/macros.h"
#include "Utilities/Linked_List/linked_list.h"
#include "Game/Clock/game_clock.h"
#include "Game/Clock/Subscribers/Tiles/_game_clock_tile_subscriber.h"

PRAGMA(warning( disable : 6308 28182 ))

Game_Clock_Tile_Subscriber* create_game_clock_tile_subscriber(Game_Renderer* renderer)
{
    Game_Clock_Tile_Subscriber* module = malloc(sizeof(Game_Clock_Tile_Subscriber));

    module->renderer = renderer;

    // Initialize the lists of tiles
    for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        module->tiles_lists[i] = (Tiles_List*)create_linked_list(NULL, 0);
    }

    return module;
}

void register_clock_subscriber_tile(
    Game_Clock_Tile_Subscriber* module, 
    Tile* tile,
    Animation_Clock_Index clock_index
)
{
    // No need to register the tile if no clock or sub clock
    if (clock_index == No_Clock) {
        return;
    }

    // Add this tile to the tiles list it belongs to
    append_linked_list_item((Linked_List*)module->tiles_lists[clock_index], tile);
}

void unregister_clock_subscriber_tile(
    Game_Clock_Tile_Subscriber* module, 
    Tile* tile,
    Animation_Clock_Index clock_index
)
{
    // Can't unregister the tile if no clock or sub clock
    if (clock_index == No_Clock) {
        return;
    }

    // Delete this tile from the tiles list it belongs to
    delete_linked_list_item((Linked_List*)module->tiles_lists[clock_index], tile);
}

void process_tile_subscriber_event(Tick_Event* tick_event, void* module_arg)
{
    Game_Clock_Tile_Subscriber* module = (Game_Clock_Tile_Subscriber*)module_arg;

    // Get list of tiles registered to tick events of this type
    Tiles_List* tiles_list = ((Game_Clock_Tile_Subscriber*)module)
        ->tiles_lists[tick_event->timer_index];

    // Loop every tile entry & update the render grid pixels for every tile in the list
    List_Entry* entry = tiles_list->head;

    while (entry != NULL) {
        ((Tile*)entry->element)->update_grid(module->renderer, entry->element, tick_event->value);
        entry = entry->next;
    }
}

void free_game_clock_tile_subscriber(Game_Clock_Tile_Subscriber* module)
{
    if (module == NULL) {
        return;
    }

    /*
    for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        free_linked_list((Linked_List*)module->tiles_lists[i]);
    }
    */

    // free(module);
}
