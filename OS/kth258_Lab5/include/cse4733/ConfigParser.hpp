#ifndef CSE4733_CONFIGPARSER_HPP
#define CSE4733_CONFIGPARSER_HPP

#include <string>

#define JSON_DIAGNOSTIC_LEVEL 3
#include <nlohmann/json.hpp>

namespace cse4733 {

    class ConfigParser {
    public:
        static nlohmann::json parse(const std::string& configFile);
    };

} // namespace cse4733

#endif // CSE4733_CONFIGPARSER_HPP
