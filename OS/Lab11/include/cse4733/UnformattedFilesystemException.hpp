#ifndef UNFORMATTED_FILESYSTEM_EXCEPTION_HPP
#define UNFORMATTED_FILESYSTEM_EXCEPTION_HPP

#include <stdexcept>

namespace cse4733
{

    class UnformattedFilesystemException : public std::runtime_error
    {
    public:
        explicit UnformattedFilesystemException()
            : std::runtime_error("Filesystem has not been formatted.") {}
    };

} // namespace cse4733

#endif // UNFORMATTED_FILESYSTEM_EXCEPTION_HPP