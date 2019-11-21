#pragma warning( disable: 6001 )

#include <stdlib.h>

#include "Utilities/Linked_List/_list_entry.h"

List_Entry* add_list_entry(List_Entry* list_tail, void* value)
{
    List_Entry* new_entry = (List_Entry*)malloc(sizeof(List_Entry*));

    new_entry->value = value;
    new_entry->next = NULL;

    if (list_tail) {
        list_tail->next = new_entry;
    }

    return new_entry;
}

void delete_list_entry(List_Entry** list_head, void* value)
{
    List_Entry** pp = list_head;
    List_Entry* entry;

    while ((entry = *pp) != NULL) {
        if (entry->value == value) {
            *pp = entry->next;
            free(*pp);
        } else {
            pp = &entry->next;
        }
    }
}