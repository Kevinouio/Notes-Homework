#ifndef CSE4733_INVALID_PAGE_TABLE_ENTRY_EXCEPTION_HPP
#define CSE4733_INVALID_PAGE_TABLE_ENTRY_EXCEPTION_HPP

#include <stdexcept>

namespace cse4733 {

class invalid_page_table_entry_exception : public std::runtime_error {
public:
    invalid_page_table_entry_exception() : std::runtime_error("Page table entry is invalid. Page fault!") {}
};

} // namespace cse4733

#endif // CSE4733_INVALID_PAGE_TABLE_ENTRY_EXCEPTION_HPP