#pragma once

/*! @brief Singly-linked list holding generic pointers as values.
 */
typedef struct Linked_List Linked_List;

/*! @brief Callback type used to loop every element in a linked list.
 */
typedef void (loop_linked_list_cb) (void* value);

/*! @brief Creates a linked list from the given values.
 *
 * If no values are given, an empty linked list is returned.
 *
 *  @param[in] values Array containing generic pointers to place in the new linked list.
 *  @param[in] values_count How many values are to be added to the new list.
 *  @return The created linked list.
 */
Linked_List* create_linked_list(void* values[], size_t values_count);

/*! @brief Loops every item in the given linked list, passing every value it the given callback.
 *
 *  @param[in] list The linked list to loop.
 *  @param[in] cb The callback function given every value.
 */
void loop_linked_list(Linked_List* list, loop_linked_list_cb cb);

/*! @brief Appends a value to a linked list.
 *
 *  @param[in] list The linked list.
 *  @param[in] value The value to add to the list.
 */
void append_linked_list_item(Linked_List* list, void* value);

/*! @brief Deletes a value from a linked list.
 *
 *  @param[in] list The linked list.
 *  @param[in] value The value to remove from the list.
 */
void delete_linked_list_item(Linked_List* list, void* value);

/*! @brief Frees the memory occupied by the linked list and its contents.
 *
 *  @param[in] list The linked list to free.
 */
void free_linked_list(Linked_List* list);