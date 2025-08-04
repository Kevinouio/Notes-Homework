#ifndef ROUND_ROBIN_HPP
#define ROUND_ROBIN_HPP

#include <IProcess.hpp>

#include <iostream>
#include <memory>
#include <vector>

namespace cse4733
{

    class round_robin
    {
    public:
        /**
         * @brief Execute the shortest_job_first algorithm
         * @param processes Handle to the input processes
         * @param quantum Time quantum for run
         */
        void run(std::vector<std::shared_ptr<cse4733::IProcess>> &processes, int quantum);

        /**
         * @brief Print the results.
         * @param processes The processes to print.
         */
        static void print_results(std::vector<std::shared_ptr<cse4733::IProcess>> &processes);
    };

} // namespace cse4733

#endif // ROUND_ROBIN_HPP
