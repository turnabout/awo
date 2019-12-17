#include <stdlib.h>

#include "Game/Data/CO/_CO_data.h"

void free_CO_type_data(CO_Type_Data* CO_type_data)
{
    if (CO_type_data != NULL) {
        if (CO_type_data->name != NULL) {
            free(CO_type_data->name);
        }

        // TODO: free frames

        free(CO_type_data);
    }
}

void free_CO_data(CO_Data* CO_data)
{
    if (CO_data != NULL) {
        for (CO_Type CO = CO_First; CO < CO_Count; CO++) {
            free_CO_type_data(CO_data->COs[CO]);
        }

        free(CO_data);
    }
}