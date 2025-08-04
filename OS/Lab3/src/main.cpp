#include <MemoryAllocator.hpp>
#include <MemoryBlock.hpp>
#include <Process.hpp>

#include <algorithm>
#include <iostream>
#include <memory>

void print_layout(const std::string& title, std::shared_ptr<cse4733::MemoryAllocator> memory_allocator)
{

    std::cout << title << std::endl;
    auto memory = memory_allocator->get_memory_layout();

    for (const auto& block : memory) {
        std::cout << block << std::endl;
    }
}

int main()
{
    try {
        // Create memory allocator with a total memory size
        auto memory_allocator = std::make_shared<cse4733::MemoryAllocator>(8192);

        // Print the initial memory layout
        print_layout("Original Memory Layout:", memory_allocator);

        // Create processes with their respective memory requirements
        cse4733::Process process1("Process A", 2048);
        cse4733::Process process2("Process B", 4096);
        cse4733::Process process3("Process C", 1024);

        // Allocate memory for processes
        process1.allocate_memory(memory_allocator);
        process2.allocate_memory(memory_allocator);
        process3.allocate_memory(memory_allocator);

        // Print the initial memory layout
        print_layout("Allocated Memory Layout:", memory_allocator);

        // Deallocate memory for processes
        process2.deallocate_memory(memory_allocator);

        // Print the initial memory layout
        print_layout("After deallocate process 2:", memory_allocator);

        process3.deallocate_memory(memory_allocator);

        // Print the updated memory layout
        print_layout("Updated Memory Layout:", memory_allocator);
    }
    catch(std::runtime_error e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

