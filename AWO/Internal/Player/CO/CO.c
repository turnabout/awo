#include <stdlib.h>

#include "Player/CO/CO.h"

CO* create_CO(CO_Type co_type)
{
    CO* co = malloc(sizeof(CO));

    if (co == NULL) {
        return NULL;
    }

    co->name = co_type_str[co_type];

    // TODO: get from game data
    co->army = OS;

    return co;
}

void free_CO(CO* co)
{
    free(co);
}
