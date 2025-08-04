#include "first_come_first_served.hpp"
#include <queue>
#include <algorithm>
#include <iostream>

namespace cse4733 {

void first_come_first_served::run(std::vector<std::shared_ptr<cse4733::IProcess>>& processes)
{

    int completion_time = 0; // Tracks the current system time
    std::queue<std::shared_ptr<cse4733::IProcess>> ready_queue;


    // TODO:
    //  Get number of processes
    int num_processes = processes.size();

    // Fill the ready queue in the order processes arrive
    for (const auto &process : processes)
    {
        ready_queue.push(process);
    }

    // Loop through the queue and execute each process in order
    while (!ready_queue.empty())
    {
        // Get the next process in line
        auto current_process = ready_queue.front();
        ready_queue.pop();

        // Get the burst time
        int burst_time = current_process->get_burst_time();

        //   Add burst time to current time
        //   Set the completion time to the current time plus the burst time
        completion_time += burst_time;
        current_process->set_completion_time(completion_time);

        //   Set the turnaround time to the completion time minus the arrival time
        int turnaround_time = completion_time - current_process->get_arrival_time();
        current_process->set_turnaround_time(turnaround_time);

        //   Set the waiting time to the turnaround time minus the burst time
        int waiting_time = turnaround_time - burst_time;
        current_process->set_waiting_time(waiting_time);


    }
}

void first_come_first_served::print_results(std::vector<std::shared_ptr<cse4733::IProcess>>& processes) {
    std::cout << "FCFS Scheduling:" << std::endl
              << "  Process ID\tCompletion Time\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time" << std::endl;

    int total_waiting = 0;
    int total_turnaround = 0;
    for (const auto& item : processes) {
        std::cout << "  " << item->to_string() << std::endl;
        total_waiting += item->get_waiting_time();
        total_turnaround += item->get_turnaround_time();
    }
    std::cout << "  Average waiting time (tics): " << total_waiting / processes.size() << std::endl;
    std::cout << "  Average turnaround time (tics): " << total_turnaround / processes.size() << std::endl << std::endl;
}


}

