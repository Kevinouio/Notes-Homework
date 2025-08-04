#include "shortest_job_first.hpp"

#include <algorithm>

namespace cse4733
{

    // Comparator function for SJF scheduling
    auto shortest_job_first::operator()(const std::shared_ptr<cse4733::IProcess> &a,
                                        const std::shared_ptr<cse4733::IProcess> &b) -> bool
    {
        return a->get_burst_time() < b->get_burst_time();
    }

    void shortest_job_first::run(std::vector<std::shared_ptr<cse4733::IProcess>> &processes)
    {
        int completion_time = 0;

        // TODO:
        // Sort processes by using the shortest job first comparator
        std::sort(processes.begin(), processes.end(), shortest_job_first());

        // For all processes
        for (auto &process : processes)
        {
            //  Get the burst time
            int burst_time = process->get_burst_time();

            //  Set the completion time to the current time plus the burst time
            completion_time += burst_time;
            process->set_completion_time(completion_time);

            //  Set the turnaround time to the completion time minus the arrival time
            int turnaround_time = completion_time - process->get_arrival_time();
            process->set_turnaround_time(turnaround_time);

            //  Set the waiting time to the turnaround time minus the burst time
            int waiting_time = turnaround_time - burst_time;
            process->set_waiting_time(waiting_time);

            //  Add burst time to completion time (already done above)
        }
    }

    void shortest_job_first::print_results(std::vector<std::shared_ptr<cse4733::IProcess>> &processes)
    {
        int total_completion_time = 0;
        int total_waiting = 0;
        int total_turnaround = 0;
        int n = processes.size();

        std::cout << "SJF Scheduling:\n";
        std::cout << "Process ID\tCompletion Time\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n";
        for (const auto &item : processes)
        {
            std::cout << "  " << item->to_string() << std::endl;
            total_turnaround += item->get_turnaround_time();
            total_waiting += item->get_waiting_time();
            total_completion_time += item->get_burst_time();
        }

        double average_waiting_time = static_cast<double>(total_waiting) / n;
        double average_turnaround_time = static_cast<double>(total_turnaround) / n;

        std::cout << "  Average Waiting Time: " << average_waiting_time << std::endl;
        std::cout << "  Average Turnaround Time: " << average_turnaround_time << std::endl
                  << std::endl;
    }

}
