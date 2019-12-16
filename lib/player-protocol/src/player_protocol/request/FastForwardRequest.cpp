#include "FastForwardRequest.hpp"
#include <cstring>

namespace player_protocol::request {
    MessageType FastForwardRequest::getMessageType() const {
        return MessageType::REQUEST_FAST_FORWARD;
    }

    std::uint32_t FastForwardRequest::serialize(char *data) const {
        std::memcpy(data, &difference, sizeof(float));
        return sizeof(float);
    }

    void FastForwardRequest::deserialize(const char *data) {
        std::memcpy(&difference, data, sizeof(float));
    }
}