#include <stdio.h>

#include "Game/Clock/_game_clock.h"

void print_tick_events_list(Tick_Events_List* tick_events_list)
{
    printf("Tick_Event_List [\n");

    for (int i = 0; i < tick_events_list->ticks_count; i++) {
        printf(
            "\tTick_Event { Clock: %-16s, Value: %d}\n",
            clock_str[tick_events_list->ticks[i].clock_index],
            tick_events_list->ticks[i].value
        );
    }

    printf("\n]\n\n");

}
