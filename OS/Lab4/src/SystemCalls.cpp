#include "cse4733/SystemCalls.hpp"

#include <cerrno>
#include <cstring>
#include <iostream>
#include <optional>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

namespace cse4733
{

    std::optional<pid_t> SystemCalls::Fork()
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            return std::nullopt;
        }
        return pid;
    }

    std::optional<unsigned int> SystemCalls::Sleep(unsigned int seconds)
    {
        unsigned int result = sleep(seconds);
        return result;
    }

    std::optional<pid_t> SystemCalls::WaitPid(pid_t pid, int *status, int options)
    {
        pid_t result = waitpid(pid, status, options);
        if (result == -1)
        {
            return std::nullopt;
        }   
        return result;
    }

    pid_t SystemCalls::GetPid()
    {
        return ::getpid();
    }

} // namespace cse4733