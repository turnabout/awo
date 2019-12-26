#include <stdio.h>

#include "Game/Clock/_game_clock.h"

void print_tick_events_list(Tick_Events_List* tick_events_list)
{
    printf("Tick_Event_List [\n");

    for (int i = 0; i < tick_events_list->ticks_count; i++) {

        // Temporary test
        const char* clock_str = "?";
        const char* sub_clock_str = "?";

        int clock_index = tick_events_list->ticks[i].timer_index;

        printf(
            "\tTick_Event { %-16s - %-16s  Frame %d}\n",
            clock_str,
            sub_clock_str,
            tick_events_list->ticks[i].value
        );
    }

    printf("\n]\n\n");

}
