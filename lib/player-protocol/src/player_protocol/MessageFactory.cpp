#include "MessageFactory.hpp"
#include <player_protocol/changed/TimeChangedMessage.hpp>
#include <player_protocol/changed/MediumChangedMessage.hpp>
#include <player_protocol/changed/VolumeChangedMessage.hpp>

#include <player_protocol/request/ChangeMediumRequest.hpp>
#include <player_protocol/request/ChangeVolumeRequest.hpp>
#include <player_protocol/request/PauseRequest.hpp>
#include <player_protocol/request/PlaylistRequest.hpp>
#include <player_protocol/request/PlayRequest.hpp>
#include <player_protocol/request/SeekRequest.hpp>
#include <player_protocol/request/StopRequest.hpp>

#include <player_protocol/response/ErrorResponse.hpp>
#include <player_protocol/response/OkResponse.hpp>
#include <player_protocol/response/PlaylistResponse.hpp>

namespace player_protocol {
    std::unique_ptr<Message> MessageFactory::create(MessageType type) {
        switch (type) {
            case MessageType::CHANGED_MEDIUM:
                return std::make_unique<changed::MediumChangedMessage>();
            case MessageType::CHANGED_TIME:
                return std::make_unique<changed::TimeChangedMessage>();
            case MessageType::CHANGED_VOLUME:
                return std::make_unique<changed::VolumeChangedMessage>();

            case MessageType::REQUEST_CHANGE_MEDIUM:
                return std::make_unique<request::ChangeMediumRequest>();
            case MessageType::REQUEST_CHANGE_VOLUME:
                return std::make_unique<request::ChangeVolumeRequest>();
            case MessageType::REQUEST_PAUSE:
                return std::make_unique<request::PauseRequest>();
            case MessageType ::REQUEST_PLAYLIST:
                return std::make_unique<request::PlaylistRequest>();
            case MessageType::REQUEST_PLAY:
                return std::make_unique<request::PlayRequest>();
            case MessageType::REQUEST_SEEK:
                return std::make_unique<request::SeekRequest>();
            case MessageType::REQUEST_STOP:
                return std::make_unique<request::StopRequest>();

            case MessageType::RESPONSE_ERROR:
                return std::make_unique<response::ErrorResponse>();
            case MessageType::RESPONSE_OK:
                return std::make_unique<response::OkResponse>();
            case MessageType::RESPONSE_PLAYLIST:
                return std::make_unique<response::PlaylistResponse>();

            default:
                throw std::invalid_argument("Unknown message type");
        }
    }
}