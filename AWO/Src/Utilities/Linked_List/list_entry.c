#include <stdlib.h>

#include "Utilities/macros.h"
#include "Utilities/Linked_List/list_entry.h"

PRAGMA(warning( disable: 6001 ))

List_Entry* add_list_entry(List_Entry* list_tail, void* value)
{
    List_Entry* new_entry = (List_Entry*)malloc(sizeof(List_Entry*));

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

void delete_list_entry(List_Entry** list_head, void* value)
{
    List_Entry** pp = list_head;
    List_Entry* entry;

    while ((entry = *pp) != NULL) {
        if (entry->element == value) {
            *pp = entry->next;
            free(*pp);
        } else {
            pp = &entry->next;
        }
    }
}