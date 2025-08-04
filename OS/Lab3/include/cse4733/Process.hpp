#ifndef CSE4733_PROCESS_HPP
#define CSE4733_PROCESS_HPP

#include <memory>
#include <string>

#include <IMemoryAllocator.hpp>

namespace cse4733
{
    // @brief Process class
    // @details This class represents a process
    //          that requests memory from the memory allocator.
    //          The process can allocate and deallocate memory.
    //          The process is identified by a process id.
    //          The process has a memory requirement.
    //          The process can allocate memory from the memory allocator.
    //          The process can deallocate memory from the memory allocator.
    //          The process can print its memory layout.
    //          The process can print the memory layout of the memory allocator.
    class Process
    {
    public:

        // @brief Constructor
        // @param process_id: process id
        // @param memory_requirement: memory requirement in bytes
        Process(const std::string process_id, std::size_t memory_requirement);

        // @brief Allocate memory for the process
        // @param memory_allocator: memory allocator
        void allocate_memory(std::shared_ptr<IMemoryAllocator> memory_allocator);

        // @brief Deallocate memory for the process
        // @param memory_allocator: memory allocator
        void deallocate_memory(std::shared_ptr<IMemoryAllocator> memory_allocator);

        // @brief Retrieve the base address of the allocated memory
        // @return base address of the allocated memory
        auto get_base_address() const -> std::size_t;

    private:

        // @brief Process id
        std::string process_id_;

        // @brief Memory requirement in bytes
        std::size_t memory_requirement_;

        // @brief Base address of the allocated memory
        std::size_t base_address_;
    };

} // namespace cse4733

#endif // CSE4733_PROCESS_HPP
