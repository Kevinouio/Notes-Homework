#include "isystem_calls.hpp"

#include <memory>
#include <vector>
#include <string>

namespace cse4733
{

    class process
    {
    public:
        /**
         * @brief Object to hold all the necessary information for a system process.
         * @param systemCalls Pointer to the system calls.
         * @param path Name of the executable binary used by the child process.
         * @param args List of command line arguments for the child process executable.
         */

        process(std::shared_ptr<ISystemCalls> systemCalls,
                std::string path,
                const std::vector<std::string> &args);

        /**
         * @brief execute
         * @return TRUE if able to create the child process. Otherwise, return FALSE.
         */
        auto execute() -> bool;

        /**
         * @brief wait Have the current process wait on the child process.
         * @return The exit status of the child process.
         */
        auto wait() -> std::optional<int>;

        /**
         * @brief Retrieve the process id for the current process.
         * @return Returned process id.
         */
        auto get_id() const -> pid_t;

        /**
         * @brief Retrieve the error message.
         * @return Error message.
        */
        auto getErrorMessage() const -> std::string;

    private:
        /**
         * @brief Pointer to the system calls.
         */
        pid_t processId;

        /**
         * @brief Name of the executable binary used by the child process.
         */
        std::string executablePath;

        /**
         * @brief List of command line arguments for the child process executable.
         */
        std::vector<char*> arguments;

        /**
         * @brief Pointer to the system calls.
         */
        std::shared_ptr<ISystemCalls> sysCalls;

        /**
         * @brief Retrieve the error message.
        */
        std::string errorMessage;

        /**
         * @brief Handlle the child exit status.
         */
        void handleChildExitStatus(int status, pid_t pid);

        /**
         * @brief Execute the parent process.
         */
        void executeParentProcess(pid_t pid);
        
        /**
         * @brief Execute the child process.
         */
        void executeChildProcess();

    };

} // namespace cse4733
