#include <stdlib.h>

#include "Game/Data/CO/_CO_data.h"

CO_Data* create_CO_data(cJSON* CO_JSON, int ss_width, int ss_height)
{
    CO_Data* data = malloc(sizeof(CO_Data));

    return data;
}

void free_CO_data(CO_Data* CO_data)
{
    if (CO_data != NULL) {
        free(CO_data);
    }
}
