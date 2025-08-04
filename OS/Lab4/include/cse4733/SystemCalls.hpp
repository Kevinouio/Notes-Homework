#ifndef CSE4733_SYSTEMCALLS_HPP
#define CSE4733_SYSTEMCALLS_HPP

#include <unistd.h>
#include <optional>

namespace cse4733
{

    class SystemCalls {
    public:

        //  @brief Forks the current process
        //  @return pid_t Process ID of the child process
        //  @throws std::nullopt if an error occurs
        static std::optional<pid_t> Fork();

        //  @brief Sleeps for the specified number of seconds
        //  @param seconds Number of seconds to sleep
        //  @return unsigned int Number of seconds left to sleep
        //  @throws std::nullopt if an error occurs
        static std::optional<unsigned int> Sleep(unsigned int seconds);

        //  @brief Waits for the specified process to change state
        //  @param[in] pid_t Process ID of the process to wait for
        //  @param[out] status Status of the process
        //  @param[in] options Options for the process
        //  @return pid_t Process ID of the process that changed state
        //  @throws std::nullopt if an error occurs
        static std::optional<pid_t> WaitPid(pid_t pid, int *status, int options);

        //  @brief Gets the process ID of the current process
        //  @return pid_t Process ID of the current process
        static pid_t GetPid();

    };

} // namespace cse4733

#endif // CSE4733_SYSTEMCALLS_HPP