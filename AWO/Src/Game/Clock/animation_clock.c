#include <stdlib.h>

#include "_animation_clock_internal.h"

Animation_Clock* AC_create_from_JSON(const cJSON* json)
{
    Animation_Clock* ac = malloc(sizeof(Animation_Clock));

    return ac;
}

void AC_update(Animation_Clock* animation_clock, int game_clock_tick)
{
}
