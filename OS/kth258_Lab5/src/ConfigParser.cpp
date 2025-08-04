#include <cse4733/ConfigParser.hpp>

#include <fstream>

namespace cse4733 {

    nlohmann::json ConfigParser::parse(const std::string& configFile) {
        std::ifstream configFileStream(configFile);
        if (!configFileStream) {
            throw std::runtime_error("Error opening config file: " + configFile);
        }
        
        return nlohmann::json::parse(configFileStream);
    }

} // namespace cse4733
