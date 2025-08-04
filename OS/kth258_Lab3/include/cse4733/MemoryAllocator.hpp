#ifndef CSE4733_MEMORYALLOCATOR_HPP
#define CSE4733_MEMORYALLOCATOR_HPP

#include <IMemoryAllocator.hpp>
#include <MemoryBlockList.hpp>

#include <string>
#include <vector>

namespace cse4733
{
 
    class MemoryAllocator : public IMemoryAllocator
    {
    public:

        // @brief Constructor
        // @param total_memory_size: total memory size in bytes
        MemoryAllocator(std::size_t total_memory_size);

        // @brief Allocate memory for a process
        // @param process_id: process id
        // @param size: memory size in bytes
        // @return starting address of the allocated memory
        // @throw std::runtime_error if no suitable memory block found for allocation
        auto allocate(const std::string &process_id, std::size_t size) -> std::size_t override;

        // @brief Deallocate memory for a process
        // @param process_id: process id
        // @throw std::runtime_error if no memory block found for deallocation
        void deallocate(const std::string &process_id) override;

        // @brief Get the memory layout
        // @return MemoryBlockList
        auto get_memory_layout() -> MemoryBlockList & override;

        // @brief Get the amount of free space available
        // @return The amount of free space available
        auto get_free_space() -> std::size_t override;

    private:

        // @brief Free memory process id
        static constexpr const char* FREE_MEMORY_STRING = "Free Memory";

        // @brief Total memory size in bytes
        std::size_t total_memory_size_;

        // @brief Free memory size in bytes
        std::size_t free_memory_size_;

        // @brief MemoryBlockList is a vector of MemoryBlock objects
        MemoryBlockList memory_blocks_;

        /**
         * Checks if two memory blocks are free and can be merged.
         * 
         * <p>This method checks whether the two provided memory blocks are both free,
         * meaning they have no associated process, and can therefore be combined
         * into a single memory block.</p>
         * 
         * @param current the current memory block to check
         * @param next the next memory block to check
         * @return {@code true} if both blocks are free and can be merged, {@code false} otherwise
         */
        auto can_merge_blocks(const MemoryBlock& current, const MemoryBlock& next) -> bool; 

        /**
         * Merges two adjacent free memory blocks into one.
         * 
         * <p>This method combines the size of the current memory block with the 
         * size of the next memory block, effectively merging them into one. 
         * The size of the current block is increased by the size of the next block.</p>
         * 
         * @param current the memory block that will be expanded
         * @param next the adjacent memory block whose size will be added to the current block
         */
        void merge_blocks(MemoryBlock& current, const MemoryBlock& next);

        // @brief Merge free blocks
        void merge_free_blocks();
    };

} // namespace cse4733

#endif // CSE4733_MEMORYALLOCATOR_HPP
