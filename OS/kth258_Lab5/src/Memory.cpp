#include <cse4733/Memory.hpp>

namespace cse4733 {

    Memory::Memory(int addressSpaceSize, int physicalMemorySize, const std::vector<Segment>& segments)
        : addressSpaceSize(addressSpaceSize), physicalMemorySize(physicalMemorySize), segments(segments) {}

    const std::vector<Segment>& Memory::getSegments() const {
        return segments;
    }

} // namespace cse4733
