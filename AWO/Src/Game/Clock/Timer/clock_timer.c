#include <stdlib.h>

#include "Game/Clock/Timer/clock_timer.h"
#include "Game/Clock/Tick_Event/tick_event.h"

struct Clock_Timer {

    // Array of frame counts corresponding to values
    Uint8* frames;

    // Count of frames this sub-clock has accumulated
    Uint8 frame_counter;

    // Index of the target count of frames to reach before sending a value
    Uint8 target_frame_index;

    // Max target frame index we can reach before having to reset the sub-clock
    Uint8 max_target_frame_index;

    // Array of values sent when target frames are reached
    Uint8* values;

    // Tick event emitted on tick
    Tick_Event* event;

    // Reference to the game clock pub-sub service
    Game_Clock_Pub_Sub* pub_sub;

};

Clock_Timer* create_clock_timer(
    Clock_Data* clock_data, 
    Clock_Index index, 
    Game_Clock_Pub_Sub* pub_sub
)
{
    Clock_Timer* timer = malloc(sizeof(Clock_Timer));

    // Gather data for this timer
    Uint8 value_count;

    gather_clock_data(
        clock_data, 
        index, 
        &timer->frames, 
        &timer->values, 
        &value_count
    );

    timer->frame_counter = 0;
    timer->max_target_frame_index = value_count;

    // Set the tick event
    timer->event = malloc(sizeof(Tick_Event));
    timer->event->timer_index = index;
    timer->event->value = 0;

    // Set the starting target frame index
    timer->target_frame_index = 1;

    // printf("First target frame count is %d\n", timer->frames[timer->target_frame_index]);

    return timer;
}

static inline void emit_clock_tick_event(Clock_Timer* timer, Uint8 value)
{
    timer->event->value = value;
    // process_clock_pub_sub_tick_event(timer->pub_sub, timer->event);
}

static inline void reset_timer(Clock_Timer* timer, Uint8 excess_frames)
{
    // printf("Resetting frame counter to %d\n", excess_frames);

    // Reset frame counter to the amount of excess frames when max value was reached
    timer->frame_counter = excess_frames;

    // Reset the target frame index to starting value
    timer->target_frame_index = 1;

    // Send first value
    emit_clock_tick_event(timer, timer->values[0]);
}

void update_timer(Clock_Timer* timer, Uint8 passed_frames)
{
    // printf("%d + %d = %d\n", timer->frame_counter, passed_frames, timer->frame_counter + passed_frames);

    timer->frame_counter += passed_frames;

    // Frame counter reached the target frame count
    while (timer->frame_counter >= timer->frames[timer->target_frame_index]) {
        // printf("Target reached: %d >= %d\n", timer->frame_counter, timer->frames[timer->target_frame_index]);

        // Reached max value, reset the timer
        if ((timer->target_frame_index) >= timer->max_target_frame_index) {
            reset_timer(
                timer, 
                timer->frame_counter - timer->frames[timer->max_target_frame_index]
            );
            return;
        }

        emit_clock_tick_event(timer, timer->values[timer->target_frame_index++]);
    }
}

void free_clock_timer(Clock_Timer* timer)
{
    if (timer != NULL) {
        free(timer);
    }
}
