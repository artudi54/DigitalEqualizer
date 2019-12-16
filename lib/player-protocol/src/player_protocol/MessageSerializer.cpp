#include "MessageSerializer.hpp"
#include <player_protocol/changed/TimeChangedMessage.hpp>
#include <player_protocol/changed/MediumChangedMessage.hpp>
#include <player_protocol/changed/VolumeChangedMessage.hpp>

#include <player_protocol/request/ChangeMediumRequest.hpp>
#include <player_protocol/request/ChangeVolumeRequest.hpp>
#include <player_protocol/request/FastForwardRequest.hpp>
#include <player_protocol/request/PlayRequest.hpp>
#include <player_protocol/request/PauseRequest.hpp>
#include <player_protocol/request/StopRequest.hpp>

#include <player_protocol/response/OkResponse.hpp>
#include <player_protocol/response/ErrorResponse.hpp>

namespace player_protocol {
    std::unique_ptr<Message> makeMessage(MessageType type) {
        if (type == MessageType::CHANGED_MEDIUM)
            return std::make_unique<changed::MediumChangedMessage>();
        if (type == MessageType::CHANGED_TIME)
            return std::make_unique<changed::TimeChangedMessage>();
        if (type == MessageType::CHANGED_VOLUME)
            return std::make_unique<changed::VolumeChangedMessage>();

        if (type == MessageType::REQUEST_CHANGE_MEDIUM)
            return std::make_unique<request::ChangeMediumRequest>();
        if (type == MessageType::REQUEST_CHANGE_VOLUME)
            return std::make_unique<request::ChangeVolumeRequest>();
        if (type == MessageType::REQUEST_FAST_FORWARD)
            return std::make_unique<request::FastForwardRequest>();
        if (type == MessageType::REQUEST_PLAY)
            return std::make_unique<request::PlayRequest>();
        if (type == MessageType::REQUEST_PAUSE)
            return std::make_unique<request::PauseRequest>();
        if (type == MessageType::REQUEST_STOP)
            return std::make_unique<request::StopRequest>();

        if (type == MessageType::RESPONSE_OK)
            return std::make_unique<response::OkResponse>();
        if (type == MessageType::RESPONSE_ERROR)
            return std::make_unique<response::ErrorResponse>();
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