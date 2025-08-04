#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mocks/mock_system_calls.hpp"
#include "process.hpp"

#include <iostream>

using ::testing::Return;

TEST(ProcessTest, ForkReturnsNonZero) {
    std::shared_ptr<cse4733::MockSystemCalls> mockSysCalls = std::make_shared<cse4733::MockSystemCalls>();
    std::string command = "ls";
    std::vector<std::string> args = {"/bin"};

    EXPECT_CALL(*mockSysCalls, Fork()).WillOnce(::testing::Return(1));
    EXPECT_CALL(*mockSysCalls, Getpid()).WillOnce(::testing::Return(1234));

    cse4733::process process(mockSysCalls, command, args);

    process.execute();
}

TEST(ProcessTest, ForkReturnsZero) {
    std::shared_ptr<cse4733::MockSystemCalls> mockSysCalls = std::make_shared<cse4733::MockSystemCalls>();
    std::string command = "ls";
    std::vector<std::string> args {"/bin"};

    testing::Mock::AllowLeak(mockSysCalls.get());

    EXPECT_CALL(*mockSysCalls, Fork()).WillOnce(::testing::Return(0));
    EXPECT_CALL(*mockSysCalls, Getpid()).WillOnce(::testing::Return(1234));
    EXPECT_CALL(*mockSysCalls, Getppid()).WillOnce(::testing::Return(5678));
    EXPECT_CALL(*mockSysCalls, Execvp(::testing::_, ::testing::_)).WillOnce(Return(std::optional<int>(0)));

    cse4733::process process(mockSysCalls, command, args);
    auto result = process.execute();
    EXPECT_FALSE(result);
}

TEST(ProcessTest, ForkFails) {
    std::shared_ptr<cse4733::MockSystemCalls> mockSysCalls = std::make_shared<cse4733::MockSystemCalls>();
    std::string command = "ls";
    std::vector<std::string> args = {"/bin"};

    EXPECT_CALL(*mockSysCalls, Fork()).Times(1).WillOnce(Return(std::nullopt));

    cse4733::process process(mockSysCalls, command, args);

    auto result = process.execute();

    EXPECT_FALSE(result);
    EXPECT_EQ(process.getErrorMessage(), "Failed to create child process.\n");
}

int main(int argc, char** argv) {
    // Initialize Google Test
    ::testing::InitGoogleTest(&argc, argv);

    // Run all the tests
    return RUN_ALL_TESTS();
}

