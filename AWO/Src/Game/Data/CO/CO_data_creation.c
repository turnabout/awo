#include <stdlib.h>
#include <string.h>

#include "Game/Data/CO/_CO_data.h"

CO_Type_Data* create_CO_type_data(cJSON* co_type_JSON, int ss_width, int ss_height)
{
    CO_Type_Data* co_type_data = malloc(sizeof(CO_Type_Data));

    // Army
    co_type_data->army = cJSON_GetObjectItemCaseSensitive(co_type_JSON, "army")->valueint;

    // Name
    char* co_name = cJSON_GetObjectItemCaseSensitive(co_type_JSON, "name")->valuestring;
    int name_len = strlen(co_name);

    co_type_data->name = malloc((name_len + 1) * sizeof(char));
    strcpy(co_type_data->name, co_name);

    // Frames
    co_type_data->frames = create_animation(
        cJSON_GetObjectItemCaseSensitive(co_type_JSON, "frames"),
        ss_width,
        ss_height
    );

    return co_type_data;
}

CO_Data* create_CO_data(cJSON* CO_JSON, int ss_width, int ss_height)
{
    CO_Data* CO_data = malloc(sizeof(CO_Data));

    cJSON* CO_type_JSON;
    CO_Type current_CO = CO_FIRST;

    cJSON_ArrayForEach(CO_type_JSON, CO_JSON)
    {
        CO_data->COs[current_CO++] = create_CO_type_data(CO_type_JSON, ss_width, ss_height);
    }

    return CO_data;
}
