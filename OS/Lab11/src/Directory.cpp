#include "cse4733/Directory.hpp"
#include "cse4733/FileAlreadyExistsException.hpp"
#include "cse4733/FileMissingException.hpp"

namespace cse4733
{

    Directory::Directory()
    {
        // Initializes an empty directory.
    }

    void Directory::addFile(const std::string &filename, int inodeIndex)
    {
        // 1. Check if the file already exists in the directory
        //    a. If it does, throw a FileAlreadyExistsException
        // 2. Add the file to the directory with the associated inode index
        if (fileExists(filename))
        {
            throw FileAlreadyExistsException(filename); // File already exists
        }

        // Add the file with the associated inode index
        fileTable[filename] = inodeIndex;
    }

    void Directory::removeFile(const std::string &filename)
    {
        // Function: removeFile
        //
        // Input: filename (string) - The name of the file to remove
        //
        // 1. Check if the file exists in the directory
        //    a. If it does not, throw a FileMissingException
        // 2. Attempt to erase the file from the directory
        if (!fileExists(filename))
        {
            throw FileMissingException(filename); // File does not exist
        }
        else
        {
            // Attempt to erase the file from the directory
            fileTable.erase(filename);
        }
    }

    unsigned int Directory::getInodeIndex(const std::string &filename) const
    {
        // Check if the file exists using the fileExists method
        // 1. If the file exists, find the file in the fileTable using the provided filename
        //    a. If the file is found, return the associated inode index
        // 2. If the file does not exist, throw a FileMissingException with the provided filename
        if (fileExists(filename))
        {
            // Find the file in the fileTable using the provided filename
            auto it = fileTable.find(filename);
            // Return the associated inode index
            return it->second;
        }
        else
        {
            auto it = fileTable.find(filename);
            if (it != fileTable.end())
            {
                return it->second; // Return the inode index if found
            }
            throw FileMissingException(filename); // File does not exist
        } // If the file was not found, throw a FileMissingException with the provided filename
        throw FileMissingException(filename);
    }

    std::vector<std::string> Directory::listFiles() const
    {
        // 1. Create a vector to store the filenames
        // 2. Iterate over each entry in the fileTable
        //    a. Add the filename to the vector
        // 3. Return the vector of filenames
        std::vector<std::string> files;
        for (const auto &entry : fileTable)
        {
            files.push_back(entry.first);
        }
        return files;
    }

    bool Directory::fileExists(const std::string &filename) const
    {
        // Check if the file exists in the directory
        return fileTable.find(filename) != fileTable.end();
    }

} // namespace cse4733
