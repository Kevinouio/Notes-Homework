#include <map>
#include <optional>
#include <utility>

namespace cse4733 {

class TLB {
private:

    /**
     * @brief entries Map of the virtual to memory addresses loaded in memory.
     * key: = virtual memory address for the memory location.
     * value: = physical memory address for the memory location.
     */
    std::map<unsigned int, unsigned int> entries;

public:

    /**
     * @brief addEntry Create a memory location within the TLB.
     * @param virtualAddress Virtual memory address of the memory location.
     * @param physicalAddress The physical memory address of the memory location.
     */
    void addEntry(unsigned int virtualAddress, unsigned int physicalAddress);

    /**
     * @brief searchTLB Find the physical address for the virtual memory address.
     * @param virtualAddress Virtual memory address of the memory location.
     * @return -1 if there is no entry for the virtual address. Otherwise return
     * the physical address for the virtual memory address.
     */
    auto searchTLB(unsigned int virtualAddress) -> std::optional<unsigned int>;
};

}  // namespace cse4733
