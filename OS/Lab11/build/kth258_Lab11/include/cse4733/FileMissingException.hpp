#ifndef FILE_MISSING_EXCEPTION_HPP
#define FILE_MISSING_EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace cse4733
{
    class FileMissingException : public std::runtime_error
    {
    public:
        explicit FileMissingException(const std::string &filename)
            : std::runtime_error("File already exists: " + filename) {}
    };

} // namespace cse4733

#endif // FILE_MISSING_EXCEPTION_HPP