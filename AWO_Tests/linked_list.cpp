#include "pch.h"

// Macro for checking the contents of a list in one line
#define EXPECT_LIST_CONTENTS(list, vals_count, vals) \
    int UNIQUE_NAME(base)[] = vals; \
    expect_list_contents(list, UNIQUE_NAME(base), vals_count);

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
    int temp_values_list[100];

    // Lists
    Linked_List* empty_list;
    Linked_List* list;
};

void check_empty_linked_list(void* element, void* additional_value)
{
    FAIL() << "List should be empty" << std::endl;
}

void expect_list_empty(Linked_List* list)
{
    loop_linked_list(list, check_empty_linked_list, NULL);
}

void expect_list_contents(Linked_List* list, int values[], int values_count)
{
    int i = 0, unexpected = -1;

    // Verify every value in the linked list
    for (i = 0; i < values_count; i++) {
        int list_val = *(int*)get_linked_list_nth_element(list, i);

        if (values[i] != list_val) {
            unexpected = list_val;
            break;
        }
    }

    // Print custom error message if unexpected value was found
    if (unexpected != -1) {
        std::cerr << "Unexpected value '" << unexpected << "' in list[" << i << "]";
        std::cerr << ", should be '" << values[i] << "'" << std::endl;

        int invalid_val_index = i;
        for (i = 0; i < values_count; i++) {

            if (i == invalid_val_index) {
                std::cerr << "v";
            } else {
                std::cerr << "   ";
            }
        }

        std::cerr << std::endl;

        for (i = 0; i < values_count; i++) {
            std::cerr << values[i] << ", ";
        }

        FAIL() << std::endl;
    }

    // Ensure no element exists past the given values
    if (get_linked_list_nth_element(list, i) != NULL) {
        int found_val = *(int*)get_linked_list_nth_element(list, i);

        std::cerr << "Found element '" << found_val << "' in list[" << i << "], should only have ";
        std::cerr << values_count << " elements" << std::endl;
        FAIL();
    }
}

TEST_F(Linked_List_Test, create_linked_list)
{
    // Test the lists created in SetUp()
    expect_list_empty(empty_list);
    EXPECT_LIST_CONTENTS(list, 4, _ARR({ a, b, c, d }));
}

TEST_F(Linked_List_Test, append_linked_list_item)
{
    // Expected: a-b
    append_linked_list_item(empty_list, &a);
    append_linked_list_item(empty_list, &b);

    EXPECT_LIST_CONTENTS(empty_list, 2, _ARR({ a, b}));

    // Expected: a-b-c-d-e-f
    int e = 10, f = 20;
    append_linked_list_item(list, &e);
    append_linked_list_item(list, &f);

    EXPECT_LIST_CONTENTS(list, 6, _ARR({ a, b, c, d, e, f}));
}

TEST_F(Linked_List_Test, delete_linked_list_item)
{
    // Delete first element - expected: b-c-d
    delete_linked_list_item(list, &a);
    EXPECT_LIST_CONTENTS(list, 3, _ARR({b, c, d}));
    Reset();

    // Delete second element - expected: a-c-d
    delete_linked_list_item(list, &b);
    EXPECT_LIST_CONTENTS(list, 3, _ARR({a, c, d}));
    Reset();

    // Delete last element - expected: a-b-c
    delete_linked_list_item(list, &d);
    EXPECT_LIST_CONTENTS(list, 3, _ARR({a, b, c}));
    Reset();

    // Delete first and last elements - expected: b-c
    delete_linked_list_item(list, &a);
    delete_linked_list_item(list, &d);
    EXPECT_LIST_CONTENTS(list, 2, _ARR({b, c}));
    Reset();

    // Delete all elements
    delete_linked_list_item(list, &a);
    delete_linked_list_item(list, &b);
    delete_linked_list_item(list, &c);
    delete_linked_list_item(list, &d);
    expect_list_empty(list);
}

TEST_F(Linked_List_Test, append_delete_linked_list_item)
{
    // Append values - Expected: f-a-b-c-d
    int e = 8, f = 9;

    append_linked_list_item(empty_list, &f);
    append_linked_list_item(empty_list, &a);
    append_linked_list_item(empty_list, &b);
    append_linked_list_item(empty_list, &c);
    append_linked_list_item(empty_list, &d);

    EXPECT_LIST_CONTENTS(empty_list, 5, _ARR({f, a, b, c, d}));

    // Delete b/d - Expected: f-a-c
    delete_linked_list_item(empty_list, &b);
    delete_linked_list_item(empty_list, &d);

    EXPECT_LIST_CONTENTS(empty_list, 3, _ARR({f, a, c}));

    // Append d/b - Expected: f-a-c-d-b
    append_linked_list_item(empty_list, &d);
    append_linked_list_item(empty_list, &b);

    EXPECT_LIST_CONTENTS(empty_list, 5, _ARR({f, a, c, d, b}));

    // Delete f/b - Expected: a-c-d
    delete_linked_list_item(empty_list, &f);
    delete_linked_list_item(empty_list, &b);

    EXPECT_LIST_CONTENTS(empty_list, 3, _ARR({a, c, d}));
}
