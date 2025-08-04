#ifndef CSE4733__IMEMORY_ALLOCATOR_HPP
#define CSE4733__IMEMORY_ALLOCATOR_HPP

#include <string>

#include <MemoryBlockList.hpp>

namespace cse4733
{
    // Interface for memory allocators
    class IMemoryAllocator
    {
    public:
        // Destructor
        virtual ~IMemoryAllocator() = default;

        // @brief Allocate memory for a process
        // @param process_id The process id
        // @param size The size of the memory to allocate
        // @return The starting address of the allocated memory
        virtual auto allocate(const std::string &process_id, std::size_t size) -> std::size_t = 0;

        // @brief Deallocate memory for a process
        // @param process_id The process id
        virtual void deallocate(const std::string &process_id) = 0;

        // @brief Get the memory layout
        // @return The memory layout
        virtual auto get_memory_layout() -> MemoryBlockList & = 0;

        // @brief Get the amount of free space available
        // @return The amount of free space available
        virtual auto get_free_space() -> std::size_t = 0;
    };

}

#endif // CSE4733__IMEMORY_ALLOCATOR_HPP