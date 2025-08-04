#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "cse4733/process.hpp"
#include "cse4733/round_robin.hpp"

using namespace cse4733;
using ::testing::_;
using ::testing::AtLeast;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::ReturnPointee;
using ::testing::SaveArg;

class RoundRobinTest : public ::testing::Test
{
protected:
    std::vector<std::shared_ptr<IProcess>> processes;
    round_robin scheduler;
    int quantum;

    void SetUp() override
    {
        quantum = 2; // Quantum time
    }
};

TEST_F(RoundRobinTest, ProcessCompletion)
{
    // Mock get and set for completion, waiting, and turnaround times
    int remainingTime1 = 15;
    int completionTime1 = 15;
    int burstTime1 = 15;
    int arrivalTime1 = 0;
    int turnaroundTime1 = completionTime1 - arrivalTime1;
    int waitingTime1 = turnaroundTime1 - burstTime1;

    // Create mock processes
    auto process1 = std::make_shared<Process>(0, burstTime1, arrivalTime1);

    processes = {process1};

    // Run the scheduler
    scheduler.run(processes, quantum);

    // Check the final state of process1
    // The exact values here depend on the behavior of your scheduler
    EXPECT_GE(process1->get_completion_time(), completionTime1); // Completion time should be at least the burst time
    EXPECT_GE(process1->get_turnaround_time(), turnaroundTime1); // Turnaround time should be at least the burst time
    EXPECT_GE(process1->get_waiting_time(), waitingTime1);       // Waiting time should be non-negative
}

TEST_F(RoundRobinTest, ProcessCompletionSix)
{
    // Mock get and set for completion, waiting, and turnaround times
    int quantum = 2; // Quantum time

    // Process 1
    int completionTime1 = 55;
    int burstTime1 = 15;
    int arrivalTime1 = 0;
    int turnaroundTime1 = completionTime1 - arrivalTime1;
    int waitingTime1 = turnaroundTime1 - burstTime1;
    auto process1 = std::make_shared<Process>(0, burstTime1, arrivalTime1);

    // Process 2
    int completionTime2 = 44;
    int burstTime2 = 10;
    int arrivalTime2 = 1; // Unique arrival time
    int turnaroundTime2 = completionTime2 - arrivalTime2;
    int waitingTime2 = turnaroundTime2 - burstTime2;
    auto process2 = std::make_shared<Process>(1, burstTime2, arrivalTime2);

    // Process 3
    int completionTime3 = 29;
    int burstTime3 = 5;
    int arrivalTime3 = 2; // Unique arrival time
    int turnaroundTime3 = completionTime3 - arrivalTime3;
    int waitingTime3 = turnaroundTime3 - burstTime3;
    auto process3 = std::make_shared<Process>(2, burstTime3, arrivalTime3);

    // Process 4
    int completionTime4 = 30;
    int burstTime4 = 5;
    int arrivalTime4 = 3; // Unique arrival time
    int turnaroundTime4 = completionTime4 - arrivalTime4;
    int waitingTime4 = turnaroundTime4 - burstTime4;
    auto process4 = std::make_shared<Process>(3, burstTime4, arrivalTime4);

    // Process 5
    int completionTime5 = 32;
    int burstTime5 = 6;
    int arrivalTime5 = 4; // Unique arrival time
    int turnaroundTime5 = completionTime5 - arrivalTime5;
    int waitingTime5 = turnaroundTime5 - burstTime5;
    auto process5 = std::make_shared<Process>(4, burstTime5, arrivalTime5);

    // Process 6
    int completionTime6 = 59;
    int burstTime6 = 18;
    int arrivalTime6 = 5; // Unique arrival time
    int turnaroundTime6 = completionTime6 - arrivalTime6;
    int waitingTime6 = turnaroundTime6 - burstTime6;
    auto process6 = std::make_shared<Process>(5, burstTime6, arrivalTime6);

    processes = {process1, process2, process3, process4, process5, process6};

    // Run the scheduler
    // Run the scheduler
    scheduler.run(processes, quantum);

    // Verify the final state of each process
    EXPECT_EQ(processes[0]->get_completion_time(), completionTime1);
    EXPECT_EQ(processes[0]->get_turnaround_time(), turnaroundTime1);
    EXPECT_EQ(processes[0]->get_waiting_time(), waitingTime1);

    EXPECT_EQ(processes[1]->get_completion_time(), completionTime2);
    EXPECT_EQ(processes[1]->get_turnaround_time(), turnaroundTime2);
    EXPECT_EQ(processes[1]->get_waiting_time(), waitingTime2);

    EXPECT_EQ(processes[2]->get_completion_time(), completionTime3);
    EXPECT_EQ(processes[2]->get_turnaround_time(), turnaroundTime3);
    EXPECT_EQ(processes[2]->get_waiting_time(), waitingTime3);

    EXPECT_EQ(processes[3]->get_completion_time(), completionTime4);
    EXPECT_EQ(processes[3]->get_turnaround_time(), turnaroundTime4);
    EXPECT_EQ(processes[3]->get_waiting_time(), waitingTime4);

    EXPECT_EQ(processes[4]->get_completion_time(), completionTime5);
    EXPECT_EQ(processes[4]->get_turnaround_time(), turnaroundTime5);
    EXPECT_EQ(processes[4]->get_waiting_time(), waitingTime5);

    EXPECT_EQ(processes[5]->get_completion_time(), completionTime6);
    EXPECT_EQ(processes[5]->get_turnaround_time(), turnaroundTime6);
    EXPECT_EQ(processes[5]->get_waiting_time(), waitingTime6);
}


