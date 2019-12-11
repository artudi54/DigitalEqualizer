#include "MessageSerializer.hpp"
#include <player_protocol/TimeChangedMessage.hpp>
#include <player_protocol/MediumChangedMessage.hpp>
#include <player_protocol/VolumeChanged.hpp>

#include <player_protocol/PlayRequest.hpp>

namespace player_protocol {

    std::unique_ptr<Message> makeMessage(MessageType type) {
        if (type == MessageType::MEDIUM_CHANGED)
            return std::make_unique<MediumChangedMessage>();
        if (type == MessageType::TIME_CHANGED)
            return std::make_unique<TimeChangedMessage>();
        if (type == MessageType::VOLUME_CHANGED)
            return std::make_unique<VolumeChanged>();
        if (type == MessageType::PLAY_REQUEST)
            return std::make_unique<PlayRequest>();
        return nullptr;
    }

    std::uint32_t MessageSerializer::serialize(const Message &message, char* data) {
        data[0] = static_cast<char>(message.getMessageType());
        return message.serialize(data + 1) + 1;
    }

    std::unique_ptr<Message> MessageSerializer::deserialize(const char *data) {
        auto type = static_cast<MessageType>(data[0]);
        auto message = makeMessage(type);
        message->deserialize(data + 1);
        return message;
    }
}