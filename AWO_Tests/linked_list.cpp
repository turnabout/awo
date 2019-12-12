#include "pch.h"

extern "C" {
#include "Utilities/Linked_List/linked_list.h"
}

class Linked_List_Test : public ::testing::Test {
    protected:
    void SetUp() override {
        empty_list = create_linked_list(NULL, 0);
        filled_list = create_linked_list((void**)values, 4);
    }

    void TearDown() override {
        free_linked_list(filled_list);
        free_linked_list(empty_list);
    }

    // List values
    int a = 1, b = 2, c = 3, d = 4;
    int* values[4] = {&a, &b, &c, &d};

    // Lists
    Linked_List* empty_list;
    Linked_List* filled_list;
};

void loop_empty_linked_list(void* element, void* additional_value)
{
    FAIL() << "List is not empty";
}

void loop_filled_linked_list(void* element, void* calculated_sum)
{
    *((int*)calculated_sum) += *((int*)element);
}
TEST_F(Linked_List_Test, create_linked_list)
{
    // Create a linked list with no values
    Linked_List* list = create_linked_list(NULL, 0);

    loop_linked_list(list, loop_empty_linked_list, NULL);
    free_linked_list(list);

    // Create a linked list with values
    int a = 1, b = 2, c = 3, d = 4;
    int* values[4] = {&a, &b, &c, &d};
    int element_count = a + b + c + d;
    int expected_element_count = 0;

    list = create_linked_list((void**)values, 4);

    loop_linked_list(list, loop_filled_linked_list, &expected_element_count);

    EXPECT_EQ(expected_element_count, element_count);
    free_linked_list(list);
}
