#include "pch.h"

#define LIST_CONTAINS(list, expected, index) EXPECT_EQ(expected, *(int*)get_linked_list_nth_element(list, index))
#define LIST_ITEM_NULL(list, index) EXPECT_TRUE(get_linked_list_nth_element(list, index) == NULL)

extern "C" {
#include "Utilities/Linked_List/linked_list.h"
}

class Linked_List_Test : public ::testing::Test {
    protected:
    void SetUp() override {
        empty_list = create_linked_list(NULL, 0);
        list = create_linked_list((void**)values, 4);
    }

    void TearDown() override {
        free_linked_list(list);
        free_linked_list(empty_list);
    }

    void Reset() {
        TearDown();
        SetUp();
    }

    // List values
    int a = 1, b = 2, c = 3, d = 4;
    int* values[4] = {&a, &b, &c, &d};

    // Lists
    Linked_List* empty_list;
    Linked_List* list;
};

void check_empty_linked_list(void* element, void* additional_value)
{
    FAIL() << "List is not empty" << std::endl;
}

TEST_F(Linked_List_Test, create_linked_list)
{
    // Test the lists created in SetUp()
    loop_linked_list(empty_list, check_empty_linked_list, NULL);

    LIST_CONTAINS(list, a, 0);
    LIST_CONTAINS(list, b, 1);
    LIST_CONTAINS(list, c, 2);
    LIST_CONTAINS(list, d, 3);
    LIST_ITEM_NULL(list, 4);
}

void find_linked_list_deleted_item(void* element, void* deleted_value)
{
    EXPECT_NE(*((int*)element), *((int*)deleted_value)) << "Element supposed to have been deleted";
}

TEST_F(Linked_List_Test, delete_linked_list_item)
{
    // Delete first element - expected result: b-c-d
    delete_linked_list_item(list, &a);

    LIST_CONTAINS(list, b, 0);
    LIST_CONTAINS(list, c, 1);
    LIST_CONTAINS(list, d, 2);
    LIST_ITEM_NULL(list, 3);
    Reset();

    // Delete second element - expected result: a-c-d
    delete_linked_list_item(list, &b);

    LIST_CONTAINS(list, a, 0);
    LIST_CONTAINS(list, c, 1);
    LIST_CONTAINS(list, d, 2);
    LIST_ITEM_NULL(list, 3);
    Reset();

    // Delete last element - expected result: a-b-c
    delete_linked_list_item(list, &d);

    LIST_CONTAINS(list, a, 0);
    LIST_CONTAINS(list, b, 1);
    LIST_CONTAINS(list, c, 2);
    LIST_ITEM_NULL(list, 3);
    Reset();

    // Delete first and last elements - expected result: b-c
    delete_linked_list_item(list, &a);
    delete_linked_list_item(list, &d);

    LIST_CONTAINS(list, b, 0);
    LIST_CONTAINS(list, c, 1);
    LIST_ITEM_NULL(list, 2);
    LIST_ITEM_NULL(list, 3);
    Reset();

    // Delete all elements
    delete_linked_list_item(list, &a);
    delete_linked_list_item(list, &b);
    delete_linked_list_item(list, &c);
    delete_linked_list_item(list, &d);

    loop_linked_list(list, check_empty_linked_list, NULL);
}
