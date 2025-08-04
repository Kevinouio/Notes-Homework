#include "process.hpp"
#include "ForkException.hpp"
#include <unistd.h>

#include <iostream>


namespace cse4733
{

    process::process(std::shared_ptr<ISystemCalls> systemCalls,
                     std::string path,
                     const std::vector<std::string> &args)
        : processId(-1),
          executablePath(std::move(path)),
          sysCalls(std::move(systemCalls)),
          errorMessage("(none)")
    {

        for (const auto &arg : args)
        {
            arguments.push_back(const_cast<char *>(arg.c_str()));
        }
        arguments.push_back(nullptr);
    }

    auto process::execute() -> bool
    {
        // TODO:
        // Call the system fork function to create a child process
        // IF the fork fails, display an error message and return false
        // IF the fork succeeds, check if this is the child process or the parent process
        //   IF the child:
        //     Execute the child process logic
        //     Return false to indicate that this is the child process
        //   ELSE the parent:
        //     Execute the parent process logic
        //     Return true to indicate that this is the parent process and the child process was created successfully

        // Call the system fork function to create a child process

        auto forkResult = sysCalls->Fork();
        if (!forkResult.has_value()) {
            std::cerr << "Error: Fork failed.\n";
            return false;
        }

        pid_t pid = forkResult.value(); // Extract the actual pid value



        if (pid < 0)
        {
            std::cerr << "Error: Fork failed.\n";
            return false; // Fork failed
        }
        else if (pid == 0)
        {
            // Child process
            executeChildProcess();
            return false;
        }
        else
        {
            // Parent process
            executeParentProcess(pid);
            return true;
        }

    }

    void process::executeChildProcess()
    {
        // TODO:
        //   Print the child process ID
        //   Print the parent process ID
        //   Execute the given program with the provided arguments
        //   Should Execvp return (if it does?) then print an error message and exit

        // Print the child process ID
        std::cout << "Child Process ID: " << getpid() << "\n";

        // Print the parent process ID
        std::cout << "Parent Process ID: " << getppid() << "\n";

        // Execute the given program with the provided arguments
        execvp(arguments[0], arguments.data());

        // If execvp returns, it means an error occurred
        std::cerr << "Error: execvp failed for " << executablePath << "\n";
        exit(EXIT_FAILURE);
    }

    void process::executeParentProcess(pid_t pid)
    {
        // TODO:
        //   Store the child process ID
        //   Print the parent process ID
        //   Print the child process ID

        // Store the child process ID
        processId = pid;

        // Print the parent process ID
        std::cout << "Parent Process ID: " << getpid() << "\n";

        // Print the child process ID
        std::cout << "Child Process ID: " << pid << "\n";

    }

    void process::handleChildExitStatus(int status, pid_t pid)
    {
        // TODO:
        // Check if the child process terminated normally
        // IF the child process terminated normally
        //    Print a message with the child process ID with the exit status.
        // ELSE IF the child process did not terminate normally
        //    Print an error message with the child process ID

        // Check if the child process terminated normally
        if (WIFEXITED(status))
        {
            std::cout << "Child Process " << pid << " terminated with exit status " << WEXITSTATUS(status) << ".\n";
        }
        else
        {
            std::cerr << "Error: Child Process " << pid << " did not terminate normally.\n";
        }
    }

    auto process::wait() -> std::optional<int>
    {
        // Declare a variable to hold the status of the child process
        // Use the Waitpid system call to wait for the child process to change state (e.g., to terminate)
        // Check if the Waitpid system call succeeded
        // If the Waitpid system call failed, print an error message and return std::nullopt
        // Else if the Waitpid system call succeeded, handle the child's exit status
        // Return the exit status of the child process


        int status;
        std::optional<int> waitResult = sysCalls->Waitpid(-1, &status, 0); // Wait for any child process
        if (!waitResult.has_value()) {
            std::cerr << "Waitpid failed" << std::endl;
            return {}; // Return an empty optional or handle the error appropriately
        }
        pid_t pid = waitResult.value(); // Extract the actual pid value


        handleChildExitStatus(status, pid);

        if (WIFEXITED(status))
        {
            return WEXITSTATUS(status);
        }

        return std::nullopt;



        return std::nullopt;
    }

    auto process::get_id() const -> pid_t
    {
        return this->processId;
    }

    auto process::getErrorMessage() const -> std::string
    {
        return errorMessage;
    }

} // namespace cse4733
