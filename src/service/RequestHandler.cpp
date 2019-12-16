#include "RequestHandler.hpp"
#include <player_protocol/MessageSerializer.hpp>
#include <player_protocol/request/PlayRequest.hpp>
#include <player_protocol/request/ChangeVolumeRequest.hpp>

namespace service {
    RequestHandler::RequestHandler(sys::BluetoothCommunicationProvider &communicationProvider, audio::PlaylistPlayer &player)
        : communicationProvider(communicationProvider)
        , player(player)
        , buffer{} {}

    void RequestHandler::progress() {
        if (!communicationProvider.hasSizedMessage())
            return;

        communicationProvider.receiveSizedMessage(buffer.data());
        auto message = player_protocol::MessageSerializer::deserialize(buffer.data());
        message->visit(*this);
    }

    void RequestHandler::handleMessage(const player_protocol::request::ChangeMediumRequest &message) {

    }

    void RequestHandler::handleMessage(const player_protocol::request::ChangeVolumeRequest &message) {
        try {
            player.setVolume(message.getNewVolume());
        }
        catch (std::exception& exc) {
        }
    }

    void RequestHandler::handleMessage(const player_protocol::request::PauseRequest &message) {

    }

    void RequestHandler::handleMessage(const player_protocol::request::PlaylistRequest &message) {

    }

    void RequestHandler::handleMessage(const player_protocol::request::PlayRequest &message) {

    }

    void RequestHandler::handleMessage(const player_protocol::request::SeekRequest &message) {

    }

    void RequestHandler::handleMessage(const player_protocol::request::StopRequest &message) {

    }

    void RequestHandler::handleInvalidMessage(const player_protocol::Message &message) {

    }

    void RequestHandler::sendMessage(const player_protocol::Message &message) {

    }
}