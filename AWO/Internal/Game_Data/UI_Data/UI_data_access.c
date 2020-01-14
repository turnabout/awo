#include <stdlib.h>

#include "Game/Data/UI/_UI_data.h"

Animation* get_UI_element_frames(UI_Data* UI_data, UI_Element_Type element)
{
    if (element < UI_ELEMENT_FIRST || element > UI_ELEMENT_LAST) {
        return NULL;
    }

    return UI_data->elements[element];
}

void free_UI_data(UI_Data* UI_data)
{
    if (UI_data != NULL) {
        for (UI_Element_Type el = UI_ELEMENT_FIRST; el < UI_ELEMENT_COUNT; el++) {
            free_animation(UI_data->elements[el]);
        }

        free(UI_data);
    }
}
