#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include <string>
#include <unordered_map>
#include <vector>

/**
 * @namespace cse4733
 * @brief Namespace for all classes in the CSE 4733 filesystem project.
 */
namespace cse4733
{

    /**
     * @class Directory
     * @brief Manages the filesystem's directory structure, storing file names and their associated inode indices.
     */
    class Directory
    {
    public:
        /**
         * @brief Constructs an empty directory.
         */
        Directory();

        /**
         * @brief Adds a new file entry to the directory.
         *
         * @param filename The name of the file to add.
         * @param inodeIndex The inode index associated with this file.
         * @throw FileAlreadyExistsException if the file already exists in the directory.
         */
        void addFile(const std::string &filename, int inodeIndex);

        /**
         * @brief Removes a file entry from the directory by its name.
         *
         * @param filename The name of the file to remove.
         * @throw FileMissingException if the file does not exist in the directory.
         */
        void removeFile(const std::string &filename);

        /**
         * @brief Gets the inode index of a file.
         *
         * @param filename The name of the file.
         * @return The inode index of the file.
         * @throws FileMissingException if the file does not exist in the directory.
         */
        unsigned int getInodeIndex(const std::string &filename) const;

        /**
         * @brief Lists all files currently in the directory.
         *
         * @return A vector of strings, each representing a filename in the directory.
         */
        std::vector<std::string> listFiles() const;

        /**
         * @brief Checks if a file exists in the directory.
         *
         * @param filename The name of the file to check.
         * @return True if the file exists, false otherwise.
         */
        bool fileExists(const std::string &filename) const;

    private:
        /**
         * @brief A hash table mapping file names to their inode indices.
         *
         * This allows for efficient lookup, addition, and removal of files within the directory.
         */
        std::unordered_map<std::string, int> fileTable;
    };

} // namespace cse4733

#endif // DIRECTORY_HPP
