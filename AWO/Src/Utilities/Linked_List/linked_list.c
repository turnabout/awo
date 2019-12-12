#include <stdio.h>
#include <stdlib.h>

#include "Utilities/macros.h"
#include "Utilities/Linked_List/linked_list.h"
#include "Utilities/Linked_List/list_entry.h"

PRAGMA(warning( disable: 6001 ))

struct Linked_List {
    List_Entry* head;
    List_Entry* tail;
};

Linked_List* create_linked_list(void* values[], size_t values_count)
{
    Linked_List* list = malloc(sizeof(Linked_List));

    if (values_count == 0) {
        list->head = NULL;
        list->tail = NULL;
        return list;
    }

    List_Entry* list_entry = NULL;
    list->head = list_entry = add_list_entry(list_entry, values[0]);

    for (size_t i = 1; i < values_count; i++) {
        list_entry = add_list_entry(list_entry, values[i]);
    }

    list->tail = list_entry;

    return list;
}

void loop_linked_list(Linked_List* list, loop_linked_list_cb cb, void* additional_value)
{
    List_Entry** pp = &list->head;

    while (*pp != NULL) {
        cb((*pp)->element, additional_value);
        pp = &((*pp)->next);
    }
}

void append_linked_list_item(Linked_List* list, void* value)
{
    list->tail = add_list_entry(list->tail, value);

    // Tail is also head
    if (list->head == NULL) {
        list->head = list->tail;
    }
}

// Find the tail of the linked list and store it as such.
void update_linked_list_tail(Linked_List* list)
{
    // List is empty (has no head)
    if (list->head == NULL) {
        list->tail = NULL;
        return;
    }

    // List has only 1 element (head is also tail)
    if (list->head->next == NULL) {
        list->tail = list->head;
        return;
    }

    // Get the last element linked to the head & set as tail
    list->tail = get_list_entry_tail(list->head);
}

void* get_linked_list_nth_element(Linked_List* list, int n)
{
    List_Entry* entry = list->head;

    for (int i = 0; entry != NULL; i++) {
        if (i == n) {
            return entry->element;
        }

        entry = entry->next;
    }

    return NULL;
}

void delete_linked_list_item(Linked_List* list, void* value)
{
    delete_list_entry(&list->head, value);
    update_linked_list_tail(list);
}

void free_linked_list(Linked_List* list)
{
    if (list == NULL) {
        return;
    }

    List_Entry* entry = list->head;

    while (entry != NULL) {
        List_Entry* next = entry->next;
        free(entry);
        entry = next;
    }

    free(list);
}
