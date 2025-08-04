#include<iostream>
#include<queue>
#include<algorithm>

#include <first_come_first_served.hpp>
#include <process.hpp>
#include <round_robin.hpp>
#include <shortest_job_first.hpp>


std::vector<std::shared_ptr<cse4733::IProcess>> generate_processes()
{
    std::vector<std::shared_ptr<cse4733::IProcess>> processes;
    processes.push_back(std::make_shared<cse4733::Process>(1,10, 0));
    processes.push_back(std::make_shared<cse4733::Process>(2, 5, 1));
    processes.push_back(std::make_shared<cse4733::Process>(3, 8, 2));
    processes.push_back(std::make_shared<cse4733::Process>(4, 2, 3));
    processes.push_back(std::make_shared<cse4733::Process>(5, 3, 4));
    return processes;
}

int main() {

    // Set quantum for Round Robin scheduling
    int quantum = 2;

     // Execute the scheduling algorithms
    cse4733::first_come_first_served obj1;
    auto processes = generate_processes();
    obj1.run(processes);
    obj1.print_results(processes);

    cse4733::shortest_job_first obj2;
    processes = generate_processes();
    obj2.run(processes);
    obj2.print_results(processes);

    cse4733::round_robin obj3;
    processes = generate_processes();
    obj3.run(processes, quantum);
    obj3.print_results(processes);

    return 0;
}
