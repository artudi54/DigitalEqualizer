#include "SeekRequest.hpp"
#include <cstring>

namespace player_protocol::request {
    MessageType SeekRequest::getMessageType() const {
        return MessageType::REQUEST_SEEK;
    }

    std::uint32_t SeekRequest::serialize(char *data) const {
        std::memcpy(data, &position, sizeof(float));
        return sizeof(float);
    }

    void SeekRequest::deserialize(const char *data) {
        std::memcpy(&position, data, sizeof(float));
    }
}