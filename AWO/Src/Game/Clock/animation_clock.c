#include <stdio.h>
#include <stdlib.h>

#include "_animation_clock_internal.h"

#pragma warning( disable: 6011 )
#pragma warning( disable: 6386 )

Animation_Clock* AC_create_from_JSON(const cJSON* json)
{
    Animation_Clock* ac = malloc(sizeof(Animation_Clock));

    cJSON* changing_ticks_JSON = cJSON_GetObjectItemCaseSensitive(json, "changingTicks");
    cJSON* subclocks_JSON = cJSON_GetObjectItemCaseSensitive(json, "subClocks");

    // Set changing ticks
    ac->current_tick = 0;
    ac->changing_ticks_count = cJSON_GetArraySize(changing_ticks_JSON);
    ac->changing_ticks = malloc(sizeof(int) * ac->changing_ticks_count);

    for (int i = 0; i < ac->changing_ticks_count; i++) {
        ac->changing_ticks[i] = cJSON_GetArrayItem(changing_ticks_JSON, i)->valueint;
    }

    // Set animation subclocks
    // TODO

    return ac;
}

void AC_update(Animation_Clock* ac, int game_clock_tick)
{
    for (int i = 0; i < ac->changing_ticks_count; i++) {
        if (game_clock_tick == ac->changing_ticks[i]) {
            ac->current_tick = i;
            printf("%d updating to index %d\n", game_clock_tick, i);
        }
    }
}