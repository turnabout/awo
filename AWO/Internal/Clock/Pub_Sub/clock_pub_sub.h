#pragma once

#include "Clock/Headers/tick_event.h"
#include "Clock/Headers/clock_subscriber_event_cb.h"

/*! @brief Module responsible for linking the game clock with its subscribers.
 */
typedef struct Clock_Pub_Sub Clock_Pub_Sub;

/*! @brief Creates the game clock's pub-sub module.
 */
Clock_Pub_Sub* create_clock_pub_sub();

/*! @brief Registers a subscriber with the pub-sub module.
 * 
 * @param[in] pub_sub The pub-sub module.
 * @param[in] subscriber_module Subscriber module to register with the pub-sub module.
 * @param[in] subscriber_callback Function called to send tick events to the subscriber.
 * @param[in] clocks The clocks (timers) from which the subscriber should receive tick events.
 * @param[in] clock_count The count of elements passed in the `clocks` argument.
 */
void register_clocks_pub_sub_subscriber(
    Clock_Pub_Sub* pub_sub,
    void* subscriber_module,
    clock_subscriber_event_cb subscriber_callback,
    Clock_Index clocks[ANIMATION_CLOCK_COUNT],
    int clock_count
);

/*! @brief Processes a tick event with the pub-sub module.
 * 
 * @param[in] pub_sub The pub-sub module.
 * @param[in] tick_event The tick event to process.
 */
void process_clock_pub_sub_tick_event(Clock_Pub_Sub* pub_sub, Tick_Event* tick_event);

/*! @brief Frees memory occupied by the pub-sub module.
 * 
 * @param[in] The pub-sub module to free.
 */
void free_clock_pub_sub(Clock_Pub_Sub* pub_sub);