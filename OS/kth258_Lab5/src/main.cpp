#include <fstream>
#include <iostream>
#include <iomanip>
#include "cse4733/AddressTranslator.hpp"
#include "cse4733/ConfigParser.hpp"

int main(int argc, char* argv[]) {
    // Check if a filename is provided
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return 1;
    }

    try {
        // Parse the configuration file
        std::string configFile = argv[1];
        std::ifstream fileStream(configFile);
        if (!fileStream) {
            std::cout << "Error opening config file: " << configFile << std::endl;
            return 1;
        }
        
        nlohmann::json config;
        config = cse4733::ConfigParser::parse(configFile);     
        
        // Create the address translator
        cse4733::AddressTranslator translator(config);

        // Print segment information
        translator.printInformation();

        // Check memory size
        translator.checkMemoryFit();

        // Translate addresses from input file
        translator.translateAddresses(config);
    } catch (const nlohmann::json::parse_error& ex) {
        std::cout << "Error parsing config file: " << ex.what() << std::endl;
        // Handle the parsing error as needed
    }
    catch (const nlohmann::json::other_error& ex) {
        std::cout << "Error parsing - other error: " << ex.what() << std::endl;
        // Handle the parsing error as needed
    }
    catch (const nlohmann::json::out_of_range& ex) {
        std::cout << "Error parsing - out of range error: " << ex.what() << std::endl;
        // Handle the parsing error as needed
    }
    catch (const nlohmann::json::type_error& ex) {
        std::cout << "Error parsing - type error: " << ex.what() << std::endl;
        // Handle the parsing error as needed
    }
    catch (const nlohmann::json::invalid_iterator& ex) {
        std::cout << "Error parsing - invalid iterator error: " << ex.what() << std::endl;
        // Handle the parsing error as needed
    }
    catch (std::runtime_error& ex)
    {
        std::cout << "Error parsing - runtime error: " << ex.what() << std::endl;
        // Handle the parsing error as needed
    }

    return 0;
}
