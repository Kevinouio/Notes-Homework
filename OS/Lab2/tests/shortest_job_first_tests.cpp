#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "cse4733/process.hpp"
#include "cse4733/shortest_job_first.hpp"

using namespace cse4733;
using ::testing::_;
using ::testing::Return;
using ::testing::SaveArg;

class ShortestJobFirstTest : public ::testing::Test
{
protected:
    std::vector<std::shared_ptr<IProcess>> processes;
    shortest_job_first scheduler;
};

// Test case for first_come_first_served::run() method
TEST_F(ShortestJobFirstTest, RunTest)
{
    // Mock get and set for completion, waiting, and turnaround times
    int completionTime1 = 30;
    int burstTime1 = 15;
    int arrivalTime1 = 0;
    int turnaroundTime1 = completionTime1 - arrivalTime1;
    int waitingTime1 = turnaroundTime1 - burstTime1;
    auto process1 = std::make_shared<Process>(1, burstTime1, arrivalTime1);

    // Mock get and set for completion, waiting, and turnaround times
    int completionTime2 = 15;
    int burstTime2 = 9;
    int arrivalTime2 = 0;
    int turnaroundTime2 = completionTime2 - arrivalTime2;
    int waitingTime2 = turnaroundTime2 - burstTime2;
    auto process2 = std::make_shared<Process>(2, burstTime2, arrivalTime2);

    // Process 3
    int completionTime3 = 6;
    int burstTime3 = 6;
    int arrivalTime3 = 0; // Unique arrival time
    int turnaroundTime3 = completionTime3 - arrivalTime3;
    int waitingTime3 = turnaroundTime3 - burstTime3;
    auto process3 = std::make_shared<Process>(3, burstTime3, arrivalTime3);

    // Populate the processes vector with MockProcess objects
    processes = {process1, process2, process3};

    // Call the run() method
    scheduler.run(processes);

    // Verify the final state of each process
    EXPECT_EQ(processes[0]->get_completion_time(), completionTime3);
    EXPECT_EQ(processes[0]->get_turnaround_time(), turnaroundTime3);
    EXPECT_EQ(processes[0]->get_waiting_time(), waitingTime3);

    EXPECT_EQ(processes[1]->get_completion_time(), completionTime2);
    EXPECT_EQ(processes[1]->get_turnaround_time(), turnaroundTime2);
    EXPECT_EQ(processes[1]->get_waiting_time(), waitingTime2);

    EXPECT_EQ(processes[2]->get_completion_time(), completionTime1);
    EXPECT_EQ(processes[2]->get_turnaround_time(), turnaroundTime1);
    EXPECT_EQ(processes[2]->get_waiting_time(), waitingTime1);
}

// Test case for first_come_first_served::run() method
TEST_F(ShortestJobFirstTest, RunTest2)
{
    int completionTime1 = 28;
    int burstTime1 = 10;
    int arrivalTime1 = 0;
    int turnaroundTime1 = completionTime1 - arrivalTime1;
    int waitingTime1 = turnaroundTime1 - burstTime1;
    auto process1 = std::make_shared<Process>(1, burstTime1, arrivalTime1);

    int completionTime2 = 10;
    int burstTime2 = 5;
    int arrivalTime2 = 1;
    int turnaroundTime2 = completionTime2 - arrivalTime2;
    int waitingTime2 = turnaroundTime2 - burstTime2;
    auto process2 = std::make_shared<Process>(2, burstTime2, arrivalTime2);

    int completionTime3 = 18;
    int burstTime3 = 8;
    int arrivalTime3 = 2;
    int turnaroundTime3 = completionTime3 - arrivalTime3;
    int waitingTime3 = turnaroundTime3 - burstTime3;
    auto process3 = std::make_shared<Process>(3, burstTime3, arrivalTime3);

    int completionTime4 = 2;
    int burstTime4 = 2;
    int arrivalTime4 = 3;
    int turnaroundTime4 = completionTime4 - arrivalTime4;
    int waitingTime4 = turnaroundTime4 - burstTime4;
    auto process4 = std::make_shared<Process>(4, burstTime4, arrivalTime4);

    int completionTime5 = 5;
    int burstTime5 = 3;
    int arrivalTime5 = 4;
    int turnaroundTime5 = completionTime5 - arrivalTime5;
    int waitingTime5 = turnaroundTime5 - burstTime5;
    auto process5 = std::make_shared<Process>(5, burstTime5, arrivalTime5);

    // Create a vector of processes
    processes = {process1, process2, process3, process4, process5};

    // Call the run() method
    scheduler.run(processes);

    // Verify the final state of each process
    EXPECT_EQ(processes[0]->get_completion_time(), completionTime4);
    EXPECT_EQ(processes[0]->get_turnaround_time(), turnaroundTime4);
    EXPECT_EQ(processes[0]->get_waiting_time(), waitingTime4);

    EXPECT_EQ(processes[1]->get_completion_time(), completionTime5);
    EXPECT_EQ(processes[1]->get_turnaround_time(), turnaroundTime5);
    EXPECT_EQ(processes[1]->get_waiting_time(), waitingTime5);

    EXPECT_EQ(processes[2]->get_completion_time(), completionTime2);
    EXPECT_EQ(processes[2]->get_turnaround_time(), turnaroundTime2);
    EXPECT_EQ(processes[2]->get_waiting_time(), waitingTime2);

    // Verify the final state of process4
    EXPECT_EQ(processes[3]->get_completion_time(), completionTime3);
    EXPECT_EQ(processes[3]->get_turnaround_time(), turnaroundTime3);
    EXPECT_EQ(processes[3]->get_waiting_time(), waitingTime3);

    // Verify the final state of process5//
    EXPECT_EQ(processes[4]->get_completion_time(), completionTime1);
    EXPECT_EQ(processes[4]->get_turnaround_time(), turnaroundTime1);
    EXPECT_EQ(processes[4]->get_waiting_time(), waitingTime1);

    // Call the run() method
    scheduler.run(processes);
}