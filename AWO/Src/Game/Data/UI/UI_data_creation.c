#include <stdlib.h>

#include "Game/Data/UI/_UI_data.h"

UI_Data* create_UI_data(cJSON* UI_JSON, int ss_width, int ss_height)
{
    UI_Data* UI_data = malloc(sizeof(UI_Data));

    cJSON* UI_element_JSON;
    UI_Element_Type current_type = UI_ELEMENT_FIRST;

    cJSON_ArrayForEach(UI_element_JSON, UI_JSON)
    {
        UI_data->elements[current_type++] = create_animation(
            UI_element_JSON,
            ss_width,
            ss_height
        );

    }

    return UI_data;
}
