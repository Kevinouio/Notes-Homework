#ifndef NOFREEBLOCKAVAILABLEEXCEPTION_HPP
#define NOFREEBLOCKAVAILABLEEXCEPTION_HPP

#include <stdexcept>

namespace cse4733
{
    class NoFreeBlockAvailableException : public std::runtime_error
    {
    public:
        NoFreeBlockAvailableException()
            : std::runtime_error("No free block available") {}
    };
} // namespace cse4733

#endif // NOFREEBLOCKAVAILABLEEXCEPTION_HPP