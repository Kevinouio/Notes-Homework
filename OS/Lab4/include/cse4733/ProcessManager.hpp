#ifndef CSE4733_PROCESSMANAGER_HPP
#define CSE4733_PROCESSMANAGER_HPP

#include <atomic>
#include <csignal>
#include <cstdlib>
#include <memory>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

namespace cse4733
{

    class ProcessManager
    {
    public:
        // @brief Default constructor
        // @param systemCalls System calls reference
        ProcessManager();

        // @brief Default destructor
        virtual ~ProcessManager() = default;

        // @brief Run the process manager
        void Run();

        // @brief Determine if the process should continue running
        // @return True if the process should continue running, false otherwise
        bool ShouldContinueRunning() const;

        // @brief Increment the sleep value
        void incrementSleepValue();

        // @brief Decrement the sleep value
        void decrementSleepValue();

        // @brief Get the sleep value
        // @return The sleep value
        int getSleepValue() const;

    private:

        // @brief Increment the child process counter
        void incrementCounter();

        // @brief Child process counter
        int m_counter;

        // @brief Child continue running
        bool m_shouldTerminate;

        // @brief Sleep value
        int m_sleepValue;
    };

} // namespace cse4733

#endif // CSE4733_PROCESSMANAGER_HPP