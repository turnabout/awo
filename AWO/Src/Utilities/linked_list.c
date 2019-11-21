#include <stdlib.h>

#include "Utilities/linked_list.h"

struct List_Entry {
    void* value;
    List_Entry* next;
};

// Create a new list entry and append after `current`
List_Entry* add_list_entry(List_Entry* current, void* value)
{
    List_Entry* new_node = (List_Entry*)malloc(sizeof(List_Entry*));

    new_node->value = value;
    new_node->next = NULL;

    if (current) {
        current->next = new_node;
    }

    return new_node;
}

List_Entry* create_linked_list(void* values[], size_t values_count)
{
    if (values_count == 0) {
        return NULL;
    }

    List_Entry* list_entry = NULL;
    List_Entry* head = list_entry = add_list_entry(list_entry, values[0]);

    for (size_t i = 1; i < values_count; i++) {
        list_entry = add_list_entry(list_entry, values[i]);
    }

    return head;
}

void add_linked_list_item(List_Entry* list_head, void* value)
{
}

void remove_linked_list_item(List_Entry* list_head, void* value)
{
    List_Entry** pp = &list_head;
    while (*pp != NULL) {
        if ((*pp)->value == value) {
            (*pp) = (*pp)->next;
        } else {
            pp = &((*pp)->next);
        }
    }
}

void free_linked_list(List_Entry* list_head)
{
}
