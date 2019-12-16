#include "VolumeChangedMessage.hpp"
#include <cstring>

namespace player_protocol::changed {
    MessageType VolumeChangedMessage::getMessageType() const {
        return MessageType::CHANGED_VOLUME;
    }

    std::uint32_t VolumeChangedMessage::serialize(char *data) const {
        std::memcpy(data, &volume, sizeof(std::uint32_t));
        return sizeof(std::uint32_t);
    }

    void VolumeChangedMessage::deserialize(const char *data) {
        std::memcpy(&volume, data, sizeof(std::uint32_t));
    }
}

