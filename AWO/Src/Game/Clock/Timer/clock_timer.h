#pragma once

#include "Game/Data/Clock/clock_data.h"
#include "Game/Clock/Pub_Sub/pub_sub.h"

/*! @brief A sub-clock working under the game clock. Registers to the clock pub-sub service and 
 *  emits tick events to it to be processed.
 */
typedef struct Clock_Timer Clock_Timer;

/*! @brief Creates a sub-clock module.
 *
 *  @param[in] clock_data Reference to the clock data module.
 *  @param[in] index Index of the sub-clock to create.
 *  @param[in] pub_sub Reference to the game clock pub-sub service.
 *  @return The created sub-clock module.
 */
Clock_Timer* create_clock_timer(
    Clock_Data* clock_data,
    Animation_Clock_Index index,
    Game_Clock_Pub_Sub* pub_sub
);

/*! @brief Updates the sub-clock by passing it the count of frames since last time it was updated.
 *
 *  @param[in] clock The sub-clock to update.
 *  @param[in] passed_frames The amount of game frames that passed since the last update.
 */
void update_timer(Clock_Timer* clock, Uint8 passed_frames);

/*! @brief Frees a sub-clock module.
 *
 *  @param[in] clock The sub-clock module to free.
 */
void free_clock_timer(Clock_Timer* clock);