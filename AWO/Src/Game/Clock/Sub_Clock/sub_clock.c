#include <stdlib.h>

#include "Game/Clock/Sub_Clock/sub_clock.h"

struct Sub_Clock {

    // Changing frames
    Uint8* frames;

    // Corresponding values
    Uint8* values;
    Uint8 value_count;
};

Sub_Clock* create_sub_clock(Clock_Data* clock_data, Animation_Clock_Index index)
{
    Sub_Clock* clock = malloc(sizeof(Sub_Clock));

    gather_clock_data(
        clock_data, 
        index, 
        &clock->frames, 
        &clock->values, 
        &clock->value_count
    );

    return clock;
}

void update_sub_clock(Sub_Clock* clock, unsigned int passed_frames)
{
}

void free_sub_clock(Sub_Clock* clock)
{
    if (clock != NULL) {
        free(clock);
    }
}
