#ifndef CSE4733_FORKEXCEPTION_HPP
#define CSE4733_FORKEXCEPTION_HPP

#include <stdexcept>
#include <cstring>

namespace cse4733 {

    // @brief Exception class for Fork Exception
    class ForkException : public std::runtime_error {
    public:

        // @brief Default constructor
        // @param message Message to display
        ForkException(const std::string& message)
            :  std::runtime_error(message + ": " + std::strerror(errno)) {}
    };

} // namespace cse4733

#endif // CSE4733_FORKEXCEPTION_HPP