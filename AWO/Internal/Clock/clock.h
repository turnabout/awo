#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cjson/cJSON.h>

#include "Game_Data/Clock_Data/clock_data.h"
#include "Headers/clock_subscriber_event_cb.h"
#include "Headers/tick_event.h"

/*! @brief Main game clock used for updating and keeping animations synchronized.
 */
typedef struct Clock Clock;

/*! @brief Creates the game clock along with its animation clocks.
 *
 *  @param[in] clock_data The clock data module describing the game's clocks.
 *  @return The created game clock module.
 */
Clock* create_clock(Clock_Data* clock_data);

/*! @brief Keeps the game clock's current tick updated, along with its animation clocks.
 *
 * @param[in] clock The game clock module.
 *  @param[in] delta_time Time elapsed since the last game frame.
 */
void update_clock(Clock* clock, float delta_time);

/*! @brief Registers a subscriber module with a clock timer.
 * 
 * @param[in] clock The game clock module.
 * @param[in] subscriber_module Subscriber module to register with the pub-sub module.
 * @param[in] subscriber_callback Function called to send tick events to the subscriber.
 * @param[in] timers The timers from which the subscriber should receive tick events.
 * @param[in] timer_count The count of elements passed in the `timers` argument.
 */
void register_clock_subscriber(
    Clock* clock,
    void* subscriber_module,
    clock_subscriber_event_cb subscriber_callback,
    Clock_Index timers[ANIMATION_CLOCK_COUNT],
    int timer_count
);

/*! @brief Frees the game clock's allocated memory.
 *
 *  @param[in] clock The game clock module.
 */
void free_clock(Clock* clock);