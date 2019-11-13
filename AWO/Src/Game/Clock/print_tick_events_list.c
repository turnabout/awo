#include <stdio.h>

#include "Game/Clock/_game_clock.h"

void print_tick_events_list(Tick_Events_List* tick_events_list)
{
    printf("Tick_Event_List [\n");

    for (int i = 0; i < tick_events_list->ticks_count; i++) {

        // Temporary test
        const char* clock_str = "?";
        const char* sub_clock_str = "?";

        int clock_index = tick_events_list->ticks[i].clock_index;
        int sub_clock_index = tick_events_list->ticks[i].sub_clock_index;

        switch (clock_index) {
        case 0:
            clock_str = "Sea clock";

            if (sub_clock_index == 0) {
                sub_clock_str = "Pyramid1";
            } else if (sub_clock_index == 1) {
                sub_clock_str = "Pyramid2";
            } else {
                sub_clock_str = "Ten";
            }

            break;
        case 1:
            clock_str = "River clock";

            if (sub_clock_index == 0) {
                sub_clock_str = "Eight";
            }

            break;
        case 2:
            clock_str = "Units clock";

            if (sub_clock_index == 0) {
                sub_clock_str = "Pyramid_3_Frames";
            }
            
            break;
        }
        printf(
            "\tTick_Event { %-16s - %-16s  Frame %d}\n",
            clock_str,
            sub_clock_str,
            tick_events_list->ticks[i].frame_index
        );
    }

    printf("\n]\n\n");

}
