#include <stdlib.h>

#include "Game/Data/Property/_properties_data.h"

Properties_Data* create_properties_data(cJSON* properties_data_JSON, int ss_width, int ss_height)
{
    Properties_Data* data = (Properties_Data*)malloc(sizeof(Properties_Data));

    // Gather all data from JSON
    Property_Type property_type = PROPERTY_TYPE_FIRST;

    // Loop tile types
    cJSON* src_JSON = cJSON_GetObjectItemCaseSensitive(properties_data_JSON, "src");
    cJSON* property_type_JSON;
    cJSON_ArrayForEach(property_type_JSON, src_JSON)
    {
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