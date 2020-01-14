#include <stdlib.h>

#include "Linked_List/list_entry.h"

List_Entry* add_list_entry(List_Entry* list_tail, void* value)
{
    List_Entry* new_entry = malloc(sizeof(List_Entry));

    new_entry->element = value;
    new_entry->next = NULL;

    if (list_tail) {
        list_tail->next = new_entry;
    }

    return new_entry;
}

List_Entry* get_list_entry_tail(List_Entry* list_head)
{
    List_Entry* entry = list_head;

    while (1) {
        if (entry->next == NULL) {
            return entry;
        }

        entry = entry->next;
    }
}

Bool delete_list_entry(List_Entry** list_head, void* value, Bool free_data)
{
    List_Entry** p = list_head;

    // Traverse list until element to delete was found, or entire list was looped
    while (*p && (**p).element != value) {
        p = &(*p)->next;
    }

    // Delete element if it was found
    if (p) {
        List_Entry* deleted_entry = *p;

        *p = deleted_entry->next;
        deleted_entry->next = NULL;

        if (free_data) {
            free(deleted_entry);
        }

        return TRUE;
    }

    return FALSE;
}