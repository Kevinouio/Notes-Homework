#include <cse4733/AddressTranslator.hpp>
#include <fstream>
#include <iostream>

namespace cse4733 {

AddressTranslator::AddressTranslator(const nlohmann::json& config) {
    readConfigData(config);
}

void AddressTranslator::printInformation() const {

    std::cout << "ARG address space size: " << this->addressSpaceSize << std::endl
              << "ARG physical memory size: " << this->physicalMemorySize << std::endl << std::endl;

    std::cout << "Segment Information:" << std::endl;
    for (const auto& segment : segments) {
        std::cout << "  Segment: " << segment.get_name() << std::endl;
        std::cout << "  Index: " << segment.get_index() << std::endl;
        std::cout << "  Base Address: " << segment.get_base() << std::endl;
        std::cout << "  Size: " << std::dec << segment.get_size() << std::endl;
        std::cout << std::endl;
    }
}

void AddressTranslator::translateAddresses(const nlohmann::json& config) {
    // Check if the 'addresses' field exists
    if (!config.contains("addresses")) {
        std::cout << "[ERROR] 'addresses' field not found in the configuration." << std::endl;
        return;
    }

    // Get the addresses array from the 'addresses' field
    const auto& addressesArray = config["addresses"];

    // Iterate over each address in the array
    for (const auto& address : addressesArray) {
        // Check if the address is a string
        if (address.is_number_unsigned()) {
            // Convert address from string to integer
            unsigned int addressInt = address.get<unsigned int>();

            translateAddress(addressInt);
        }
    }
}



void AddressTranslator::readConfigData(const nlohmann::json& config) {
    if (config.contains("address_space_size")) {
        addressSpaceSize = config["address_space_size"].get<int>();
    } else {
        throw std::runtime_error("[ERROR] Address space size not present in the configuration.");
    }

    if (config.contains("physical_memory_size")) {
        physicalMemorySize = config["physical_memory_size"].get<int>();
    } else {
        throw std::runtime_error("[ERROR] Physical memory size not present in the configuration.");
    }

    if (config.contains("segments")) {
        readSegmentData(config["segments"]);
        checkSegmentOverlap();
        checkMemoryFit();
    } else {
        throw std::runtime_error("[ERROR] Segments data not present in the configuration.");
    }
}

void AddressTranslator::readSegmentData(const nlohmann::json& segmentData) {
    for (const auto& segment : segmentData) {
        int index = segment["index"].get<int>();
        std::string name = segment["name"].get<std::string>();
        int base = segment["base"].get<int>();
        int size = segment["size"].get<int>();

        Segment seg(index, name, base, size);
        segments.push_back(seg);
    }
}


int AddressTranslator::calculateTranslatedAddress(int segmentId, int offset) const {
    const Segment& segment = segments[segmentId];
    int baseAddress = segment.get_base();
    return baseAddress + offset;
}

void AddressTranslator::translateAddress(unsigned int address) const {
    unsigned int segmentId = (address >> 30) & 0x3;  // Extract the top two bits for segment ID
    unsigned int offset = address & 0x3FFFFFFF;  // Extract the lower 30 bits for offset

    if (!isValidSegmentId(segmentId)) {
        reportSegmentationFault(segmentId, address);
        return;
    }

    unsigned int translatedAddress = calculateTranslatedAddress(segmentId, offset);

    if (!isAddressInBounds(translatedAddress, segments[segmentId])) {
        reportSegmentationFault(segmentId, address);
        return;
    }

    // Address translation successful
    std::cout << "Translated address: 0x" << std::hex << translatedAddress
              << '(' << std::dec << translatedAddress << ')' << std::endl;
}

void AddressTranslator::reportSegmentationFault(unsigned int segmentId, unsigned int address) const {
    unsigned int offset = address & 0x3FFFFFFF;  // Extract the lower 30 bits for offset
    unsigned int translatedAddress = calculateTranslatedAddress(segmentId, offset);
    const Segment& segment = segments[segmentId];

    std::cout << "[ERROR] Segmentation fault at address: 0x" << std::hex << address
              << std::dec << " (Segment: " << segmentId << " (" << segment.get_name() << ") )" << std::endl
              << "   Translated Address: 0x" << std::hex << translatedAddress
              << '(' << std::dec << translatedAddress << ')' << std::endl;
}

bool AddressTranslator::isValidSegmentId(unsigned int segmentId) const {
    return segmentId >= 0 && segmentId < segments.size();
}

bool AddressTranslator::isAddressInBounds(unsigned int address, const Segment& segment) const {
    return address >= segment.get_base() &&
            address < segment.get_base() + segment.get_size();
}

void AddressTranslator::checkMemoryFit() const {
    int totalSegmentMemorySize = 0;
    for (const auto& segment : segments) {
        totalSegmentMemorySize += segment.get_size();
    }

    if (totalSegmentMemorySize > physicalMemorySize) {
        std::cout << "[ERROR] Total segment memory size exceeds physical memory size." << std::endl;
    } else {
        std::cout << "[OK] Total segment memory size fits within physical memory size." << std::endl;
    }
}

void AddressTranslator::checkSegmentOverlap() const {
    // Sort the segments based on base address
    std::vector<Segment> sortedSegments = segments;
    std::sort(sortedSegments.begin(), sortedSegments.end(), [](const Segment& seg1, const Segment& seg2) {
        return seg1.get_base() < seg2.get_base();
    });

    // Check for overlap
    for (size_t i = 0; i < sortedSegments.size() - 1; ++i) {
        const Segment& currentSegment = sortedSegments[i];
        const Segment& nextSegment = sortedSegments[i + 1];

        unsigned int currentSegmentEndAddress = currentSegment.get_base() + currentSegment.get_size();
        unsigned int nextSegmentStartAddress = nextSegment.get_base();

        if (nextSegmentStartAddress - currentSegmentEndAddress < 0) {
            // Handle overlap
            std::cout << "[ERROR] Segment overlap detected between '" << currentSegment.get_name()
                      << "' and '" << nextSegment.get_name() << "'." << std::endl;
        }
    }
}


} // namespace cse4733
