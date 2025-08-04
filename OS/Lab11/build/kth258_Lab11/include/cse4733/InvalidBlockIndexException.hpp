#ifndef INVALIDBLOCKINDEXEXCEPTION_HPP
#define INVALIDBLOCKINDEXEXCEPTION_HPP

#include <stdexcept>

namespace cse4733
{

    class InvalidBlockIndexException : public std::runtime_error
    {
    public:
        InvalidBlockIndexException(unsigned int blockIndex)
            : std::runtime_error("Invalid block index: " + std::to_string(blockIndex)) {}
    };

} // namespace cse4733

#endif // INVALIDBLOCKINDEXEXCEPTION_HPP