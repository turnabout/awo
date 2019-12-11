#include "pch.h"

extern "C" {
#include "Utilities/Linked_List/linked_list.h"
}

class Linked_List_Test : public ::testing::Test {
    protected:
    void SetUp() override {
        value = 1;
    }

    // void TearDown() override {}

    int value = 0;
};

TEST_F(Linked_List_Test, create_linked_list)
{
    Linked_List* list = create_linked_list(NULL, 0);

    EXPECT_TRUE(list != NULL);

    /*
    int a = 1, b = 2, c = 3, d = 4;
    int* values[4] = {&a, &b, &c, &d};

    Linked_List* list = create_linked_list((void**)values, 4);


    EXPECT_TRUE(list == NULL);
    EXPECT_TRUE(list == NULL);
    EXPECT_EQ(value, 1) << "Error";
    EXPECT_TRUE(true);
    */
}
