               #include "round_robin.hpp"

#include<algorithm>
#include<queue>

namespace cse4733 {

void round_robin::run(std::vector<std::shared_ptr<cse4733::IProcess>> &processes, int quantum)
    {
        int completion_time = 0;
        std::queue<std::shared_ptr<cse4733::IProcess>> ready_queue;

        // TODO:
        //  Get number of processes
        int num_processes = processes.size();

        //  Fill the ready queue
        for (const auto &process : processes) {
            ready_queue.push(process);
        }

        //  Loop until all processes are removed from the ready queue
        while (!ready_queue.empty())
        {
            //  Get the next process from the ready queue
            auto current_process = ready_queue.front();
            ready_queue.pop();

            //  Get the remaining time for the process
            int remaining_time = current_process->get_remaining_time();

            //  Execute the process for the quantum or remaining time, whichever is smaller
            int time_slice = std::min(quantum, remaining_time);
            completion_time += time_slice; // Advance time by the executed duration
            current_process->set_remaining_time(remaining_time - time_slice);

            //  Update the completion time and remaining time
            //  Add back to the queue if the process still has remaining time
            if (current_process->get_remaining_time() != 0) {

                ready_queue.push(current_process);
            }
            //  Else set the completion time, turnaround time, and waiting time
            else {
                current_process->set_completion_time(completion_time);
                int turnaround_time = completion_time - current_process->get_arrival_time();
                current_process->set_turnaround_time(turnaround_time);
                int waiting_time = turnaround_time - current_process->get_burst_time();
                current_process->set_waiting_time(waiting_time);

            }
        }
    }

void round_robin::print_results(std::vector<std::shared_ptr<cse4733::IProcess>> &processes)
    {
        int total_waiting = 0;
        int total_turnaround = 0;
        int n = processes.size();

        std::cout << "Round Robin Scheduling:\n";
        std::cout << "Process ID\tCompletion Time\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n";
        for (const auto& item : processes)
        {
            std::cout << "  " << item->to_string() << std::endl;

            // Set the total turnaround time
            total_turnaround += item->get_turnaround_time();

            // Set the total waiting time
            total_waiting += item->get_waiting_time();
        }
        std::cout << "  Average Waiting Time: " << (double)total_waiting / n << std::endl;
        std::cout << "  Average Turnaround Time: " << (double)total_turnaround / n << std::endl;
    }

}

