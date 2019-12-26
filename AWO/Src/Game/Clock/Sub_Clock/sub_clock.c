#include <stdlib.h>

#include "Game/Clock/Sub_Clock/sub_clock.h"
#include "Game/Clock/Tick_Event/tick_event.h"

struct Sub_Clock {

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

};

Sub_Clock* create_sub_clock(Clock_Data* clock_data, Animation_Clock_Index index)
{
    Sub_Clock* clock = malloc(sizeof(Sub_Clock));

    // Gather data for this sub-clock
    Uint8 value_count;

    gather_clock_data(
        clock_data, 
        index, 
        &clock->frames, 
        &clock->values, 
        &value_count
    );

    clock->frame_counter = 0;
    clock->max_target_frame_index = value_count;

    // Set the tick event
    clock->event = malloc(sizeof(Tick_Event));
    clock->event->clock_index = index;
    clock->event->value = 0;

    // Set the starting target frame index
    clock->target_frame_index = 1;

    printf("First target frame count is %d\n", clock->frames[clock->target_frame_index]);

    return clock;
}

static inline void emit_sub_clock_tick_event(Sub_Clock* clock, Uint8 value)
{
    clock->event->value = value;
    printf("Emitting value %d\n", value);
}

static inline void reset_sub_clock(Sub_Clock* clock, Uint8 excess_frames)
{
    printf("Resetting frame counter to %d\n", excess_frames);

    // Reset frame counter to the amount of excess frames when max value was reached
    clock->frame_counter = excess_frames;

    // Reset the target frame index to starting value
    clock->target_frame_index = 1;

    // Send first value
    emit_sub_clock_tick_event(clock, clock->values[0]);
}

void update_sub_clock(Sub_Clock* clock, Uint8 passed_frames)
{
    printf("%d + %d = %d\n", clock->frame_counter, passed_frames, clock->frame_counter + passed_frames);

    clock->frame_counter += passed_frames;

    // Frame counter reached the target frame count
    while (clock->frame_counter >= clock->frames[clock->target_frame_index]) {
        printf("Target reached: %d >= %d\n", clock->frame_counter, clock->frames[clock->target_frame_index]);

        // Reached max value, reset the sub-clock
        if ((clock->target_frame_index) >= clock->max_target_frame_index) {
            reset_sub_clock(
                clock, 
                clock->frame_counter - clock->frames[clock->max_target_frame_index]
            );
            return;
        }

        emit_sub_clock_tick_event(clock, clock->values[clock->target_frame_index++]);
    }
}

void free_sub_clock(Sub_Clock* clock)
{
    if (clock != NULL) {
        free(clock);
    }
}
