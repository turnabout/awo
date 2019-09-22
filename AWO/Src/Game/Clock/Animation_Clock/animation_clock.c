#include <stdlib.h>

#include "_animation_clock_internal.h"

#pragma warning( disable: 6011 6386 )

Animation_Clock* AC_create_from_JSON(const cJSON* json)
{
    Animation_Clock* ac = malloc(sizeof(Animation_Clock));

    // Set changing ticks
    const cJSON* changing_ticks_JSON = cJSON_GetObjectItemCaseSensitive(json, "changingTicks");

    ac->current_tick = 0;
    ac->changing_ticks_count = cJSON_GetArraySize(changing_ticks_JSON);
    ac->changing_ticks = malloc(sizeof(int) * ac->changing_ticks_count);

    for (int i = 0; i < ac->changing_ticks_count; i++) {
        ac->changing_ticks[i] = cJSON_GetArrayItem(changing_ticks_JSON, i)->valueint;
    }

    // Set animation sub-clocks
    const cJSON* sub_clocks_JSON = cJSON_GetObjectItemCaseSensitive(json, "subClocks");
    int sub_clocks_count = cJSON_GetArraySize(sub_clocks_JSON);

    ac->sub_clocks = malloc(sizeof(Animation_Sub_Clock*) * sub_clocks_count);

    // Add every sub-clock to this animation clock
    for (int i = 0; i < sub_clocks_count; i++) {
        *(ac->sub_clocks++) = ASC_create_from_JSON( cJSON_GetArrayItem(sub_clocks_JSON, i) );
    }

    // Reset to first sub-clock pointer
    ac->sub_clocks -= sub_clocks_count;
    ac->sub_clocks_count = sub_clocks_count;

    return ac;
}

void AC_update_sub_clocks(Animation_Clock* ac)
{
    for (int i = 0; i < ac->sub_clocks_count; i++) {
        ASC_update(ac->sub_clocks[i], ac->current_tick);
    }
}

void AC_update(Animation_Clock* ac, int game_clock_tick)
{
    for (int i = 0; i < ac->changing_ticks_count; i++) {

        // Update tick if a game clock tick is found amongst changing ticks
        if (game_clock_tick == ac->changing_ticks[i]) {
            ac->current_tick = i;

            // Animation clock update, so update its sub-clocks
            AC_update_sub_clocks(ac);
        }
    }
}

void AC_free(Animation_Clock* ac)
{
    for (int i = 0; i < ac->sub_clocks_count; i++) {
        ASC_free(ac->sub_clocks[i]);
    }

    free(ac->changing_ticks);
    free(ac->sub_clocks);
    free(ac);
}