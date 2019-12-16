#include "MessageSerializer.hpp"
#include <player_protocol/MessageFactory.hpp>


namespace player_protocol {
    std::uint32_t MessageSerializer::serialize(const Message &message, char* data) {
        data[0] = static_cast<char>(message.getMessageType());
        return message.serialize(data + 1) + 1;
    }

    std::unique_ptr<Message> MessageSerializer::deserialize(const char *data) {
        auto type = static_cast<MessageType>(data[0]);
        auto message = MessageFactory::create(type);
        message->deserialize(data + 1);
        return message;
    }
}