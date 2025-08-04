#include <iostream>

#include <Process.hpp>

namespace cse4733
{

Process::Process(const std::string process_id,
                 std::size_t memory_requirement)
    : process_id_{std::move(process_id)},
      memory_requirement_{memory_requirement},
      base_address_{0}
{}

void Process::allocate_memory(std::shared_ptr<IMemoryAllocator> memory_allocator)
{
    try {
        base_address_ = memory_allocator->allocate(process_id_, memory_requirement_);
        std::cout << "Memory allocated for process_id: " << process_id_ << std::endl;
        std::cout << "Starting address: " << std::hex << "0x" << base_address_ << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Memory allocation failed for process_id: " << process_id_ << std::endl;
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void Process::deallocate_memory(std::shared_ptr<IMemoryAllocator> memory_allocator)
{
    try {
        memory_allocator->deallocate(process_id_);
        std::cout << "Memory deallocated for process_id: " << process_id_ << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Memory deallocation failed for process_id: " << process_id_ << std::endl;
        std::cout << "Error: " << e.what() << std::endl;
    }
}

auto Process::get_base_address() const -> std::size_t
{
    return base_address_;
}

} // namespace cse4733
