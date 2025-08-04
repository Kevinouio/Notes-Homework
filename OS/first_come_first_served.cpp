#include "first_come_first_served.hpp"

#include <iostream>

namespace cse4733 {

void first_come_first_served::run(std::vector<std::shared_ptr<cse4733::IProcess>>& processes)
{
    int completion_time = 0;
        // TODO:
        //
        // Set 'current_time' to zero. It will keep track of the elapsed process execution times.
        // For all processes
        //   Get the burst time
        //   Set the completion time to the current time plus the burst time
        //   Set the turnaround time to the completion time minus the arrival time
        //   Set the waiting time to the turnaround time minus the burst time
        //   Add burst time to current time
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

