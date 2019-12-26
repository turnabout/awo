#pragma once

#include <cJSON.h>

#include "types.h"
#include "Game/Data/Clock/enums.h"

typedef struct Clock_Data Clock_Data;

Clock_Data* create_clock_data(cJSON* clock_data_JSON);

void gather_clock_data(
    Clock_Data* clock_data,
    Clock_Index index,
    Uint8** frames,
    Uint8** values,
    Uint8* value_count
);

void free_clock_data(Clock_Data* clock_data);