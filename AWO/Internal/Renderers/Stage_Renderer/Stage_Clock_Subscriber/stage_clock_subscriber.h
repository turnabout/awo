#pragma once

#include "Clock/clock.h"

/*! @brief Module responsible for animating entities making up the stage by using the clock module.
 */
typedef struct Stage_Clock_Subscriber Stage_Clock_Subscriber;

Stage_Clock_Subscriber* create_stage_clock_subscriber(Clock* clock);

// TODO: moving to new Stage_Renderer submodule
/*! @brief Registers the given tile with the game clock module to keep its animation updated.
 *
 *  @param[in] game_clock The game clock.
 *  @param[in] tile The tile object.
 *  @param[in] clock_index Index of the animation clock the tile should subscribe to.
 *  @param[in] sub_clock_index Index of the animation sub-clock the tile should subscribe to.
 */
/*
void register_game_clock_tile(
    Clock* game_clock, 
    Tile* tile,
    Clock_Index clock_index
);
void unregister_game_clock_tile(
    Clock* game_clock,
    Tile* tile,
    Clock_Index clock_index
);
*/

void free_stage_clock_subscriber(Stage_Clock_Subscriber* subscriber);