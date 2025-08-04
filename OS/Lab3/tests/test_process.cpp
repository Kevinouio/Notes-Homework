#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cse4733/Process.hpp>
#include <cse4733/IMemoryAllocator.hpp>

#include "mocks/MockMemoryAllocator.hpp"

using namespace testing;

// Test fixture for Process class
class ProcessTest : public ::testing::Test
{
protected:
    std::shared_ptr<MockMemoryAllocator> memory_allocator_mock;
    std::shared_ptr<cse4733::Process> process;

    // Define default constructor for ProcessTest class
    ProcessTest() = default;

    void SetUp() override
    {
        memory_allocator_mock = std::make_shared<MockMemoryAllocator>();
    }

    void SetupAllocator(const std::string &process_id,
                        std::size_t block_size,
                        std::size_t base_address)
    {
        process = std::make_shared<cse4733::Process>(process_id, block_size);

        ON_CALL(*memory_allocator_mock, allocate(process_id, block_size))
            .WillByDefault(Return(base_address));
        ON_CALL(*memory_allocator_mock, deallocate(process_id))
            .WillByDefault(Return());
    }
};

TEST_F(ProcessTest, AllocateMemory_Success)
{

    SetupAllocator("test_process", 100, 0);

    // Set expectations
    EXPECT_CALL(*memory_allocator_mock, allocate("test_process", 100))
        .WillOnce(Return(0x1000));
    EXPECT_EQ(process->get_base_address(), 0);

    // Call the function
    process->allocate_memory(memory_allocator_mock);
}

TEST_F(ProcessTest, DeallocateMemory_Success)
{

    SetupAllocator("test_process", 100, 0);

    EXPECT_CALL(*memory_allocator_mock, deallocate("test_process"))
        .Times(1); // Expect the deallocate function to be called once

    // Call the function
    process->deallocate_memory(memory_allocator_mock);
}