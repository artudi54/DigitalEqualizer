#include "TimeChangedMessage.hpp"
#include <cstring>

namespace player_protocol::changed {
    TimeChangedMessage::TimeChangedMessage()
        : currentTime(0.0f)
        , totalTime(0.0f) {}

    TimeChangedMessage::TimeChangedMessage(float currentTime, float totalTime)
        : currentTime(currentTime)
        , totalTime(totalTime) {}

    MessageType TimeChangedMessage::getMessageType() const {
        return MessageType::CHANGED_TIME;
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

    void TimeChangedMessage::visit(MessageVisitor &visitor) const {
        visitor.handleMessage(*this);
    }

    float TimeChangedMessage::getCurrentTime() const {
        return currentTime;
    }

    void TimeChangedMessage::setCurrentTime(float currentTime) {
        this->currentTime = currentTime;
    }

    float TimeChangedMessage::getTotalTime() const {
        return totalTime;
    }

    void TimeChangedMessage::setTotalTime(float totalTime) {
        this->totalTime = totalTime;
    }
}