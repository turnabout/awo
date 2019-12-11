#include "pch.h"
#include "Utilities/Linked_List/linked_list.h"

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
    Linked_List* list = NULL;

    EXPECT_TRUE(list == NULL);
    EXPECT_EQ(value, 1) << "Error";
    EXPECT_TRUE(true);
}
