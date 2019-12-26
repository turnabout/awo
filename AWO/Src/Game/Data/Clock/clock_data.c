#include <stdlib.h>

#include "Game/Data/Clock/clock_data.h"

PRAGMA( warning(disable: 6001) );

typedef struct Animation_Clock_Data {

    // Changing frames
    Uint8* frames;

    // Corresponding values
    Uint8* values;
    Uint8 value_count;

} Animation_Clock_Data;

struct Clock_Data {
    Animation_Clock_Data* clocks[ANIMATION_CLOCK_COUNT];
};

void gather_clock_data(
    Clock_Data* clock_data,
    Animation_Clock_Index index, 
    Uint8** frames, 
    Uint8** values, 
    Uint8* value_count
)
{
    Animation_Clock_Data* data = clock_data->clocks[index];

    if (frames != NULL) {
        *frames = data->frames;
    }

    if (values != NULL) {
        *values = data->values;
    }

    if (value_count != NULL) {
        *value_count = data->value_count;
    }
}

Animation_Clock_Data* create_animation_clock_data(cJSON* clock_JSON)
{
    Animation_Clock_Data* data = malloc(sizeof(Animation_Clock_Data));

    cJSON* frames_JSON = cJSON_GetObjectItemCaseSensitive(clock_JSON, "frames");
    cJSON* values_JSON = cJSON_GetObjectItemCaseSensitive(clock_JSON, "values");

    data->value_count = cJSON_GetArraySize(values_JSON);

    // Frame count should be the value count + 1 (last frame resets to first frame/value)
    if (cJSON_GetArraySize(frames_JSON) != (data->value_count + 1)) {
        free(data);
        // TODO: error
        return NULL;
    }

    // Store frames & values
    data->frames = malloc(sizeof(Uint8) * data->value_count + 1);
    data->values = malloc(sizeof(Uint8) * data->value_count);

    for (int i = 0; i < data->value_count; i++) {
        data->values[i] = cJSON_GetArrayItem(values_JSON, i)->valueint;
        data->frames[i] = cJSON_GetArrayItem(frames_JSON, i)->valueint;
    }

    data->frames[data->value_count] = cJSON_GetArrayItem(frames_JSON, data->value_count)->valueint;
    return data;
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

        if (clock_data->clocks[i]->frames != NULL) {
            free(clock_data->clocks[i]->frames);
        }

        if (clock_data->clocks[i]->values != NULL) {
            free(clock_data->clocks[i]->values);
        }

        free(clock_data->clocks[i]);
    }

    free(clock_data);
}