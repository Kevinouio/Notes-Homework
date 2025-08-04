#ifndef FIRST_COME_FIRST_SERVED_HPP
#define FIRST_COME_FIRST_SERVED_HPP

#include <IProcess.hpp>

#include <iostream>
#include <memory>
#include <vector>

namespace cse4733 {

class first_come_first_served
{
public:

    /**
     * @brief Execute the first_come_first_served algorithm
     */
    static void run(std::vector<std::shared_ptr<cse4733::IProcess>>& processes);

    /**
     * @brief Print the results.
     * @param processes The processes to print.
    */
    static void print_results(std::vector<std::shared_ptr<cse4733::IProcess>>& processes);
};

} // namespace cse4733

#endif // FIRST_COME_FIRST_SERVED_HPP
