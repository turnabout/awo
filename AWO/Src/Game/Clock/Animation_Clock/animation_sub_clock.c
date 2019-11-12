#include <stdlib.h>

#include "Game/Clock/Animation_Clock/_animation_sub_clock.h"

Animation_Sub_Clock* create_animation_sub_clock(
    const cJSON* JSON,
    Animation_Clock_Index clock_index,
    Animation_Sub_Clock_Index sub_clock_index
)
{
    Animation_Sub_Clock* sub_clock = (Animation_Sub_Clock*)malloc(sizeof(Animation_Sub_Clock));

    sub_clock->current_tick = 0;
    sub_clock->clock_index = clock_index;
    sub_clock->sub_clock_index = sub_clock_index;

    // Build up the sub-clock's tick array
    int ticks_count = cJSON_GetArraySize(JSON);

    sub_clock->ticks_array = malloc(sizeof(int) * ticks_count);

    for (int i = 0; i < ticks_count; i++) {
        sub_clock->ticks_array[i] = cJSON_GetArrayItem(JSON, i)->valueint;
    }

    return sub_clock;
}

void update_animation_sub_clock(
    Animation_Sub_Clock* sub_clock, 
    int ac_current_tick,
    Tick_Event_List* event_list
)
{
    event_list->ticks[event_list->ticks_count].clock_index = sub_clock->clock_index;
    event_list->ticks[event_list->ticks_count].sub_clock_index = sub_clock->sub_clock_index;
    event_list->ticks[event_list->ticks_count].frame_index = sub_clock->ticks_array[ac_current_tick];
    event_list->ticks_count++;
}

void free_animation_sub_clock(Animation_Sub_Clock* sub_clock)
{
    free(sub_clock->ticks_array);
    free(sub_clock);
}

int* get_animation_sub_clock_tick_ptr(Animation_Sub_Clock* sub_clock)
{
    return &sub_clock->current_tick;
}
