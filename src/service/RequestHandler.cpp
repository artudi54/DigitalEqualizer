#include "RequestHandler.hpp"
#include <algorithm>
#include <player_protocol/MessageSerializer.hpp>

#include <player_protocol/request/ChangeEqualizerParametersRequest.hpp>
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
using namespace player_protocol;

namespace service {
    RequestHandler::RequestHandler(sys::BluetoothCommunicationProvider &communicationProvider, audio::PlaylistPlayer &player, audio::filter::DigitalEqualizerFilter& filter)
        : communicationProvider(communicationProvider)
        , player(player)
        , filter(filter)
        , buffer{} {}

    void RequestHandler::progress() {
        while(communicationProvider.hasSizedMessage()) {
            communicationProvider.receiveSizedMessage(buffer.data());
            auto message = MessageSerializer::deserialize(buffer.data());
            message->visit(*this);
        }
    }

    void RequestHandler::handleMessage(const request::ChangeEqualizerParametersRequest &message) {
        const player_protocol::EqualizerParameters& messageParameters = message.getParameters();
        audio::filter::DigitalEqualizerParameters parameters;
        parameters.setGainDb(messageParameters.getGainDb());
        for (std::size_t i = 0; i < 10; ++i)
            parameters.setDbGainAt(i, messageParameters.getGainDbAt(i));
        filter.setParameters(parameters);
    }

    void RequestHandler::handleMessage(const request::ChangeMediumRequest &message) {
        auto& files = player.getPlaylist().getFilePaths();
        auto it = std::find(files.begin(), files.end(), message.getNewMedium());
        if (it != files.end()) {
            player.setCurrentTrackNumber(it - files.begin());
            sendMessage(response::OkResponse());
        }
        else
            sendMessage(response::ErrorResponse("Cannot find file to play in playlist"));
    }

    void RequestHandler::handleMessage(const request::ChangeVolumeRequest &message) {
        try {
            player.setVolume(message.getNewVolume());
        }
        catch (std::exception& exc) {
            sendMessage(response::ErrorResponse(exc.what()));
            return;
        }
        sendMessage(response::OkResponse());
    }

    void RequestHandler::handleMessage(const request::PauseRequest &message) {
        (void)message;

        try {
            player.pause();
        }
        catch (std::exception& exc) {
            sendMessage(response::ErrorResponse(exc.what()));
            return;
        }
        sendMessage(response::OkResponse());
    }

    void RequestHandler::handleMessage(const request::PlaylistRequest &message) {
        (void)message;

        sendMessage(response::PlaylistResponse(player.getPlaylist().getFilePaths()));
    }

    void RequestHandler::handleMessage(const request::PlayRequest &message) {
        (void)message;

        try {
            player.play();
        }
        catch (std::exception& exc) {
            sendMessage(response::ErrorResponse(exc.what()));
            return;
        }
        sendMessage(response::OkResponse());
    }

    void RequestHandler::handleMessage(const request::ResetRequest &message) {
        (void)message;

        try {
            player.reset();
            filter.resetParameters();
        }
        catch (std::exception& exc) {
            sendMessage(response::ErrorResponse(exc.what()));
            return;
        }
        sendMessage(response::OkResponse());
    }

    void RequestHandler::handleMessage(const request::SeekRequest &message) {
        try {
            player.seek(message.getPosition());
        }
        catch (std::exception& exc) {
            sendMessage(response::ErrorResponse(exc.what()));
            return;
        }
        sendMessage(response::OkResponse());
    }

    void RequestHandler::handleMessage(const request::StopRequest &message) {
        (void)message;

        try {
            player.stop();
        }
        catch (std::exception& exc) {
            sendMessage(response::ErrorResponse(exc.what()));
            return;
        }
        sendMessage(response::OkResponse());
    }

    void RequestHandler::handleInvalidMessage(const Message &message) {
        (void)message;
        sendMessage(response::ErrorResponse("Server received message not being request"));
    }

    void RequestHandler::sendMessage(const Message &message) {
        std::uint32_t length = MessageSerializer::serialize(message, buffer.data());
        communicationProvider.transmitSizedMessage(buffer.data(), length);
    }
}