#ifndef CSE4733_PAGE_TABLE_ENTRY_NOT_FOUND_EXCEPTION_HPP
#define CSE4733_PAGE_TABLE_ENTRY_NOT_FOUND_EXCEPTION_HPP

#include <stdexcept>

namespace cse4733 {

class page_table_entry_not_found_exception : public std::runtime_error {
public:
    page_table_entry_not_found_exception() : std::runtime_error("Page table entry not found. Page fault!") {}
};

} // namespace cse4733

#endif // CSE4733_PAGE_TABLE_ENTRY_NOT_FOUND_EXCEPTION_HPP