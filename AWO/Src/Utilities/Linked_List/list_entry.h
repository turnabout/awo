#pragma once
#include <stdlib.h>

#include "types.h"

typedef struct List_Entry List_Entry;

struct List_Entry {
    void* element;
    List_Entry* next;
};

/*! @brief Creates a new list entry and append after the given `current` list entry.
 */
List_Entry* add_list_entry(List_Entry* list_tail, void* value);

/*! @brief Returns the last element in a list of entries.
 */
List_Entry* get_list_entry_tail(List_Entry* list_head);

/*! @brief Deletes the list entry found with the given value, starting at the given list head.
 *  @return TRUE if the list entry was found and delete, FALSE if it wasn't.
 */
Bool delete_list_entry(List_Entry** list_head, void* value);
