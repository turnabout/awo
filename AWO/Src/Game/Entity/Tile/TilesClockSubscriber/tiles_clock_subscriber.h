#pragma once

#include "Game/Entity/Tile/tile.h"

// Tiles clock subscriber module.
// Subscribes to the game clock and updates their associated render map.
typedef struct Tiles_Clock_Subscriber Tiles_Clock_Subscriber;

Tiles_Clock_Subscriber* create_tiles_clock_subscriber();

void register_tiles_clock_subscriber_tile(Tiles_Clock_Subscriber* sub_module, Tile* tile);

void process_tiles_tick_events(Tiles_Clock_Subscriber* sub_module, Tick_Event_List* events_list);

void free_tiles_clock_subscriber(Tiles_Clock_Subscriber* subscriber_module);
