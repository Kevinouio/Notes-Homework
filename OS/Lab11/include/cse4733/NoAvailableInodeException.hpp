#ifndef NO_AVAILABLE_INODES_EXCEPTION_HPP
#define NO_AVAILABLE_INODES_EXCEPTION_HPP

#include <stdexcept>

namespace cse4733
{

    class NoAvailableInodeException : public std::runtime_error
    {
    public:
        explicit NoAvailableInodeException()
            : std::runtime_error("Filesystem inode is not available.") {}
    };

} // namespace cse4733

#endif // NO_AVAILABLE_INODES_EXCEPTION_HPP