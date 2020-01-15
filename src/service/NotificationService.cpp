#include "NotificationService.hpp"

#include <player_protocol/MessageSerializer.hpp>

#include <player_protocol/changed/EqualizerParametersChanged.hpp>
#include <player_protocol/changed/MediumChangedMessage.hpp>
#include <player_protocol/changed/PlayerStateChangedMessage.hpp>
#include <player_protocol/changed/TimeChangedMessage.hpp>
#include <player_protocol/changed/VolumeChangedMessage.hpp>

namespace service {

    NotificationService::NotificationService(sys::BluetoothCommunicationProvider &communicationProvider)
        : communicationProvider(communicationProvider)
        , buffer{} {}

    void NotificationService::initializeCallbacks(audio::PlaylistPlayer &player) {
        player.setOnStateChanged([&](auto state) { handleStateChanged(state); });
        player.setOnProgressChanged([&](auto currentTime, auto totalTime) { handleTimeChanged(currentTime, totalTime); });
        player.setOnMediumChanged([&](auto& medium) { handleMediumChanged(medium); });
        player.setOnVolumeChanged([&](auto volume) { handleVolumeChanged(volume); });
    }

    void NotificationService::initializeCallbacks(audio::filter::DigitalEqualizerFilter &filter) {
        filter.setOnParametersChanged([&](auto& parameters) { handleEqualizerParametersChanged(parameters); });
    }

    void NotificationService::handleStateChanged(audio::AudioPlayer::State state) {
        player_protocol::changed::PlayerStateChangedMessage message(static_cast<player_protocol::PlayerState>(state));
        std::uint32_t size = player_protocol::MessageSerializer::serialize(message, buffer.data());
        communicationProvider.transmitSizedMessage(buffer.data(), size);
    }

    void NotificationService::handleTimeChanged(float currentTime, float totalTime) {
        player_protocol::changed::TimeChangedMessage message(currentTime, totalTime);
        std::uint32_t size = player_protocol::MessageSerializer::serialize(message, buffer.data());
        communicationProvider.transmitSizedMessage(buffer.data(), size);
    }

    void NotificationService::handleMediumChanged(const std::string &medium) {
        player_protocol::changed::MediumChangedMessage message(medium);
        std::uint32_t size = player_protocol::MessageSerializer::serialize(message, buffer.data());
        communicationProvider.transmitSizedMessage(buffer.data(), size);
    }

    void NotificationService::handleVolumeChanged(std::uint32_t volume) {
        player_protocol::changed::VolumeChangedMessage message(volume);
        std::uint32_t size = player_protocol::MessageSerializer::serialize(message, buffer.data());
        communicationProvider.transmitSizedMessage(buffer.data(), size);
    }

    void NotificationService::handleEqualizerParametersChanged(const audio::filter::DigitalEqualizerParameters &parameters) {
        player_protocol::EqualizerParameters messageParameters;
        messageParameters.setGainDb(parameters.getGainDb());
        for (std::size_t i = 0; i < 10; ++i)
            messageParameters.setGainDbAt(i, parameters.getDbGain(i));
        player_protocol::changed::EqualizerParametersChanged message(messageParameters);
        std::uint32_t size = player_protocol::MessageSerializer::serialize(message, buffer.data());
        communicationProvider.transmitSizedMessage(buffer.data(), size);
    }
}