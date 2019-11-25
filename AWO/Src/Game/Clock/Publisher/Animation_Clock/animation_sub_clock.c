#include <stdlib.h>

#include "Game/Clock/Publisher/Animation_Clock/_animation_sub_clock.h"

Animation_Sub_Clock* create_animation_sub_clock(
    const cJSON* JSON,
    Animation_Clock_Index clock_index,
    Animation_Sub_Clock_Index sub_clock_index,
    Game_Clock_Pub_Sub_Service* pub_sub_service
)
{
    Animation_Sub_Clock* sub_clock = (Animation_Sub_Clock*)malloc(sizeof(Animation_Sub_Clock));

    sub_clock->previous_tick_value = 0;
    sub_clock->clock_index = clock_index;
    sub_clock->sub_clock_index = sub_clock_index;
    sub_clock->pub_sub_service = pub_sub_service;

    // Build up the sub-clock's tick array
    int ticks_count = cJSON_GetArraySize(JSON);

    sub_clock->ticks_array = malloc(sizeof(Uint8) * ticks_count);

    for (int i = 0; i < ticks_count; i++) {
        sub_clock->ticks_array[i] = cJSON_GetArrayItem(JSON, i)->valueint;
    }

    return sub_clock;
}

void tick_animation_sub_clock(
    Animation_Sub_Clock* sub_clock, 
    int ac_current_tick,
    Tick_Events_List* event_list
)
{
    // Only register tick event if new tick value is different from the previous one
    if (sub_clock->ticks_array[ac_current_tick] != sub_clock->previous_tick_value) {

        // Register tick event
        event_list->ticks[event_list->ticks_count].clock_index = sub_clock->clock_index;
        event_list->ticks[event_list->ticks_count].sub_clock_index = sub_clock->sub_clock_index;
        event_list->ticks[event_list->ticks_count].frame_index = sub_clock->ticks_array[ac_current_tick];

        event_list->ticks_count++;

        // Record the previous tick value
        sub_clock->previous_tick_value = sub_clock->ticks_array[ac_current_tick];
    }
}

void free_animation_sub_clock(Animation_Sub_Clock* sub_clock)
{
    free(sub_clock->ticks_array);
    free(sub_clock);
}
