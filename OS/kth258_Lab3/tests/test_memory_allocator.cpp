#include <gtest/gtest.h>
#include <stdexcept>
#include <memory>
#include <string>
#include <vector>
#include <cse4733/MemoryAllocator.hpp>

using namespace cse4733;

// Test fixture for MemoryAllocator class
class MemoryAllocatorTest : public ::testing::Test {
protected:
    std::shared_ptr<MemoryAllocator> memory_allocator;
    std::size_t total_memory_size = 0;

    void SetUpAllocator(std::size_t memory_size)
    {
        memory_allocator = std::make_shared<MemoryAllocator>(memory_size);
        total_memory_size = memory_size;
    }
};

TEST_F(MemoryAllocatorTest, Allocate_ValidBlockSize) {

    SetUpAllocator(0x200);

    // Allocate a block of size 100
    std::size_t allocated_address = memory_allocator->allocate("test_process", 100);

    // Verify the allocated address is within the valid range
    EXPECT_GE(allocated_address, 0);
    EXPECT_LT(allocated_address, total_memory_size);

    // Verify the allocated block exists in the memory layout
    const MemoryBlockList& memory_layout = memory_allocator->get_memory_layout();
    bool block_found = false;
    for (const auto& block : memory_layout) {
        if (block.get_base_address() == allocated_address &&
            block.get_size() == 100 &&
            block.get_process_id() == "test_process") {
            block_found = true;
            break;
        }
    }
    EXPECT_TRUE(block_found);
}

TEST_F(MemoryAllocatorTest, Allocate_InvalidBlockSize) {
    // Allocate a block with size 0
    SetUpAllocator(0x200);

    EXPECT_THROW(memory_allocator->allocate("test_process", 0), std::invalid_argument);

    // Allocate a block with size exceeding the total memory size
    EXPECT_THROW(memory_allocator->allocate("test_process", total_memory_size + 1), std::runtime_error);
}

TEST_F(MemoryAllocatorTest, Allocate_NoSuitableBlock) {
    SetUpAllocator(0x100);

    // Allocate a block of size 0x100
    memory_allocator->allocate("test_process", 0x100);

    EXPECT_THROW(memory_allocator->allocate("test_process", 200), std::runtime_error);
}