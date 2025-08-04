#ifndef PROCESS_INTERFACE_HPP
#define PROCESS_INTERFACE_HPP

#include <string>

namespace cse4733
{

    /**
     * @brief The IProcess class
     * This is the interface for the Process class.
     * This is used to allow the scheduler to work with
     * different types of processes.
     */
    class IProcess
    {
    public:
        /**
         * Get the unique identifier.
         * @return Integer value for unique identifier.
         */
        virtual auto get_pid() const -> int = 0;

        /**
         * Get the burst time for the process.
         * @return Value of the burst time.
         */
        virtual auto get_burst_time() const -> int = 0;

        /**
         * Get the arrival time for the process.
         * @param time Value of the arrival time.
         */
        virtual void set_arrival_time(int time) = 0;

        /**
         * Get the arrival time for the process.
         * @return Value of the arrival time.
         */
        virtual auto get_arrival_time() const -> int = 0;

        /**
         * Get the remaining time for the process.
         * @return Value of the remaining time.
         */
        virtual auto get_remaining_time() const -> int = 0;

        /**
         * Set the remaining time for the process.
         * @return Value of the remaining time.
         */
        virtual void set_remaining_time(int time) = 0;

        /**
         * Get the turnaround time for the process.
         * @return Value of the turnaround time.
         */
        virtual auto get_turnaround_time() const -> int = 0;

        /**
         * Set the turnaround time for the process.
         * @param time Value of the turnaround time.
         */
        virtual void set_turnaround_time(int time) = 0;

        /**
         * Get the waiting time for the process.
         * @return Value of the waiting time.
         */
        virtual auto get_waiting_time() const -> int = 0;

        /**
         * Set the waiting time for the process.
         * @param time Value of the waiting time
         */
        virtual void set_waiting_time(int time) = 0;

        /**
         * Get the completion time for the process.
         * @return Value of the completion time.
         */
        virtual auto get_completion_time() const -> int = 0;

        /**
         * Set the completion time for the process.
         * @param time Value of the completion time
         */
        virtual void set_completion_time(int time) = 0;

        /**
         * @brief Create a string representation of the process.
        */
        virtual auto to_string() const -> std::string = 0;
    };
}

#endif // PROCESS_INTERFACE_HPP