// Test for process 8 with quantum value of 3
TEST_F(RoundRobinTest, ProcessCompletionEight_Quantum3)
{
    // Mock get and set for completion, waiting, and turnaround times
    int remainingTime8 = 1;
    int completionTime8 = 5;
    int burstTime8 = 5;
    int arrivalTime8 = 7; // Unique arrival time
    int turnaroundTime8 = completionTime8 - arrivalTime8;
    int waitingTime8 = turnaroundTime8 - burstTime8;
    auto process8 = std::make_shared<Process>(8, burstTime8, arrivalTime8);

    processes = {process8};

    int quantum3 = 3; // Quantum time of 3

    // Run the scheduler with quantum value of 3
    scheduler.run(processes, quantum3);

    // Verify the final state of process8
    EXPECT_EQ(process8->get_completion_time(), completionTime8);
    EXPECT_EQ(process8->get_turnaround_time(), turnaroundTime8);
    EXPECT_EQ(process8->get_waiting_time(), waitingTime8);
}

TEST_F(RoundRobinTest, RunTest3)
{
    // Mock get and set for completion, waiting, and turnaround times
    int remainingTime1 = 10;
    int completionTime1 = 28;
    int burstTime1 = 10;
    int arrivalTime1 = 0;
    int turnaroundTime1 = completionTime1 - arrivalTime1;
    int waitingTime1 = turnaroundTime1 - burstTime1;
    auto process1 = std::make_shared<Process>(1, burstTime1, arrivalTime1);

    // Mock get and set for completion, waiting, and turnaround times
    int remainingTime2 = 5;
    int completionTime2 = 20;
    int burstTime2 = 5;
    int arrivalTime2 = 1;
    int turnaroundTime2 = completionTime2 - arrivalTime2;
    int waitingTime2 = turnaroundTime2 - burstTime2;
    auto process2 = std::make_shared<Process>(2, burstTime2, arrivalTime2);

    int remainingTime3 = 8;
    int completionTime3 = 26;
    int burstTime3 = 8;
    int arrivalTime3 = 2;
    int turnaroundTime3 = completionTime3 - arrivalTime3;
    int waitingTime3 = turnaroundTime3 - burstTime3;
    auto process3 = std::make_shared<Process>(3, burstTime3, arrivalTime3);

    int remainingTime4 = 2;
    int completionTime4 = 8;
    int burstTime4 = 2;
    int arrivalTime4 = 3;
    int turnaroundTime4 = completionTime4 - arrivalTime4;
    int waitingTime4 = turnaroundTime4 - burstTime4;
    auto process4 = std::make_shared<Process>(4, burstTime4, arrivalTime4);

    int remainingTime5 = 3;
    int completionTime5 = 17;
    int burstTime5 = 3;
    int arrivalTime5 = 4;
    int turnaroundTime5 = completionTime5 - arrivalTime5;
    int waitingTime5 = turnaroundTime5   - burstTime5;
    auto process5 = std::make_shared<Process>(5, burstTime5, arrivalTime5);

    // Create a vector of processes
    std::vector<std::shared_ptr<IProcess>> processes = {process1, process2, process3, process4, process5};

    // Create an instance of the first_come_first_served scheduler
    round_robin scheduler;

    // Call the run() method
    scheduler.run(processes, quantum);

    // Verify the final state of each process
    EXPECT_EQ(processes[0]->get_completion_time(), completionTime1);
    EXPECT_EQ(processes[0]->get_turnaround_time(), turnaroundTime1);
    EXPECT_EQ(processes[0]->get_waiting_time(), waitingTime1);

    EXPECT_EQ(processes[1]->get_completion_time(), completionTime2);
    EXPECT_EQ(processes[1]->get_turnaround_time(), turnaroundTime2);
    EXPECT_EQ(processes[1]->get_waiting_time(), waitingTime2);

    EXPECT_EQ(processes[2]->get_completion_time(), completionTime3);
    EXPECT_EQ(processes[2]->get_turnaround_time(), turnaroundTime3);
    EXPECT_EQ(processes[2]->get_waiting_time(), waitingTime3);

    EXPECT_EQ(processes[3]->get_completion_time(), completionTime4);
    EXPECT_EQ(processes[3]->get_turnaround_time(), turnaroundTime4);
    EXPECT_EQ(processes[3]->get_waiting_time(), waitingTime4);

    EXPECT_EQ(processes[4]->get_completion_time(), completionTime5);
    EXPECT_EQ(processes[4]->get_turnaround_time(), turnaroundTime5);
    EXPECT_EQ(processes[4]->get_waiting_time(), waitingTime5);
}