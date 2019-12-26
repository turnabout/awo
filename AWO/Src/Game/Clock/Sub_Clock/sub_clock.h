#pragma once

#include "Game/Data/Clock/clock_data.h"
#include "Game/Clock/Tick_Event/tick_event.h"
#include "Game/Clock/Pub_Sub/_pub_sub.h"

/*! @brief A sub-clock working under the game clock. Registers to the clock pub-sub service and 
 *  emits tick events to it to be processed.
 */
typedef struct Sub_Clock Sub_Clock;

/*! @brief Creates a sub-clock module.
 *
 *  @param[in] clock_data Reference to the clock data module.
 *  @param[in] index Index of the sub-clock to create.
 *  @return The created sub-clock module.
 */
Sub_Clock* create_sub_clock(Clock_Data* clock_data, Animation_Clock_Index index);

/*! @brief Updates the sub-clock by passing it the count of frames since last time it was updated.
 *
 *  @param[in] clock The sub-clock to update.
 *  @param[in] passed_frames The amount of game frames that passed since the last update.
 */
void update_sub_clock(Sub_Clock* clock, unsigned int passed_frames);

/*! @brief Frees a sub-clock module.
 *
 *  @param[in] clock The sub-clock module to free.
 */
void free_sub_clock(Sub_Clock* clock);