#pragma once

#include <cJSON.h>

#include "Utilities/utilities.h"
#include "Headers/clock_types.h"
#include "Include/Game_Data/game_data.h"

Clock_Data* create_clock_data(cJSON* clock_data_JSON);

void gather_clock_data(
    Clock_Data* clock_data,
    Clock_Index index,
    Uint8** frames,
    Uint8** values,
    Uint8* value_count
);

void free_clock_data(Clock_Data* clock_data);