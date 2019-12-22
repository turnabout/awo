#pragma once

#include <cJSON.h>

#include "Game/Data/Clock/enums.h"

typedef struct Clock_Data Clock_Data;

Clock_Data* create_clock_data(cJSON* clock_data_JSON);

void free_clock_data(Clock_Data* clock_data);