#include <system_calls.hpp>

#include <sys/wait.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

namespace cse4733
{

std::optional<pid_t> SystemCalls::Fork()
{
    pid_t pid = fork();
    if (pid == -1)
    {
        std::cerr << "Fork failed: " << strerror(errno) << std::endl;
        return std::nullopt;
    }
    return pid;
}


std::optional<int> SystemCalls::Execvp(const char *file, std::vector<char *> argv)
{
    int result = execvp(file, argv.data());
    if (result == -1)
    {
        std::cerr << "Execvp failed: " << strerror(errno) << std::endl;
        return std::nullopt;
    }
    // execvp is expected not to return on success
    return {};
}

std::optional<pid_t> SystemCalls::Waitpid(pid_t pid, int *status, int options)
{
    pid_t result = waitpid(pid, status, options);
    if (result == -1)
    {
        std::cerr << "Waitpid failed: " << strerror(errno) << std::endl;
        return std::nullopt;
    }
    return result;
}

    pid_t SystemCalls::Getpid()
    {
        return getpid();
    }

    pid_t SystemCalls::Getppid()
    {
        return getppid();
    }
}
