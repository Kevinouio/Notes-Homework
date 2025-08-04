#include "cse4733/Inode.hpp"

namespace cse4733
{

    Inode::Inode() : isAllocated(false), fileSize(0), creationTime(0), modificationTime(0)
    {
        // Reserve space for the maximum number of direct blocks to avoid reallocations
        directBlocks.reserve(MAX_DIRECT_BLOCKS);
    }

    void Inode::allocate(size_t size, const std::vector<int> &blocks)
    {
        // Mark the inode as allocated
        isAllocated = true;

        // Set the file size
        fileSize = size;

        // Set the creation time to the current time
        creationTime = std::time(nullptr);

        // Set the modification time to the creation time initially
        modificationTime = creationTime;

        // Assign the provided blocks to the inode
        directBlocks = blocks;
    }

    void Inode::deallocate()
    {
        // Mark the inode as not allocated
        isAllocated = false;

        // Reset the file size
        fileSize = 0;

        // Reset the creation time
        creationTime = 0;

        // Reset the modification time
        modificationTime = 0;

        // Clear all block indices
        directBlocks.clear();
    }

} // namespace cse4733
