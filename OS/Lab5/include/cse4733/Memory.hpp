#ifndef CSE4733_MEMORY_HPP
#define CSE4733_MEMORY_HPP

#include <vector>
#include "Segment.hpp"

namespace cse4733 {

    class Memory {
    private:
        int addressSpaceSize;
        int physicalMemorySize;
        std::vector<Segment> segments;

    public:
        Memory(int addressSpaceSize, int physicalMemorySize, const std::vector<Segment>& segments);

        const std::vector<Segment>& getSegments() const;
    };

} // namespace cse4733

#endif // CSE4733_MEMORY_HPP
