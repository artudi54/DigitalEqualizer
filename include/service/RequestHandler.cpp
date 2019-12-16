#include "RequestHandler.hpp"
#include <player_protocol/MessageSerializer.hpp>
#include <player_protocol/request/PlayRequest.hpp>

namespace service {

    RequestHandler::RequestHandler(sys::BluetoothCommunicationProvider &communicationProvider,
                                   audio::AudioPlayer &player)
        : communicationProvider(communicationProvider)
        , player(player) {}

    void RequestHandler::progress() {
        if (!communicationProvider.hasSizedMessage())
            return;

        communicationProvider.receiveSizedMessage(buffer.data());
        auto message = player_protocol::MessageSerializer::deserialize(buffer.data());
        if (dynamic_cast<player_protocol::request::PlayRequest*>(message.get()))
            handlePlay();
    }

    void RequestHandler::handlePlay() {
        player.play();
    }

    void RequestHandler::handlePause() {

    }
}