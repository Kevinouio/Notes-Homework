#include <cse4733/TLB.hpp>

namespace cse4733
{

    void TLB::addEntry(unsigned int virtualAddress, unsigned int physicalAddress)
    {
        // TODO: Implement this function
        // 1. Add the virtual address and physical address to the entries map
        entries[virtualAddress] = physicalAddress;
    }

    auto TLB::searchTLB(unsigned int virtualAddress) -> std::optional<unsigned int>
    {
        // TODO: Implement this function
        // 1. Search the entries map for the virtual address
        auto it = entries.find(virtualAddress);
        //    a. If the virtual address is found, return the physical address
        if (it != entries.end()) {
            return it->second;
        }
        //    b. If the virtual address is not found, return nullopt
        return std::nullopt;
    }

} // namespace cse4733
