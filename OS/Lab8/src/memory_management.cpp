#include "memory_management.hpp"
#include "invalid_page_table_entry_exception.hpp"
#include "invalid_virtual_address_exception.hpp"
#include "page_table_entry_not_found_exception.hpp"

#include <iostream>

namespace cse4733
{

    memory_management::memory_management()
    {
        /** TODO: Implement the constructor for the memory_management class
         * 1. Create an empty page table as a map with pairs
         *    of unsigned integers as keys and page_table_entry
         *    as values.
         * 2. Loop over the range from 0 to PAGE_DIRECTORY_SIZE
         *    a. Nested loop over the range from 0 to PAGE_TABLE_SIZE
         *       1) Create a pair of unsigned integers (i, j)
         *          as the key.
         *       2) Assign a new page_table_entry to the page table
         *          at the key.
         *       3) Set the valid bit of the page_table_entry to true
         *          and assign the page frame number as j.
         */
        // Loop over all page directory entries
        for (unsigned int i = 0; i < PAGE_DIRECTORY_SIZE; i++) {
            for (unsigned int j = 0; j < PAGE_TABLE_SIZE; j++) {
                std::pair<unsigned int, unsigned int> key(i, j);
                
                page_table_entry entry;
                entry.valid = true;
                entry.page_frame_number = j;
                
                m_pageTable[key] = entry;
            }
        }
    }


    auto memory_management::pageTableLookup(unsigned int virtualAddress) -> unsigned int
{
    // TODO: Implement the pageTableLookup method
    /**
     * 1. Function `pageTableLookup` takes an unsigned integer
     *    `virtualAddress` as a parameter
     * 2. Check if the `virtualAddress` is valid
     *    1. If the `virtualAddress` is greater than `MAX_VIRTUAL_ADDRESS`
     *       or less than 0, throw `invalid_virtual_address_exception`
     * 3. Calculate the `pageTableIndex`, `pageDirectoryIndex`, and
     *    `pageOffset` from the `virtualAddress`
     * 4. Create a pair of unsigned integers (`pageDirectoryIndex`, `pageTableIndex`)
     *    as the key
     * 5. Find the page table entry using the key
     *    a. If the entry does not exist in the page table, throw
     *       `page_table_entry_not_found_exception`
     * 6. Access the page table entry
     * 7. Check if the page table entry is valid
     *    a. If the page table entry is not valid,
     *       throw `invalid_page_table_entry_exception`
     * 8. Calculate the physical address using the page frame number
     *    from the page table entry and the `pageOffset`
     * 9. Print the virtual address, page directory index, page table index,
     *    and page offset
     * 10. Print the physical address
     * 11. Return the physical address
     */
    
    
    if (virtualAddress > MAX_VIRTUAL_ADDRESS)
    {
        throw invalid_virtual_address_exception();
    }
   
    unsigned int pageTableIndex = (virtualAddress & PAGE_TABLE_MASK) >> PAGE_TABLE_BIT_SHIFT;
    unsigned int pageDirectoryIndex = (virtualAddress & PAGE_DIRECTORY_MASK) >> PAGE_DIRECTORY_BIT_SHIFT;
    unsigned int pageOffset = virtualAddress & PAGE_OFFSET_MASK;
    
    std::pair<unsigned int, unsigned int> key(pageDirectoryIndex, pageTableIndex);

    auto it = m_pageTable.find(key);
    if (it == m_pageTable.end()) {
        throw page_table_entry_not_found_exception();
    }
    
    page_table_entry& entry = it->second;
    if (!entry.valid) {
        throw invalid_page_table_entry_exception();
    }

    unsigned int physicalAddress = (entry.page_frame_number << PAGE_FRAME_NUMBER_SHIFT) | pageOffset;
    
    std::printf("Virtual Address: 0x%08X\n", virtualAddress);
    std::printf("Page Directory Index: 0x%04X\n", pageDirectoryIndex);
    std::printf("Page Table Index: 0x%04X\n", pageTableIndex);
    std::printf("Page Offset: 0x%04X\n", pageOffset, pageOffset);
    std::printf("Physical Address: 0x%08X\n", physicalAddress);
    std::cout << std::endl;
    
    return physicalAddress;
    
}


} // namespace cse4733
