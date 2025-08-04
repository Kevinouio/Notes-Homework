#ifndef CSE4733_SEGMENT_HPP
#define CSE4733_SEGMENT_HPP

#include <string>

namespace cse4733 {

    class Segment {
    private:

        int index;
        std::string name;
        int base;
        int size;

    public:
        Segment(int index, const std::string& name, int base, int size);

        int get_index() const;
        const std::string &get_name() const;
        unsigned int get_base() const;
        unsigned int get_size() const;
    };

} // namespace cse4733

#endif // CSE4733_SEGMENT_HPP
