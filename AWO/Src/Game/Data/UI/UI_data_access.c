#include <stdlib.h>

#include "Game/Data/UI/_UI_data.h"

void free_UI_data(UI_Data* UI_data)
{
    if (UI_data != NULL) {
        for (UI_Element_Type el = UI_ELEMENT_FIRST; el < UI_ELEMENT_COUNT; el++) {
            free_animation(UI_data->elements[el]);
        }

        free(UI_data);
    }
}
