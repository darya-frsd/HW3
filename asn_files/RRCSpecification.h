#ifndef RRCSPECIFICATION_H
#define RRCSPECIFICATION_H

#include <vector>
#include <iostream>
#include <cstdint>

class RRCSpecification {
public:
    struct RRCConnectionSetupRequest {
        std::vector<uint8_t> subscriberId;

        void encode(std::vector<uint8_t>& buffer) const {
            buffer.insert(buffer.end(), subscriberId.begin(), subscriberId.end());
        }

        void decode(const std::vector<uint8_t>& buffer) {
            subscriberId = buffer;
        }

        size_t coderLength() const {
            return subscriberId.size();
        }
    };

    struct RRCConnectionSetupComplete {
        std::vector<uint8_t> subscriberId;

        void encode(std::vector<uint8_t>& buffer) const {
            buffer.insert(buffer.end(), subscriberId.begin(), subscriberId.end());
        }

        void decode(const std::vector<uint8_t>& buffer) {
            subscriberId = buffer;
        }

        size_t coderLength() const {
            return subscriberId.size();
        }
    };
};

#endif // RRCSPECIFICATION_H
