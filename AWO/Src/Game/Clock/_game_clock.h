#pragma once

#include "Game/Clock/game_clock.h"
#include "Game/Clock/Publisher/_game_clock_publisher.h"
#include "Game/Clock/Tile_Subscriber/_game_clock_tile_subscriber.h"
#include "Game/Clock/Pub_Sub_Service/_pub_sub_service.h"

struct Game_Clock {

    // The publisher section of the game clock, responsible for ticking and populating the current
    // tick events array.
    Game_Clock_Publisher* publisher;

    // Links the game clock publisher and subscribers.
    Game_Clock_Pub_Sub_Service* pub_sub;

    // Game clock subscriber for tiles. Keeps tiles' animations up to date in accordance with the
    // contents of the tick events list provided by the game clock publisher.
    Game_Clock_Tile_Subscriber* tile_subscriber;
    
};
