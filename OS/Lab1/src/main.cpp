#include <process.hpp>
#include <system_calls.hpp>

#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <boost/spirit/include/qi.hpp>

bool parsePath(std::string env_str, std::vector<std::string>& pathComponents)
{
    boost::spirit::qi::rule<std::string::iterator, std::string()> component = +(boost::spirit::qi::char_ - ':');
    boost::spirit::qi::rule<std::string::iterator, std::vector<std::string>()> pathGrammar = component % ':';

    // Parse the path
    auto it = env_str.begin();
    auto end = env_str.end();
    bool success = boost::spirit::qi::parse(it, end, pathGrammar, pathComponents);

    // Check if parsing was successful
    if (success && it == end) {
        std::cout << "Parsed " << pathComponents.size() << " path components." << std::endl;
        return true;
    } else {
        std::cerr << "Failed to parse the path." << std::endl;
        return false;
    }
}

std::optional<std::string> getFullCommandPath(const std::string& command) {
    std::vector<std::string> paths;

    const char* pathEnv = getenv("PATH");
    if (!pathEnv) {
        std::cerr << "PATH environment variable is not set." << std::endl;
        return std::nullopt;
    }

    if (!parsePath(pathEnv, paths)) {
        std::cerr << "Failed to parse the PATH." << std::endl;
        return std::nullopt;
    }

    for (const auto& path : paths) {
        std::filesystem::path filePath(path + '/' + command);
        if (std::filesystem::exists(filePath) &&
            std::filesystem::is_regular_file(filePath) &&
            (std::filesystem::status(filePath).permissions() & std::filesystem::perms::owner_exec) != std::filesystem::perms::none)
        {
            return filePath.string();
        }
    }

    std::cerr << "Command not found in PATH." << std::endl;
    return std::nullopt;
}

int main (int argc, char** argv)
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <command> [args...]" << std::endl;
        return 1;
    }

    // Get the full path of the command
    auto commandPathOpt = getFullCommandPath(argv[1]);
    if (!commandPathOpt.has_value()) {
        std::cerr << "Command not found." << std::endl;
        return 1;
    }

    std::string commandPath = commandPathOpt.value();

    // Set up the command and arguments for execvp()
    std::vector<std::string> commandArgs;
    for (int i = 1; i < argc; ++i) {
        commandArgs.push_back(argv[i]);
    }

        auto sysCalls = std::make_shared<cse4733::SystemCalls>();
    cse4733::process process(sysCalls, commandPath, commandArgs);

    if (process.execute()) {
        process.wait();
        if (!process.getErrorMessage().empty()) {
            std::cerr << "Error: " << process.getErrorMessage() << std::endl;
            return 1;
        }
        std::cout << "Child process " << process.get_id() << " terminated normally." << std::endl;
        auto statusOpt = process.wait();
        if (!statusOpt.has_value()) {
            std::cerr << "Failed to wait for child process." << std::endl;
            return 1;
        }
        std::cout << "Child process terminated with status: " << statusOpt.value() << std::endl;
    } else {
        std::cerr << "Error: " << process.getErrorMessage() << std::endl;
        return 1;
    }

    return 0;
}
