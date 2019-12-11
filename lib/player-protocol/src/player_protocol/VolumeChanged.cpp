#include "VolumeChanged.hpp"
#include <cstring>

namespace player_protocol {
    MessageType VolumeChanged::getMessageType() const {
        return MessageType::VOLUME_CHANGED;
    }

    std::uint32_t VolumeChanged::serialize(char *data) const {
        std::memcpy(data, &volume, sizeof(std::uint32_t));
        return sizeof(std::uint32_t);
    }

    void VolumeChanged::deserialize(const char *data) {
        std::memcpy(&volume, data, sizeof(std::uint32_t));
    }
}


