#ifndef PAGE_TABLE_ENTRY_H
#define PAGE_TABLE_ENTRY_H

namespace cse4733 {

// Structure representing a Page Table Entry (PTE)
struct page_table_entry {
    bool valid; // Valid bit
    unsigned int page_frame_number; // Page Frame Number (PFN)
};

}

#endif // PAGE_TABLE_ENTRY_H