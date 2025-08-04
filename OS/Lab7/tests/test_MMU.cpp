#include <iostream>
#include "MMU.hpp"

int main() {
    // Test case 1
    cse4733::MMU mmu1(10, 0x1000, 0x200);
    std::cout << "Test case 1: MMU object created successfully!" << std::endl;

    // Test case 2
    cse4733::MMU mmu2(5, 0x2000, 0x400);
    std::cout << "Test case 2: MMU object created successfully!" << std::endl;

    // Add more test cases as needed...

    return 0;
}