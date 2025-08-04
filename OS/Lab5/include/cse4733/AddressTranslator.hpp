#ifndef CSE4733_ADDRESSTRANSLATOR_HPP
#define CSE4733_ADDRESSTRANSLATOR_HPP

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include <cse4733/Segment.hpp>

namespace cse4733 {

class AddressTranslator {
public:
    AddressTranslator(const nlohmann::json& config);

    void printInformation() const;
    void translateAddresses(const nlohmann::json& addressData);
    void checkMemoryFit() const;

private:
    void readConfigData(const nlohmann::json& config);
    void readSegmentData(const nlohmann::json& config);
    void translateAddress(unsigned int address) const;
    void reportSegmentationFault(unsigned int segmentId, unsigned int address) const;
    bool isValidSegmentId(unsigned int segmentId) const;
    bool isAddressInBounds(unsigned int address, const Segment& segment) const;
    int calculateTranslatedAddress(int segmentId, int offset) const;
    void checkSegmentOverlap() const;

    int addressSpaceSize;
    int physicalMemorySize;
    std::vector<Segment> segments;
};

} // namespace cse4733

#endif // CSE4733_ADDRESSTRANSLATOR_HPP
