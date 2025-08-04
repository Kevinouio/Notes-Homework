#include <MemoryBlock.hpp>

namespace cse4733
{

    MemoryBlock::MemoryBlock(std::size_t address, std::size_t size, std::string process_id)
        : m_start_address(address),
          m_size(size),
          m_process_id(std::move(process_id))
    {
    }

    auto MemoryBlock::operator=(MemoryBlock &&other) noexcept -> MemoryBlock &
    {
        if (this != &other)
        {
            // Perform the move assignment logic here
            m_start_address = other.m_start_address;
            m_size = other.m_size;
            m_process_id = std::move(other.m_process_id);

            // Reset the other object's data
            other.m_start_address = 0;
            other.m_size = 0;
            other.m_process_id.clear();
        }
        return *this;
    }

    auto MemoryBlock::operator=(const MemoryBlock &other) -> MemoryBlock &
    {
        if (this != &other)
        {
            // Perform the copy assignment logic here
            m_start_address = other.m_start_address;
            m_size = other.m_size;
            m_process_id = other.m_process_id;
        }
        return *this;
    }

    auto MemoryBlock::get_base_address() const -> std::size_t
    {
        return m_start_address;
    }

    void MemoryBlock::set_base_address(std::size_t address)
    {
        m_start_address = address;
    }

    auto MemoryBlock::get_size() const -> std::size_t
    {
        return m_size;
    }

    void MemoryBlock::set_size(std::size_t size)
    {
        m_size = size;
    }

    auto MemoryBlock::get_process_id() const -> const std::string &
    {
        return m_process_id;
    }

    void MemoryBlock::set_process_id(const std::string &id)
    {
        m_process_id = id;
    }

    auto MemoryBlock::empty() const -> bool
    {
        return m_size == 0;
    }

    auto operator<<(std::ostream &os, const MemoryBlock& block) -> std::ostream &
    {
        const auto address = block.get_base_address();
        const auto size = block.get_size();
        os << "[0x"
           << std::hex
           << address
           << "-"
           << address + size - 1
           << "] "
           << block.get_process_id() << " (0x" << size << " bytes)\n";
        return os;
    }

} // namespace cse4733