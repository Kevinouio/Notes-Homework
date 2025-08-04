#include <cse4733/Segment.hpp>

namespace cse4733 {

int Segment::get_index() const
{
    return index;
}

const std::string &Segment::get_name() const
{
    return name;
}

unsigned int Segment::get_base() const
{
    return base;
}

unsigned int Segment::get_size() const
{
    return size;
}

Segment::Segment(int index, const std::string& name, int base, int size)
        : index(index), name(name), base(base), size(size) {}

} // namespace cse4733
