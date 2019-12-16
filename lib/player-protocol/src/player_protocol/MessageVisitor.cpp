#include "MessageVisitor.hpp"

#include <player_protocol/changed/MediumChangedMessage.hpp>
#include <player_protocol/changed//TimeChangedMessage.hpp>
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
    MessageVisitor::~MessageVisitor() = default;



    void MessageClientVisitor::handleMessage(const request::ChangeMediumRequest &message) {
        handleInvalidMessage(message);
    }

    void MessageClientVisitor::handleMessage(const request::ChangeVolumeRequest &message) {
        handleInvalidMessage(message);
    }

    void MessageClientVisitor::handleMessage(const request::PauseRequest &message) {
        handleInvalidMessage(message);
    }

    void MessageClientVisitor::handleMessage(const request::PlayRequest &message) {
        handleInvalidMessage(message);
    }

    void MessageClientVisitor::handleMessage(const request::SeekRequest &message) {
        handleInvalidMessage(message);
    }

    void MessageClientVisitor::handleMessage(const request::StopRequest &message) {
        handleInvalidMessage(message);
    }

    void MessageClientVisitor::handleMessage(const request::PlaylistRequest &message) {
        handleInvalidMessage(message);
    }


    void MessageServerVisitor::handleMessage(const changed::MediumChangedMessage &message) {
        handleInvalidMessage(message);
    }

    void MessageServerVisitor::handleMessage(const changed::TimeChangedMessage &message) {
        handleInvalidMessage(message);
    }

    void MessageServerVisitor::handleMessage(const changed::VolumeChangedMessage &message) {
        handleInvalidMessage(message);
    }

    void MessageServerVisitor::handleMessage(const response::ErrorResponse &message) {
        handleInvalidMessage(message);
    }

    void MessageServerVisitor::handleMessage(const response::OkResponse &message) {
        handleInvalidMessage(message);
    }

    void MessageServerVisitor::handleMessage(const response::PlaylistResponse &message) {
        handleInvalidMessage(message);
    }
}
