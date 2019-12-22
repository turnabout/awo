#pragma once

#include "types.h"
#include "Game/Clock/game_clock.h"
#include "Game/Clock/Publisher/Animation_Clock/_animation_clock.h"
#include "Game/Clock/Pub_Sub/_pub_sub.h"

typedef struct Game_Clock_Publisher {

    // Current tick the game clock is on.
    Uint8 current_tick;

    // Accumulated game delta time.
    float accum_time;

    // Animation clocks attached to game clock.
    Animation_Clock* animation_clocks[ANIMATION_CLOCK_COUNT];

    // Static tick counter, always pointing to 0. Given to static tiles.
    int* static_tick;

} Game_Clock_Publisher;

/*! @brief Creates the game clock publisher along with its animation clocks.
 *
 *  @param[in] clock_data_cJSON The data JSON object describing the game clock and its animation 
 *  clocks.
 *  @param[in] pub_sub_service The pub-sub service module. Used to route clock tick events to 
 *  subscribers.
 */
Game_Clock_Publisher* create_game_clock_publisher(
    const cJSON* clock_data_JSON,
    Game_Clock_Pub_Sub* pub_sub_service
);

/*! @brief Keeps the game clock publisher's current tick updated, along with its animation clocks.
 *
 *  @param[in] publisher The game clock publisher.
 *  @param[in] delta_time Time elapsed since the last game frame.
 */
void update_game_clock_publisher(Game_Clock_Publisher* publisher, float delta_time);

/*! @brief Frees the game clock publisher's allocated memory.
 *
 *  @param[in] publisher The game clock publisher.
 */
void free_game_clock_publisher(Game_Clock_Publisher* publisher);