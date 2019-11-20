#include <stdlib.h>

#include "Game/Player/CO/CO.h"

CO* create_CO(CO_Type co_type)
{
    CO* co = (CO*)malloc(sizeof(CO));

    co->name = co_type_str[co_type];

    // TODO: get from game data
    co->army = OS;

    return co;
}

void free_CO(CO* co)
{
    free(co);
}
