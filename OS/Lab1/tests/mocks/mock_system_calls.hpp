#include <gmock/gmock.h>
#include <cse4733/isystem_calls.hpp>

namespace cse4733 {

class MockSystemCalls : public ISystemCalls {
public:
    MOCK_METHOD(std::optional<pid_t>, Fork, (), (override));
    MOCK_METHOD(std::optional<int>, Execvp, (const char *file, std::vector<char*> argv), (override));
    MOCK_METHOD(std::optional<pid_t>, Waitpid, (pid_t pid, int *status, int options), (override));
    MOCK_METHOD(pid_t, Getpid, (), (override));
    MOCK_METHOD(pid_t, Getppid, (), (override));
};

} // namespace cse4733p