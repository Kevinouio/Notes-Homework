#ifndef CSE4733_MEMORYBLOCK_HPP
#define CSE4733_MEMORYBLOCK_HPP

#include <ostream>
#include <string>

namespace cse4733
{

    class MemoryBlock
    {
    private:
        std::size_t m_start_address;
        std::size_t m_size;
        std::string m_process_id;

    public:
        /**
         * @brief MemoryBlock Create a new memory block
         * @param address Integer value of the starting address.
         * @param size Integer value of the memory block in bytes.
         * @param process_id String representation of the owner process.
         */
        MemoryBlock(std::size_t address, std::size_t size, std::string process_id);

        // Default destructor
        ~MemoryBlock() = default;

        /**
         * @brief Copy constuctor
         * @param obj Handle to the object to be copied.
         * @return Reference to the new object.
         * @note This is a deep copy.
         */
        MemoryBlock(const MemoryBlock &obj) = default;
        
        // @brief Default move operator
        // @param other Handle to the object to be moved.
        // @return Reference to the new object.
        // @note This is a shallow copy.
        MemoryBlock(MemoryBlock &&other) = default;

        // @brief Move assignment operator
        // @param other Handle to the object to be moved.
        // @return Reference to the new object.
        // @note This is a shallow copy.
        auto operator=(MemoryBlock &&other) noexcept -> MemoryBlock &;

        // @brief Copy assignment operator
        // @param other Handle to the object to be copied.
        // @return Reference to the new object.
        // @note This is a deep copy.
        auto operator=(const MemoryBlock &other) -> MemoryBlock &;

        /**
         * Retrieve the starting address
         * @return Integer value of the starting address.
         * @note This is a deep copy.
         */
        auto get_base_address() const -> std::size_t;

        /**
         * Set the starting address.
         * @param address Integer value of the starting address.
         * @note This is a deep copy.
         */
        void set_base_address(std::size_t address);

        /**
         * Set the size.
         * @param size Integer value of the memory block in bytes.
         * @note This is a deep copy.
         */
        void set_size(std::size_t size);

        /**
         * Retrieve the size
         * @return Integer value of the memory block in bytes.
         * @note This is a deep copy.
         */
        auto get_size() const -> std::size_t;

        /**
         * Retrieve the process id
         * @return String representation of the owner process.
         */
        auto get_process_id() const -> const std::string &;

        /**
         * Set the process id
         * @param id String representation of the owner process.
         */
        void set_process_id(const std::string &id);

        /**
         * Determine if the memory block is empty.
         * @return True if the memory block is empty, false otherwise.
         */
        auto empty() const -> bool;

    };

    /**
     * @brief operator <<
     * @param os Output stream where the string representation of MemoryBlock is placed.
     * @return Reference to the filled output stream.
     */
    auto operator<<(std::ostream &os, const MemoryBlock &) -> std::ostream &;

} // namespace cse4733

#endif // CSE4733_MEMORYBLOCK_HPP
