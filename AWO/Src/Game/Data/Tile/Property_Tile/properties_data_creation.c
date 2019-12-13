#include <stdlib.h>

#include "types.h"
#include "Game/Data/Tile/Property_Tile/_property_tiles_data.h"

Property_Type_Data* create_property_type_data(
    cJSON* property_type_JSON, 
    int ss_w, 
    int ss_h, 
    Bool empty
)
{
    Property_Type_Data* property_type_data = malloc(
        sizeof(Property_Type_Data)
    );

    property_type_data->army_variation_count = cJSON_GetArraySize(property_type_JSON);

    // Loop army variations
    cJSON* army_var_JSON;
    Army_Type army_variation = ARMY_TYPE_FIRST;

    cJSON_ArrayForEach(army_var_JSON, property_type_JSON)
    {
        if (empty) {
            property_type_data->frames[army_variation++] = malloc(sizeof(Frame));
        } else {
            property_type_data->frames[army_variation++] = create_frame(
                army_var_JSON,
                ss_w,
                ss_h
            );
        }
    }

    return property_type_data;
}

Property_Tiles_Data* create_property_tiles_data(cJSON* properties_data_JSON, int ss_width, int ss_height)
{
    Property_Tiles_Data* data = malloc(sizeof(Property_Tiles_Data));

    cJSON* src_JSON = cJSON_GetObjectItemCaseSensitive(properties_data_JSON, "src");

    // Loop weather variations
    Weather weather = WEATHER_FIRST;
    cJSON* property_weather_var_JSON;
    cJSON_ArrayForEach(property_weather_var_JSON, src_JSON)
    {
        // Loop property types
        Property_Type property_type = PROPERTY_TYPE_FIRST;
        cJSON* property_type_JSON;
        cJSON_ArrayForEach(property_type_JSON, property_weather_var_JSON)
        {
            if (weather == WEATHER_FIRST) {
                data->active_src[property_type] = create_property_type_data(
                    property_type_JSON,
                    ss_width,
                    ss_height,
                    TRUE
                );
            }

            data->src[weather][property_type++] = create_property_type_data(
                property_type_JSON,
                ss_width,
                ss_height,
                FALSE
            );
        }

        weather++;
    }

    return data;
}