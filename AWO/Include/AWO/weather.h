#pragma once

#include "Include/macros.h"

// Game weathers
#define FOREACH_WEATHER(WEATHER) \
    WEATHER(Clear) \
    WEATHER(Snow) \
    WEATHER(Rain) \

typedef enum {FOREACH_WEATHER(GENERATE_ENUM)} Weather;
static const char* weather_str[] = {FOREACH_WEATHER(GENERATE_STRING)};

#define WEATHER_FIRST Clear
#define WEATHER_LAST Rain
#define WEATHER_COUNT WEATHER_LAST + 1
#define WEATHER_DEFAULT WEATHER_FIRST

// Count of weathers used in property data (Clear/Snow)
#define PROPERTY_WEATHER_COUNT 2