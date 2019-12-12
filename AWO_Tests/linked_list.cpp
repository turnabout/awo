#include "pch.h"

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

    // List values
    int a = 1, b = 2, c = 3, d = 4;
    int* values[4] = {&a, &b, &c, &d};
    int elements_sum = a + b + c + d;

    // Lists
    Linked_List* empty_list;
    Linked_List* list;
};

void loop_empty_linked_list(void* element, void* additional_value)
{
    FAIL() << "List is not empty";
}

void loop_filled_linked_list(void* element, void* elements_sum)
{
    *((int*)elements_sum) += *((int*)element);
}
TEST_F(Linked_List_Test, create_linked_list)
{
    // Create a linked list with no values
    Linked_List* created_list = create_linked_list(NULL, 0);

    loop_linked_list(created_list, loop_empty_linked_list, NULL);
    free_linked_list(created_list);

    // Create a linked list with values
    int calculated_elements_sum = 0;

    created_list = create_linked_list((void**)values, 4);

    loop_linked_list(created_list, loop_filled_linked_list, &calculated_elements_sum);

    EXPECT_EQ(calculated_elements_sum, elements_sum);
    free_linked_list(created_list);
}

TEST_F(Linked_List_Test, get_linked_list_nth_item)
{
    int* res;

    res = (int*)get_linked_list_nth_element(list, 0);
    EXPECT_EQ(*res, a);

    res = (int*)get_linked_list_nth_element(list, 1);
    EXPECT_EQ(*res, b);

    res = (int*)get_linked_list_nth_element(list, 2);
    EXPECT_EQ(*res, c);

    res = (int*)get_linked_list_nth_element(list, 3);
    EXPECT_EQ(*res, d);

    res = (int*)get_linked_list_nth_element(list, 4);
    EXPECT_TRUE(res == NULL);
}

void find_linked_list_deleted_item(void* element, void* deleted_value)
{
    EXPECT_NE(*((int*)element), *((int*)deleted_value)) << "Element supposed to have been deleted";
}
TEST_F(Linked_List_Test, delete_linked_list_item)
{
    // Delete first element
    int calculated_elements_sum = 0;

    delete_linked_list_item(list, &a);
    loop_linked_list(list, find_linked_list_deleted_item, &a);
    loop_linked_list(list, loop_filled_linked_list, &calculated_elements_sum);

    EXPECT_EQ(calculated_elements_sum, elements_sum - a);

    // Delete second element
    TearDown();
    SetUp();

    calculated_elements_sum = 0;

    delete_linked_list_item(list, &b);
    loop_linked_list(list, find_linked_list_deleted_item, &b);
    loop_linked_list(list, loop_filled_linked_list, &calculated_elements_sum);

    EXPECT_EQ(calculated_elements_sum, elements_sum - b);

    // Delete last element
    TearDown();
    SetUp();

    calculated_elements_sum = 0;

    delete_linked_list_item(list, &d);
    loop_linked_list(list, find_linked_list_deleted_item, &d);
    loop_linked_list(list, loop_filled_linked_list, &calculated_elements_sum);

    EXPECT_EQ(calculated_elements_sum, elements_sum - d);

    // Delete all elements
    TearDown();
    SetUp();

    delete_linked_list_item(list, &a);
    delete_linked_list_item(list, &b);
    delete_linked_list_item(list, &c);
    delete_linked_list_item(list, &d);

    loop_linked_list(list, loop_empty_linked_list, NULL);
}
