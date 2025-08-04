#include <cse4733/MMU.hpp>
#include <iostream>
#include <stdexcept>

namespace cse4733 {

MMU::MMU(int numPages, unsigned int base_address, unsigned int offset) :
    pageTable(),
    tlbHits{0},
    tlbMisses{0},
    m_base_address(base_address),
    m_offset(offset)  // Added this line as offset was not initialized in the class
{}

auto MMU::addEntry(unsigned int virtualAddress) -> unsigned int
{
    // TODO: Implement this function
    // 1. Create the physical address equal to the virtual address plus the base address
    unsigned int physicalAddress = virtualAddress + m_base_address;
    // 2. Add the translation to the TLB
    tlb.addEntry(virtualAddress, physicalAddress);
    // 3. Calculate where to insert the physical address into the page table
    // 4. Add the physical address to the page table
    pageTable[virtualAddress] = physicalAddress;
    return physicalAddress;
}

unsigned int MMU::translateAddress(unsigned int virtualAddress) {

    // TODO:
    //
    // This function should translate a given virtual address to a physical address:
    //
    // 1. It should check that the address is within the 0 to offset range bounds.
    //    Throw an exception of std::out_of_range if it is not.
    if (virtualAddress >= m_offset) {
        throw std::out_of_range("Virtual address out of bounds");
    }
    
    // 2. It should check if the translation is in the TLB (a TLB hit).
    //    a. If it is, it should return the physical address from the TLB
    //       and increment the count of TLB hits.
    auto tlbResult = tlb.searchTLB(virtualAddress);
    if (tlbResult.has_value()) {
        tlbHits++;
        return tlbResult.value();
    } else {
        // 3. If it is NOT in the TLB (a TLB miss), it should:
        //    a. It should look up the physical address in the page table with
        //       the 'virtual address' variable.
        //    b. If the physical address IS NOT in the page table, it should
        //       1) Set the physical address to the virtual address plus the base address
        unsigned int physicalAddress = virtualAddress + m_base_address;
        //       2) Add the translation to the TLB
        tlb.addEntry(virtualAddress, physicalAddress);
        //       3) Store the physical address in the page table
        pageTable[virtualAddress] = physicalAddress;
        //    c. Otherwise, the physical address IS in the page table, it should
        //       1) Create an entry in the TLB table (already handled above)
        //    d. Increment the count of TLB misses.
        tlbMisses++;
        // 4. Return the physical address.
        return physicalAddress;
    }
}

auto MMU::getHitRatio() const -> double
{
    // TODO:
    //   - Calculate HIT ratio
    unsigned int total = tlbHits + tlbMisses;
    if (total == 0) {
        return 0.0;
    }
    return static_cast<double>(tlbHits) / total;
}

auto MMU::getMissRatio() const -> double
{
    // TODO:
    //   - Calculate MISS ratio
    unsigned int total = tlbHits + tlbMisses;
    if (total == 0) {
        return 0.0;
    }
    return static_cast<double>(tlbMisses) / total;
}

}  // namespace cse4733
