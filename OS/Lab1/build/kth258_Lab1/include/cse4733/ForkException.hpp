#ifndef CSE4733_FORKEXCEPTION_HPP
#define CSE4733_FORKEXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace cse4733 {

class ForkException : public std::runtime_error
{
public:
    ForkException(const std::string& message) : std::runtime_error(message) {}
};

} // namespace cse4733

#endif // CSE4733_FORKEXCEPTION_HPP
