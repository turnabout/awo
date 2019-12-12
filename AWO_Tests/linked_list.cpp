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

    EXPECT_EQ(a, *(int*)get_linked_list_nth_element(list, 0));
    EXPECT_EQ(b, *(int*)get_linked_list_nth_element(list, 1));
    EXPECT_EQ(c, *(int*)get_linked_list_nth_element(list, 2));
    EXPECT_EQ(d, *(int*)get_linked_list_nth_element(list, 3));
}

TEST_F(Linked_List_Test, get_linked_list_nth_item)
{
    EXPECT_EQ(*(int*)get_linked_list_nth_element(list, 0), a);
    EXPECT_EQ(*(int*)get_linked_list_nth_element(list, 1), b);
    EXPECT_EQ(*(int*)get_linked_list_nth_element(list, 2), c);
    EXPECT_EQ(*(int*)get_linked_list_nth_element(list, 3), d);
    EXPECT_TRUE(get_linked_list_nth_element(list, 4) == NULL);
}

void find_linked_list_deleted_item(void* element, void* deleted_value)
{
    EXPECT_NE(*((int*)element), *((int*)deleted_value)) << "Element supposed to have been deleted";
}
TEST_F(Linked_List_Test, delete_linked_list_item)
{
    // Delete first element - expected result: b-c-d
    delete_linked_list_item(list, &a);

    EXPECT_EQ(b, *(int*)get_linked_list_nth_element(list, 0));
    EXPECT_EQ(c, *(int*)get_linked_list_nth_element(list, 1));
    EXPECT_EQ(d, *(int*)get_linked_list_nth_element(list, 2));
    EXPECT_TRUE(get_linked_list_nth_element(list, 3) == NULL);
    Reset();

    // Delete second element - expected result: a-c-d
    delete_linked_list_item(list, &b);

    EXPECT_EQ(a, *(int*)get_linked_list_nth_element(list, 0));
    EXPECT_EQ(c, *(int*)get_linked_list_nth_element(list, 1));
    EXPECT_EQ(d, *(int*)get_linked_list_nth_element(list, 2));
    EXPECT_TRUE(get_linked_list_nth_element(list, 3) == NULL);
    Reset();

    // Delete last element - expected result: a-b-c
    delete_linked_list_item(list, &d);

    EXPECT_EQ(a, *(int*)get_linked_list_nth_element(list, 0));
    EXPECT_EQ(b, *(int*)get_linked_list_nth_element(list, 1));
    EXPECT_EQ(c, *(int*)get_linked_list_nth_element(list, 2));
    EXPECT_TRUE(get_linked_list_nth_element(list, 3) == NULL);
    Reset();

    // Delete first and last elements - expected result: b-c
    delete_linked_list_item(list, &a);
    delete_linked_list_item(list, &d);

    EXPECT_EQ(b, *(int*)get_linked_list_nth_element(list, 0));
    EXPECT_EQ(c, *(int*)get_linked_list_nth_element(list, 1));
    EXPECT_TRUE(get_linked_list_nth_element(list, 2) == NULL);
    EXPECT_TRUE(get_linked_list_nth_element(list, 3) == NULL);
    Reset();

    // Delete all elements
    delete_linked_list_item(list, &a);
    delete_linked_list_item(list, &b);
    delete_linked_list_item(list, &c);
    delete_linked_list_item(list, &d);

    loop_linked_list(list, check_empty_linked_list, NULL);
}
