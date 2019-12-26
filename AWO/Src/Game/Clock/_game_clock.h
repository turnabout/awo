#pragma once

#include "Game/Clock/game_clock.h"
#include "Game/Clock/Subscribers/Tiles/_game_clock_tile_subscriber.h"
#include "Game/Clock/Subscribers/Property_Lights/_property_lights_subscriber.h"
#include "Game/Clock/Tick_Event/tick_event.h"
#include "Game/Clock/Pub_Sub/_pub_sub.h"
#include "Game/Clock/Sub_Clock/sub_clock.h"

struct Game_Clock {

    // Array of all sub-clocks belonging to the game clock module.
    Sub_Clock* sub_clocks[ANIMATION_CLOCK_COUNT];

    // Links the game clock publishers and subscribers.
    Game_Clock_Pub_Sub* pub_sub;

    // Game clock subscriber for tiles. Keeps tiles' animations up to date in accordance with the
    // contents of the tick events list provided by the game clock publisher.
    Game_Clock_Tile_Subscriber* tile_subscriber;

    // Game clock subscriber for properties' lights.
    Game_Clock_Property_Lights_Subscriber* property_lights_subscriber;
    
};
