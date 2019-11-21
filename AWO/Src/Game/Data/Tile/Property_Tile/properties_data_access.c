#include <stdlib.h>

#include "Game/Data/Tile/Property_Tile/_property_tiles_data.h"
#include "Game/Data/Tile/_tiles_data.h"

Property_Type_Data* get_property_type_data(
    Tiles_Data* tiles_data, 
    Weather weather_variation,
    Property_Type property_type
)
{
    // If given weather variation doesn't exist, return data for default weather
    Weather used_weather =
        (weather_variation < PROPERTY_WEATHER_COUNT)
            ? weather_variation
            : WEATHER_FIRST;

    return tiles_data->property_tiles->src[used_weather][property_type];
}

Frame* get_property_type_frame(Property_Type_Data* property_type_data, Army_Type army_variation)
{
    // If given army variation doesn't exist on unit type, return data for default variation
    Army_Type used_army_variation = 
        (army_variation < property_type_data->army_variation_count)
            ? army_variation
            : ARMY_TYPE_FIRST;

    return property_type_data->frames[used_army_variation];
}

void free_properties_data(Tiles_Data* tiles_data)
{
    for (Weather weather = WEATHER_FIRST; weather < PROPERTY_WEATHER_COUNT; weather++) {
        for (Property_Type type = PROPERTY_TYPE_FIRST; type < PROPERTY_TYPE_COUNT; type++) {
            free(tiles_data->property_tiles->src[weather][type]->frames);
            free(tiles_data->property_tiles->src[weather][type]);
        }
    }

    free(tiles_data->property_tiles);
}
