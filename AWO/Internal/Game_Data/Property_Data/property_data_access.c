#include <stdlib.h>
#include <string.h>

#include "Game_Data/Property_Data/_property_data.h"

void update_tiles_data_active_property_weather_var(
    Property_Tiles_Data* property_data,
    Weather weather_variation
)
{
    Weather used_weather =
        (weather_variation < PROPERTY_WEATHER_COUNT)
            ? weather_variation
            : WEATHER_FIRST;

    // Copy frames data from src to active_src
    Property_Type_Data** from = property_data->src[used_weather];
    Property_Type_Data** to = property_data->active_src;

    for (Property_Type type = PROPERTY_TYPE_FIRST; type < PROPERTY_TYPE_COUNT; type++) {
        for (Army_Type army_type = 0; army_type < from[type]->army_variation_count; army_type++) {
            memcpy(
                to[type]->frames[army_type],
                from[type]->frames[army_type],
                sizeof(Frame)
            );
        }
    }
}

Frame** get_property_type_frame(
    Property_Tiles_Data* property_data,
    Property_Type property_type, 
    Army_Type army_variation
)
{
    // Get the data for the given property type
    Property_Type_Data* prop_type_data = property_data->active_src[property_type];

    // If given army variation doesn't exist on unit type, return data for default variation
    Army_Type used_army_variation = 
        (army_variation < prop_type_data->army_variation_count)
            ? army_variation
            : ARMY_TYPE_FIRST;

    // return &(tiles_data->property_tiles->active_src[0][0]->frames[0]);
    return &(prop_type_data->frames[used_army_variation]);
}
