#pragma once
#include <stdlib.h>

typedef struct List_Entry List_Entry;

struct List_Entry {
    void* value;
    List_Entry* next;
};

/*! @brief Creates a new list entry and append after the given `current` list entry.
 */
List_Entry* add_list_entry(List_Entry* list_tail, void* value);

/*! @brief Deletes the list entry found with the given value, starting at the given list head.
 */
void delete_list_entry(List_Entry** list_head, void* value);
