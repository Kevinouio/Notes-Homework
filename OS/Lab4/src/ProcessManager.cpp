#include <iostream>
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

#include "cse4733/ForkException.hpp"
#include "cse4733/ProcessManager.hpp"
#include "cse4733/SignalHandlers.hpp"
#include "cse4733/SleepException.hpp"
#include "cse4733/SystemCalls.hpp"
#include "cse4733/WaitPidException.hpp"

namespace cse4733
{

    ProcessManager::ProcessManager()
        : m_counter(0),
          m_shouldTerminate(false),
          m_sleepValue(1)
    {
    }

    void ProcessManager::incrementCounter()
    {
        m_counter++;
    }

    void ProcessManager::incrementSleepValue()
    {
        m_sleepValue++;
    }

    void ProcessManager::decrementSleepValue()
    {
        m_sleepValue--;
    }

    int ProcessManager::getSleepValue() const
    {
        return m_sleepValue;
    }

    bool ProcessManager::ShouldContinueRunning() const
    {
        return !m_shouldTerminate &&
               m_counter >= 0 &&
               m_counter < 60;
    }

    void ProcessManager::Run()
    {
        /*
        TODO: Implement the Run method.
        1. Create a child process using the fork system call.
        2. If the fork failed, throw a ForkException with the message "Error occurred during fork."
        3. If the fork returned a negative value, throw a ForkException with the message "Failed to fork a child process."
        4. If the fork returned 0, this is the child process:
        4.1. Register signal handlers for SIGINT, SIGUSR1, and SIGALRM.
        4.2. Output the child process ID and a message indicating that the program is running.
        4.3. While the process should continue running:
        4.3.1. Sleep for the specified duration.
        4.3.2. Output the child process ID and sleep duration.
        4.3.3. Increment the counter.
        5. If the fork returned a positive value, this is the parent process:
        5.1. Wait for the child process to terminate.
        5.2. If the wait failed, throw a WaitPidException with the message "Error occurred during waitpid."
        5.3. If the child process terminated normally, output the exit status.
        5.4. If the child process was terminated by a signal, output the signal number.
        */

        // 1. Create a child process using the fork system call.
        auto maybePid = cse4733::SystemCalls::Fork();
        if (!maybePid.has_value())
        {
            // 2. If the fork failed, throw a ForkException with the message "Error occurred during fork."
            throw ForkException("Error occurred during fork.");
        }

        pid_t pid = maybePid.value();
        if (pid < 0)
        {
            // 3. If the fork returned a negative value, throw a ForkException with the message "Failed to fork a child process."
            throw ForkException("Failed to fork a child process.");
        }
        else if (pid == 0)
        {
            // 4. If the fork returned 0, this is the child process:
            // 4.1. Register signal handlers for SIGINT, SIGUSR1, and SIGALRM.
            std::signal(SIGINT, handleSIGINT);
            std::signal(SIGUSR1, handleSIGUSR1);
            std::signal(SIGALRM, handleSIGALRM);

            // 4.2. Output the child process ID and a message indicating that the program is running.
            std::cout << "Process ID: " << cse4733::SystemCalls::GetPid() << std::endl;
            std::cout << "Running the program." << std::endl;

            // 4.3. While the process should continue running:
            while (ShouldContinueRunning())
            {
                // 4.3.1. Sleep for the specified duration.
                auto maybeSleep = cse4733::SystemCalls::Sleep(static_cast<unsigned int>(getSleepValue()));
                if (!maybeSleep.has_value())
                {
                    throw SleepException("Error occurred during sleep.");
                }

                // 4.3.2. Output the child process ID and sleep duration.
                std::cout << "Child process " << cse4733::SystemCalls::GetPid()
                          << " completed sleep for " << getSleepValue()
                          << " seconds." << std::endl;

                // 4.3.3. Increment the counter.
                incrementCounter();
            }

            // Exit child process with success code
            std::exit(0);
        }
        else
        {
            // 5. If the fork returned a positive value, this is the parent process:
            // 5.1. Wait for the child process to terminate.
            int status = 0;
            auto maybeWait = cse4733::SystemCalls::WaitPid(pid, &status, 0);
            if (!maybeWait.has_value())
            {
                // 5.2. If the wait failed, throw a WaitPidException with the message "Error occurred during waitpid."
                throw WaitPidException("Error occurred during waitpid.");
            }

            // 5.3. If the child process terminated normally, output the exit status.
            if (WIFEXITED(status))
            {
                int exitStatus = WEXITSTATUS(status);
                std::cout << "Child process " << pid
                          << " terminated with exit status: " << exitStatus
                          << std::endl;
            }
            // 5.4. If the child process was terminated by a signal, output the signal number.
            else if (WIFSIGNALED(status))
            {
                int termSignal = WTERMSIG(status);
                std::cout << "Child process " << pid
                          << " terminated by signal: " << termSignal
                          << std::endl;
            }
        }
        
    }

} // namespace cse4733
