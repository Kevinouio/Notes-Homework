#include "cse4733/BlockManager.hpp"
#include "cse4733/InvalidBlockIndexException.hpp"
#include "cse4733/NoFreeBlockAvailableException.hpp"

#include <cstddef>
#include <algorithm>
#include <iostream>

namespace cse4733
{

    BlockManager::BlockManager(size_t totalBlocks)
        : blockSize(64),
          blocks(totalBlocks),
          freeBlocks(totalBlocks, true)
    {
    }

    unsigned int BlockManager::allocateBlock()
    {
        // 1. Use std::find_if to find the first free block
        // 2. Check if a free block was found
        //    a. Mark the block as allocated
        //    b. Return the index of the allocated block
        // 3. No free block available, throw NoFreeBlockAvailableException
        auto it = std::find_if(freeBlocks.begin(), freeBlocks.end(), [](bool isFree)
                               { return isFree; });

        // Check if a free block was found
        if (it != freeBlocks.end())
        {
            // Mark the block as allocated
            *it = false;
            // Return the index of the allocated block
            return std::distance(freeBlocks.begin(), it);
        }

        // No free block available
        throw cse4733::NoFreeBlockAvailableException();
    }

    void BlockManager::freeBlock(unsigned int blockIndex)
    {
        // 1. Check if the block index is within bounds
        //   a. Mark the block as free
        // 2. If the block index is out of bounds, throw InvalidBlockIndexException
        if (blockIndex < freeBlocks.size())
        {
            freeBlocks[blockIndex] = true;
        }
        else
        {
            throw InvalidBlockIndexException(blockIndex);
        }
    }

    std::vector<int> BlockManager::allocateBlocks(size_t numBlocks)
    {
        // 1. Create vector to store the indices of allocated blocks
        // 2. Try to allocate the requested number of blocks
        //    a. Allocate a block and save the index
        //    b. Add the index of the allocated block to the vector
        // 3. If a NoFreeBlockAvailableException is thrown while allocating blocks
        //    a. Try to free the already allocated blocks
        //    b. If an InvalidBlockIndexException is thrown while freeing blocks
        //      1) Log the error or handle it as needed
        //      2) Rethrow the exception
        //    c. Rethrow the NoFreeBlockAvailableException
        // 4. Return the vector of allocated block indices
        std::vector<int> allocatedBlocks;
        try
        {
            // Allocate the requested number of blocks
            for (size_t i = 0; i < numBlocks; ++i)
            {
                int blockIndex = allocateBlock();
                allocatedBlocks.push_back(blockIndex);
            }
        }
        catch (const cse4733::NoFreeBlockAvailableException &no_free_block_error)
        {
            std::cerr << "Unable to allocated all the requested blocks. Freeing already allocated blocks." << std::endl;
            // Free already allocated blocks in case of failure
            try
            {
                for (int index : allocatedBlocks)
                {
                    freeBlock(index);
                }
            }
            catch (const InvalidBlockIndexException &invalid_block_error)
            {
                // Handle the case where freeBlock throws an InvalidBlockIndexException
                // This should not happen if the allocateBlock and freeBlock methods are implemented correctly
                // Log the error or handle it as needed
                std::cerr << "Error freeing allocated blocks." << std::endl;
                throw invalid_block_error;
            }
            // Return an empty vector to indicate failure
            throw no_free_block_error;
        }
        // Return the vector of allocated block indices
        return allocatedBlocks;
    }

    void BlockManager::writeBlock(unsigned int blockIndex, const std::string &data)
    {
        // 1. Check if the block index is within bounds
        //    a. Write the data to the block
        // 2. If the block index is out of bounds, throw InvalidBlockIndexException
        if (blockIndex < blocks.size())
        {
            blocks[blockIndex] = data.substr(0, blockSize); // Ensure data fits in the block
        }
        else
        {
            throw InvalidBlockIndexException(blockIndex);
        }
    }

    std::string BlockManager::readBlock(unsigned int blockIndex) const
    {
        // 1. Check if the block index is within bounds
        //    a. Read the data from the block
        //    b. Return the data
        // 2. If the block index is out of bounds, throw InvalidBlockIndexException
        if (blockIndex < blocks.size())
        {
            return blocks[blockIndex];
        }
        else
        {
            throw InvalidBlockIndexException(blockIndex);
        }
    }

    size_t BlockManager::getBlockSize() const
    {
        // Return the size of each block
        return blockSize;
    }

    size_t BlockManager::getTotalBlocks() const
    {
        // Return the total number of blocks
        return blocks.size();
    }

    size_t BlockManager::getFreeBlockCount() const
    {
        // Count the number of free blocks where freeBlocks[i] is true
        size_t count = std::count_if(freeBlocks.begin(), freeBlocks.end(), [](bool free)
                                     { return free; });
        return count;
    }

} // namespace cse4733
