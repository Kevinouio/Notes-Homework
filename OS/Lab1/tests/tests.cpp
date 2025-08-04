#include <gtest/gtest.h>

// Include the header file for the class/functions you want to test

// Example test case
TEST(ProcessExampleTest, ExampleTest) {
    // Write your test assertions
    ASSERT_EQ(2 + 2, 4);
}

int main(int argc, char** argv) {
    // Initialize Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // Run all the tests
    return RUN_ALL_TESTS();
}

