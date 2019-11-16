#include <stdlib.h>

#include "Game/Data/Property/_properties_data.h"

Property_Type_Data* create_property_type_data(cJSON* property_type_JSON, int ss_w, int ss_h)
{
    Property_Type_Data* property_type = (Property_Type_Data*)malloc(sizeof(Property_Type_Data));

    // Loop weather variations
    cJSON* property_weather_var_JSON;
    cJSON_ArrayForEach(property_weather_var_JSON, property_type_JSON)
    {
        property_type->army_variation_count = cJSON_GetArraySize(property_weather_var_JSON);

        // Loop army variations
        cJSON* army_var_JSON;
        cJSON_ArrayForEach(army_var_JSON, property_weather_var_JSON)
        {
            printf("%s\n\n", cJSON_Print(army_var_JSON));
        }
    }

    return property_type;
}

Properties_Data* create_properties_data(cJSON* properties_data_JSON, int ss_width, int ss_height)
{
    Properties_Data* data = (Properties_Data*)malloc(sizeof(Properties_Data));

    // Gather all data from JSON
    Property_Type property_type = PROPERTY_TYPE_FIRST;

    // Loop property types
    cJSON* src_JSON = cJSON_GetObjectItemCaseSensitive(properties_data_JSON, "src");
    cJSON* property_type_JSON;
    cJSON_ArrayForEach(property_type_JSON, src_JSON)
    {
        printf("%d - %s\n", property_type, property_type_str[property_type]);

        /*
        data->src[property_type++] = create_property_type_data(
            property_type_JSON, 
            ss_width,
            ss_height
        );
        */
    }

    return data;
}