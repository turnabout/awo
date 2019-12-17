#include <stdlib.h>
#include <string.h>

#include "Game/Data/CO/_CO_data.h"

CO_Type_Data* create_CO_type_data(cJSON* CO_type_JSON)
{
    CO_Type_Data* CO_type_data = malloc(sizeof(CO_Type_Data));

    // Army
    CO_type_data->army = cJSON_GetObjectItemCaseSensitive(CO_type_JSON, "army")->valueint;

    // Name
    char* CO_name = cJSON_GetObjectItemCaseSensitive(CO_type_JSON, "name")->valuestring;
    int name_len = strlen(CO_name);

    CO_type_data->name = malloc(name_len * sizeof(char));
    strcpy(CO_type_data->name, CO_name);

    // Frames
    // TODO: get frames

    return CO_type_data;
}

CO_Data* create_CO_data(cJSON* CO_JSON, int ss_width, int ss_height)
{
    CO_Data* CO_data = malloc(sizeof(CO_Data));

    cJSON* CO_type_JSON;
    CO_Type current_CO = CO_First;

    cJSON_ArrayForEach(CO_type_JSON, CO_JSON)
    {
        CO_data->COs[current_CO++] = create_CO_type_data(CO_type_JSON);
    }

    return CO_data;
}
