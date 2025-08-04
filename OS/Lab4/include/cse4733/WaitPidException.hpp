#ifndef CSE4733_WAITPIDEXCEPTION_HPP
#define CSE4733_WAITPIDEXCEPTION_HPP

#include <stdexcept>
#include <cstring>

namespace cse4733
{
    // @brief Exception class for WaitPid
    class WaitPidException : public std::runtime_error
    {
    public:

        // @brief Default constructor
        // @param message Message to display
        explicit WaitPidException(const std::string &message)
            : std::runtime_error(message + ": " + std::strerror(errno)) {}
    };
} // namespace cse4733

#endif // CSE4733_WAITPIDEXCEPTION_HPP
