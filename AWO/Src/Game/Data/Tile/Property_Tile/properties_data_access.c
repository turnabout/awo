#include <stdlib.h>

#include "Game/Data/Tile/Property_Tile/_property_tiles_data.h"
#include "Game/Data/Tile/_tiles_data.h"

Frame* get_property_frame(
    Tiles_Data* tiles_data, 
    Property_Type property_type, 
    Weather weather_variation, 
    Unit_Variation army_variation
)
{
    // If given army variation doesn't exist on unit type, return data for default variation
    Unit_Variation used_army_variation = 
        (army_variation < tiles_data->property_tiles->src[property_type]->army_variation_count)
            ? army_variation
            : UNIT_VAR_FIRST;

    // If given weather variation doesn't exist, return data for default weather
    Weather used_weather =
        (weather_variation < PROPERTY_WEATHER_COUNT)
            ? weather_variation
            : WEATHER_FIRST;

    return tiles_data->property_tiles->src[property_type]->frames[used_weather][used_army_variation];
}

void free_properties_data(Tiles_Data* tiles_data)
{
    for (Property_Type type = PROPERTY_TYPE_FIRST; type < PROPERTY_TYPE_COUNT; type++) {
        for (Weather weather = WEATHER_FIRST; weather < PROPERTY_WEATHER_COUNT; weather++) {
            free(tiles_data->property_tiles->src[type]->frames[weather]);
        }

        free(tiles_data->property_tiles->src[type]);
    }

    free(tiles_data->property_tiles);
}
