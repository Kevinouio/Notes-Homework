#ifndef PROCESS_HPP
#define PROCESS_HPP

#include "IProcess.hpp"

#include <iostream>

namespace cse4733
{

    // Process struct
    class Process : public IProcess
    {
    private:
        int m_pid;             // Process ID
        int m_burst;           // Burst time
        int m_arrival;         // Arrival time
        int m_remaining;       // Remaining time
        int m_turnaround;      // Turnaround time
        int m_waiting;         // Waiting time
        int m_completion_time; // Completion time

    public:
        /**
         * @brief Process
         * @param pid Unique identifier for process given my operating system.
         * @param burst Burst time value for the process.
         * @param arrival Arrival time value for the process.
         */
        Process(int pid, int burst, int arrival);

        /**
         * Get the unique identifier.
         * @return Integer value for unique identifier.
         */
        auto get_pid() const -> int override;

        /**
         * Get the burst time for the process.
         * @return Value of the burst time.
         */
        auto get_burst_time() const -> int override;

        /**
         * Get the arrival time for the process.
         * @param time Value of the arrival time.
         */
        void set_arrival_time(int time) override;

        /**
         * Get the arrival time for the process.
         * @return Value of the arrival time.
         */
        auto get_arrival_time() const -> int override;

        /**
         * Get the remaining time for the process.
         * @return Value of the remaining time.
         */
        auto get_remaining_time() const -> int override;

        /**
         * Set the remaining time for the process.
         * @return Value of the remaining time.
         */
        void set_remaining_time(int time) override;

        /**
         * Get the turnaround time for the process.
         * @return Value of the turnaround time.
         */
        auto get_turnaround_time() const -> int override;

        /**
         * Set the turnaround time for the process.
         * @param time Value of the turnaround time.
         */
        void set_turnaround_time(int time) override;

        /**
         * Get the waiting time for the process.
         * @return Value of the waiting time.
         */
        auto get_waiting_time() const -> int override;

        /**
         * Set the waiting time for the process.
         * @param time Value of the waiting time
         */
        void set_waiting_time(int time) override;

        /**
         * Get the completion time for the process.
         * @return Value of the completion time.
         */
        auto get_completion_time() const -> int override;

        /**
         * Set the completion time for the process.
         * @param time Value of the completion time
         */
        void set_completion_time(int time) override;

        /**
         * @brief Create a string representation of the process.
         */
        virtual auto to_string() const -> std::string override;
    };

} // namespace cse4733

#endif
