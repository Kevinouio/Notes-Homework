#include <string>
#include <vector>

namespace cse4733
{

    class BlockManager
    {
    public:
        /**
         * @brief Constructs a BlockManager with a specified number of blocks.
         *
         * @param totalBlocks The total number of blocks in the filesystem.
         */
        BlockManager(size_t totalBlocks);

        /**
         * @brief Frees a specific block by index.
         *
         * @param blockIndex The index of the block to free.
         */
        void freeBlock(unsigned int blockIndex);

        /**
         * @brief Allocates a single free block.
         *
         * @return The index of the allocated block.
         * @throw NoFreeBlockAvailableException if no free blocks are available.
         * @throw InvalidBlockIndexException if the block index is out of bounds while freeing allocated memory blocks.
         */
        unsigned int allocateBlock();

        /**
         * @brief Allocates multiple blocks as requested.
         *
         * @param numBlocks The number of blocks to allocate.
         * @return A vector containing the indices of the allocated blocks, or an empty vector if not enough free blocks are available.
         */
        std::vector<int> allocateBlocks(size_t numBlocks);

        /**
         * @brief Writes data to a specific block.
         *
         * @param blockIndex The index of the block to write to.
         * @param data The data to write to the block.
         * @throw InvalidBlockIndexException if the block index is out of bounds.
         */
        void writeBlock(unsigned int blockIndex, const std::string &data);

        /**
         * @brief Reads data from a specific block.
         *
         * @param blockIndex The index of the block to read from.
         * @return The data read from the block.
         * @throw InvalidBlockIndexException if the block index is out of bounds.
         */
        std::string readBlock(unsigned int blockIndex) const;

        /**
         * @brief Returns the size of each block.
         *
         * @return The size of each block.
         */
        size_t getBlockSize() const;

        /**
         * @brief Returns the total number of blocks.
         */
        size_t getTotalBlocks() const;

        /**
         * @brief Returns the number of free blocks.
         *
         * @return The number of free blocks available in the filesystem.
         */
        size_t getFreeBlockCount() const;

    private:
        /**
         * @brief The total number of blocks in the filesystem.
         *
         * This value is set during construction and does not change.
         */
        size_t blockSize;

        /**
         * @brief The list of blocks in the filesystem.
         */
        std::vector<std::string> blocks;

        /**
         * @brief The total number of blocks in the filesystem.
         *
         * This value is set during construction and does not change.
         */
        std::vector<bool> freeBlocks;
    };

} // namespace cse4733