#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <string>
#include <vector>

#include "Inode.hpp"
#include "BlockManager.hpp"
#include "Directory.hpp"

/**
 * @namespace cse4733
 * @brief Namespace for all classes in the CSE 4733 filesystem project.
 */
namespace cse4733
{

    /**
     * @class FileSystem
     * @brief Manages files, directories, and block allocations within the filesystem.
     */
    class FileSystem
    {
    public:
        /**
         * @brief Constructs a filesystem with specified disk and block sizes.
         *
         * @param diskSize The total size of the simulated disk.
         * @param blockSize The size of each block.
         */
        FileSystem(size_t diskSize, size_t blockSize);

        /**
         * @brief Destructor to clean up resources.
         */
        ~FileSystem();

        /// Creates a new file with the specified name.
        bool createFile(const std::string &filename);

        /// Deletes the specified file and frees its resources.
        bool deleteFile(const std::string &filename);

        /// Writes data to the specified file.
        bool writeFile(const std::string &filename, const std::string &data);

        /// Reads and returns the content of the specified file.
        std::string readFile(const std::string &filename);

        /// Lists all files in the root directory.
        std::vector<std::string> listFiles();

        /// Initializes or reformats the filesystem.
        bool format();

        /**
         * @brief Returns the number of free blocks.
         *
         * @return The number of free blocks available in the filesystem.
         */
        size_t getFreeBlockCount() const;

        /**
         * @brief Returns the total number of blocks.
         *
         * @return The total number of blocks in the filesystem.
         */
        size_t getTotalBlockCount() const;

    private:

        /**
         * @brief Finds the inode index for a given filename.
         * 
         * @param filename The name of the file to look up.
         * @return The inode index if the file exists, or -1 if it does not exist.
         */
        int findInode(const std::string &filename);

        /**
         * @brief Allocates a new inode for a file.
         * 
         * @return The index of the allocated inode.
         * @throw NoAvailableInodeException if no inodes are available.
         * @throw UnformattedFilesystemException if the filesystem has not been formatted.
         */
        unsigned int allocateInode();

        /**
         * @brief Releases an inode and its associated blocks.
         * 
         * @param inodeIndex The index of the inode to release.
         * @return True if the inode was successfully released, false if the inode was not allocated.
         */
        void releaseInode(int inodeIndex);

        /// Manages block allocation and deallocation.        
        BlockManager blockManager;

        /// Root directory of the filesystem.
        Directory rootDirectory;

        /// Table of inodes.
        std::vector<Inode> inodeTable;

        /// Size of each block.
        size_t blockSize;

        /// Total size of the simulated disk.
        size_t diskSize;

        /**
         * @brief Indicates if the filesystem has been formatted.
         * 
         * @return True if the filesystem has been formatted, false otherwise.
         */
        bool isFormatted = false;

        /**
         * @brief Writes data to a series of blocks.
         * 
         * @param data The data to write.
         * @return A vector of block indices where the data was written.
         */
        std::vector<int> writeDataToBlocks(const std::string &data);

        /**
         * @brief Reads data from a series of blocks.
         * 
         * @param blockIndexes The indices of the blocks to read.
         * @return The data read from the blocks.
         */
        std::string readDataFromBlocks(const std::vector<int> &blockIndexes);
    };

} // namespace cse4733

#endif // FILESYSTEM_HPP
