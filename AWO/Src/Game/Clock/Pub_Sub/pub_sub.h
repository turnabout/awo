#pragma once

#include "Game/Clock/Tick_Event/tick_event.h"


/*! @brief Function used by clock subscribers to receive tick events from the pub-sub module.
 *
 * Added to the pub-sub service which is then responsible for feeding those callbacks with tick 
 * events generated by the clock publisher.
 *
 *  @param[in] tick_event The tick event received.
 *  @param[in] subscriber_module Reference to the subscriber module the tick event is sent to.
 */
typedef void (*clock_subscriber_event_cb)(Tick_Event* tick_event, void* subscriber_module);

/*! @brief Module responsible for linking the game clock with its subscribers.
 */
typedef struct Game_Clock_Pub_Sub Game_Clock_Pub_Sub;

/*! @brief Creates the game clock's pub-sub module.
 */
Game_Clock_Pub_Sub* create_clock_pub_sub();

/*! @brief Registers a subscriber with the pub-sub module.
 * 
 * @param[in] pub_sub The pub-sub module.
 * @param[in] subscriber_module Subscriber module to register with the pub-sub module.
 * @param[in] subscriber_callback Function called to send tick events to the subscriber.
 * @param[in] clocks The clocks from which the subscriber should receive tick events.
 * @param[in] clock_count The count of clocks passed to the function.
 */
void register_clocks_pub_sub_subscriber(
    Game_Clock_Pub_Sub* pub_sub,
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
void process_clock_pub_sub_tick_event(Game_Clock_Pub_Sub* pub_sub, Tick_Event* tick_event);

/*! @brief Frees memory occupied by the pub-sub module.
 * 
 * @param[in] The pub-sub module to free.
 */
void free_clock_pub_sub(Game_Clock_Pub_Sub* pub_sub);