#include <process.hpp>

#include <sstream>

namespace cse4733
{

    Process::Process(int pid, int burst, int arrival)
        : m_pid(pid),
          m_burst(burst),
          m_arrival(arrival),
          m_remaining(burst),
          m_turnaround(0),
          m_waiting(0),
          m_completion_time(0)
    {
    }

    auto Process::get_pid() const -> int
    {
        return m_pid;
    }

    auto Process::get_burst_time() const -> int
    {
        return m_burst;
    }

    void Process::set_arrival_time(int time)
    {
        m_arrival = time;
    }

    auto Process::get_arrival_time() const -> int
    {
        return m_arrival;
    }

    auto Process::get_remaining_time() const -> int
    {
        return m_remaining;
    }

    void Process::set_remaining_time(int time)
    {
        m_remaining = time;
    }

    auto Process::get_turnaround_time() const -> int
    {
        return m_turnaround;
    }

    void Process::set_turnaround_time(int time)
    {
        m_turnaround = time;
    }

    auto Process::get_waiting_time() const -> int
    {
        return m_waiting;
    }

    void Process::set_waiting_time(int time)
    {
        m_waiting = time;
    }

    auto Process::get_completion_time() const -> int
    {
        return m_completion_time;
    }

    void Process::set_completion_time(int time)
    {
        m_completion_time = time;
    }

    auto Process::to_string() const -> std::string
    {
        std::stringstream os;
        os << get_pid()
           << "\t\t"
           << get_completion_time()
           << "\t\t"
           << get_burst_time()
           << "\t\t"
           << get_arrival_time()
           << "\t\t"
           << get_waiting_time()
           << "\t\t"
           << get_turnaround_time();
        return os.str();
    }

}
