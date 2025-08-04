#include <atomic>
#include <iostream>
#include <csignal>
#include <cstdlib>
#include <memory>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "cse4733/GlobalVariables.hpp"
#include "cse4733/ProcessManager.hpp"

auto main() -> int
{

    try
    {
        g_processManager = std::make_shared<cse4733::ProcessManager>();
        g_processManager->Run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
