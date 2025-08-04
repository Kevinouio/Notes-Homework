#include "memory_management.hpp"

#include "invalid_page_table_entry_exception.hpp"
#include "invalid_virtual_address_exception.hpp"
#include "page_table_entry_not_found_exception.hpp"

#include <array>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <map>
#include <boost/program_options.hpp>

int main(int argc, char *argv[])
{
    // Declare the supported command-line options
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()("help,h", "produce help message");

    // Parse the command-line options
    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    // Display help message if requested or if the number of virtual addresses is not provided
    if (vm.count("help"))
    {
        std::cout << desc << "\n";
        return 1;
    }

    cse4733::memory_management memManager;

    // Define your 10 specific addresses
    std::array<unsigned long long, 10> addresses = {
        0x08004823, 
        0x08100588,
        0x09810482,
        0x19456780,
        0x23056789,
        0x67890112,
        0x78901554,
        0x89012110,
        0x90123779,
        0xA0123323};

    // Generate and simulate page table lookup for virtual addresses
    std::for_each(addresses.begin(), addresses.end(), [&](unsigned long long virtualAddress) {
        try
        {
            unsigned int physicalAddress = memManager.pageTableLookup(virtualAddress);
        }
        catch (const cse4733::invalid_virtual_address_exception &e)
        {
            std::cerr << "Invalid virtual address exception caught: " << e.what() << std::endl;
        }
        catch (const cse4733::page_table_entry_not_found_exception &e)
        {
            std::cerr << "Page table entry not found exception caught: " << e.what() << std::endl;
        }
        catch (const cse4733::invalid_page_table_entry_exception &e)
        {
            std::cerr << "Page table entry invalid exception caught: " << e.what() << std::endl;
        }
    });

    return 0;
}
