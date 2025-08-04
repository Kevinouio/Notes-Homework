#ifndef CSE4733_SLEEPEXCEPTION_HPP 
#define CSE4733_SLEEPEXCEPTION_HPP

#include <stdexcept>
#include <cstring>

namespace cse4733 {

    // @brief Exception class for Sleep Exception
    class SleepException : public std::runtime_error {
    public:

        // @brief Default constructor
        // @param message Message to display
        SleepException(const std::string& message)
            : std::runtime_error(message + ": " + std::strerror(errno)) {}
    };

} // namespace cse4733

#endif // CSE4733_SLEEPEXCEPTION_HPP