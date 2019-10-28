#include <stdlib.h>

#include "Game/Clock/Animation_Clock/_animation_clock.h"

Animation_Sub_Clock* create_animation_sub_clock_from_JSON(const cJSON* json)
{
    Animation_Sub_Clock* asc = (Animation_Sub_Clock*)malloc(sizeof(Animation_Sub_Clock));

    asc->current_tick = 0;

    // Build up the sub-clock's tick array
    int ticks_count = cJSON_GetArraySize(json);

    asc->ticks_array = malloc(sizeof(int) * ticks_count);

    for (int i = 0; i < ticks_count; i++) {
        asc->ticks_array[i] = cJSON_GetArrayItem(json, i)->valueint;
    }

    return asc;
}

void update_animation_sub_clock(Animation_Sub_Clock* asc, int ac_current_tick)
{
    asc->current_tick = asc->ticks_array[ac_current_tick];
}

void free_animation_sub_clock(Animation_Sub_Clock* asc)
{
    free(asc->ticks_array);
    free(asc);
}

int* get_animation_sub_clock_tick_ptr(Animation_Sub_Clock* asc)
{
    return &asc->current_tick;
}
