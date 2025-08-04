#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cse4733/process.hpp>

using namespace cse4733;

// Test case for get_pid() method
TEST(ProcessTest, GetPidTest) {
    Process process(1, 5, 0);
    EXPECT_EQ(process.get_pid(), 1);
}

// Test case for get_burst_time() method
TEST(ProcessTest, GetBurstTimeTest) {
    Process process(1, 5, 0);
    EXPECT_EQ(process.get_burst_time(), 5);
}

// Test case for set_arrival_time() and get_arrival_time() methods
TEST(ProcessTest, SetAndGetArrivalTimeTest) {
    Process process(1, 5, 0);
    process.set_arrival_time(10);
    EXPECT_EQ(process.get_arrival_time(), 10);
}

// Test case for get_remaining_time() and set_remaining_time() methods
TEST(ProcessTest, GetAndSetRemainingTimeTest) {
    Process process(1, 5, 0);
    process.set_remaining_time(3);
    EXPECT_EQ(process.get_remaining_time(), 3);
}

// Test case for get_turnaround_time() and set_turnaround_time() methods
TEST(ProcessTest, GetAndSetTurnaroundTimeTest) {
    Process process(1, 5, 0);
    process.set_turnaround_time(15);
    EXPECT_EQ(process.get_turnaround_time(), 15);
}

// Test case for get_waiting_time() and set_waiting_time() methods
TEST(ProcessTest, GetAndSetWaitingTimeTest) {
    Process process(1, 5, 0);
    process.set_waiting_time(8);
    EXPECT_EQ(process.get_waiting_time(), 8);
}

// Test case for get_completion_time() and set_completion_time() methods
TEST(ProcessTest, GetAndSetCompletionTimeTest) {
    Process process(1, 5, 0);
    process.set_completion_time(20);
    EXPECT_EQ(process.get_completion_time(), 20);
}

// Test case for to_string() method
TEST(ProcessTest, ToStringTest) {
    Process process(1, 5, 0);
    process.set_completion_time(10);
    process.set_waiting_time(2);
    process.set_turnaround_time(12);

    // Call the to_string() method and check the result
    std::string result = process.to_string();
    std::string expected = "1\t\t10\t\t5\t\t0\t\t2\t\t12";
    EXPECT_EQ(result, expected);
}