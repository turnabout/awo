#include <stdlib.h>

#include "Game/Data/CO/_CO_data.h"

void free_CO_type_data(CO_Type_Data* co_type_data)
{
    if (co_type_data != NULL) {
        if (co_type_data->name != NULL) {
            free(co_type_data->name);
        }

        free_animation(co_type_data->frames);

        free(co_type_data);
    }
}

void free_CO_data(CO_Data* co_data)
{
    if (co_data != NULL) {
        for (CO_Type co = CO_FIRST; co < CO_COUNT; co++) {
            free_CO_type_data(co_data->COs[co]);
        }

        free(co_data);
    }
}