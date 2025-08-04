#ifndef CSE4733_INVALID_VIRTUAL_ADDRESS_EXCEPTION_HPP
#define CSE4733_INVALID_VIRTUAL_ADDRESS_EXCEPTION_HPP

#include <stdexcept>

namespace cse4733
{

    class invalid_virtual_address_exception : public std::runtime_error
    {
    public:
        invalid_virtual_address_exception() : std::runtime_error("Invalid virtual address!") {}
    };

} // namespace cse4733

#endif // CSE4733_INVALID_VIRTUAL_ADDRESS_EXCEPTION_HPP
