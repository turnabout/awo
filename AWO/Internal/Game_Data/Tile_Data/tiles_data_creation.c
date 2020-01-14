#include <stdlib.h>

#include "Game/Data/Tile/_tiles_data.h"

Tiles_Data* create_tiles_data(
    cJSON* neutral_tiles_JSON,
    cJSON* property_tiles_JSON,
    int ss_width,
    int ss_height
)
{
    Tiles_Data* tiles_data = malloc(sizeof(Tiles_Data));

    tiles_data->neutral_tiles = create_neutral_tiles_data(neutral_tiles_JSON, ss_width, ss_height);
    tiles_data->property_tiles = create_property_tiles_data(property_tiles_JSON, ss_width, ss_height);

    // Initialize the active property weather variation
    update_tiles_data_active_property_weather_var(tiles_data, WEATHER_DEFAULT);

    return tiles_data;
}
