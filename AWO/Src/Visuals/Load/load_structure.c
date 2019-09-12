#include <stdio.h>

#include "JSON.h"
#include "../../conf.h"

int load_visuals_data_structure(void)
{
    // Load visuals JSON contents into cJSON struct
    cJSON* visuals_JSON;

    if (load_visuals_JSON(&visuals_JSON) == ERR) {
        return ERR;
    }

    // Load cJSON into the visuals data structure
    printf("%s", cJSON_Print(visuals_JSON));

    return OK;
}