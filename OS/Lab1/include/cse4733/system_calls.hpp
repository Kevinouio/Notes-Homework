#ifndef SYSTEM_CALLS_HPP
#define SYSTEM_CALLS_HPP

#include "isystem_calls.hpp"

namespace cse4733 {

class SystemCalls : public ISystemCalls {
public:

    /**
     * @brief The Fork system call is used for creating a new process in Linux, and Unix systems,
     *        which is called the child process, which runs concurrently with the process that
     *        makes the fork() call (parent process). After a new child process is created, both
     *        processes will execute the next instruction following the fork() system call.
     * @return Integer value athat shows:
     *        - negative value: error - could not create child process.
     *        - zero: Indicates that the current process is the child process.
     *        - positive: Value contains the process ID of the newly created child process.
     */
    std::optional<pid_t> Fork() override;

    /**
     * @brief Execvp replaces the current process image with a new process image.
     * @param file The file to replace the current process image. If just the file name,
     *        without a sash, the file is sought using the PATH environment variable.
     *        Otherwise, it will the file path given.
     * @param argv The lits of arguments must be terminated by a NULL pointer.
     * @return Return -1 if there is an error. The 'errno' variable is set to indicate
     *         the error code.
     */
    std::optional<int> Execvp(const char *file,  std::vector<char*> argv) override;

    /**
     * @brief Wait for a child process to stop or terminate.
     * @param pid[in] The pid argument specifies the integer id of a child process for which status is requested.
     * 
     * @param status[out] The integer value of the child process. If the status pointer is not NULL,
     *                    Waitpid places the child process return status in the variable.
     *                    
     * 
     * @param options[in] The options argument is constructed from the bitwise-inclusive OR of zero or more of the
     *                    following flags: WCONTINUED, WNOHANG, or WUNTRACED
     * @return The integer value equal to the process ID of the child process for which status is reported. If a
     *         signal is caught, -1 shall be returned and 'errno' variable is set to indicate the error code.
     */
    std::optional<pid_t> Waitpid(pid_t pid, int *status, int options) override;

    /**
     * @brief Retrieve the current process identifier.
     * @return Integer value of the process id.
     */
    pid_t Getpid() override;

    /**
     * @brief Retrieve the process identifier of the parent process.
     * @return Integer value of the process id.
     */
    pid_t Getppid() override;
};

} // namespace cse4733

#endif // SYSTEM_CALLS_HPP
