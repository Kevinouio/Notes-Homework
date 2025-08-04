#ifndef MOCK_MEMORY_ALLOCATOR_HPP
#define MOCK_MEMORY_ALLOCATOR_HPP

#include <gmock/gmock.h>

#include <cse4733/IMemoryAllocator.hpp>
#include <cse4733/MemoryBlockList.hpp>

// Mock class for MemoryAllocator
class MockMemoryAllocator : public cse4733::IMemoryAllocator
{
public:

    MOCK_METHOD(std::size_t, allocate, (const std::string &process_id, std::size_t size), (override));
    MOCK_METHOD(void, deallocate, (const std::string &process_id), (override));
    MOCK_METHOD(cse4733::MemoryBlockList &, get_memory_layout, (), (override));
    MOCK_METHOD(std::size_t, get_free_space, (), (override));
};

#endif // MOCK_MEMORY_ALLOCATOR_HPP