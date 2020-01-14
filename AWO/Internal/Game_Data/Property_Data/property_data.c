#include <stdlib.h>

#include "Utilities/utilities.h"
#include "Game_Data/Property_Data/_property_data.h"

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

Property_Tiles_Data* create_property_tiles_data(
    cJSON* properties_data_JSON, 
    int ss_width, 
    int ss_height
)
{
    Property_Tiles_Data* data = malloc(sizeof(Property_Tiles_Data));

    // Loop weather variations
    Weather weather = WEATHER_FIRST;
    cJSON* property_weather_var_JSON;
    cJSON_ArrayForEach(property_weather_var_JSON, properties_data_JSON)
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

void free_property_type_data(Property_Type_Data* prop_type_data)
{
    if (prop_type_data == NULL) {
        return;
    }

    for (int i = 0; i < prop_type_data->army_variation_count; i++) {
        free_frame(prop_type_data->frames[i]);
    }

    free(prop_type_data);
}

void free_properties_data(Property_Tiles_Data* property_data)
{
    if (property_data == NULL) {
        return;
    }

    for (Weather weather = WEATHER_FIRST; weather < PROPERTY_WEATHER_COUNT; weather++) {
        for (Property_Type type = PROPERTY_TYPE_FIRST; type < PROPERTY_TYPE_COUNT; type++) {
            if (weather == WEATHER_FIRST) {
                free_property_type_data(property_data->active_src[type]);
            }

            free_property_type_data(property_data->src[weather][type]);
        }
    }

    free(property_data);
}