#include "TimeChangedMessage.hpp"
#include <cstring>

namespace player_protocol {
    MessageType player_protocol::TimeChangedMessage::getMessageType() const {
        return MessageType::TIME_CHANGED;
    }

    std::uint32_t TimeChangedMessage::serialize(char *data) const {
        std::uint32_t offset = 0;

        std::memcpy(data + offset, &currentTime, sizeof(float));
        offset += sizeof(float);

        std::memcpy(data + offset, &totalTime, sizeof(float));
        offset += sizeof(float);

        return offset;
    }

    void TimeChangedMessage::deserialize(const char *data) {
        std::uint32_t offset = 0;

        std::memcpy(&currentTime, data + offset, sizeof(float));
        offset += sizeof(float);

        std::memcpy(&totalTime, data + offset, sizeof(float));
        offset += sizeof(float);
    }
}