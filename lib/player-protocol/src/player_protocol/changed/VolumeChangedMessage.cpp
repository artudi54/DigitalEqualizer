#include "VolumeChangedMessage.hpp"
#include <cstring>

namespace player_protocol::changed {
    VolumeChangedMessage::VolumeChangedMessage()
            : volume(0) {}

    VolumeChangedMessage::VolumeChangedMessage(std::uint32_t volume)
            : volume(volume) {}

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

    void VolumeChangedMessage::visit(MessageVisitor &visitor) const {
        visitor.handleMessage(*this);
    }

    std::uint32_t VolumeChangedMessage::getVolume() const {
        return volume;
    }

    void VolumeChangedMessage::setVolume(std::uint32_t volume) {
        this->volume = volume;
    }
}


