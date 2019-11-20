#include <stdlib.h>

#include "Game/Data/Tile/Property_Tile/_property_tiles_data.h"

Property_Type_Data* create_property_type_data(cJSON* property_type_JSON, int ss_w, int ss_h)
{
    Property_Type_Data* property_type_data = (Property_Type_Data*)malloc(
        sizeof(Property_Type_Data)
    );

    // Loop weather variations
    cJSON* property_weather_var_JSON;
    Weather weather = WEATHER_FIRST;
    cJSON_ArrayForEach(property_weather_var_JSON, property_type_JSON)
    {
        property_type_data->army_variation_count = cJSON_GetArraySize(property_weather_var_JSON);

        property_type_data->frames[weather] = (Frame**)malloc(
            sizeof(Frame*) * property_type_data->army_variation_count
        );

        // Loop army variations
        cJSON* army_var_JSON;
        Army_Type army_variation = ARMY_TYPE_FIRST;
        
        cJSON_ArrayForEach(army_var_JSON, property_weather_var_JSON)
        {
            property_type_data->frames[weather][army_variation++] = create_frame(
                army_var_JSON,
                ss_w,
                ss_h
            );
        }

        weather++;
    }

    return property_type_data;
}

Property_Tiles_Data* create_property_tiles_data(cJSON* properties_data_JSON, int ss_width, int ss_height)
{
    Property_Tiles_Data* data = (Property_Tiles_Data*)malloc(sizeof(Property_Tiles_Data));

    // Loop property types & populate properties source data
    Property_Type property_type = PROPERTY_TYPE_FIRST;
    cJSON* src_JSON = cJSON_GetObjectItemCaseSensitive(properties_data_JSON, "src");
    cJSON* property_type_JSON;
    cJSON_ArrayForEach(property_type_JSON, src_JSON)
    {
        data->src[property_type++] = create_property_type_data(
            property_type_JSON, 
            ss_width,
            ss_height
        );
    }

    return data;
}