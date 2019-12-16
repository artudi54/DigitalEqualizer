#include "NotificationService.hpp"

#include <player_protocol/MessageSerializer.hpp>

#include <player_protocol/changed/MediumChangedMessage.hpp>
#include <player_protocol/changed/TimeChangedMessage.hpp>
#include <player_protocol/changed/VolumeChangedMessage.hpp>

namespace service {

    NotificationService::NotificationService(sys::BluetoothCommunicationProvider &communicationProvider)
        : communicationProvider(communicationProvider)
        , buffer{} {}

    void NotificationService::initializeCallbacks(audio::AudioPlayer &player) {
        player.setOnProgressChanged([&](auto currentTime, auto totalTime) { handleTimeChanged(currentTime, totalTime); });
        player.setOnMediumChanged([&](auto& medium) { handleMediumChanged(medium); });
        player.setOnVolumeChanged([&](auto volume) { handleVolumeChanged(volume); });
    }

    void NotificationService::handleTimeChanged(float currentTime, float totalTime) {
        player_protocol::changed::TimeChangedMessage message;
        message.currentTime = currentTime;
        message.totalTime = totalTime;
        std::uint32_t size = player_protocol::MessageSerializer::serialize(message, buffer.data());
        communicationProvider.transmitSizedMessage(buffer.data(), size);
    }

    void NotificationService::handleMediumChanged(const std::string &medium) {
        player_protocol::changed::MediumChangedMessage message;
        message.medium = medium;
        std::uint32_t size = player_protocol::MessageSerializer::serialize(message, buffer.data());
        communicationProvider.transmitSizedMessage(buffer.data(), size);
    }

    void NotificationService::handleVolumeChanged(std::uint32_t volume) {
        player_protocol::changed::VolumeChangedMessage message;
        message.volume = volume;
        std::uint32_t size = player_protocol::MessageSerializer::serialize(message, buffer.data());
        communicationProvider.transmitSizedMessage(buffer.data(), size);
    }
}