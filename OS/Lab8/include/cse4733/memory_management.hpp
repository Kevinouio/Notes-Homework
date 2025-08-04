#ifndef CSE4733_MEMORY_MANAGEMENT_HPP
#define CSE4733_MEMORY_MANAGEMENT_HPP

#include "page_table_entry.hpp"

#include <map>
#include <limits>

namespace cse4733
{

    class memory_management
    {
    private:

        /**
         * @brief Page table
         */
        std::map<std::pair<unsigned int, unsigned int>, page_table_entry> m_pageTable;

        const unsigned int PAGE_TABLE_MASK = 0x3FF000;        // bits 12-21
        const unsigned int PAGE_TABLE_BIT_SHIFT = 12;
        const unsigned int PAGE_DIRECTORY_MASK = 0xFFC00000;  // bits 22-31
        const unsigned int PAGE_DIRECTORY_BIT_SHIFT = 22;
        const unsigned int PAGE_OFFSET_MASK = 0x0FFF;         // bits 0-11
        const unsigned int PAGE_FRAME_NUMBER_SHIFT = 22;


        // Maximum virtual address
        const unsigned int MAX_VIRTUAL_ADDRESS = std::numeric_limits<unsigned int>::max();

    public:
        /**
         * Constants
         */

        /**
         * @brief Page size in bytes
         */
        static const unsigned int PAGE_SIZE = 4096;

        /**
         * @brief Number of entries in page table
         */
        static const unsigned int PAGE_TABLE_SIZE = 1024;

        /**
         * @brief Number of entries in page directory
         */
        static const unsigned int PAGE_DIRECTORY_SIZE = 1024;

        /**
         * Constructor
         */
        memory_management();

        /**
         * Destructor
        */
        ~memory_management() = default;

        /**
         *
         * @brief A virtual address can be further broken down into individual bits,
         * each representing a specific component of the address. Here's the
         * bit breakdown of a virtual address:
         *
         *--------------------------------------------------------------
         * Assuming a 32-bit virtual address space:
         *
         * The highest-order bits represent the page directory index.
         * The next set of bits represents the page table index.
         * The remaining bits represent the page offset.
         * Here's an example breakdown of a 32-bit virtual address:
         *
         * 31            22            12                0
         * +--------------+--------------+----------------+
         * | Page Dir.    | Page Table   | Page Offset    |
         * | Index        | Index        |                |
         * +--------------+--------------+----------------+
         *
         * @param virtualAddress The virtual address
         * @return The physical address
         */
        auto pageTableLookup(unsigned int virtualAddress) -> unsigned int;
    };

} // namespace cse4733

#endif // CSE4733_MEMORY_MANAGEMENT_HPP