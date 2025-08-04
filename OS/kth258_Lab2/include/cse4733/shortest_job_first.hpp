#ifndef SHORTEST_JOB_FIRST_HPP
#define SHORTEST_JOB_FIRST_HPP

#include <IProcess.hpp>

#include <iostream>
#include <memory>
#include <vector>

namespace cse4733
{

    class shortest_job_first
    {
    public:
        // Comparator function for SJF scheduling
        auto operator()(const std::shared_ptr<cse4733::IProcess> &a,
                        const std::shared_ptr<cse4733::IProcess> &b) -> bool;

        /**
         * @brief Execute the shortest_job_first algorithm
         */
        void run(std::vector<std::shared_ptr<cse4733::IProcess>> &processes);

        /**
         * @brief Print the results.
         * @param processes The processes to print.
         */
        static void print_results(std::vector<std::shared_ptr<cse4733::IProcess>> &processes);
    };

} // namespace cse4733

#endif // SHORTEST_JOB_FIRST_HPP
