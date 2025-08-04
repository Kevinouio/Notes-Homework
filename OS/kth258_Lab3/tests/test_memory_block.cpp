#include <gtest/gtest.h>
#include <cse4733/MemoryBlock.hpp>

using namespace cse4733;

TEST(MemoryBlockTest, MoveAssignmentOperator) {
    // Create a source MemoryBlock object
    MemoryBlock source(0x1000, 100, "source_process");

    // Create a destination MemoryBlock object
    MemoryBlock destination(0x2000, 200, "destination_process");

    // Perform the move assignment
    destination = std::move(source);

    // Verify the destination object's data
    EXPECT_EQ(destination.get_base_address(), 0x1000);
    EXPECT_EQ(destination.get_size(), 100);
    EXPECT_EQ(destination.get_process_id(), "source_process");

    // Verify the source object's data
    EXPECT_EQ(source.get_base_address(), 0);
    EXPECT_EQ(source.get_size(), 0);
    EXPECT_TRUE(source.get_process_id().empty());
}

TEST(MemoryBlockTest, MoveAssignmentOperator_SameObject) {
    // Create a MemoryBlock object
    MemoryBlock block(0x1000, 100, "test_process");

    // Perform the move assignment
    block = std::move(block);

    // Verify the object's data remains unchanged
    EXPECT_EQ(block.get_base_address(), 0x1000);
    EXPECT_EQ(block.get_size(), 100);
    EXPECT_EQ(block.get_process_id(), "test_process");
}

TEST(MemoryBlockTest, AssignmentOperator) {
    // Create a source MemoryBlock object
    MemoryBlock source(0x1000, 100, "source_process");

    // Create a destination MemoryBlock object
    MemoryBlock destination(0x2000, 200, "destination_process");

    // Perform the assignment
    destination = source;

    // Verify the destination object's data
    EXPECT_EQ(destination.get_base_address(), 0x1000);
    EXPECT_EQ(destination.get_size(), 100);
    EXPECT_EQ(destination.get_process_id(), "source_process");

    // Verify the source object's data
    EXPECT_EQ(source.get_base_address(), 0x1000);
    EXPECT_EQ(source.get_size(), 100);
    EXPECT_EQ(source.get_process_id(), "source_process");
}

TEST(MemoryBlockTest, AssignmentOperator_SameObject) {
    // Create a source MemoryBlock object
    MemoryBlock source(0x1000, 100, "source_process");

    // Perform the assignment
    source = source;

    // Verify the source object's data
    EXPECT_EQ(source.get_base_address(), 0x1000);
    EXPECT_EQ(source.get_size(), 100);
    EXPECT_EQ(source.get_process_id(), "source_process");
}

TEST(MemoryBlockTest, SetBaseAddress) {
    // Create a MemoryBlock object
    MemoryBlock block(0x1000, 100, "test_process");

    // Set a new base address
    block.set_base_address(0x2000);

    // Verify the updated base address
    EXPECT_EQ(block.get_base_address(), 0x2000);
}

TEST(MemoryBlockTest, SetSize) {
    // Create a MemoryBlock object
    MemoryBlock block(0x1000, 100, "test_process");

    // Set a new ize
    block.set_size(0x2000);

    // Verify the updated size
    EXPECT_EQ(block.get_size(), 0x2000);
}

TEST(MemoryBlockTest, SetProcessId) {
    // Create a MemoryBlock object
    MemoryBlock block(0x1000, 100, "test_process");

    // Set a new base address
    block.set_process_id("new_process");

    // Verify the updated base address
    EXPECT_EQ(block.get_process_id(), "new_process");
}

TEST(MemoryBlockTest, AssignmentOperator_EmptyTrue) {
    // Create an empty MemoryBlock object
    MemoryBlock emptyBlock(0x0, 0, "");

    // Create a non-empty MemoryBlock object
    MemoryBlock nonEmptyBlock(0x1000, 100, "test_process");

    // Perform the assignment
    emptyBlock = nonEmptyBlock;

    // Verify the empty block's data
    EXPECT_EQ(emptyBlock.get_base_address(), 0x1000);
    EXPECT_EQ(emptyBlock.get_size(), 100);
    EXPECT_EQ(emptyBlock.get_process_id(), "test_process");
}

TEST(MemoryBlockTest, AssignmentOperator_EmptyFalse) {
    // Create a non-empty MemoryBlock object
    MemoryBlock nonEmptyBlock(0x1000, 100, "test_process");

    // Perform the assignment
    nonEmptyBlock = nonEmptyBlock;

    // Verify the non-empty block's data remains unchanged
    EXPECT_EQ(nonEmptyBlock.get_base_address(), 0x1000);
    EXPECT_EQ(nonEmptyBlock.get_size(), 100);
    EXPECT_EQ(nonEmptyBlock.get_process_id(), "test_process");
}
