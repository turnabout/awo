#include <stdlib.h>

#include "Game/Clock/Publisher/Animation_Clock/_animation_clock.h"

Animation_Clock* create_animation_clock(
    const cJSON* JSON,
    Animation_Clock_Index clock_index,
    Game_Clock_Pub_Sub* pub_sub_service
)
{
    Animation_Clock* clock = malloc(sizeof(Animation_Clock));

    // Set changing ticks
    const cJSON* changing_ticks_JSON = cJSON_GetObjectItemCaseSensitive(JSON, "changingTicks");

    clock->current_tick = 0;
    clock->changing_ticks_count = cJSON_GetArraySize(changing_ticks_JSON);
    clock->changing_ticks = malloc(sizeof(int) * clock->changing_ticks_count);

    for (int i = 0; i < clock->changing_ticks_count; i++) {
        clock->changing_ticks[i] = cJSON_GetArrayItem(changing_ticks_JSON, i)->valueint;
    }

    // Set animation sub-clocks
    const cJSON* sub_clocks_JSON = cJSON_GetObjectItemCaseSensitive(JSON, "subClocks");
    int sub_clocks_count = cJSON_GetArraySize(sub_clocks_JSON);

    clock->sub_clocks = malloc(sizeof(Animation_Sub_Clock*) * sub_clocks_count);

    // Add every sub-clock to this animation clock
    for (int i = 0; i < sub_clocks_count; i++) {
        *(clock->sub_clocks++) = create_animation_sub_clock(
            cJSON_GetArrayItem(sub_clocks_JSON, i),
            clock_index,
            (Animation_Sub_Clock_Index)i,
            pub_sub_service
        );
    }

    // Reset to first sub-clock pointer
    clock->sub_clocks -= sub_clocks_count;
    clock->sub_clocks_count = sub_clocks_count;

    return clock;
}

void update_animation_clock_children(Animation_Clock* animation_clock)
{
    for (int i = 0; i < animation_clock->sub_clocks_count; i++) {
        tick_animation_sub_clock(animation_clock->sub_clocks[i], animation_clock->current_tick);
    }
}

void update_animation_clock(Animation_Clock* animation_clock, int game_clock_tick)
{
    for (int i = 0; i < animation_clock->changing_ticks_count; i++) {

        // Update tick if a game clock tick is found amongst changing ticks
        if (game_clock_tick == animation_clock->changing_ticks[i]) {
            animation_clock->current_tick = i;

            // Animation clock update, so update its sub-clocks
            update_animation_clock_children(animation_clock);
        }
    }
}

void free_animation_clock(Animation_Clock* ac)
{
    for (int i = 0; i < ac->sub_clocks_count; i++) {
        free_animation_sub_clock(ac->sub_clocks[i]);
    }

    free(ac->changing_ticks);
    free(ac->sub_clocks);
    free(ac);
}
