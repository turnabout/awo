#include <stdlib.h>

#include "Game/Clock/Sub_Clock/sub_clock.h"

struct Sub_Clock {
    int p;
};

Sub_Clock* create_sub_clock(Clock_Data* clock_data)
{
    Sub_Clock* clock = malloc(sizeof(Sub_Clock));

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
