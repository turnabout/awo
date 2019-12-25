#include <stdlib.h>

#include "types.h"
#include "Game/Data/Clock/clock_data.h"

PRAGMA( warning(disable: 6001) );

typedef struct Animation_Clock_Data {



    // Changing ticks
    int* changing_ticks;
    int changing_ticks_count;

    // Child sub-clocks
    Uint8** sub_clocks_tick_arrays;
    int sub_clock_count;

} Animation_Clock_Data;

struct Clock_Data {

    // Data for each animation clock.
    Animation_Clock_Data* clocks[ANIMATION_CLOCK_COUNT];

};

Animation_Clock_Data* create_animation_clock_data(cJSON* JSON)
{
    /*
    Animation_Clock_Data* data = malloc(sizeof(Animation_Clock_Data));

    // Store changing ticks data
    cJSON* changing_ticks_JSON = cJSON_GetObjectItemCaseSensitive(JSON, "changingTicks");

    data->changing_ticks_count = cJSON_GetArraySize(changing_ticks_JSON);
    data->changing_ticks = malloc(sizeof(int) * data->changing_ticks_count);

    for (int i = 0; i < data->changing_ticks_count; i++) {
        data->changing_ticks[i] = cJSON_GetArrayItem(changing_ticks_JSON, i)->valueint;
    }

    // Store sub clock data
    cJSON* sub_clocks_JSON = cJSON_GetObjectItemCaseSensitive(JSON, "subClocks");

    data->sub_clock_count = cJSON_GetArraySize(sub_clocks_JSON);
    data->sub_clocks_tick_arrays = malloc(sizeof(Uint8*) * data->sub_clock_count);

    for (int i = 0; i < data->sub_clock_count; i++) {
        data->sub_clocks_tick_arrays[i] = malloc(sizeof(Uint8) * data->changing_ticks_count);

        cJSON* sub_clock_JSON = cJSON_GetArrayItem(sub_clocks_JSON, i);

        for (int j = 0; j < data->changing_ticks_count; j++) {
            data->sub_clocks_tick_arrays[i][j] = cJSON_GetArrayItem(sub_clock_JSON, j)->valueint;
        }
    }

    return data;
    */
    return NULL;
}

Clock_Data* create_clock_data(cJSON* JSON)
{
    Clock_Data* clock_data = malloc(sizeof(Clock_Data));

    for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        clock_data->clocks[i] = create_animation_clock_data( cJSON_GetArrayItem(JSON, i) );
    }

    return clock_data;
}

void free_clock_data(Clock_Data* clock_data)
{
    if (clock_data == NULL) {
        return;
    }

    // Free animation clocks
    for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        if (clock_data->clocks[i] == NULL) {
            continue;
        }

        /*
        Animation_Clock_Data* anim_clock = clock_data->clocks[i];

        // Free animation clock's sub-clocks
        for (int j = 0; j < anim_clock->sub_clock_count; j++) {
            free(anim_clock->sub_clocks_tick_arrays[j]);
        }

        // Free animation clock
        if (anim_clock->changing_ticks != NULL) {
            free(anim_clock->changing_ticks);
        }

        if (anim_clock->sub_clocks_tick_arrays != NULL) {
            free(anim_clock->sub_clocks_tick_arrays);
        }
        */


        free(clock_data->clocks[i]);
    }

    free(clock_data);
}