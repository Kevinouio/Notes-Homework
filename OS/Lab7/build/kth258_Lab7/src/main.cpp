#include <iomanip>
#include <iostream>
#include <vector>

#include <cse4733/MMU.hpp>

int main() {

    const unsigned int base_address = 0x30000000;

    // Create an MMU with a page table of size 10
    cse4733::MMU mmu(10, base_address, 10);

    // Add some entries to the page table
    // For simplicity, let's say that the physical address is the same as the virtual address
    for (unsigned int i = 0; i < 5; i++) {
        mmu.addEntry(i);
    }

    // Translate some virtual addresses
    // Some of these addresses are in the page table, and some are not
    std::vector<int> virtualAddresses {1, 2, 6, 11, 4, 9, 10, 14, 11, 11, 12, 7, 9, 11, 9, 12, 1, 15, 9, 11, 6, 2, 5, 4, 8, 8, 4, 7, 2, 6};
    for (int i : virtualAddresses) {
        try {
            int physicalAddress = mmu.translateAddress(i);
            std::cout << "Virtual address 0x" << std::hex << i << " translates to physical address 0x" << physicalAddress << std::endl;
        } catch (std::exception& e) {
            std::cout << "Error translating virtual address 0x" << i << ": " << e.what() << std::endl;
        }
    }

    // Print out the hit and miss ratios
    std::cout << "Hit ratio: " << mmu.getHitRatio() << std::endl;
    std::cout << "Miss ratio: " << mmu.getMissRatio() << std::endl;

    return 0;
}
