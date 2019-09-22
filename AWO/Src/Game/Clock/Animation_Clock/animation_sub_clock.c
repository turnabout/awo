#include <stdlib.h>

#include "_animation_clock_internal.h"

#pragma warning( disable: 6011 6386 )

Animation_Sub_Clock* ASC_create_from_JSON(const cJSON* json)
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

void ASC_update(Animation_Sub_Clock* asc, int ac_current_tick)
{
    asc->current_tick = asc->ticks_array[ac_current_tick];
}

void ASC_free(Animation_Sub_Clock* asc)
{
    free(asc->ticks_array);
    free(asc->current_tick);
    free(asc);
}

int* ASC_get_tick_ptr(Animation_Sub_Clock* asc)
{
    return &asc->current_tick;
}
