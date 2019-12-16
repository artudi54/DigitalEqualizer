#include "ChangeVolumeRequest.hpp"
#include <cstring>

namespace player_protocol::request {
    MessageType ChangeVolumeRequest::getMessageType() const {
        return MessageType::REQUEST_CHANGE_VOLUME;
    }

    std::uint32_t ChangeVolumeRequest::serialize(char *data) const {
        std::memcpy(data, &newVolume, sizeof(std::uint32_t));
        return sizeof(std::uint32_t);
    }

    void ChangeVolumeRequest::deserialize(const char *data) {
        std::memcpy(&newVolume, data, sizeof(std::uint32_t));
    }
}