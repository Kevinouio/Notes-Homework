#ifndef FILE_ALREADY_EXISTS_EXCEPTION_HPP
#define FILE_ALREADY_EXISTS_EXCEPTION_HPP

#include <stdexcept>
#include <string>

namespace cse4733
{

    class FileAlreadyExistsException : public std::runtime_error
    {
    public:
        explicit FileAlreadyExistsException(const std::string &filename)
            : std::runtime_error("File already exists: " + filename) {}
    };

}

#endif // FILE_ALREADY_EXISTS_EXCEPTION_HPP