#pragma once

/*! @brief Single entry in a linked list holding generic pointers for values.
 */
typedef struct List_Entry List_Entry;

/*! @brief Creates a linked list from the given values.
 *  @param[in] values Array containing generic pointers to place in the new linked list.
 *  @param[in] values_count How many values are to be added to the new list.
 *  @return The head of the newly created linked list.
 */
List_Entry* create_linked_list(void* values[], size_t values_count);

void add_linked_list_item(List_Entry* list_head, void* value);

void remove_linked_list_item(List_Entry* list_head, void* value);

void free_linked_list(List_Entry* list_head);
