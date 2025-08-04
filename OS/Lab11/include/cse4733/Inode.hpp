#ifndef INODE_HPP
#define INODE_HPP

#include <vector>
#include <ctime>

namespace cse4733
{

    class Inode
    {
    public:
        /**
         * @brief Constructs an unallocated inode.
         */
        Inode();

        /**
         * @brief Initializes inode for a new file.
         *
         * @param size The size of the file in bytes.
         * @param blocks The list of data block indices assigned to this file.
         */
        void allocate(size_t size, const std::vector<int> &blocks);

        /**
         * @brief Clears inode data when a file is deleted.
         */
        void deallocate();

        /* Indicates if the inode is currently in use. */
        bool isAllocated;

        /* Size of the file in bytes. */
        size_t fileSize;

        /* Timestamp for when the file was created. */
        std::time_t creationTime;

        /* Timestamp for when the file was last modified. */
        std::time_t modificationTime;

        /* List of direct block indices for this file. */
        std::vector<int> directBlocks;

    private:
        static const int MAX_DIRECT_BLOCKS = 10; /* Maximum number of direct blocks per inode. */
    };

} // namespace cse4733

#endif // INODE_HPP